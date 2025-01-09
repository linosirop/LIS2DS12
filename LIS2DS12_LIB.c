#include"LIS2DS12_LIB.h"



/***********************************************************************************
 * LIS2DS12_Check_WIA
 *
 * @brief -> This function reads the WIA (Who I Am) register
 * and compares it with the value that should always be there (constantly specified)
 *
 * @param -> def -> main structure with read/write functions
 **********************************************************************************/

int LIS2DS12_Check_WIA(LIS2DS12* def) // 1 -> good, 0 -> bad // WHO I'M AM
{
	if (!(def->read))
		return ERR;

	uint8_t raw;

	if (def->read)
		def->read(LIS2DS12_REG_WHO_AM_I, &raw, 1);

	if (raw == WHO_AM_I_NORM_VALUE)
		return SUCCESS;
	else
		return ERR;
}

/***********************************************************************************
 * LIS2DS12_SetCTRL1
 *
 * @brief -> This function allows you to configure CTRL1
 * using the structure passed to it
 *
 * @param -> def -> main structure with read/write functions
 * @param -> par -> The structure with which CTRL1 is configured
 **********************************************************************************/

int LIS2DS12_SetCTRL1(LIS2DS12_CTRL_1* par, LIS2DS12* def)
{

	if (!def->write)
		return ERR;

	int Status = def->write(LIS2DS12_REG_CTRL_1, &par->byte, 1);

	if (Status == 0)
		return SUCCESS;
	else
		return ERR;
}

/***********************************************************************************
 * LIS2DS12_SetCTRL2
 *
 * @brief -> This function allows you to configure CTRL2
 * using the structure passed to it
 *
 * @param -> def -> main structure with read/write functions
 * @param -> par -> The structure with which CTRL2 is configured
 **********************************************************************************/

int LIS2DS12_SetCTRL2(LIS2DS12_CTRL_2* par, LIS2DS12* def)
{


	if (!def->write)
		return ERR;

	int Status = def->write(LIS2DS12_REG_CTRL_2, &par->byte, 1);

	if (Status == 0)
		return SUCCESS;
	else
		return ERR;
}

/***********************************************************************************
 * LIS2DS12_SetCTRL3
 *
 * @brief -> This function allows you to configure CTRL3
 * using the structure passed to it
 *
 * @param -> def -> main structure with read/write functions
 * @param -> par -> The structure with which CTRL3 is configured
 **********************************************************************************/

int LIS2DS12_SetCTRL3(LIS2DS12_CTRL_3* par, LIS2DS12* def)
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

	return def->write(LIS2DS12_REG_CTRL_3, &par->byte, 1);
}

/***********************************************************************************
 * LIS2DS12_SetCTRL4
 *
 * @brief -> This function allows you to configure CTRL4
 * using the structure passed to it
 *
 * @param -> def -> main structure with read/write functions
 * @param -> par -> The structure with which CTRL4 is configured
 **********************************************************************************/

int LIS2DS12_SetCTRL4(LIS2DS12_CTRL_4* par, LIS2DS12* def)
{

	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_CTRL_4, &par->byte, 1);
}

/***********************************************************************************
 * LIS2DS12_SetCTRL5
 *
 * @brief -> This function allows you to configure CTRL5
 * using the structure passed to it
 *
 * @param -> def -> main structure with read/write functions
 * @param -> par -> The structure with which CTRL5 is configured
 **********************************************************************************/

int LIS2DS12_SetCTRL5(LIS2DS12_CTRL_5* par, LIS2DS12* def)
{

	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_CTRL_5, &par->byte, 1);
}

/***********************************************************************************
 * LIS2DS12_SetFIFO_CTRL
 *
 * @brief -> This function allows you to configure FIFO_CTRL
 * using the structure passed to it
 *
 * @param -> def -> main structure with read/write functions
 * @param -> par -> The structure with which FIFO_CTRL is configured
 **********************************************************************************/

int LIS2DS12_SetFIFO_CTRL(LIS2DS12_FIFO_CTRL* par, LIS2DS12* def)
{

	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_FIFO_CTRL, &par->byte, 1);
}

/***********************************************************************************
 * LIS2DS12_GetTemp
 *
 * @brief -> Using this function you can get the temperature
 *
 * @param -> def -> main structure with read/write functions
 *
 **********************************************************************************/

