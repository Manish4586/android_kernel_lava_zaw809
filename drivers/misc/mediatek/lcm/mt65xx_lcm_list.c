#include <lcm_drv.h>
#ifdef BUILD_LK
#include <platform/disp_drv_platform.h>
#else
#include <linux/delay.h>
#include <mach/mt_gpio.h>
#endif
#include <cust_gpio_usage.h>
//used to identify float ID PIN status
#define LCD_HW_ID_STATUS_LOW      0
#define LCD_HW_ID_STATUS_HIGH     1
#define LCD_HW_ID_STATUS_FLOAT 0x02
#define LCD_HW_ID_STATUS_ERROR  0x03

#ifdef BUILD_LK
#define LCD_DEBUG(fmt)  dprintf(CRITICAL,fmt)
#else
#define LCD_DEBUG(fmt)  printk(fmt)
#endif

extern LCM_DRIVER lp079x01_lcm_drv;
extern LCM_DRIVER ili9881_dsi_hd720_txd_zaw809_lcm_drv;
extern LCM_DRIVER hx8369_lcm_drv;
extern LCM_DRIVER hx8369_6575_lcm_drv;
extern LCM_DRIVER hx8363_6575_dsi_lcm_drv;
extern LCM_DRIVER hx8363_6575_dsi_hvga_lcm_drv;
extern LCM_DRIVER hx8363_6575_dsi_qvga_lcm_drv;
extern LCM_DRIVER hx8363b_wvga_dsi_cmd_drv;
extern LCM_DRIVER bm8578_lcm_drv;
extern LCM_DRIVER nt35582_mcu_lcm_drv;
extern LCM_DRIVER nt35582_mcu_6575_lcm_drv;
extern LCM_DRIVER nt35582_rgb_6575_lcm_drv;
extern LCM_DRIVER hx8357b_lcm_drv;
extern LCM_DRIVER hx8357c_hvga_dsi_cmd_drv;
extern LCM_DRIVER hx8369_dsi_lcm_drv;
extern LCM_DRIVER hx8369_dsi_6575_lcm_drv;
extern LCM_DRIVER hx8369_dsi_6575_hvga_lcm_drv;
extern LCM_DRIVER hx8369_dsi_6575_qvga_lcm_drv;
extern LCM_DRIVER hx8369_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8369b_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8369b_wvga_dsi_vdo_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_drv;
extern LCM_DRIVER hx8369_hvga_lcm_drv;
extern LCM_DRIVER ili9481_lcm_drv;
extern LCM_DRIVER nt35582_lcm_drv;
extern LCM_DRIVER s6d0170_lcm_drv;
extern LCM_DRIVER spfd5461a_lcm_drv;
extern LCM_DRIVER ta7601_lcm_drv;
extern LCM_DRIVER tft1p3037_lcm_drv;
extern LCM_DRIVER ha5266_lcm_drv;
extern LCM_DRIVER hsd070idw1_lcm_drv;
extern LCM_DRIVER lg4571_lcm_drv;
extern LCM_DRIVER lg4573b_wvga_dsi_vdo_lh430mv1_drv;
extern LCM_DRIVER lvds_wsvga_lcm_drv;
extern LCM_DRIVER lvds_wsvga_ti_lcm_drv;
extern LCM_DRIVER lvds_wsvga_ti_n_lcm_drv;
extern LCM_DRIVER nt35565_3d_lcm_drv;
extern LCM_DRIVER tm070ddh03_lcm_drv;
extern LCM_DRIVER r61408_lcm_drv;
extern LCM_DRIVER r61408_wvga_dsi_cmd_drv;
extern LCM_DRIVER nt35510_lcm_drv;
extern LCM_DRIVER nt35510_dpi_lcm_drv;
extern LCM_DRIVER nt35510_hvga_lcm_drv;
extern LCM_DRIVER nt35510_qvga_lcm_drv;
extern LCM_DRIVER nt35510_wvga_dsi_cmd_drv;
extern LCM_DRIVER nt35510_6517_lcm_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_hvga_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_fwvga_drv;
extern LCM_DRIVER nt35510_dsi_cmd_6572_qvga_drv;
extern LCM_DRIVER nt35510_dsi_vdo_6572_drv;
extern LCM_DRIVER nt35510_mcu_6572_lcm_drv;
extern LCM_DRIVER nt51012_hd720_dsi_vdo_lcm_drv;
extern LCM_DRIVER r63303_idisplay_lcm_drv;
extern LCM_DRIVER hj080ia_lcm_drv;
extern LCM_DRIVER hj101na02a_lcm_drv;
extern LCM_DRIVER hj101na02a_8135_lcm_drv;
extern LCM_DRIVER hsd070pfw3_lcm_drv;
extern LCM_DRIVER hsd070pfw3_8135_lcm_drv;
extern LCM_DRIVER cm_n070ice_dsi_vdo_lcm_drv;
extern LCM_DRIVER ej101ia_lcm_drv;
extern LCM_DRIVER scf0700m48ggu02_lcm_drv;
extern LCM_DRIVER nt35510_fwvga_lcm_drv;
#if defined(GN_SSD2825_SMD_S6E8AA)
extern LCM_DRIVER gn_ssd2825_smd_s6e8aa;
#endif
extern LCM_DRIVER nt35517_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8369_dsi_bld_lcm_drv;
extern LCM_DRIVER hx8369_dsi_tm_lcm_drv;
extern LCM_DRIVER otm1280a_hd720_dsi_cmd_drv;	 
extern LCM_DRIVER otm8018b_dsi_vdo_lcm_drv;	 
extern LCM_DRIVER nt35512_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35512_wvga_dsi_vdo_boe_drv;
extern LCM_DRIVER hx8369_rgb_6585_fpga_lcm_drv;
extern LCM_DRIVER hx8369_rgb_6572_fpga_lcm_drv;
extern LCM_DRIVER hx8369_mcu_6572_lcm_drv;
extern LCM_DRIVER hx8369a_wvga_dsi_cmd_drv;
extern LCM_DRIVER hx8369a_wvga_dsi_vdo_drv;
extern LCM_DRIVER hx8392a_dsi_cmd_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER ssd2075_hd720_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_fwvga_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_wvga_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_auo_qhd_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_cmi_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ipsboe_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ipsboe_wvga_lcm_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_ips9k1431_drv;
extern LCM_DRIVER nt35516_qhd_dsi_cmd_tft9k1342_drv;
extern LCM_DRIVER bp070ws1_lcm_drv;
extern LCM_DRIVER bp101wx1_lcm_drv;
extern LCM_DRIVER bp101wx1_n_lcm_drv;
extern LCM_DRIVER nt35516_qhd_rav4_lcm_drv;
extern LCM_DRIVER r63311_fhd_dsi_vdo_sharp_lcm_drv;
extern LCM_DRIVER r81592_hvga_dsi_cmd_drv;
extern LCM_DRIVER rm68190_dsi_vdo_lcm_drv;
extern LCM_DRIVER nt35596_fhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER nt35596_fhd_dsi_vdo_yassy_lcm_drv;
extern LCM_DRIVER nt35590_hd720_dsi_cmd_truly2_lcm_drv;
extern LCM_DRIVER otm9608_wvga_dsi_cmd_drv;
extern LCM_DRIVER nt35510_dbi_18bit_gionee_lcm_drv;
extern LCM_DRIVER otm8009a_fwvga_dsi_cmd_tianma_lcm_drv;
extern LCM_DRIVER otm8009a_fwvga_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER cm_otc3108bhv161_dsi_vdo_lcm_drv;
extern LCM_DRIVER auo_b079xat02_dsi_vdo_lcm_drv;
extern LCM_DRIVER hx8389b_qhd_dsi_vdo_tianma055xdhp_lcm_drv;
extern LCM_DRIVER cpt_claa101fp01_dsi_vdo_lcm_drv;
extern LCM_DRIVER h070d_18dm_lcm_drv;
extern LCM_DRIVER hx8394a_hd720_dsi_vdo_tianma_lcm_drv;
extern LCM_DRIVER cpt_clap070wp03xg_sn65dsi83_lcm_drv;
extern LCM_DRIVER nt35520_hd720_tm_lcm_drv;
extern LCM_DRIVER nt35520_hd720_boe_lcm_drv;
extern LCM_DRIVER nt35521_hd720_dsi_vdo_boe_lcm_drv;
extern LCM_DRIVER nt35521_hd720_tm_lcm_drv;
extern LCM_DRIVER r69429_wuxga_dsi_vdo_lcm_drv;
extern LCM_DRIVER r69429_wuxga_dsi_cmd_lcm_drv;
extern LCM_DRIVER rm68210_hd720_dsi_ufoe_cmd_lcm_drv;
extern LCM_DRIVER r63311_fhd_dsi_vedio_lcm_drv;
extern LCM_DRIVER ili9806c_dsi_vdo_djn_fwvga_oncell_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140227
extern LCM_DRIVER ili9806c_dsi_vdo_djn_fwvga_lcm_drv;		//++++rgk bug_id: none add by jiangwanwei 140228
//++++rgk bug-id:no add by yangjuwei 20140303 start
extern LCM_DRIVER ili9806c_dsi_vdo_by_fwvga_oncell_lcm_drv; 
extern LCM_DRIVER hx8379a_dsi_vdo_by_fwvga_lcm_drv;
extern LCM_DRIVER ili9806c_dsi_vdo_azet_fwvga_oncell_lcm_drv;
extern LCM_DRIVER otm9605a_dsi_vdo_djn_qhd_lcm_drv;  // yangjuwei add
extern LCM_DRIVER hx8394_dsi_vdo_txd_ips_hd_lcm_drv; //add by yangjuwei
extern LCM_DRIVER nt35521_dsi_auo_by_hd_lcm_drv; //add by yangjuwei
extern LCM_DRIVER ili9806e_dsi_vdo_djn_fwvga_lcm_drv;
extern LCM_DRIVER hx8389b_dsi_vdo_txd_qhd_lcm_drv; // zhoulidong add 
extern LCM_DRIVER otm1283a_dsi_vdo_hlt_hd_lcm_drv; //add by yangjuwei
extern LCM_DRIVER otm1283a_dsi_vdo_djn_hd_lcm_drv;//zhoulidong add 
extern LCM_DRIVER ili9806e_dsi_vdo_hlt_fwvga_oncell_lcm_drv;
//++++rgk bug-id:no add by yangjuwei 20140303 end
extern LCM_DRIVER otm9605a_dsi_vdo_hlt_qhd_ips_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140306
extern LCM_DRIVER otm9605a_dsi_vdo_djn_qhd_ips_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140306
extern LCM_DRIVER hx8394_dsi_vdo_truly_hd720_ips_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140307
extern LCM_DRIVER hx8394_dsi_vdo_truly_cmi_hd720_ips_lcm_drv;
extern LCM_DRIVER otm8018b_dsi_vdo_txd_fwvga_tn_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140317
extern LCM_DRIVER ili9806c_dsi_vdo_djn_fwvga_tn_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140317
extern LCM_DRIVER hx8379a_dsi_vdo_by_fwvga_ips_lcm_drv;
extern LCM_DRIVER otm1283a_dsi_vdo_trust_hd720_ips_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140401
extern LCM_DRIVER ili9806c_dsi_vdo_djn_fwvga_oncell_j511_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140221
extern LCM_DRIVER ili9806e_dsi_vdo_dijin_fwvga_ips_j511_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140318
extern LCM_DRIVER otm8019a_fwvga_dsi_vdo_trust_lcm_drv;
extern LCM_DRIVER r69429_wuxga_dsi_cmd_songxia_lcm_drv;//++++rgk bug_id:null add by yangjuwei 20140313

