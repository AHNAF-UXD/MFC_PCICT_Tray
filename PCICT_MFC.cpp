
// PCICT_MFC.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "PCICT_MFC.h"
#include "PCICT_MFCDlg.h"
#include "loginDlg.h"
#include "afxdialogex.h"
#include "afxinet.h"
#include "json.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>
#include <cstdlib>
#include <regex>
#include <atlbase.h> //Required for CRegKey

using namespace std;
using json = nlohmann::json;


// PCICTMFCApp

BEGIN_MESSAGE_MAP(PCICTMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// PCICTMFCApp construction

PCICTMFCApp::PCICTMFCApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only PCICTMFCApp object

PCICTMFCApp theApp;

void AddToStartup()
{
	CRegKey regKey;
	LONG lResult;
	const wchar_t* szAppName = L"PCICT";
	wchar_t szPath[MAX_PATH];

	GetModuleFileName(NULL, szPath, MAX_PATH);

	lResult = regKey.Open(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", KEY_WRITE);
	if (lResult == ERROR_SUCCESS)
	{
		regKey.SetStringValue(szAppName, szPath);
		regKey.Close();
	}
}


// PCICTMFCApp initialization

BOOL PCICTMFCApp::InitInstance()
{

	AddToStartup(); // Ensure the app runs on startup

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	//INITCOMMONCONTROLSEX InitCtrls;
	//InitCtrls.dwSize = sizeof(InitCtrls);
	//// Set this to include all the common control classes you want to use
	//// in your application.
	//InitCtrls.dwICC = ICC_WIN95_CLASSES;
	//InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	//AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	//CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	
	//SetRegistryKey(_T("Ultra-X BD"));

	//CPCICTMFCDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//}
	//else if (nResponse == -1)
	//{
	//	TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	//	TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	//}

	//// Delete the shell manager created above.
	//if (pShellManager != nullptr)
	//{
	//	delete pShellManager;
	//}
	// 
	// 
	 // Query for saved login token
	CString token = this->GetSavedLoginToken();
	// Start login check logic
	LABEL_LOGIN_CHECK_START:
	if (token == L"TOKEN_NOT_FOUND" || token == L"")
	{
		// Show the login dialog
		loginDlg myLoginDlg;
		INT_PTR loginResponse = myLoginDlg.DoModal();

		//CString chk;
		//chk.Format(L"%d",loginResponse);
		//AfxMessageBox(L"main er agey eta pelam " + chk);

		// Check the response from the login dialog
		if (loginResponse == IDOK)
		{
			//AfxMessageBox(L"Direct main e dhukse");
			// If login is successful, show the main dialog
			delete myLoginDlg;
			this->user_id = this->GetSavedLoginUserID();
			this->username = this->GetSavedLoginUsername();
			this->user_role = this->GetSavedLoginUserRole();
			this->language = this->GetSavedLoginLanguage();
			/*CPCICTMFCDlg mainDlg;
			m_pMainWnd = &mainDlg;
			mainDlg.DoModal();*/
		}
		else if(loginResponse == -1)
		{
			//AfxMessageBox(L"Just check 1");
			goto LABEL_LOGIN_CHECK_START;
		}
		else {
			// Login failed or was cancelled, exit the application
			//AfxMessageBox(L"Just check 2");
			return FALSE;
		}
}
	else
	{
		int tokenValidity = LoginTokenCheck();

		if (tokenValidity == -1)
		{
			// If the token is invalid, show the login dialog
			loginDlg myLoginDlg;
			INT_PTR loginResponse = myLoginDlg.DoModal();
			// Check the response from the login dialog
			if (loginResponse == IDOK)
			{
				// If login is successful, show the main dialog
				delete myLoginDlg;
				this->user_id = this->GetSavedLoginUserID();
				this->username = this->GetSavedLoginUsername();
				this->user_role = this->GetSavedLoginUserRole();
				this->language = this->GetSavedLoginLanguage();
				//AfxMessageBox(language);
				/*CPCICTMFCDlg mainDlg;
				m_pMainWnd = &mainDlg;
				mainDlg.DoModal();*/
			}
			else {
				// Login failed or was cancelled, exit the application
				return FALSE;
			}
		}
		else
		{
			//AfxMessageBox(L"Token check success");
			// If the token is valid, show the main dialog
			/*CPCICTMFCDlg mainDlg;
			m_pMainWnd = &mainDlg;
			mainDlg.DoModal();*/
		}
		// If the login token exists, directly show the main dialog
		this->user_id = this->GetSavedLoginUserID();
		this->username = this->GetSavedLoginUsername();
		this->user_role = this->GetSavedLoginUserRole();
		this->language = this->GetSavedLoginLanguage();
		//AfxMessageBox(language);

		/*CPCICTMFCDlg mainDlg;
		m_pMainWnd = &mainDlg;
		INT_PTR nResponse = mainDlg.DoModal();*/

		//if (nResponse == IDOK)
		//{
		//	// Handle case when the dialog is dismissed with OK
		//	delete mainDlg;
		//}
		//else if (nResponse == IDCANCEL)
		//{
		//	// Handle case when the dialog is dismissed with Cancel
		//	delete mainDlg;
		//}

		//LoginTokenCheck();

	}

	CPCICTMFCDlg mainDlg;
	//m_pMainWnd = &mainDlg;
	mainDlg.DoModal();


	//#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	//	ControlBarCleanUp();
	//#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}

CString PCICTMFCApp::GetSavedLoginToken()
{
	CRegKey regKey;
	CString token;
	ULONG nChars = 512;  // Length for the token buffer

	// Open the registry key
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_READ);

	if (result == ERROR_SUCCESS)
	{
		// Try to retrieve the token
		TCHAR szToken[512] = { 0 };
		if (regKey.QueryStringValue(_T("LoginToken"), szToken, &nChars) == ERROR_SUCCESS && szToken != _T(""))
		{
			token = szToken;  // Assign token if found
		}
		else {
			token = _T("TOKEN_NOT_FOUND");
		}
		regKey.Close();
	}

	return token;
}

CString PCICTMFCApp::GetSavedLoginUserID()
{
	CRegKey regKey;
	CString token;
	ULONG nChars = 512;  // Length for the token buffer

	// Open the registry key
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_READ);

	if (result == ERROR_SUCCESS)
	{
		// Try to retrieve the token
		TCHAR szToken[512] = { 0 };
		if (regKey.QueryStringValue(_T("UserID"), szToken, &nChars) == ERROR_SUCCESS && szToken != _T(""))
		{
			token = szToken;  // Assign token if found
		}
		else {
			token = _T("USER_ID_NOT_FOUND");
		}
		regKey.Close();
	}

	return token;
}

CString PCICTMFCApp::GetSavedLoginUsername()
{
	CRegKey regKey;
	CString token;
	ULONG nChars = 512;  // Length for the token buffer

	// Open the registry key
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_READ);

	if (result == ERROR_SUCCESS)
	{
		// Try to retrieve the token
		TCHAR szToken[512] = { 0 };
		if (regKey.QueryStringValue(_T("Username"), szToken, &nChars) == ERROR_SUCCESS && szToken != _T(""))
		{
			token = szToken;  // Assign token if found
		}
		else {
			token = _T("USERNAME_NOT_FOUND");
		}
		regKey.Close();
	}

	return token;
}