int LIS2DS12_GetTemp(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	uint8_t temp;
	def->read(LIS2DS12_REG_OUT_TEMP, &temp, 1);

	if (temp == 0xFE)
		return 23;
	if (temp == 0xFF)
		return 24;
	else
		return temp + 25;
}

/***********************************************************************************
 * LIS2DS12_SetODR
 *
 * @brief -> With this function you can change the ODR without changing the entire CTRL
 *
 * @param -> def -> main structure with read/write functions
 *
 * @param -> ODR -> The enum with which ODR is configured
 *
 * @param -> mode -> The enum with which ODR_MODE is configured
 **********************************************************************************/

int LIS2DS12_SetODR(LIS2DS12_ODR_Hz ODR, LIS2DS12_ODR_Hz_MODE mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.mode = mode;
	ctrl.bits.ODR = ODR;

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

}

/***********************************************************************************
 * LIS2DS12_SetFS
 *
 * @brief -> With this function you can change the FS without changing the entire CTRL
 *
 * @param -> def -> main structure with read/write functions
 *
 * @param -> fs -> The enum with which FS is configured
 *
 **********************************************************************************/

int LIS2DS12_SetFS(LIS2DS12_FS fs, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.fs = fs;

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);
}

/***********************************************************************************
 * LIS2DS12_SetHF_ODR
 *
 * @brief -> With this function you can change the HF_ODR without changing the entire CTRL
 *
 * @param -> def -> main structure with read/write functions
 *
 * @param -> HF_ODR -> Boolean parameter that allows/disables HF_ODR
 *
 **********************************************************************************/

int LIS2DS12_SetHF_ODR(bool HF_ODR, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.HF_ODR = HF_ODR;

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);
}

/***********************************************************************************
 * LIS2DS12_SetBDU
 *
 * @brief -> This function enables/disables BDU
 *
 * @param -> def -> main structure with read/write functions
 *
 * @param -> HF_ODR -> Boolean parameter that allows/disables BDU
 *
 **********************************************************************************/

int LIS2DS12_SetBDU(bool BDU, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_1 ctrl;
	def->read(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);

	ctrl.bits.BDU = BDU;

	return def->write(LIS2DS12_REG_CTRL_1, &ctrl.byte, 1);
}

/***********************************************************************************
 * LIS2DS12_BOOTRESET
 *
 * @brief -> This function resets all registers
 *
 * @param -> def -> main structure with read/write functions
 *
 **********************************************************************************/

