
// PCICT_MFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PCICT_MFC.h"
#include "PCICT_MFCDlg.h"
#include "profileDlg.h"
#include "afxdialogex.h"

#include <afxwin.h>
#include <afxinet.h>  // For CInternetSession, CHttpConnection, etc.
#include <fstream> 

#include <windows.h>
#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

#include <setupapi.h>
#include <devguid.h>
#include <string>
#include <vector>
#pragma comment(lib, "setupapi.lib")
#include <iostream>
#include <cstdlib>
#include <future>
#include <cmath>

#include <Lmcons.h>

#include <intrin.h>
#include <sstream>   // for std::stringstream
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "KeyboardDlg.h"


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPCICTMFCDlg dialog



CPCICTMFCDlg::CPCICTMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PCICT_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CPCICTMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
	DDX_Control(pDX, IDC_MFCMENUBUTTON1, profileButton);
	DDX_Control(pDX, IDC_PROGRESS_CPU_TEST_PROGRESS, m_progressCPU);
	DDX_Control(pDX, IDC_PROGRESS_CPU_TEST_START, m_startButton);
	DDX_Control(pDX, IDC_STATIC_SingleT, static_singleT);
	DDX_Control(pDX, IDC_STATIC_multiT, static_multiT);
	DDX_Control(pDX, IDC_STATIC_rating, static_rating);
	DDX_Control(pDX, IDC_STATIC_CPUresult, CPUresultHeading);
	DDX_Control(pDX, IDC_STATIC_KBresult, KBresultHeading);
	DDX_Control(pDX, IDC_STATIC_KBtest, KBtestHeading);
	DDX_Control(pDX, IDC_STATIC_CPUtest, CPUtestHeading);
	DDX_Control(pDX, IDC_STATIC_PCinfo, PCinfoHeading);
	DDX_Control(pDX, IDC_STATIC_kb_status, static_kb_status);
	DDX_Control(pDX, IDC_COMBO_LANG, combox);
	DDX_Control(pDX, IDC_BUTTON_profile, prf_btn);
	DDX_Control(pDX, IDC_BUTTON2, file_btn);
	DDX_Control(pDX, IDC_BUTTON3, act_btn);
	DDX_Control(pDX, IDC_BUTTON4, view_btn);
	DDX_Control(pDX, IDC_BUTTON5, help_btn);
	DDX_Control(pDX, IDC_BUTTON_KB_TEST_START, t_kb_btn);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD, up_btn);

}

BEGIN_MESSAGE_MAP(CPCICTMFCDlg, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_MESSAGE(WM_SHOW_BENCHMARK_RESULT, &CPCICTMFCDlg::OnShowBenchmarkResult)
	ON_BN_CLICKED(IDC_MFCMENUBUTTON, &CPCICTMFCDlg::OnBnClickedMfcmenubutton1)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CPCICTMFCDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_CPU_TEST_START, &CPCICTMFCDlg::OnBnClickedButtonCpuTestStart)
	ON_BN_CLICKED(IDC_BUTTON_KB_TEST_START, &CPCICTMFCDlg::OnBnClickedButtonKbTestStart)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CPCICTMFCDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_profile, &CPCICTMFCDlg::OnBnClickedButtonprofile)
	ON_CBN_SELCHANGE(IDC_COMBO_LANG, &CPCICTMFCDlg::OnCbnSelchangeComboLang)
	ON_MESSAGE(WM_USER + 1, &CPCICTMFCDlg::OnTrayNotification)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void CPCICTMFCDlg::ShowTrayIcon()
{
	m_TrayIconData.cbSize = sizeof(NOTIFYICONDATA);
	m_TrayIconData.hWnd = this->GetSafeHwnd();
	m_TrayIconData.uID = 1;
	m_TrayIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_TrayIconData.uCallbackMessage = WM_USER + 1;
	m_TrayIconData.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_TrayIconData.szTip, L"PCICT Running");

	Shell_NotifyIcon(NIM_ADD, &m_TrayIconData);
	m_bTrayIconVisible = TRUE;
}

void CPCICTMFCDlg::RemoveTrayIcon()
{
	if (m_bTrayIconVisible)
	{
		Shell_NotifyIcon(NIM_DELETE, &m_TrayIconData);
		m_bTrayIconVisible = FALSE;
	}
}

LRESULT CPCICTMFCDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN)
	{
		ShowWindow(SW_RESTORE);
		SetForegroundWindow();
		RemoveTrayIcon();
	}
	return 0;
}

void CPCICTMFCDlg::OnClose()
{
	ShowTrayIcon();
	ShowWindow(SW_MINIMIZE);
	ShowWindow(SW_HIDE); // Hide the window
}

void CPCICTMFCDlg::OnRestoreFromTray()
{
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();
	RemoveTrayIcon();
}


// CPCICTMFCDlg message handlers

void CPCICTMFCDlg::OnCancel()
{
	//AfxMessageBox(L"Hello Test");
	//DestroyWindow(); // Properly destroy the dialog window
	CDialogEx::OnClose(); // Call base class implementation
	PostQuitMessage(0);
}



BOOL CPCICTMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	combox.AddString(_T("English"));
	combox.AddString(_T("日本語"));

	if (theApp.language == L"en")
	{
		// Set default selection to "English"
		combox.SetCurSel(0);
	}
	else if (theApp.language == L"jp")
	{
		// Set default selection to "English"
		combox.SetCurSel(1);
	}
	else 
	{
		// Set default selection to "English"
		combox.SetCurSel(0);
		theApp.language == L"en";
	}


	OnCbnSelchangeComboLang();


	get_all_pc_info();
	all_tree_drawing();

	// Create a bigger font
	// Create a bold font
    BigFont.CreateFont(
        20,                      // Height of font (in pixels)
        0,                       // Width of font (0 for default)
        0,                       // Escapement
        0,                       // Orientation
        FW_BOLD,                 // Font weight (FW_BOLD for bold text)
        FALSE,                   // Italic
        FALSE,                   // Underline
        0,                       // StrikeOut
        DEFAULT_CHARSET,         // Character Set
        OUT_DEFAULT_PRECIS,      // Output Precision
        CLIP_DEFAULT_PRECIS,     // Clipping Precision
        DEFAULT_QUALITY,         // Quality
        DEFAULT_PITCH | FF_SWISS,// Pitch and Family
        _T("Segoe UI")              // Font face name
    );
	//UlFont.CreateFont(
	//	19,                      // Height of font (in pixels)
	//	0,                       // Width of font (0 for default)
	//	0,                       // Escapement
	//	0,                       // Orientation
	//	400,                 // Font weight (FW_BOLD for bold text)
	//	FALSE,                   // Italic
	//	TRUE,                   // Underline
	//	0,                       // StrikeOut
	//	DEFAULT_CHARSET,         // Character Set
	//	OUT_DEFAULT_PRECIS,      // Output Precision
	//	CLIP_DEFAULT_PRECIS,     // Clipping Precision
	//	DEFAULT_QUALITY,         // Quality
	//	DEFAULT_PITCH | FF_SWISS,// Pitch and Family
	//	_T("Segoe UI")              // Font face name
	//);

	UlFont.CreateFont(
		20,                        // Height of font (8 pixels)
		0,                        // Width of font (0 for default)
		0,                        // Escapement
		0,                        // Orientation
		0,               // Font weight (FW_REGULAR for regular text)
		FALSE,                    // Italic
		TRUE,                    // Underline
		0,                        // StrikeOut
		DEFAULT_CHARSET,          // Character Set (Western Script)
		OUT_DEFAULT_PRECIS,       // Output Precision
		CLIP_DEFAULT_PRECIS,      // Clipping Precision
		DEFAULT_QUALITY,          // Quality
		DEFAULT_PITCH | FF_SCRIPT,// Pitch and Family (Script)
		_T("Segoe UI")        // Font name (Script Western style)
	);


	CPUresultHeading.SetFont(&UlFont);
	KBresultHeading.SetFont(&UlFont);

	CPUtestHeading.SetFont(&BigFont);
	KBtestHeading.SetFont(&BigFont);
	PCinfoHeading.SetFont(&BigFont);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPCICTMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPCICTMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPCICTMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// WM_GETMINMAXINFO message handler
void CPCICTMFCDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialogEx::OnGetMinMaxInfo(lpMMI);

	// Set the minimum size for the window
	int minWidth = 932;  // Minimum width
	int minHeight = 777;  // Minimum height

	// Apply the minimum size to lpMMI
	lpMMI->ptMinTrackSize.x = minWidth;
	lpMMI->ptMinTrackSize.y = minHeight;
}

