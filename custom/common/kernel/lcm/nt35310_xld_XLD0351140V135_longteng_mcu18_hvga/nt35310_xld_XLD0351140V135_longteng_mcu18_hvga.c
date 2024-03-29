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
        
    #define Lcd_Log printf
#else
    #include <linux/string.h>
    #include <linux/kernel.h>
    #include <mach/mt_gpio.h>
    #include <mach/mt_pm_ldo.h>
        
    #define Lcd_Log printk
#endif
#include "lcm_drv.h"


// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (320)
#define FRAME_HEIGHT (480)
#define LCM_ID       (0x5310)
#define GPIO_LCD_ID_PIN GPIO_LCM_ID_PIN

#define __LCM_TE_ON__
// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))
static unsigned int lcm_compare_id(void);
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height);

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

static __inline unsigned int HIGH_BYTE(unsigned int val)
{
    return (val >> 8) & 0xFF;
}

static __inline unsigned int LOW_BYTE(unsigned int val)
{
    return (val & 0xFF);
}

static __inline void send_ctrl_cmd(unsigned int cmd)
{
    lcm_util.send_cmd(cmd);
}

static __inline void send_data_cmd(unsigned int data)
{
    lcm_util.send_data(data);
}

static __inline unsigned int read_data_cmd()
{
    return lcm_util.read_data();
}

static __inline void set_lcm_register(unsigned int regIndex,
                                      unsigned int regData)
{
    send_ctrl_cmd(regIndex);
    send_data_cmd(regData);
}

static void sw_clear_panel(unsigned int color)
{
    unsigned short x0, y0, x1, y1, x, y;
    unsigned short h_X_start,l_X_start,h_X_end,l_X_end,h_Y_start,l_Y_start,h_Y_end,l_Y_end;

    x0 = (unsigned short)0;
    y0 = (unsigned short)0;
    x1 = (unsigned short)FRAME_WIDTH-1;
    y1 = (unsigned short)FRAME_HEIGHT-1;

    h_X_start=((x0&0xFF00)>>8);
    l_X_start=(x0&0x00FF);
    h_X_end=((x1&0xFF00)>>8);
    l_X_end=(x1&0x00FF);

    h_Y_start=((y0&0xFF00)>>8);
    l_Y_start=(y0&0x00FF);
    h_Y_end=((y1&0xFF00)>>8);
    l_Y_end=(y1&0x00FF);

    send_ctrl_cmd(0x2A);
    send_data_cmd(h_X_start); 
    send_data_cmd(l_X_start); 
    send_data_cmd(h_X_end); 
    send_data_cmd(l_X_end); 

    send_ctrl_cmd(0x2B);
    send_data_cmd(h_Y_start); 
    send_data_cmd(l_Y_start); 
    send_data_cmd(h_Y_end); 
    send_data_cmd(l_Y_end); 
    //MDELAY(120);
    
    send_ctrl_cmd(0x29); 

    send_ctrl_cmd(0x2C);
    for (y = y0; y <= y1; ++ y) {
        for (x = x0; x <= x1; ++ x) {
            lcm_util.send_data(color);
        }
    }
}

static int get_lcd_id(void)
{
    mt_set_gpio_mode(GPIO_LCD_ID_PIN,0);
    mt_set_gpio_dir(GPIO_LCD_ID_PIN,0);
    mt_set_gpio_pull_enable(GPIO_LCD_ID_PIN,1);
    mt_set_gpio_pull_select(GPIO_LCD_ID_PIN,0);
    MDELAY(1);

    return mt_get_gpio_in(GPIO_LCD_ID_PIN);
}