extern LCM_DRIVER ili9806e_dsi_vdo_hlt_fwvga_ips_j502_lcm_drv;//++++rgk anxiang.xiao add  20140324
extern LCM_DRIVER ili9806e_dsi_vdo_dijin_fwvga_ips_j502_lcm_drv;//++++rgk anxiang.xiao add  20140324
extern LCM_DRIVER hx8379a_dsi_vdo_azet_ips_lcm_drv;// add anxiang.xiao
extern LCM_DRIVER otm8018b_dsi_vdo_dijing_fwvga_boe_ips_lcm_drv;//+++rgk bug-id:null fix:add by sunyangmei 0140526
extern LCM_DRIVER ili9806c_dsi_vdo_txd_lcm_drv;	 	 // add anxiang.xiao 
extern LCM_DRIVER ili9806c_dsi_vdo_azet_ips_lcm_drv;   // add anxiang.xiao
extern LCM_DRIVER ili9806c_dsi_vdo_djn_lcm_drv;		// add anxiang.xiao
extern LCM_DRIVER ili9806c_dsi_vdo_txd_ips_lcm_drv;// add anxiang.xiao
extern LCM_DRIVER otm8018b_dsi_vdo_trust_lcm_drv;	// add anxiang.xiao
extern LCM_DRIVER hx8379a_dsi_vdo_azet_wvga_ips_lcm_drv;//++++rgk bug_id:null add by yangjuwei 20140508

