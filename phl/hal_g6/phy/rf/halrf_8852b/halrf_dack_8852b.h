/******************************************************************************
 *
 * Copyright(c) 2007 - 2020  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/
#ifndef __HALRF_DACK_8852B_H__
#define __HALRF_DACK_8852B_H__
#ifdef RF_8852B_SUPPORT

#define DACK_VER_8852B 0x8

void halrf_dack_recover_8852b(struct rf_info *rf,
			      u8 offset,
			      enum rf_path path,
			      u32 val,
			      bool reload);
void halrf_dac_cal_8852b(struct rf_info *rf, bool force);
#endif
#endif /*  __INC_PHYDM_API_H_8852A__ */