static void init_lcm_registers(void)
{
    ///////////NT35310+IVO3.5_MPU////////////////
    send_ctrl_cmd(0xED);
    send_data_cmd(0x01);
    send_data_cmd(0xFE);
    
    send_ctrl_cmd(0xEE);
    send_data_cmd(0xDE);
    send_data_cmd(0x21);
    
    send_ctrl_cmd(0xB3);    
    send_data_cmd(0x00);//00=MCU 01=RGB
    
    send_ctrl_cmd(0xC0);
    send_data_cmd(0x44);
    send_data_cmd(0x44);
    send_data_cmd(0x10);
    send_data_cmd(0x10);
    
    send_ctrl_cmd(0xB4);  //15=2DOT 3F=column
    send_data_cmd(0x0C); //0X0F
    
    send_ctrl_cmd(0xC4);  //Set VCOM
    send_data_cmd(0x63);  //0x4B   0x5D
    
    //////////////////Enter Page1
    send_ctrl_cmd(0xBF);
    send_data_cmd(0xAA);
    
    send_ctrl_cmd(0xB0);
    send_data_cmd(0x0D);
    send_data_cmd(0x00);
    send_data_cmd(0x0D);
    send_data_cmd(0x00);
    send_data_cmd(0x11);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x21);
    send_data_cmd(0x00);
    send_data_cmd(0x2D);
    send_data_cmd(0x00);
    send_data_cmd(0x3D);
    send_data_cmd(0x00);
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB1);
    send_data_cmd(0x80);
    send_data_cmd(0x00);
    send_data_cmd(0x8B);
    send_data_cmd(0x00);
    send_data_cmd(0x96);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB2);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x02);
    send_data_cmd(0x00);
    send_data_cmd(0x03);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB3);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB4);
    send_data_cmd(0x8B);
    send_data_cmd(0x00);
    send_data_cmd(0x96);
    send_data_cmd(0x00);
    send_data_cmd(0xA1);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB5);
    send_data_cmd(0x02);
    send_data_cmd(0x00);
    send_data_cmd(0x03);
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB6);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB7);
    send_data_cmd(0x3F);//3E
    send_data_cmd(0x00);
    send_data_cmd(0x5E);
    send_data_cmd(0x00);
    send_data_cmd(0x9E);
    send_data_cmd(0x00);
    send_data_cmd(0x74);
    send_data_cmd(0x00);
    send_data_cmd(0x8C);
    send_data_cmd(0x00);
    send_data_cmd(0xAC);
    send_data_cmd(0x00);
    send_data_cmd(0xDC);
    send_data_cmd(0x00);
    send_data_cmd(0x70);
    send_data_cmd(0x00);
    send_data_cmd(0xB9);
    send_data_cmd(0x00);
    send_data_cmd(0xEC);
    send_data_cmd(0x00);
    send_data_cmd(0xDC);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xB8);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xC2);
    send_data_cmd(0x0A);//00
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xC9);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xE0);
    send_data_cmd(0x00);//
    send_data_cmd(0x00);
    send_data_cmd(0x01);//
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x32);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x79);
    send_data_cmd(0x00);
    send_data_cmd(0x8A);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xA4);
    send_data_cmd(0x00);
    send_data_cmd(0xB2);
    send_data_cmd(0x00);
    
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0xC0);
    send_data_cmd(0x00);
    send_data_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0xCC);
    send_data_cmd(0x00);
    send_data_cmd(0xD3);
    send_data_cmd(0x00);
    send_data_cmd(0xF3);
    send_data_cmd(0x00);  
    
    send_ctrl_cmd(0xE1);
    send_data_cmd(0x00);//
    send_data_cmd(0x00);
    send_data_cmd(0x01);//
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x32);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x79);
    send_data_cmd(0x00);
    send_data_cmd(0x8A);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xA4);
    send_data_cmd(0x00);
    send_data_cmd(0xB2);
    send_data_cmd(0x00);
    
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0xC0);
    send_data_cmd(0x00);
    send_data_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0xCC);
    send_data_cmd(0x00);
    send_data_cmd(0xD3);
    send_data_cmd(0x00);
    send_data_cmd(0xF3);
    send_data_cmd(0x00);  
    
    send_ctrl_cmd(0xE2);
    send_data_cmd(0x00);//
    send_data_cmd(0x00);
    send_data_cmd(0x01);//
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x32);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x79);
    send_data_cmd(0x00);
    send_data_cmd(0x8A);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xA4);
    send_data_cmd(0x00);
    send_data_cmd(0xB2);
    send_data_cmd(0x00);
    
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0xC0);
    send_data_cmd(0x00);
    send_data_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0xCC);
    send_data_cmd(0x00);
    send_data_cmd(0xD3);
    send_data_cmd(0x00);
    send_data_cmd(0xF3);
    send_data_cmd(0x00);  
    
    send_ctrl_cmd(0xE3);
    send_data_cmd(0x00);//
    send_data_cmd(0x00);
    send_data_cmd(0x01);//
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x32);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x79);
    send_data_cmd(0x00);
    send_data_cmd(0x8A);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xA4);
    send_data_cmd(0x00);
    send_data_cmd(0xB2);
    send_data_cmd(0x00);
    
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0xC0);
    send_data_cmd(0x00);
    send_data_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0xCC);
    send_data_cmd(0x00);
    send_data_cmd(0xD3);
    send_data_cmd(0x00);
    send_data_cmd(0xF3);
    send_data_cmd(0x00);  
    
    send_ctrl_cmd(0xE4);
    send_data_cmd(0x00);//
    send_data_cmd(0x00);
    send_data_cmd(0x01);//
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x32);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x79);
    send_data_cmd(0x00);
    send_data_cmd(0x8A);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xA4);
    send_data_cmd(0x00);
    send_data_cmd(0xB2);
    send_data_cmd(0x00);
    
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0xC0);
    send_data_cmd(0x00);
    send_data_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0xCC);
    send_data_cmd(0x00);
    send_data_cmd(0xD3);
    send_data_cmd(0x00);
    send_data_cmd(0xF3);
    send_data_cmd(0x00);  
    
    send_ctrl_cmd(0xE5);
    send_data_cmd(0x00);//
    send_data_cmd(0x00);
    send_data_cmd(0x01);//
    send_data_cmd(0x00);
    send_data_cmd(0x04);
    send_data_cmd(0x00);
    send_data_cmd(0x19);
    send_data_cmd(0x00);
    send_data_cmd(0x32);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    
    send_data_cmd(0x5D);
    send_data_cmd(0x00);
    send_data_cmd(0x79);
    send_data_cmd(0x00);
    send_data_cmd(0x8A);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xA4);
    send_data_cmd(0x00);
    send_data_cmd(0xB2);
    send_data_cmd(0x00);
    
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0xC0);
    send_data_cmd(0x00);
    send_data_cmd(0xC7);
    send_data_cmd(0x00);
    send_data_cmd(0xCC);
    send_data_cmd(0x00);
    send_data_cmd(0xD3);
    send_data_cmd(0x00);
    send_data_cmd(0xF3);
    send_data_cmd(0x00);  
    
    //////////////////////////////////////////////////////////
    send_ctrl_cmd(0xE6);
    send_data_cmd(0x21);
    send_data_cmd(0x00);
    send_data_cmd(0x55);
    send_data_cmd(0x00);
    send_data_cmd(0x99);
    send_data_cmd(0x00);
    send_data_cmd(0x77);
    send_data_cmd(0x00);
    send_data_cmd(0x77);
    send_data_cmd(0x00);
    send_data_cmd(0x76);
    send_data_cmd(0x00);
    
    send_data_cmd(0x78);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0x99);
    send_data_cmd(0x00);
    send_data_cmd(0x66);
    send_data_cmd(0x00);
    send_data_cmd(0x54);
    send_data_cmd(0x00);
    
    send_data_cmd(0x45);
    send_data_cmd(0x00);
    send_data_cmd(0x34);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    send_data_cmd(0x34);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xE7);
    send_data_cmd(0x21);
    send_data_cmd(0x00);
    send_data_cmd(0x55);
    send_data_cmd(0x00);
    send_data_cmd(0x99);
    send_data_cmd(0x00);
    send_data_cmd(0x77);
    send_data_cmd(0x00);
    send_data_cmd(0x77);
    send_data_cmd(0x00);
    send_data_cmd(0x76);
    send_data_cmd(0x00);
    
    send_data_cmd(0x78);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0x99);
    send_data_cmd(0x00);
    send_data_cmd(0x66);
    send_data_cmd(0x00);
    send_data_cmd(0x54);
    send_data_cmd(0x00);
    
    send_data_cmd(0x45);
    send_data_cmd(0x00);
    send_data_cmd(0x34);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    send_data_cmd(0x34);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xE8);
    send_data_cmd(0x21);
    send_data_cmd(0x00);
    send_data_cmd(0x55);
    send_data_cmd(0x00);
    send_data_cmd(0x99);
    send_data_cmd(0x00);
    send_data_cmd(0x77);
    send_data_cmd(0x00);
    send_data_cmd(0x77);
    send_data_cmd(0x00);
    send_data_cmd(0x76);
    send_data_cmd(0x00);
    
    send_data_cmd(0x78);
    send_data_cmd(0x00);
    send_data_cmd(0x98);
    send_data_cmd(0x00);
    send_data_cmd(0xBB);
    send_data_cmd(0x00);
    send_data_cmd(0x99);
    send_data_cmd(0x00);
    send_data_cmd(0x66);
    send_data_cmd(0x00);
    send_data_cmd(0x54);
    send_data_cmd(0x00);
    
    send_data_cmd(0x45);
    send_data_cmd(0x00);
    send_data_cmd(0x34);
    send_data_cmd(0x00);
    send_data_cmd(0x44);
    send_data_cmd(0x00);
    send_data_cmd(0x34);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xE9);
    send_data_cmd(0xAA);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0xE9);
    send_data_cmd(0xAA);
    send_data_cmd(0x00);
    send_data_cmd(0x00);
    send_data_cmd(0x00);  
    
    //Enter Page0
    send_ctrl_cmd(0x00);
    send_data_cmd(0xAA);
    
    send_ctrl_cmd(0xF1);
    send_data_cmd(0x01);
    
    send_ctrl_cmd(0xEE);
    send_data_cmd(0xDE);
    send_data_cmd(0x21);
    
    send_ctrl_cmd(0xF3);
    send_data_cmd(0x00);
       
    send_ctrl_cmd(0x36);
    send_data_cmd(0x00);
    
    //send_ctrl_cmd(0x20);
    send_ctrl_cmd(0x3A);
    send_data_cmd(0x66);
    
    send_ctrl_cmd(0x35);
    send_data_cmd(0x00);
    
    send_ctrl_cmd(0x11);
    MDELAY(120);
    
    send_ctrl_cmd(0x29);
    send_ctrl_cmd(0x2C);
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

    params->type   = LCM_TYPE_DBI;
    params->ctrl   = LCM_CTRL_PARALLEL_DBI;
    params->width  = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;
    params->io_select_mode = 3;
    /* serial host interface configurations */
    
    params->dbi.port                    = 0;
    params->dbi.data_width              = LCM_DBI_DATA_WIDTH_18BITS;
    params->dbi.data_format.color_order = LCM_COLOR_ORDER_RGB;
    params->dbi.data_format.trans_seq   = LCM_DBI_TRANS_SEQ_MSB_FIRST;
    params->dbi.data_format.padding     = LCM_DBI_PADDING_ON_LSB;
    params->dbi.data_format.format      = LCM_DBI_FORMAT_RGB666;
    params->dbi.data_format.width       = LCM_DBI_DATA_WIDTH_18BITS;
    params->dbi.cpu_write_bits          = LCM_DBI_CPU_WRITE_16_BITS;
    params->dbi.io_driving_current      = LCM_DRIVING_CURRENT_6575_8MA;

    params->dbi.parallel.write_setup    = 1; //1
    params->dbi.parallel.write_hold     = 1; //1
    params->dbi.parallel.write_wait     = 4; // 4
    params->dbi.parallel.read_setup     = 3; // 1
    params->dbi.parallel.read_latency   = 20; //31
    params->dbi.parallel.wait_period    = 0; //6

