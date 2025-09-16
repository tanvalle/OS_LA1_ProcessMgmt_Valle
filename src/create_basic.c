#include <stdio.h>
#include <windows.h>

int main() {
    DWORD parentPid = GetCurrentProcessId();
    printf("Parent PID: %lu\n", parentPid);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command to run child_echo.exe with parent PID as argument
    char cmdLine[100];
    sprintf(cmdLine, "child_echo.exe %lu", parentPid);

    if (!CreateProcess(
            NULL,        // application name
            cmdLine,     // command line
            NULL,        // process security
            NULL,        // thread security
            FALSE,       // inherit handles
            0,           // creation flags
            NULL,        // environment
            NULL,        // current directory
            &si,         // startup info
            &pi)) {      // process info
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    printf("Child exited with code %lu\n", exitCode);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
