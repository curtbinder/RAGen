// Device.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

class CDevice
{
public:
	//CDevice(void);
	CDevice(int ID, CString sFunction, CString sFunctionParams, BOOL fUseMemory = TRUE);
	~CDevice(void);

	CString GetFunction();
	virtual CString GetFunctionParams();
	inline int GetID() { return m_ID; }
	inline BOOL IsUseMemory() { return m_fUseMemory; }

	void UseMemory(BOOL fEnable) { m_fUseMemory = fEnable; }

private:
	int m_ID;
	CString m_sFunction;
	CString m_sFunctionParams;
	BOOL m_fUseMemory;
};
