#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Initialize structures and handles
STARTUPINFO sti = {0};
SECURITY_ATTRIBUTES sats = {0};
PROCESS_INFORMATION pi = {0};
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
BYTE buffer[2048];
DWORD writ, excode, read, available;

// Function to set up a connection to an external process (e.g., a chess engine)
void ConnectToEngine(TCHAR path[])
{   
	// Initialize handles to NULL
    pipin_w = pipin_r = pipout_w = pipout_r = NULL;
    
	// Set security attributes for the pipes
    sats.nLength = sizeof(sats);
    sats.bInheritHandle = TRUE;
    sats.lpSecurityDescriptor = NULL;
    
	// Create pipes for input and output
    CreatePipe(&pipout_r, &pipout_w, &sats, 0);
    CreatePipe(&pipin_r, &pipin_w, &sats, 0);
    
	// Set up the STARTUPINFO structure to redirect standard input, output, and error
    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    sti.wShowWindow = SW_HIDE; // Hide the window
    sti.hStdInput = pipin_r;   // Redirect standard input to pipin_r
    sti.hStdOutput = pipout_w; // Redirect standard output to pipout_w
    sti.hStdError = pipout_w;  // Redirect standard error to pipout_w
    
	// Create the process, with redirection of handles set up in STARTUPINFO
    if (!CreateProcess(NULL, path, NULL, NULL, TRUE, 0, NULL, NULL, &sti, &pi))
    {
        std::cerr << "Error creating process: " << GetLastError() << std::endl;
    }
} 

// Function to send a position command to the engine and retrieve the next move
std::string getNextMove(std::string position)
{
    std::string str;
    // Prepare the command to send to the engine
    position = "position startpos moves " + position + "\ngo\n";

    // Write the command to the engine's input pipe
    WriteFile(pipin_w, position.c_str(), position.length(), &writ, NULL);

    // Sleep for a short duration to allow the engine to process the command
    Sleep(500);

    // Peek into the pipe to determine the amount of data available
    PeekNamedPipe(pipout_r, buffer, sizeof(buffer), &read, &available, NULL);

    do
    {
        // Clear the buffer
        ZeroMemory(buffer, sizeof(buffer));
        
        // Read data from the pipe
        if (!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read) break;
        
        // Null-terminate the buffer and append to the result string
        buffer[read] = 0;
        str += (char*)buffer;
    }
    while (read >= sizeof(buffer)); // Continue reading while there is data available

    // Find and extract the best move from the response string
    int n = str.find("bestmove");
    if (n != -1) return str.substr(n + 9, 4);

    // Return "error" if the best move is not found
    return "error";
}

// Function to close the connection and clean up resources
void CloseConnection()
{
    // Send a quit command to the engine
    WriteFile(pipin_w, "quit\n", 5, &writ, NULL);

    // Close all open handles
    if (pipin_w != NULL) CloseHandle(pipin_w);
    if (pipin_r != NULL) CloseHandle(pipin_r);
    if (pipout_w != NULL) CloseHandle(pipout_w);
    if (pipout_r != NULL) CloseHandle(pipout_r);
    if (pi.hProcess != NULL) CloseHandle(pi.hProcess);
    if (pi.hThread != NULL) CloseHandle(pi.hThread);
}

#endif // ENGINE_H
