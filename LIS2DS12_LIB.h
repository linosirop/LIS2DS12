#ifndef NULL
#ifdef __cplusplus
#define NULL         0
#else
#define NULL         ((void *) 0)
#endif
#endif
#ifndef TRUE
#define TRUE                                      UINT8_C(1)
#endif
#ifndef FALSE
#define FALSE                                     UINT8_C(0)
#endif

///  В данном примере используется учебная плата MiniZed в качестве ведущего устройства с использованием акселерометра

#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"

#include <stdbool.h>

/// 1. Настройка макросов

#define SUCCESS 0
#define ERR -1



#define LIS2DS12_REG_WHO_AM_I                       UINT8_C(0x0F)
#define WHO_AM_I_NORM_VALUE                         UINT8_C(0b01000011)



#define LIS2DS12_REG_CTRL_1                         UINT8_C(0x20)


#define	ODR_HZ_PD                                   0

#define	ODR_HZ_LP_1 								0b1000
#define	ODR_HZ_LP_12_5 								0b1001
#define	ODR_HZ_LP_25						   		0b1010
#define	ODR_HZ_LP_50 								0b1011
#define	ODR_HZ_LP_100 								0b1100
#define	ODR_HZ_LP_200 								0b1101
#define	ODR_HZ_LP_400 								0b1110
#define	ODR_HZ_LP_800 								0b1111

#define	ODR_HZ_HR_12_5								0b0001
#define	ODR_HZ_HR_25 								0b0010
#define	ODR_HZ_HR_50 								0b0011
#define	ODR_HZ_HR_100 								0b0100
#define	ODR_HZ_HR_200 								0b0101
#define	ODR_HZ_HR_400 								0b0110
#define	ODR_HZ_HR_800								0b0111

#define	ODR_HF_1600 								0b0101
#define	ODR_HF_3200 								0b0110
#define	ODR_HF_6400									0b0111

#define FS_2_DEF                                    UINT8_C(0b00)
#define FS_4_DEF                                    UINT8_C(0b10)
#define FS_8_DEF                                    UINT8_C(0b11)
#define FS_16_DEF                                   UINT8_C(0b01)
#define HF_ODR_DEF                                  UINT8_C(1 << 1)



#define LIS2DS12_REG_CTRL_2                         UINT8_C(0x21)


#define BOOT_DEF 									UINT8_C(1 << 7)
#define SOFT_RESET_DEF 								UINT8_C(1 << 6)
#define FUNC_CFG_EN_DEF 							UINT8_C(1 << 4)
#define FDS_SLOPE_DEF 								UINT8_C(1 << 3)
#define IF_ADD_INC_DEF								UINT8_C(1 << 2)
#define I2C_DISABLE_DEF 							UINT8_C(1 << 1)
#define I2C_ENABLE_DEF 								UINT8_C(0b11111101)
#define SIM_DEF 									UINT8_C(1)
#define AGREE_UPGRATE_PEDOMETR_SETTINGS_DEF			UINT8_C(1 << 5)
#define DISAGREE_UPGRATE_PEDOMETR_SETTINGS_DEF		UINT8_C(0b11011111)



#define LIS2DS12_REG_CTRL_3                         UINT8_C(0x22)


#define TAPX_ENABLE_DEF      				  			    UINT8_C(1 << 5)
#define TAPX_DISABLE_DEF      				  			    UINT8_C(0b11011111)
#define TAPY_ENABLE_DEF      				  				UINT8_C(1 << 4)
#define TAPY_DISABLE_DEF      				  				UINT8_C(0b11101111)
#define TAPZ_ENABLE_DEF     				  				UINT8_C(1 << 3)
#define TAPZ_DISABLE_DEF     				  				UINT8_C(0b11110111)
#define LIR_DEF      				  				UINT8_C(1 << 2)
#define H_LACTIVE_DEF       				  		UINT8_C(1 << 1)
#define PP_OD_DEF      				  				UINT8_C(1)



#define LIS2DS12_REG_CTRL_4                         UINT8_C(0x23)



#define LIS2DS12_REG_CTRL_5                         UINT8_C(0x24)



#define LIS2DS12_REG_FIFO_CTRL                      UINT8_C(0x25)



