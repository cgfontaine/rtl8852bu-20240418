/******************************************************************************
 *
 * Copyright(c) 2019 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#include "halrf_precomp.h"

#define OLD_BACKUP_RESTORE_ENABLE (0)

//#ifdef RF_8852A_SUPPORT
u8 iqk_kpath(struct rf_info *rf, enum phl_phy_idx phy_idx)
{
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;
	return iqk_ops->iqk_kpath(rf, phy_idx);
}

void iqk_restore(struct rf_info *rf, u8 path)
{
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;
	iqk_ops->iqk_restore(rf, path);
	return;
}

void iqk_backup_mac_reg(struct rf_info *rf, u32 *backup_mac_reg_val)
{
	struct rfk_iqk_info *iqk_info = rf->rfk_iqk_info;
	u32 i;
	for (i = 0; i < iqk_info->backup_mac_reg_num; i++) {
		if (i >= RF_BACKUP_MAC_REG_MAX_NUM) {
			RF_DBG(rf, DBG_RF_IQK,
			       "[IQK] %s backup size not enough\n", __func__);
			break;
		}
		*(backup_mac_reg_val + i) =
			halrf_rreg(rf, iqk_info->backup_mac_reg[i], MASKDWORD);
/*
		RF_DBG(rf, DBG_RF_IQK, "[IQK]backup mac reg :  %x, value =%x\n",
		       iqk_info->backup_mac_reg[i], *(backup_mac_reg_val + i));
*/
	}
}

void iqk_backup_bb_reg(struct rf_info *rf, u32 *backup_bb_reg_val)
{
	struct rfk_iqk_info *iqk_info = rf->rfk_iqk_info;
	u32 i;
	for (i = 0; i < iqk_info->backup_bb_reg_num; i++) {
		if (i >= RF_BACKUP_BB_REG_MAX_NUM) {
			RF_DBG(rf, DBG_RF_IQK,
			       "[IQK] %s backup size not enough\n", __func__);
			break;
		}
		*(backup_bb_reg_val + i) =
			halrf_rreg(rf, iqk_info->backup_bb_reg[i], MASKDWORD);
/*
		RF_DBG(rf, DBG_RF_IQK, "[IQK]backup bb reg : %x, value =%x\n",
		       iqk_info->backup_bb_reg[i], *(backup_bb_reg_val + i));
*/
	}
}

void iqk_backup_rf_reg(struct rf_info *rf, u32 *backup_rf_reg_val, u8 rf_path)
{
	struct rfk_iqk_info *iqk_info = rf->rfk_iqk_info;
	u32 i;
	for (i = 0; i < iqk_info->backup_rf_reg_num; i++) {
		if (i >= RF_BACKUP_RF_REG_MAX_NUM) {
			RF_DBG(rf, DBG_RF_IQK,
			       "[IQK] %s backup size not enough\n", __func__);
			break;
		}
		*(backup_rf_reg_val + i) = halrf_rrf(
			rf, rf_path, iqk_info->backup_rf_reg[i], MASKRF);
/*
		RF_DBG(rf, DBG_RF_IQK,
		       "[IQK]backup rf S%d reg : %x, value =%x\n", rf_path,
		       iqk_info->backup_rf_reg[i], *(backup_rf_reg_val + i));
*/
	}
}

void iqk_restore_mac_reg(struct rf_info *rf, u32 *backup_mac_reg_val)
{
	struct rfk_iqk_info *iqk_info = rf->rfk_iqk_info;
	u32 i;
	for (i = 0; i < iqk_info->backup_mac_reg_num; i++) {
		if (i >= RF_BACKUP_MAC_REG_MAX_NUM) {
			RF_DBG(rf, DBG_RF_IQK,
			       "[IQK] %s restore size not enough\n", __func__);
			break;
		}
		halrf_wreg(rf, iqk_info->backup_mac_reg[i], MASKDWORD,
			   *(backup_mac_reg_val + i));
/*
		RF_DBG(rf, DBG_RF_IQK,
		       "[IQK]restore mac reg :  %x, value =%x\n",
		       iqk_info->backup_mac_reg[i], *(backup_mac_reg_val + i));
*/
	}
}