int LIS2DS12_BOOTRESET(LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.BOOT_RESET = 1;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

/***********************************************************************************
 * LIS2DS12_SOFTRESET
 *
 * @brief -> This function resets all registers
 *
 * @param -> def -> main structure with read/write functions
 *
 **********************************************************************************/

int LIS2DS12_SOFT_RESET(LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.SOFT_RESET = 1;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

/***********************************************************************************
 * LIS2DS12_UPGRATE_PEDOMETR_SETTINGS
 *
 * @brief -> This function enables/disables UPGRATE_PEDOMETR_SETTINGS
 *
 * @param -> def -> main structure with read/write functions
 *
 * @param -> mode -> (if 1 = enable) (if 0 = disable)
 *
 **********************************************************************************/

int LIS2DS12_UPGRATE_PEDOMETR_SETTINGS(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.UPGRATE_PEDOMETR_SETTINGS = mode;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int LIS2DS12_FUNC_CFG_EN(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.FUNC_CFG_EN = mode;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}
int LIS2DS12_FDS_SLOPE(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.FDS_SLOPE = mode;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int LIS2DS12_IF_ADD_INC(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.IF_ADD_INC = mode;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int LIS2DS12_I2C_SWICH(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.I2C_SWICH = mode;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int LIS2DS12_SIM(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_2 ctrl;
	def->read(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);

	ctrl.bits.SIM = mode;

	return def->write(LIS2DS12_REG_CTRL_2, &ctrl.byte, 1);
}

int LIS2DS12_SELF_TEST_ENABLE(LIS2DS12_SELF_TEST_MODE mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.mode = mode;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_TAP_X(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.TAPX = mode;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_TAP_Y(bool ENABLE_DISABLE, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.TAPY = ENABLE_DISABLE;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_TAP_Z(bool ENABLE_DISABLE, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.TAPZ = ENABLE_DISABLE;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_LIR(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.LIR = mode;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_H_LACTIVE(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.H_LACTIVE = mode;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_PP_OD(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_3 ctrl;
	def->read(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);

	ctrl.bits.PP_OD = mode;

	return def->write(LIS2DS12_REG_CTRL_3, &ctrl.byte, 1);
}

int LIS2DS12_INT1_MASTER_DRDY(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_MASTER_DRDY = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}

int LIS2DS12_INT1_S_TAP(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_S_TAP = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int LIS2DS12_INT1_WU(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_WU = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int LIS2DS12_INT1_FF(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_FF = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int LIS2DS12_INT1_TAP(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_TAP = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int LIS2DS12_INT1_6D(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_6D = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int LIS2DS12_INT1_FTH(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_FTH = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}
int LIS2DS12_INT1_DRDY(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_4 ctrl;
	def->read(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);

	ctrl.bits.INT1_DRDY = mode;

	return def->write(LIS2DS12_REG_CTRL_4, &ctrl.byte, 1);
}


int LIS2DS12_DRDY_PULSED(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.DRDY_PULSED = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_BOOT(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_BOOT = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_ON_INT1(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_ON_INT1 = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_TILT(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_TILT = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_SIG_MOT(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_SIG_MOT = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_STEP_DET(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_STEP_DET = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_FTH(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_FTH = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}
int LIS2DS12_INT2_DRDY(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_CTRL_5 ctrl;
	def->read(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);

	ctrl.bits.INT2_DRDY = mode;

	return def->write(LIS2DS12_REG_CTRL_5, &ctrl.byte, 1);
}



int LIS2DS12_SETFIFO_MODE(LIS2DS12_FIFO_MODE* mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.mode = *mode;

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}

int LIS2DS12_INT2_STEP_COUNT_OV(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.INT2_STEP_COUNT_OV = mode;

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}
int LIS2DS12_MODULE_TO_FIFO(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.MODULE_TO_FIFO = mode;

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}
int LIS2DS12_IF_CS_PU_DIS(bool mode, LIS2DS12* def)
{
	if (!def->write)
		return ERR;
	if (!def->read)
		return ERR;

	LIS2DS12_FIFO_CTRL ctrl;
	def->read(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);

	ctrl.bits.IF_CS_PU_DIS = mode;

	return def->write(LIS2DS12_REG_FIFO_CTRL, &ctrl.byte, 1);
}

int LIS2DS12_Get_Status(LIS2DS12* def, LIS2DS12_STATUS* ret)
{


	if (!def->read)
		return ERR;

	return def->read(LIS2DS12_REG_STATUS, &ret->byte, 1);
}

uint16_t LIS2DS12_OUT_X(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	uint8_t buf[2];

	def->read(LIS2DS12_REG_OUT_X_L, buf, 2);

	return (((uint16_t)(buf[1]) << 8) | (uint16_t)(buf[0])) >> 2;

}


uint16_t LIS2DS12_OUT_Y(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	uint8_t buf[2];

	def->read(LIS2DS12_REG_OUT_Y_L, buf, 2);

	return (((uint16_t)(buf[1]) << 8) | (uint16_t)(buf[0])) >> 2;
}
uint16_t LIS2DS12_OUT_Z(LIS2DS12* def)
{
	if (!def->read)
		return ERR;

	uint8_t buf[2];

	def->read(LIS2DS12_REG_OUT_Z_L, buf, 2);

	return (((uint16_t)(buf[1]) << 8) | (uint16_t)(buf[0])) >> 2;
}

int LIS2DS12_SET_FIFO_THS(LIS2DS12_FIFO_THS* par, LIS2DS12* def)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_FIFO_THS, &par->byte, 1);
}

int LIS2DS12_GET_FIFO_THS(LIS2DS12* def, LIS2DS12_FIFO_THS* ret)
{

	if (!def->read)
		return ERR;

	return def->read(LIS2DS12_REG_FIFO_THS, &ret->byte, 1);
}

int LIS2DS12_GET_FIFO_SRC(LIS2DS12* def, LIS2DS12_FIFO_SRC* ret)
{

	if (!def->read)
		return ERR;

	return def->read(LIS2DS12_REG_FIFO_SRC, &ret->byte, 1);
}

int LIS2DS12_GET_FIFO_SAMPLES(LIS2DS12* def, uint8_t* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_FIFO_SAMPLES, ret, 1);
}

int LIS2DS12_SET_TAP_6D_THS(LIS2DS12* def, LIS2DS12_TAP_6D_THS* par)
{

	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_TAP_6D_THS, &par->byte, 1);
}
int LIS2DS12_GET_INT_DUR(LIS2DS12* def, LIS2DS12_INT_DUR* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_INT_DUR, &ret->byte, 1);
}
int LIS2DS12_SET_INT_DUR(LIS2DS12* def, LIS2DS12_INT_DUR* par)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_INT_DUR, &par->byte, 1);
}

int LIS2DS12_GET_WAKE_UP_THS(LIS2DS12* def, LIS2DS12_WAKE_UP_THS* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_WAKE_UP_THS, &ret->byte, 1);
}
int LIS2DS12_SET_WAKE_UP_THS(LIS2DS12* def, LIS2DS12_WAKE_UP_THS* par)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_WAKE_UP_THS, &par->byte, 1);
}

int LIS2DS12_GET_WAKE_UP_DUR (LIS2DS12* def, LIS2DS12_WAKE_UP_DUR* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_WAKE_UP_DUR, &ret->byte, 1);
}
int LIS2DS12_SET_WAKE_UP_DUR (LIS2DS12* def, LIS2DS12_WAKE_UP_DUR* par)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_WAKE_UP_DUR, &par->byte, 1);
}

int LIS2DS12_GET_FREE_FALL(LIS2DS12* def, LIS2DS12_FREE_FALL* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_FREE_FALL, &ret->byte, 1);
}
int LIS2DS12_SET_FREE_FALL(LIS2DS12* def, LIS2DS12_FREE_FALL* par)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_FREE_FALL, &par->byte, 1);
}

int LIS2DS12_GET_STATUS_DUP(LIS2DS12* def, LIS2DS12_STATUS_DUP* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_STATUS_DUP, &ret->byte, 1);
}

int LIS2DS12_GET_WAKE_UP_SRC(LIS2DS12* def, LIS2DS12_WAKE_UP_SRC* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_WAKE_UP_SRC, &ret->byte, 1);
}

int LIS2DS12_GET_TAP_SRC(LIS2DS12* def, LIS2DS12_TAP_SRC* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_TAP_SRC, &ret->byte, 1);
}

int LIS2DS12_GET_6D_SRC(LIS2DS12* def, LIS2DS12_6D_SRC* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_6D_SRC, &ret->byte, 1);
}

int LIS2DS12_GET_STEP_COUNTER_MINTHS(LIS2DS12* def, LIS2DS12_STEP_COUNTER_MINTHS* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_STEP_COUNTER_MINTHS, &ret->byte, 1);
}
int LIS2DS12_SET_STEP_COUNTER_MINTHS(LIS2DS12* def, LIS2DS12_STEP_COUNTER_MINTHS* par)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_STEP_COUNTER_MINTHS, &par->byte, 1);
}

