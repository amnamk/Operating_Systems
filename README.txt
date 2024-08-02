• Introduction:

Welcome to our Shell project from the course "Operating Systems"! We have made shells that satisfy all the basic, intermediate, and advanced 
requests from a project description. Also, we provided answers to the questions related to the 1.5 task. 
We hope that you will enjoy the result of our work and we look forward to your feedback.

• Group Members:

Amna Mutap
Džanan Habibija

• Project Task:

Shell Project 2

• Submission Content:

- 1.2task and 1.4.c
- advanced1.1.c
- basic1.1.c
- basic1.3.c
- forkbomb.c
- source.txt
- README.txt

• Answers to Assignment Questions:

 1.5.1 Kernel Mode vs. User Mode

Reading from disk:
Reading from the disk requires kernel mode. When a program needs to access data from the physical disk, it interacts with hardware devices, a privileged operation that necessitates switching to kernel mode. The kernel performs the necessary disk I/O operations (e.g., issuing commands to the disk controller) and returns the requested data to the user-mode process.

 Reading the current time from the hardware clock:
Similar to disk access, reading from the hardware clock is a privileged operation. The kernel manages the hardware clock and provides a safe interface for user-mode programs to access the current time through system calls. This ensures that processes cannot directly manipulate the hardware clock, potentially causing system inconsistencies.

1.5.2 System Calls

Purpose:
System calls are the mechanism through which a user-mode program requests services from the operating system kernel. They provide a controlled and secure interface for processes to interact with hardware devices, manage memory, create/terminate processes, and perform other essential tasks that require kernel-level privileges.


 
Categories and Examples:

- Process Management:
  - `fork()`: Creates a new process (child) as a copy of the calling process (parent).
  - `wait()`: Allows a parent process to wait for termination of its child process(es).

- File Management:
  - `open()`: Opens a file for various operations (reading, writing, etc.).
  - `read()`: Reads data from an open file into a process's memory buffer.
  - `write()`: Writes data from a process's memory buffer to an open file.
  - `close()`: Closes an open file, releasing system resources associated with it.

- Device Management:
  - `read()` (for devices): Reads data from a device (e.g., keyboard, network card).
  - `write()` (for devices): Writes data to a device (e.g., display, printer).

- Memory Management:
  - `malloc()`: Allocates memory dynamically for a process.
  - `free()`: Deallocates memory previously allocated using `malloc()`.


1.5.3 Program Output Scenarios

Assumptions:
- The program uses `fork()` to create a child process.
- `os.waitpid(pid, 0)` is used in the parent process to wait for the child to finish.
- The child process executes `some_executable` using `os.execlp()`.

Possible Outputs:

1. Scenario: The fork() system call succeeds, but exec() fails:
     -The child process prints “Hello1”.
     -The child process tries to execute “some executable” but fails.
     -The child process prints “Hello2”.
     -The parent process waits for the child to finish.
     -The parent process prints “Hello3”.
2. Scenario: The fork() system call succeeds, and exec() also succeeds:
     -The child process prints “Hello1”.
     -“some executable” is executed successfully, so “Hello2” is not printed (since exec() replaces the current address space with a new one).
     -The parent process waits for the child to finish executing “some executable”.
     -After waiting, the parent prints “Hello3”.
3. Scenario: If fork() fails:
     -The program directly goes to the else part.
     -The parent process prints “Hello4”.



• Assignment Outline:
Implemented basic shell functionality.
Implemented file operations (e.g., cp, history, free, fortune), within some additional operations(wc,sl) in file_operations.c.
Added support for output redirection and piping.
Created a README file to document the submission.


• Compilation Instructions:
To compile the shell program, use the following commands:
gcc -Wall -o shell basic1.1.c 
./shell

• Challenges Encountered:
Understanding the system calls and process management.
Parsing user input into executable commands, arguments, and options.
Implementing output redirection and piping correctly.

• Sources/Tutorials Used:
https://github.com/Jerrydepon/CS344_Operating-System-1 
Operating Systems Three Easy Pieces (Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau).
C Programming Language (Brian Kernighan and Dennis Ritchie).
GNU C Library Reference Manual.
Creating a Simple Shell in C (Stephen Brennan).
Implementing a Shell in C (GeeksforGeeks).
youtube.com
Stack Overflow for troubleshooting specific issues.