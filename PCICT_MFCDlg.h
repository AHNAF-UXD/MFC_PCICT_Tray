
// PCICT_MFCDlg.h : header file
//

#pragma once
#include <atomic>
#include <thread>
#include <chrono>

#define WM_SHOW_BENCHMARK_RESULT (WM_APP + 1)

// CPCICTMFCDlg dialog
class CPCICTMFCDlg : public CDialogEx
{
// Construction
public:
	CPCICTMFCDlg(CWnd* pParent = nullptr);	// standard constructor

	// Benchmark results
	int SingleBenchmarkResult;
	int MultiBenchmarkResult;
	double CPU_rating;
	CString singleThreadScoreStr;
	CString multiThreadScoreStr;
	CString cpuRatingStr;

	CString kbStatusMessage;

	NOTIFYICONDATA m_TrayIconData;
	BOOL m_bTrayIconVisible;

	void ShowTrayIcon();
	void RemoveTrayIcon();
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnRestoreFromTray();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PCICT_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Control variables for progress bar and button
	CProgressCtrl m_progressCPU;
	CButton m_startButton;

	// Atomic flag to control benchmark duration
	std::atomic<bool> m_benchmarkRunning;

	// Benchmark functions
	void RunSingleThreadedBenchmark();
	void RunMultiThreadedBenchmark();
	double CalculateCPUScore();

	// Prime factorization function
	bool IsPrime(int n);

	// Generated message map functions
	void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void OnCancel();
	//void OnOK();
	//void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Global CString variables to store device information

	CDialogEx* m_pChildDialog;

	CString deviceName;
	CString deviceUUID;
	CString deviceManufacturer;
	CString deviceModel;
	CString deviceSerialNumber;
	CString deviceMACAddress;

	CString cpuName;
	CString cpuManufacturer;
	CString cpuClockSpeed;

	CString uefiBios;
	CString biosVersion;
	CString biosManufacturer;
	CString biosReleaseDate;

	CString ramManufacturers;
	CString ramSizes;
	CString ramSlotCount;

	CString storageDeviceNames;
	CString storageDeviceSizes;
	CString storageDeviceTypes;

	CString osName;
	CString kernel;
	CString arch;
	CString pcUserName;
	CString userID;
	CString userToken;

	CString bluetoothName;
	CString bluetoothManufacturer;

	CString startupTime;

	CString cameraName;
	CString cameraManufacturer;

	CString batteryDeviceName;
	CString batteryManufacturer;
	CString chemistryType;
	CString degradationRateMsg;
	CString batteryHealth;
	CString CPUstScore = L"Not tested yet";
	CString CPUmtScore = L"Not tested yet";
	CString CPUratingScore = L"Not tested yet";
	CString KBstatus = L"N/A";
	CString KBtotalKeyPress = L"Not tested yet";
	bool isKeyboardTested = false;
	bool isCPUTested = false;
	bool firstOpen = true;
	int batteryChemistry = 0;
	int designedCapacity = 0;
	int fullChargedCapacity = 0;
	int currentCapacity = 0;
	int cycleCount = 0;
	double degradationRate = 0.0;                  

	CString wifiName;
	CString wifiManufacturer;
	CString wifiMacAddress;

	//afx_msg void OnEnChangeEdit1();
	CTreeCtrl m_treeCtrl;
	afx_msg void OnBnClickedMfcmenubutton1();
	CMFCMenuButton profileButton;
	void PostNcDestroy();
	afx_msg void OnBnClickedButtonUpload();
	bool SaveToFile(CString fileContent);
	CString strAllInfoJson;
	CString allInfoJson();
	bool UploadLogFile(CString logFilePath);
	CString GetValueByKey(const CString& response, const CString& key);
	void get_all_pc_info();
	void all_tree_drawing();
	CString logPath;
	CString logFileName;
	//afx_msg LRESULT OnShowBenchmarkResult(WPARAM wParam, LPARAM lParam);
	void OnBnClickedButtonCpuTestStart();
	//CProgressCtrl m_progressCPU;
	//CButton m_startButton;
	CStatic static_singleT;
	CStatic static_multiT;
	CStatic static_rating;

	CStatic static_kb_status;

	CFont BigFont, UlFont;
	CStatic CPUresultHeading;
	CStatic KBresultHeading;
	CStatic KBtestHeading;
	CStatic CPUtestHeading;
	CStatic PCinfoHeading;
	afx_msg void OnBnClickedButtonKbTestStart();
	afx_msg void OnBnClickedButtonclose();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonprofile();
	CComboBox combox;
	afx_msg void OnCbnSelchangeComboLang();
	CButton prf_btn;
	CButton file_btn;
	CButton act_btn;
	CButton view_btn;
	CButton help_btn;
	CButton t_kb_btn;
	CButton up_btn;
};



// Custom clamp function for C++14
template <typename T>
T clamp(const T& value, const T& minValue, const T& maxValue) {
	if (value < minValue) return minValue;
	if (value > maxValue) return maxValue;
	return value;
};
