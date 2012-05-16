// Device.cpp
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "StdAfx.h"
#include "Device.h"

CDevice::CDevice(int ID, CString sFunction, CString sFunctionParams, BOOL fUseMemory /*= TRUE*/)
{
	m_ID = ID;
	m_fUseMemory = fUseMemory;
	m_sFunction = sFunction;
	m_sFunctionParams = sFunctionParams;
}

CDevice::~CDevice(void)
{
}

CString CDevice::GetFunction()
{
	return m_sFunction;
}

CString CDevice::GetFunctionParams()
{
	return m_sFunctionParams;
}
