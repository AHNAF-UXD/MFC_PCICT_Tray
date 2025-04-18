#pragma once
#include "afxdialogex.h"


// profileDlg dialog

class profileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(profileDlg)

public:
	profileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~profileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROFILE };
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void ClearLoginToken();
	virtual BOOL OnInitDialog();

	CButton logoutbtn;
};
