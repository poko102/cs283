1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  Calling execvp directly leads the shell to be completely replaced by the new command’s process but by using fork, you create a child process to run, while the parent process is preserved and can  accept further commands. Fork gives the ability to branch off and multi-task, and it’s also really useful b/c if you have an issue in the child process, it won’t also affect the parent process. 


2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  The fork() system call might fail if the maximum number of processes has been reached and it returns -1 to the parent process which shows that a child process was not made. My implementation checks the return value and handles the error by printing an error message, and then skipping the execution of the command instead of the shell crashing.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  Execvp() finds the command to execute by checking the filename against the list of directories that are specified by the  PATH environment variable which is basically a map that tells execvp() which directories to check for executable files.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  The purpose of calling wait() in the parent process after forking is to pause its execution until the child process is terminated. This allows the parent to get the child’s exit status to know if it failed or succeeded and also prevents the child from still being an entry in the process table. If we didn’t call wait(), the parent would not collect the finished child's exit status which would lead to the system keeping the record and wasting space/resources.


5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  WEXITSTATUS() gets the exit code from the s value returned by wait() which tells you whether the child process finished successfully or not/had an issue. The provided information is really important because it lets the shell know whether to report success, return an error, or use that value in further other logic, for example the rc command.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  In build_cmd_buff(), the command line is duplicated and then tokenized in which the process then carefully checks for quotes. It skips the opening quote, then collects all characters including spaces until it reaches the closing quote which it also skips and treats the inside as one big token. This is necessary because a lot of different commands have arguments with spaces but need to be processed as a one unit.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  In this assignment, I improved my parsing by handling strings with quotes so that they’re processed as a single token rather than being split at each space and being separate tokens. This also made it more challenging because I had to be careful when adjusting the pointer logic and making sure to handle the memory allocation carefully.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  The purpose of signals in a linux system is to act like a quick notification that is sent to a process to let it know that something has happened. They’re different from other IPC methods as signals are simple alerts that can interrupt a process at any time and other IPC methods have more detailed exchanges.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGKILL: forces a process to stop immediately as  it can’t be caught or ignored.
                   SIGTERM: asks a process to end and it allows the process to perform any necessary cleanup/actions before shutting it down
                   SIGINT: interrupts a process and can be caught so the process can decide how to handle the interruption


- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  When a process receives SIGSTOP, the OS immediately pauses it,and it cannot be caught, blocked, or ignored. This is to make sure the process can be properly ended for things like debugging or managing the system.
