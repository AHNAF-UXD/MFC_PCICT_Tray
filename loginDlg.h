#pragma once
#include "afxdialogex.h"


// loginDlg dialog

class loginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(loginDlg)

public:
	loginDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~loginDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()



	//protected:
	//    virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	//
	//    DECLARE_MESSAGE_MAP()

public:
	CString username;
	CString password;

	afx_msg void OnBnClickedButtonLogin();
	void SaveLoginToken(const CString& token, const CString& user_id, const CString& username, const CString& user_role, const CString user_lang);
	CString GetSavedLoginToken();
	int PerformLogin();
	void ClearLoginToken();
	bool IsEmailValid(const CString& email); // Helper function to validate email
	bool IsPasswordValid(const CString& password); // Helper function to validate password
	
	CEdit ctl_email;
	CEdit ctl_password;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeComboLangP();
	CComboBox combox_p;
	CStatic static_wc;
	CStatic static_email;
	CStatic static_password;
	CButton btn_login;
	CStatic static_reg_q;
	CMFCLinkCtrl link_reg;
};
