#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"



/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */

extern void print_dragon(void);


#ifndef CMD_ERR_EXECUTE
#define CMD_ERR_EXECUTE "error: execution failed"
#endif

 //initializes cmd_buff_t and all pointers in the argv array to NULL
 int alloc_cmd_buff(cmd_buff_t *cmd_buff) 
 {
    if (cmd_buff == NULL)
    {
        return ERR_MEMORY;
    }
 
    cmd_buff->argc = 0; 
    cmd_buff->_cmd_buffer = NULL;
    for (int i = 0; i < CMD_ARGV_MAX; i++) 
    {         
        cmd_buff->argv[i] = NULL; 
        
    }
    return OK;                                       
 }

//clears the cmd_buff_t structure for reuse
int clear_cmd_buff(cmd_buff_t *cmd_buff) 
{
    if (cmd_buff->_cmd_buffer != NULL) 
    {
        free(cmd_buff->_cmd_buffer);
        cmd_buff->_cmd_buffer = NULL;
    }
    
    cmd_buff->argc = 0;
    for (int i = 0; i < CMD_ARGV_MAX; i++) 
    {
        cmd_buff->argv[i] = NULL;
    }
    return OK;
}

//duplicates the input command line into cmd_buff_t 
int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff) 
{
    cmd_buff->_cmd_buffer = strdup(cmd_line);
    //checks for memory allocation failure and retrsun error
    if (cmd_buff->_cmd_buffer == NULL) 
    {
        return ERR_MEMORY;
    }

    return OK;
}


int exec_local_cmd_loop()
{
    char *cmd_buff;
    int rc = 0;
    cmd_buff_t cmd;

    // memory allocation for the command buffer
    cmd_buff = malloc(SH_CMD_MAX);
    if (cmd_buff == NULL) 
    {
        return ERR_MEMORY;
    }
   
    //initializea cmd_buff_t
    if (alloc_cmd_buff(&cmd) != OK) 
    {
        free(cmd_buff);
        return ERR_MEMORY;
    }
   
    // TODO IMPLEMENT MAIN LOOP
    //prompts and processes user commands
    while(1)
    {
        printf("%s", SH_PROMPT);

        if (fgets(cmd_buff, SH_CMD_MAX, stdin) == NULL)
        {
            printf("\n");
            break;
        }
        //remove the trailing \n from cmd_buff
        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';
       
        //IMPLEMENT THE REST OF THE REQUIREMENTS

        //if input is empty, prints warning
        if (strlen(cmd_buff) == 0) 
        {
            printf("%s\n", CMD_WARN_NO_CMD);
            continue;
        }
       
        //breaks loop if user types exit
        if (strcmp(cmd_buff, EXIT_CMD) == 0) 
        {
            break;
        }


        // TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff

        //uses build_cmd_buff to duplicate input
        rc = build_cmd_buff(cmd_buff, &cmd);
        if (rc != OK) 
        {
            if (rc == WARN_NO_CMDS)
                printf("%s\n", CMD_WARN_NO_CMD); 
            else
                fprintf(stderr, "Error: command parsing failed\n");
            continue;
        }
       
        
        //trims leading whitespace
        char *start = cmd._cmd_buffer;
        while (*start && isspace((unsigned char)*start))
        {
            start++;
        }
        if (start != cmd._cmd_buffer)
        {
            memmove(cmd._cmd_buffer, start, strlen(start) + 1);
        }
        //trims trailing whitespace
        size_t len = strlen(cmd._cmd_buffer);
        while (len > 0 && isspace((unsigned char)cmd._cmd_buffer[len - 1])) 
        {
            cmd._cmd_buffer[len - 1] = '\0';
            len--;
        }
       
        //clear and continue if trimmed command is empty
        if (strlen(cmd._cmd_buffer) == 0) 
        {
            clear_cmd_buff(&cmd);
            continue;
        }
       
        //splits command string into tokens and preserves text in double quotes
        char *p = cmd._cmd_buffer;
        cmd.argc = 0;
        while (*p) 
        {
            //skips extra whitespace
            while (*p && isspace((unsigned char)*p))
            {
                p++;
            }
            if (*p == '\0')
            {
                break;
            }
            char *token = NULL;
            
            if (*p == '"') 
            {
                //skips opening quote and starts token
                p++;             
                token = p;
                while (*p && *p != '"')
                {
                //finds closing quote and ends the token while skipping closing qoute
                    p++;  
                }     
                if (*p == '"') 
                {
                    *p = '\0';
                    p++;       
                }
            } 
            else 
            {
                ///marks start of token and moves, if there is whitespace, terminate token
                token = p; 
                while (*p && !isspace((unsigned char)*p))
                    p++;   
                if (*p != '\0') 
                {
                    *p = '\0';
                    p++;       
                }
            }
            //adds token to argv array
            if (cmd.argc < CMD_ARGV_MAX - 1)
            {
                cmd.argv[cmd.argc++] = token;
            }
            else 
            {
                return ERR_TOO_MANY_COMMANDS;
                break;
            }
        }
        cmd.argv[cmd.argc] = NULL;

        if (cmd.argc == 0 || cmd.argv[0] == NULL) {
            clear_cmd_buff(&cmd);
            continue;
        }
        
       
        //checks if command is "cd" and if so, change directory
        if (strcmp(cmd.argv[0], "cd") == 0) 
        {
            if (cmd.argc < 2) {
                clear_cmd_buff(&cmd);
                continue;
            }
            if (chdir(cmd.argv[1]) != 0) 
            {
                perror("chdir failed");
            }
            clear_cmd_buff(&cmd);
            continue;
        }
       
        //if command is "rc", output return code of last external command
        if (strcmp(cmd.argv[0], "rc") == 0) 
        {
            printf("%d\n", rc);
            clear_cmd_buff(&cmd);
            continue;
        }
       
        // TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
        if (strcmp(cmd.argv[0], "dragon") == 0) 
        {
            print_dragon();
            clear_cmd_buff(&cmd);
            continue;
        }

        
       
    
        // TODO IMPLEMENT if not built-in command, fork/exec as an external command
        // for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"


        //forks a child process to execute external command
        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("fork failed");
            clear_cmd_buff(&cmd);
            continue;
        } 
        else if (pid == 0) 
        {
            //in child process, execute command using execvp and if it returns, give an error
            execvp(cmd.argv[0], cmd.argv);
            perror(CMD_ERR_EXECUTE);
            exit(1);
        } 
        else 
        {
            //parent process waits for child process to be done
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                rc = WEXITSTATUS(status);
        }
       
        clear_cmd_buff(&cmd);
    }
   
    //frees buff
    free(cmd_buff);
    return rc;
}
