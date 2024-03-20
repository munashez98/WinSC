#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

#pragma comment(lib, "advapi32.lib")

TCHAR szCommand[10];
TCHAR szSvcName[80];
TCHAR szPath[MAX_PATH];
TCHAR szStartType[80];
TCHAR szErrorType[80]; 
TCHAR szSvcType[80];
TCHAR szFailReboot[80];
TCHAR szFailSet[80];
TCHAR szFailRestart[80];
TCHAR szFailCommand[80];
TCHAR szFailReset[80];
DWORD szFailResetDelay;
DWORD szFailRestartDelay;


VOID __stdcall DisplayUsage(void);
VOID __stdcall DisplayManual(void);

VOID __stdcall DoQuerySvc(void);
VOID __stdcall DoUpdateSvcDesc(void);
VOID __stdcall DoEnableSvc(void);
VOID __stdcall DoStopSvc(void);
VOID __stdcall DoSvcInstall(void);
VOID __stdcall DoSvcConfigureStart(void);
VOID __stdcall DoSvcConfigureError(void);
VOID __stdcall DoSvcConfigureType(void);
VOID __stdcall DoSvcFailure(void);


//  
// Purpose: 
//   Entry point function. Executes specified command from user.
//
// Parameters:
//   Command-line syntax is: scem [command] [service_path]
// 
// Return value:
//   None, defaults to 0 (zero)
// 
int __cdecl _tmain(int argc, TCHAR* argv[])

{
    printf("\n");
    if (argc != 3)
    {

        if ((argc == 2) && (lstrcmpi(argv[1], TEXT("?")) == 0))
        {
            DisplayManual();
            return 0;
        }
        else if ((argc == 4) && (lstrcmpi(argv[1], TEXT("create")) == 0))
        {
            StringCchCopy(szPath, MAX_PATH, argv[3]);
            StringCchCopy(szSvcName, 80, argv[2]);
            DoSvcInstall();
            return 0;
        }
        else if ((argc == 5) && (lstrcmpi(argv[1], TEXT("config")) == 0))
        {

            if (lstrcmpi(argv[3], TEXT("start")) == 0)
            {
                StringCchCopy(szSvcName, 80, argv[2]);
                StringCchCopy(szStartType, 80, argv[4]);
                DoSvcConfigureStart();
                return 0;
            }
            else if (lstrcmpi(argv[3], TEXT("error")) == 0)
            {
                StringCchCopy(szSvcName, 80, argv[2]);
                StringCchCopy(szErrorType, 80, argv[4]);
                DoSvcConfigureError();
                return 0;
            }
            else if (lstrcmpi(argv[3], TEXT("type")) == 0)
            {
                StringCchCopy(szSvcName, 80, argv[2]);
                StringCchCopy(szSvcType, 80, argv[4]);
                DoSvcConfigureType();
                return 0;
            }
            else {
                printf("Error: failed to execute command \n");
                DisplayUsage();

            }
        }
        else if ((argc == 5) && (lstrcmpi(argv[1], TEXT("failure")) == 0))
        {

            if (lstrcmpi(argv[3], TEXT("reset")) == 0)
            {
                

                StringCchCopy(szSvcName, 80, argv[2]);;
                StringCchCopy(szFailReset, 80, argv[3]);

                int szFailReset = _ttoi(argv[4]);
                DWORD szFailResetDelay = static_cast<DWORD>(szFailReset);
                DoSvcFailure();
                return 0;
            }
            else if (lstrcmpi(argv[3], TEXT("reboot")) == 0)
            {
                StringCchCopy(szSvcName, 80, argv[2]);
                StringCchCopy(szFailReboot, 80, argv[3]);
                StringCchCopy(szFailSet, 80, argv[4]);
                DoSvcFailure();
                return 0;
            }
            else if (lstrcmpi(argv[3], TEXT("command")) == 0)
            {
                StringCchCopy(szSvcName, 80, argv[2]);
                StringCchCopy(szFailCommand, 80, argv[3]);
                StringCchCopy(szFailSet, 80, argv[4]);
                DoSvcFailure();
                return 0;
            }
            else if (lstrcmpi(argv[3], TEXT("restart")) == 0)
            {
                StringCchCopy(szSvcName, 80, argv[2]);
                StringCchCopy(szFailRestart, 80, argv[3]);

                int szFailRestart = _ttoi(argv[4]);
                DWORD szFailRestartDelay = static_cast<DWORD>(szFailRestart);
                DoSvcFailure();
                return 0;
            }
            else {
                printf("Error: failed to execute command \n");
                DisplayUsage();

            }

        }
        else {
            printf("ERROR:\tIncorrect number of arguments\n\n");
            DisplayUsage();
            return 0;
        }
    }

    else if ((argc == 3) && (lstrcmpi(argv[1], TEXT("create")) == 0)){ //specifically deals with arguments for create command
        printf("ERROR:\tIncorrect number of arguments\n\n");
        DisplayUsage();
    }

    StringCchCopy(szCommand, 10, argv[1]);
    StringCchCopy(szSvcName, 80, argv[2]);



    if (lstrcmpi(szCommand, TEXT("query")) == 0)
        DoQuerySvc();
    else if (lstrcmpi(szCommand, TEXT("describe")) == 0)
        DoUpdateSvcDesc();
    else if (lstrcmpi(szCommand, TEXT("start")) == 0)
        DoEnableSvc();
    else if (lstrcmpi(szCommand, TEXT("stop")) == 0)
        DoStopSvc();
    else
    {
        _tprintf(TEXT("Unknown command (%s)\n\n"), szCommand);
        DisplayUsage();
    }

}



