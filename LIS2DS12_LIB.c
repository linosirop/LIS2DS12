#include"LIS2DS12_LIB.h"

typedef int (*LISWRITE)(uint8_t reg_addr, const uint8_t* reg_data, uint32_t len);
typedef int (*LISREAD)(uint8_t reg_addr, uint8_t* reg_data, uint32_t len);
typedef int (*LISRESET)(uint8_t reg_addr, uint8_t* reg_data, uint32_t len);





int Check_WIA(LIS2DS12* def) // 1 -> good, 0 -> bad // WHO I'M AM
{
	if (!(def->read))
		return ERR;

	uint8_t a;

	if (def->read)
		def->read(LIS2DS12_REG_WHO_AM_I, &a, 1);

	if (a == WHO_AM_I_NORM_VALUE)
		return SUCCESS;
	else
		return ERR;
}

int SetCTRL1(CTRL_1* par, LIS2DS12* def)
{
	// b1, b2, b3, b4 -> ODR_MODE
	// b5, b6 -> FS -> Full-scale selection 2, 4, 8, 16
	// b7 -> HF_ODR -> High-frequency ODR mode enable (1 - enable or 0 - not)
	// b8 -> BDU -> Block data update (1 - enable or 0 - not)

	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	int Status = def->write(LIS2DS12_REG_CTRL_1, &par->byte, 1);

	if (Status == 0)
		return SUCCESS;
	else
		return ERR;
}
int SetCTRL2(CTRL_2* par, LIS2DS12* def)
{
	//	b1 -> BOOT RESET-> Forces the reboot of the flash content in the trimming and configuration registers.
	//	b2 -> 0 -> This bit must be set to ‘0’ for the correct operation of the device
	//	b3 -> SOFT_RESET -> Soft reset acts as reset for all control registers, then goes to 0. Default value: 0 (0: disabled; 1: enabled)
	//	b4 -> FUNC_CFG_EN -> Access to pedometer/sensor hub advanced configuration registers from address 2Bh to 3Fh. Default value: 0 (0: disable the access to pedometer/sensor hub advanced configuration registers; 1: enable the access to pedometer/sensor hub advanced configuration registers)
	//	b5 -> FDS_SLOPE -> High-pass filter data selection on output register and FIFO. Default value: 0 (0: internal filter bypassed; 1: internal filter enabled on output register and FIFO)
	//	b6 -> IF_ADD_INC -> Register address automatically incremented during multiple byte access with a serial interface (I 2C or SPI). Default value: 1 (0: disabled; 1: enabled)
	//	b7 -> I2C_DISABLE -> Disable I2C communication protocol. Default value: 0 (0: SPI and I2C interfaces enabled; 1: I 2C mode disabled)
	//	b8 -> SIM -> SPI serial interface mode selection. Default value: 0 0: 4-wire interface; 1: 3-wire interface

	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	int Status = def->write(LIS2DS12_REG_CTRL_2, &par->byte, 1);

	if (Status == 0)
		return SUCCESS;
	else
		return ERR;
}
int SetCTRL3(CTRL_3* par, LIS2DS12* def)
{


	//	b1, b2 -> SELF-TEST MODE
	//	b3 -> TAPX -> Tap recognition on X direction enable. (0: disabled; 1: enabled)
	//	b4 -> TAPY -> Tap recognition on Y direction enable. (0: disabled; 1: enabled)
	//	b5 -> TAPZ -> Tap recognition on Z direction enable. (0: disabled; 1: enabled)
	//	b6 -> LIR -> Latched Interrupt (0: disabled; 1: enabled)
	//	b7 -> H_LACTIVE -> Interrupt active high, low. (0: active high; 1: active low)
	//	b8 -> PP_OD -> Push-pull/open-drain selection on interrupt pad. (0: push-pull; 1: open-drain)


	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &par->byte, 1);
}

int SetCTRL4(CTRL_4* par, LIS2DS12* def)
{
	//	b1 -> INT1_MASTER_DRDY -> Manage the Master DRDY signal on INT1
	//	b2 -> INT1_S_TAP -> Single-tap recognition is routed on INT1
	//	b3 -> INT1_WU -> Wakeup recognition is routed on INT1
	//	b4 -> INT1_FF -> Free-fall recognition is routed on INT1
	//	b5 -> INT1_TAP -> Double-tap recognition is routed on INT1
	//	b6 -> INT1_6D -> 6D recognition is routed on INT1
	//	b7 -> INT1_FTH -> FIFO threshold interrupt is routed on INT1
	//	b8 -> INT1_DRDY -> Data-Ready is routed on INT1

	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &par->byte, 1);
}

