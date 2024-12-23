
#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LIS2DS12_LIB.h"




#define IIC_DEVICE_ID		XPAR_XIICPS_0_DEVICE_ID    /// Впишите айди устройства, который можно найти в xparametrs.h
#define IIC_SLAVE_ADDR		0b0011101   /// Адресс ведомого устройства из схематики
#define IIC_SCLK_RATE		100000   /// Клок



XIicPs Iic;
// Пример использования датчика с одноразовом выводом температуры и постоянным
// выводом раз в секунду ускорения по осям x,y,z

int write(uint8_t reg_addr, const uint8_t* reg_data, uint32_t len)
{
	uint8_t* mas = (uint8_t*)malloc(len + 1);
	mas[0] = reg_addr;
	memcpy(mas + (uint8_t)1, reg_data, len);
	while(XIicPs_BusIsBusy(&Iic));
    int Status = XIicPs_MasterSendPolled(&Iic, mas, len + (uint8_t)1, IIC_SLAVE_ADDR);


    return Status;
}

int read(uint8_t reg_addr, uint8_t* reg_data, uint32_t len)
{
	while(XIicPs_BusIsBusy(&Iic));
	XIicPs_MasterSendPolled(&Iic, &reg_addr, 1, IIC_SLAVE_ADDR);
	while(XIicPs_BusIsBusy(&Iic));
	return XIicPs_MasterRecvPolled(&Iic, reg_data, len, IIC_SLAVE_ADDR);

}



int main(void)
{


	LIS2DS12 def;
	def.read = read;
	def.write = write;

	int Status;
	XIicPs_Config *Config;

		Config = XIicPs_LookupConfig(IIC_DEVICE_ID);
		if (NULL == Config) {
			return XST_FAILURE;
		}

		Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

        //RESET

		LIS2DS12_SOFT_RESET(&def);

		//START

		uint8_t a;
		def.read(LIS2DS12_REG_WHO_AM_I, &a, 1);

		if(a == 0b01000011)
			xil_printf("WIM PORT IS NORMAL\n");
		else
			xil_printf("WIM PORT IS NOT NORMAL\n");

		/// CNTRL 1
		/// ODR register setting: power down (PD) and low power (LP)

		LIS2DS12_CTRL_1 ctrl1;

		ctrl1.byte = 0x60;

		ctrl1.bits.ODR = ODR_HZ_200;
		ctrl1.bits.fs = FS_8;

		LIS2DS12_SetCTRL1(&ctrl1, &def);

		/// CTRL 2

		LIS2DS12_CTRL_2 ctrl2;
		ctrl2.byte = 0;
		LIS2DS12_SetCTRL2(&ctrl2, &def);

		///CTRL 3

		LIS2DS12_CTRL_3 ctrl3;
		ctrl3.byte = 0b00111111;
		ctrl3.bits.mode = POSITIVE_SIGN_SELF_TEST;
		LIS2DS12_SetCTRL3(&ctrl3, &def);


		// CTRL 4

		LIS2DS12_CTRL_4 ctrl4;
		ctrl4.byte = 0x01;
		LIS2DS12_SetCTRL4(&ctrl4, &def);


	    //FIFO_CTRL

		LIS2DS12_FIFO_CTRL fifoctrl;
		fifoctrl.byte = 0b00000000;
		LIS2DS12_SetFIFO_CTRL(&fifoctrl, &def);

		///TEMP

		int temp = LIS2DS12_GetTemp(&def);
		printf("\nTemp = %d\nPress any key:\n", temp);
		getchar();
		LIS2DS12_STATUS stat;
		stat.byte = 0;

		while(1)
		{
			do
			{
			LIS2DS12_Get_Status(&def, &stat);
			}while(stat.bits.DRDY != 1);

					u16 x,y,z;

				/// x

					x = LIS2DS12_OUT_X(&def);

				/// y

					y = LIS2DS12_OUT_Y(&def);

			    /// z

					z = LIS2DS12_OUT_Z(&def);


			        x = x * 0.061;
		   			y = y * 0.061;
					z = z * 0.061;

					printf("Axis acceleration: x = %d   y = %d   z = %d\n", x ,y ,z );

					for(int i = 0; i < 5000000;i++);
		}

}