CString CPCICTMFCDlg::allInfoJson()
{
	CString strLog;
	userID = theApp.user_id;
	CString kbStEng = L"N/A";
	AfxMessageBox(KBstatus);
	if (KBstatus == L"Working") {
		kbStEng = L"Working";
	}
	if (KBstatus == L"Faulty") {
		kbStEng = L"Faulty";
	}
	if (KBstatus == L"動作中") {
		kbStEng = L"Working";
	}
	if (KBstatus == L"故障しています") {
		kbStEng = L"Faulty";
	}

	//AfxMessageBox(KBstatus + L" " + kbStEng);

	strLog.Format(
		_T("{\n")
		_T("    \"device_info\": {\n")
		_T("        \"device_uuid\": \"%s\",\n")
		_T("        \"user_id\": \"%s\",\n")
		_T("        \"uefi\": \"%s\",\n")
		_T("        \"bios_version\": \"%s\",\n")
		_T("        \"bios_vendor\": \"%s\",\n")
		_T("        \"bios_date\": \"%s\",\n")
		_T("        \"device_name\": \"%s\",\n")
		_T("        \"device_model\": \"%s\",\n")
		_T("        \"serial\": \"%s\",\n")
		_T("        \"mac_address\": \"%s\",\n")
		_T("        \"cpu_name\": \"%s\",\n")
		_T("        \"cpu_vendor\": \"%s\",\n")
		_T("        \"cpu_clock\": \"%s\",\n")
		_T("        \"ram_vendor\": \"%s\",\n")
		_T("        \"ram_size\": \"%s\",\n")
		_T("        \"ram_slot\": \"%s\",\n")
		_T("        \"storage_device_name\": \"%s\",\n")
		_T("        \"storage_device_size\": \"%s\",\n")
		_T("        \"storage_device_type\": \"%s\",\n")
		_T("        \"os_name\": \"%s\",\n")
		_T("        \"kernel\": \"%s\",\n")
		_T("        \"arch\": \"%s\",\n")
		_T("        \"hostname\": \"%s\",\n")
		_T("        \"bluetooth_adapter_name\": \"%s\",\n")
		_T("        \"bluetooth_adapter_manufacturer\": \"%s\",\n")
		_T("        \"bluetooth_mac_address\": \"%s\",\n")
		_T("        \"wifi_adapter_name\": \"%s\",\n")
		_T("        \"wifi_adapter_manufacturer\": \"%s\",\n")
		_T("        \"wifi_mac_address\": \"%s\",\n")
		_T("        \"camera_name\": \"%s\",\n")
		_T("        \"camera_manufacturer\": \"%s\",\n")
		_T("        \"battery_device_name\": \"%s\",\n")
		_T("        \"battery_manufacturer\": \"%s\",\n")
		_T("        \"battery_chemistry\": \"%s\",\n")
		_T("        \"battery_health\": \"%s\",\n")
		_T("        \"battery_design_capacity\": \"%s\",\n")
		_T("        \"battery_full_charge_capacity\": \"%s\",\n")
		_T("        \"battery_current_charge_capacity\": \"%s\",\n")
		_T("        \"battery_degradation_rate\": \"%s\",\n")
		_T("        \"battery_cycle_count\": \"%s\",\n")
		_T("        \"cpu_single_thread_score\": \"%s\",\n")
		_T("        \"cpu_multi_thread_score\": \"%s\",\n")
		_T("        \"cpu_rating\": \"%s\",\n")
		_T("        \"keyboard_status\": \"%s\"\n")
		_T("    }\n")
		_T("}\n")
		_T("EndOfLogFile"),
		deviceUUID, userID, uefiBios, biosVersion, biosManufacturer, biosReleaseDate, deviceName, deviceModel,
		deviceSerialNumber, deviceMACAddress, cpuName, cpuManufacturer, cpuClockSpeed, ramManufacturers, ramSizes,
		ramSlotCount, storageDeviceNames, storageDeviceSizes, storageDeviceTypes, osName, kernel, arch, pcUserName,
		bluetoothName, bluetoothManufacturer, deviceMACAddress, wifiName, wifiManufacturer, wifiMacAddress,
		cameraName, cameraManufacturer, batteryDeviceName, batteryManufacturer, chemistryType, batteryHealth,
		CString(std::to_wstring(designedCapacity).c_str()), CString(std::to_wstring(fullChargedCapacity).c_str()),
		CString(std::to_wstring(currentCapacity).c_str()), degradationRateMsg, CString(std::to_wstring(cycleCount).c_str())
		, CPUstScore, CPUmtScore, CPUratingScore, kbStEng
	);

	AfxMessageBox(CPUstScore + L" " + CPUmtScore + L" " + CPUratingScore + L" " + kbStEng);
	
	return strLog;
}



// Function to save content to a file
bool CPCICTMFCDlg::SaveToFile(CString fileContent)
{
	TCHAR szPath[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, szPath, MAX_PATH);
	CString rtPath(szPath);

	// Remove the application executable name from the path to get the root folder
	int pos = rtPath.ReverseFind(_T('\\'));
	if (pos != -1)
	{
		rtPath = rtPath.Left(pos); // Extract the directory path
	}

	// Construct the path to the LOG folder
	CString logFolderPath = rtPath + _T("\\LOG");

	// Check if the LOG folder exists, create it if not
	if (!PathFileExistsW(logFolderPath))
	{
		CreateDirectoryW(logFolderPath, NULL);
	}

	CTime currentTime = CTime::GetCurrentTime();
	CString dateTimeStr;

	// Format: "year-month-date-time" (e.g., "2024-09-18-14-30-45")
	dateTimeStr = currentTime.Format(_T("%Y-%m-%d-%H-%M-%S"));


	logFileName = deviceUUID + _T("-") + dateTimeStr + _T(".log");
	// Append the file name to the LOG folder path
	CString fullPath = logFolderPath + _T("\\") + logFileName;
	logPath = fullPath;

	//AfxMessageBox(rtPath);
	
	////////////////////////////////////////////////////////////////////////////
	
	// Step 2: Convert CString (UTF-16) to UTF-8
	std::string utf8Content;
	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, fileContent, -1, nullptr, 0, nullptr, nullptr);
	utf8Content.resize(sizeNeeded - 1);
	WideCharToMultiByte(CP_UTF8, 0, fileContent, -1, &utf8Content[0], sizeNeeded - 1, nullptr, nullptr);
	
	////////////////////////////////////////////////////////////////////////////
	CStdioFile file;
	if (file.Open(fullPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		// Step 3: Write UTF-8 BOM (Byte Order Mark) for compatibility
		const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
		file.Write(bom, sizeof(bom));

		// Step 4: Write the UTF-8 content
		file.Write(utf8Content.c_str(), utf8Content.size());

		file.Close();
		//AfxMessageBox(_T("File saved successfully."));
		return true;
	}
	else
	{
		//AfxMessageBox(_T("Failed to save the file."));
		return false;
	}
}

// Helper function to extract value by key
CString CPCICTMFCDlg::GetValueByKey(const CString& response, const CString& key) {

	
	// Construct a search pattern: "key":
	CString searchPattern = _T("\"") + key + _T("\":");

	int startIndex = response.Find(searchPattern);
	if (startIndex == -1) {
		return _T("Key not found");
	}

	// Move startIndex to the position after the key and colon
	startIndex += searchPattern.GetLength();

	// Skip any extra spaces
	while (response[startIndex] == ' ' || response[startIndex] == '\"') {
		++startIndex;
	}

	// Find the end of the value (comma, closing brace, or quotation mark)
	int endIndex = response.FindOneOf(_T("}"));
	if (endIndex == -1) {
		// If no comma or brace is found, check for a quotation mark instead
		endIndex = response.Find(_T("\""), startIndex);
	}

	if (endIndex == -1) {
		return _T("Parsing error");
	}

	// Extract the value
	CString value = response.Mid(startIndex, endIndex - startIndex);
	//CString chk;
	//chk.Format(L"%d - %d", startIndex, endIndex - startIndex);
	//AfxMessageBox(value + L"na paile " + chk);

	// Trim any surrounding quotes (for string values)
	value.Trim(_T("\""));

	return value+L".";
}

