#include "pch.h"

//CString GetCPUInfo() {
//	HRESULT hres;
//
//	// Step 1: Initialize COM
//	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//	if (FAILED(hres)) {
//		return _T("Failed to initialize COM library");
//	}
//
//	// Step 2: Set COM security levels
//	hres = CoInitializeSecurity(
//		NULL,
//		-1,                          // COM authentication
//		NULL,                        // Authentication services
//		NULL,                        // Reserved
//		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
//		NULL,                        // Authentication info
//		EOAC_NONE,                   // Additional capabilities 
//		NULL                         // Reserved
//	);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to initialize security");
//	}
//
//	// Step 3: Obtain the initial locator to WMI
//	IWbemLocator* pLoc = NULL;
//	hres = CoCreateInstance(
//		CLSID_WbemLocator,
//		0,
//		CLSCTX_INPROC_SERVER,
//		IID_IWbemLocator, (LPVOID*)&pLoc);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to create IWbemLocator object");
//	}
//
//	// Step 4: Connect to WMI
//	IWbemServices* pSvc = NULL;
//	hres = pLoc->ConnectServer(
//		_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
//		NULL,                    // User name
//		NULL,                    // User password
//		0,                       // Locale 
//		NULL,                    // Security flags
//		0,                       // Authority 
//		0,                       // Context object
//		&pSvc                    // IWbemServices proxy
//	);
//
//	if (FAILED(hres)) {
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not connect to WMI namespace");
//	}
//
//	// Step 5: Set security levels on the proxy
//	hres = CoSetProxyBlanket(
//		pSvc,                        // Indicates the proxy to set
//		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
//		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
//		NULL,                        // Server principal name 
//		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
//		NULL,                        // Client identity
//		EOAC_NONE                    // Proxy capabilities 
//	);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not set proxy blanket");
//	}
//
//	// Step 6: Query CPU Information
//	IEnumWbemClassObject* pEnumerator = NULL;
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_Processor"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Query for CPU info failed");
//	}
//
//	// Step 7: Retrieve CPU information
//	IWbemClassObject* pclsObj = NULL;
//	ULONG uReturn = 0;
//	CString cpuDetails;
//
//	while (pEnumerator) {
//		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//
//		if (0 == uReturn) {
//			break;
//		}
//
//		VARIANT vtProp;
//
//		// CPU Name
//		pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
//		cpuDetails += _T("CPU Name: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Manufacturer
//		pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//		cpuDetails += _T("Manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		//// Number of Cores
//		//pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
//		//cpuDetails += _T("Number of Cores: ") + CString(std::to_wstring(vtProp.uintVal).c_str()) + _T("\n");
//		//VariantClear(&vtProp);
//
//		//// Max Clock Speed
//		//pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
//		//cpuDetails += _T("Max Clock Speed: ") + CString(std::to_wstring(vtProp.uintVal).c_str()) + _T(" MHz\n");
//		//VariantClear(&vtProp);
//
//		//// Number of Logical Processors
//		//pclsObj->Get(L"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
//		//cpuDetails += _T("Number of Logical Processors: ") + CString(std::to_wstring(vtProp.uintVal).c_str()) + _T("\n");
//		//VariantClear(&vtProp);
//
//		// Number of Cores
//		pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
//		CString numCores;
//		numCores.Format(_T("%u"), vtProp.uintVal);
//		cpuDetails += _T("Number of Cores: ") + numCores + _T("\n");
//		VariantClear(&vtProp);
//
//		// Max Clock Speed
//		pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
//		CString maxClockSpeed;
//		maxClockSpeed.Format(_T("%u MHz"), vtProp.uintVal);
//		cpuDetails += _T("Max Clock Speed: ") + maxClockSpeed + _T("\n");
//		VariantClear(&vtProp);
//
//		// Number of Logical Processors
//		pclsObj->Get(L"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
//		CString numLogicalProcessors;
//		numLogicalProcessors.Format(_T("%u"), vtProp.uintVal);
//		cpuDetails += _T("Number of Logical Processors: ") + numLogicalProcessors + _T("\n");
//		VariantClear(&vtProp);
//
//
//		// Processor ID
//		pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);
//		cpuDetails += _T("Processor ID: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		pclsObj->Release();
//	}
//
//	// Cleanup
//	pSvc->Release();
//	pLoc->Release();
//	pEnumerator->Release();
//	CoUninitialize();
//
//	return cpuDetails;
//}
//
//
//CString GetRAMInfo() {
//	HRESULT hres;
//
//	// Initialize COM
//	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//	if (FAILED(hres)) {
//		return _T("Failed to initialize COM library");
//	}
//
//	// Initialize COM security
//	hres = CoInitializeSecurity(
//		NULL,
//		-1,                          // COM authentication
//		NULL,                        // Authentication services
//		NULL,                        // Reserved
//		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
//		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
//		NULL,                        // Authentication info
//		EOAC_NONE,                   // Additional capabilities 
//		NULL                         // Reserved
//	);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to initialize security");
//	}
//
//	// Obtain the initial locator to WMI
//	IWbemLocator* pLoc = NULL;
//	hres = CoCreateInstance(
//		CLSID_WbemLocator,
//		0,
//		CLSCTX_INPROC_SERVER,
//		IID_IWbemLocator, (LPVOID*)&pLoc);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to create IWbemLocator object");
//	}
//
//	// Connect to WMI
//	IWbemServices* pSvc = NULL;
//	hres = pLoc->ConnectServer(
//		_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
//		NULL,                    // User name
//		NULL,                    // User password
//		0,                       // Locale 
//		NULL,                    // Security flags
//		0,                       // Authority 
//		0,                       // Context object
//		&pSvc                    // IWbemServices proxy
//	);
//
//	if (FAILED(hres)) {
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not connect to WMI namespace");
//	}
//
//	// Set security levels on the proxy
//	hres = CoSetProxyBlanket(
//		pSvc,                        // Indicates the proxy to set
//		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
//		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
//		NULL,                        // Server principal name 
//		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
//		NULL,                        // Client identity
//		EOAC_NONE                    // Proxy capabilities 
//	);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not set security levels");
//	}
//
//	// Use the IWbemServices pointer to make requests of WMI
//	IEnumWbemClassObject* pEnumerator = NULL;
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_PhysicalMemory"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Query for RAM info failed");
//	}
//
//	// Retrieve RAM information
//	IWbemClassObject* pclsObj = NULL;
//	ULONG uReturn = 0;
//	CString ramDetails;
//
//	while (pEnumerator) {
//		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//
//		if (0 == uReturn) {
//			break;
//		}
//
//		VARIANT vtProp;
//		// Get the properties of each RAM module
//		pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//		ramDetails += _T("Manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
//		ramDetails += _T("Serial Number: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		pclsObj->Get(L"Capacity", 0, &vtProp, 0, 0);
//
//
//		// Create a CString to hold the capacity
//		CString capacity;
//		capacity.Format(_T("%lld MB\n"), _wtoll(vtProp.bstrVal) / (1024 * 1024));
//
//		// Concatenate the result to ramDetails
//		ramDetails += _T("Capacity: ") + capacity;
//		VariantClear(&vtProp);
//
//		pclsObj->Get(L"PartNumber", 0, &vtProp, 0, 0);
//		ramDetails += _T("Part Number: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		pclsObj->Release();
//	}
//
//	// Cleanup
//	pSvc->Release();
//	pLoc->Release();
//	pEnumerator->Release();
//	CoUninitialize();
//
//	return ramDetails;
//}
//
//
//CString GetStorageInfo() {
//	HRESULT hres;
//
//	// Step 1: Initialize COM
//	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//	if (FAILED(hres)) {
//		return _T("Failed to initialize COM library");
//	}
//
//	// Step 2: Set COM security levels
//	hres = CoInitializeSecurity(
//		NULL,
//		-1,                          // COM authentication
//		NULL,                        // Authentication services
//		NULL,                        // Reserved
//		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
//		NULL,                        // Authentication info
//		EOAC_NONE,                   // Additional capabilities 
//		NULL                         // Reserved
//	);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to initialize security");
//	}
//
//	// Step 3: Obtain the initial locator to WMI
//	IWbemLocator* pLoc = NULL;
//	hres = CoCreateInstance(
//		CLSID_WbemLocator,
//		0,
//		CLSCTX_INPROC_SERVER,
//		IID_IWbemLocator, (LPVOID*)&pLoc);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to create IWbemLocator object");
//	}
//
//	// Step 4: Connect to WMI
//	IWbemServices* pSvc = NULL;
//	hres = pLoc->ConnectServer(
//		_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
//		NULL,                    // User name
//		NULL,                    // User password
//		0,                       // Locale 
//		NULL,                    // Security flags
//		0,                       // Authority 
//		0,                       // Context object
//		&pSvc                    // IWbemServices proxy
//	);
//
//	if (FAILED(hres)) {
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not connect to WMI namespace");
//	}
//
//	// Step 5: Set security levels on the proxy
//	hres = CoSetProxyBlanket(
//		pSvc,                        // Indicates the proxy to set
//		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
//		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
//		NULL,                        // Server principal name 
//		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
//		NULL,                        // Client identity
//		EOAC_NONE                    // Proxy capabilities 
//	);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not set proxy blanket");
//	}
//
//	// Step 6: Query Storage Information
//	IEnumWbemClassObject* pEnumerator = NULL;
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_DiskDrive"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Query for storage info failed");
//	}
//
//	// Step 7: Retrieve Storage information
//	IWbemClassObject* pclsObj = NULL;
//	ULONG uReturn = 0;
//	CString storageDetails;
//
//	while (pEnumerator) {
//		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//
//		if (0 == uReturn) {
//			break;
//		}
//
//		VARIANT vtProp;
//
//		// Device ID
//		pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
//		storageDetails += _T("Device ID: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Model
//		pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
//		storageDetails += _T("Model: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Manufacturer
//		pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//		storageDetails += _T("Manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Serial Number
//		pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
//		storageDetails += _T("Serial Number: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Size
//		pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
//
//		// Format the size as a CString
//		CString sizeStr;
//		sizeStr.Format(_T("%lld GB"), _wtoll(vtProp.bstrVal) / (1024 * 1024 * 1024));
//
//		// Concatenate to storage details
//		storageDetails += _T("Size: ") + sizeStr + _T("\n");
//
//		VariantClear(&vtProp);
//
//
//		// Interface Type
//		pclsObj->Get(L"InterfaceType", 0, &vtProp, 0, 0);
//		storageDetails += _T("Interface Type: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		pclsObj->Release();
//	}
//
//	// Cleanup
//	pSvc->Release();
//	pLoc->Release();
//	pEnumerator->Release();
//	CoUninitialize();
//
//	return storageDetails;
//}
//
//CString GetMotherboardAndBIOSInfo() {
//	HRESULT hres;
//
//	// Initialize COM
//	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//	if (FAILED(hres)) {
//		return _T("Failed to initialize COM library");
//	}
//
//	// Set COM security levels
//	hres = CoInitializeSecurity(
//		NULL,
//		-1,                          // COM authentication
//		NULL,                        // Authentication services
//		NULL,                        // Reserved
//		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
//		NULL,                        // Authentication info
//		EOAC_NONE,                   // Additional capabilities 
//		NULL                         // Reserved
//	);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to initialize security");
//	}
//
//	// Obtain the initial locator to WMI
//	IWbemLocator* pLoc = NULL;
//	hres = CoCreateInstance(
//		CLSID_WbemLocator,
//		0,
//		CLSCTX_INPROC_SERVER,
//		IID_IWbemLocator, (LPVOID*)&pLoc);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to create IWbemLocator object");
//	}
//
//	// Connect to WMI
//	IWbemServices* pSvc = NULL;
//	hres = pLoc->ConnectServer(
//		_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
//		NULL,                    // User name
//		NULL,                    // User password
//		0,                       // Locale 
//		NULL,                    // Security flags
//		0,                       // Authority 
//		0,                       // Context object
//		&pSvc                    // IWbemServices proxy
//	);
//
//	if (FAILED(hres)) {
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not connect to WMI namespace");
//	}
//
//	// Set security levels on the proxy
//	hres = CoSetProxyBlanket(
//		pSvc,                        // Indicates the proxy to set
//		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
//		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
//		NULL,                        // Server principal name 
//		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
//		NULL,                        // Client identity
//		EOAC_NONE                    // Proxy capabilities 
//	);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not set proxy blanket");
//	}
//
//	// Query Motherboard Information
//	IEnumWbemClassObject* pEnumerator = NULL;
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_BaseBoard"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Query for motherboard info failed");
//	}
//
//	// Retrieve Motherboard Information
//	IWbemClassObject* pclsObj = NULL;
//	ULONG uReturn = 0;
//	CString motherboardDetails;
//
//	while (pEnumerator) {
//		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//
//		if (0 == uReturn) {
//			break;
//		}
//
//		VARIANT vtProp;
//
//		// Manufacturer
//		pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//		motherboardDetails += _T("Motherboard Manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Product
//		pclsObj->Get(L"Product", 0, &vtProp, 0, 0);
//		motherboardDetails += _T("Motherboard Product: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Serial Number
//		pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
//		motherboardDetails += _T("Motherboard Serial Number: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// Version
//		pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
//		motherboardDetails += _T("Motherboard Version: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		pclsObj->Release();
//	}
//
//	// Query BIOS Information
//	pEnumerator = NULL;
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_BIOS"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Query for BIOS info failed");
//	}
//
//	// Retrieve BIOS Information
//	while (pEnumerator) {
//		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//
//		if (0 == uReturn) {
//			break;
//		}
//
//		VARIANT vtProp;
//
//		// BIOS Manufacturer
//		pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//		motherboardDetails += _T("BIOS Manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// BIOS Version
//		pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
//		motherboardDetails += _T("BIOS Version: ") + CString(vtProp.bstrVal) + _T("\n");
//		VariantClear(&vtProp);
//
//		// BIOS Release Date
//		pclsObj->Get(L"ReleaseDate", 0, &vtProp, 0, 0);
//		if (vtProp.vt == VT_BSTR) {
//			CString strReleaseDate(vtProp.bstrVal);
//			CString year = strReleaseDate.Mid(0, 4);
//			CString month = strReleaseDate.Mid(4, 2);
//			CString day = strReleaseDate.Mid(6, 2);
//			CString formattedDate;
//			formattedDate.Format(_T("%s-%s-%s"), year, month, day);
//
//			motherboardDetails += _T("BIOS Release Date: ") + formattedDate + _T("\n");
//		}
//		VariantClear(&vtProp);
//
//
//		pclsObj->Release();
//	}
//
//	// Cleanup
//	pSvc->Release();
//	pLoc->Release();
//	pEnumerator->Release();
//	CoUninitialize();
//
//	return motherboardDetails;
//}
//
//
//CString GetAllDeviceInfo() {
//	HRESULT hres;
//	CString deviceInfo;
//
//	// Initialize COM
//	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//	if (FAILED(hres)) {
//		return _T("Failed to initialize COM library");
//	}
//
//	// Set COM security levels
//	hres = CoInitializeSecurity(
//		NULL,
//		-1,                          // COM authentication
//		NULL,                        // Authentication services
//		NULL,                        // Reserved
//		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
//		NULL,                        // Authentication info
//		EOAC_NONE,                   // Additional capabilities 
//		NULL                         // Reserved
//	);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to initialize security");
//	}
//
//	// Obtain the initial locator to WMI
//	IWbemLocator* pLoc = NULL;
//	hres = CoCreateInstance(
//		CLSID_WbemLocator,
//		0,
//		CLSCTX_INPROC_SERVER,
//		IID_IWbemLocator, (LPVOID*)&pLoc);
//
//	if (FAILED(hres)) {
//		CoUninitialize();
//		return _T("Failed to create IWbemLocator object");
//	}
//
//	// Connect to WMI
//	IWbemServices* pSvc = NULL;
//	hres = pLoc->ConnectServer(
//		_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
//		NULL,                    // User name
//		NULL,                    // User password
//		0,                       // Locale 
//		NULL,                    // Security flags
//		0,                       // Authority 
//		0,                       // Context object
//		&pSvc                    // IWbemServices proxy
//	);
//
//	if (FAILED(hres)) {
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not connect to WMI namespace");
//	}
//
//	// Set security levels on the proxy
//	hres = CoSetProxyBlanket(
//		pSvc,                        // Indicates the proxy to set
//		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
//		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
//		NULL,                        // Server principal name 
//		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
//		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
//		NULL,                        // Client identity
//		EOAC_NONE                    // Proxy capabilities 
//	);
//
//	if (FAILED(hres)) {
//		pSvc->Release();
//		pLoc->Release();
//		CoUninitialize();
//		return _T("Could not set proxy blanket");
//	}
//
//	// Query for all needed WMI classes
//	IEnumWbemClassObject* pEnumerator = NULL;
//	IWbemClassObject* pclsObj = NULL;
//	ULONG uReturn = 0;
//	VARIANT vtProp;
//
//	// Query BIOS Information
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_BIOS"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			// Retrieve BIOS data
//			pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
//			deviceInfo += _T("bios_version: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//			deviceInfo += _T("bios_manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"ReleaseDate", 0, &vtProp, 0, 0);
//			if (vtProp.vt == VT_BSTR) {
//				CString strReleaseDate(vtProp.bstrVal);
//				CString year = strReleaseDate.Mid(0, 4);
//				CString month = strReleaseDate.Mid(4, 2);
//				CString day = strReleaseDate.Mid(6, 2);
//				CString formattedDate;
//				formattedDate.Format(_T("%s-%s-%s"), year, month, day);
//				deviceInfo += _T("bios_release_date: ") + formattedDate + _T("\n");
//			}
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		pEnumerator->Release();
//	}
//
//	// Query Motherboard Information
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_ComputerSystemProduct"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			// Device information
//			pclsObj->Get(L"UUID", 0, &vtProp, 0, 0);
//			deviceInfo += _T("device_uuid: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Vendor", 0, &vtProp, 0, 0);
//			deviceInfo += _T("device_manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
//			deviceInfo += _T("device_model: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"IdentifyingNumber", 0, &vtProp, 0, 0);
//			deviceInfo += _T("device_serial_number: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		pEnumerator->Release();
//	}
//
//	// Query CPU Information
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_Processor"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			// CPU data
//			pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
//			deviceInfo += _T("cpu_name: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//			deviceInfo += _T("cpu_manufacturer: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
//			// Format cpu_clock_speed as a CString
//			CString clockSpeedStr;
//			clockSpeedStr.Format(_T("%d MHz\n"), vtProp.intVal);  // Assuming vtProp.intVal is an integer
//			// Concatenate the formatted string to deviceInfo
//			deviceInfo += _T("cpu_clock_speed: ") + clockSpeedStr;
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		pEnumerator->Release();
//	}
//
//	// Query RAM Information
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_PhysicalMemory"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		CString ramManufacturers, ramSizes;
//		int ramSlotCount = 0;
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			ramSlotCount++;
//
//			// RAM data
//			pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
//			ramManufacturers += CString(vtProp.bstrVal) + _T(", ");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Capacity", 0, &vtProp, 0, 0);
//			// Convert BSTR to __int64 and calculate capacity in GB
//			__int64 capacityGB = _wtoi64(vtProp.bstrVal) / (1024 * 1024 * 1024);
//			// Format the capacity as a CString
//			CString capacityStr;
//			capacityStr.Format(_T("%lld GB, "), capacityGB);
//			// Concatenate the formatted string to ramSizes
//			ramSizes += capacityStr;
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		ramManufacturers.TrimRight(_T(", "));
//		ramSizes.TrimRight(_T(", "));
//		deviceInfo += _T("ram_manufacturers: ") + ramManufacturers + _T("\n");
//		deviceInfo += _T("ram_sizes: ") + ramSizes + _T("\n");
//		// Format ramSlotCount as a CString
//		CString ramSlotCountStr;
//		ramSlotCountStr.Format(_T("%d"), ramSlotCount);  // Assuming ramSlotCount is an integer
//		// Concatenate the formatted string to deviceInfo
//		deviceInfo += _T("ram_slot: ") + ramSlotCountStr + _T("\n");
//		pEnumerator->Release();
//	}
//
//	// Query Storage Device Information
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_DiskDrive"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		CString storageNames, storageSizes, storageTypes;
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			// Storage data
//			pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
//			storageNames += CString(vtProp.bstrVal) + _T(", ");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
//			// Convert BSTR to __int64 and calculate size in GB
//			__int64 sizeGB = _wtoi64(vtProp.bstrVal) / (1024 * 1024 * 1024);
//			// Format the size as a CString
//			CString sizeStr;
//			sizeStr.Format(_T("%lld GB, "), sizeGB);
//			// Concatenate the result to storageSizes
//			storageSizes += sizeStr;
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"MediaType", 0, &vtProp, 0, 0);
//			storageTypes += CString(vtProp.bstrVal) + _T(", ");
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		storageNames.TrimRight(_T(", "));
//		storageSizes.TrimRight(_T(", "));
//		storageTypes.TrimRight(_T(", "));
//		deviceInfo += _T("storage_device_name: ") + storageNames + _T("\n");
//		deviceInfo += _T("storage_device_size: ") + storageSizes + _T("\n");
//		deviceInfo += _T("storage_device_type: ") + storageTypes + _T("\n");
//		pEnumerator->Release();
//	}
//
//	// Query OS Information
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_OperatingSystem"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			// OS data
//			pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
//			deviceInfo += _T("os_name: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
//			deviceInfo += _T("kernel: nt ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Get(L"OSArchitecture", 0, &vtProp, 0, 0);
//			deviceInfo += _T("arch: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		pEnumerator->Release();
//	}
//
//	// Query Device Name
//	hres = pSvc->ExecQuery(
//		bstr_t("WQL"),
//		bstr_t("SELECT * FROM Win32_ComputerSystem"),
//		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//		NULL,
//		&pEnumerator);
//
//	if (SUCCEEDED(hres)) {
//		while (pEnumerator) {
//			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//			if (0 == uReturn) break;
//
//			// Retrieve Device Name
//			pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
//			deviceInfo += _T("device_name: ") + CString(vtProp.bstrVal) + _T("\n");
//			VariantClear(&vtProp);
//
//			pclsObj->Release();
//		}
//		pEnumerator->Release();
//	}
//
//	// Get PC user name
//	TCHAR userName[UNLEN + 1];
//	DWORD userNameSize = UNLEN + 1;
//	if (GetUserName(userName, &userNameSize)) {
//		deviceInfo += _T("pc user name: ") + CString(userName) + _T("\n");
//	}
//
//	// Cleanup
//	pSvc->Release();
//	pLoc->Release();
//	CoUninitialize();
//
//	return deviceInfo;
//}