#ifdef  __LCM_TE_ON__
    // enable tearing-free
    params->dbi.te_mode                 = LCM_DBI_TE_MODE_VSYNC_ONLY;
    params->dbi.te_edge_polarity        = LCM_POLARITY_RISING;    
#else 
    params->dbi.te_mode                 = LCM_DBI_TE_MODE_DISABLED;  
#endif
}

static void lcm_init(void)
{
#ifdef BUILD_LK
    upmu_set_rg_vgp2_vosel(5);
    upmu_set_rg_vgp2_en(1);
    MDELAY(50);
        
    upmu_set_rg_vgp3_vosel(3);
    upmu_set_rg_vgp3_en(1); 
#else
    hwPowerOn(MT6323_POWER_LDO_VGP2,VOL_2800,"LCM28");
    hwPowerOn(MT6323_POWER_LDO_VGP3,VOL_1800,"LCM18");
#endif
    MDELAY(100);
	
	SET_RESET_PIN(1);
	MDELAY(100);
	SET_RESET_PIN(0);
	MDELAY(200);
	SET_RESET_PIN(1);
	MDELAY(120);
	
	init_lcm_registers();
	sw_clear_panel(0x00);
	MDELAY(50);
}

static void lcm_suspend(void)
{
    send_ctrl_cmd(0x28);   // Display off 
    MDELAY(20); 
    send_ctrl_cmd(0x10);   // Enter Sleep mode
    MDELAY(120);  
}

