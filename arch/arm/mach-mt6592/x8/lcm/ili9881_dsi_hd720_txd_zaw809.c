/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------
#define LCM_ID										0x9881

#define LCM_DSI_CMD_MODE								0

#define FRAME_WIDTH									(720)
#define FRAME_HEIGHT									(1280)
#define REGFLAG_DELAY             							0XAA
#define REGFLAG_END_OF_TABLE      						0xAB   // END OF REGISTERS MARKER

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)									(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)				lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)					lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)												lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)								lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)												lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)							lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)    

struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};



static struct LCM_setting_table lcm_initialization_setting[] = {
/*	{0xf0, 5, {0x52,0x08,0x02}},
	{0xee, 1, {0x01}},
	{0xb0, 16, {0x00,0x00,0x00,0x13,0x00,0x34,0x00,0x4c,0x00,0x61,0x00,0x76,0x00,0x99,0x00,0xcf}},
	{0xb1, 16, {0x00,0xf5,0x01,0x30,0x01,0x60,0x01,0xad,0x01,0xec,0x01,0xee,0x02,0x2b,0x02,0x6f}},
	{0xb2, 16, {0x02,0x99,0x02,0xd4,0x02,0xfe,0x03,0x2f,0x03,0x54,0x03,0x82,0x03,0xb2,0x03,0xcf}},
	{0xb3, 4, {0x03,0xf6,0x03,0xff}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x06}},
	{0xb0, 2, {0x2d,0x2e}},
	{0xb1, 2, {0x29,0x2a}},
	{0xb2, 2, {0x16,0x18}},
	{0xb3, 2, {0x10,0x12}},
	{0xb4, 2, {0x00,0x02}},
	{0xb5, 2, {0x31,0x31}},
	{0xb6, 2, {0x31,0x31}},
	{0xb7, 2, {0x31,0x31}},
	{0xb8, 2, {0x31,0x31}},
	{0xb9, 2, {0x31,0x31}},
	{0xba, 2, {0x31,0x31}},
	{0xbb, 2, {0x31,0x31}},
	{0xbc, 2, {0x31,0x31}},
	{0xbd, 2, {0x31,0x31}},
	{0xbe, 2, {0x31,0x31}},
	{0xbf, 2, {0x03,0x01}},
	{0xc0, 2, {0x13,0x11}},
	{0xc1, 2, {0x19,0x17}},
	{0xc2, 2, {0x2a,0x29}},
	{0xc3, 2, {0x2e,0x2d}},
	{0xe5, 2, {0x31,0x31}},
	{0xc4, 2, {0x2e,0x2d}},
	{0xc5, 2, {0x29,0x2a}},
	{0xc6, 2, {0x13,0x11}},
	{0xc7, 2, {0x19,0x17}},
	{0xc8, 2, {0x03,0x01}},
	{0xc9, 2, {0x31,0x31}},
	{0xca, 2, {0x31,0x31}},
	{0xcb, 2, {0x31,0x31}},
	{0xcc, 2, {0x31,0x31}},
	{0xcd, 2, {0x31,0x31}},
	{0xce, 2, {0x31,0x31}},
	{0xcf, 2, {0x31,0x31}},
	{0xd0, 2, {0x31,0x31}},
	{0xd1, 2, {0x31,0x31}},
	{0xd2, 2, {0x31,0x31}},
	{0xd3, 2, {0x00,0x02}},
	{0xd4, 2, {0x16,0x18}},
	{0xd5, 2, {0x10,0x12}},
	{0xd6, 2, {0x2a,0x29}},
	{0xd7, 2, {0x2d,0x2e}},
	{0xe6, 2, {0x31,0x31}},
	{0xd8, 5, {0x00,0x00,0x00,0x00,0x00}},
	{0xd9, 5, {0x00,0x00,0x00,0x00,0x00}},
	{0xe7, 1, {0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xed, 1, {0x30}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x03}},
	{0xb1, 2, {0x20,0x00}},
	{0xb0, 2, {0x20,0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xe5, 1, {0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xb0, 2, {0x17,0x06}},
	{0xb8, 1, {0x00}},
	{0xbd, 5, {0x03,0x03,0x00,0x03,0x03}},
	{0xb1, 2, {0x17,0x06}},
	{0xb9, 2, {0x00,0x03}},
	{0xb2, 2, {0x17,0x06}},
	{0xba, 2, {0x00,0x00}},
	{0xb3, 2, {0x17,0x06}},
	{0xbb, 2, {0x02,0x03}},
	{0xb4, 2, {0x17,0x06}},
	{0xb5, 2, {0x17,0x06}},
	{0xb6, 2, {0x17,0x06}},
	{0xb7, 2, {0x17,0x06}},
	{0xbc, 2, {0x02,0x03}},
	{0xe5, 1, {0x06}},
	{0xe6, 1, {0x06}},
	{0xe7, 1, {0x00}},
	{0xe8, 1, {0x06}},
	{0xe9, 1, {0x06}},
	{0xea, 1, {0x06}},
	{0xeb, 1, {0x00}},
	{0xec, 1, {0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xc0, 1, {0x0b}},
	{0xc1, 1, {0x09}},
	{0xc2, 1, {0xa6}},
	{0xc3, 1, {0x05}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x03}},
	{0xb2, 5, {0x05,0x00,0x4b,0x00,0x00}},
	{0xb3, 5, {0x05,0x00,0x4b,0x00,0x00}},
	{0xb4, 5, {0x05,0x00,0x17,0x00,0x00}},
	{0xb5, 5, {0x05,0x00,0x17,0x00,0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xc4, 1, {0x00}},
	{0xc5, 1, {0x02}},
	{0xc6, 1, {0x22}},
	{0xc7, 1, {0x03}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x03}},
	{0xb6, 5, {0x02,0x00,0x19,0x00,0x00}},
	{0xb7, 5, {0x02,0x00,0x19,0x00,0x00}},
	{0xb8, 5, {0x02,0x00,0x19,0x00,0x00}},
	{0xb9, 5, {0x02,0x00,0x19,0x00,0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xc8, 2, {0x07,0x20}},
	{0xc9, 2, {0x03,0x20}},
	{0xca, 2, {0x01,0x60}},
	{0xcb, 2, {0x01,0x60}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x03}},
	{0xba, 5, {0x53,0x01,0xf4,0x00,0x00}},
	{0xbb, 5, {0x53,0x01,0xf4,0x00,0x00}},
	{0xbc, 5, {0x53,0x00,0x1a,0x00,0x00}},
	{0xbd, 5, {0x53,0x00,0x1a,0x00,0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xd1, 5, {0x00,0x05,0x01,0x07,0x10}},
	{0xd2, 5, {0x10,0x05,0x05,0x03,0x10}},
	{0xd3, 5, {0x20,0x00,0x43,0x07,0x10}},
	{0xd4, 5, {0x30,0x00,0x43,0x07,0x10}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xd0, 7, {0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0xd5, 11, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0xd6, 11, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0xd7, 11, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0xd8, 5, {0x00,0x00,0x00,0x00,0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x05}},
	{0xcc, 3, {0x00,0x00,0x01}},
	{0xcd, 3, {0x00,0x00,0x01}},
	{0xce, 3, {0x00,0x00,0x02}},
	{0xcf, 3, {0x00,0x00,0x02}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x03}},
	{0xc0, 4, {0x00,0x34,0x00,0x00}},
	{0xc1, 4, {0x00,0x00,0x34,0x00}},
	{0xc2, 4, {0x00,0x00,0x34,0x00}},
	{0xc3, 4, {0x00,0x00,0x34,0x00}},
	{0xf0, 5, {0x55,0xaa,0x52,0x08,0x03}},
	{0xc4, 1, {0x60}},
	{0xc5, 1, {0xc0}},
	{0xc6, 1, {0x00}},
	{0xc7, 1, {0x00}},
	{0x11, 1, {0x00}},
	{0xab, 150, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xab,0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x29, 1, {0x00}},
	{0xab, 20, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}*/
};

