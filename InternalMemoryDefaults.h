// InternalMemoryDefaults.h
//
// Contains the default values for the settings on the controller
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

#define DEFAULT_WM1_INTERVAL			200
#define DEFAULT_WM2_INTERVAL			354
#define DEFAULT_ACTINIC					50
#define DEFAULT_DAYLIGHT				50
#define DEFAULT_FEEDING_TIMER			900
#define DEFAULT_LCD_TIMER				600
#define DEFAULT_PH7						550
#define DEFAULT_PH10					840
#define DEFAULT_ATO_LOW_TIMEOUT			60
#define DEFAULT_ATO_HIGH_TIMEOUT		60
#define DEFAULT_ATO_LOW_INTERVAL		0
#define DEFAULT_ATO_HIGH_INTERVAL		0
#define DEFAULT_MH_ON_HOUR				8
#define DEFAULT_MH_ON_MINUTE			0
#define DEFAULT_MH_OFF_HOUR				15
#define DEFAULT_MH_OFF_MINUTE			0
#define DEFAULT_MH_DELAY				5
#define DEFAULT_STD_ON_HOUR				8
#define DEFAULT_STD_ON_MINUTE			0
#define DEFAULT_STD_OFF_HOUR			15
#define DEFAULT_STD_OFF_MINUTE			0
#define DEFAULT_DP1_ON_HOUR				20
#define DEFAULT_DP1_ON_MINUTE			0
#define DEFAULT_DP1_RUN_TIME			10
#define DEFAULT_DP2_ON_HOUR				22
#define DEFAULT_DP2_ON_MINUTE			30
#define DEFAULT_DP2_RUN_TIME			10
#define DEFAULT_HEATER_ON_TEMP_F		80  // offset, 78.0F
#define DEFAULT_HEATER_OFF_TEMP_F		91  // offset, 79.1F
#define DEFAULT_CHILLER_ON_TEMP_F		110 // offset, 81.0F
#define DEFAULT_CHILLER_OFF_TEMP_F		85  // offset, 78.5F
#define DEFAULT_OVERHEAT_TEMP_F			700 // offset, 150.0F
#define DEFAULT_HEATER_ON_TEMP_C		44  // offset, 25.5C
#define DEFAULT_HEATER_OFF_TEMP_C		51  // offset, 26.2C
#define DEFAULT_CHILLER_ON_TEMP_C		61  // offset, 27.2C
#define DEFAULT_CHILLER_OFF_TEMP_C		47  // offset, 25.8C
#define DEFAULT_OVERHEAT_TEMP_C			389 // offset, 65.5C
#define DEFAULT_DELAY_MINUTES			5
#define DEFAULT_SAL_MAX					2550
//#define DEFAULT_RF_MODE					"Constant"
#define DEFAULT_RF_SPEED				100
#define DEFAULT_RF_DURATION				10
#define DEFAULT_PWM_START_PERCENT		15
#define DEFAULT_PWM_END_PERCENT			100
#define DEFAULT_PWM_DURATION			60

// default temperature ranges
#define DEG_F_LOW_TEMP					70.0
#define DEG_F_HIGH_TEMP					90.0
#define DEG_F_LOW_OVERHEAT_TEMP			80.0
#define DEG_F_HIGH_OVERHEAT_TEMP		200.0
#define DEG_C_LOW_TEMP					21.1
#define DEG_C_HIGH_TEMP					32.3
#define DEG_C_LOW_OVERHEAT_TEMP			26.6
#define DEG_C_HIGH_OVERHEAT_TEMP		93.3
#define DEG_SYMBOL						176
#define DEG_F_OFFSET					700
#define DEG_F_OVERHEAT_OFFSET			800
#define DEG_C_OFFSET					211
#define DEG_C_OVERHEAT_OFFSET			266

// value ranges for items
#define PWM_MIN				0
#define PWM_MAX				100
#define HR_MIN				0
#define HR_MAX				23
#define MIN_MIN				0
#define MIN_MAX				59
#define BYTE_MIN			0
#define BYTE_MAX			255
#define WM_MIN				0
#define WM_MAX				21600
#define PH_MIN				0
#define PH_MAX				1024
#define TIMEOUTS_MIN		0
#define TIMEOUTS_MAX		3600
#define MENU_MIN			1
#define MENU_MAX			9
#define MENU_DEFAULT		6