static void lcm_resume(void)
{
#if 0
    send_ctrl_cmd(0x11);
    MDELAY(200);
    send_ctrl_cmd(0x29);
    MDELAY(10);
#else
    lcm_init();
#endif
}

static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
    unsigned short x0, y0, x1, y1;
    unsigned short h_X_start,l_X_start,h_X_end,l_X_end,h_Y_start,l_Y_start,h_Y_end,l_Y_end;

    x0 = (unsigned short)x;
    y0 = (unsigned short)y;
    x1 = (unsigned short)x+width-1;
    y1 = (unsigned short)y+height-1;

    h_X_start=((x0&0xFF00)>>8);
    l_X_start=(x0&0x00FF);
    h_X_end=((x1&0xFF00)>>8);
    l_X_end=(x1&0x00FF);

    h_Y_start=((y0&0xFF00)>>8);
    l_Y_start=(y0&0x00FF);
    h_Y_end=((y1&0xFF00)>>8);
    l_Y_end=(y1&0x00FF);

    send_ctrl_cmd(0x2A);
    send_data_cmd(h_X_start); 
    send_data_cmd(l_X_start); 
    send_data_cmd(h_X_end); 
    send_data_cmd(l_X_end); 

    send_ctrl_cmd(0x2B);
    send_data_cmd(h_Y_start); 
    send_data_cmd(l_Y_start); 
    send_data_cmd(h_Y_end); 
    send_data_cmd(l_Y_end); 
    //MDELAY(120);
    
    send_ctrl_cmd(0x29); 

    send_ctrl_cmd(0x2C);
}