CString PCICTMFCApp::GetSavedLoginUserRole()
{
	CRegKey regKey;
	CString token;
	ULONG nChars = 512;  // Length for the token buffer

	// Open the registry key
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_READ);

	if (result == ERROR_SUCCESS)
	{
		// Try to retrieve the token
		TCHAR szToken[512] = { 0 };
		if (regKey.QueryStringValue(_T("Role"), szToken, &nChars) == ERROR_SUCCESS && szToken != _T(""))
		{
			token = szToken;  // Assign token if found
		}
		else {
			token = _T("USER_ROLE_NOT_FOUND");
		}
		regKey.Close();
	}

	return token;
}

CString PCICTMFCApp::GetSavedLoginLanguage()
{
	CRegKey regKey;
	CString lang;
	ULONG nChars = 512;  // Length for the token buffer

	// Open the registry key
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_READ);

	if (result == ERROR_SUCCESS)
	{
		// Try to retrieve the token
		TCHAR szLang[512] = { 0 };
		if (regKey.QueryStringValue(_T("Language"), szLang, &nChars) == ERROR_SUCCESS && szLang != _T(""))
		{
			lang = szLang;  // Assign token if found
		}
		else {
			lang = _T("LANGUAGE_NOT_FOUND");
		}
		regKey.Close();
	}

	return lang;
}

