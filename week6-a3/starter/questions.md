1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  It is a good choice for this application because it can read an entire line from the input up to a specified max which is very useful for input dealing with command lines/input that is based on lines. It also is very useful since it stops reading once it gets to a new line or whatever limit you implement.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  We needed to use malloc becuase it allows us to fix the size of our buffer if needed. This is very useful as it comes in handy to be flexible and is useful for saving memory when you're not sure how much space is needed.


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**: Trimming the leading and trailing spaces is necessary so that the commands can be parsed correctly. Any extra space could be interpreted as a different command or make the arguments seems different too. This could lead to a lot of different complications and errors for the shell. 

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  First example of redirection is output redirection(>) which sends the command’s output to a specified file instead of being in the terminal. The second example is input redirection(<) which lets a command read input from a specified file rather than the keyboard/what you’re entering in the terminal.  The third example is error redirection (2>) which lets you control where any error messages go, like into a separate file which is useful if you want to have a log/record file of what went wrong. However, implementing these in a shell can be challenging for a couple reasons.  First, the shell has to correctly parse the command to get redirection symbols without mistake. The shell also has to open/ create the correct files with the correct permissions. Overall, implementing these would be very useful but also they all add another layer of complexity.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  Redirection changes where input comes from or where output is going. Piping connects output of a command to the input of another command/just connects commands together.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**: Keeping these seperate in a shell is really useful since it creates a clear distinction between which messages are errors or which are just output. This makes understanding what is going on in the shell a lot easier for a user and makes debugging/implementation a lot easier for a programmer.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > I think our shell should check exit status of each command and display errors messages if commands fail, and I think they should be kept seperate. It is easier to understand and more neat to have the seperate. However, if a user prefers, it could be useful to at least have the option to merge them if they wanted, but the default should be seperate.