
// PCICT_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// PCICTMFCApp:
// See PCICT_MFC.cpp for the implementation of this class
//

class PCICTMFCApp : public CWinApp
{
public:
	PCICTMFCApp();

// Overrides
public:
	CString user_id;
	CString username;
	CString first_name;
	CString last_name;
	CString user_role;
	CString language = L"";
	virtual BOOL InitInstance();
	CString GetSavedLoginToken();
	CString GetSavedLoginUserID();
	CString GetSavedLoginUsername();
	CString GetSavedLoginUserRole();
	CString GetSavedLoginLanguage();
	void CallForRestart();

	int LoginTokenCheck();

	CString KB_status;
	CString KB_totalKeyPress;

	int prdlgX;
	int prdlgY;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern PCICTMFCApp theApp;
