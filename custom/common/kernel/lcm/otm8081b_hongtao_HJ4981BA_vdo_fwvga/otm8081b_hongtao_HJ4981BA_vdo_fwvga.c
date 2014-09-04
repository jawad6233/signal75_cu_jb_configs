

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


#ifdef BUILD_LK
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#else
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>
    #include <linux/string.h>
   
#endif
#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(480)
#define FRAME_HEIGHT 										(854)

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0xFB   // END OF REGISTERS MARKER

////#define LCM_DSI_CMD_MODE									0
static unsigned int lcm_esd_test = 0;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))

//static kal_bool IsFirstBoot = KAL_TRUE;

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)    

static struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[120];
};


static struct LCM_setting_table lcm_initialization_setting[] = {
	
	/*
	Note :

	Data ID will depends on the following rule.
	
		count of parameters > 1	=> Data ID = 0x39
		count of parameters = 1	=> Data ID = 0x15
		count of parameters = 0	=> Data ID = 0x05

	Structure Format :

	{DCS command, count of parameters, {parameter list}}
	{REGFLAG_DELAY, milliseconds of time, {}},

	...

	Setting ending by predefined flag
	
	{REGFLAG_END_OF_TABLE, 0x00, {}}
	*/
{0x00,1,{0x00}},
{0xff,3,{0x80,0x09,0x01}},
{0x00,1,{0x80}},
{0xff,2,{0x80,0x09}},
{0x00,1,{0x03}},
{0xff,1,{0x01}},
{0x00,1,{0xb4}},												  
{0xc0,1,{0x50}},   //50
{0x00,1,{0x82}},												  
{0xc5,1,{0xa3}},
{0x00,1,{0x90}},												  
{0xc5,2,{0x96,0x76}},   //
{0x00,1,{0x00}},												   
{0xd8,2,{0x97,0x97}},  //5.0V
{0x00,1,{0x00}},
{0xd9,1,{0x3d}},   //39
{0x00,1,{0x00}},
{0xe1,16,{0x09,0x0c,0x12,0x0e,0x08,0x1c,0x0e,0x0E,0x00,0x04,0x02,0x07,0x0F,0x21,0x1C,0x0f}},
{0x00,1,{0x00}},
{0xe2,16,{0x09,0x0c,0x12,0x0e,0x08,0x1c,0x0e,0x0E,0x00,0x04,0x02,0x07,0x0E,0x20,0x1D,0x0f}},
{0x00,1,{0x81}},
{0xc1,1,{0x77}},
{0x00,1,{0xa1}},
{0xc1,1,{0x0e}},

{0x00,1,{0xa0}},
{0xc1,1,{0xea}},//MIPI I/F

{0x00,1,{0x89}},
{0xc4,1,{0x08}},
{0x00,1,{0xa2}},
{0xc0,3,{0x04,0x00,0x02}},
{0x00,1,{0x80}},
{0xc4,1,{0x30}},
{0x00,1,{0xa6}},
{0xc1,1,{0x01}},
{0x00,1,{0xc0}},
{0xc5,1,{0x00}},
{0x00,1,{0x8b}},
{0xb0,1,{0x40}},
{0x00,1,{0xb2}},
{0xf5,3,{0x15,0x00,0x15,0x00}},
{0x00,1,{0x93}},
{0xc5,1,{0x03}},
{0x00,1,{0x81}},
{0xc4,1,{0x83}},
{0x00,1,{0x92}},
{0xc5,1,{0x01}},
{0x00,1,{0xb1}},
{0xc5,1,{0xa9}},
{0x00,1,{0x92}},
{0xb3,1,{0x45}},
{0x00,1,{0x90}},
{0xb3,1,{0x02}},
{0x00,1,{0x80}},
{0xc0,5,{0x00,0x58,0x00,0x14,0x16}},
{0x00,1,{0x90}},
{0xc0,6,{0x00,0x56,0x00,0x00,0x00,0x03}},
{0x00,1,{0xa6}},
{0xc1,3,{0x01,0x00,0x00}},
{0x00,1,{0x80}},
{0xce,12,{0x87,0x03,0x00,0x85,0x03,0x00,0x86,0x03,0x00,0x84,0x03,0x00}},
{0x00,1,{0xa0}},
{0xce,14,{0x38,0x03,0x03,0x58,0x00,0x00,0x00,0x38,0x02,0x03,0x59,0x00,0x00,0x00}},
{0x00,1,{0xb0}},
{0xce,14,{0x38,0x01,0x03,0x5a,0x00,0x00,0x00,0x38,0x00,0x03,0x5b,0x00,0x00,0x00}},
{0x00,1,{0xc0}},
{0xce,14,{0x30,0x00,0x03,0x5c,0x00,0x00,0x00,0x30,0x01,0x03,0x5d,0x00,0x00,0x00}},
{0x00,1,{0xd0}},
{0xce,14,{0x30,0x02,0x03,0x5e,0x00,0x00,0x00,0x30,0x03,0x03,0x5f,0x00,0x00,0x00}},
{0x00,1,{0xc7}},
{0xcf,1,{0x00}},
{0x00,1,{0xc9}},
{0xcf,1,{0x00}},
{0x00,1,{0xc4}},
{0xcb,6,{0x04,0x04,0x04,0x04,0x04,0x04}},
{0x00,1,{0xd9}},
{0xcb,6,{0x04,0x04,0x04,0x04,0x04,0x04}},
{0x00,1,{0x84}},
{0xcc,6,{0x0c,0x0a,0x10,0x0e,0x03,0x04}},
{0x00,1,{0x9e}},
{0xcc,1,{0x0b}},
{0x00,1,{0xa0}},
{0xcc,5,{0x09,0x0f,0x0d,0x01,0x02}},
{0x00,1,{0xb4}},
{0xcc,6,{0x0d,0x0f,0x09,0x0b,0x02,0x01}},
{0x00,1,{0xce}},
{0xcc,1,{0x0e}},
{0x00,1,{0xd0}},
{0xcc,7,{0x10,0x0a,0x0c,0x04,0x03,0x05,0x85}},
{0x00,1,{0x00}},
{0xff,3,{0xff,0xff,0xff}},
{0x3A, 1 ,{0x77}},
{0x11, 1 ,{0x00}}, 
{REGFLAG_DELAY, 50, {}},
{0x29, 1 ,{0x00}}, 
{REGFLAG_DELAY, 100, {}},	