void iqk_restore_bb_reg(struct rf_info *rf, u32 *backup_bb_reg_val)
{
	struct rfk_iqk_info *iqk_info = rf->rfk_iqk_info;
	u32 i;
	for (i = 0; i < iqk_info->backup_bb_reg_num; i++) {
		if (i >= RF_BACKUP_BB_REG_MAX_NUM) {
			RF_DBG(rf, DBG_RF_IQK,
			       "[IQK] %s restore size not enough\n", __func__);
			break;
		}
		halrf_wreg(rf, iqk_info->backup_bb_reg[i], MASKDWORD,
			   *(backup_bb_reg_val + i));
/*
		RF_DBG(rf, DBG_RF_IQK, "[IQK]restore bb reg : %x, value =%x\n",
		       iqk_info->backup_bb_reg[i], *(backup_bb_reg_val + i));
*/
	}
}

void iqk_restore_rf_reg(struct rf_info *rf, u32 *backup_rf_reg_val, u8 rf_path)
{
	struct rfk_iqk_info *iqk_info = rf->rfk_iqk_info;
	u32 i;
	for (i = 0; i < iqk_info->backup_rf_reg_num; i++) {
		if (i >= RF_BACKUP_RF_REG_MAX_NUM) {
			RF_DBG(rf, DBG_RF_IQK,
			       "[IQK] %s restore size not enough\n", __func__);
			break;
		}
		halrf_wrf(rf, rf_path, iqk_info->backup_rf_reg[i], MASKRF,
			  *(backup_rf_reg_val + i));
/*
		RF_DBG(rf, DBG_RF_IQK,
		       "[IQK]restore rf S%d reg: %x, value =%x\n", rf_path,
		       iqk_info->backup_rf_reg[i], *(backup_rf_reg_val + i));
*/
	}
}
void iqk_macbb_setting(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
#if 1
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===> %s\n", __func__);
	iqk_ops->iqk_macbb_setting(rf, phy_idx, path);

#else
	iqk_macbb_setting_8852a(rf, path, dbcc_en);
#endif
	return;
}

void iqk_preset(struct rf_info *rf, u8 path)
{
#if 1
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;

	iqk_ops->iqk_preset(rf, path);

#endif
	return;
}

void iqk_afebb_restore(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
#if 1
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;

	//RF_DBG(rf, DBG_RF_IQK, "[IQK]===> %s\n", __func__);
	iqk_ops->iqk_afebb_restore(rf, phy_idx, path);
#else

	iqk_afebb_restore_8852a(rf, path);
#endif
	return;
}

void iqk_get_ch_info(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
#if 1
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;

	iqk_ops->iqk_get_ch_info(rf, phy_idx, path);
#else

	iqk_get_ch_info_8852a(rf, phy_idx, path);
#endif
	return;
}

bool iqk_mcc_page_sel(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;

	return iqk_ops->iqk_mcc_page_sel(rf, phy_idx, path);;
}

void iqk_start_iqk(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
#if 1
	struct halrf_iqk_ops *iqk_ops = rf->rfk_iqk_info->rf_iqk_ops;

	iqk_ops->iqk_start_iqk(rf, phy_idx, path);
#else

	iqk_start_iqk_8852a(rf, phy_idx, path);
#endif
	return;
}

void halrf_iqk_init(struct rf_info *rf)
{
	
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
	case RF_RTL8852A:
		iqk_init_8852ab(rf);
	break;
#endif		
#ifdef RF_8852B_SUPPORT
	case RF_RTL8852B:
		iqk_init_8852b(rf);
	break;
#endif
#ifdef RF_8852BT_SUPPORT
	case RF_RTL8852BT:
		iqk_init_8852bt(rf);
	break;
#endif
#ifdef RF_8852BPT_SUPPORT
	case RF_RTL8852BPT:
		iqk_init_8852bpt(rf);
	break;
#endif
#ifdef RF_8852C_SUPPORT
	case RF_RTL8852C:
		iqk_init_8852c(rf);
	break;
#endif
#ifdef RF_8832BR_SUPPORT
	case RF_RTL8832BR:
		iqk_init_8832br(rf);
	break;
#endif
#ifdef RF_8192XB_SUPPORT
	case RF_RTL8192XB:
		iqk_init_8192xb(rf);
	break;
#endif
#ifdef RF_8852BP_SUPPORT
	case RF_RTL8852BP:
		iqk_init_8852bp(rf);
	break;
#endif

#ifdef RF_8730A_SUPPORT
	case RF_RTL8730A:
		iqk_init_8730a(rf);
	break;
#endif
#ifdef RF_8852D_SUPPORT
	case RF_RTL8852D:
		iqk_init_8852d(rf);
	break;
#endif
#ifdef RF_8832D_SUPPORT
	case RF_RTL8832D:
		iqk_init_8832d(rf);
	break;
#endif


		default:
		break;
	}
