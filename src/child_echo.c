#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();

    if (argc < 2) {
        printf("Child (PID: %lu) - No parent PID provided\n", pid);
    } else {
        printf("Child (PID: %lu) - Parent PID: %s\n", pid, argv[1]);
    }

 // Keep the child alive so you can inspect it with PowerShell
    Sleep(20000); // 20000 ms = 20 seconds

    return 42;  // exit code 0 means success
}
