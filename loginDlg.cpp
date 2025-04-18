// loginDlg.cpp : implementation file
//

#include "pch.h"
#include "PCICT_MFC.h"
#include "PCICT_MFCDlg.h"
#include "afxdialogex.h"
#include "loginDlg.h"
#include "afxinet.h"
#include "json.hpp"

#include <string>
#include <cstdlib>
#include <regex>

using namespace std;
using json = nlohmann::json;

// loginDlg dialog

IMPLEMENT_DYNAMIC(loginDlg, CDialogEx)

loginDlg::loginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{

}

loginDlg::~loginDlg()
{
}

void loginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_EMAIL, ctl_email);
	DDX_Control(pDX, IDC_INPUT_PASSWORD, ctl_password);
	DDX_Control(pDX, IDC_COMBO_LANG_P, combox_p);
	DDX_Control(pDX, IDC_STATIC_WC, static_wc);
	DDX_Control(pDX, IDC_STATIC_EMAIL, static_email);
	DDX_Control(pDX, IDC_STATIC_PASS, static_password);
	DDX_Control(pDX, IDC_BUTTON1, btn_login);
	DDX_Control(pDX, IDC_STATIC_REG, static_reg_q);
	DDX_Control(pDX, IDC_MFCLINK1, link_reg);
}


BEGIN_MESSAGE_MAP(loginDlg, CDialogEx)
	/*ON_BN_CLICKED(IDC_BUTTON1, &loginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &loginDlg::OnBnClickedOk)*/
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &loginDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON1, &loginDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_LANG_P, &loginDlg::OnCbnSelchangeComboLangP)
END_MESSAGE_MAP()

//
BOOL loginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CFont m_StylishFont;
	// Create the font
	m_StylishFont.CreatePointFont(180, _T("Arial")); // 180 = 18 points (you can adjust this value)


	theApp.language = theApp.GetSavedLoginLanguage();

	// Set the font to the static text control
	GetDlgItem(IDC_STATIC_WC)->SetFont(&m_StylishFont);
	if (theApp.language == L"jp")
	{
		combox_p.SetCurSel(1);
		//AfxMessageBox(_T("jp"));
	}
	else
	{
		combox_p.SetCurSel(0);
		//theApp.language = L"en";
		//AfxMessageBox(L"en");
	}
	OnCbnSelchangeComboLangP();

	return TRUE;
}
// loginDlg message handlers