return;
}

void halrf_doiqk(struct rf_info *rf, bool force, enum phl_phy_idx phy_idx,
		 u8 path)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;

	u32 backup_mac_val[RF_BACKUP_MAC_REG_MAX_NUM] = {0x0};
	u32 backup_bb_val[RF_BACKUP_BB_REG_MAX_NUM] = {0x0};
	u32 backup_rf_val[RF_PATH_MAX_NUM][RF_BACKUP_RF_REG_MAX_NUM] = {{0x0}};
	u8 rf_path = 0x0;
	
#if 0	
	if(!force) {
		if (!phl_is_mp_mode(rf->phl_com)) {
			if(iqk_mcc_page_sel(rf, phy_idx, path)) {
				RF_DBG(rf, DBG_RF_IQK, "[IQK]==========IQK reload!!!!==========\n");
				return;
			}
		}
	}
#endif

	//halrf_btc_rfk_ntfy(rf, ((BIT(phy_idx) << 4) | RF_AB), RF_BTC_IQK, RFK_ONESHOT_START);
	//iqk_info->version = iqk_version;
	RF_DBG(rf, DBG_RF_IQK, "[IQK]==========IQK strat!!!!!==========\n");
	//RF_DBG(rf, DBG_RF_IQK, "[IQK]Test Ver 0x%x\n", iqk_info->version);
	iqk_get_ch_info(rf, phy_idx, path);
	iqk_backup_mac_reg(rf, &backup_mac_val[0]);
	iqk_backup_bb_reg(rf, &backup_bb_val[0]);
	iqk_backup_rf_reg(rf, &backup_rf_val[path][0], path);
	halrf_bb_ctrl_rx_cca(rf, false, phy_idx);
	iqk_macbb_setting(rf, phy_idx, path);
	iqk_preset(rf, path);
	iqk_start_iqk(rf, phy_idx, path);
	iqk_restore(rf, path);
	iqk_afebb_restore(rf, phy_idx, path);

	//halrf_write_fwofld_start(rf);		/*FW Offload Start*/

	iqk_restore_mac_reg(rf, &backup_mac_val[0]);
	iqk_restore_bb_reg(rf, &backup_bb_val[0]);
	halrf_bb_ctrl_rx_cca(rf, true, phy_idx);
	iqk_restore_rf_reg(rf, &backup_rf_val[path][0], path);

	//halrf_write_fwofld_end(rf);		/*FW Offload Start*/

	iqk_info->iqk_times++;
	//halrf_btc_rfk_ntfy(rf, ((BIT(phy_idx) << 4) | RF_AB), RF_BTC_IQK, RFK_ONESHOT_STOP);
	return;
}

void halrf_drv_iqk(struct rf_info *rf, enum phl_phy_idx phy_idx, bool force) {

	/*drv_iqk*/ 	
	RF_DBG(rf, DBG_RF_IQK, "[IQK]====  DRV IQK ==== \n");
	switch (iqk_kpath(rf, phy_idx)) {
	case RF_A:
		halrf_doiqk(rf, force, phy_idx, RF_PATH_A);
		break;
	case RF_B:
		halrf_doiqk(rf, force, phy_idx, RF_PATH_B);
		break;
	case RF_AB:
		halrf_doiqk(rf, force, phy_idx, RF_PATH_A);
		halrf_doiqk(rf, force, phy_idx, RF_PATH_B);
		break;
	default:
		break;
	}

}

