/********************************************************************************************************
 * @file    charger.h
 *
 * @brief   This is the header file for B91
 *
 * @author  Driver Group
 * @date    2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
/**	@page CHARGER
 *
 *	Introduction
 *	===============
 * Note the following in auto mode:
 * 1. under auto mode, the reference voltage of the charger inside the chip is 1.2v, which is generated by BG in the vbus voltage domain,
 *    since 1.2V is inherently inaccurate, the 4.2V threshold may be inaccurate (detection of 4.2V requires CC --> CV), such deviations are unavoidable in the absence of calibration.
 * 2. in auto mode, CV current gear traversal lasts relatively fast. when the battery internal resistance is large, a large pressure difference may be generated,
 *    resulting in a large difference between the actual battery voltage and the vbat voltage. as a result, the battery is not fully charged.
 * 3. the base voltage of each board may be different, a battery may be charged by different chips, a battery may be overloaded in another chip, and err (auto mode) will appear.
 *
 * Note the following in manual mode:
 * 1.some hardware protection mechanisms are missing (vbus/vbat/current protection mechanism),in manual mode,all operations are controlled by the software and are not affected;
 * 2.under normal circumstances, first convert to the high current charge, and then use the low current, otherwise the charging process will be slow;
 * 3.if do not turn off manual_shut_down, switch mode first and then current to avoid sudden change from low current to high current;
 *
 *	API Reference
 *	===============
 *	Header File: charger.h
 */

#ifndef CHARGER_H_
#define CHARGER_H_
#include "reg_include/soc.h"
#include "reg_include/charger_reg.h"


typedef enum{
	CHARGER_CC_CURRENT_23p01mA  =0x00,
	CHARGER_CC_CURRENT_28p02mA  =0x01,
	CHARGER_CC_CURRENT_32p89mA  =0x02,
	CHARGER_CC_CURRENT_37p69mA  =0x03,
	CHARGER_CC_CURRENT_42p04mA  =0x04,
	CHARGER_CC_CURRENT_47p04mA  =0x05,
	CHARGER_CC_CURRENT_52p03mA  =0x06,
	CHARGER_CC_CURRENT_57p02mA  =0x07,
	CHARGER_CC_CURRENT_62p00mA  =0x08,
	CHARGER_CC_CURRENT_66p09mA  =0x09,
	CHARGER_CC_CURRENT_72p00mA  =0x0a,
	CHARGER_CC_CURRENT_76p70mA  =0x0b,
	CHARGER_CC_CURRENT_81p05mA  =0x0c,
	CHARGER_CC_CURRENT_86p06mA  =0x0d,
	CHARGER_CC_CURRENT_91p07mA  =0x0e,
	CHARGER_CC_CURRENT_96p03mA  =0x0f,
}charger_cc_current_e;


typedef enum{
	CHARGER_TC_CURRENT_1p57mA  =0x00,
	CHARGER_TC_CURRENT_2p06mA  =0x01,
	CHARGER_TC_CURRENT_2p46mA  =0x02,
	CHARGER_TC_CURRENT_2p93mA  =0x03,
	CHARGER_TC_CURRENT_3p41mA  =0x04,
	CHARGER_TC_CURRENT_3p88mA  =0x05,
	CHARGER_TC_CURRENT_4p36mA  =0x06,
	CHARGER_TC_CURRENT_4p84mA  =0x07,
	CHARGER_TC_CURRENT_5p32mA  =0x08,
	CHARGER_TC_CURRENT_5p80mA  =0x09,
	CHARGER_TC_CURRENT_6p27mA  =0x0a,
	CHARGER_TC_CURRENT_6p75mA  =0x0b,
	CHARGER_TC_CURRENT_7p23mA  =0x0c,
	CHARGER_TC_CURRENT_7p70mA  =0x0d,
	CHARGER_TC_CURRENT_8p17mA  =0x0e,
	CHARGER_TC_CURRENT_8p66mA  =0x0f,
}charger_tc_current_e;


