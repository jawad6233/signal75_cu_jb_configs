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

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "camera_custom_if.h"

//<2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property
#define LOG_TAG "Camera Config"
#include <cutils/properties.h>
 #include <android/log.h>
 #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "keymatch", __VA_ARGS__)
//>2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property
namespace NSCamCustom
{
/*******************************************************************************
* 
*******************************************************************************/
#include "cfg_tuning_mt6575.h"
#include "cfg_facebeauty_tuning.h"
#include "flicker_tuning.h"
//
#include "cfg_setting_imgsensor.h"
#include "cfg_tuning_imgsensor.h"

/*******************************************************************************
* custom exif
*******************************************************************************/
//<2012/10/11,daisy zang,[8317][CQ][BU2SC00136449][BU2SC00136677][CAMERA]<The "Maker" and "Model" display have fault. "Maker" and "Model"  are empty>
#define EN_CUSTOM_EXIF_INFO
//>2012/10/11,daisy zang,[8317][CQ][BU2SC00136449][BU2SC00136677][CAMERA]<The "Maker" and "Model" display have fault. "Maker" and "Model"  are empty>


//<2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property
char buf[32];
bool ReadFinish=false;
//<2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property

MINT32 custom_SetExif(void **ppCustomExifTag)
{
#ifdef EN_CUSTOM_EXIF_INFO
//<2012/10/11,daisy zang,[8317][CQ][BU2SC00136449][BU2SC00136677][CAMERA]<The "Maker" and "Model" display have fault. "Maker" and "Model"  are empty>
#define CUSTOM_EXIF_STRING_MAKE  "MOTOROLA"
#if defined(ARIMA_PROJECT_HAWK35) 
        #ifdef GEMINI        
           #define  CUSTOM_EXIF_STRING_MODEL "XT916"       
        #else
            #define CUSTOM_EXIF_STRING_MODEL  "XT915"
        #endif
 #else
        #ifdef GEMINI 
	  #define  CUSTOM_EXIF_STRING_MODEL  "XT919"
	#else 
	   #define  CUSTOM_EXIF_STRING_MODEL "XT918"
	#endif
#endif

//<2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property
       if (ReadFinish==false)
      {
	 	memset(buf, 0x00, 32);
	        property_get("ro.build.product", buf, "0");
		LOGD("Daisy test,get value form system property,%s",buf);
		ReadFinish=true;
      	}
//>2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property

//#define CUSTOM_EXIF_STRING_MODEL "custom model"
//>2012/10/11,daisy zang,[8317][CQ][BU2SC00136449][BU2SC00136677][CAMERA]<The "Maker" and "Model" display have fault. "Maker" and "Model"  are empty>
//<2013/01/22,daisy zang,[8315][8317][Camera]Change the CUSTOM_EXIF_STRING_SOFTWARE to "Android"
#define CUSTOM_EXIF_STRING_SOFTWARE "Android"
//>2013/01/22,daisy zang,[8315][8317][Camera]Change the CUSTOM_EXIF_STRING_SOFTWARE to "Android"
static customExifInfo_t exifTag = {CUSTOM_EXIF_STRING_MAKE,CUSTOM_EXIF_STRING_MODEL,CUSTOM_EXIF_STRING_SOFTWARE};
//<2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property
    strcpy( (char *)exifTag.strModel,(char const *)buf);	
//>2012/11/30,daisy zang,[8315][8317][CQ][BU2SC00140403][BU2SC00140312][Camera]Change the model name read from Systerm property
    if (0 != ppCustomExifTag) {
        *ppCustomExifTag = (void*)&exifTag;
    }
    return 0;
#else
    return -1;
#endif
}
//
customExif_t const&
getCustomExif()
{
    static customExif_t inst = {
//<2013/02/06-ClarkLin-ExpProgram change to program normal
        bEnCustom       :   true,  // default value: false.
        u4ExpProgram    :   2,      // default value: 0.    '0' means not defined, '1' manual control, '2' program normal
//>2013/02/06-ClarkLin
    };
    return inst;
}
//
/*******************************************************************************
* LCM physical orienation 
*   Return:
*       0   : no inverse
*       1   : inverse
*       -1  : error
*******************************************************************************/
MUINT32
getLCMPhysicalOrientation()
{
    return ::atoi(MTK_LCM_PHYSICAL_ROTATION); 
}

/*******************************************************************************
* Author : cotta
* Functionality : custom flashlight gain between preview/capture flash
*******************************************************************************/
#define FLASHLIGHT_CALI_LED_GAIN_PRV_TO_CAP_10X 10
MUINT32 custom_GetFlashlightGain10X(void)
{
    // x10 , 1 mean 0.1x gain
    //10 means no difference. use torch mode for preflash and cpaflash
    //> 10 means capture flashlight is lighter than preflash light. < 10 is opposite condition.


    return (MUINT32)FLASHLIGHT_CALI_LED_GAIN_PRV_TO_CAP_10X;
}

MUINT32 custom_BurstFlashlightGain10X(void)
{
    return (MUINT32)FLASHLIGHT_CALI_LED_GAIN_PRV_TO_CAP_10X;
}


/*******************************************************************************
* 
*******************************************************************************/
};  //NSCamCustom