extern LCM_DRIVER r63311_dsi_vdo_fhd_ips_lcm_drv;//++++rgk bug_id:null add by yangjuwei 20140528

extern LCM_DRIVER r63311_fhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER r63315_fhd_dsi_vdo_truly_lcm_drv;
extern LCM_DRIVER otm8019a_fwvga_dsi_vdo_trust_ips_oncell_lcm_drv;  //sym add in 20140609

extern LCM_DRIVER otm1283a_dsi_vdo_trust_hd720_cmi_ips_lcm_drv;//++++rgk bug-id:no add by yangjuwei 20140703
extern LCM_DRIVER nt35521_hd720_dsi_vdo_djn_boe_ips_oncell_lcm_drv;  //sym add in 20140704
extern LCM_DRIVER hx8394_dsi_vdo_djn_hd720_cpt_ips_oncell_lcm_drv;
extern LCM_DRIVER otm1283a_dsi_vdo_hlt_boe_hd720_ips_lcm_drv; //sym add in 20140721

extern LCM_DRIVER otm1283a_hd720_dsi_vdo_belij_lcm_drv;//add by wuhao 2014/7/24
extern LCM_DRIVER hx8379c_dsi_vdo_azet_wvga_ips_lcm_drv;//sym add in 20140725
extern LCM_DRIVER ili9806e_dsi_vdo_hlt_fwvga_ips_d5020_lcm_drv;
extern LCM_DRIVER hx8379c_dsi_vdo_trust_fwvga_ips_lcm_drv;
extern LCM_DRIVER hx8394d_dsi_vdo_djn_boe_hd720_ips_lcm_drv;