VOID __stdcall DisplayUsage() //Displays how to use the tool via the command line
{
    printf("Description:\n");
    printf("\tCommand-line tool that configures a service.\n\n");
    printf("Usage:\n");
    printf("\tsvcconfig [command] [service_name]\n\n");
    printf("\t[commands]\n");
    printf("\t  query [SERVICENAME]\n");
    printf("\t  create [SERVICENAME] [PATH]\n");
    printf("\t  describe [SERVICENAME]\n");
    printf("\t  config [SERVICENAME] [PARAMETER] [VALUE]\n");
    printf("\t  disable [SERVICENAME]\n");
    printf("\t  start [SERVICENAME]\n");
    printf("\t  stop [SERVICENAME]\n");
    printf("\t  failure [SERVICENAME] [PARAMETER] [VALUE]\n");
}

VOID __stdcall DisplayManual() //displays tool manual
{
    printf("Description:\n");
    printf("\tCommand-line tool that emulates sc.exe functionality.\n\n");
    printf("Usage:\n\n");
    printf("\t[commands]\n");
    printf("\t  query [SERVICENAME]\n");
    printf("\t  create [SERVICENAME] [PATH]\n");
    printf("\t  describe [SERVICENAME]\n");
    printf("\t  config [SERVICENAME] [PARAMETER] [VALUE]\n");
    printf("\t  disable [SERVICENAME]\n");
    printf("\t  start [SERVICENAME]\n");
    printf("\t  stop [SERVICENAME]\n");
    printf("\t  failure [SERVICENAME] [PARAMETER] [VALUE]\n\n\n");

    printf("Parameters:\n\n");
    printf("config:\n");
    printf("\tstart: \t\tconfigure service start type\n");
    printf("\terror: \t\tspecify severity of the error\n");
    printf("\ttype: \t\tspecify service type\n\n\n");

    printf("failure:\n");
    printf("\treset: \t\tspecifies time after which to reset the failure count to zero if there are no failures\n");
    printf("\treboot: \tmessage to be broadcast to server users before rebooting\n");
    printf("\tcommand: \tcommand-line command to be run when the specified service fails\n");
    printf("\trestart: \tspecifies length of time to wait before restarting in milliseconds\n\n\n");
}

