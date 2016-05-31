// DllDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DllDemo.h"
#include "../SimpleDll/Add.h"
#include <Strsafe.h>
#include "../StaticLib/Header.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
void TestStaticLib()
{
	double x = 1.0, y = 2.0;
	CString msg;
	msg.Format(_T("%f"), Multiply(x, y));
	AfxMessageBox(msg);

}

void TestImplicitDll()
{
	double x = 1.0, y = 2.0;
	CString msg;
	msg.Format(_T("%f"), Add(x, y));
	AfxMessageBox(msg);
}


void TestExplicitDll()
{
	HMODULE module = ::LoadLibrary(_T("SimpleDLL2.dll"));
	auto substract = reinterpret_cast<double(*)(double, double)>(
		::GetProcAddress(module, "Substract"));

	if (substract == nullptr)
	{
		ErrorExit(_T("GetProcAddress"));
	}
	else
	{
		CString msg;
		msg.Format(_T("%f"), substract(2.0, 1.0));
		AfxMessageBox(msg);

	}

	::FreeLibrary(module);
}

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: change error code to suit your needs
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
			TestImplicitDll();
			TestExplicitDll();
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