#define LIS2DS12_REG_OUT_TEMP      				    UINT8_C(0x26)
#define LIS2DS12_REG_STATUS                         UINT8_C(0x27)
#define LIS2DS12_REG_OUT_X_L                        UINT8_C(0x28)
#define LIS2DS12_REG_OUT_Y_L                        UINT8_C(0x2A)
#define LIS2DS12_REG_OUT_Z_L                        UINT8_C(0x2C)
#define LIS2DS12_REG_FIFO_THS                       UINT8_C(0x2E)
#define LIS2DS12_REG_FIFO_SRC                       UINT8_C(0x2F)
#define LIS2DS12_REG_FIFO_SAMPLES                   UINT8_C(0x30)
#define LIS2DS12_REG_TAP_6D_THS                     UINT8_C(0x31)
#define LIS2DS12_REG_INT_DUR                        UINT8_C(0x32)
#define LIS2DS12_REG_WAKE_UP_THS                    UINT8_C(0x33)
#define LIS2DS12_REG_WAKE_UP_DUR                    UINT8_C(0x34)
#define LIS2DS12_REG_FREE_FALL                      UINT8_C(0x35)
#define LIS2DS12_REG_STATUS_DUP                     UINT8_C(0x36)
#define LIS2DS12_REG_WAKE_UP_SRC                    UINT8_C(0x37)
#define LIS2DS12_REG_TAP_SRC                        UINT8_C(0x38)
#define LIS2DS12_REG_6D_SRC                         UINT8_C(0x39)
#define LIS2DS12_REG_STEP_COUNTER_MINTHS            UINT8_C(0x3A)
#define LIS2DS12_REG_STEP_COUNTER_L                 UINT8_C(0x3B)
#define LIS2DS12_REG_FUNC_CK_GATE                   UINT8_C(0x3D)
#define LIS2DS12_REG_FUNC_SRC                       UINT8_C(0x3E)
#define LIS2DS12_REG_FUNC_CTRL                      UINT8_C(0x3F)





typedef int (*LISWRITE)(uint8_t reg_addr, const uint8_t* reg_data, uint32_t len);
typedef int (*LISREAD)(uint8_t reg_addr, uint8_t* reg_data, uint32_t len);
typedef int (*LISRESET)(uint8_t reg_addr, uint8_t* reg_data, uint32_t len);


typedef struct LIS2DS12
{
	LISWRITE write;
	LISREAD read;
	uint8_t slave_addr;
} LIS2DS12;



int LIS2DS12_Check_WIA(LIS2DS12* def); // 1 -> good, 0 -> bad



////// CTRL1  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    |  |  | ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    V  V  V ////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	    ODR_PD_MODE = 0,
		ODR_LP_MODE = 1,
		ORD_HR_MODE = 0
}LIS2DS12_ODR_Hz_MODE;

typedef enum
{
		ODR_PD = 0,
		ODR_HZ_1 = 0,
		ODR_HZ_12_5 = 0b001,
		ODR_HZ_25 = 0b010,
		ODR_HZ_50 = 0b011,
		ODR_HZ_100 = 0b100,
		ODR_HZ_200 = 0b101,
		ODR_HZ_400 = 0b110,
		ODR_HZ_800 = 0b111,
		ODR_HZ_1600 = 0b101,
		ODR_HZ_3200 = 0b110,
		ODR_HZ_6400 = 0b111,
}LIS2DS12_ODR_Hz;

typedef enum
{
	FS_2 = 0,
	FS_4 = 2,
	FS_8 = 3,
	FS_16 = 1,
}LIS2DS12_FS;

typedef struct LIS2DS12_CTRL_1
{
	union
	{
		uint8_t byte;

		struct
		{
			uint8_t BDU : 1; // 1 -> ON , 0 -> OFF
			uint8_t HF_ODR : 1; // 1 -> ON , 0 -> OFF
			LIS2DS12_FS fs : 2;
			LIS2DS12_ODR_Hz ODR : 3;
			LIS2DS12_ODR_Hz_MODE mode : 1;
		} bits;
	};
} LIS2DS12_CTRL_1;

int LIS2DS12_SetCTRL1(LIS2DS12_CTRL_1* par, LIS2DS12* def);