bool CPCICTMFCDlg::UploadLogFile(CString logFilePath)
{
	CInternetSession session;
	CHttpConnection* pConnection = nullptr;
	CHttpFile* pFile = nullptr;

	try
	{
		// Set the local server IP and endpoint
		//CString serverName = _T("192.168.88.33");
		CString serverName = _T("bdtmp.ultra-x.jp");
		CString apiEndpoint = _T("/pcict_backend/device/uploadLog");

		// Set the local server IP and endpoint
		//CString serverName = _T("bdtmp.ultra-x.jp");
		//CString apiEndpoint = _T("/pcict_backend/users/login");
		
		//int port = 3152;  // Local port

		// Connect to the server (Local IP and custom port)
		//pConnection = session.GetHttpConnection(serverName, INTERNET_FLAG_SECURE, INTERNET_DEFAULT_HTTPS_PORT);

		// Open a request to the server
		//pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, apiEndpoint, NULL, 1, NULL, NULL, INTERNET_FLAG_SECURE);

		//int port = 3152;  // Local port

		// Connect to the server (Local IP and custom port)
		pConnection = session.GetHttpConnection(serverName, INTERNET_FLAG_SECURE, INTERNET_DEFAULT_HTTPS_PORT);

		// Open a request to the server
		pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, apiEndpoint, NULL, 1, NULL, NULL, INTERNET_FLAG_SECURE);
		//CHttpConnection::HTTP_VERB_POST, loginAPI, NULL, 1, NULL, NULL, INTERNET_FLAG_SECURE

		// Prepare multipart form-data boundary
		CString boundary = _T("---------------------------7de6b36e");
		CString headers;
		headers.Format(_T("Content-Type: multipart/form-data; boundary=%s\r\n"), boundary);

		// Create body for multipart form-data
		CString body;

		CString token = theApp.GetSavedLoginToken();
		//AfxMessageBox(token);
		// Part 1: Add user token to the body
		//body += _T("--") + boundary + _T("\r\n");
		//body += _T("Content-Disposition: form-data; name=\"token\"\r\n\r\n");
		//body += token + _T("\r\n");

		// Part 2: Add file content to the body
		body += _T("--") + boundary + _T("\r\n");
		body += _T("Content-Disposition: form-data; name=\"log\"; filename=\"") + logFileName + _T("\"\r\n");
		//body += _T("Content-Type: text/plain\r\n\r\n");
		body += _T("Content-Type: application/octet-stream\r\n\r\n");

		// Read the log file
		/*std::ifstream logFile(logFilePath, std::ios::binary);
		if (!logFile)
		{
			AfxMessageBox(_T("Failed to open log file."));
			return;
		}*/

		// Step 3: Open the UTF-8 file to read its content
		CStdioFile logFile;
		if (!logFile.Open(logFilePath, CFile::modeRead | CFile::typeBinary)) {
			AfxMessageBox(_T("Failed to open the log file for reading."));
			//return false;
		}

		// Step 4: Read the file content into memory
		ULONGLONG fileSize = logFile.GetLength();
		BYTE* buffer = new BYTE[(UINT)fileSize];
		logFile.Read(buffer, (UINT)fileSize);
		logFile.Close();

		//std::string __fileContent((std::istreambuf_iterator<char>(logFile)), std::istreambuf_iterator<char>());
		//CString fileContentCString(__fileContent.c_str());
		//CString __fileContent = allInfoJson();


		//AfxMessageBox(fileContentCString);

		// Output to the debugger console
		//OutputDebugString(__fileContent);

		//CStringA __fileContentUtf8Data(CW2A(__fileContent.GetString(), CP_UTF8));  // Convert to UTF-8 for transfer
		
		// Step 6: Prepare the data to send (including the file)
		std::string dataToSend = CT2A(body);
		dataToSend.append(reinterpret_cast<char*>(buffer), (size_t)fileSize);

		
		//body += fileContentCString;  // Add the file content to the body


		//logFile.close();

		// Part 3: End of multipart form-data
		dataToSend += "\r\n-----------------------------7de6b36e--\r\n";

		// Step 5: Convert UTF-8 back to CString (UTF-16)
		int sizeNeededForWide = MultiByteToWideChar(CP_UTF8, 0, dataToSend.c_str(), -1, nullptr, 0);
		CString result;
		MultiByteToWideChar(CP_UTF8, 0, dataToSend.c_str(), -1, result.GetBuffer(sizeNeededForWide - 1), sizeNeededForWide - 1);
		result.ReleaseBuffer();

		// Step 6: Display the read content in a message box
		//AfxMessageBox(result);

		

		// Add headers and send request
		pFile->AddRequestHeaders(headers);
		CString tokenHeader;
		//std::string tokenString = CStringA(token);
		tokenHeader = L"Authorization: Bearer " + token;
		//AfxMessageBox(tokenHeader);
		pFile->AddRequestHeaders(tokenHeader);
		// Set headers
		//pFile->AddRequestHeaders(_T("Content-Type: application/json\r\n"));
		//pFile->AddRequestHeaders(_T("Accept: application/json\r\n"));
		//body = _T("{\"email\":\"ahnaf@uxd.co.jp\", \"password\":\"Test123!\"}");
		std::string jsonansi = CStringA(body);
		//AfxMessageBox(body);
		BOOL bRequestSent = pFile->SendRequest(NULL, 0, (LPVOID)dataToSend.c_str(), dataToSend.length());

		if (!bRequestSent)
		{
			AfxMessageBox(_T("Failed to send request."));
			//return false;
		}

		// Check server response status code
		DWORD statusCode = 0;
		pFile->QueryInfoStatusCode(statusCode);

		if (statusCode == HTTP_STATUS_OK)
		{
			//AfxMessageBox(_T("Log file uploaded successfully."));
			// Optionally, log the response from the server
			CString serverResponse;
			char responseBuffer[1024];
			UINT bytesRead;
			while ((bytesRead = pFile->Read(responseBuffer, sizeof(responseBuffer) - 1)) > 0)
			{
				responseBuffer[bytesRead] = 0;  // Null-terminate the buffer
				serverResponse += CString(responseBuffer);
			}
			//AfxMessageBox(serverResponse);
			// Use GetValueByKey to extract values
			CString message = GetValueByKey(serverResponse, _T("message"));
			MessageBoxW(message, L"Success", MB_OK | MB_ICONINFORMATION);
			//return true;
		}
		else
		{
			CString errorMessage;
			errorMessage.Format(_T("Error: HTTP status code %lu"), statusCode);
			//AfxMessageBox(errorMessage);

			// Optionally, log the response from the server
			CString serverResponse;
			char responseBuffer[1024];
			UINT bytesRead;
			while ((bytesRead = pFile->Read(responseBuffer, sizeof(responseBuffer) - 1)) > 0)
			{
				responseBuffer[bytesRead] = 0;  // Null-terminate the buffer
				serverResponse += CString(responseBuffer);
			}

			//AfxMessageBox(serverResponse);

			// Use GetValueByKey to extract values
			CString message = GetValueByKey(serverResponse, _T("message"));
			AfxMessageBox(message + L"\n" + errorMessage);

			//return false;

		}

		// Cleanup
		pFile->Close();
		pConnection->Close();
		//return true;
	}
	catch (CInternetException* e)
	{
		TCHAR errorMessage[256];
		e->GetErrorMessage(errorMessage, 256);

		// Show detailed error message in a message box
		CString fullErrorMessage;
		fullErrorMessage.Format(_T("Internet Exception: %s"), errorMessage);
		AfxMessageBox(fullErrorMessage);

		e->Delete();
		//return false;
	}
	catch (CFileException* e)
	{
		// Handle file-related exceptions
		TCHAR errorMessage[256];
		e->GetErrorMessage(errorMessage, 256);
		AfxMessageBox(CString("File Exception: ") + errorMessage);
		e->Delete();
		//return false;
	}
	catch (...)
	{
		AfxMessageBox(_T("An unknown error occurred."));
		//return false;
	}

	// Ensure session is closed properly
	if (pFile) pFile->Close();
	if (pConnection) pConnection->Close();
	return true;
}



void CPCICTMFCDlg::OnBnClickedMfcmenubutton1()
{
	// TODO: Add your control notification handler code here
	profileDlg prdlg;

	// Get the position of the "Profile" button
	CRect buttonRect;
	CWnd* pButton = GetDlgItem(IDC_MFCMENUBUTTON1); // Ensure the correct control ID is used
	if (pButton)
	{
		pButton->GetWindowRect(&buttonRect); // Get button's screen coordinates
	}
	else
	{
		// Handle the case where pButton is null
		AfxMessageBox(_T("Profile button not found!"));
		return;
	}

	// Move the profile dialog to the position under the button
	theApp.prdlgX = buttonRect.left - 3;  // X position of the button
	theApp.prdlgY = buttonRect.top; // Y position just below the button
	//CString posChk;
	//posChk.Format(L"X: %d and Y: %d",theApp.prdlgX, theApp.prdlgY);		

	//AfxMessageBox(posChk);


	// Move the dialog to the desired position
	//prdlg.MoveWindow(xPos, yPos, 0, 0);
	//prdlg.SetWindowPos(NULL, xPos, yPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	prdlg.DoModal();
}

void CPCICTMFCDlg::PostNcDestroy()
{
	delete this;
}



void CPCICTMFCDlg::OnBnClickedButtonUpload()
{
	if (isCPUTested == false && isKeyboardTested == false)
	{
		AfxMessageBox(_T("Please test the CPU and keyboard before uploading the log"));
		return;
	}
	else if (isCPUTested == false && isKeyboardTested == true)
	{
		AfxMessageBox(_T("Please test the CPU before uploading the log"));
		return;
	}
	else if (isCPUTested == true && isKeyboardTested == false)
	{
		AfxMessageBox(_T("Please test the Keyboard before uploading the log"));
		return;
	}

	strAllInfoJson = allInfoJson();

	// Call the function to save the log and json content
	bool isSaved = SaveToFile(strAllInfoJson);

	if (isSaved)
	{
		UploadLogFile(logPath);
	}
	else
	{
		AfxMessageBox(_T("Failed to save the log file."));
	}

}

