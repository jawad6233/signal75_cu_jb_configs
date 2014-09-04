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
    CCM         :0,
    Gamma       :0
},
Shading:{
    {set:{//00 Preview
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x10000000,0x9050903C,0xC2019900,0x0052003F,0x20202020,
    }},
    {set:{//01 Capture
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x10000000,0xF064F04B,0x00000000,0x0068004E,0x20202020,
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
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x03050709, 0x0B0D0F11, 0x03050709, 
        0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x0206090D, 0x10101010, 
    }},
    {set:{//01 Preview ISO200
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x03050709, 0x0B0D0F11, 0x03050709, 
        0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x0206090D, 0x10101010, 
    }},
    {set:{//02 Preview ISO400
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x080A0C0E, 0x10121416, 0x080A0C0E, 
        0x10121416, 0x080A0C0E, 0x10121416, 0x080A0C0E, 0x10121416, 0x0206090D, 0x10101010, 
    }},
    {set:{//03 Preview ISO800
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x080A0C0E, 0x10121416, 0x080A0C0E, 
        0x10121416, 0x080A0C0E, 0x10121416, 0x080A0C0E, 0x10121416, 0x0206090D, 0x10101010, 
    }},
    {set:{//04 Preview ISO1600
        0x000000C4, 0x000011A0, 0x093028C8, 0x0000089C, 0x050D1115, 0x181C1F23, 0x070D1114, 
        0x16181A1C, 0x070D1114, 0x16181A1C, 0x060D1113, 0x16181B1D, 0x0206090D, 0x10101010, 
    }},
    {set:{//05 Capture ISO100
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x03050709, 0x0B0D0F11, 0x03050709, 
        0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x0206090D, 0x10101010, 
    }},
    {set:{//06 Capture ISO200
        0x000000C4, 0x000011A0, 0x092328C8, 0x0000089C, 0x01030405, 0x06070809, 0x02030506, 
        0x06070808, 0x02030506, 0x06070808, 0x01030405, 0x06070809, 0x0206090D, 0x10101010, 
    }},
    {set:{//07 Capture ISO400
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x080A0C0E, 0x10121416, 0x080A0C0E, 
        0x10121416, 0x080A0C0E, 0x10121416, 0x080A0C0E, 0x10121416, 0x0206090D, 0x10101010, 
    }},
    {set:{//08 Capture ISO800
        0x000000C4, 0x000011A0, 0x092328C8, 0x000008AC, 0x080A0C0E, 0x10121416, 0x080A0C0E, 
        0x10121416, 0x080A0C0E, 0x10121416, 0x080A0C0E, 0x10121416, 0x0206090D, 0x10101010, 
    }},
    {set:{//09 Capture IS1600
        0x000000C4, 0x000011A0, 0x093028C8, 0x0000089C, 0x050D1115, 0x181C1F23, 0x070D1114, 
        0x16181A1C, 0x070D1114, 0x16181A1C, 0x060D1113, 0x16181B1D, 0x0206090D, 0x10101010, 
    }},
    {set:{//10 Disable (Do not modify me)
        0x000000C0, 0x000011A0, 0x094428A0, 0x000007AF, 0x03050709, 0x0B0D0F11, 0x03050709, 
        0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x03050709, 0x0B0D0F11, 0x0406090D, 0x10101010, 
    }}
        },