////// CTRL2  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    |  |  | ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    V  V  V ////////////////////////////////////////////////////////////////////////////////////////////////////////////


//	b1 -> BOOT_RESET -> Forces the reboot of the flash content in the trimming and configuration registers.
//	b2 -> SOFT_RESET -> Soft reset acts as reset for all control registers, then goes to 0. Default value: 0 (0: disabled; 1: enabled)
//	b3 -> 0 -> This bit must be set to ‘0’ for the correct operation of the device
//	b4 -> FUNC_CFG_EN -> Access to pedometer/sensor hub advanced configuration registers from address 2Bh to 3Fh. Default value: 0 (0: disable the access to pedometer/sensor hub advanced configuration registers; 1: enable the access to pedometer/sensor hub advanced configuration registers)
//	b5 -> FDS_SLOPE -> High-pass filter data selection on output register and FIFO. Default value: 0 (0: internal filter bypassed; 1: internal filter enabled on output register and FIFO)
//	b6 -> IF_ADD_INC -> Register address automatically incremented during multiple byte access with a serial interface (I 2C or SPI). Default value: 1 (0: disabled; 1: enabled)
//	b7 -> I2C_DISABLE -> Disable I2C communication protocol. Default value: 0 (0: SPI and I2C interfaces enabled; 1: I 2C mode disabled)
//	b8 -> SIM -> SPI serial interface mode selection. Default value: 0 0: 4-wire interface; 1: 3-wire interface

typedef struct LIS2DS12_CTRL_2
{
	union
	{
		uint8_t byte;

		struct
		{
			uint8_t SIM : 1;
			uint8_t I2C_SWICH : 1;
			uint8_t IF_ADD_INC : 1;
			uint8_t FDS_SLOPE : 1;
			uint8_t FUNC_CFG_EN : 1;
			uint8_t b3 : 1; // must be 0
			uint8_t SOFT_RESET : 1;
			uint8_t BOOT_RESET : 1;
		} bits;
	};
} LIS2DS12_CTRL_2;

int LIS2DS12_SetCTRL2(LIS2DS12_CTRL_2* par, LIS2DS12* def);


////// CTRL3  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    |  |  | ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    V  V  V ////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  NORMAL MODE
//	b1 -> 0
//	b2 -> 0
//  POSITIVE SIGN SELF-TEST
//	b1 -> 0
//	b2 -> 1
//  NEGATIVE SIGN SELF-TEST
//	b1 -> 1
//	b2 -> 0
//  NOT ALLOWED
//	b1 -> 1
//	b2 -> 1

//	b3 -> TAPX -> Tap recognition on X direction enable. (0: disabled; 1: enabled)
//	b4 -> TAPY -> Tap recognition on Y direction enable. (0: disabled; 1: enabled)
//	b5 -> TAPZ -> Tap recognition on Z direction enable. (0: disabled; 1: enabled)
//	b6 -> LIR -> Latched Interrupt (0: disabled; 1: enabled)
//	b7 -> H_LACTIVE -> Interrupt active high, low. (0: active high; 1: active low)
//	b8 -> PP_OD -> Push-pull/open-drain selection on interrupt pad. (0: push-pull; 1: open-drain)

typedef enum
{

	NORMAL_MODE = 0b00, POSITIVE_SIGN_SELF_TEST = 0b01,
	NEGATIVE_SIGN_SELF_TEST = 0b10, NOT_ALLOWED = 0b11

}LIS2DS12_SELF_TEST_MODE;

typedef struct LIS2DS12_CTRL_3
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t PP_OD : 1;
			uint8_t H_LACTIVE : 1;
			uint8_t LIR : 1;
			uint8_t TAPZ : 1;
			uint8_t TAPY : 1;
			uint8_t TAPX : 1;
			LIS2DS12_SELF_TEST_MODE mode : 2;
		} bits;
	};
} LIS2DS12_CTRL_3;

int LIS2DS12_SetCTRL3(LIS2DS12_CTRL_3* par, LIS2DS12* def);



////// CTRL4  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    |  |  | ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    V  V  V ////////////////////////////////////////////////////////////////////////////////////////////////////////////