void CPCICTMFCDlg::get_all_pc_info()
{
	//all data initialize here//
	{
		HRESULT hres;

		// Initialize COM
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres)) {
			return;
		}

		// Set COM security levels
		hres = CoInitializeSecurity(
			NULL, -1, NULL, NULL,
			RPC_C_AUTHN_LEVEL_DEFAULT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL, EOAC_NONE, NULL
		);

		if (FAILED(hres)) {
			CoUninitialize();
			return;
		}

		// Obtain the initial locator to WMI
		IWbemLocator* pLoc = NULL;
		hres = CoCreateInstance(
			CLSID_WbemLocator, 0,
			CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc
		);

		if (FAILED(hres)) {
			CoUninitialize();
			return;
		}

		// Connect to WMI
		IWbemServices* pSvc = NULL;
		hres = pLoc->ConnectServer(
			_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0,
			NULL, 0, 0, &pSvc
		);

		if (FAILED(hres)) {
			pLoc->Release();
			CoUninitialize();
			return;
		}

		// Set security levels on the proxy
		hres = CoSetProxyBlanket(
			pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE,
			NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL, EOAC_NONE
		);

		if (FAILED(hres)) {
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return;
		}

		IEnumWbemClassObject* pEnumerator = NULL;
		IWbemClassObject* pclsObj = NULL;
		ULONG uReturn = 0;
		VARIANT vtProp;

		// Query Device Name
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_ComputerSystem"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				// Retrieve Device Name
				pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				deviceName = vtProp.bstrVal;
				VariantClear(&vtProp);

				// Retrieve Device Model
				pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
				deviceModel = vtProp.bstrVal;
				VariantClear(&vtProp);


				pclsObj->Release();
			}
			pEnumerator->Release();
		}

		// Query Device Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_ComputerSystemProduct"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;


				// Retrieve Device Manufacturer
				pclsObj->Get(L"Vendor", 0, &vtProp, 0, 0);
				deviceManufacturer = vtProp.bstrVal;
				VariantClear(&vtProp);

				// Retrieve Device Serial Number
				pclsObj->Get(L"IdentifyingNumber", 0, &vtProp, 0, 0);
				deviceSerialNumber = vtProp.bstrVal;
				VariantClear(&vtProp);

				// Retrieve Device UUID
				pclsObj->Get(L"UUID", 0, &vtProp, 0, 0);
				deviceUUID = vtProp.bstrVal;
				VariantClear(&vtProp);


				pclsObj->Release();
			}
			pEnumerator->Release();
		}

		// Query BIOS Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_BIOS"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				// BIOS Data
				pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
				biosVersion = vtProp.bstrVal;
				VariantClear(&vtProp);

				pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				biosManufacturer = vtProp.bstrVal;
				VariantClear(&vtProp);

				/*pclsObj->Get(L"ReleaseDate", 0, &vtProp, 0, 0);
				g_biosReleaseDate = vtProp.bstrVal;
				VariantClear(&vtProp);*/

				// BIOS Release Date
				pclsObj->Get(L"ReleaseDate", 0, &vtProp, 0, 0);
				if (vtProp.vt == VT_BSTR) {
					CString strReleaseDate(vtProp.bstrVal);
					CString year = strReleaseDate.Mid(0, 4);
					CString month = strReleaseDate.Mid(4, 2);
					CString day = strReleaseDate.Mid(6, 2);
					CString formattedDate;
					formattedDate.Format(_T("%s-%s-%s"), year, month, day);

					biosReleaseDate = formattedDate;
				}
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}

		// Query CPU Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_Processor"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				// CPU Data
				pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				cpuName = vtProp.bstrVal;
				VariantClear(&vtProp);

				pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				cpuManufacturer = vtProp.bstrVal;
				VariantClear(&vtProp);

				pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
				cpuClockSpeed.Format(_T("%d MHz"), vtProp.intVal);
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}

		// Query RAM Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_PhysicalMemory"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			int ramSlotCounts = 0;
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				ramSlotCounts++;

				// RAM Data
				pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				ramManufacturers += CString(vtProp.bstrVal) + _T(", ");
				VariantClear(&vtProp);

				// Retrieve the Capacity property
				pclsObj->Get(L"Capacity", 0, &vtProp, 0, 0);			// Convert BSTR to __int64 and calculate capacity in GB
				__int64 capacityGB = _wtoi64(vtProp.bstrVal) / (1024 * 1024 * 1024);
				// Format the capacity as a CString
				CString capacityStr;
				capacityStr.Format(_T("%lld GB, "), capacityGB);
				// Concatenate the formatted string to g_ramSizes
				ramSizes += capacityStr;
				VariantClear(&vtProp);


				pclsObj->Release();
			}
			ramManufacturers.TrimRight(_T(", "));
			ramSizes.TrimRight(_T(", "));
			ramSlotCount.Format(_T("%d"), ramSlotCounts);
			pEnumerator->Release();
		}

		// Query Storage Device Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_DiskDrive"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				// Storage Data
				pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
				storageDeviceNames += CString(vtProp.bstrVal) + _T(", ");
				VariantClear(&vtProp);

				// Retrieve the Size property
				pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
				// Convert BSTR to __int64 and calculate size in GB
				__int64 sizeGB = _wtoi64(vtProp.bstrVal) / (1024 * 1024 * 1024);
				// Format the size as a CString
				CString sizeStr;
				sizeStr.Format(_T("%lld GB, "), sizeGB);
				// Concatenate the formatted string to g_storageDeviceSizes
				storageDeviceSizes += sizeStr;
				VariantClear(&vtProp);

				pclsObj->Get(L"MediaType", 0, &vtProp, 0, 0);
				storageDeviceTypes += CString(vtProp.bstrVal) + _T(", ");
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			storageDeviceNames.TrimRight(_T(", "));
			storageDeviceSizes.TrimRight(_T(", "));
			storageDeviceTypes.TrimRight(_T(", "));
			pEnumerator->Release();
		}

		// Query OS Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_OperatingSystem"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				// OS Data
				pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
				osName = vtProp.bstrVal;
				VariantClear(&vtProp);

				pclsObj->Get(L"BuildNumber", 0, &vtProp, 0, 0);
				kernel = vtProp.bstrVal;
				VariantClear(&vtProp);

				pclsObj->Get(L"OSArchitecture", 0, &vtProp, 0, 0);
				arch = vtProp.bstrVal;
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}

		

		// Query WiFi Information
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_NetworkAdapter WHERE NetConnectionStatus = 2 OR AdapterType = 'Ethernet 802.3' AND PhysicalAdapter = TRUE AND DeviceId = 1"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator);

		if (SUCCEEDED(hres)) {
			while (pEnumerator) {
				HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) break;

				// Get WiFi Adapter Name
				pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wifiName = vtProp.bstrVal;
				//AfxMessageBox(wifiName);
				VariantClear(&vtProp);

				// Get WiFi Manufacturer
				pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				wifiManufacturer = vtProp.bstrVal;
				//AfxMessageBox(wifiManufacturer);
				VariantClear(&vtProp);

				// Get WiFi Manufacturer
				pclsObj->Get(L"MACAddress", 0, &vtProp, 0, 0);
				wifiMacAddress = vtProp.bstrVal;
				//AfxMessageBox(wifiManufacturer);
				VariantClear(&vtProp);

				pclsObj->Release();
			}
			pEnumerator->Release();
		}


		// Execute WMI query to retrieve Bluetooth adapter details
		//IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_PnPEntity WHERE Name LIKE '%Bluetooth%' AND Status = 'OK' AND Service = 'BTHUSB'"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL, &pEnumerator
		);
		if (FAILED(hres)) {
			//std::wcout << L"Query failed." << std::endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return;
		}

		// Retrieve and display Bluetooth adapter information
		//IWbemClassObject* pclsObj = NULL;
		//ULONG uReturn = 0;
		bool adapterFound = false;

		if (pEnumerator) {
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (uReturn) {
				adapterFound = true;
				VARIANT vtProp;

				// Get Adapter Name
				hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hr)) {
					bluetoothName = vtProp.bstrVal;
					//AfxMessageBox(bluetoothName);
				}
				VariantClear(&vtProp);

				// Get Manufacturer
				hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hr)) {
					bluetoothManufacturer = vtProp.bstrVal;
				}
				VariantClear(&vtProp);

				// Get PNP Device ID
				hr = pclsObj->Get(L"PNPDeviceID", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hr)) {
					//std::wcout << L"PNP Device ID: " << vtProp.bstrVal << std::endl;
				}
				VariantClear(&vtProp);

				// Additional Bluetooth Properties (like MAC address)
				hr = pclsObj->Get(L"MACAddress", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hr) && vtProp.vt == VT_BSTR) {
					//std::wcout << L"MAC Address: " << vtProp.bstrVal << std::endl;
				}
				else {
					//std::wcout << L"MAC Address not available." << std::endl;
				}
				VariantClear(&vtProp);

				pclsObj->Release();
			}
		}
		if (SUCCEEDED(hres)) {
			CString cameraNames, cameraInstanceIds;
			int cameraCount = 0;

			// Query Camera Devices (Filtered by Name containing 'Camera')
			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT * FROM Win32_PnPEntity WHERE Name LIKE '%Camera%'"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pEnumerator
			);

			if (FAILED(hres)) {
				AfxMessageBox(_T("Query for camera devices failed"));
				pSvc->Release();
				pLoc->Release();
				CoUninitialize();
				return;
			}

			IWbemClassObject* pclsObj = NULL;
			ULONG uReturn = 0;
			VARIANT vtProp;

			// Enumerate through the results
			while (pEnumerator) {
				hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn)
					break;

				cameraCount++;

				// Retrieve the Name property (camera name)
				pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				cameraName = CString(vtProp.bstrVal); // Update global cameraName
				VariantClear(&vtProp);

				// Retrieve the Manufacturer property (camera manufacturer)
				pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
				cameraManufacturer = CString(vtProp.bstrVal); // Update global cameraManufacturer
				VariantClear(&vtProp);

				pclsObj->Release();
			}

			// Trim trailing comma and space from camera names and IDs
			cameraNames.TrimRight(_T(", "));
			cameraInstanceIds.TrimRight(_T(", "));

			// Optionally, display a message box (if you still need this for debugging)
	/*		CString cameraSummary;
			cameraSummary.Format(_T("Found %d Cameras:\nNames: %s\nInstance IDs: %s"), cameraCount, cameraNames, cameraInstanceIds);
			AfxMessageBox(cameraSummary);*/

			pEnumerator->Release();
		}


		if (SUCCEEDED(hres)) {
			CComPtr<IWbemLocator> pLoc;
			hres = CoCreateInstance(
				CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
			if (FAILED(hres)) {
				//AfxMessageBox(_T("Failed to create IWbemLocator instance"));
				CoUninitialize();
				return;
			}

			CComPtr<IWbemServices> pSvc;
			hres = pLoc->ConnectServer(
				_bstr_t(L"ROOT\\WMI"), // Use correct namespace
				NULL, NULL, 0, NULL, 0, 0, &pSvc
			);
			if (FAILED(hres)) {
				//AfxMessageBox(_T("Failed to connect to WMI namespace"));
				CoUninitialize();
				return;
			}

			hres = CoSetProxyBlanket(
				pSvc,                        // the proxy to set
				RPC_C_AUTHN_WINNT,           // authentication service
				RPC_C_AUTHZ_NONE,            // authorization service
				NULL,                        // server principal name
				RPC_C_AUTHN_LEVEL_CALL,      // authentication level
				RPC_C_IMP_LEVEL_IMPERSONATE, // impersonation level
				NULL,                        // client identity
				EOAC_NONE                    // proxy capabilities
			);
			if (FAILED(hres)) {
				//AfxMessageBox(_T("Failed to set proxy blanket"));
				CoUninitialize();
				return;
			}

			// Query for BatteryStaticData
			CComPtr<IEnumWbemClassObject> pEnumerator;
			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT DeviceName, ManufactureName, Chemistry, DesignedCapacity FROM BatteryStaticData"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pEnumerator
			);
			if (FAILED(hres)) {
				CString errorMsg;
				errorMsg.Format(_T("Failed to execute WMI query for BatteryStaticData. HRESULT: 0x%08X"), hres);
				//AfxMessageBox(errorMsg);
				CoUninitialize();
				return;
			}

			IWbemClassObject* pclsObj = NULL;
			ULONG uReturn = 0;
			VARIANT vtProp;
			bool hasData = false;

			while (pEnumerator) {
				hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) {
					break; // No more objects
				}

				hasData = true;
				CString batteryDetails;

				// Retrieve DeviceName
				hres = pclsObj->Get(L"DeviceName", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_BSTR && vtProp.bstrVal != nullptr) {
					batteryDetails.AppendFormat(_T("Device Name: %s\n"), vtProp.bstrVal);
					batteryDeviceName = CString(vtProp.bstrVal);
				}
				else {
					batteryDetails.AppendFormat(_T("Device Name: Not Available\n"));
				}
				VariantClear(&vtProp);
				// Retrieve DeviceName
				hres = pclsObj->Get(L"ManufactureName", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_BSTR && vtProp.bstrVal != nullptr) {
					batteryDetails.AppendFormat(_T("Manufacture Name: %s\n"), vtProp.bstrVal);
					batteryManufacturer = CString(vtProp.bstrVal);
				}
				else {
					batteryDetails.AppendFormat(_T("Manufacture Name: Not Available\n"));
				}
				VariantClear(&vtProp);
				// Retrieve Chemistry from Win32_Battery using the correct namespace
				CComPtr<IWbemServices> pSvcCIMV2;
				hres = pLoc->ConnectServer(
					_bstr_t(L"ROOT\\CIMV2"), // Correct namespace
					NULL, NULL, 0, NULL, 0, 0, &pSvcCIMV2
				);
				if (FAILED(hres)) {
					//AfxMessageBox(_T("Failed to connect to WMI namespace ROOT\\CIMV2 for Chemistry"));
					CoUninitialize();
					return;
				}

				CComPtr<IEnumWbemClassObject> pChemistryEnumerator;
				hres = pSvcCIMV2->ExecQuery(
					bstr_t("WQL"),
					bstr_t("SELECT Chemistry FROM Win32_Battery"),
					WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
					NULL, &pChemistryEnumerator
				);
				if (FAILED(hres)) {
					CString errorMsg;
					errorMsg.Format(_T("Failed to execute WMI query for Chemistry in ROOT\\CIMV2. HRESULT: 0x%08X"), hres);
					//AfxMessageBox(errorMsg);
					CoUninitialize();
					return;
				}

				bool chemistryDataFound = false;
				while (pChemistryEnumerator) {
					IWbemClassObject* pclsObj = nullptr; // Separate object pointer for this loop
					hres = pChemistryEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
					if (0 == uReturn) {
						break; // No more objects
					}

					if (SUCCEEDED(hres) && pclsObj) {
						chemistryDataFound = true;
						hres = pclsObj->Get(L"Chemistry", 0, &vtProp, 0, 0);
						if (SUCCEEDED(hres) && vtProp.vt == VT_I4) {
							switch (vtProp.intVal) {
							case 1: chemistryType = _T("Other"); break;
							case 2: chemistryType = _T("Lithium Ion"); break;
							case 3: chemistryType = _T("Lead Acid"); break;
							case 4: chemistryType = _T("Nickel Cadmium"); break;
							case 5: chemistryType = _T("Nickel Metal Hydride"); break;
							case 6: chemistryType = _T("Lithium Ion"); break;
							case 7: chemistryType = _T("Zinc Air"); break;
							case 8: chemistryType = _T("Lithium Polymer"); break;
							default: chemistryType = _T("Unspecified Chemistry"); break;
							}
							batteryDetails.AppendFormat(_T("Chemistry: %s\n"), chemistryType);
							batteryChemistry = vtProp.intVal;
						}
						else {
							batteryDetails.AppendFormat(_T("Chemistry: Not Available\n"));
						}
						VariantClear(&vtProp);
					}
					if (pclsObj) {
						pclsObj->Release(); // Release after using it
						pclsObj = nullptr; // Reset pointer
					}
				}

				if (!chemistryDataFound) {
					//AfxMessageBox(_T("No data available for Chemistry in Win32_Battery"));
				}



				// Display the gathered information
				//AfxMessageBox(batteryDetails);
				pclsObj->Release(); // Release after using it
			}

			if (!hasData) {
				//AfxMessageBox(_T("No data available for BatteryStaticData"));
			}

			// Query for TimeOnBattery and TimeToFullCharge
			CComPtr<IEnumWbemClassObject> pBatteryEnumerator;
			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT TimeOnBattery, TimeToFullCharge FROM Win32_Battery"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pBatteryEnumerator
			);
			if (FAILED(hres)) {
				CString errorMsg;
				errorMsg.Format(_T("Failed to execute WMI query for TimeOnBattery and TimeToFullCharge. HRESULT: 0x%08X"), hres);
				//AfxMessageBox(errorMsg);
				CoUninitialize();
				return;
			}

			bool hasBatteryTimingData = false;

			while (pBatteryEnumerator) {
				hres = pBatteryEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) {
					break; // No more objects
				}

				hasBatteryTimingData = true;
				CString timingDetails;

				// Retrieve TimeOnBattery
				hres = pclsObj->Get(L"TimeOnBattery", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_UI4) {
					timingDetails.AppendFormat(_T("Time On Battery: %u seconds\n"), vtProp.uintVal);
				}
				else {
					timingDetails.AppendFormat(_T("Time On Battery: Not Available or retrieval failed.\n"));
				}
				VariantClear(&vtProp);

				// Retrieve TimeToFullCharge
				hres = pclsObj->Get(L"TimeToFullCharge", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_UI4) {
					timingDetails.AppendFormat(_T("Time To Full Charge: %u seconds\n"), vtProp.uintVal);
				}
				else {
					timingDetails.AppendFormat(_T("Time To Full Charge: Not Available or retrieval failed.\n"));
				}
				VariantClear(&vtProp);

				// Display the gathered information
				//AfxMessageBox(timingDetails);

				pclsObj->Release(); // Release after using it
			}

			if (!hasBatteryTimingData) {
				//AfxMessageBox(_T("No data available for TimeOnBattery or TimeToFullCharge"));
			}



			// Query for BatteryFullChargedCapacity
			CComPtr<IEnumWbemClassObject> pFullChargeEnumerator;
			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT FullChargedCapacity FROM BatteryFullChargedCapacity"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pFullChargeEnumerator
			);
			if (FAILED(hres)) {
				CString errorMsg;
				errorMsg.Format(_T("Failed to execute WMI query for BatteryFullChargedCapacity. HRESULT: 0x%08X"), hres);
				//AfxMessageBox(errorMsg);
				CoUninitialize();
				return;
			}

			hasData = false;

			while (pFullChargeEnumerator) {
				hres = pFullChargeEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) {
					break; // No more objects
				}

				hasData = true;
				CString fullChargeDetails;
				hres = pclsObj->Get(L"FullChargedCapacity", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_I4) {
					fullChargeDetails.AppendFormat(_T("Full Charged Capacity: %d mWh\n"), vtProp.intVal);
					fullChargedCapacity = vtProp.intVal;

				}
				else {
					fullChargeDetails.AppendFormat(_T("Full Charged Capacity: Not Available\n"));
				}
				VariantClear(&vtProp);

				// Display the gathered information
				//AfxMessageBox(fullChargeDetails);
				pclsObj->Release(); // Release after using it
			}


			if (!hasData) {
				//AfxMessageBox(_T("No data available for BatteryFullChargedCapacity"));
			}

			// Query for BatteryCycleCount
			CComPtr<IEnumWbemClassObject> pCycleCountEnumerator;
			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT CycleCount FROM BatteryCycleCount"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pCycleCountEnumerator
			);
			if (FAILED(hres)) {
				CString errorMsg;
				errorMsg.Format(_T("Failed to execute WMI query for BatteryCycleCount. HRESULT: 0x%08X"), hres);
				//AfxMessageBox(errorMsg);
				CoUninitialize();
				return;
			}

			hasData = false;

			while (pCycleCountEnumerator) {
				hres = pCycleCountEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) {
					break; // No more objects
				}

				hasData = true;
				CString cycleCountDetails;
				hres = pclsObj->Get(L"CycleCount", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_I4) {
					cycleCountDetails.AppendFormat(_T("Cycle Count: %d\n"), vtProp.intVal);
					cycleCount = vtProp.intVal;
	
				}
				else {
					cycleCountDetails.AppendFormat(_T("Cycle Count: Not Available\n"));
				}
				VariantClear(&vtProp);

				// Display the gathered information
				//AfxMessageBox(cycleCountDetails);
				pclsObj->Release(); // Release after using it
			}

			if (!hasData) {
				//AfxMessageBox(_T("No data available for BatteryCycleCount"));
			}

			// Query for BatteryStatus
			CComPtr<IEnumWbemClassObject> pCurrentCapacityEnumerator;
			hres = pSvc->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT RemainingCapacity FROM BatteryStatus"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pCurrentCapacityEnumerator
			);
			if (FAILED(hres)) {
				CString errorMsg;
				errorMsg.Format(_T("Failed to execute WMI query for BatteryStatus. HRESULT: 0x%08X"), hres);
				//AfxMessageBox(errorMsg);
				CoUninitialize();
				return;
			}

			hasData = false;

			while (pCurrentCapacityEnumerator) {
				hres = pCurrentCapacityEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
				if (0 == uReturn) {
					break; 
				}

				hasData = true;
				CString currentCapacityDetails;
				hres = pclsObj->Get(L"RemainingCapacity", 0, &vtProp, 0, 0);
				if (SUCCEEDED(hres) && vtProp.vt == VT_I4) {
					currentCapacityDetails.AppendFormat(_T("Current Capacity: %d mWh\n"), vtProp.intVal);
					currentCapacity = vtProp.intVal;
			
				}
				else {
					currentCapacityDetails.AppendFormat(_T("Current Capacity: Not Available\n"));
				}
				VariantClear(&vtProp);

				//AfxMessageBox(currentCapacityDetails);
				pclsObj->Release();
			}

			if (!hasData) {
				//AfxMessageBox(_T("No data available for BatteryStatus"));
			}
			CComPtr<IWbemLocator> pLocator;
			HRESULT hLocatorResult = CoCreateInstance(
				CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
			if (FAILED(hLocatorResult) || !pLocator) {
				//AfxMessageBox(_T("Failed to create IWbemLocator instance"));
				CoUninitialize();
				return;
			}

			CComPtr<IWbemServices> pServices;
			HRESULT hConnectResult = pLocator->ConnectServer(
				_bstr_t(L"ROOT\\CIMV2"), // Connect to the namespace
				NULL, NULL, 0, NULL, 0, 0, &pServices
			);
			if (FAILED(hConnectResult) || !pServices) {
				//AfxMessageBox(_T("Failed to connect to WMI namespace"));
				CoUninitialize();
				return;
			}

			HRESULT hProxyResult = CoSetProxyBlanket(
				pServices,                        // the proxy to set
				RPC_C_AUTHN_WINNT,                // authentication service
				RPC_C_AUTHZ_NONE,                 // authorization service
				NULL,                             // server principal name
				RPC_C_AUTHN_LEVEL_CALL,           // authentication level
				RPC_C_IMP_LEVEL_IMPERSONATE,      // impersonation level
				NULL,                             // client identity
				EOAC_NONE                         // proxy capabilities
			);
			if (FAILED(hProxyResult)) {
				//AfxMessageBox(_T("Failed to set proxy blanket"));
				CoUninitialize();
				return;
			}

			// Query for DesignCapacity using Win32_PortableBattery
			CComPtr<IEnumWbemClassObject> pEnumerator1;
			HRESULT hQueryResult = pServices->ExecQuery(
				bstr_t("WQL"),
				bstr_t("SELECT DesignCapacity FROM Win32_PortableBattery"),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
				NULL, &pEnumerator1
			);
			if (FAILED(hQueryResult) || !pEnumerator1) {
				CString errorMsg;
				errorMsg.Format(_T("Failed to execute WMI query for DesignCapacity in Win32_PortableBattery. HRESULT: 0x%08X"), hQueryResult);
				//AfxMessageBox(errorMsg);
				CoUninitialize();
				return;
			}

			bool bDesignCapacityFound = false;
			CComPtr<IWbemClassObject> pObject;
			ULONG uObjectCount = 0;
			VARIANT vDesignCapacity;
			VariantInit(&vDesignCapacity);

			while (true) {
				HRESULT hNextResult = pEnumerator1->Next(WBEM_INFINITE, 1, &pObject, &uObjectCount);
				if (FAILED(hNextResult) || uObjectCount == 0) {
					break; // Stop if there are no more objects or operation fails
				}

				if (pObject) {
					bDesignCapacityFound = true;

					HRESULT hGetResult = pObject->Get(L"DesignCapacity", 0, &vDesignCapacity, 0, 0);
					if (SUCCEEDED(hGetResult) && vDesignCapacity.vt == VT_I4) {
						CString designCapacityMsg;
						designCapacityMsg.Format(_T("Design Capacity (Win32_PortableBattery): %d mWh\n"), vDesignCapacity.intVal);
						designedCapacity = vDesignCapacity.intVal;
				
						if (designedCapacity > 0 && fullChargedCapacity > 0) {
							double degradationRate = ((double)(designedCapacity - fullChargedCapacity) / designedCapacity) * 100.0;

							// Format degradation rate with 2 decimal places and a percentage sign
							degradationRateMsg.Format(L"%d%%", int(degradationRate));
							batteryHealth.Format(_T("%d%%"), (100 - int(degradationRate)));
				
							// Optionally display it
							//AfxMessageBox(degradationRateMsg);
						}
						//AfxMessageBox(designCapacityMsg);
					}
					else {
						//AfxMessageBox(_T("Design Capacity not available in Win32_PortableBattery data."));
					}

					VariantClear(&vDesignCapacity); // Clear VARIANT to avoid memory leaks
					pObject.Release();             // Explicitly release the object
				}
			}

			if (!bDesignCapacityFound) {
				//AfxMessageBox(_T("No data available for DesignCapacity in Win32_PortableBattery"));
			}


		}

		// Get PC user name
		TCHAR userName[UNLEN + 1];
		DWORD userNameSize = UNLEN + 1;
		if (GetUserName(userName, &userNameSize)) {
			pcUserName = userName;
		}

		// Query MAC Address Information
		ULONG outBufLen = sizeof(IP_ADAPTER_INFO);
		IP_ADAPTER_INFO* pAdapterInfo = (IP_ADAPTER_INFO*)malloc(outBufLen);

		if (GetAdaptersInfo(pAdapterInfo, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
			free(pAdapterInfo);
			pAdapterInfo = (IP_ADAPTER_INFO*)malloc(outBufLen);
		}

		if (GetAdaptersInfo(pAdapterInfo, &outBufLen) == NO_ERROR) {
			deviceMACAddress.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"),
				pAdapterInfo->Address[0], pAdapterInfo->Address[1], pAdapterInfo->Address[2],
				pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
		}

		if (pAdapterInfo) free(pAdapterInfo);

		BYTE buffer[1];
		DWORD result = GetFirmwareEnvironmentVariable(L"", L"{00000000-0000-0000-0000-000000000000}", buffer, sizeof(buffer));

		if (result != 0 || GetLastError() != ERROR_INVALID_FUNCTION) {
			uefiBios = _T("UEFI");
		}
		else {
			uefiBios = _T("Legacy BIOS");
		}

		// Cleanup
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}

	// all initialize end here//
}