	// Note
	// Strongly recommend not to set Sleep out / Display On here. That will cause messed frame to be shown as later the backlight is on.

	// Setting ending by predefined flag
{REGFLAG_END_OF_TABLE, 0x00, {}}
};



static struct LCM_setting_table lcm_sleep_out_setting[] = {
    // Sleep Out
	{0x11, 0, {0x00}},
    {REGFLAG_DELAY, 120, {}},

    // Display ON
	{0x29, 0, {0x00}},
    {REGFLAG_DELAY, 100, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x28, 0, {0x00}},
        {REGFLAG_DELAY, 120, {}},
    // Sleep Mode On
	{0x10, 0, {0x00}},
        {REGFLAG_DELAY, 20, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
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
       	}
    }
	
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

		// enable tearing-free
             params->dbi.te_mode				= LCM_DBI_TE_MODE_DISABLED;
             params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;
             params->dsi.mode   = SYNC_EVENT_VDO_MODE;
		// DSI
		/* Command mode setting */
		params->dsi.LANE_NUM				= LCM_TWO_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Highly depends on LCD driver capability.
		// Not support in MT6573
		params->dsi.packet_size=256;

		// Video mode setting		
		params->dsi.intermediat_buffer_num = 2;

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

		params->dsi.vertical_sync_active				= 4;//2
		params->dsi.vertical_backporch					= 16;//50
		params->dsi.vertical_frontporch					= 15;//20
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 

		params->dsi.horizontal_sync_active				= 10;//2
		params->dsi.horizontal_backporch				= 64;//100
		params->dsi.horizontal_frontporch				= 64;//100
		params->dsi.horizontal_blanking_pixel			= 60;   //add
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;


		// Bit rate calculation
		//params->dsi.pll_div1=30;//32		// fref=26MHz, fvco=fref*(div1+1)	(div1=0~63, fvco=500MHZ~1GHz)
		//params->dsi.pll_div2=1; 		// div2=0~15: fout=fvo/(2*div2)
                params->dsi.pll_div1=1;//48;		// fref=26MHz, fvco=fref*(div1+1)	(div1=0~63, fvco=500MHZ~1GHz)
		params->dsi.pll_div2=1; 		// div2=0~15: fout=fvo/(2*div2)
		 params->dsi.fbk_sel=1;	//add
                params->dsi.fbk_div =30;
                
    /* ESD or noise interference recovery For video mode LCM only. */ // Send TE packet to LCM in a period of n frames and check the response. 
		//params->dsi.lcm_int_te_monitor = FALSE; 
		//params->dsi.lcm_int_te_period = 1; // Unit : frames 
 
		// Need longer FP for more opportunity to do int. TE monitor applicably. 
		//if(params->dsi.lcm_int_te_monitor) 
		//	params->dsi.vertical_frontporch *= 2; 
 
		// Monitor external TE (or named VSYNC) from LCM once per 2 sec. (LCM VSYNC must be wired to baseband TE pin.) 
		//params->dsi.lcm_ext_te_monitor = FALSE; 
		// Non-continuous clock 
		//params->dsi.noncont_clock = TRUE; 
		//params->dsi.noncont_clock_period = 2; // Unit : frames
}