//
// Purpose: 
//   Retrieves and displays the current service configuration.
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoQuerySvc()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;
    LPQUERY_SERVICE_CONFIG lpsc = NULL;
    LPSERVICE_DESCRIPTION lpsd = NULL;
    DWORD dwBytesNeeded, cbBufSize, dwError;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }




    // Get a handle to the service.

    schService = OpenService(
        schSCManager,          // SCM database 
        szSvcName,             // name of service 
        SERVICE_QUERY_CONFIG); // need query config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }

    // Get the configuration information.

    if (!QueryServiceConfig(
        schService,
        NULL,
        0,
        &dwBytesNeeded))
    {
        dwError = GetLastError();
        if (ERROR_INSUFFICIENT_BUFFER == dwError)
        {
            cbBufSize = dwBytesNeeded;
            lpsc = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LMEM_FIXED, cbBufSize);
        }
        else
        {
            printf("QueryServiceConfig failed (%d)", dwError);
            goto cleanup;
        }
    }

    if (!QueryServiceConfig(
        schService,
        lpsc,
        cbBufSize,
        &dwBytesNeeded))
    {
        printf("QueryServiceConfig failed (%d)", GetLastError());
        goto cleanup;
    }

    if (!QueryServiceConfig2(
        schService,
        SERVICE_CONFIG_DESCRIPTION,
        NULL,
        0,
        &dwBytesNeeded))
    {
        dwError = GetLastError();
        if (ERROR_INSUFFICIENT_BUFFER == dwError)
        {
            cbBufSize = dwBytesNeeded;
            lpsd = (LPSERVICE_DESCRIPTION)LocalAlloc(LMEM_FIXED, cbBufSize);
        }
        else
        {
            printf("QueryServiceConfig2 failed (%d)", dwError);
            goto cleanup;
        }
    }

    if (!QueryServiceConfig2(
        schService,
        SERVICE_CONFIG_DESCRIPTION,
        (LPBYTE)lpsd,
        cbBufSize,
        &dwBytesNeeded))
    {
        printf("QueryServiceConfig2 failed (%d)", GetLastError());
        goto cleanup;
    }

    // Print the configuration information.

    _tprintf(TEXT("%s configuration: \n"), szSvcName);
    _tprintf(TEXT("  Type: 0x%x\n"), lpsc->dwServiceType);
    _tprintf(TEXT("  Start Type: 0x%x\n"), lpsc->dwStartType);
    _tprintf(TEXT("  Error Control: 0x%x\n"), lpsc->dwErrorControl);
    _tprintf(TEXT("  Binary path: %s\n"), lpsc->lpBinaryPathName);
    _tprintf(TEXT("  Account: %s\n"), lpsc->lpServiceStartName);

    if (lpsd->lpDescription != NULL && lstrcmp(lpsd->lpDescription, TEXT("")) != 0)
        _tprintf(TEXT("  Description: %s\n"), lpsd->lpDescription);
    if (lpsc->lpLoadOrderGroup != NULL && lstrcmp(lpsc->lpLoadOrderGroup, TEXT("")) != 0)
        _tprintf(TEXT("  Load order group: %s\n"), lpsc->lpLoadOrderGroup);
    if (lpsc->dwTagId != 0)
        _tprintf(TEXT("  Tag ID: %d\n"), lpsc->dwTagId);
    if (lpsc->lpDependencies != NULL && lstrcmp(lpsc->lpDependencies, TEXT("")) != 0)
        _tprintf(TEXT("  Dependencies: %s\n"), lpsc->lpDependencies);

    LocalFree(lpsc);
    LocalFree(lpsd);

cleanup:
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

//
// Purpose: 
//   Starts the service.
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoEnableSvc()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,            // SCM database 
        szSvcName,               // name of service 
        SERVICE_CHANGE_CONFIG);  // need change config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }

    // Change the service start type.

    if (!ChangeServiceConfig(
        schService,            // handle of service 
        SERVICE_NO_CHANGE,     // service type: no change 
        SERVICE_DEMAND_START,  // service start type 
        SERVICE_NO_CHANGE,     // error control: no change 
        NULL,                  // binary path: no change 
        NULL,                  // load order group: no change 
        NULL,                  // tag ID: no change 
        NULL,                  // dependencies: no change 
        NULL,                  // account name: no change 
        NULL,                  // password: no change 
        NULL))                // display name: no change
    {
        printf("ChangeServiceConfig failed (%d)\n", GetLastError());
    }
    else printf("Service enabled successfully.\n");

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