static unsigned int lcm_compare_id(void)
{
    unsigned int id = 0;
    unsigned int temp1, temp2;

#ifdef BUILD_LK
    upmu_set_rg_vgp2_vosel(5);
    upmu_set_rg_vgp2_en(1);
    MDELAY(50);

    upmu_set_rg_vgp3_vosel(3);
    upmu_set_rg_vgp3_en(1);
#else
    hwPowerOn(MT6323_POWER_LDO_VGP2,VOL_2800,"LCM28");
    hwPowerOn(MT6323_POWER_LDO_VGP3,VOL_1800,"LCM18");
#endif
    MDELAY(100);

    SET_RESET_PIN(0);
    MDELAY(200);
    SET_RESET_PIN(1);
    MDELAY(120);
    
     send_ctrl_cmd(0xED);
    send_data_cmd(0x01);
    send_data_cmd(0xFE);

    send_ctrl_cmd(0xD4);
    read_data_cmd(); // 1
    read_data_cmd(); // 2
    temp1 = read_data_cmd(); // 3 
    temp2 = read_data_cmd(); // 4
    id = ((temp1 << 8) & 0xFF00) | (temp2 & 0x00FF);  //5310
	
#if defined(BUILD_LK)
    printf("LCM_ID should be %x, read_id = 0x%x\n", LCM_ID, id);
#endif
    
    return (LCM_ID == id)?1:0;  
}

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER nt35310_xld_XLD0351140V135_longteng_mcu18_hvga_lcm_drv = 
{
    .name            = "nt35310_xld_XLD0351140V135_longteng_mcu18_hvga",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .update         = lcm_update,
    .compare_id     = lcm_compare_id    
};
