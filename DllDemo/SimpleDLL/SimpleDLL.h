// SimpleDLL.h : main header file for the SimpleDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSimpleDLLApp
// See SimpleDLL.cpp for the implementation of this class
//



class CSimpleDLLApp : public CWinApp
{
public:
	CSimpleDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