int LIS2DS12_GET_STEP_COUNTER(LIS2DS12* def, uint16_t* ret)
{
	if (!def->read)
			return ERR;

	uint8_t l_byte,h_byte;
	int status = def->read(LIS2DS12_REG_STEP_COUNTER_L, &l_byte, 1);
	if (status != 0)
		return ERR;

	status = def->read(LIS2DS12_REG_STEP_COUNTER_L, &h_byte, 1);
	return status;

	*ret = (((uint16_t)h_byte << 8) | (uint16_t)l_byte);
}


int LIS2DS12_GET_FUNC_CK_GATE (LIS2DS12* def, uint8_t* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_FUNC_CK_GATE, ret, 1);
}

int LIS2DS12_GET_FUNC_SRC (LIS2DS12* def, LIS2DS12_FUNC_SRC* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_FUNC_SRC, &ret->byte, 1);
}

int LIS2DS12_GET_FUNC_CTRL(LIS2DS12* def, LIS2DS12_FUNC_CTRL* ret)
{
	if (!def->read)
			return ERR;

	return def->read(LIS2DS12_REG_FUNC_CTRL, &ret->byte, 1);
}
int LIS2DS12_SET_FUNC_CTRL(LIS2DS12* def, LIS2DS12_FUNC_CTRL* par)
{
	if (!def->write)
		return ERR;

	return def->write(LIS2DS12_REG_FUNC_CTRL, &par->byte, 1);
}
