/*
 *
 * Module Author : Yuvraj
 * Creation Date : 03/0318
 * You don't rights to change or remove this block of code from here!
 * If you use this make sure ti give proper credits!
 *
 */

#ifndef BUILD_LK
#include <linux/string.h>
#endif

#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
	#include <string.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
//	#include <mach/mt_gpio.h>
#endif

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH                                         (720)
#define FRAME_HEIGHT                                        (1280)
#define LCM_ID                       (0x1283)

#define REGFLAG_DELAY               (0XFE)
#define REGFLAG_END_OF_TABLE        (0xFFF) // END OF REGISTERS MARKER


#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)                                    (lcm_util.set_reset_pin((v)))

#define UDELAY(n)                                           (lcm_util.udelay(n))
#define MDELAY(n)                                           (lcm_util.mdelay(n))

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg											lcm_util.dsi_read_reg()
#define read_reg_v2(cmd, buffer, buffer_size)


 struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};


static struct LCM_setting_table lcm_initialization_setting[] = {
	{ 0xFF, 0x03, { 0x98, 0x51, 0x07 } },
	{ 0x03, 0x01, { 0x20 } },
	{ 0x04, 0x01, { 0x0C } },
	{ 0x05, 0x01, { 0x00 } },
	{ 0x06, 0x01, { 0x00 } },
	{ 0x07, 0x01, { 0x00 } },
	{ 0x08, 0x01, { 0x00 } },
	{ 0x09, 0x01, { 0x00 } },
	{ 0x0A, 0x01, { 0x01 } },
	{ 0x0B, 0x01, { 0x01 } },
	{ 0x0C, 0x01, { 0x01 } },
	{ 0x0D, 0x01, { 0x01 } },
	{ 0x0E, 0x01, { 0x01 } },
	{ 0x0F, 0x01, { 0x01 } },
	{ 0x10, 0x01, { 0x44 } },
	{ 0x11, 0x01, { 0x0A } },
	{ 0x12, 0x01, { 0x03 } },
	{ 0x13, 0x01, { 0x99 } },
	{ 0x14, 0x01, { 0x0A } },
	{ 0x15, 0x01, { 0x03 } },
	{ 0x16, 0x01, { 0x01 } },
	{ 0x17, 0x01, { 0x01 } },
	{ 0x18, 0x01, { 0x00 } },
	{ 0x19, 0x01, { 0x00 } },
	{ 0x1A, 0x01, { 0x00 } },
	{ 0x1B, 0x01, { 0xC0 } },
	{ 0x1C, 0x01, { 0xB8 } },
	{ 0x1D, 0x01, { 0x0B } },
	{ 0x1E, 0x01, { 0x01 } },
	{ 0x1F, 0x01, { 0x8C } },
	{ 0x20, 0x01, { 0x8C } },
	{ 0x21, 0x01, { 0x00 } },
	{ 0x22, 0x01, { 0x00 } },
	{ 0x23, 0x01, { 0xC0 } },
	{ 0x24, 0x01, { 0x30 } },
	{ 0x25, 0x01, { 0x00 } },
	{ 0x26, 0x01, { 0x00 } },
	{ 0x27, 0x01, { 0x23 } },
	{ 0x30, 0x01, { 0x01 } },
	{ 0x31, 0x01, { 0x23 } },
	{ 0x32, 0x01, { 0x45 } },
	{ 0x33, 0x01, { 0x67 } },
	{ 0x34, 0x01, { 0x89 } },
	{ 0x35, 0x01, { 0xAB } },
	{ 0x36, 0x01, { 0x01 } },
	{ 0x37, 0x01, { 0x23 } },
	{ 0x38, 0x01, { 0x45 } },
	{ 0x39, 0x01, { 0x67 } },
	{ 0x3A, 0x01, { 0x89 } },
	{ 0x3B, 0x01, { 0xAB } },
	{ 0x3C, 0x01, { 0xCD } },
	{ 0x3D, 0x01, { 0xEF } },
	{ 0x50, 0x01, { 0x11 } },
	{ 0x51, 0x01, { 0x0C } },
	{ 0x52, 0x01, { 0x0D } },
	{ 0x53, 0x01, { 0x0E } },
	{ 0x54, 0x01, { 0x0F } },
	{ 0x55, 0x01, { 0x06 } },
	{ 0x56, 0x01, { 0x07 } },
	{ 0x57, 0x01, { 0x02 } },
	{ 0x58, 0x01, { 0x02 } },
	{ 0x59, 0x01, { 0x02 } },
	{ 0x5A, 0x01, { 0x02 } },
	{ 0x5B, 0x01, { 0x02 } },
	{ 0x5C, 0x01, { 0x02 } },
	{ 0x5D, 0x01, { 0x02 } },
	{ 0x5E, 0x01, { 0x02 } },
	{ 0x5F, 0x01, { 0x02 } },
	{ 0x60, 0x01, { 0x02 } },
	{ 0x61, 0x01, { 0x02 } },
	{ 0x62, 0x01, { 0x02 } },
	{ 0x63, 0x01, { 0x02 } },
	{ 0x64, 0x01, { 0x02 } },
	{ 0x65, 0x01, { 0x01 } },
	{ 0x66, 0x01, { 0x00 } },
	{ 0x67, 0x01, { 0x0C } },
	{ 0x68, 0x01, { 0x0D } },
	{ 0x69, 0x01, { 0x0E } },
	{ 0x6A, 0x01, { 0x0F } },
	{ 0x6B, 0x01, { 0x06 } },
	{ 0x6C, 0x01, { 0x07 } },
	{ 0x6D, 0x01, { 0x02 } },
	{ 0x6E, 0x01, { 0x02 } },
	{ 0x6F, 0x01, { 0x02 } },
	{ 0x70, 0x01, { 0x02 } },
	{ 0x71, 0x01, { 0x02 } },
	{ 0x72, 0x01, { 0x02 } },
	{ 0x73, 0x01, { 0x02 } },
	{ 0x74, 0x01, { 0x02 } },
	{ 0x75, 0x01, { 0x02 } },
	{ 0x76, 0x01, { 0x02 } },
	{ 0x77, 0x01, { 0x02 } },
	{ 0x78, 0x01, { 0x02 } },
	{ 0x79, 0x01, { 0x02 } },
	{ 0x7A, 0x01, { 0x02 } },
	{ 0x7B, 0x01, { 0x01 } },
	{ 0x7C, 0x01, { 0x00 } },
	{ 0xFF, 0x03, { 0x98, 0x81, 0x08 } },
	{ 0x76, 0x01, { 0xA4 } },
	{ 0x78, 0x01, { 0x04 } },
	{ 0x74, 0x01, { 0x1A } },
	{ 0x8E, 0x01, { 0x20 } },
	{ 0x40, 0x01, { 0x01 } },
	{ 0x84, 0x01, { 0x81 } },
	{ 0x72, 0x01, { 0x25 } },
	{ 0xE3, 0x01, { 0x45 } },
	{ 0x7D, 0x01, { 0xCB } },
	{ 0x7E, 0x01, { 0x49 } },
	{ 0x49, 0x01, { 0x10 } },
	{ 0xFF, 0x03, { 0x98, 0x81, 0x01 } },
	{ 0x22, 0x01, { 0x0A } },
	{ 0x31, 0x01, { 0x00 } },
	{ 0x53, 0x01, { 0x53 } },
	{ 0x55, 0x01, { 0x58 } },
	{ 0x50, 0x01, { 0x95 } },
	{ 0x51, 0x01, { 0x95 } },
	{ 0xA0, 0x01, { 0x08 } },
	{ 0xA1, 0x01, { 0x11 } },
	{ 0xA2, 0x01, { 0x1B } },
	{ 0xA3, 0x01, { 0x0F } },
	{ 0xA4, 0x01, { 0x0C } },
	{ 0xA5, 0x01, { 0x1F } },
	{ 0xA6, 0x01, { 0x13 } },
	{ 0xA7, 0x01, { 0x18 } },
	{ 0xA8, 0x01, { 0x59 } },
	{ 0xA9, 0x01, { 0x1D } },
	{ 0xAA, 0x01, { 0x27 } },
	{ 0xAB, 0x01, { 0x4F } },
	{ 0xAC, 0x01, { 0x19 } },
	{ 0xAD, 0x01, { 0x18 } },
	{ 0xAE, 0x01, { 0x4A } },
	{ 0xAF, 0x01, { 0x23 } },
	{ 0xB0, 0x01, { 0x26 } },
	{ 0xB1, 0x01, { 0x4A } },
	{ 0xB2, 0x01, { 0x60 } },
	{ 0xB3, 0x01, { 0x39 } },
	{ 0xC0, 0x01, { 0x08 } },
	{ 0xC1, 0x01, { 0x10 } },
	{ 0xC2, 0x01, { 0x1C } },
	{ 0xC3, 0x01, { 0x0F } },
	{ 0xC4, 0x01, { 0x0C } },
	{ 0xC5, 0x01, { 0x20 } },
	{ 0xC6, 0x01, { 0x13 } },
	{ 0xC7, 0x01, { 0x18 } },
	{ 0xC8, 0x01, { 0x5A } },
	{ 0xC9, 0x01, { 0x1C } },
	{ 0xCA, 0x01, { 0x28 } },
	{ 0xCB, 0x01, { 0x4E } },
	{ 0xCC, 0x01, { 0x19 } },
	{ 0xCD, 0x01, { 0x17 } },
	{ 0xCE, 0x01, { 0x4A } },
	{ 0xCF, 0x01, { 0x24 } },
	{ 0xD0, 0x01, { 0x26 } },
	{ 0xD1, 0x01, { 0x4A } },
	{ 0xD2, 0x01, { 0x61 } },
	{ 0xD3, 0x01, { 0x39 } },
	{ 0xFF, 0x03, { 0x98, 0x81, 0x00 } },
	{ 0x35, 0x01, { 0x00 } },
	{ 0x36, 0x01, { 0x00 } },
	{ 0x11, 0x01, { 0x00 } },
	{ REGFLAG_DELAY, 0x78, { 0x00 } },
	{ 0x29, 0x01, { 0x00 } },
	{ REGFLAG_DELAY, 0x0A, { 0x00 } },
	{ REGFLAG_END_OF_TABLE, 0x00, { 0x00 } }
};

