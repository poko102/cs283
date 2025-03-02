1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My shell calls waitpid() for every child process which makes sure that every command is complete before the shell goes back to prompting the user for new input. If I forgot to call it on the children processes, the parent would not collect the finished children's exit status which would lead to the system keeping the record and wasting space/resources.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

When you use dup2(), it copies one file descriptor onto another. After that, you have extra file descriptors that aren’t needed anymore and closing them is ideal because it frees up resources and prevents any potential issues with file descriptors running out/leaking.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

The cd command is built in instead of being an external command because it needs to change the current working directory of the shell process. If cd was an external command, it would have to run in a separate child process which means that any attempts to change directories would only affect that child process that it is running in. This does not update to the parent and its working directory would be unchanged which makes it impossible for users to actually change directories.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

To implement an arbitrary number of piped commands while still handling memory allocation efficiently, one could replace the array with a fixed size with a dynamic array or linked list instead. I could implement an  array that grows as needed and resizes while also allocating memory as needed. You could also try to implement a linked list. The trade-offs to consider are that while it would be useful, it would also  make the code harder/complex which could lead to a lot of potential issues especially with resizing and managing memory. 