bool halrf_check_fwiqk_done(struct rf_info *rf)
{

	bool isfail = false;

	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			isfail = halrf_check_fwiqk_done_8852ab(rf);
		break;
#endif

#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			isfail = halrf_check_fwiqk_done_8852b(rf);
		break;
#endif

#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			isfail = halrf_check_fwiqk_done_8852bt(rf);
		break;
#endif

#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			isfail = halrf_check_fwiqk_done_8852bpt(rf);
		break;
#endif

#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			isfail = halrf_check_fwiqk_done_8852c(rf);
		break;
#endif

		default:
		break;
		}
		return isfail;
}

void halrf_iqk_get_ch_info(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{

	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			iqk_get_ch_info_8852ab(rf, phy_idx, path); 
		break;
#endif

#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			iqk_get_ch_info_8852b(rf, phy_idx, path); 
		break;
#endif

#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			iqk_get_ch_info_8852bt(rf, phy_idx, path); 
		break;
#endif

#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			iqk_get_ch_info_8852bpt(rf, phy_idx, path); 
		break;
#endif

#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			iqk_get_ch_info_8852c(rf, phy_idx, path); 
		break;
#endif

		default:
		break;
	}
	return;
}

void halrf_iqk_set_info(struct rf_info *rf, enum phl_phy_idx phy_idx, u8 path)
{
	
		switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			iqk_set_info_8852ab(rf, phy_idx, path); 
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			iqk_set_info_8852b(rf, phy_idx, path); 
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			iqk_set_info_8852bt(rf, phy_idx, path); 
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			iqk_set_info_8852bpt(rf, phy_idx, path); 
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			iqk_set_info_8852c(rf, phy_idx, path); 
		break;
#endif

		default:
		break;
		}

			return;
}

u8 halrf_get_fw_iqk_times(struct rf_info *rf)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u8 times =0x0;	

	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			times = halrf_get_iqk_times_8852ab(rf); 
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			times = halrf_get_iqk_times_8852b(rf); 
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			times = halrf_get_iqk_times_8852bt(rf); 
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			times = halrf_get_iqk_times_8852bpt(rf); 
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			times = halrf_get_iqk_times_8852c(rf); 
		break;
#endif

		default:
		break;
	}
	return times ;
}


bool halrf_fw_iqk(struct rf_info *rf, enum phl_phy_idx phy_idx, bool force) {
	
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	u32 data_to_fw[2] = {0};
	u16 len = (u16) (sizeof(data_to_fw) / sizeof(u32))*4;
	bool isfail = true;

	RF_DBG(rf, DBG_RF_IQK, "[IQK]====  FW IQK START v3 ==== \n");
	data_to_fw[0] = (u32) phy_idx;
	data_to_fw[1] = (u32) rf->hal_com->dbcc_en;
#if 0
	halrf_btc_rfk_ntfy(rf, ((BIT(phy_idx) << 4) | RF_AB), RF_BTC_IQK, RFK_ONESHOT_START);		
#endif
	RF_DBG(rf, DBG_RF_IQK, "[IQK] phy_idx  = 0x%x\n", data_to_fw[0]);		
	RF_DBG(rf, DBG_RF_IQK, "[IQK] dbcc_en = 0x%x\n", data_to_fw[1]);
	halrf_iqk_get_ch_info(rf, phy_idx, RF_PATH_A);	
	halrf_iqk_get_ch_info(rf, phy_idx, RF_PATH_B);		
	halrf_fill_h2c_cmd(rf, len, FWCMD_H2C_IQK_OFFLOAD, 0xa, H2CB_TYPE_DATA, (u32 *) data_to_fw);
	halrf_check_fwiqk_done(rf);	
	iqk_info->iqk_times = halrf_get_fw_iqk_times(rf);
	halrf_iqk_set_info(rf, phy_idx, RF_PATH_A);	
	halrf_iqk_set_info(rf, phy_idx, RF_PATH_B);
#if 0
	halrf_btc_rfk_ntfy(rf, ((BIT(phy_idx) << 4) | RF_AB), RF_BTC_IQK, RFK_ONESHOT_STOP);
#endif	
	RF_DBG(rf, DBG_RF_IQK, "[IQK]====  FW IQK FINISH ==== \n");
	return isfail;
}