int SetCTRL5(CTRL_5* par, LIS2DS12* def)
{
	//	b1 -> DRDY_PULSED -> Data-ready interrupt mode selection: latched mode / pulsed mode. (0: disabled; 1: enabled)
	//	b2 -> INT2_BOOT -> Boot state routed on INT2 pad. Default value: 0 (0: disabled; 1: enabled)
	//	b3 -> INT2_ON_INT1 -> All signals routed on INT2 are also routed on INT1. Default value: 0 (0: disabled; 1: enabled)
	//	b4 -> INT2_TILT -> Tilt event is routed on INT2 pad. Default value: 0 (0: disabled; 1: enabled)
	//	b5 -> INT2_SIG_MOT -> Significant motion detection is routed on INT2 pad. Default value: 0 (0: disabled; 1: enabled)
	//	b6 -> INT2_STEP_DET -> Step detection is routed on INT2 pad. Default value: 0 (0: disabled; 1: enabled)
	//	b7 -> INT2_FTH -> FIFO threshold interrupt is routed on INT2 pad. Default value: 0 (0: disabled; 1: enabled)
	//	b8 -> INT2_DRDY -> Data-Ready is routed on INT2 pad. Default value: 0 (0: disabled; 1: enabled)

	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &par->byte, 1);
}

int SetFIFO_CTRL(FIFO_CTRL* par, LIS2DS12* def)
{

	/// FIFOS MODES
	//  b1 b2 b3
	//  BYPASS MODE          - > FIFO turned offOFF
	//  FIFO MODE		     - > Stops_collecting data when FIFO is fullStops collecting data when FIFO is full.
	//  CONTINUOUS TO FIFO   - > STREAM MODE until trigger is deasserted then FIFO modeContinuous-to-FIFO: Stream mode until trigger is deasserted, then FIFO mode
	//  BYPASS TO CONTINUOUS - > Bypass mode until trigger is deasserted, then FIFO modeBypass-to-Continuous: Bypass mode until trigger is deasserted, then FIFO mode
	//  CONTINIOUS_MODE		 - >  Data If the FIFO is full, the new sample over writes the older sampleContinuous mode: data If the FIFO is full, the new sample over- writes the older sample.
	//	b4 -> INT2_STEP_COUNT_OV		 - > Step counter overflow interrupt enable on INT2
	//	b5 -> MODULE_TO_FIFO -> When set to '1'-logic, module routine result is send to FIFO instead of X,Y,Z acceleration data
	//	b6 -> This bit must be set to '0' for correct device operation.
	//	b7 -> This bit must be set to '0' for correct device operation.
	//	b8 -> IF_CS_PU_DIS -> When '1'-logic disconnects pull-up in if_cs pad. Default: 0

	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FIFO_CTRL, &par->byte, 1);
}

int GetTemp(LIS2DS12* def)
{
	if (!def->read)
		return ERR;
	for (int i = 0; i < 10000; i++);
	uint8_t a;
	def->read(LIS2DS12_REG_OUT_TEMP, &a, 1);

	if (a == 0xFE)
		return 23;
	if (a == 0xFF)
		return 24;
	else
		return a + 25;
}
int SetODR(ODR_Hz ODR, ODR_Hz_MODE mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.mode = mode;
	ctrl.bits.ODR = ODR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

}


int SetFS(FS fs, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.fs = fs;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);
}

int SetHF_ODR(bool HF_ODR, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.HF_ODR = HF_ODR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);
}

int SetBDU(bool BDU, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.BDU = BDU;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);
}