void CPCICTMFCDlg::all_tree_drawing()
{
	HTREEITEM hPC, hRAM, hCPU, hStorage, hDevice, hBIOS, hOS, hCamera, hBluetooth, hWifi, hEnd, hBattery;

	// Add root item
	hPC = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"全てのPC情報" : L"All PC Information");

	// Add child items
	hDevice = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイス情報" : L"Device Information", hPC);
	hCPU = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"CPU情報" : L"CPU Information", hPC);
	hStorage = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"ストレージ情報" : L"Storage Information", hPC);
	hRAM = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"RAM情報" : L"RAM Information", hPC);
	hBIOS = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"BIOS情報" : L"BIOS Information", hPC);
	hOS = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"オペレーティングシステム" : L"Operating System", hPC);
	hCamera = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"カメラインフォメーション" : L"Camera Information", hPC);
	hBluetooth = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"Bluetooth情報" : L"Bluetooth Information", hPC);
	hWifi = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"Wi-Fi情報" : L"WiFi Information", hPC);
	hBattery = m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"バッテリー情報" : L"Battery Information", hPC);
	hEnd = m_treeCtrl.InsertItem(L"", hPC);

	// Add sub-child items with language-specific text
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイス名: " + deviceName : L"Device Name: " + deviceName, hDevice);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイスUUID: " + deviceUUID : L"Device UUID: " + deviceUUID, hDevice);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイスメーカー: " + deviceManufacturer : L"Device Manufacturer: " + deviceManufacturer, hDevice);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイスモデル: " + deviceModel : L"Device Model: " + deviceModel, hDevice);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイスシリアル番号: " + deviceSerialNumber : L"Device Serial Number: " + deviceSerialNumber, hDevice);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"デバイスMACアドレス: " + deviceMACAddress : L"Device MAC Address: " + deviceMACAddress, hDevice);

	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"CPU名: " + cpuName : L"CPU Name: " + cpuName, hCPU);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"CPUクロックスピード: " + cpuClockSpeed : L"CPU Clock Speed: " + cpuClockSpeed, hCPU);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"CPUメーカー: " + cpuManufacturer : L"CPU Manufacturer: " + cpuManufacturer, hCPU);

	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"BIOSファームウェア: " + uefiBios : L"BIOS Firmware: " + uefiBios, hBIOS);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"BIOSバージョン: " + biosVersion : L"BIOS Version: " + biosVersion, hBIOS);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"BIOSメーカー: " + biosManufacturer : L"BIOS Manufacturer: " + biosManufacturer, hBIOS);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"BIOSリリース日: " + biosReleaseDate : L"BIOS Release Date: " + biosReleaseDate, hBIOS);

	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"RAMメーカー: " + ramManufacturers : L"RAM Manufacturer: " + ramManufacturers, hRAM);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"RAM容量: " + ramSizes : L"RAM Capacity: " + ramSizes, hRAM);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"RAMスロット数: " + ramSlotCount : L"RAM Slot Count: " + ramSlotCount, hRAM);

	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"ストレージデバイス名: " + storageDeviceNames : L"Storage Device Name: " + storageDeviceNames, hStorage);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"ストレージデバイスサイズ: " + storageDeviceSizes : L"Storage Device Size: " + storageDeviceSizes, hStorage);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"ストレージデバイスタイプ: " + storageDeviceTypes : L"Storage Device Type: " + storageDeviceTypes, hStorage);

	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"OS名: " + osName : L"OS Name: " + osName, hOS);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"カーネル: " + kernel : L"Kernel: " + kernel, hOS);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"アーキテクチャ: " + arch : L"Architecture: " + arch, hOS);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"ユーザー名: " + pcUserName : L"User Name: " + pcUserName, hOS);

	// Add camera details
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"カメラ名: " + cameraName : L"Camera Name: " + cameraName, hCamera);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"カメラメーカー: " + cameraManufacturer : L"Camera Manufacturer: " + cameraManufacturer, hCamera);

	// Add Bluetooth info
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"Bluetoothアダプター名: " + bluetoothName : L"Bluetooth Adapter Name: " + bluetoothName, hBluetooth);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"Bluetoothアダプターメーカー: " + bluetoothManufacturer : L"Bluetooth Adapter Manufacturer: " + bluetoothManufacturer, hBluetooth);

	// Add WiFi info
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"Wi-Fiアダプタ名: " + wifiName : L"WiFi Adapter Name: " + wifiName, hWifi);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"Wi-Fiアダプターメーカー: " + wifiManufacturer : L"WiFi Adapter Manufacturer: " + wifiManufacturer, hWifi);

	// Add Battery info
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"バッテリーデバイス名: " + batteryDeviceName : L"Battery Device Name: " + batteryDeviceName, hBattery);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"バッテリーメーカー: " + batteryManufacturer : L"Battery Manufacturer: " + batteryManufacturer, hBattery);

	CString designedCapacityStr = designedCapacity > 0
		? CString(std::to_wstring(designedCapacity).c_str()) + L" mWh"
		: L"N/A";
	CString fullChargedCapacityStr = fullChargedCapacity > 0
		? CString(std::to_wstring(fullChargedCapacity).c_str()) + L" mWh"
		: L"N/A";
	CString currentCapacityStr = currentCapacity > 0
		? CString(std::to_wstring(currentCapacity).c_str()) + L" mWh"
		: L"N/A";
	CString batteryHealthStr = !batteryHealth.IsEmpty()
		? batteryHealth
		: L"N/A";
	CString degradationRateMsgStr = !degradationRateMsg.IsEmpty()
		? degradationRateMsg
		: L"N/A";
	CString cycleCountStr = cycleCount > 0
		? CString(std::to_wstring(cycleCount).c_str())
		: L"N/A";

	// Add battery capacity and health info
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"設計容量: " + designedCapacityStr : L"Designed Capacity: " + designedCapacityStr, hBattery);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"フル充電容量: " + fullChargedCapacityStr : L"Full Charged Capacity: " + fullChargedCapacityStr, hBattery);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"現在の容量: " + currentCapacityStr : L"Current Charge Capacity: " + currentCapacityStr, hBattery);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"バッテリー健康状態: " + batteryHealthStr : L"Battery Health: " + batteryHealthStr, hBattery);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"劣化率: " + degradationRateMsgStr : L"Degradation Rate: " + degradationRateMsgStr, hBattery);
	m_treeCtrl.InsertItem(theApp.language == L"jp" ? L"サイクルカウント: " + cycleCountStr : L"Cycle Count: " + cycleCountStr, hBattery);

	// Expand all the nodes
	m_treeCtrl.Expand(hPC, TVE_EXPAND);
	m_treeCtrl.Expand(hDevice, TVE_EXPAND);
	m_treeCtrl.Expand(hCPU, TVE_EXPAND);
	m_treeCtrl.Expand(hStorage, TVE_EXPAND);
	m_treeCtrl.Expand(hRAM, TVE_EXPAND);
	m_treeCtrl.Expand(hBIOS, TVE_EXPAND);
	m_treeCtrl.Expand(hOS, TVE_EXPAND);
	m_treeCtrl.Expand(hCamera, TVE_EXPAND);
	m_treeCtrl.Expand(hBluetooth, TVE_EXPAND);
	m_treeCtrl.Expand(hWifi, TVE_EXPAND);
	m_treeCtrl.Expand(hBattery, TVE_EXPAND);
}