void loginDlg::SaveLoginToken(const CString& token, const CString& user_id, const CString& username, const CString& user_role, const CString user_lang)
{
	// Open or create a registry key in HKEY_CURRENT_USER
	CRegKey regKey;
	CString mytoken = token;
	mytoken.Trim(_T("\""));
	LONG result = regKey.Create(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"));

	if (result == ERROR_SUCCESS)
	{
		// Save the token in the registry
		regKey.SetStringValue(_T("LoginToken"), mytoken);
		regKey.SetStringValue(_T("UserID"), user_id);
		regKey.SetStringValue(_T("Username"), username);
		regKey.SetStringValue(_T("Role"), user_role);
		regKey.SetStringValue(_T("Language"), user_lang);
		regKey.Close();
	}
	else
	{
		AfxMessageBox(_T("Failed to open registry key."));
	}
}

CString loginDlg::GetSavedLoginToken()
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

int loginDlg::PerformLogin()
{
	// Start of Login methodology
	CString email, password, loginToken;
	CString domain = _T("bdtmp.ultra-x.jp");
	CString loginAPI = _T("/pcict_backend/users/login");
	CString regAPI = L"/pcict_backend/users/register";
	CString userdataAPI = L"/pcict_backend/users/getMyUserData";
	CString strLogin, strResponse;
	string status;
	char buffer[1024];
	UINT bytesRead = 0;
	//UpdateData(TRUE);
	ctl_email.GetWindowTextW(email);
	ctl_password.GetWindowTextW(password);
	//GetDlgItem(IDC_INPUT_EMAIL)->GetWindowText(email);
	//AfxMessageBox(email);
	//GetDlgItem(IDC_INPUT_PASSWORD)->GetWindowText(password);


	//if (email == L"") {
	//	AfxMessageBox(L"Invalid email address. Please enter a valid email.");
	//	return -1;
	//}
	//if (password == L"") {
	//	AfxMessageBox(L"Please enter correct password");
	//	return -1;
	//}

	// Validate the email
	if (!IsEmailValid(email)) {
		AfxMessageBox(_T("Invalid email address. Please enter a valid email."));
		return -1;  // Restart the login process (stay on the same dialog)
	}

	// Validate the password
	if (!IsPasswordValid(password)) {
		AfxMessageBox(_T("Invalid password. Password must be at least 6 characters long."));
		return -1;  // Restart the login process (stay on the same dialog)
	}


	strLogin.Format(_T("{\"email\":\"%s\", \"password\":\"%s\"}"), email, password);
	string jsonansi = CStringA(strLogin);
	//json jsonLogin = json::parse((string)CStringA(strLogin));
	//AfxMessageBox(_T("ei porjonto asche"));
	try {
		//AfxMessageBox(L"Login Function e Dhukse");
		CInternetSession session;
		CHttpConnection* pServer = session.GetHttpConnection(domain, INTERNET_FLAG_SECURE, INTERNET_DEFAULT_HTTPS_PORT);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, loginAPI, NULL, 1, NULL, NULL, INTERNET_FLAG_SECURE);

		// Set headers
		pFile->AddRequestHeaders(_T("Content-Type: application/json\r\n"));
		pFile->AddRequestHeaders(_T("Accept: application/json\r\n"));
		// Send the request with the JSON data
		pFile->SendRequest(NULL, 0, (LPVOID)jsonansi.c_str(), jsonansi.length());

		DWORD statusCode = 0;
		pFile->QueryInfoStatusCode(statusCode);
		if (statusCode != HTTP_STATUS_OK && statusCode != 401) {
			CString errorMsg;
			errorMsg.Format(_T("HTTP request failed with status code: %d"), statusCode);
			AfxMessageBox(errorMsg);
			return -1;
		}
		while ((bytesRead = pFile->Read(buffer, sizeof(buffer) - 1)) > 0) {
			buffer[bytesRead] = 0;
			strResponse += buffer;
		}
		json jsonResponse = json::parse((string)CStringA(strResponse));
		status = jsonResponse["status"].dump();
		if (statusCode == 401) {
			string failMessage = jsonResponse["message"].dump();
			AfxMessageBox(CString(failMessage.c_str()));
			return -1;
		}
		string tmp = jsonResponse["token"].dump();
		theApp.user_id = CString((jsonResponse["user"]["user_id"].dump()).c_str());
		theApp.first_name = CString((jsonResponse["user"]["first_name"].get<string>()).c_str());
		theApp.last_name = CString((jsonResponse["user"]["last_name"].get<string>()).c_str());
		theApp.user_role = CString((jsonResponse["user"]["role"].get<string>()).c_str());
		//AfxMessageBox(theApp.language);
		loginToken = CString(tmp.c_str());

		pFile->Close();
		delete pFile;
		delete pServer;
		session.Close();
		//AfxMessageBox(L"Login Token Saved Successfull");
		this->SaveLoginToken(loginToken, theApp.user_id, theApp.first_name + L" " + theApp.last_name, theApp.user_role, theApp.language);
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

void loginDlg::ClearLoginToken()
{
	CRegKey regKey;
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_SET_VALUE);

	if (result == ERROR_SUCCESS)
	{
		regKey.SetStringValue(_T("LoginToken"), _T(""));  // Clear the token
		regKey.SetStringValue(_T("UserID"), _T(""));
		regKey.SetStringValue(_T("Username"), _T(""));
		regKey.SetStringValue(_T("Role"), _T(""));
		regKey.SetStringValue(_T("Language"), _T(""));
		regKey.Close();
	}
}

// Function to validate email format
bool loginDlg::IsEmailValid(const CString& email)
{
	// Convert CString to std::string for regex handling
	std::string strEmail = CT2A(email);

	// Regular expression to validate email format
	const std::regex emailPattern(
		//R"((\w+)(\.{1}\w+)*@(\w+)(\.\w{2,})+)"
		R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})?$)"
	);

	return std::regex_match(strEmail, emailPattern);
	//CString chk;
	//chk.Format(L"%d", std::regex_match(strEmail, emailPattern));
	//AfxMessageBox(chk);
	//return true;
}