typedef enum{
	CHARGER_CV_VOLTAGE_3p980V  =0x00,
	CHARGER_CV_VOLTAGE_3p999V  =0x10,
	CHARGER_CV_VOLTAGE_4p018V  =0x20,
	CHARGER_CV_VOLTAGE_4p035V  =0x30,
	CHARGER_CV_VOLTAGE_4p054V  =0x40,
	CHARGER_CV_VOLTAGE_4p072V  =0x50,
	CHARGER_CV_VOLTAGE_4p090V  =0x60,
	CHARGER_CV_VOLTAGE_4p108V  =0x70,
	CHARGER_CV_VOLTAGE_4p127V  =0x80,
	CHARGER_CV_VOLTAGE_4p145V  =0x90,
	CHARGER_CV_VOLTAGE_4p163V  =0xa0,
	CHARGER_CV_VOLTAGE_4p181V  =0xb0,
	CHARGER_CV_VOLTAGE_4p199V  =0xc0,
	CHARGER_CV_VOLTAGE_4p218V  =0xd0,
	CHARGER_CV_VOLTAGE_4p236V  =0xe0,
	CHARGER_CV_VOLTAGE_4p254V  =0xf0,
}charger_cv_voltage_e;


typedef enum{
	MANUAL_SHUT_DOWM = 0xb0, /**< automatic mode has its own shutdown mode, which refers to the shutdown mode in manual mode */
	MANUAL_TC = 0xc0,        /**< Pre-charging(TC):the charger is in tc mode and can be manually adjusted current for charging,voltage keeps rising */
	MANUAL_CC = 0xd0,        /**< Constant current charging(CC):the charger is in cc mode and can be manually adjusted for charging,voltage keeps rising */
	MANUAL_CV = 0xe0,        /**< Constant voltage charging(CV):the charger switches to cv mode, keeping the charging voltage constant and gradually decreasing the charging current in the process */
	AUTO_MODE = 0x40,        /**< the charger core is controlled by a state machine during automatic charging */
}charger_mode_e;


typedef enum{
	CHARGER_STATUS_TC = 0x47,
	CHARGER_STATUS_CC = 0x46,
	CHARGER_STATUS_CV = 0x4a,
	CHARGER_STATUS_STDBY = 0x60,
	CHARGER_STATUS_ERROR = 0x50,
}charger_status_e;


/**
 * @brief      The function of this API is to set charger mode.
 * @param[in]  manual_mode_e - charger model.
 * @return     none
 */
void charger_set_mode(charger_mode_e charger_mode);


/**
 * @brief      The function of this API is to adjust constant current charging current.
 * @param[in]  cc_current - enumeration of current gear.
 * @return     none
 */
void charger_set_cc_current(charger_cc_current_e cc_current);

/**
 * @brief      The function of this API is to adjust charge in advance charging current.
 * @param[in]  tc_current - enumeration of current gear.
 * @return     none
 */
void charger_set_tc_current(charger_tc_current_e tc_current);

/**
 * @brief      The function of this API is to adjust constant voltage charging voltage.
 * @param[in]  cv_voltage - enumeration of voltage gear.
 * @return     none
 */
void charger_set_cv_voltage(charger_cv_voltage_e cv_voltage);

/**
 * @brief      The function of this API is to check whether the usb is on or off,
 *             due to the jitter of manual usb insertion and removal, through the experimental test, the jitter range is as follows:
 *             the max of the usb insertion: 3ms    the max of the usb removal:1ms
 * @return     1:vbus power on 0:vbus power down;
 */
_Bool charger_get_vbus_status();


/*******************************************************************************************************************
 *		          the functions for internal use in charger,in order to test                                       *
 ******************************************************************************************************************/
/**
 * @brief      The function of this API is to get charge status.
 * @return     none
 */
charger_status_e charger_get_status();
#endif /* CHARGER_H_ */