//void CPCICTMFCDlg::OnBnClickedButton6()
//{
//	// TODO: Add your control notification handler code here
//}

//LRESULT CPCICTMFCDlg::OnShowBenchmarkResult(WPARAM wParam, LPARAM lParam)
//{
//	// Retrieve the message string
//	//CString* pResultMessage = (CString*)lParam;
//
//	// Display the message box
//	//AfxMessageBox(*pResultMessage);
//
//	// Clean up the dynamically allocated CString
//	//delete pResultMessage;
//
//	return 0;
//}


// Start button handler
void CPCICTMFCDlg::OnBnClickedButtonCpuTestStart()
{
	isCPUTested = false;
	SingleBenchmarkResult = 0;
	MultiBenchmarkResult = 0;
	CPU_rating = 0.0;
	m_benchmarkRunning = true;

	// Set up the progress bar
	m_progressCPU.SetRange(0, 100);
	m_progressCPU.SetPos(0);

	// Disable the button during benchmarking
	m_startButton.EnableWindow(FALSE);

	// Hide the button
	m_progressCPU.ShowWindow(SW_SHOW);

	// Run benchmarks sequentially in a thread
	std::thread benchmarkThread([this]() {
		// Run Single-threaded benchmark
		RunSingleThreadedBenchmark();
		m_progressCPU.SetPos(50);

		// Run Multi-threaded benchmark
		RunMultiThreadedBenchmark();
		m_progressCPU.SetPos(100);

		// Calculate the CPU Rating
		CPU_rating = CalculateCPUScore();

		// Update string variables with new values
		singleThreadScoreStr.Format(L"%d", SingleBenchmarkResult);
		multiThreadScoreStr.Format(L"%d", MultiBenchmarkResult);
		cpuRatingStr.Format(L"%.0f", CPU_rating);

		CString singleT, multiT, rating;

		if (theApp.language == L"jp") 
		{
			singleT.Format(L"シングルスレッドスコア: %s", singleThreadScoreStr);
			multiT.Format(L"マルチスレッドスコア: %s", multiThreadScoreStr);
			rating.Format(L"CPU評価: %s / 100", cpuRatingStr);
		}
		else
		{
			singleT.Format(L"Single-Thread Score: %s", singleThreadScoreStr);
			multiT.Format(L"Multi-Thread Score: %s", multiThreadScoreStr);
			rating.Format(L"CPU Rating: %s out of 100", cpuRatingStr);
		}

		CPUstScore = singleThreadScoreStr;
		CPUmtScore = multiThreadScoreStr;
		CPUratingScore = cpuRatingStr;

		// Update UI
		static_singleT.SetWindowTextW(singleT);
		static_multiT.SetWindowTextW(multiT);
		static_rating.SetWindowTextW(rating);

		// Re-enable the Start button
		m_startButton.EnableWindow(TRUE);
		m_startButton.SetWindowTextW(theApp.language == L"jp" ? L"テスト再開" : L"Test Again");

		isCPUTested = true;
		});

	benchmarkThread.detach();
}


