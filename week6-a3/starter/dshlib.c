//Alicia Ait-Seddik aa4659
//CS283 - Assignment 3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */

 int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    //makes a copy of input line to modify it safely
    char *line_copy = strdup(cmd_line);
    if (line_copy == NULL)
    {
        perror("Error duplicating command line");
        return ERR_CMD_OR_ARGS_TOO_BIG;
    }

    //outer token splits the input using the pipe character and pointer variable
    char *outer_ptr;
    char *outer_token = strtok_r(line_copy, PIPE_STRING, &outer_ptr);

    while (outer_token != NULL)
    {
        //trims leading whitespaces from outer token
        while (*outer_token && isspace((unsigned char)*outer_token))
            outer_token++;

        //trim trailing whitespace
        size_t len = strlen(outer_token);
        while (len > 0 && isspace((unsigned char)outer_token[len - 1]))
        {
            outer_token[len - 1] = '\0';
            len--;
        }

        //if token is empty after trimming -> skip
        if (strlen(outer_token) == 0)
        {
            outer_token = strtok_r(NULL, PIPE_STRING, &outer_ptr);
            continue;
        }

        //checks if user exceeded the max num of commands
        if (clist->num >= CMD_MAX)
        {
            free(line_copy);
            return ERR_TOO_MANY_COMMANDS;
        }

        //separate copy of the outer token for inner token so that the outer_ptr isn't affected when modified
        
        char *command_copy = strdup(outer_token);
        if (command_copy == NULL)
        {
            free(line_copy);
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }

        //inner token splits the command string by spaces
        char *inner_ptr;
        char *inner_token = strtok_r(command_copy, " ", &inner_ptr);

        //if no tokens are found -> free and keep going
        if (inner_token == NULL)
        {
            free(command_copy);
            outer_token = strtok_r(NULL, PIPE_STRING, &outer_ptr);
            continue;
        }

        //first token is the executable
        if (strlen(inner_token) >= EXE_MAX)
        {
            free(command_copy);
            free(line_copy);
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }
        strcpy(clist->commands[clist->num].exe, inner_token);

        //allocates a buffer for the arguments
        char *arg_buffer = malloc(ARG_MAX);
        if (arg_buffer == NULL)
        {
            free(command_copy);
            free(line_copy);
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }
        arg_buffer[0] = '\0'; 

        //used to help with spacing between arguments
        int first_arg = 1; 

        //processes remaining inner tokens as arguments
        while ((inner_token = strtok_r(NULL, " ", &inner_ptr)) != NULL)
        {
            //checks that adding token does not exceed max args
            if (strlen(arg_buffer) + strlen(inner_token) + (first_arg ? 0 : 1) >= ARG_MAX)
            {
                free(arg_buffer);
                free(command_copy);
                free(line_copy);
                return ERR_CMD_OR_ARGS_TOO_BIG;
            }
            //appends space if it is not the first argument
            if (!first_arg)
                strcat(arg_buffer, " ");
            strcat(arg_buffer, inner_token);
            first_arg = 0;
        }

        //copies the arguments into the command structure
        strcpy(clist->commands[clist->num].args, arg_buffer);

        //frees allocated memory used for command's inner token
        free(arg_buffer);
        free(command_copy);

        //increments num of parsed commands
        clist->num++;

        //gets the next outer token
        outer_token = strtok_r(NULL, PIPE_STRING, &outer_ptr);
    }

    //frees original input line duplicate
    free(line_copy);

    //warning if no commands were parsed
    if (clist->num == 0)
        return WARN_NO_CMDS;

    return OK;
}