void halrf_iqk(struct rf_info *rf, enum phl_phy_idx phy_idx, bool force)
{
	struct halrf_iqk_info *iqk_info = &rf->iqk;
	bool isfail = true;
	struct rtw_hal_com_t *hal_i = rf->hal_com;

#if 0
	if ((rf->phl_com->id.id & 0x7)== 0x2)  //USB
		iqk_info->is_fw_iqk = true;
	else
		iqk_info->is_fw_iqk = false;
#endif

	if (iqk_info->is_fw_iqk) {
		isfail = halrf_fw_iqk(rf, phy_idx, force);
		if (isfail) {
			iqk_info->is_iqk_init = false;
			halrf_iqk_init(rf);
			isfail = halrf_fw_iqk(rf, phy_idx, force);
		}
	} else {
		halrf_write_fwofld_start(rf);	/*FW Offload Start*/
		halrf_drv_iqk(rf, phy_idx, force);
		halrf_write_fwofld_end(rf); 	/*FW Offload End*/
	}
	return;
}

////////////// debg command //////////////////////////

u32 halrf_get_iqk_ver(struct rf_info *rf)
{
	u32 tmp = 0x0;
	
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
	case RF_RTL8852A:
		tmp = halrf_get_iqk_ver_8852a();
	break;
#endif		
#ifdef RF_8852B_SUPPORT
	case RF_RTL8852B:
		tmp =halrf_get_iqk_ver_8852b();
	break;
#endif
#ifdef RF_8852BT_SUPPORT
	case RF_RTL8852BT:
		tmp =halrf_get_iqk_ver_8852bt();
	break;
#endif
#ifdef RF_8852BPT_SUPPORT
	case RF_RTL8852BPT:
		tmp =halrf_get_iqk_ver_8852bpt();
	break;
#endif
#ifdef RF_8852C_SUPPORT
	case RF_RTL8852C:
		tmp =halrf_get_iqk_ver_8852c();
	break;
#endif
#ifdef RF_8832BR_SUPPORT
	case RF_RTL8832BR:
		tmp =halrf_get_iqk_ver_8832br();
	break;
#endif
#ifdef RF_8192XB_SUPPORT
	case RF_RTL8192XB:
		tmp =halrf_get_iqk_ver_8192xb();
	break;
#endif
#ifdef RF_8852D_SUPPORT
	case RF_RTL8852D:
		tmp =halrf_get_iqk_ver_8852d();
	break;
#endif
#ifdef RF_8832D_SUPPORT
	case RF_RTL8832D:
		tmp =halrf_get_iqk_ver_8832d();
	break;
#endif

	default:
	break;
	}
	return tmp;

}
void halrf_iqk_toneleakage(void *rf_void, u8 path)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
		
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_toneleakage_8852ab(rf, path);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_toneleakage_8852b(rf, path);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_toneleakage_8852bt(rf, path);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_toneleakage_8852bpt(rf, path);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_toneleakage_8852c(rf, path);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_iqk_toneleakage_8832br(rf, path);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_iqk_toneleakage_8192xb(rf, path);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_toneleakage_8852d(rf, path);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_toneleakage_8832d(rf, path);
		break;
#endif
		default:
		break;
	}

	return;
}

void halrf_iqk_tx_bypass(void *rf_void, u8 path)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
	
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_tx_bypass_8852ab(rf, path);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_tx_bypass_8852b(rf, path);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_tx_bypass_8852bt(rf, path);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_tx_bypass_8852bpt(rf, path);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_tx_bypass_8852c(rf, path);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_iqk_tx_bypass_8832br(rf, path);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_iqk_tx_bypass_8192xb(rf, path);
		break;
#endif
#ifdef RF_8851B_SUPPORT
		case RF_RTL8851B:
			halrf_iqk_tx_bypass_8851b(rf, path);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_tx_bypass_8852d(rf, path);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_tx_bypass_8832d(rf, path);
		break;
#endif
		default:
		break;
	}

	return;
}

void halrf_iqk_rx_bypass(void *rf_void, u8 path)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
		
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_rx_bypass_8852ab(rf, path);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_rx_bypass_8852b(rf, path);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_rx_bypass_8852bt(rf, path);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_rx_bypass_8852bpt(rf, path);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_rx_bypass_8852c(rf, path);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_iqk_rx_bypass_8832br(rf, path);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_iqk_rx_bypass_8192xb(rf, path);
		break;
