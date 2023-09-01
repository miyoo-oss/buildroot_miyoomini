#ifndef PNL_TABLE_K101_IM2BVL
#define PNL_TABLE_K101_IM2BVL

#include "/home/industio/ssd20x/project/release/include/mi_panel_datatype.h"

#define FLAG_DELAY            0xFE
#define FLAG_END_OF_TABLE     0xFF   // END OF REGISTERS MARKER

MhalPnlParamConfig_t stPanel_K101_IM2BVL =
{
    "K101_IM2BVL", // 
#if !defined (__aarch64__)
    0,
#endif
    0,             // m_bPanelDither
    E_MHAL_PNL_LINK_MIPI_DSI, // m_ePanelLinkType

    ///////////////////////////////////////////////
    // Board related setting
    ///////////////////////////////////////////////
    1,  //MS_U8 m_bPanelDualPort  :1;              ///<  VOP_21[8], MOD_4A[1],    PANEL_DUAL_PORT, refer to m_bPanelDoubleClk
    0,  //MS_U8 m_bPanelSwapPort  :1;              ///<  MOD_4A[0],               PANEL_SWAP_PORT, refer to "LVDS output app note" A/B channel swap
    0,  //MS_U8 m_bPanelSwapOdd_ML    :1;          ///<  PANEL_SWAP_ODD_ML
    0,  //MS_U8 m_bPanelSwapEven_ML   :1;          ///<  PANEL_SWAP_EVEN_ML
    0,  //MS_U8 m_bPanelSwapOdd_RB    :1;          ///<  PANEL_SWAP_ODD_RB
    0,  //MS_U8 m_bPanelSwapEven_RB   :1;          ///<  PANEL_SWAP_EVEN_RB

    0,  //MS_U8 m_bPanelSwapLVDS_POL  :1;          ///<  MOD_40[5], PANEL_SWAP_LVDS_POL, for differential P/N swap
    0,  //MS_U8 m_bPanelSwapLVDS_CH   :1;          ///<  MOD_40[6], PANEL_SWAP_LVDS_CH, for pair swap
    0,  //MS_U8 m_bPanelPDP10BIT      :1;          ///<  MOD_40[3], PANEL_PDP_10BIT ,for pair swap
    1, // m_bPanelLVDS_TI_MODE (Based on TI_MODE being 1 in miyoos panel)

    ///////////////////////////////////////////////
    // For TTL Only
    ///////////////////////////////////////////////
    0,  //MS_U8 m_ucPanelDCLKDelay;                ///<  PANEL_DCLK_DELAY
    0,  //MS_U8 m_bPanelInvDCLK   :1;              ///<  MOD_4A[4],                   PANEL_INV_DCLK
    0,  //MS_U8 m_bPanelInvDE     :1;              ///<  MOD_4A[2],                   PANEL_INV_DE
    1,  //MS_U8 m_bPanelInvHSync  :1;              ///<  MOD_4A[12],                  PANEL_INV_HSYNC
    1,  //MS_U8 m_bPanelInvVSync  :1;              ///<  MOD_4A[3],                   PANEL_INV_VSYNC

    ///////////////////////////////////////////////
    // Output driving current setting
    ///////////////////////////////////////////////
    // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
    1,  //MS_U8 m_ucPanelDCKLCurrent;              ///<  define PANEL_DCLK_CURRENT
    1,  //MS_U8 m_ucPanelDECurrent;                ///<  define PANEL_DE_CURRENT
    1,  //MS_U8 m_ucPanelODDDataCurrent;           ///<  define PANEL_ODD_DATA_CURRENT
    1,  //MS_U8 m_ucPanelEvenDataCurrent;          ///<  define PANEL_EVEN_DATA_CURRENT

    ///////////////////////////////////////////////
    // panel on/off timing
    ///////////////////////////////////////////////
    30,  //MS_U16 m_wPanelOnTiming1;                ///<  time between panel & data while turn on power
    400,  //MS_U16 m_wPanelOnTiming2;                ///<  time between data & back light while turn on power
    80,  //MS_U16 m_wPanelOffTiming1;               ///<  time between back light & data while turn off power
    30,  //MS_U16 m_wPanelOffTiming2;               ///<  time between data & panel while turn off power

    ///////////////////////////////////////////////
    // panel timing spec.
    ///////////////////////////////////////////////
    // sync related
    20,  //MS_U8 m_ucPanelHSyncWidth;               ///<  VOP_01[7:0], PANEL_HSYNC_WIDTH
    22,  //MS_U8 m_ucPanelHSyncBackPorch;           ///<  PANEL_HSYNC_BACK_PORCH, no register setting, provide value for query only

                                             ///<  not support Manuel VSync Start/End now
                                             ///<  VOP_02[10:0] VSync start = Vtt - VBackPorch - VSyncWidth
                                             ///<  VOP_03[10:0] VSync end = Vtt - VBackPorch
    5,  //MS_U8 m_ucPanelVSyncWidth;               ///<  define PANEL_VSYNC_WIDTH
    13,  //MS_U8 m_ucPanelVBackPorch;               ///<  define PANEL_VSYNC_BACK_PORCH

    // DE related
    40,  //MS_U16 m_wPanelHStart;                   ///<  VOP_04[11:0], PANEL_HSTART, DE H Start (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
    18,  //MS_U16 m_wPanelVStart;                   ///<  VOP_06[11:0], PANEL_VSTART, DE V Start
    640,  //MS_U16 m_wPanelWidth;                    ///< PANEL_WIDTH, DE width (VOP_05[11:0] = HEnd = HStart + Width - 1)
    480,  //MS_U16 m_wPanelHeight;                   ///< PANEL_HEIGHT, DE height (VOP_07[11:0], = Vend = VStart + Height - 1)

    // DClk related
    0,  //MS_U16 m_wPanelMaxHTotal;                ///<  PANEL_MAX_HTOTAL. Reserved for future using.
    780,  //MS_U16 m_wPanelHTotal;                   ///<  VOP_0C[11:0], PANEL_HTOTAL
    0,  //MS_U16 m_wPanelMinHTotal;                ///<  PANEL_MIN_HTOTAL. Reserved for future using.

    0,  //MS_U16 m_wPanelMaxVTotal;                ///<  PANEL_MAX_VTOTAL. Reserved for future using.
    515,  //MS_U16 m_wPanelVTotal;                   ///<  VOP_0D[11:0], PANEL_VTOTAL
    0,  //MS_U16 m_wPanelMinVTotal;                ///<  PANEL_MIN_VTOTAL. Reserved for future using.

    0,  //MS_U8 m_dwPanelMaxDCLK;                  ///<  PANEL_MAX_DCLK. Reserved for future using.
    23,  //MS_U8 m_dwPanelDCLK;                     ///<  LPLL_0F[23:0], PANEL_DCLK          ,{0x3100_10[7:0], 0x3100_0F[15:0]}
    0,  //MS_U8 m_dwPanelMinDCLK;                  ///<  PANEL_MIN_DCLK. Reserved for future using.
                                             ///<  spread spectrum
    0,  //MS_U16 m_wSpreadSpectrumStep;            ///<  move to board define, no use now.
    0,  //MS_U16 m_wSpreadSpectrumSpan;            ///<  move to board define, no use now.

    160,  //MS_U8 m_ucDimmingCtl;                    ///<  Initial Dimming Value
    255,  //MS_U8 m_ucMaxPWMVal;                     ///<  Max Dimming Value
    80,  //MS_U8 m_ucMinPWMVal;                     ///<  Min Dimming Value

    0,  //MS_U8 m_bPanelDeinterMode   :1;          ///<  define PANEL_DEINTER_MODE,  no use now
    E_MHAL_PNL_ASPECT_RATIO_WIDE,  //MHAL_DISP_PnlAspectRatio_e m_ucPanelAspectRatio; ///<  Panel Aspect Ratio, provide information to upper layer application for aspect ratio setting.
  /*
    *
    * Board related params
    *
    *  If a board ( like BD_MST064C_D01A_S ) swap LVDS TX polarity
    *    : This polarity swap value =
    *      (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L from board define,
    *  Otherwise
    *    : The value shall set to 0.
    */
    0,  //MS_U16 m_u16LVDSTxSwapValue;
    E_MHAL_PNL_TI_8BIT_MODE,  //MHAL_DISP_ApiPnlTiBitMode_e m_ucTiBitMode;                         ///< MOD_4B[1:0], refer to "LVDS output app note"
    E_MHAL_PNL_OUTPUT_8BIT_MODE,  //MHAL_DISP_ApiPnlOutPutFormatBitMode_e m_ucOutputFormatBitMode;

    0,  //MS_U8 m_bPanelSwapOdd_RG    :1;          ///<  define PANEL_SWAP_ODD_RG
    0,  //MS_U8 m_bPanelSwapEven_RG   :1;          ///<  define PANEL_SWAP_EVEN_RG
    0,  //MS_U8 m_bPanelSwapOdd_GB    :1;          ///<  define PANEL_SWAP_ODD_GB
    0,  //MS_U8 m_bPanelSwapEven_GB   :1;          ///<  define PANEL_SWAP_EVEN_GB

    /**
    *  Others
    */
    1,  //MS_U8 m_bPanelDoubleClk     :1;             ///<  LPLL_03[7], define Double Clock ,LVDS dual mode
    0x001c848e,  //MS_U8 m_dwPanelMaxSET;                     ///<  define PANEL_MAX_SET MARKER
    0x0018eb59,  //MS_U8 m_dwPanelMinSET;                     ///<  define PANEL_MIN_SET MARKER
    E_MHAL_PNL_CHG_VTOTAL,  //MHAL_DISP_ApiPnlOutTimingMode_e m_ucOutTimingMode;   ///<Define which panel output timing change mode is used to change VFreq for same panel
    0,  //MS_U8 m_bPanelNoiseDith     :1;             ///<  PAFRC mixed with noise dither disable
    (MhalPnlChannelSwapType_e)2,
    (MhalPnlChannelSwapType_e)4,
    (MhalPnlChannelSwapType_e)3,
    (MhalPnlChannelSwapType_e)1,
    (MhalPnlChannelSwapType_e)0,
/*
    (MhalPnlChannelSwapType_e)2,
    (MhalPnlChannelSwapType_e)4,
    (MhalPnlChannelSwapType_e)3,
    (MhalPnlChannelSwapType_e)1,
    (MhalPnlChannelSwapType_e)0,
*/
};

