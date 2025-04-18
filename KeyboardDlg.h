
#pragma once
#include "afxdialogex.h"

// KeyboardDlg dialog

class KeyboardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(KeyboardDlg)

public:
	KeyboardDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~KeyboardDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_KB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	BOOL OnInitDialog();

	void OnDestroy();

private:
	CFont BFont, SFont, NFont;
	void allKeyNormal();
	void HighlightKey(UINT key, bool isPressed);
	//void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	CButton kb1;
	HHOOK g_hKeyboardHook = NULL; // Global hook handle
	int test = 15061996;
	int keyBoard_Status = 1;
	//afx_msg void OnBnClicked1046();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);

	afx_msg void OnBnClickedButtonkbyes();
	afx_msg void OnBnClickedButtonkbno();
	void OnClose();
	//void OnCancel();
	static LRESULT LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	void SetKeyboardHook();
	void RemoveKeyboardHook();
	afx_msg void OnBnClickedButtonkbrefresh();
};