// b1 -> INT1_MASTER_DRDY -> Manage the Master DRDY signal on INT1 pad.
// b2 -> INT1_S_TAP       -> Single-tap recognition is routed on INT1 pad
// b3 -> INT1_WU		  -> Wakeup recognition is routed on INT1 pad
// b4 -> INT1_FF		  -> Free-fall recognition is routed on INT1 pad
// b5 -> INT1_TAP		  -> Double-tap recognition is routed on INT1 pad
// b6 -> INT1_6D		  -> 6D recognition is routed on INT1 pad
// b7 -> INT1_FTH		  -> FIFO threshold interrupt is routed on INT1 pad
// b8 -> INT1_DRDY		  -> Data-Ready is routed on INT1 pad

typedef struct LIS2DS12_CTRL_4
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t INT1_DRDY : 1;
			uint8_t INT1_FTH : 1;
			uint8_t INT1_6D : 1;
			uint8_t INT1_TAP : 1;
			uint8_t INT1_FF : 1;
			uint8_t INT1_WU : 1;
			uint8_t INT1_S_TAP : 1;
			uint8_t INT1_MASTER_DRDY : 1;
		} bits;
	};
} LIS2DS12_CTRL_4;

int LIS2DS12_SetCTRL4(LIS2DS12_CTRL_4* par, LIS2DS12* def);

////// CTRL5  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    |  |  | ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    V  V  V ////////////////////////////////////////////////////////////////////////////////////////////////////////////


// b1 ->  DRDY_PULSED	 -> Manage the Master DRDY signal on INT1 pad.
// b2 ->  INT2_BOOT      -> Single-tap recognition is routed on INT1 pad
// b3 ->  INT2_ON_INT1	 -> Wakeup recognition is routed on INT1 pad
// b4 ->  INT2_TILT		 -> Free-fall recognition is routed on INT1 pad
// b5 ->  INT2_SIG_MOT   -> Double-tap recognition is routed on INT1 pad
// b6 ->  INT2_STEP_DET  -> 6D recognition is routed on INT1 pad
// b7 ->  INT2_FTH		 -> FIFO threshold interrupt is routed on INT1 pad
// b8 ->  INT2_DRDY		 -> Data-Ready is routed on INT1 pad

typedef struct LIS2DS12_CTRL_5
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t INT2_DRDY : 1;
			uint8_t INT2_FTH : 1;
			uint8_t INT2_STEP_DET : 1;
			uint8_t INT2_SIG_MOT : 1;
			uint8_t INT2_TILT : 1;
			uint8_t INT2_ON_INT1 : 1;
			uint8_t INT2_BOOT : 1;
			uint8_t DRDY_PULSED : 1;
		} bits;
	};
} LIS2DS12_CTRL_5;

int LIS2DS12_SetCTRL5(LIS2DS12_CTRL_5* par, LIS2DS12* def);

////// FIFO_CTRL ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     |  |  |   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     V  V  V   ////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
		MODE_BYPASS = 0b000, MODE_FIFO = 0b001,
		CONTINUOUS_TO_FIFO = 0b011, BYPASS_TO_CONTINUOUS = 0b100, MODE_CONTINIOUS = 0b110
		//BYPASS MODE - > FIFO turned off
		//FIFO MODE - > Stops_collecting data when FIFO is full
		//CONTINUOUS TO FIFO - > STREAM MODE until trigger is deasserted then FIFO mode
		//BYPASS TO CONTINUOUS - > Bypass mode until trigger is deasserted, then FIFO mode
		//CONTINIOUS_MODE - >  Data If the FIFO is full, the new sample over writes the older sample
}LIS2DS12_FIFO_MODE;

typedef struct LIS2DS12_FIFO_CTRL
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t IF_CS_PU_DIS : 1;
			uint8_t : 1;
			uint8_t : 1;
			uint8_t MODULE_TO_FIFO : 1;
			uint8_t INT2_STEP_COUNT_OV : 1;
			LIS2DS12_FIFO_MODE mode : 3;
		} bits;
	};
} LIS2DS12_FIFO_CTRL;

int LIS2DS12_SetFIFO_CTRL(LIS2DS12_FIFO_CTRL* par, LIS2DS12* def);

int LIS2DS12_GetTemp();

int LIS2DS12_SetODR(LIS2DS12_ODR_Hz ODR, LIS2DS12_ODR_Hz_MODE mode, LIS2DS12* def);