LCM_DRIVER* lcm_driver_list[] = 
{ 	
	#if defined(HX8394D_DSI_VDO_DJN_BOE_HD720_IPS)
	&hx8394d_dsi_vdo_djn_boe_hd720_ips_lcm_drv,
#endif	

	#if defined(HX8379C_DSI_VDO_AZET_WVGA_IPS)
	&hx8379c_dsi_vdo_azet_wvga_ips_lcm_drv,
#endif	
	#if defined(OTM1283A_DSI_VDO_HLT_BOE_HD720_IPS)
	&otm1283a_dsi_vdo_hlt_boe_hd720_ips_lcm_drv,
#endif	
	
//add by yangjuwei
#if defined(OTM1283A_DSI_VDO_HLT_HD)
	&otm1283a_dsi_vdo_hlt_hd_lcm_drv,
#endif

// anxiang.xiao add start
#if defined(HX8379A_DSI_VDO_AZET_IPS)
		&hx8379a_dsi_vdo_azet_ips_lcm_drv,
#endif
#if defined(ILI9806C_DSI_VDO_DJN)	
	&ili9806c_dsi_vdo_djn_lcm_drv, 
#endif
#if defined(ILI9806C_DSI_VDO_AZET_IPS)	
	&ili9806c_dsi_vdo_azet_ips_lcm_drv, 
#endif
#if defined(ILI9806C_DSI_VDO_TXD)	
	&ili9806c_dsi_vdo_txd_lcm_drv, 
#endif
#if defined(ILI9806C_DSI_VDO_TXD_IPS)
		&ili9806c_dsi_vdo_txd_ips_lcm_drv,
#endif
#if defined(OTM8018B_DSI_VDO_TRUST)	
	&otm8018b_dsi_vdo_trust_lcm_drv, 
#endif
//anxiang.xiao add end

#if defined(HX8379A_DSI_VDO_BY_FWVGA_IPS)
	&hx8379a_dsi_vdo_by_fwvga_ips_lcm_drv,
#endif
//++++rgk bug_id: none modify by jiangwanwei 140228 start++++
#if defined(ILI9806C_DSI_VDO_DJN_FWVGA)
	&ili9806c_dsi_vdo_djn_fwvga_lcm_drv,
#endif
//++++rgk bug_id: none add by jiangwanwei 140228 end++++

#if defined(R63311_FHD_DSI_VDO)
	&r63311_fhd_dsi_vedio_lcm_drv,
#endif
#if defined(NT35517_QHD_DSI_VDO)
	&nt35517_dsi_vdo_lcm_drv,
#endif


#if defined(LP079X01)
	&lp079x01_lcm_drv,
#endif

#if defined(HX8369)
	&hx8369_lcm_drv,
#endif

#if defined(HX8369_6575)
	&hx8369_6575_lcm_drv,
#endif

#if defined(BM8578)
	&bm8578_lcm_drv,
#endif

#if defined(NT35582_MCU)
	&nt35582_mcu_lcm_drv,
#endif

#if defined(NT35582_MCU_6575)
	&nt35582_mcu_6575_lcm_drv,
#endif

#if defined(NT35590_HD720_DSI_CMD_TRULY2)
	&nt35590_hd720_dsi_cmd_truly2_lcm_drv, 
#endif

#if defined(NT35590_HD720_DSI_VDO_TRULY)
	&nt35590_hd720_dsi_vdo_truly_lcm_drv, 
#endif

#if defined(SSD2075_HD720_DSI_VDO_TRULY)
	&ssd2075_hd720_dsi_vdo_truly_lcm_drv, 
#endif

#if defined(NT35590_HD720_DSI_CMD)
	&nt35590_hd720_dsi_cmd_drv,
#endif

#if defined(NT35590_HD720_DSI_CMD_AUO)
	&nt35590_hd720_dsi_cmd_auo_lcm_drv,
#endif

#if defined(NT35590_HD720_DSI_CMD_AUO_WVGA)
	&nt35590_hd720_dsi_cmd_auo_wvga_lcm_drv,
#endif

#if defined(NT35590_HD720_DSI_CMD_AUO_QHD)
	&nt35590_hd720_dsi_cmd_auo_qhd_lcm_drv,
#endif

#if defined(NT35590_HD720_DSI_CMD_AUO_FWVGA)
	&nt35590_hd720_dsi_cmd_auo_fwvga_lcm_drv,
#endif

#if defined(NT35590_HD720_DSI_CMD_CMI)
	&nt35590_hd720_dsi_cmd_cmi_lcm_drv,
#endif

#if defined(NT35582_RGB_6575)
	&nt35582_rgb_6575_lcm_drv,
#endif

#if  defined(NT51012_HD720_DSI_VDO) 
	&nt51012_hd720_dsi_vdo_lcm_drv,
#endif

#if defined(HX8369_RGB_6585_FPGA)
	&hx8369_rgb_6585_fpga_lcm_drv,
#endif

#if defined(HX8369_RGB_6572_FPGA)
	&hx8369_rgb_6572_fpga_lcm_drv,
#endif

#if defined(HX8369_MCU_6572)
	&hx8369_mcu_6572_lcm_drv,
#endif

#if defined(HX8369A_WVGA_DSI_CMD)
	&hx8369a_wvga_dsi_cmd_drv,
#endif

#if defined(HX8369A_WVGA_DSI_VDO)
	&hx8369a_wvga_dsi_vdo_drv,
#endif

#if defined(HX8357B)
	&hx8357b_lcm_drv,
#endif

#if defined(HX8357C_HVGA_DSI_CMD)
	&hx8357c_hvga_dsi_cmd_drv,
#endif

#if defined(R61408)
	&r61408_lcm_drv,
#endif

#if defined(R61408_WVGA_DSI_CMD)
	&r61408_wvga_dsi_cmd_drv,
#endif

#if defined(HX8369_DSI_VDO)
	&hx8369_dsi_vdo_lcm_drv,
#endif

#if defined(HX8369_DSI)
	&hx8369_dsi_lcm_drv,
#endif

#if defined(HX8369_6575_DSI)
	&hx8369_dsi_6575_lcm_drv,
#endif

#if defined(HX8369_6575_DSI_NFC_ZTE)
	&hx8369_dsi_6575_lcm_drv,
#endif

#if defined(HX8369_6575_DSI_HVGA)
	&hx8369_dsi_6575_hvga_lcm_drv,
#endif

#if defined(HX8369_6575_DSI_QVGA)
	&hx8369_dsi_6575_qvga_lcm_drv,
#endif

#if defined(HX8369_HVGA)
	&hx8369_hvga_lcm_drv,
#endif

#if defined(NT35510)
	&nt35510_lcm_drv,
#endif

#if defined(NT35510_RGB_6575) 
	&nt35510_dpi_lcm_drv,
#endif	

#if defined(NT35510_HVGA)
	&nt35510_hvga_lcm_drv,
#endif

#if defined(NT35510_QVGA)
	&nt35510_qvga_lcm_drv,
#endif

#if defined(NT35510_WVGA_DSI_CMD)
	&nt35510_wvga_dsi_cmd_drv,
#endif

#if defined(NT35510_6517)
	&nt35510_6517_lcm_drv,
#endif

#if defined(NT35510_DSI_CMD_6572)
	&nt35510_dsi_cmd_6572_drv,
#endif

#if defined(NT35510_DSI_CMD_6572_HVGA)
	&nt35510_dsi_cmd_6572_hvga_drv,
#endif

#if defined(NT35510_DSI_CMD_6572_FWVGA)
	&nt35510_dsi_cmd_6572_fwvga_drv,
#endif

#if defined(NT35510_DSI_CMD_6572_QVGA)
	&nt35510_dsi_cmd_6572_qvga_drv,
#endif

#if defined(NT35510_DSI_VDO_6572)
	&nt35510_dsi_vdo_6572_drv,
#endif

#if defined(NT35510_MCU_6572)
	&nt35510_mcu_6572_lcm_drv,
#endif

#if defined(ILI9481)
	&ili9481_lcm_drv,
#endif

#if defined(NT35582)
	&nt35582_lcm_drv,
#endif

#if defined(S6D0170)
	&s6d0170_lcm_drv,
#endif

#if defined(SPFD5461A)
	&spfd5461a_lcm_drv,
#endif

#if defined(TA7601)
	&ta7601_lcm_drv,
#endif

#if defined(TFT1P3037)
	&tft1p3037_lcm_drv,
#endif

#if defined(HA5266)
	&ha5266_lcm_drv,
#endif

#if defined(HSD070IDW1)
	&hsd070idw1_lcm_drv,
#endif

#if defined(HX8363_6575_DSI)
	&hx8363_6575_dsi_lcm_drv,
#endif

#if defined(HX8363_6575_DSI_HVGA)
	&hx8363_6575_dsi_hvga_lcm_drv,
#endif

#if defined(HX8363B_WVGA_DSI_CMD)
	&hx8363b_wvga_dsi_cmd_drv,
#endif

#if defined(LG4571)
	&lg4571_lcm_drv,
#endif

#if defined(LG4573B_WVGA_DSI_VDO_LH430MV1)
	&lg4573b_wvga_dsi_vdo_lh430mv1_drv,
#endif

#if defined(LVDS_WSVGA)
	&lvds_wsvga_lcm_drv,
#endif

#if defined(LVDS_WSVGA_TI)
	&lvds_wsvga_ti_lcm_drv,
#endif

#if defined(LVDS_WSVGA_TI_N)
	&lvds_wsvga_ti_n_lcm_drv,
#endif

#if defined(NT35565_3D)
	&nt35565_3d_lcm_drv,
#endif

#if defined(TM070DDH03)
	&tm070ddh03_lcm_drv,
#endif
#if defined(R63303_IDISPLAY)
	&r63303_idisplay_lcm_drv,
#endif

#if defined(HX8369B_DSI_VDO)
	&hx8369b_dsi_vdo_lcm_drv,
#endif

#if defined(HX8369B_WVGA_DSI_VDO)
	&hx8369b_wvga_dsi_vdo_drv,
#endif

#if defined(HX8369B_QHD_DSI_VDO)
	&hx8389b_qhd_dsi_vdo_drv,
#endif

#if defined(GN_SSD2825_SMD_S6E8AA)
	&gn_ssd2825_smd_s6e8aa,
#endif
#if defined(HX8369_TM_DSI)
	&hx8369_dsi_tm_lcm_drv,
#endif

#if defined(HX8369_BLD_DSI)
	&hx8369_dsi_bld_lcm_drv,
#endif

#if defined(HJ080IA)
	&hj080ia_lcm_drv,
#endif

#if defined(HJ101NA02A)
	&hj101na02a_lcm_drv,
#endif

#if defined(HJ101NA02A_8135)
	&hj101na02a_8135_lcm_drv,
#endif

#if defined(HSD070PFW3)
	&hsd070pfw3_lcm_drv,
#endif

#if defined(HSD070PFW3_8135)
	&hsd070pfw3_8135_lcm_drv,
#endif

#if defined(EJ101IA)
	&ej101ia_lcm_drv,
#endif

#if defined(SCF0700M48GGU02)
	&scf0700m48ggu02_lcm_drv,
#endif

#if defined(OTM1280A_HD720_DSI_CMD)	
	&otm1280a_hd720_dsi_cmd_drv, 
#endif

#if defined(OTM8018B_DSI_VDO)	
	&otm8018b_dsi_vdo_lcm_drv, 
#endif

#if defined(NT35512_DSI_VDO)
	&nt35512_dsi_vdo_lcm_drv, 
#endif

#if defined(NT35512_WVGA_DSI_VDO_BOE)
	&nt35512_wvga_dsi_vdo_boe_drv, 
#endif

#if defined(HX8392A_DSI_CMD)
  &hx8392a_dsi_cmd_lcm_drv,
#endif 

#if defined(NT35516_QHD_DSI_CMD_IPSBOE)
  &nt35516_qhd_dsi_cmd_ipsboe_lcm_drv,
#endif

#if defined(NT35516_QHD_DSI_CMD_IPSBOE_WVGA)
  &nt35516_qhd_dsi_cmd_ipsboe_wvga_lcm_drv,
#endif

#if defined(NT35516_QHD_DSI_CMD_IPS9K1431)
  &nt35516_qhd_dsi_cmd_ips9k1431_drv,
#endif

#if defined(NT35516_QHD_DSI_CMD_TFT9K1342)
  &nt35516_qhd_dsi_cmd_tft9k1342_drv,
#endif

#if defined(NT35516_QHD_DSI_VEDIO)
  &nt35516_qhd_rav4_lcm_drv,
#endif

#if defined(BP070WS1)
  &bp070ws1_lcm_drv,
#endif

#if defined(BP101WX1)
  &bp101wx1_lcm_drv,
#endif

#if defined(BP101WX1_N)
  &bp101wx1_n_lcm_drv,
#endif

#if defined(CM_N070ICE_DSI_VDO)
    &cm_n070ice_dsi_vdo_lcm_drv,
#endif

#if defined(CM_OTC3108BH161_DSI_VDO)
    &cm_otc3108bhv161_dsi_vdo_lcm_drv,
#endif
#if defined(NT35510_FWVGA)
  &nt35510_fwvga_lcm_drv,
#endif

#if defined(R63311_FHD_DSI_VDO_SHARP)
	&r63311_fhd_dsi_vdo_sharp_lcm_drv,
#endif

#if defined(R81592_HVGA_DSI_CMD)
	&r81592_hvga_dsi_cmd_drv,
#endif

#if defined(RM68190_QHD_DSI_VDO)
	&rm68190_dsi_vdo_lcm_drv,
#endif

#if defined(NT35596_FHD_DSI_VDO_TRULY)
	&nt35596_fhd_dsi_vdo_truly_lcm_drv,
#endif

#if defined(NT35596_FHD_DSI_VDO_YASSY)
	&nt35596_fhd_dsi_vdo_yassy_lcm_drv,
#endif

#if defined(AUO_B079XAT02_DSI_VDO)
    &auo_b079xat02_dsi_vdo_lcm_drv,
#endif
#if defined(OTM9608_WVGA_DSI_CMD)
	&otm9608_wvga_dsi_cmd_drv,
#endif

#if defined(NT35510_DBI_18BIT_GIONEE)
	&nt35510_dbi_18bit_gionee_lcm_drv,
#endif

#if defined(OTM8009A_FWVGA_DSI_CMD_TIANMA)
	&otm8009a_fwvga_dsi_cmd_tianma_lcm_drv,
#endif

#if defined(OTM8009A_FWVGA_DSI_VDO_TIANMA)
	&otm8009a_fwvga_dsi_vdo_tianma_lcm_drv,
#endif

#if defined(HX8389B_QHD_DSI_VDO_TIANMA)
	&hx8389b_qhd_dsi_vdo_tianma_lcm_drv,
#endif
#if defined(HX8389B_QHD_DSI_VDO_TIANMA055XDHP)
		&hx8389b_qhd_dsi_vdo_tianma055xdhp_lcm_drv,
#endif

#if defined(CPT_CLAA101FP01_DSI_VDO)
    &cpt_claa101fp01_dsi_vdo_lcm_drv,
#endif

#if defined(CPT_CLAP070WP03XG_SN65DSI83)
	&cpt_clap070wp03xg_sn65dsi83_lcm_drv,
#endif
#if defined(NT35520_HD720_DSI_CMD_TM)
  &nt35520_hd720_tm_lcm_drv,
#endif
#if defined(NT35520_HD720_DSI_CMD_BOE)
  &nt35520_hd720_boe_lcm_drv,
#endif

//juwei yang add
#if defined(OTM9605A_DSI_VDO_DJN_QHD)
		&otm9605a_dsi_vdo_djn_qhd_lcm_drv,
#endif

#if defined(NT35521_HD720_DSI_VDO_BOE)
  &nt35521_hd720_dsi_vdo_boe_lcm_drv,
#endif

//juwei yang add
#if defined(HX8394_DSI_VDO_TXD_IPS_HD)
		&hx8394_dsi_vdo_txd_ips_hd_lcm_drv,
#endif

#if defined(NT35521_HD720_DSI_VIDEO_TM)
  &nt35521_hd720_tm_lcm_drv,
#endif

//add by yangjuwei
#if defined(NT35521_DSI_AUO_BY_HD)
		&nt35521_dsi_auo_by_hd_lcm_drv,
#endif
#if defined(H070D_18DM)
    &h070d_18dm_lcm_drv,
#endif
#if defined(R69429_WUXGA_DSI_VDO)
    &r69429_wuxga_dsi_vdo_lcm_drv,
#endif


#if defined(HX8394A_HD720_DSI_VDO_TIANMA)
	&hx8394a_hd720_dsi_vdo_tianma_lcm_drv,
#endif

#if defined(HX8389B_DSI_VDO_TXD_QHD)
		&hx8389b_dsi_vdo_txd_qhd_lcm_drv,
#endif

#if defined(R69429_WUXGA_DSI_CMD)
	&r69429_wuxga_dsi_cmd_lcm_drv,
#endif



#if defined(RM68210_HD720_DSI_UFOE_CMD)
  &rm68210_hd720_dsi_ufoe_cmd_lcm_drv,
#endif

#if defined(OTM1283A_DSI_VDO_DJN_HD)
		&otm1283a_dsi_vdo_djn_hd_lcm_drv,
#endif

//++++rgk bug-id:no add by yangjuwei 20140227 start
#if defined(ILI9806C_DSI_VDO_DJN_FWVGA_ONCELL)
	&ili9806c_dsi_vdo_djn_fwvga_oncell_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140227 end


//++++rgk bug-id:no add by yangjuwei 20140303 start
#if defined(ILI9806C_DSI_VDO_BY_FWVGA_ONCELL)
	&ili9806c_dsi_vdo_by_fwvga_oncell_lcm_drv,
#endif 
#if defined(HX8379A_DSI_VDO_BY_FWVGA)
	&hx8379a_dsi_vdo_by_fwvga_lcm_drv,
#endif
#if defined(ILI9806C_DSI_VDO_AZET_FWVGA_ONCELL)
	&ili9806c_dsi_vdo_azet_fwvga_oncell_lcm_drv,
#endif
#if defined(ILI9806E_DSI_VDO_DJN_FWVGA)
	&ili9806e_dsi_vdo_djn_fwvga_lcm_drv,
#endif
#if defined(ILI9806E_DSI_VDO_HLT_FWVGA_ONCELL)
	&ili9806e_dsi_vdo_hlt_fwvga_oncell_lcm_drv,
#endif

//++++rgk bug-id:no add by yangjuwei 20140303 end

//manish.n.manish45@gmail.com add at 20151108 begin	
#if defined(ILI9881_DSI_HD720_TXD_ZAW809)
	&ili9881_dsi_hd720_txd_zaw809_lcm_drv,
#endif
//manish.n.manish45@gmail.com add at 20151108 end	
	
//+#endif++rgk bug-id:no add by yangjuwei 20140306 start
#if defined(OTM9605A_DSI_VDO_HLT_QHD_IPS)
	&otm9605a_dsi_vdo_hlt_qhd_ips_lcm_drv,
#endif

#if defined(OTM9605A_DSI_VDO_DJN_QHD_IPS)
	&otm9605a_dsi_vdo_djn_qhd_ips_lcm_drv,
#endif

//++++rgk bug-id:no add by yangjuwei 20140306 end

//++++rgk bug-id:no add by yangjuwei 20140307 start
#if defined(HX8394_DSI_VDO_TRULY_HD720_IPS)
	&hx8394_dsi_vdo_truly_hd720_ips_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140307 end

#if defined(HX8394_DSI_VDO_TRULY_CMI_HD720_IPS)
	&hx8394_dsi_vdo_truly_cmi_hd720_ips_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140317 start
#if defined(OTM8018B_DSI_VDO_TXD_FWVGA_TN)
	&otm8018b_dsi_vdo_txd_fwvga_tn_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140317 end

//++++rgk bug-id:no add by yangjuwei 20140317 start
#if defined(ILI9806C_DSI_VDO_DJN_FWVGA_TN)
	&ili9806c_dsi_vdo_djn_fwvga_tn_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140317 end

//++++rgk bug-id:no add by yangjuwei 20140401 start
#if defined(OTM1283A_DSI_VDO_TRUST_HD720_IPS)
	&otm1283a_dsi_vdo_trust_hd720_ips_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140401 end

//++++rgk bug-id:no add by yangjuwei 20140221 start
#if defined(ILI9806C_DSI_VDO_DJN_FWVGA_ONCELL_J511)
		&ili9806c_dsi_vdo_djn_fwvga_oncell_j511_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140221 end

//++++rgk bug-id:no add by yangjuwei 20140318 start
#if defined(ILI9806E_DSI_VDO_DIJIN_FWVGA_IPS_J511)
	&ili9806e_dsi_vdo_dijin_fwvga_ips_j511_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140318 end

#if defined(OTM8019A_FWVGA_DSI_VDO_TRUST)
	&otm8019a_fwvga_dsi_vdo_trust_lcm_drv,
#endif
//++++rgk bug_id:null add by yangjuwei 20140313 start
#if defined(R69429_WUXGA_DSI_CMD_SONGXIA)
	&r69429_wuxga_dsi_cmd_songxia_lcm_drv,
#endif
//++++rgk bug_id:null add by yangjuwei 20140313 end

//++++rgk bug_id:null add by yangjuwei 20140508 start
#if defined(HX8379A_DSI_VDO_AZET_WVGA_IPS)
	&hx8379a_dsi_vdo_azet_wvga_ips_lcm_drv,
#endif
//++++rgk bug_id:null add by yangjuwei 20140508 end


//++++rgk bug_id:null add by yangjuwei 20140528 start
#if defined(R63311_DSI_VDO_FHD_IPS)
	&r63311_dsi_vdo_fhd_ips_lcm_drv,
#endif
//++++rgk bug_id:null add by yangjuwei 20140528 end



#if defined(R63311_FHD_DSI_VDO_TRULY)
	&r63311_fhd_dsi_vdo_truly_lcm_drv,
#endif
#if defined(R63315_FHD_DSI_VDO_TRULY)
	&r63315_fhd_dsi_vdo_truly_lcm_drv,
#endif
#if defined(ILI9806E_DSI_VDO_HLT_FWVGA_IPS_J502)
	&ili9806e_dsi_vdo_hlt_fwvga_ips_j502_lcm_drv, 
#endif

#if defined(ILI9806E_DSI_VDO_DIJIN_FWVGA_IPS_J502)
	&ili9806e_dsi_vdo_dijin_fwvga_ips_j502_lcm_drv, 
#endif

//add otm8018 dijing fwvga lcd by sym in 20140526 start
#if defined(OTM8018B_DSI_VDO_DIJING_FWVGA_BOE_IPS)
	&otm8018b_dsi_vdo_dijing_fwvga_boe_ips_lcm_drv,
#endif
#if defined(OTM8019A_FWVGA_DSI_VDO_TRUST_IPS_ONCELL)
	&otm8019a_fwvga_dsi_vdo_trust_ips_oncell_lcm_drv,
#endif

//++++rgk bug-id:no add by yangjuwei 20140703 start
#if defined(OTM1283A_DSI_VDO_TRUST_HD720_CMI_IPS)
	&otm1283a_dsi_vdo_trust_hd720_cmi_ips_lcm_drv,
#endif
 //sym add in 20140704
#if defined(NT35521_HD720_DSI_VDO_DJN_BOE_IPS_ONCELL)
	&nt35521_hd720_dsi_vdo_djn_boe_ips_oncell_lcm_drv,
#endif
//++++rgk bug-id:no add by yangjuwei 20140703 end

#if defined(HX8394_DSI_VDO_DJN_HD720_CPT_IPS_ONCELL)
	&hx8394_dsi_vdo_djn_hd720_cpt_ips_oncell_lcm_drv,
#endif

#if defined(OTM1283A_HD720_DSI_VDO_BELIJ)
	&otm1283a_hd720_dsi_vdo_belij_lcm_drv,
#endif
#if defined(ILI9806E_DSI_VDO_HLT_FWVGA_IPS_D5020)
	&ili9806e_dsi_vdo_hlt_fwvga_ips_d5020_lcm_drv,
#endif
#if(HX8379C_DSI_VDO_TRUST_FWVGA_IPS)
	&hx8379c_dsi_vdo_trust_fwvga_ips_lcm_drv,
#endif

};



