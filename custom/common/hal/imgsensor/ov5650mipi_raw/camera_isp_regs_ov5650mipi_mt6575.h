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

/*******************************************************************************
*   ISP_NVRAM_REGISTER_STRUCT
********************************************************************************/
Idx:{//ISP_NVRAM_REG_INDEX_STRUCT
    Shading     :0,
    OB          :0,
    DM          :0,
    DP          :0, 
    NR1         :0,
    NR2         :0,
    EE          :0,
    Saturation  :0,
    Contrast    :4,
    Hue         :1,
    CCM         :2,
    Gamma       :0
},
Shading:{
    {set:{//00 Preview
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x10000000,0x90409030,0x00204120,0x00420033,0x20202020,
    }},
    {set:{//01 Capture
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x10000000,0xF050F03C,0x00240020,0x0052003F,0x20202020,
    }},
    {set:{//02
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    }}
},
OB:{
    {set:{//00
        0x91919191
    }}
}, 
DM:{
    {set:{//00 Preview ISO100/ISO200/ISO400
        0x00000100,	0x0A800810,	0x0020083F
    }}, 
    {set:{//01 Preview ISO800
        0x00000100,	0x0A800810,	0x0020083F
    }}, 
    {set:{//02 Preview ISO1600
        0x00000100,	0x0A800810,	0x0020083F
    }}, 
    {set:{//03 Capture ISO100/ISO200
        0x00000100,	0x0A800810,	0x0020083F
    }}, 
    {set:{//04 Capture ISO400
        0x00000100,	0x0A800810,	0x0020083F
    }}, 
    {set:{//05 Capture ISO800
        0x00000100,	0x0A800810,	0x0020083F
    }}, 
    {set:{//06 Capture ISO1600
        0x00000100,	0x0A800810,	0x0020083F
    }}
}, 
DP:{//Auto Defect
    {set:{//00
        0x000006E7, 0x50285050,	0x006003A0,	0x00300050,	0x000009B7
    }},
    {set:{//01
        0x000006E7, 0x50285050,	0x006003A0,	0x00300050,	0x000009B7
    }},
    {set:{//02
        0x000006E7, 0x50285050,	0x006003A0,	0x00300050,	0x000009B7
    }}, 
    {set:{//03 Disable (Do not modify me)
        0x00000000, 0x50285050, 0x006003A0, 0x00300050, 0x000008B7
    }}
},
NR1:{
    {set:{//00 Preview ISO100
        0x000002E7, 0x000011A0, 0x092328C8, 0x00000678, 0x02020303, 0x04040606, 0x02020303, 
        0x04040606, 0x02020303, 0x04040606, 0x02020303, 0x04040606, 0x0206090D, 0x10101010, 
    }},
    {set:{//01 Preview ISO200
        0x00000227, 0x000001A0, 0x092528C8, 0x00000888, 0x03030305, 0x05070709, 0x03030305, 
        0x05050709, 0x03030305, 0x05050709, 0x03030305, 0x05050709, 0x0206090D, 0x10101010, 
    }},
    {set:{//02 Preview ISO400
        0x000002E7, 0x000011A0, 0x092728C8, 0x0000089A, 0x0C0C0E0E, 0x10101214, 0x0C0C0E0E, 
        0x10101214, 0x0C0C0E0E, 0x10101214, 0x0C0C0E0E, 0x10101214, 0x0206090D, 0x10101010, 
    }},
    {set:{//03 Preview ISO800
        0x000002E7, 0x000011A0, 0x092928C8, 0x0000089C, 0x10101012, 0x12121418, 0x10101012, 
        0x12121418, 0x10101012, 0x12121418, 0x10101010, 0x12121418, 0x0206090D, 0x10101010, 
    }},
    {set:{//04 Preview ISO1600
        0x000002E7, 0x000011A0, 0x092D28C8, 0x0000089C, 0x03090C0E, 0x10121416, 0x04090B0E, 
        0x0F101213, 0x04090B0E, 0x0F101213, 0x02090B0E, 0x11131518, 0x0206090D, 0x10101010, 
    }},
    {set:{//05 Capture ISO100
        0x000002E7, 0x000011A0, 0x092328C8, 0x00000678, 0x02020303, 0x04040606, 0x02020303, 
        0x04040606, 0x02020303, 0x04040606, 0x02020303, 0x04040606, 0x0206090D, 0x10101010, 
    }},
    {set:{//06 Capture ISO200
        0x00000227, 0x000001A0, 0x092428C8, 0x00000888, 0x03030505, 0x07070909, 0x03030505, 
        0x07070909, 0x03030505, 0x07070909, 0x03030505, 0x07070909, 0x0206090D, 0x10101010, 
    }}, 
    {set:{//07 Capture ISO400
        0x000002E7, 0x000011A0, 0x092728C8, 0x0000089A, 0x02050507, 0x07090D0F, 0x05050707, 
        0x090D0F0F, 0x05050707, 0x09090D0F, 0x05050707, 0x09090D0F, 0x0206090D, 0x10101010, 
    }},
    {set:{//08 Capture ISO800
        0x000002E7, 0x000011A0, 0x092728C8, 0x0000089A, 0x03060909, 0x0B0B0D0F, 0x0306090B, 
        0x0D0D0F0F, 0x0306090B, 0x0B0D0D0F, 0x0206090B, 0x0B0D0D0F, 0x0206090D, 0x10101010, 
    }},
    {set:{//09 Capture IS1600
        0x000002E7, 0x000011A0, 0x092928C8, 0x0000089C, 0x0306090C, 0x0C0E0E10, 0x0306090C, 
        0x0C0E0E10, 0x0306090C, 0x0C0E0E10, 0x0206090C, 0x0C0E0E10, 0x0206090D, 0x10101010, 
    }},
    {set:{//10 Disable (Do not modify me)
        0x000000C0, 0x000011A0, 0x094428A0, 0x000007AF, 0x03050709, 0x0B0D0F11, 0x03050709, 
        0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x0406090D, 0x10101010, 
    }}
},
NR2:{
    {set:{//00 Preview ISO100
        0x00200003, 0x00191414, 0x00D27768, 0x05090E14, 0x0205070A, 0x01107ACE, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x0306090D, 
    }},
    {set:{//01 Preview ISO200
        0x00200003, 0x00191414, 0x00D27788, 0x1014181C, 0x1014181C, 0x01107ACE, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x0306090D, 
    }},
    {set:{//02 Preview ISO400
        0x00200003, 0x00191414, 0x00D27788, 0x14181C24, 0x141C242C, 0x01107ACE, 0x08080808, 0x10101010, 0x01AF5B88, 0x0000056B, 0x0306090D, 
    }},
    {set:{//03 Preview ISO800
        0x00200003, 0x00191414, 0x00D27788, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B88, 0x0000056B, 0x060B1119, 
    }},
    {set:{//04 Preview ISO1600
        0x00200003, 0x00191414, 0x00D27768, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }},
    {set:{//05 Capture Mode0 ISO100
        0x00200002, 0x00191414, 0x00D27768, 0x05090E14, 0x0205070A, 0x01107ACE, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x0306090D, 
    }},
    {set:{//06 Capture Mode0 ISO200
        0x00200002, 0x00191414, 0x00D27768, 0x080F1721, 0x01030406, 0x00B06A8E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x050A0F16, 
    }},
    {set:{//07 Capture Mode0 ISO400
        0x00200003, 0x00191414, 0x00D27768, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }},
    {set:{//08 Capture Mode0 ISO800
        0x00200003, 0x00191414, 0x00D27768, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }},
    {set:{//09 Capture Mode0 ISO1600
        0x00200003, 0x00191414, 0x00D27768, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }}, 
    {set:{//10 Capture Mode1 ISO100
        0x00210002, 0x00191414, 0x00D27768, 0x05090E14, 0x0205070A, 0x01107ACE, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x0306090D, 
    }},
    {set:{//11 Capture Mode1 ISO200
        0x00210002, 0x00191414, 0x00D27768, 0x080F1721, 0x01030406, 0x00B06A8E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x050A0F16, 
    }},
    {set:{//12 Capture Mode1 ISO400
        0x00210003, 0x00191414, 0x00D27768, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }},
    {set:{//13 Capture Mode1 ISO800
        0x00210003, 0x00191414, 0x00D27768, 0x09111925, 0x101F2D41, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }},
    {set:{//14 Capture Mode1 ISO1600
        0x00210003, 0x00191414, 0x00D27768, 0x090F1521, 0x101B2937, 0x0110728E, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x060B1119, 
    }},
    {set:{//15 Disable (Do not modify me)
        0x00000000, 0x0001FF01, 0x00523264, 0x04090B0F, 0x050A0B10, 0x02107294, 0x08101820, 0x10080604, 0x01AF5B43, 0x0000056B, 0x0306070A, 
    }}
},
EE:{//EE
    {set:{//00 Preview ISO100 (middle sharpness)
        0x00000028, 0x0037372D, 0x00320128, 0x023C0A5A, 0x02E70482, 0x033101AA, 0xFFFFFD0D, 
    }},
    {set:{//01 Preview ISO200 (middle sharpness)
        0x00000026, 0x00281E2D, 0x00240028, 0x01E0085A, 0x026D0382, 0x01E000AA, 0xFFFFFD0D, 
    }},
    {set:{//02 Preview ISO400 (middle sharpness)
        0x00000024, 0x00140A2D, 0x00000049, 0x0145067B, 0x01A602A3, 0x01D000CB, 0xFFFFFD0D, 
    }},
    {set:{//03 Preview ISO800 (middle sharpness)
        0x00000024, 0x0008022D, 0x00000063, 0x00ED0495, 0x013401BD, 0x015200E5, 0xFFFFFB0D, 
    }},
    {set:{//04 Preview ISO1600 (middle sharpness)
        0x00000028, 0x007F3721, 0x000E0068, 0x00DB049A, 0x011C01C2, 0x013800EA, 0xFFFFFB0D, 
    }},
    {set:{//05 Capture ISO100 (middle sharpness)
        0x0000002A, 0x0037372D, 0x00800328, 0x03350D5A, 0x03FF0582, 0x033100AA, 0xFFFFFD0D, 
    }},
    {set:{//06 Capture ISO200 (middle sharpness)
        0x00000028, 0x0037372D, 0x0060013A, 0x03350E6C, 0x03FF0594, 0x026D00BC, 0xFFFFFD0D, 
    }},
    {set:{//07 Capture ISO400 (middle sharpness)
        0x00000028, 0x0037372D, 0x00400049, 0x026D0B7B, 0x033505A3, 0x026D00CB, 0xFFFFFD0D, 
    }},
    {set:{//08 Capture ISO800 (middle sharpness)
        0x00000028, 0x0037372D, 0x000F0063, 0x00ED0495, 0x013401BD, 0x015200E5, 0xFFFFFB0D, 
    }},
    {set:{//09 Capture ISO1600 (middle sharpness)
        0x00000028, 0x00281E2D, 0x000E0068, 0x00DB049A, 0x011C01C2, 0x013800EA, 0xFFFFFB0D, 
    }},
    {set:{//10  no one uses this, this is Min EE (low sharpness)
        0x00000024, 0x0008022D, 0x00050023, 0x012C0B3C, 0x020001D0, 0x020000E7, 0xFFFF0005, 
    }},
    {set:{//11 no one uses this, this is Max EE (high sharpness)
        0x0000002C, 0x00373721, 0x000A0023, 0x03203937, 0x03FF01D0, 0x03FF00E7, 0xFFFF0005, 
    }}
}, 
Saturation:{
    {set:{//00 (middle saturation)
        0x00010709, 0x1020E0F0, 0x28464A46, 0x28000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//01 (middle saturation)
        0x00010709, 0x1020E0F0, 0x28464A46, 0x28000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//02 (middle saturation)
        0x00010709, 0x1020E0F0, 0x24424442, 0x24000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//03 (middle saturation)
        0x00010709, 0x1020E0F0, 0x20414141, 0x20000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//04 (middle saturation)
        0x00010709, 0x1020E0F0, 0x1E3C403C, 0x1A000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//05 no one uses this, this is Min Sat. (low saturation)
        0x00000709, 0x1020E0F0, 0x14343434, 0x14000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//06 no one uses this, this is Max Sat. (high saturation)
        0x00000709, 0x1020E0F0, 0x40606060, 0x40000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }}
}, 
Contrast:{
    //..........................................................................
    //  low brightness
    {set:{//00  //  low contrast
        0x00000008, 0x00F00000, 0xFF00003B
    }},
    {set:{//01  //  middle contrast
        0x00000008, 0x00F00000, 0xFF000040
    }},
    {set:{//02  //  high contrast
        0x00000008, 0x00F00000, 0xFF000045
    }}, 
    //..........................................................................
    //  middle brightness
    {set:{//03  //  low contrast
        0x00000008, 0x00000000, 0xFF00003B
    }},
    {set:{//04  //  middle contrast
        0x00000008, 0x00000000, 0xFF000040
    }},
    {set:{//05  //  high contrast
        0x00000008, 0x00000000, 0xFF000045
    }}, 
    //..........................................................................
    //  high brightness
    {set:{//06  //  low contrast
        0x00000008, 0x000A0000, 0xFF00003B
    }},
    {set:{//07  //  middle contrast
        0x00000008, 0x000A0000, 0xFF000040
    }},
    {set:{//08  //  high contrast
        0x00000008, 0x000A0000, 0xFF000045
    }}, 
}, 
Hue:{
    {set:{//00  //  low hue
        0x00000002, 0x808062AE
    }},
    {set:{//01  //  middle hue
        0x00000002, 0x00007F01
    }},
    {set:{//02  //  high hue
        0x00000002, 0x80806252
    }}
}, 
CCM:{
    {set:{//00
        0x01660434, 0x0432043A, 0x01380002, 0x001904D9, 0x01C00000, 
    }},
    {set:{//01
        0x01AE048E, 0x0420043F, 0x0135000A, 0x00150482, 0x016D0000, 
    }},
    {set:{//02
        0x0197046E, 0x04290427, 0x0143041C, 0x001B046D, 0x01520000, 
    }}
},
Gamma:{
    {set:{//00
        0x3F1A0D03, 0x8A7C6C5A, 0xC0B2A196, 0xE2DCD3CB, 0xFBF8F2ED, 
    }},
}