int LIS2DS12_SetFS(LIS2DS12_FS fs, LIS2DS12* def);

int LIS2DS12_SetHF_ODR(bool LIS2DS12_HF_ODR, LIS2DS12* def);

int LIS2DS12_SetBDU(bool BDU, LIS2DS12* def);

int LIS2DS12_BOOTRESET(LIS2DS12* def);

int LIS2DS12_SOFT_RESET(LIS2DS12* def);

int LIS2DS12_UPGRATE_PEDOMETR_SETTINGS(bool mode, LIS2DS12* def);// mode - > on\off 1\0

int LIS2DS12_FUNC_CFG_EN(bool mode, LIS2DS12* def);// mode - > on\off 1\0

int LIS2DS12_FDS_SLOPE(bool mode, LIS2DS12* def);// mode - > on\off 1\0

int LIS2DS12_IF_ADD_INC(bool mode, LIS2DS12* def);// mode - > on\off 1\0

int LIS2DS12_I2C_SWICH(bool mode, LIS2DS12* def);// mode - > on\off 1\0

int LIS2DS12_SIM(bool mode, LIS2DS12* def);// mode - > on\off 1\0

int LIS2DS12_SELF_TEST_ENABLE(LIS2DS12_SELF_TEST_MODE mode, LIS2DS12* def);

int LIS2DS12_TAP_X(bool mode, LIS2DS12* def);

int LIS2DS12_TAP_Y(bool mode, LIS2DS12* def);

int LIS2DS12_TAP_Z(bool mode, LIS2DS12* def);

int LIS2DS12_LIR(bool mode, LIS2DS12* def);

int LIS2DS12_H_LACTIVE(bool mode, LIS2DS12* def);

