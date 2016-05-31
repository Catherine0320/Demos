// SimpleDLL2.h : main header file for the SimpleDLL2 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSimpleDLL2App
// See SimpleDLL2.cpp for the implementation of this class
//

class CSimpleDLL2App : public CWinApp
{
public:
	CSimpleDLL2App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