//
// Purpose: 
//   Get a description of the service.
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoUpdateSvcDesc()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;
    LPQUERY_SERVICE_CONFIG lpsc = NULL;
    LPSERVICE_DESCRIPTION lpsd = NULL;
    DWORD dwBytesNeeded, cbBufSize, dwError;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,          // SCM database 
        szSvcName,             // name of service 
        SERVICE_QUERY_CONFIG); // need query config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }

    // Get the configuration information.

    if (!QueryServiceConfig(
        schService,
        NULL,
        0,
        &dwBytesNeeded))
    {
        dwError = GetLastError();
        if (ERROR_INSUFFICIENT_BUFFER == dwError)
        {
            cbBufSize = dwBytesNeeded;
            lpsc = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LMEM_FIXED, cbBufSize);
        }
        else
        {
            printf("QueryServiceConfig failed (%d)", dwError);
            goto cleanup;
        }
    }

    if (!QueryServiceConfig(
        schService,
        lpsc,
        cbBufSize,
        &dwBytesNeeded))
    {
        printf("QueryServiceConfig failed (%d)", GetLastError());
        goto cleanup;
    }

    if (!QueryServiceConfig2(
        schService,
        SERVICE_CONFIG_DESCRIPTION,
        NULL,
        0,
        &dwBytesNeeded))
    {
        dwError = GetLastError();
        if (ERROR_INSUFFICIENT_BUFFER == dwError)
        {
            cbBufSize = dwBytesNeeded;
            lpsd = (LPSERVICE_DESCRIPTION)LocalAlloc(LMEM_FIXED, cbBufSize);
        }
        else
        {
            printf("QueryServiceConfig2 failed (%d)", dwError);
            goto cleanup;
        }
    }

    if (!QueryServiceConfig2(
        schService,
        SERVICE_CONFIG_DESCRIPTION,
        (LPBYTE)lpsd,
        cbBufSize,
        &dwBytesNeeded))
    {
        printf("QueryServiceConfig2 failed (%d)", GetLastError());
        goto cleanup;
    }

    // Print the description.

    if (lpsd->lpDescription != NULL && lstrcmp(lpsd->lpDescription, TEXT("")) != 0)
        _tprintf(TEXT("  Description: %s\n"), lpsd->lpDescription);

    LocalFree(lpsc);
    LocalFree(lpsd);

cleanup:
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

// Purpose: 
//   Stops the service.
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoStopSvc()

{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;
    SERVICE_STATUS_PROCESS ssp;
    DWORD dwStartTime = GetTickCount();
    DWORD dwBytesNeeded;
    DWORD dwTimeout = 30000; // 30-second time-out
    DWORD dwWaitTime;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,         // SCM database 
        szSvcName,            // name of service 
        SERVICE_STOP |
        SERVICE_QUERY_STATUS |
        SERVICE_ENUMERATE_DEPENDENTS);

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }

    // Make sure the service is not already stopped.

    if (!QueryServiceStatusEx(
        schService,
        SC_STATUS_PROCESS_INFO,
        (LPBYTE)&ssp,
        sizeof(SERVICE_STATUS_PROCESS),
        &dwBytesNeeded))
    {
        printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
        goto stop_cleanup;
    }

    if (ssp.dwCurrentState == SERVICE_STOPPED)
    {
        printf("Service is already stopped.\n");
        goto stop_cleanup;
    }

    // If a stop is pending, wait for it.

    while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
    {
        printf("Service stop pending...\n");

        // Do not wait longer than the wait hint. A good interval is 
        // one-tenth of the wait hint but not less than 1 second  
        // and not more than 10 seconds. 

        dwWaitTime = ssp.dwWaitHint / 10;

        if (dwWaitTime < 1000)
            dwWaitTime = 1000;
        else if (dwWaitTime > 10000)
            dwWaitTime = 10000;

        Sleep(dwWaitTime);

        if (!QueryServiceStatusEx(
            schService,
            SC_STATUS_PROCESS_INFO,
            (LPBYTE)&ssp,
            sizeof(SERVICE_STATUS_PROCESS),
            &dwBytesNeeded))
        {
            printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
            goto stop_cleanup;
        }

        if (ssp.dwCurrentState == SERVICE_STOPPED)
        {
            printf("Service stopped successfully.\n");
            goto stop_cleanup;
        }

        if (GetTickCount() - dwStartTime > dwTimeout)
        {
            printf("Service stop timed out.\n");
            goto stop_cleanup;
        }
    }

    // Send a stop code to the service.

    if (!ControlService(
        schService,
        SERVICE_CONTROL_STOP,
        (LPSERVICE_STATUS)&ssp))
    {
        printf("ControlService failed (%d)\n", GetLastError());
        goto stop_cleanup;
    }

    // Wait for the service to stop.

    while (ssp.dwCurrentState != SERVICE_STOPPED)
    {
        Sleep(ssp.dwWaitHint);
        if (!QueryServiceStatusEx(
            schService,
            SC_STATUS_PROCESS_INFO,
            (LPBYTE)&ssp,
            sizeof(SERVICE_STATUS_PROCESS),
            &dwBytesNeeded))
        {
            printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
            goto stop_cleanup;
        }

        if (ssp.dwCurrentState == SERVICE_STOPPED)
            break;

        if (GetTickCount() - dwStartTime > dwTimeout)
        {
            printf("Wait timed out\n");
            goto stop_cleanup;
        }
    }
    printf("Service stopped successfully\n");