MI_U8 K101_IM2BVL[] =
{
    0x01,0x01,0x00,0xFE,0xFE,0x50,0xB9,0x03,0xF1,0x12,0x83,0xB1,0x05,0x00,0x00,0x00,
	0xDA,0x80,0xB2,0x03,0x00,0x13,0x70,0xB3,0x0A,0x10,0x10,0x28,0x28,0x03,0xFF,0x00,
	0x00,0x00,0x00,0xB4,0x01,0x82,0xB5,0x02,0x0A,0x0A,0xB6,0x02,0x8D,0x8D,0xB8,0x04,
	0x2A,0x62,0xF0,0x60,0xBA,0x1B,0x31,0x81,0x05,0xF9,0x0E,0x0E,0x20,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x44,0x25,0x00,0x90,0x0A,0x00,0x00,0x01,0x4F,0x01,0x00,0x00,
	0x37,0xBC,0x01,0x47,0xBF,0x03,0x02,0x11,0x00,0xC0,0x09,0x73,0x73,0x50,0x50,0x00,
	0x00,0x12,0x50,0x00,0xC1,0x0C,0x53,0x00,0x32,0x32,0x77,0xD1,0xCC,0xCC,0x77,0x77,
	0x33,0x33,0xC6,0x06,0x82,0x00,0xBF,0xFF,0x00,0xFF,0xC7,0x06,0xB8,0x00,0x0A,0x00,
	0x00,0x00,0xC8,0x04,0x10,0x40,0x1E,0x02,0xCC,0x01,0x0B,0x36,0x01,0xC0,0xE0,0x22,
	0x00,0x07,0x0D,0x37,0x35,0x3F,0x41,0x44,0x06,0x0C,0x0D,0x0F,0x11,0x10,0x12,0x14,
	0x1A,0x00,0x07,0x0D,0x37,0x35,0x3F,0x41,0x44,0x06,0x0C,0x0D,0x0F,0x11,0x10,0x12,
	0x14,0x1A,0xE3,0x0E,0x02,0x02,0x0B,0x0B,0x0B,0x0B,0x00,0x00,0x00,0x00,0xFF,0x00,
	0xC0,0x10,0xE9,0x3F,0xC8,0x10,0x02,0x00,0x00,0xB0,0xB1,0x11,0x31,0x23,0x28,0x80,
	0xB0,0xB1,0x27,0x08,0x00,0x04,0x02,0x00,0x00,0x00,0x00,0x04,0x02,0x00,0x00,0x00,
	0x88,0x88,0xBA,0x60,0x24,0x08,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0xBA,0x71,0x35,
	0x18,0x88,0x88,0x88,0x88,0x88,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xEA,0x3D,0x97,0x0A,0x82,0x02,0x03,0x07,0x00,0x00,0x00,0x00,0x00,
	0x00,0x81,0x88,0xBA,0x17,0x53,0x88,0x88,0x88,0x88,0x88,0x88,0x80,0x88,0xBA,0x06,
	0x42,0x88,0x88,0x88,0x88,0x88,0x88,0x23,0x00,0x00,0x02,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xEF,0x03,0xFF,0xFF,0x01,0x11,0x01,0x00,0xFE,0xFE,0x96,0x29,0x01,0x00,
	0xFE,0xFE,0x14,0xFF,0xFF
};

