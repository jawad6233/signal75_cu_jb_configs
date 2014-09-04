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
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   sensor.h
 *
 * Project:
 * --------
 *   DUMA
 *
 * Description:
 * ------------
 *   Header file of Sensor driver
 *
 *
 * Author:
 * -------
 *   PC Huang (MTK02204)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 * 
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
/* SENSOR FULL SIZE */
#ifndef __SENSOR_H
#define __SENSOR_H

	//follow is define by jun
	/* SENSOR READ/WRITE ID */

#define GC0309_IMAGE_SENSOR_QVGA_WIDTH       (320)
#define GC0309_IMAGE_SENSOR_QVGA_HEIGHT      (240)
#define GC0309_IMAGE_SENSOR_VGA_WIDTH        (640)
#define GC0309_IMAGE_SENSOR_VGA_HEIGHT       (480)
#define GC0309_IMAGE_SENSOR_SXGA_WIDTH       (1280)
#define GC0309_IMAGE_SENSOR_SXGA_HEIGHT      (1024)

#define GC0309_IMAGE_SENSOR_FULL_WIDTH	   GC0309_IMAGE_SENSOR_VGA_WIDTH  
#define GC0309_IMAGE_SENSOR_FULL_HEIGHT	   GC0309_IMAGE_SENSOR_VGA_HEIGHT    

#define GC0309_IMAGE_SENSOR_PV_WIDTH   GC0309_IMAGE_SENSOR_VGA_WIDTH   
#define GC0309_IMAGE_SENSOR_PV_HEIGHT  GC0309_IMAGE_SENSOR_VGA_HEIGHT

//SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD
#define GC0309_VGA_DEFAULT_PIXEL_NUMS		   (656)	
#define GC0309_VGA_DEFAULT_LINE_NUMS 		   (500)

#define GC0309_QVGA_DEFAULT_PIXEL_NUMS		   (656)	 
#define GC0309_QVGA_DEFAULT_LINE_NUMS		   (254)

/* MAX/MIN FRAME RATE (FRAMES PER SEC.) */
#define GC0309_MIN_FRAMERATE_5					(50)
#define GC0309_MIN_FRAMERATE_7_5 				(75)
#define GC0309_MIN_FRAMERATE_10					(100)

//Video Fixed Framerate
#define GC0309_VIDEO_FIX_FRAMERATE_5 			(50)
#define GC0309_VIDEO_FIX_FRAMERATE_7_5			(75)
#define GC0309_VIDEO_FIX_FRAMERATE_10			(100)
#define GC0309_VIDEO_FIX_FRAMERATE_15			(150)
#define GC0309_VIDEO_FIX_FRAMERATE_20			(200)
#define GC0309_VIDEO_FIX_FRAMERATE_25			(250)
#define GC0309_VIDEO_FIX_FRAMERATE_30			(300)


#define GC0309_WRITE_ID		0x42
#define GC0309_READ_ID		0x43

	//#define GC0309_SCCB_SLAVE_ADDR 0x42

typedef struct _SENSOR_INIT_INFO
{
	  kal_uint8 address;
	  kal_uint8 data;
}GC0309_SENSOR_INIT_INFO;
typedef enum __VIDEO_MODE__
{
	  GC0309_VIDEO_NORMAL = 0,
	  GC0309_VIDEO_MPEG4,	  
	  GC0309_VIDEO_MAX
} GC0309_VIDEO_MODE;

struct GC0309_sensor_STRUCT
{    
      	  kal_bool first_init;
	  kal_bool pv_mode;                 //True: Preview Mode; False: Capture Mode
	  kal_bool night_mode;              //True: Night Mode; False: Auto Mode
	  kal_bool MPEG4_Video_mode;      //Video Mode: MJPEG or MPEG4
	  kal_uint8 mirror;
	  kal_uint32 pv_pclk;               //Preview Pclk
	  kal_uint32 cp_pclk;               //Capture Pclk
	  kal_uint16 pv_dummy_pixels;          //Dummy Pixels
	  kal_uint16 pv_dummy_lines;           //Dummy Lines
	  kal_uint16 cp_dummy_pixels;          //Dummy Pixels
	  kal_uint16 cp_dummy_lines;           //Dummy Lines         
	  kal_uint16 fix_framerate;         //Fixed Framerate
	  kal_uint32 wb;
	  kal_uint32 exposure;
	  kal_uint32 effect;
	  kal_uint32 banding;
	  kal_uint16 pv_line_length;
	  kal_uint16 pv_frame_height;
	  kal_uint16 cp_line_length;
	  kal_uint16 cp_frame_height;
	  kal_uint16 video_current_frame_rate;
};


//export functions
UINT32 GC0309Open(void);
UINT32 GC0309GetResolution(MSDK_SENSOR_RESOLUTION_INFO_STRUCT *pSensorResolution);
UINT32 GC0309GetInfo(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_INFO_STRUCT *pSensorInfo, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 HGC0309Control(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *pImageWindow, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 GC0309FeatureControl(MSDK_SENSOR_FEATURE_ENUM FeatureId, UINT8 *pFeaturePara,UINT32 *pFeatureParaLen);
UINT32 GC0309Close(void);


#endif /* __SENSOR_H */
