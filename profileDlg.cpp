// profileDlg.cpp : implementation file
//

#include "pch.h"
#include "PCICT_MFC.h"
#include "afxdialogex.h"
#include "profileDlg.h"
#include "loginDlg.h"
#include "PCICT_MFCDlg.h"


// profileDlg dialog

IMPLEMENT_DYNAMIC(profileDlg, CDialogEx)

profileDlg::profileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROFILE, pParent)
{

}

profileDlg::~profileDlg()
{
}

void profileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, logoutbtn);
}



BEGIN_MESSAGE_MAP(profileDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &profileDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &profileDlg::OnBnClickedButtonLogout)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// profileDlg message handlers


void profileDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	EndDialog(IDOK); // This will close the dialog
}

void profileDlg::ClearLoginToken()
{
	CRegKey regKey;
	LONG result = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Ultra-X BD\\Login"), KEY_SET_VALUE);

	if (result == ERROR_SUCCESS)
	{
		regKey.SetStringValue(_T("LoginToken"), _T(""));  // Clear the token
		regKey.SetStringValue(_T("UserID"), _T(""));  // Clear the userID
		regKey.SetStringValue(_T("Username"), _T(""));  // Clear the username
		regKey.SetStringValue(_T("Role"), _T(""));  // Clear the User role
		//regKey.SetStringValue(_T("Language"), _T(""));  // Clear the language
		regKey.Close();
	}
}

BOOL profileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (theApp.language == L"en") {
		logoutbtn.SetWindowTextW(L"Logout");  // English text
	}
	else {
		logoutbtn.SetWindowTextW(L"ログアウト");  // Japanese text (Logout in Japanese)
	}
	
	

	//GetDlgItem(IDC_FULLNAME)->SetWindowTextW(theApp.username.MakeUpper());
	//GetDlgItem(IDC_USER_ROLE)->SetWindowTextW(theApp.user_role.MakeUpper());

	GetDlgItem(IDC_FULLNAME)->SetWindowTextW(theApp.username);
	GetDlgItem(IDC_USER_ROLE)->SetWindowTextW(theApp.user_role);
	
	//CString chk;
	//chk.Format(L"X: %d and Y: %d", theApp.prdlgX, theApp.prdlgX);
	//AfxMessageBox(chk);
	//MoveWindow(100,200,200,200);
	SetWindowPos(NULL, theApp.prdlgX + 3, theApp.prdlgY + 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	CStatic* pImageCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
	if (pImageCtrl)
	{
		// Load the icon from resources
		HICON hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_IMAGE));
		if (hIcon)
		{
			// Set the icon to the CStatic control
			pImageCtrl->SetIcon(hIcon);
		}
	}

	return TRUE;
}


void profileDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	CString currentToken = theApp.GetSavedLoginToken();
	if (currentToken == L"TOKEN_NOT_FOUND" || currentToken.IsEmpty()) {
		AfxMessageBox(L"You are not logged in");

		this->ClearLoginToken();
		EndDialog(IDOK);
		// Restart the application
		theApp.CallForRestart();

	}
	else {

		this->ClearLoginToken();
		EndDialog(IDOK);
		// Restart the application
		theApp.CallForRestart();

	}
}

void profileDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	if (nState == WA_INACTIVE)
	{
		// Close the dialog when it becomes inactive (clicked outside)
		//DestroyWindow();
		EndDialog(IDOK);
		//PostQuitMessage(0);
		if (GetParent())
		{
			// Inform the parent that the child is closed
			//((CImageTestDlg*)GetParent())->m_pChildDialog = nullptr;
			//AfxMessageBox(L"Hello World");
		}

	}

}