MhalPnlMipiDsiConfig_t stMipiDsiConfig_stPanel_K101_IM2BVL =
{
    // New values based on K101_IM2BVL
    // HsTrail   HsPrpr  HsZero  ClkHsPrpr  ClkHsExit  ClkTrail  ClkZero  ClkHsPost  DaHsExit  ContDet.
       3,         2,      5,       2,         4,         4,       10,       10,        4,       0,

    // New values based on K101_IM2BVL
    // Lpx   TaGet  TaSure  TaGo
       16,    26,     22,     50,

    //Hac,  Hpw,  Hbp, Hfp, Vac,  Vpw,  Vbp, Vfp,  Bllp, Fps
      640,  20,  22, 76, 480, 5,  13, 17,  0,    60,

    E_MHAL_PNL_MIPI_DSI_LANE_2,      // MIPnlMipiDsiLaneMode_e enLaneNum;
    E_MHAL_PNL_MIPI_DSI_RGB888,      // MIPnlMipiDsiFormat_e enFormat;
    E_MHAL_PNL_MIPI_DSI_SYNC_PULSE,  // MIPnlMipiDsiCtrlMode_e enCtrl;

    K101_IM2BVL,
    sizeof(K101_IM2BVL),
    1, 431, 441, 32914, 9, 0, 0, 0, 0, 0, E_MHAL_PNL_MIPI_DSI_PACKET_TYPE_DCS
};

#endif