int LIS2DS12_PP_OD(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_MASTER_DRDY(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_S_TAP(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_WU(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_FF(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_TAP(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_6D(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_FTH(bool mode, LIS2DS12* def);

int LIS2DS12_INT1_DRDY(bool mode, LIS2DS12* def);

int LIS2DS12_DRDY_PULSED(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_BOOT(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_ON_INT1(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_TILT(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_SIG_MOT(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_STEP_DET(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_FTH(bool mode, LIS2DS12* def);

int LIS2DS12_INT2_DRDY(bool mode, LIS2DS12* def);

int LIS2DS12_SETFIFO_MODE(LIS2DS12_FIFO_MODE* mode, LIS2DS12* def);

int LIS2DS12_INT2_STEP_COUNT_OV(bool mode, LIS2DS12* def);

int LIS2DS12_MODULE_TO_FIFO(bool mode, LIS2DS12* def);

int LIS2DS12_IF_CS_PU_DIS(bool mode, LIS2DS12* def);

typedef struct LIS2DS12_STATUS
{
	union
	{
		uint8_t byte;
		struct
		{
			bool DRDY : 1;
			bool FF_IA : 1;
			bool _6D_IA : 1;
			bool SINGLE_TAP : 1;
			bool DOUBLE_TAP : 1;
			bool SLEEP_STATE : 1;
			bool WU_IA : 1;
			bool FIFO_THS : 1;
		} bits;
	};
} LIS2DS12_STATUS;

int LIS2DS12_Get_Status(LIS2DS12* def, LIS2DS12_STATUS *ret);

uint16_t LIS2DS12_OUT_X(LIS2DS12* def);
uint16_t LIS2DS12_OUT_Y(LIS2DS12* def);
uint16_t LIS2DS12_OUT_Z(LIS2DS12* def);

typedef struct LIS2DS12_FIFO_THS
{
	union
	{
		uint8_t byte;
		struct
		{
			bool FTH0 : 1;
			bool FTH1 : 1;
			bool FTH2 : 1;
			bool FTH3 : 1;
			bool FTH4 : 1;
			bool FTH5 : 1;
			bool FTH6 : 1;
			bool FTH7 : 1;
		} bits;
	};
} LIS2DS12_FIFO_THS;

int LIS2DS12_SET_FIFO_THS(LIS2DS12_FIFO_THS* par, LIS2DS12* def);

int LIS2DS12_GET_FIFO_THS(LIS2DS12* def, LIS2DS12_FIFO_THS* ret);

typedef struct LIS2DS12_FIFO_SRC
{
	union
	{
		uint8_t byte;
		struct
		{
			bool DIFF8 : 1;
			bool FIFOOVR : 1;
			bool FTH : 1;

		} bits;
	};
} LIS2DS12_FIFO_SRC;
int LIS2DS12_GET_FIFO_SRC(LIS2DS12* def, LIS2DS12_FIFO_SRC* ret);

int LIS2DS12_GET_FIFO_SAMPLES(LIS2DS12* def, uint8_t* ret);

typedef enum
{
	_80_degrees = 0, _70_degrees = 1,
	_60_degrees = 2, _50_degrees = 3

}LIS2DS12_6D_THS;

typedef struct LIS2DS12_TAP_6D_THS
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t TAP_THS : 5;
			LIS2DS12_6D_THS degrees: 2;
			bool _4D_EN : 1;

		} bits;
	};
} LIS2DS12_TAP_6D_THS;



int LIS2DS12_SET_TAP_6D_THS(LIS2DS12* def, LIS2DS12_TAP_6D_THS* par) ;



int LIS2DS12_GET_TAP_6D_THS(LIS2DS12* def, uint8_t* ret);
typedef struct LIS2DS12_INT_DUR
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t SHOCK : 2;
			uint8_t QUIET : 2;
			uint8_t LAT : 4;

		} bits;
	};
} LIS2DS12_INT_DUR;

int LIS2DS12_GET_INT_DUR(LIS2DS12* def, LIS2DS12_INT_DUR* ret);
int LIS2DS12_SET_INT_DUR(LIS2DS12* def, LIS2DS12_INT_DUR* par);





typedef struct LIS2DS12_WAKE_UP_THS
{
	union
	{
		uint8_t byte;
		struct
		{
			bool WU_THS : 1;
			bool SLEEP_ON : 1;
			uint8_t SINGLE_DOUBLE_TAP : 6;

		} bits;
	};
} LIS2DS12_WAKE_UP_THS;

int LIS2DS12_GET_WAKE_UP_THS(LIS2DS12* def, LIS2DS12_WAKE_UP_THS* ret);
int LIS2DS12_SET_WAKE_UP_THS(LIS2DS12* def, LIS2DS12_WAKE_UP_THS* par);

typedef struct LIS2DS12_WAKE_UP_DUR
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t SLEEP_DUR : 4;
			bool INT1_FSS7 : 1;
			uint8_t WU_DUR : 2;
			bool DUR5 : 1;

		} bits;
	};
} LIS2DS12_WAKE_UP_DUR;

int LIS2DS12_GET_WAKE_UP_DUR (LIS2DS12* def, LIS2DS12_WAKE_UP_DUR* ret);
int LIS2DS12_SET_WAKE_UP_DUR (LIS2DS12* def, LIS2DS12_WAKE_UP_DUR* par);

typedef enum
{
	LSB_5 = 0,LSB_7 = 1,LSB_8 = 2,
	LSB_10 = 3,LSB_11 = 4,LSB_13 = 5,
	LSB_15 = 6,LSB_16 = 7
}LIS2DS12_FF_THS;

typedef struct LIS2DS12_FREE_FALL
{
	union
	{
		uint8_t byte;
		struct
		{
			LIS2DS12_FF_THS ff_fhs : 3;
			uint8_t FF_DUR : 5;

		} bits;
	};
} LIS2DS12_FREE_FALL;


int LIS2DS12_GET_FREE_FALL(LIS2DS12* def, LIS2DS12_FREE_FALL* ret);
int LIS2DS12_SET_FREE_FALL(LIS2DS12* def, LIS2DS12_FREE_FALL* par);


typedef struct LIS2DS12_STATUS_DUP
{
	union
	{
		uint8_t byte;
		struct
		{
			bool DRDY : 1;
			bool FF_IA : 1;
			bool _6D_IA : 1;
			bool SINGLE_TAP : 1;
			bool DOUBLE_TAP : 1;
			bool SLEEP_STATE : 1;
			bool WU_IA : 1;
			bool OVR : 1;
		} bits;
	};
} LIS2DS12_STATUS_DUP;

int LIS2DS12_GET_STATUS_DUP(LIS2DS12* def, LIS2DS12_STATUS_DUP* ret);

typedef struct LIS2DS12_WAKE_UP_SRC
{
	union
	{
		uint8_t byte;
		struct
		{
			bool Z_WU : 1;
			bool Y_WU : 1;
			bool X_WU : 1;
			bool WU_IA : 1;
			bool SLEEP_STATE_IA : 1;
			bool FF_IA : 1;
			bool : 1;
			bool : 1;
		} bits;
	};
} LIS2DS12_WAKE_UP_SRC;

int LIS2DS12_GET_WAKE_UP_SRC(LIS2DS12* def, LIS2DS12_WAKE_UP_SRC* ret);

typedef struct LIS2DS12_TAP_SRC
{
	union
	{
		uint8_t byte;
		struct
		{
			bool Z_TAP : 1;
			bool Y_TAP : 1;
			bool X_TAP : 1;
			bool TAP_SIGN : 1;
			bool DOUBLE_TAP : 1;
			bool SINGLE_TAP : 1;
			bool TAP_IA : 1;
			bool : 1;
		} bits;
	};
} LIS2DS12_TAP_SRC;

int LIS2DS12_GET_TAP_SRC(LIS2DS12* def, LIS2DS12_TAP_SRC* ret);

typedef struct LIS2DS12_6D_SRC
{
	union
	{
		uint8_t byte;
		struct
		{
			bool XL : 1;
			bool XH : 1;
			bool YL : 1;
			bool YH : 1;
			bool ZL : 1;
			bool ZH : 1;
			bool _6D_IA : 1;
			bool : 1;
		} bits;
	};
} LIS2DS12_6D_SRC;

int LIS2DS12_GET_6D_SRC(LIS2DS12* def, LIS2DS12_6D_SRC* ret);



typedef struct LIS2DS12_STEP_COUNTER_MINTHS
{
	union
	{
		uint8_t byte;
		struct
		{
			uint8_t SC_MTHS : 6;
			bool PEDO4g : 1;
			bool RST_nSTEP : 1;

		} bits;
	};
} LIS2DS12_STEP_COUNTER_MINTHS;


int LIS2DS12_GET_STEP_COUNTER_MINTHS(LIS2DS12* def, LIS2DS12_STEP_COUNTER_MINTHS* ret);
int LIS2DS12_SET_STEP_COUNTER_MINTHS(LIS2DS12* def, LIS2DS12_STEP_COUNTER_MINTHS* par);


int LIS2DS12_GET_STEP_COUNTER(LIS2DS12* def, uint16_t* ret);

////

typedef enum
{
	FS_SRC_2g = 1, FS_SRC_4g = 2, FS_SRC_NOSCALING = 3
}LIS2DS12_FS_SRC;



int LIS2DS12_GET_FUNC_CK_GATE (LIS2DS12* def, uint8_t* ret);

//   a * ( x - 1 ) =>  a * x - a * 1


typedef struct LIS2DS12_FUNC_SRC
{
	union
	{
		uint8_t byte;
		struct
		{
			bool SENSORHUB_END_OP : 1;
			bool MODULE_READY : 1;
			bool b6 : 1;
			bool b5 : 1;
			bool b4 : 1;
			bool b3 : 1;
			bool b2 : 1;
			bool b1 : 1;
		} bits;
	};
} LIS2DS12_FUNC_SRC;
int LIS2DS12_GET_FUNC_SRC (LIS2DS12* def, LIS2DS12_FUNC_SRC* ret);


typedef struct LIS2DS12_FUNC_CTRL
{
	union
	{
		uint8_t byte;
		struct
		{
			bool STEP_CNT_ON : 1;
			bool SIGN_MOT_ON : 1;
			bool MASTER_ON : 1;
			bool TUD_EN : 1;
			bool TILT_ON : 1;
			bool MODULE_ON : 1;
			bool : 1;
			bool : 1;
		} bits;
	};
} LIS2DS12_FUNC_CTRL;

int LIS2DS12_GET_FUNC_CTRL(LIS2DS12* def, LIS2DS12_FUNC_CTRL* ret);
int LIS2DS12_SET_FUNC_CTRL(LIS2DS12* def, LIS2DS12_FUNC_CTRL* par);