// Function to check if a number is prime
bool CPCICTMFCDlg::IsPrime(int n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}

// Single-threaded benchmark function
void CPCICTMFCDlg::RunSingleThreadedBenchmark()
{
	std::cout << "Started single thread\n";
	auto start = std::chrono::high_resolution_clock::now();
	int progress = 0;
	int number = 2; // Starting number for prime checking

	while (m_benchmarkRunning)
	{
		// Prime checking for benchmarking
		if (IsPrime(number)) {
			++SingleBenchmarkResult; // Count prime numbers
		}
		++number; // Check next number

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = now - start;

		// Update progress bar (first 50%)
		progress = static_cast<int>((elapsed.count() / 10.0) * 50);
		m_progressCPU.SetPos(progress);

		if (elapsed.count() >= 10.0) // Stop after 10 seconds
		{
			m_benchmarkRunning = false;
			break;
		}
	}
	m_progressCPU.SetPos(50); // Ensure progress bar reaches 50%
	m_benchmarkRunning = true; // Reset for next benchmark
	std::cout << "Finished single thread\n";
}

// Multi-threaded benchmark function
void CPCICTMFCDlg::RunMultiThreadedBenchmark()
{
	auto start = std::chrono::high_resolution_clock::now();
	int numThreads = std::thread::hardware_concurrency();
	int progress = 50; // Progress starts at 50% (continuing from single-threaded)
	std::atomic<int> totalPrimes{ 0 }; // Shared variable to count primes

	// Lambda function for prime calculation in each thread
	auto primeCalc = [this, &totalPrimes]() {
		int number = 2; // Start with a small number for simplicity
		while (m_benchmarkRunning)
		{
			if (IsPrime(number)) {
				++totalPrimes; // Atomically update the prime count
			}
			++number;
		}
		};

	// Launch threads to perform prime calculation
	std::vector<std::future<void>> futures;
	for (int t = 0; t < numThreads; ++t)
	{
		futures.push_back(std::async(std::launch::async, primeCalc));
	}

	while (m_benchmarkRunning)
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = now - start;

		// Update progress bar (50% to 100%)
		progress = 50 + static_cast<int>((elapsed.count() / 10.0) * 50);
		m_progressCPU.SetPos(progress);

		if (elapsed.count() >= 10.0) // Stop after 10 seconds
		{
			m_benchmarkRunning = false;
			break;
		}
	}

	// Wait for all threads to finish
	for (auto& f : futures)
	{
		if (f.valid())
			f.get();
	}

	// Store the result
	MultiBenchmarkResult = totalPrimes.load();
	m_progressCPU.SetPos(100); // Ensure progress bar reaches 100%
}