static void lcm_init(void)
{
	unsigned int data_array[64];

		#if defined(BUILD_LK)
	upmu_set_rg_vgp2_vosel(5);
	upmu_set_rg_vgp2_en(1);

	upmu_set_rg_vgp3_vosel(3);
	upmu_set_rg_vgp3_en(1);	
#else
	hwPowerOn(MT6323_POWER_LDO_VGP2, VOL_2800, "Lance_LCM");
       hwPowerOn(MT6323_POWER_LDO_VGP3, VOL_1800, "Lance_LCM");
#endif

    SET_RESET_PIN(1);
    SET_RESET_PIN(0);
    MDELAY(10);//Must > 10ms
    SET_RESET_PIN(1);
    MDELAY(40);//Must > 120ms

    push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_suspend(void)
{
    SET_RESET_PIN(1);
	 MDELAY(10);//Must > 10ms
    SET_RESET_PIN(0);
    MDELAY(10);//Must > 10ms
  ///  SET_RESET_PIN(1);
///   MDELAY(120);//Must > 120ms

	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_resume(void)
{
	//lcm_compare_id();

	lcm_init();
	
	////push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
}
static unsigned int lcm_compare_id(void)
{
	
	  	return 1;
}

#if defined (BIRD_ESD_CHECK)
static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_LK
	static int ok_count = 0;
	 unsigned char buffer[12];
	 unsigned int array[16];
	 int i;
	 
	if(lcm_esd_test)
  {
      lcm_esd_test = 0;
      return 1;
  }
	 	
	array[0] = 0x00013700;
	dsi_set_cmdq(array, 1, 1);
	MDELAY(10);
	read_reg_v2(0x0A, buffer, 1);
	 
	printk("mycat$$ truly ### esd check buffer[0] = 0x%x\r\n",buffer[0]);
	if(buffer[0] == 0x9C)
		return 0;
	else
		return 1;
 			
#endif
}

static unsigned int lcm_esd_recover(void)
{
  lcm_init();
	
#ifndef BUILD_LK	
	printk("mycat truly ### lcm_esd_recover \r\n");
#endif
	
	return 1;
}
#endif

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER otm8081b_hongtao_HJ4981BA_vdo_fwvga_lcm_drv = 
{
    .name			= "otm8081b_hongtao_HJ4981BA_vdo_fwvga",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,

    .compare_id    = lcm_compare_id,
   // .update         = lcm_update
   
#if defined (BIRD_ESD_CHECK)//rm esd resolve LCD  flick
	.esd_check = lcm_esd_check,
  .esd_recover = lcm_esd_recover,
#endif

};