NR2:{
    {set:{//00 Preview ISO100
        0x00200002, 0x00111414, 0x00D27764, 0x0205070B, 0x0306090E, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B43, 0x0000056B, 0x01030507, 
    }},
    {set:{//01 Preview ISO200
        0x00200002, 0x00111414, 0x00D27764, 0x0205070B, 0x0306090E, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B43, 0x0000056B, 0x01030507, 
    }},
    {set:{//02 Preview ISO400
        0x00200003, 0x00111414, 0x00D27768, 0x060B1118, 0x1B33496B, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x04070B10, 
    }},
    {set:{//03 Preview ISO800
        0x00200003, 0x00111414, 0x00D27788, 0x060B1118, 0x3D73A7F3, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B88, 0x0000056B, 0x04070B10, 
    }},
    {set:{//04 Preview ISO1600
        0x00200003, 0x00119414, 0x00D27748, 0x14263750, 0xFFFFFFFF, 0x01907A8C, 0x08080808, 0x10101010, 0x01AF5B38, 0x0000056B, 0x0D192536, 
    }},
    {set:{//05 Capture Mode0 ISO100
        0x00200002, 0x00111414, 0x00D27764, 0x0205070B, 0x0306090E, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B43, 0x0000056B, 0x01030507, 
    }},
    {set:{//06 Capture Mode0 ISO200
        0x00200003, 0x00111414, 0x00D27748, 0x05090E14, 0x050A0F16, 0x020E728E, 0x08080808, 0x10101010, 0x01AF5B38, 0x0000056B, 0x0306090D, 
    }},
    {set:{//07 Capture Mode0 ISO400
        0x00200003, 0x00111414, 0x00D27768, 0x060B1118, 0x1B33496B, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x04070B10, 
    }},
    {set:{//08 Capture Mode0 ISO800
        0x00200003, 0x00111414, 0x00D27788, 0x060B1118, 0x3D73A7F3, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B88, 0x0000056B, 0x04070B10, 
    }},
    {set:{//09 Capture Mode0 ISO1600
        0x00200003, 0x00119414, 0x00D27748, 0x14263750, 0xFFFFFFFF, 0x01907A8C, 0x08080808, 0x10101010, 0x01AF5B38, 0x0000056B, 0x0D192536, 
    }},
    {set:{//10 Capture Mode1 ISO100
        0x00210002, 0x00111414, 0x00D27764, 0x0205070B, 0x0306090E, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B43, 0x0000056B, 0x01030507, 
    }},
    {set:{//11 Capture Mode1 ISO200
        0x00210002, 0x00111414, 0x00D27764, 0x0205070B, 0x0306090E, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B43, 0x0000056B, 0x01030507, 
    }},
    {set:{//12 Capture Mode1 ISO400
        0x00210003, 0x00111414, 0x00D27768, 0x060B1118, 0x1B33496B, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B48, 0x0000056B, 0x04070B10, 
    }},
    {set:{//13 Capture Mode1 ISO800
        0x00210003, 0x00111414, 0x00D27788, 0x060B1118, 0x3D73A7F3, 0x02105182, 0x08080808, 0x10101010, 0x01AF5B88, 0x0000056B, 0x04070B10, 
    }},
    {set:{//14 Capture Mode1 ISO1600
        0x00210003, 0x00119414, 0x00D27748, 0x0D192536, 0xFFFFFFFF, 0x0190728C, 0x08080808, 0x10101010, 0x01AF5B28, 0x0000056B, 0x09111924, 
    }},
    {set:{//15 Disable (Do not modify me)
        0x00000000, 0x0001FF01, 0x00523264, 0x04090B0F, 0x050A0B10, 0x02107294, 0x08101820, 0x10080604, 0x01AF5B43, 0x0000056B, 0x0306070A, 
    }}
},
EE:{// EE
    {set:{//00 Preview ISO100 (middle sharpness)
        0x00000000, 0x0037370D, 0x01F40B2D, 0x03FF1446, 0x03FF0073, 0x03FF00D7, 0xFFFF000D, 
    }},
    {set:{//01 Preview ISO200 (middle sharpness)
        0x00000008, 0x0037372D, 0x01F40B2D, 0x03FF1446, 0x03FF0073, 0x03FF00D7, 0xFFFFFA0D, 
    }},
    {set:{//02 Preview ISO400 (middle sharpness)
        0x00000028, 0x0037372D, 0x00000064, 0x012C078C, 0x02BC06C8, 0x03FF00FF, 0xFFFF000D, 
    }},
    {set:{//03 Preview ISO800 (middle sharpness)
        0x00000028, 0x0037372D, 0x000000B4, 0x000000C8, 0x02BC17E6, 0x038400F0, 0xFFFFFF0D, 
    }},
    {set:{//04 Preview ISO1600 (middle sharpness)
        0x00000028, 0x0037372C, 0x000000E6, 0x000000E6, 0x02BCBCE6, 0x038400F0, 0xFFFFFF0D, 
    }},
    {set:{//05 Capture ISO100 (middle sharpness)
        0x00000008, 0x0037372D, 0x01F40B2D, 0x03FF1446, 0x03FF0073, 0x03FF00D7, 0xFFFFFA0D, 
    }},
    {set:{//06 Capture ISO200 (middle sharpness)
        0x00000000, 0x0037370D, 0x01F40B2D, 0x03FF1446, 0x03FF0073, 0x03FF00D7, 0xFFFF000D, 
    }},
    {set:{//07 Capture ISO400 (middle sharpness)
        0x00000008, 0x0037372D, 0x00000064, 0x012C078C, 0x02BC06C8, 0x03FF00FF, 0xFFFF000D, 
    }},
    {set:{//08 Capture ISO800 (middle sharpness)
        0x00000028, 0x0037372D, 0x000000B4, 0x000000C8, 0x02BC17E6, 0x038400F0, 0xFFFFFF0D, 
    }},
    {set:{//09 Capture ISO1600 (middle sharpness)
        0x00000028, 0x0037372D, 0x00000000, 0x0000007B, 0x000000AD, 0x000000F3, 0xFFFFFF0D, 
    }},
    {set:{//10  no one uses this, this is Min EE (low sharpness)
        0x00000024, 0x0037372D, 0x00050023, 0x012C113C, 0x020001D0, 0x020000E7, 0xFFFF0005, 
    }},
    {set:{//11 no one uses this, this is Max EE (high sharpness)
        0x0000002C, 0x00373721, 0x000A0023, 0x03203937, 0x03FF01D0, 0x03FF00E7, 0xFFFF0005, 
    }}
            }, 
Saturation:{
    {set:{//00 (middle saturation)
        0x00010709, 0x1020E0F0, 0x28404040, 0x28000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//01 (middle saturation)
        0x00010709, 0x1020E0F0, 0x28404040, 0x28000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//02 (middle saturation)
        0x00010709, 0x1020E0F0, 0x1E3C3C3C, 0x1E000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//03 (middle saturation)
        0x00010709, 0x1020E0F0, 0x14303030, 0x14000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//04 (middle saturation)
        0x00010709, 0x1020E0F0, 0x0F282828, 0x0F000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//05 no one uses this, this is Min Sat. (low saturation)
        0x00000709, 0x1020E0F0, 0x34343434, 0x34000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
    }},
    {set:{//06 no one uses this, this is Max Sat. (high saturation)
        0x00000709, 0x1020E0F0, 0x4A4A4A4A, 0x4A000000, 0xFF00FF00, 0x001A2D40, 0x000A0A0A, 0x00643C1E, 
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
        0x022504F8, 0x042D0454, 0x0183042F, 0x040504A5, 0x01AA0000, 
    }},
    {set:{//01
        0x022504F8, 0x042D0454, 0x0183042F, 0x040504A5, 0x01AA0000, 
    }},
    {set:{//02
        0x01EB04B3, 0x04380429, 0x0184045B, 0x000604A5, 0x019F0000, 
    }}
},
Gamma:{
    {set:{//00
        0x42251309, 0x897C6C59, 0xBFB1A095, 0xE2DBD3CA, 0xFBF7F2ED, 
    }},
            }