// Function to validate password (at least 6 characters)
bool loginDlg::IsPasswordValid(const CString& password)
{
	return password.GetLength() >= 6;
}

void loginDlg::OnBnClickedButtonLogin()
{
//	// TODO: Add your control notification handler code here
//	//LOGIN_AGAIN:
//	int status = this->PerformLogin();
//	//int status = 10;
//	CString chk;
//	chk.Format(L"%d", status);
//	AfxMessageBox(_T("Login code- " + chk));
//
//	if (status == -1) {
//		return;
//	}
//	else {
//		AfxMessageBox(_T("Login sure hobe"));
//		CPCICTMFCDlg mainDlg;
//		//CWinThread::m_pMainWnd = &mainDlg;
//		mainDlg.DoModal();
//		EndDialog(IDOK);
//	}
}

void loginDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int status = this->PerformLogin();
	//int status = 10;
	//CString chk;
	//chk.Format(L"%d", status);
	//AfxMessageBox(_T("Login code- " + chk));
	
	if (status == -1) {
		return;
	}
	else {
		//AfxMessageBox(_T("Login sure hobe"));
		//CPCICTMFCDlg mainDlg;
		//m_pMainWnd = &mainDlg;
		//mainDlg.DoModal();
		// Add a small delay before proceeding (2500 milliseconds)
		//Sleep(2500);
		CDialogEx::OnClose();
		EndDialog(IDOK);
	}
}


void loginDlg::OnCbnSelchangeComboLangP()
{
	// TODO: Add your control notification handler code here

	// TODO: Add your control notification handler code here
	int sel = combox_p.GetCurSel(); // Get selected index
	CString selectedLang;
	combox_p.GetLBText(sel, selectedLang); // Get text of selected item

	if (combox_p.GetCurSel() == 1)
	{
		theApp.language = L"jp";
		static_wc.SetWindowTextW(_T("PCICTへようこそ"));
		static_email.SetWindowTextW(_T("電子メール"));
		static_password.SetWindowTextW(_T("パスワード"));
		btn_login.SetWindowTextW(_T("ログイン"));
		static_reg_q.SetWindowTextW(_T("アカウントをお持ちでない場合は、"));
		link_reg.SetWindowTextW(_T("ここに登録してください"));

	}
	else
	{
		theApp.language = L"en";
		static_wc.SetWindowTextW(_T("Welcome to PCICT"));
		static_email.SetWindowTextW(_T("Email"));
		static_password.SetWindowTextW(_T("Password"));
		btn_login.SetWindowTextW(_T("Login"));
		static_reg_q.SetWindowTextW(_T("Don't have an account?"));
		link_reg.SetWindowTextW(_T("Register Here"));

	}
	//AfxMessageBox(selectedText + _T(" is selected")); // Show message

	// Open or create a registry key in HKEY_CURRENT_USER
	CRegKey regKey;

	LONG result = regKey.Create(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"));

	if (result == ERROR_SUCCESS)
	{
		// Save the language in the registry
		regKey.SetStringValue(_T("Language"), theApp.language);
		regKey.Close();
	}
	else
	{
		AfxMessageBox(_T("Failed to open registry key to save language."));
	}

}