static struct LCM_setting_table lcm_sleep_out_setting[] = {
	// Sleep Out
	{0x11, 1, {0x00}},
	{REGFLAG_DELAY, 20, {}},

	// Display ON
	{0x29, 1, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
/*	// Display off sequence
	{0x28, 1, {0x00}},
	{REGFLAG_DELAY, 200, {}},

	// Sleep Mode On
	{0x10, 1, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}} */
};

static struct LCM_setting_table page1_select[] = {
/*	//CMD_Page 1
	{0xFF, 3,{0x98,0x81,0x01}},
	{REGFLAG_END_OF_TABLE, 0x00, {}} */
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

	for(i = 0; i < count; i++) {
		
		unsigned cmd;
		cmd = table[i].cmd;
		
	switch (cmd) {
			
		case REGFLAG_DELAY :
 			MDELAY(table[i].count);
   			break;
				
		case REGFLAG_END_OF_TABLE :
   			break;
				
		default:
			dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
			MDELAY(2);
		}
	}
	
}


static void init_lcm_registers(void)
{
	unsigned int data_array[16];
}
// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));

	params->type   = LCM_TYPE_DSI;

	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

#if (LCM_DSI_CMD_MODE)
	params->dsi.mode   = CMD_MODE;
	params->dsi.switch_mode = SYNC_PULSE_VDO_MODE;//SYNC_EVENT_VDO_MODE;
#else
    params->dsi.mode   = SYNC_PULSE_VDO_MODE;//SYNC_EVENT_VDO_MODE;
	params->dsi.switch_mode = CMD_MODE;
#endif
	params->dsi.switch_mode_enable = 0;