static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	{ 0xFF, 0x03, { 0x98, 0x81, 0x00 } },
	{ 0x28, 0x01, { 0x00 } },
	{ REGFLAG_DELAY, 0x32, { 0x00 } },
	{ 0x10, 0x01, { 0x00 } },
	{ REGFLAG_DELAY, 0x78, { 0x00 } },
	{ REGFLAG_END_OF_TABLE, 0x00, { 0x00 } }
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;

    for(i = 0; i < count; i++) {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd) {
			/*case 0xd9:
			table[i].para_list[0]=vcom;
			dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
            vcom+=2;
			break;
			*/
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
    params->type   = 2;
    params->width  = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;

    // enable tearing-free
    params->dbi.te_mode             = LCM_DBI_TE_MODE_VSYNC_ONLY;
    params->dbi.te_edge_polarity        = LCM_POLARITY_RISING;



    params->dsi.mode   = 1;


    // DSI
    /* Command mode setting */
    params->dsi.LANE_NUM                = LCM_FOUR_LANE;
    //The following defined the fomat for data coming from LCD engine. 
    params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
    params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST; 
    params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
    params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;
    // Highly depends on LCD driver capability.
    // Not support in MT6573
    params->dsi.packet_size=256;
    params->dsi.word_count=720*3;
    params->dsi.ssc_disable = 0;
    params->dsi.ssc_range = 8;
    // Video mode setting       
    params->dsi.intermediat_buffer_num = 2;
    params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
    params->dsi.vertical_sync_active                = 4;
    params->dsi.vertical_backporch                  = 16;
    params->dsi.vertical_frontporch                 = 20;
    params->dsi.vertical_active_line                = FRAME_HEIGHT; 
    params->dsi.horizontal_sync_active              = 10;
    params->dsi.horizontal_backporch                = 110;
    params->dsi.horizontal_frontporch               = 80;
    params->dsi.horizontal_blanking_pixel              = 60;
    params->dsi.horizontal_active_pixel            = FRAME_WIDTH;
    // Bit rate calculation
    params->dsi.PLL_CLOCK=221;
}

static void lcm_init(void)
{
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(20);
	SET_RESET_PIN(1);
	MDELAY(150);

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_resume(void)
{
	lcm_init();
}

static unsigned int lcm_compare_id(void)
{
       return 1;
}

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER ili9881_dsi_hd720_txd_zaw809_lcm_drv =
{
    .name           = "ili9881_dsi_hd720_txd_zaw809",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .compare_id    = lcm_compare_id,
};
	