#define LCM_COMPILE_ASSERT(condition) LCM_COMPILE_ASSERT_X(condition, __LINE__)
#define LCM_COMPILE_ASSERT_X(condition, line) LCM_COMPILE_ASSERT_XX(condition, line)
#define LCM_COMPILE_ASSERT_XX(condition, line) char assertion_failed_at_line_##line[(condition)?1:-1]

unsigned int lcm_count = sizeof(lcm_driver_list)/sizeof(LCM_DRIVER*);
LCM_COMPILE_ASSERT(0 != sizeof(lcm_driver_list)/sizeof(LCM_DRIVER*));
#if defined(NT35520_HD720_DSI_CMD_TM) | defined(NT35520_HD720_DSI_CMD_BOE) | defined(NT35521_HD720_DSI_VDO_BOE) | defined(NT35521_HD720_DSI_VIDEO_TM)
#ifdef BUILD_LK
extern void mdelay(unsigned long msec);
#endif
static unsigned char lcd_id_pins_value = 0xFF;


/******************************************************************************
Function:       which_lcd_module_triple
  Description:    read LCD ID PIN status,could identify three status:high¡¢low¡¢float
  Input:           none
  Output:         none
  Return:         LCD ID1|ID0 value
  Others:         
******************************************************************************/
unsigned char which_lcd_module_triple(void)
{
    unsigned char  high_read0 = 0;
    unsigned char  low_read0 = 0;
    unsigned char  high_read1 = 0;
    unsigned char  low_read1 = 0;
    unsigned char  lcd_id0 = 0;
    unsigned char  lcd_id1 = 0;
    unsigned char  lcd_id = 0;
    //Solve Coverity scan warning : check return value
    unsigned int ret = 0;
    //only recognise once
    if(0xFF != lcd_id_pins_value) 
    {
        return lcd_id_pins_value;
    }
    //Solve Coverity scan warning : check return value
    ret = mt_set_gpio_mode(GPIO_DISP_ID0_PIN, GPIO_MODE_00);
    if(0 != ret)
    {
        LCD_DEBUG("ID0 mt_set_gpio_mode fail\n");
    }
    ret = mt_set_gpio_dir(GPIO_DISP_ID0_PIN, GPIO_DIR_IN);
    if(0 != ret)
    {
        LCD_DEBUG("ID0 mt_set_gpio_dir fail\n");
    }
    ret = mt_set_gpio_pull_enable(GPIO_DISP_ID0_PIN, GPIO_PULL_ENABLE);
    if(0 != ret)
    {
        LCD_DEBUG("ID0 mt_set_gpio_pull_enable fail\n");
    }
    ret = mt_set_gpio_mode(GPIO_DISP_ID1_PIN, GPIO_MODE_00);
    if(0 != ret)
    {
        LCD_DEBUG("ID1 mt_set_gpio_mode fail\n");
    }
    ret = mt_set_gpio_dir(GPIO_DISP_ID1_PIN, GPIO_DIR_IN);
    if(0 != ret)
    {
        LCD_DEBUG("ID1 mt_set_gpio_dir fail\n");
    }
    ret = mt_set_gpio_pull_enable(GPIO_DISP_ID1_PIN, GPIO_PULL_ENABLE);
    if(0 != ret)
    {
        LCD_DEBUG("ID1 mt_set_gpio_pull_enable fail\n");
    }
    //pull down ID0 ID1 PIN    
    ret = mt_set_gpio_pull_select(GPIO_DISP_ID0_PIN,GPIO_PULL_DOWN);
    if(0 != ret)
    {
        LCD_DEBUG("ID0 mt_set_gpio_pull_select->Down fail\n");
    }
    ret = mt_set_gpio_pull_select(GPIO_DISP_ID1_PIN,GPIO_PULL_DOWN);
    if(0 != ret)
    {
        LCD_DEBUG("ID1 mt_set_gpio_pull_select->Down fail\n");
    }
    //delay 100ms , for discharging capacitance 
    mdelay(100);
    //get ID0 ID1 status
    low_read0 = mt_get_gpio_in(GPIO_DISP_ID0_PIN);
    low_read1 = mt_get_gpio_in(GPIO_DISP_ID1_PIN);
    //pull up ID0 ID1 PIN 
    ret = mt_set_gpio_pull_select(GPIO_DISP_ID0_PIN,GPIO_PULL_UP);
    if(0 != ret)
    {
        LCD_DEBUG("ID0 mt_set_gpio_pull_select->UP fail\n");
    }
    ret = mt_set_gpio_pull_select(GPIO_DISP_ID1_PIN,GPIO_PULL_UP);
    if(0 != ret)
    {
        LCD_DEBUG("ID1 mt_set_gpio_pull_select->UP fail\n");
    }
    //delay 100ms , for charging capacitance 
    mdelay(100);
    //get ID0 ID1 status
    high_read0 = mt_get_gpio_in(GPIO_DISP_ID0_PIN);
    high_read1 = mt_get_gpio_in(GPIO_DISP_ID1_PIN);

    if( low_read0 != high_read0 )
    {
        /*float status , pull down ID0 ,to prevent electric leakage*/
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID0_PIN,GPIO_PULL_DOWN);
        if(0 != ret)
        {
            LCD_DEBUG("ID0 mt_set_gpio_pull_select->Down fail\n");
        }
        lcd_id0 = LCD_HW_ID_STATUS_FLOAT;
    }
    else if((LCD_HW_ID_STATUS_LOW == low_read0) && (LCD_HW_ID_STATUS_LOW == high_read0))
    {
        /*low status , pull down ID0 ,to prevent electric leakage*/
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID0_PIN,GPIO_PULL_DOWN);
        if(0 != ret)
        {
            LCD_DEBUG("ID0 mt_set_gpio_pull_select->Down fail\n");
        }
        lcd_id0 = LCD_HW_ID_STATUS_LOW;
    }
    else if((LCD_HW_ID_STATUS_HIGH == low_read0) && (LCD_HW_ID_STATUS_HIGH == high_read0))
    {
        /*high status , pull up ID0 ,to prevent electric leakage*/
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID0_PIN,GPIO_PULL_UP);
        if(0 != ret)
        {
            LCD_DEBUG("ID0 mt_set_gpio_pull_select->UP fail\n");
        }
        lcd_id0 = LCD_HW_ID_STATUS_HIGH;
    }
    else
    {
        LCD_DEBUG(" Read LCD_id0 error\n");
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID0_PIN,GPIO_PULL_DISABLE);
        if(0 != ret)
        {
            LCD_DEBUG("ID0 mt_set_gpio_pull_select->Disbale fail\n");
        }
        lcd_id0 = LCD_HW_ID_STATUS_ERROR;
    }


    if( low_read1 != high_read1 )
    {
        /*float status , pull down ID1 ,to prevent electric leakage*/
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID1_PIN,GPIO_PULL_DOWN);
        if(0 != ret)
        {
            LCD_DEBUG("ID1 mt_set_gpio_pull_select->Down fail\n");
        }
        lcd_id1 = LCD_HW_ID_STATUS_FLOAT;
    }
    else if((LCD_HW_ID_STATUS_LOW == low_read1) && (LCD_HW_ID_STATUS_LOW == high_read1))
    {
        /*low status , pull down ID1 ,to prevent electric leakage*/
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID1_PIN,GPIO_PULL_DOWN);
        if(0 != ret)
        {
            LCD_DEBUG("ID1 mt_set_gpio_pull_select->Down fail\n");
        }
        lcd_id1 = LCD_HW_ID_STATUS_LOW;
    }
    else if((LCD_HW_ID_STATUS_HIGH == low_read1) && (LCD_HW_ID_STATUS_HIGH == high_read1))
    {
        /*high status , pull up ID1 ,to prevent electric leakage*/
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID1_PIN,GPIO_PULL_UP);
        if(0 != ret)
        {
            LCD_DEBUG("ID1 mt_set_gpio_pull_select->UP fail\n");
        }
        lcd_id1 = LCD_HW_ID_STATUS_HIGH;
    }
    else
    {

        LCD_DEBUG(" Read LCD_id1 error\n");
        ret = mt_set_gpio_pull_select(GPIO_DISP_ID1_PIN,GPIO_PULL_DISABLE);
        if(0 != ret)
        {
            LCD_DEBUG("ID1 mt_set_gpio_pull_select->Disable fail\n");
        }
        lcd_id1 = LCD_HW_ID_STATUS_ERROR;
    }
#ifdef BUILD_LK
    dprintf(CRITICAL,"which_lcd_module_triple,lcd_id0:%d\n",lcd_id0);
    dprintf(CRITICAL,"which_lcd_module_triple,lcd_id1:%d\n",lcd_id1);
#else
    printk("which_lcd_module_triple,lcd_id0:%d\n",lcd_id0);
    printk("which_lcd_module_triple,lcd_id1:%d\n",lcd_id1);
#endif
    lcd_id =  lcd_id0 | (lcd_id1 << 2);

#ifdef BUILD_LK
    dprintf(CRITICAL,"which_lcd_module_triple,lcd_id:%d\n",lcd_id);
#else
    printk("which_lcd_module_triple,lcd_id:%d\n",lcd_id);
#endif

    lcd_id_pins_value = lcd_id;
    return lcd_id;
}
#endif