	// DSI
	/* Command mode setting */
	params->dsi.LANE_NUM				= LCM_FOUR_LANE;
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order 	= LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq   	= LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding     	= LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format      		= LCM_DSI_FORMAT_RGB888;

	// Highly depends on LCD driver capability.
	params->dsi.packet_size=256;
	//video mode timing

	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

	params->dsi.vertical_sync_active				= 3;
	params->dsi.vertical_backporch					= 20;
	params->dsi.vertical_frontporch					= 12;
	params->dsi.vertical_active_line					= FRAME_HEIGHT;

	params->dsi.horizontal_sync_active				= 30;
	params->dsi.horizontal_backporch				= 12;
	params->dsi.horizontal_frontporch				= 80;
	params->dsi.horizontal_active_pixel				= FRAME_WIDTH;
        params->dsi.PLL_CLOCK = 217;
	params->dsi.clk_lp_per_line_enable = 0;
	params->dsi.esd_check_enable = 0;// 1;
	params->dsi.customization_esd_check_enable = 0;

	params->dsi.word_count = 2160;
	params->dbi.te_mode = 0;
	params->dbi.te_edge_polarity = 0;
	params->dsi.intermediat_buffer_num = 0;
	params->dsi.CLK_HS_POST = 22;
	params->dsi.ssc_range = 8;
	params->dsi.ssc_disable = 1;
	params->dsi.HS_PRPR = 3;
	params->dsi.DA_HS_EXIT = 20;
}

static void lcm_init(void)
{
	unsigned int data_array[16];
	static int count = 0;

	//SET_RESET_PIN(1);
	MDELAY(1);
	//SET_RESET_PIN(0);
	MDELAY(20);
	//SET_RESET_PIN(1);
	MDELAY(20);
	
	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
 
}



static void lcm_suspend(void)
{
	unsigned int data_array[16];

	data_array[0]=0x00280500; // Display Off
	dsi_set_cmdq(data_array, 1, 1);
	
	data_array[0] = 0x00100500; // Sleep In
	dsi_set_cmdq(data_array, 1, 1);

	
	//SET_RESET_PIN(1);	
	//SET_RESET_PIN(0);
	MDELAY(100); // 1ms
	
	//SET_RESET_PIN(1);
	MDELAY(120);      

}


static void lcm_resume(void)
{
	lcm_init();

	//push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);

}


static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(data_array, 3, 1);

	data_array[0]= 0x002c3909;
	dsi_set_cmdq(data_array, 1, 0);

}

static unsigned int lcm_compare_id(void)
{
        return 1;
}

LCM_DRIVER ili9881_dsi_hd720_txd_zaw809_lcm_drv = 
{
	.name				= "ili9881_dsi_hd720_txd_zaw809",
	.set_util_funcs			= lcm_set_util_funcs,
	.compare_id			= lcm_compare_id,
	.get_params			= lcm_get_params,
	.init				= lcm_init,
	.suspend			= lcm_suspend,
	.resume         		= lcm_resume,
#if (LCM_DSI_CMD_MODE)
	.update				= lcm_update,
#endif
};