void PCICTMFCApp::CallForRestart()
{
	// Restart the application
	CString appPath;
	::GetModuleFileName(NULL, appPath.GetBufferSetLength(MAX_PATH), MAX_PATH);
	appPath.ReleaseBuffer();

	// Start a new instance of the application
	::ShellExecute(NULL, _T("open"), appPath, NULL, NULL, SW_SHOWNORMAL);

	// Close the current instance
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

int PCICTMFCApp::LoginTokenCheck()
{
	// Start of Login methodology
	CString domain = _T("bdtmp.ultra-x.jp");
	CString tokenCheckAPI = _T("/pcict_backend/users/checkUser");

	CString strResponse;

	char buffer[1024];
	UINT bytesRead = 0;
	string status;
	//UpdateData(TRUE);


	CString tokenHeader;
	CString token = this->GetSavedLoginToken();

	try {
		//AfxMessageBox(L"Login Function e Dhukse");
		CInternetSession session;
		CHttpConnection* pServer = session.GetHttpConnection(domain, INTERNET_FLAG_SECURE, INTERNET_DEFAULT_HTTPS_PORT);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, tokenCheckAPI, NULL, 1, NULL, NULL, INTERNET_FLAG_SECURE);

		// Set headers
		pFile->AddRequestHeaders(_T("Content-Type: application/json\r\n"));
		pFile->AddRequestHeaders(_T("Accept: application/json\r\n"));
		tokenHeader = L"Authorization: Bearer " + token;
		pFile->AddRequestHeaders(tokenHeader);
		// Send the request with the JSON data
		pFile->SendRequest(NULL, 0, 0, 0);

		DWORD statusCode = 0;
		pFile->QueryInfoStatusCode(statusCode);
		if (statusCode != HTTP_STATUS_OK && statusCode != 401) {
			CString errorMsg;
			errorMsg.Format(_T("HTTP request failed with status code: %d"), statusCode);
			AfxMessageBox(errorMsg);
			return -1;
		}

		if (statusCode != 200) {
			//AfxMessageBox(L"Kop Diye Dilam");
			return -1;
		}

		//json jsonResponse = json::parse((string)CStringA(strResponse));


		if (statusCode == 401) {
			AfxMessageBox(L"Error with 401");
			return -1;
		}

		while ((bytesRead = pFile->Read(buffer, sizeof(buffer) - 1)) > 0) {
			buffer[bytesRead] = 0;
			strResponse += buffer;
		}

		//AfxMessageBox(strResponse);


		/*string tmp = jsonResponse["token"].dump();
		theApp.user_id = CString((jsonResponse["user"]["user_id"].dump()).c_str());
		theApp.first_name = CString((jsonResponse["user"]["first_name"].get<string>()).c_str());
		theApp.last_name = CString((jsonResponse["user"]["last_name"].get<string>()).c_str());
		theApp.user_role = CString((jsonResponse["user"]["role"].get<string>()).c_str());
		loginToken = CString(tmp.c_str());*/

		pFile->Close();
		delete pFile;
		delete pServer;
		session.Close();
	}
	catch (CInternetException* pEx) {
		TCHAR szError[1024];
		pEx->GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		pEx->Delete();
		return -1;
	}
	catch (json::parse_error& e) {
		CString jsonError;
		jsonError.Format(_T("JSON parsing failed: %s"), CString(e.what()));
		AfxMessageBox(jsonError);
		return -1;
	}

	return 0;
}