int BOOTRESET(LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.BOOT_RESET = 1;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int SOFT_RESET(LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.SOFT_RESET = 1;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int UPGRATE_PEDOMETR_SETTINGS(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.b3 = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int FUNC_CFG_EN(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.FUNC_CFG_EN = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}
int FDS_SLOPE(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.FDS_SLOPE = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int IF_ADD_INC(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.IF_ADD_INC = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int I2C_SWICH(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.I2C_SWICH = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int SIM(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.SIM = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int SELF_TEST_ENABLE(SELF_TEST_MODE mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.mode = mode;

	for(int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int TAP_X(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.TAPX = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int TAP_Y(bool ENABLE_DISABLE, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.TAPY = ENABLE_DISABLE;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int TAP_Z(bool ENABLE_DISABLE, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.TAPZ = ENABLE_DISABLE;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIR(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.LIR = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int H_LACTIVE(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.H_LACTIVE = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int PP_OD(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.PP_OD = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int INT1_MASTER_DRDY(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_MASTER_DRDY = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}

int INT1_S_TAP(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_S_TAP = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int INT1_WU(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_WU = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int INT1_FF(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_FF = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int INT1_TAP(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_TAP = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int INT1_6D(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_6D = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int INT1_FTH(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_FTH = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int INT1_DRDY(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_DRDY = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}


int DRDY_PULSED(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.DRDY_PULSED = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_BOOT(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_BOOT = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_ON_INT1(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_ON_INT1 = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_TILT(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_TILT = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_SIG_MOT(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_SIG_MOT = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_STEP_DET(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_STEP_DET = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_FTH(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_FTH = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int INT2_DRDY(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_DRDY = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}



int SETFIFO_MODE(FIFO_MODE* mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.mode = *mode;


	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}

int INT2_STEP_COUNT_OV(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.INT2_STEP_COUNT_OV = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}
int MODULE_TO_FIFO(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.MODULE_TO_FIFO = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}
int IF_CS_PU_DIS(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.IF_CS_PU_DIS = mode;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}

int Get_Status(LIS2DS12* def, STATUS* ret)
{


	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);


	return def->read(LIS2DS12_REG_STATUS, &ret->byte, 1);


}

uint16_t OUT_X(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	for (int i = 0; i < 1500; i++);

	uint8_t buf[2];

	def->read(LIS2DS12_REG_OUT_X_L, buf, 2);

	return (((uint16_t)(buf[1]) << 8) | (uint16_t)(buf[0])) >> 2;

}
uint16_t OUT_Y(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	for (int i = 0; i < 1500; i++);

	uint8_t buf[2];

	def->read(LIS2DS12_REG_OUT_Y_L, buf, 2);

	return (((uint16_t)(buf[1]) << 8) | (uint16_t)(buf[0])) >> 2;
}
uint16_t OUT_Z(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	for (int i = 0; i < 1500; i++);

	uint8_t buf[2];

	def->read(LIS2DS12_REG_OUT_Z_L, buf, 2);

	return (((uint16_t)(buf[1]) << 8) | (uint16_t)(buf[0])) >> 2;
}

int SET_FIFO_THS(FIFO_THS* par, LIS2DS12* def)
{
	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FIFO_THS, &par->byte, 1);
}

int GET_FIFO_THS(LIS2DS12* def, FIFO_THS* ret)
{

	if (!def->read)
		return ERR;



	for (int i = 0; i < 10000; i++);

	return def->read(LIS2DS12_REG_FIFO_THS, &ret->byte, 1);


}

int GET_FIFO_SRC(LIS2DS12* def, FIFO_SRC* ret)
{


	if (!def->read)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->read(LIS2DS12_REG_FIFO_SRC, &ret->byte, 1);


}

int GET_FIFO_SAMPLES(LIS2DS12* def, uint8_t* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_FIFO_SAMPLES, ret, 1);
}

int SET_TAP_6D_THS(LIS2DS12* def, TAP_6D_THS* par)
{

	if (!def->write)
		return ERR;
	for (int i = 0; i < 10000; i++);
	return def->write(LIS2DS12_REG_TAP_6D_THS, &par->byte, 1);
}
int GET_INT_DUR(LIS2DS12* def, INT_DUR* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_INT_DUR, &ret->byte, 1);
}
int SET_INT_DUR(LIS2DS12* def, INT_DUR* par)
{
	if (!def->write)
		return ERR;
	for (int i = 0; i < 10000; i++);
	return def->write(LIS2DS12_REG_INT_DUR, &par->byte, 1);
}

int GET_WAKE_UP_THS(LIS2DS12* def, WAKE_UP_THS* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_WAKE_UP_THS, &ret->byte, 1);
}
int SET_WAKE_UP_THS(LIS2DS12* def, WAKE_UP_THS* par)
{
	if (!def->write)
		return ERR;
	for (int i = 0; i < 10000; i++);
	return def->write(LIS2DS12_REG_WAKE_UP_THS, &par->byte, 1);
}

int GET_WAKE_UP_DUR (LIS2DS12* def, WAKE_UP_DUR* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_WAKE_UP_DUR, &ret->byte, 1);
}
int SET_WAKE_UP_DUR (LIS2DS12* def, WAKE_UP_DUR* par)
{
	if (!def->write)
		return ERR;
	for (int i = 0; i < 10000; i++);
	return def->write(LIS2DS12_REG_WAKE_UP_DUR, &par->byte, 1);
}

int GET_FREE_FALL(LIS2DS12* def, FREE_FALL* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_FREE_FALL, &ret->byte, 1);
}
int SET_FREE_FALL(LIS2DS12* def, FREE_FALL* par)
{
	if (!def->write)
		return ERR;
	for (int i = 0; i < 10000; i++);
	return def->write(LIS2DS12_REG_FREE_FALL, &par->byte, 1);
}

int GET_STATUS_DUP(LIS2DS12* def, STATUS_DUP* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_STATUS_DUP, &ret->byte, 1);
}

int GET_WAKE_UP_SRC(LIS2DS12* def, WAKE_UP_SRC* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_WAKE_UP_SRC, &ret->byte, 1);
}

int GET_TAP_SRC(LIS2DS12* def, TAP_SRC* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_TAP_SRC, &ret->byte, 1);
}

int GET_6D_SRC(LIS2DS12* def, _6D_SRC* ret)
{
	if (!def->read)
			return ERR;
	for (int i = 0; i < 10000; i++);
	return def->read(LIS2DS12_REG_6D_SRC, &ret->byte, 1);
}

int GET_STEP_COUNTER_MINTHS(LIS2DS12* def, STEP_COUNTER_MINTHS* ret)
{
	if (!def->read)
			return ERR;

	for (int i = 0; i < 10000; i++);

	return def->read(LIS2DS12_REG_STEP_COUNTER_MINTHS, &ret->byte, 1);
}
int SET_STEP_COUNTER_MINTHS(LIS2DS12* def, STEP_COUNTER_MINTHS* par)
{
	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_STEP_COUNTER_MINTHS, &par->byte, 1);
}

int GET_STEP_COUNTER(LIS2DS12* def, uint16_t* ret)
{
	if (!def->read)
			return ERR;

	for (int i = 0; i < 10000; i++);
	uint8_t a,b;
	int status = def->read(LIS2DS12_REG_STEP_COUNTER_L, &a, 1);
	if (status != 0)
		return ERR;
	for (int i = 0; i < 10000; i++);
	status = def->read(LIS2DS12_REG_STEP_COUNTER_L, &b, 1);
	return status;
	a = (((uint16_t)b << 8) | (uint16_t)a);
}

////////

int GET_FUNC_CK_GATE (LIS2DS12* def, uint8_t* ret)
{
	if (!def->read)
			return ERR;

	for (int i = 0; i < 10000; i++);

	return def->read(LIS2DS12_REG_FUNC_CK_GATE, ret, 1);
}

int GET_FUNC_SRC (LIS2DS12* def, FUNC_SRC* ret)
{
	if (!def->read)
			return ERR;

	for (int i = 0; i < 10000; i++);

	return def->read(LIS2DS12_REG_FUNC_SRC, &ret->byte, 1);
}

int GET_FUNC_CTRL(LIS2DS12* def, FUNC_CTRL* ret)
{
	if (!def->read)
			return ERR;

	for (int i = 0; i < 10000; i++);

	return def->read(LIS2DS12_REG_FUNC_CTRL, &ret->byte, 1);
}
int SET_FUNC_CTRL(LIS2DS12* def, FUNC_CTRL* par)
{
	if (!def->write)
		return ERR;

	for (int i = 0; i < 10000; i++);

	return def->write(LIS2DS12_REG_FUNC_CTRL, &par->byte, 1);
}
