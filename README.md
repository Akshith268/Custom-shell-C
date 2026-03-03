# Custom-shell-C
A high-performance, POSIX-compliant shell implemented in C, featuring asynchronous process management and I/O redirection.

🛠 Technical Overview
This project is a deep dive into the Linux System Call Interface. It moves beyond basic command execution by implementing kernel-level process synchronization and signal-driven resource cleanup.

🚀 Key Features
Process Lifecycle Management: Utilizes the fork() and execvp() pattern to maintain a stable parent shell while executing child processes.

Asynchronous "Zombie" Reaping: Implements a SIGCHLD signal handler with waitpid and the WNOHANG flag to prevent defunct processes from leaking system resources.

Signal Resilience: Uses the sigaction API to trap SIGINT (Ctrl+C), ensuring the shell remains active while foreground tasks are interrupted.

I/O Stream Redirection: Manages the Virtual File System (VFS) by using dup2() and file descriptor manipulation to redirect STDOUT to disk.

Background Execution: Supports non-blocking command execution using the & operator for concurrent task management.

🏗 Architecture
The shell operates as a REPL (Read-Eval-Print Loop):

Lexical Analysis: Tokenizes raw input strings into command arguments.

Signal Registration: Sets up kernel-level interrupts for process communication.

Process Branching: Clones the execution environment for command isolation.

Resource Cleanup: Handles the exit status of children asynchronously.

💻 How to Run
Bash
# Clone the repository
git clone https://github.com/yourusername/custom-linux-shell.git

# Compile using GCC
gcc myshell.c -o myshell

# Run the shell
./myshell


🧠 Skills Demonstrated
Systems Programming in C

Linux Kernel API

Inter-Process Communication (IPC)

Memory Management & File Descriptors
