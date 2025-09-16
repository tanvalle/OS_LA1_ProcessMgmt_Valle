#include <stdio.h>
#include <windows.h>

int main() {
    DWORD parentPid = GetCurrentProcessId();
    printf("Parent PID: %lu\n", parentPid);

    STARTUPINFO si[2];
    PROCESS_INFORMATION pi[2];

    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        char cmdLine[100];
        sprintf(cmdLine, "child_echo.exe %lu", parentPid);

        if (!CreateProcess(
                NULL,
                cmdLine,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si[i],
                &pi[i])) {
            printf("CreateProcess for child %d failed (%lu).\n", i + 1, GetLastError());
            return 1;
        }
    }

    // Wait for both children
    HANDLE handles[2] = { pi[0].hProcess, pi[1].hProcess };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    // Get exit codes
    for (int i = 0; i < 2; i++) {
        DWORD exitCode;
        GetExitCodeProcess(pi[i].hProcess, &exitCode);
        printf("Child %d exited with code %lu\n", i + 1, exitCode);

        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}