stop_cleanup:
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

// Purpose: 
//   Creates a new service.
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoSvcInstall()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;

    if (!GetModuleFileName(NULL, szPath, MAX_PATH))
    { 
        printf("Cannot install service (%d)\n", GetLastError());
        return;
    }
    

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 



    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    
    // Create the service

    schService = CreateService(
        schSCManager,              // SCM database 
        szSvcName,                 // name of service 
        NULL,                      // service name to display 
        SERVICE_ALL_ACCESS,        // desired access 
        SERVICE_WIN32_OWN_PROCESS, // service type 
        SERVICE_DEMAND_START,      // start type 
        SERVICE_ERROR_NORMAL,      // error control type 
        szPath,                    // path to service's binary 
        NULL,                      // no load ordering group 
        NULL,                      // no tag identifier 
        NULL,                      // no dependencies 
        NULL,                      // LocalSystem account 
        NULL);                     // no password 

    if (schService == NULL)
    {
        printf("CreateService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }
    else printf("Service installed successfully\n");

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

// Purpose: 
//   Configure the service start type
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoSvcConfigureStart()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,            // SCM database 
        szSvcName,               // name of service 
        SERVICE_CHANGE_CONFIG);  // need change config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }

    // Configure the start type 
    if (szStartType != NULL)
    {

        if (lstrcmpi(szStartType, TEXT("boot")) == 0) //boot start


        {
            if (!ChangeServiceConfig(
                schService,        // handle of service 
                SERVICE_NO_CHANGE, // service type: no change 
                SERVICE_BOOT_START,// service start type 
                SERVICE_NO_CHANGE, // error control: no change 
                NULL,              // binary path: no change 
                NULL,              // load order group: no change 
                NULL,              // tag ID: no change 
                NULL,              // dependencies: no change 
                NULL,              // account name: no change 
                NULL,              // password: no change 
                NULL))            // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        
        else if (lstrcmpi(szStartType, TEXT("system")) == 0) // system start
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_SYSTEM_START, // service start type 
                SERVICE_NO_CHANGE,    // error control: no change 
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");

        }
        
        else if (lstrcmpi(szStartType, TEXT("auto")) == 0) // auto start
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_AUTO_START,   // service start type 
                SERVICE_NO_CHANGE,    // error control: no change 
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        else if (lstrcmpi(szStartType, TEXT("d")) == 0) // demand start
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_DEMAND_START, // service start type 
                SERVICE_NO_CHANGE,    // error control: no change 
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        else 
            printf("ChangeServiceConfig failed (%d)\n", GetLastError());
  
       
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

// Purpose: 
//   Configure the service error type
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoSvcConfigureError()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;


    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,            // SCM database 
        szSvcName,               // name of service 
        SERVICE_CHANGE_CONFIG);  // need change config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }
    
    // Configure the service
    if (szErrorType != NULL)
    {
        // Sets service error to normal
        if (lstrcmpi(szErrorType, TEXT("normal")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_ERROR_NORMAL, // error control type
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }

        // Sets service error to severe
        else if(lstrcmpi(szErrorType, TEXT("severe")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_ERROR_SEVERE, // error control type
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }

      // Sets service error to critical
        else if (lstrcmpi(szErrorType, TEXT("critical")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_ERROR_CRITICAL, // error control type
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }

        // Set service error to ignore
        else if (lstrcmpi(szErrorType, TEXT("ignore")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_NO_CHANGE,    // service type: no change 
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_ERROR_IGNORE, // error control type
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        else
            printf("ChangeServiceConfig failed (%d)\n", GetLastError());
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

}

// Purpose: 
//   Configure the service type
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoSvcConfigureType()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;

    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service.

    schService = OpenService(
        schSCManager,            // SCM database 
        szSvcName,               // name of service 
        SERVICE_CHANGE_CONFIG);  // need change config access 

    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }

    // Configure the service
    if (szSvcType != NULL)
    {
        // Sets service type to own
        if (lstrcmpi(szSvcType, TEXT("own")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_WIN32_OWN_PROCESS, // service type
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_NO_CHANGE, // error control type: no change
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        // Sets service type to share
        else if (lstrcmpi(szSvcType, TEXT("share")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_WIN32_SHARE_PROCESS,    // service type
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_NO_CHANGE,    // error control type: no change
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        // Sets service type to kernel
        else if (lstrcmpi(szSvcType, TEXT("kernel")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_KERNEL_DRIVER,// service type
                SERVICE_NO_CHANGE,    // service start type: no change
                SERVICE_NO_CHANGE,    // error control type: no change
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
        // Sets service type to file system
        else if (lstrcmpi(szSvcType, TEXT("filesys")) == 0)
        {
            if (!ChangeServiceConfig(
                schService,           // handle of service 
                SERVICE_FILE_SYSTEM_DRIVER,    // service type
                SERVICE_NO_CHANGE,    // service start type: no change 
                SERVICE_NO_CHANGE, // error control type: no change
                NULL,                 // binary path: no change 
                NULL,                 // load order group: no change 
                NULL,                 // tag ID: no change 
                NULL,                 // dependencies: no change 
                NULL,                 // account name: no change 
                NULL,                 // password: no change 
                NULL))                // display name: no change
            {
                printf("ChangeServiceConfig failed (%d)\n", GetLastError());
            }
            else printf("Service configured successfully.\n");
        }
    }
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

//
// Purpose: 
//   Define what happens to a service upon failure.
//
// Parameters:
//   None
// 
// Return value:
//   None
//
VOID __stdcall DoSvcFailure()
{
    SC_HANDLE schSCManager;
    SC_HANDLE schService;
    SERVICE_FAILURE_ACTIONS sfa;
    SC_ACTION actions[3];


    // Get a handle to the SCM database. 

    schSCManager = OpenSCManager(
        NULL,                    // local computer
        NULL,                    // ServicesActive database 
        SC_MANAGER_ALL_ACCESS);  // full access rights 

    if (NULL == schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        return;
    }

    // Get a handle to the service with change config access.

    schService = OpenService(
        schSCManager,            // SCM database 
        szSvcName,               // name of service 
        SERVICE_CHANGE_CONFIG);  // need change config access 


    if (schService == NULL)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        return;
    }


    if (lstrcmpi(szFailReset, TEXT("reset")) == 0) //reset options
    {
        sfa.dwResetPeriod = szFailResetDelay;

    }
    else {
        sfa.dwResetPeriod = INFINITE;
    }

    if (lstrcmpi(szFailReboot, TEXT("command")) == 0) //command message
    {
        sfa.lpCommand = szFailSet;
    }
    else {
        sfa.lpCommand = NULL;
    }

    if (lstrcmpi(szFailCommand, TEXT("reboot")) == 0) //reboot message
    {

        sfa.lpRebootMsg = szFailSet;
    }
    else {
        sfa.lpRebootMsg = NULL;
    }

    if (lstrcmpi(szFailRestart, TEXT("restart")) == 0) //restart options
    {
        sfa.lpsaActions = actions;
        szFailRestartDelay = 5000;

        sfa.lpsaActions[0].Type = SC_ACTION_RESTART;
        sfa.lpsaActions[0].Delay = 5000;;
    }
    else {
        sfa.lpsaActions = NULL;
    }

    if(!ChangeServiceConfig2(schService, SERVICE_CONFIG_FAILURE_ACTIONS, &sfa))
    {
        printf("ChangeServiceConfig2 failed (%d)\n", GetLastError());
    }
    else 
        printf("Service failure actions updated successfully.\n");

cleanup:
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}