#endif
#ifdef RF_8851B_SUPPORT
		case RF_RTL8851B:
			halrf_iqk_rx_bypass_8851b(rf, path);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_rx_bypass_8852d(rf, path);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_rx_bypass_8832d(rf, path);
		break;
#endif
		default:
		break;
	}
	return;
}

void halrf_iqk_lok_bypass(void *rf_void, u8 path)
{
	struct rf_info *rf = (struct rf_info *)rf_void;

	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_lok_bypass_8852ab(rf, path);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_lok_bypass_8852b(rf, path);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_lok_bypass_8852bt(rf, path);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_lok_bypass_8852bpt(rf, path);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_lok_bypass_8852c(rf, path);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_iqk_lok_bypass_8832br(rf, path);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_iqk_lok_bypass_8192xb(rf, path);
		break;
#endif
#ifdef RF_8851B_SUPPORT
		case RF_RTL8851B:
			halrf_iqk_lok_bypass_8851b(rf, path);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_lok_bypass_8852d(rf, path);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_lok_bypass_8832d(rf, path);
		break;
#endif
		default:
		break;
	}
	return;
}

void halrf_nbiqk_enable(void *rf_void, bool iqk_nbiqk_en)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
				
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_nbiqk_enable_8852ab(rf, iqk_nbiqk_en);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_nbiqk_enable_8852b(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_nbiqk_enable_8852bt(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_nbiqk_enable_8852bpt(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_nbiqk_enable_8852c(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_nbiqk_enable_8832br(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_nbiqk_enable_8192xb(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8851B_SUPPORT
		case RF_RTL8851B:
			halrf_nbiqk_enable_8851b(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_nbiqk_enable_8852d(rf, iqk_nbiqk_en);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_nbiqk_enable_8832d(rf, iqk_nbiqk_en);
		break;
#endif

		default:
		break;
	}
	return;
}

void halrf_iqk_xym_enable(void *rf_void, bool iqk_xym_en)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
					
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_xym_enable_8852ab(rf, iqk_xym_en);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_xym_enable_8852b(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_xym_enable_8852bt(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_xym_enable_8852bpt(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_xym_enable_8852c(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_iqk_xym_enable_8832br(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_iqk_xym_enable_8192xb(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8851B_SUPPORT
		case RF_RTL8851B:
			halrf_iqk_xym_enable_8851b(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_xym_enable_8852d(rf, iqk_xym_en);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_xym_enable_8832d(rf, iqk_xym_en);
		break;
#endif

		default:
		break;
	}
	return;
}

void halrf_iqk_fft_enable(void *rf_void, bool iqk_fft_en)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
						
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_fft_enable_8852ab(rf, iqk_fft_en);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_fft_enable_8852b(rf, iqk_fft_en);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_fft_enable_8852bt(rf, iqk_fft_en);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_fft_enable_8852bpt(rf, iqk_fft_en);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_fft_enable_8852c(rf, iqk_fft_en);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_fft_enable_8852d(rf, iqk_fft_en);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_fft_enable_8832d(rf, iqk_fft_en);
		break;
#endif
		default:
		break;
	}
	return;
}

void halrf_iqk_cfir_enable(void *rf_void, bool iqk_cfir_en)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
							
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
	case RF_RTL8852A:
		halrf_iqk_cfir_enable_8852ab(rf, iqk_cfir_en);
	break;
#endif		
#ifdef RF_8852B_SUPPORT
	case RF_RTL8852B:
		halrf_iqk_cfir_enable_8852b(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8852BT_SUPPORT
	case RF_RTL8852BT:
		halrf_iqk_cfir_enable_8852bt(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8852BPT_SUPPORT
	case RF_RTL8852BPT:
		halrf_iqk_cfir_enable_8852bpt(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8852C_SUPPORT
	case RF_RTL8852C:
		halrf_iqk_cfir_enable_8852c(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8832BR_SUPPORT
	case RF_RTL8832BR:
		halrf_iqk_cfir_enable_8832br(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8192XB_SUPPORT
	case RF_RTL8192XB:
		halrf_iqk_cfir_enable_8192xb(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8852D_SUPPORT
	case RF_RTL8852D:
		halrf_iqk_cfir_enable_8852d(rf, iqk_cfir_en);
	break;
#endif
#ifdef RF_8832D_SUPPORT
	case RF_RTL8832D:
		halrf_iqk_cfir_enable_8832d(rf, iqk_cfir_en);
	break;
#endif
	default:
	break;
	}
	return;
}

void halrf_iqk_sram_enable(void *rf_void, bool iqk_sram_en)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
								
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_sram_enable_8852ab(rf, iqk_sram_en);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_sram_enable_8852b(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_sram_enable_8852bt(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_sram_enable_8852bpt(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_sram_enable_8852c(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			halrf_iqk_sram_enable_8832br(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			halrf_iqk_sram_enable_8192xb(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8851B_SUPPORT
		case RF_RTL8851B:
			halrf_iqk_sram_enable_8851b(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_sram_enable_8852d(rf, iqk_sram_en);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_sram_enable_8832d(rf, iqk_sram_en);
		break;
#endif

		default:
		break;
	}
	return;
}

void halrf_iqk_reload(void *rf_void, u8 path)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
									
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
		halrf_iqk_reload_8852ab(rf, path);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_reload_8852b(rf, path);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_reload_8852bt(rf, path);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_reload_8852bpt(rf, path);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_reload_8852c(rf, path);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_reload_8852d(rf, path);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_reload_8832d(rf, path);
		break;
#endif
		default:
		break;
	}
	return;
}

void halrf_iqk_dbcc(void *rf_void, u8 path)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
										
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			halrf_iqk_dbcc_8852ab(rf, path);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			halrf_iqk_dbcc_8852b(rf, path);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			halrf_iqk_dbcc_8852bt(rf, path);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			halrf_iqk_dbcc_8852bpt(rf, path);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			halrf_iqk_dbcc_8852c(rf, path);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_iqk_dbcc_8852d(rf, path);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_iqk_dbcc_8832d(rf, path);
		break;
#endif
		default:
		break;
	}
	return;
}

u8 halrf_iqk_get_mcc_ch0(void *rf_void)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
	u8 tmp = 0x0;

	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			 tmp = halrf_iqk_get_mcc_ch0_8852ab(rf);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
		 	tmp = halrf_iqk_get_mcc_ch0_8852b(rf);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
		 	tmp = halrf_iqk_get_mcc_ch0_8852bt(rf);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
		 	tmp = halrf_iqk_get_mcc_ch0_8852bpt(rf);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			tmp = halrf_iqk_get_mcc_ch0_8852c(rf);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			tmp = halrf_iqk_get_mcc_ch0_8852d(rf);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			tmp = halrf_iqk_get_mcc_ch0_8832d(rf);
		break;
#endif

		default:
		break;
	}
	return tmp;

}

u8 halrf_iqk_get_mcc_ch1(void *rf_void)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
	u8 tmp = 0x0;
	
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			tmp=  halrf_iqk_get_mcc_ch0_8852ab(rf);
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			tmp =  halrf_iqk_get_mcc_ch0_8852b(rf);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			tmp =  halrf_iqk_get_mcc_ch0_8852bt(rf);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			tmp =  halrf_iqk_get_mcc_ch0_8852bpt(rf);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			tmp =  halrf_iqk_get_mcc_ch0_8852c(rf);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			tmp =  halrf_iqk_get_mcc_ch0_8852d(rf);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			tmp =  halrf_iqk_get_mcc_ch0_8832d(rf);
		break;
#endif

		default:
		break;
	}
	return tmp;

}
void halrf_enable_fw_iqk(void *rf_void, bool is_fw_iqk)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
		
	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
	case RF_RTL8852A:
		halrf_enable_fw_iqk_8852ab(rf, is_fw_iqk);
	break;
#endif		
#ifdef RF_8852B_SUPPORT
	case RF_RTL8852B:
		halrf_enable_fw_iqk_8852b(rf, is_fw_iqk);
	break;
#endif
#ifdef RF_8852BT_SUPPORT
	case RF_RTL8852BT:
		halrf_enable_fw_iqk_8852bt(rf, is_fw_iqk);
	break;
#endif
#ifdef RF_8852BPT_SUPPORT
	case RF_RTL8852BPT:
		halrf_enable_fw_iqk_8852bpt(rf, is_fw_iqk);
	break;
#endif
#ifdef RF_8852C_SUPPORT
	case RF_RTL8852C:
		halrf_enable_fw_iqk_8852c(rf, is_fw_iqk);
	break;
#endif
#ifdef RF_8730A_SUPPORT
	case RF_RTL8730A:
		halrf_enable_fw_iqk_8730a(rf, is_fw_iqk);
	break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			halrf_enable_fw_iqk_8852d(rf, is_fw_iqk);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			halrf_enable_fw_iqk_8832d(rf, is_fw_iqk);
		break;
#endif
	default:
	break;
	}

	return;
}

u8 halrf_iqk_get_rxevm(void *rf_void)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
	u8 rxevm =0x0;

	switch (rf->ic_type) {
#ifdef RF_8852A_SUPPORT
	case RF_RTL8852A:
		rxevm = 0x0;
	break;
#endif		
#ifdef RF_8852B_SUPPORT
	case RF_RTL8852B:
		rxevm = halrf_iqk_get_rxevm_8852b(rf);
	break;
#endif
#ifdef RF_8852BT_SUPPORT
	case RF_RTL8852BT:
		rxevm = halrf_iqk_get_rxevm_8852bt(rf);
	break;
#endif
#ifdef RF_8852BPT_SUPPORT
	case RF_RTL8852BPT:
		rxevm = halrf_iqk_get_rxevm_8852bpt(rf);
	break;
#endif
#ifdef RF_8852C_SUPPORT
	case RF_RTL8852C:
		rxevm = halrf_iqk_get_rxevm_8852c(rf);
	break;
#endif
#ifdef RF_8832BR_SUPPORT
	case RF_RTL8832BR:
		rxevm = halrf_iqk_get_rxevm_8832br(rf);
	break;
#endif
#ifdef RF_8192XB_SUPPORT
	case RF_RTL8192XB:
		rxevm = halrf_iqk_get_rxevm_8192xb(rf);
	break;
#endif
#ifdef RF_8852D_SUPPORT
	case RF_RTL8852D:
		rxevm = halrf_iqk_get_rxevm_8852d(rf);
	break;
#endif
#ifdef RF_8832D_SUPPORT
	case RF_RTL8832D:
		rxevm = halrf_iqk_get_rxevm_8832d(rf);
	break;
#endif

	default:
	break;
	}
	return rxevm;
}

u32 halrf_iqk_get_rximr(void *rf_void, u8 path, u32 idx)
{
	struct rf_info *rf = (struct rf_info *)rf_void;
	u32 rximr =0x0;
	
	switch (rf->ic_type) {

#ifdef RF_8852A_SUPPORT
		case RF_RTL8852A:
			rximr = 0x0;
		break;
#endif		
#ifdef RF_8852B_SUPPORT
		case RF_RTL8852B:
			rximr = halrf_iqk_get_rximr_8852b(rf, path, idx);
		break;
#endif
#ifdef RF_8852BT_SUPPORT
		case RF_RTL8852BT:
			rximr = halrf_iqk_get_rximr_8852bt(rf, path, idx);
		break;
#endif
#ifdef RF_8852BPT_SUPPORT
		case RF_RTL8852BPT:
			rximr = halrf_iqk_get_rximr_8852bpt(rf, path, idx);
		break;
#endif
#ifdef RF_8852C_SUPPORT
		case RF_RTL8852C:
			rximr = halrf_iqk_get_rximr_8852c(rf, path, idx);
		break;
#endif
#ifdef RF_8832BR_SUPPORT
		case RF_RTL8832BR:
			rximr = halrf_iqk_get_rximr_8832br(rf, path, idx);
		break;
#endif
#ifdef RF_8192XB_SUPPORT
		case RF_RTL8192XB:
			rximr = halrf_iqk_get_rximr_8192xb(rf, path, idx);
		break;
#endif
#ifdef RF_8852D_SUPPORT
		case RF_RTL8852D:
			rximr = halrf_iqk_get_rximr_8852d(rf, path, idx);
		break;
#endif
#ifdef RF_8832D_SUPPORT
		case RF_RTL8832D:
			rximr = halrf_iqk_get_rximr_8832d(rf, path, idx);
		break;
#endif
		default:
		break;
	}
	return rximr;
}


//#endif
