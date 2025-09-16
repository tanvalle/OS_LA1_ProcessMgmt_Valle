#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command to simulate exec: run "cmd /c dir"
    char cmdLine[] = "cmd /c dir";

    if (!CreateProcess(
            NULL,
            cmdLine,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for child to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Parent exits with the same exit code
    return exitCode;
}