// Calculate CPU score
double CPCICTMFCDlg::CalculateCPUScore()
{
	// Define the worst and best scores for normalization
	const int worstSingleScore = 1000;  // Intel Core 2 Duo E8400
	const int bestSingleScore = 30000; // Intel Core i9-12900K
	const int worstMultiScore = 2000;  // Athlon 64 X2
	const int bestMultiScore = 500000; // Ryzen 9 5950X

	// Normalize single-threaded and multi-threaded scores
	double normalizedSingle = 100.0 * (SingleBenchmarkResult - worstSingleScore) / (bestSingleScore - worstSingleScore);
	double normalizedMulti = 100.0 * (MultiBenchmarkResult - worstMultiScore) / (bestMultiScore - worstMultiScore);

	// Clamp the values to the range [0, 100]
	normalizedSingle = clamp(normalizedSingle, 0.0, 100.0);
	normalizedMulti = clamp(normalizedMulti, 0.0, 100.0);
	
	// Calculate the average CPU rating
	return (normalizedSingle + normalizedMulti) / 2.0;
}


void CPCICTMFCDlg::OnBnClickedButtonKbTestStart()
{
	// TODO: Add your control notification handler code here
	KeyboardDlg dlg;
	dlg.DoModal();

	// Determine the keyboard test status
	CString kbStatusMessage;

	if (dlg.keyBoard_Status == 1) {
		KBstatus = L"N/A";
		kbStatusMessage = (theApp.language == L"jp") ?
			L"キーボードのテストステータス: " + KBstatus :
			L"Keyboard Test Status: " + KBstatus;
		isKeyboardTested = false;
	}
	else if (dlg.keyBoard_Status == 2) {
		if (theApp.language == L"en") {
			KBstatus = L"Working";
			kbStatusMessage = L"Keyboard Test Status: " + KBstatus;
		}
		else if (theApp.language == L"jp") {
			KBstatus = L"動作中";  // "Faulty" in Japanese
			kbStatusMessage = L"キーボードのテストステータス: " + KBstatus;
		}
		isKeyboardTested = true;
	}
	else if (dlg.keyBoard_Status == 3) {
		if (theApp.language == L"en") {
			KBstatus = L"Faulty";
			kbStatusMessage = L"Keyboard Test Status: " + KBstatus;
		}
		else if (theApp.language == L"jp") {
			KBstatus = L"故障しています";  // "Faulty" in Japanese
			kbStatusMessage = L"キーボードのテストステータス: " + KBstatus;
		}
		isKeyboardTested = true;
	}

	// Update the UI with the correct status message
	static_kb_status.SetWindowTextW(kbStatusMessage);
}



void CPCICTMFCDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
	//EndDialog(IDOK);
}


void CPCICTMFCDlg::OnBnClickedButtonprofile()
{
	// TODO: Add your control notification handler code here
	profileDlg prdlg;

	// Get the position of the "Profile" button
	CRect buttonRect;
	CWnd* pButton = GetDlgItem(IDC_MFCMENUBUTTON1); // Ensure the correct control ID is used
	if (pButton)
	{
		pButton->GetWindowRect(&buttonRect); // Get button's screen coordinates
	}
	else
	{
		// Handle the case where pButton is null
		AfxMessageBox(_T("Profile button not found!"));
		return;
	}

	// Move the profile dialog to the position under the button
	theApp.prdlgX = buttonRect.left - 3;  // X position of the button
	theApp.prdlgY = buttonRect.top; // Y position just below the button
	//CString posChk;
	//posChk.Format(L"X: %d and Y: %d",theApp.prdlgX, theApp.prdlgY);		

	//AfxMessageBox(posChk);


	// Move the dialog to the desired position
	//prdlg.MoveWindow(xPos, yPos, 0, 0);
	//prdlg.SetWindowPos(NULL, xPos, yPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	//prdlg.DoModal();

	m_pChildDialog = new profileDlg(this);
	m_pChildDialog->Create(IDD_DIALOG_PROFILE, this);
	m_pChildDialog->ShowWindow(SW_SHOW);

}


void CPCICTMFCDlg::OnCbnSelchangeComboLang()
{
	// TODO: Add your control notification handler code here
	int sel = combox.GetCurSel(); // Get selected index
	CString selectedLang;
	combox.GetLBText(sel, selectedLang); // Get text of selected item

	if (combox.GetCurSel() == 1) // Japanese Language Selected
	{
		theApp.language = L"jp";

		prf_btn.SetWindowTextW(L"プロフィール");
		CPUtestHeading.SetWindowTextW(L"CPUテスト");
		CPUresultHeading.SetWindowTextW(L"CPUベンチマーク結果");

		if (singleThreadScoreStr.IsEmpty() || singleThreadScoreStr == L"N/A")
			singleThreadScoreStr = L"N/A";

		if (multiThreadScoreStr.IsEmpty() || multiThreadScoreStr == L"N/A")
			multiThreadScoreStr = L"N/A";

		if (cpuRatingStr.IsEmpty() || cpuRatingStr == L"N/A")
			cpuRatingStr = L"N/A";

		if (KBstatus.IsEmpty() || KBstatus == L"N/A")
			KBstatus = L"N/A";
		else {
			if (KBstatus == L"Working") {
				KBstatus = L"動作中";  // "Working" in Japanese
			}
			else if (KBstatus == L"Faulty") {
				KBstatus = L"故障しています";  // "Faulty" in Japanese
			}
		}

		static_singleT.SetWindowTextW(CString(L"シングルスレッドスコア: ") + singleThreadScoreStr);
		static_multiT.SetWindowTextW(CString(L"マルチスレッドスコア: ") + multiThreadScoreStr);
		static_rating.SetWindowTextW(CString(L"CPU評価: ") + cpuRatingStr);

		KBtestHeading.SetWindowTextW(L"キーボードテスト");
		KBresultHeading.SetWindowTextW(L"キーボードテスト結果");
		static_kb_status.SetWindowTextW(CString(L"キーボードのテストステータス: ") + KBstatus);
		PCinfoHeading.SetWindowTextW(L"パソコン情報");
		file_btn.SetWindowTextW(L"ファイル");
		act_btn.SetWindowTextW(L"アクション");
		view_btn.SetWindowTextW(L"表示");
		help_btn.SetWindowTextW(L"ヘルプ");
		GetDlgItem(IDC_BUTTON_CPU_TEST_START)->SetWindowTextW(L"テストCPU");
		t_kb_btn.SetWindowTextW(L"キーボードをテスト");
		up_btn.SetWindowTextW(L"アップロード");
	}
	else // English Language Selected
	{
		theApp.language = L"en";

		prf_btn.SetWindowTextW(L"Profile");
		CPUtestHeading.SetWindowTextW(L"CPU Test");
		CPUresultHeading.SetWindowTextW(L"CPU Benchmark Result");

		if (singleThreadScoreStr.IsEmpty() || singleThreadScoreStr == L"N/A")
			singleThreadScoreStr = L"N/A";

		if (multiThreadScoreStr.IsEmpty() || multiThreadScoreStr == L"N/A")
			multiThreadScoreStr = L"N/A";

		if (cpuRatingStr.IsEmpty() || cpuRatingStr == L"N/A")
			cpuRatingStr = L"N/A";

		if (KBstatus.IsEmpty() || KBstatus == L"N/A")
			KBstatus = L"N/A";
		else {
			if (KBstatus == L"動作中") {
				KBstatus = L"Working";
			}
			else if (KBstatus == L"故障しています") {
				KBstatus = L"Faulty";
			}
		}

		static_singleT.SetWindowTextW(CString(L"Single-Thread Score: ") + singleThreadScoreStr);
		static_multiT.SetWindowTextW(CString(L"Multi-Thread Score: ") + multiThreadScoreStr);
		static_rating.SetWindowTextW(CString(L"CPU Rating: ") + cpuRatingStr);

		KBtestHeading.SetWindowTextW(L"Keyboard Test");
		KBresultHeading.SetWindowTextW(L"Keyboard Test Result");
		static_kb_status.SetWindowTextW(CString(L"Keyboard Test Status: ") + KBstatus);
		PCinfoHeading.SetWindowTextW(L"PC Information");
		file_btn.SetWindowTextW(L"File");
		act_btn.SetWindowTextW(L"Action");
		view_btn.SetWindowTextW(L"View");
		help_btn.SetWindowTextW(L"Help");
		GetDlgItem(IDC_BUTTON_CPU_TEST_START)->SetWindowTextW(L"Test CPU");
		t_kb_btn.SetWindowTextW(L"Test Keyboard");
		up_btn.SetWindowTextW(L"Upload");
	}
	if (firstOpen == FALSE) {
		// Clear the tree view before rerawing
		m_treeCtrl.DeleteAllItems();

		// Re-draw the tree view after changing language
		all_tree_drawing();
	}
	firstOpen = FALSE;

	//Open or create a registry key in HKEY_CURRENT_USER
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

