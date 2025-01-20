// Alicia Ait-Seddik
// CS283
// Assignment 1 - C -Refresher
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SZ 50

// prototypes
void usage(char *);
void print_buff(char *, int);
int setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int count_words(char *, int, int);
int reverse(char *, int, int);
int find(char *, char *);
int replace(char *, char *, char *, int, int);
int print(char *, int, int);

int setup_buff(char *buff, char *user_str, int len) 
{
    // TODO: #4:  Implement the setup buff as per the directions

    //buffer length validation
    if (len > BUFFER_SZ) 
    {
        return -1;
    }
    char *temp = buff;

    //skips any front spaces
    while (*user_str == ' ')
    {
        user_str++;
    }

    //copies string to buffer while removing extra spaces
    for (int str_len = 0; *user_str != '\0' && str_len < len - 1; user_str++) 
    {
        if (*user_str == ' ' && (*(user_str + 1) == ' ' || *(user_str + 1) == '\0')) 
        {
            continue;
        }
        //copies character to buffer 
        *temp++ = *user_str;
        str_len++;
    }

    //terminates buffer
    *temp = '\0'; 
    return temp - buff;
}

void print_buff(char *buff, int len) {
    printf("Buffer:  ");
    for (int i = 0; i < len; i++) {
        putchar(*(buff + i));
    }
    putchar('\n');
}

void usage(char *exename) {
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);
}

int count_words(char *buff, int len, int str_len) 
{
    // YOU MUST IMPLEMENT
    int counter = 0;
    bool counted = false;

    //loops thru buffer and counts the words 
    while (*buff != '\0') 
    {
        if (*buff != ' ' && !counted)
         {
            counted = true;
            counter++;
        } 
        else if (*buff == ' ' && counted) 
        {
            counted = false;
        }
        buff++;
    }
    return counter;
}

// ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int reverse(char *buff, int buff_len, int str_len) 
{
    //throws error if the length of buffer is 0 
    if (buff_len == 0) 
    {
        return -1;
    }

    //pointers to start and end of the string
    char*str_at_start = buff;
    char *str_end = buff + str_len - 1;
    char temp;

    //reverses string by swapping characters and returns 0 if done successfully
    while (str_at_start < str_end) 
    {
        temp = *str_at_start;
        *str_at_start++ = *str_end;
        *str_end-- = temp;
    }

    return 0;
}

int find(char *buff, char *word) 
{
    //pointer to buffer
    const char *b_ptr = buff; 
    //pointer to word
    const char *w_ptr = word;

    //loops through buffer to find the word and returns the index if found or -1 if not found
    while (*b_ptr)
    {
        if (*b_ptr == *w_ptr) 
        {
            const char *b_ptr_temp = b_ptr;
            const char *w_ptr_temp = w_ptr;
            while (*w_ptr_temp && *b_ptr_temp == *w_ptr_temp)
            {
                b_ptr_temp++;
                w_ptr_temp++;

                if (!*w_ptr_temp) 
                {
                    return b_ptr - buff;
                }
            }
        }
        b_ptr++;
    }
    return -1;
}

int replace(char *buff, char *word, char *replacement, int buff_len, int str_len) 
{
    // finds the index of the word in buffer, returns -1 if not found
    int i = find(buff, word);

    //error if word is not found in string
    if (i == -1) 
    {
        return -1;
    }

    //lengths of the word and the replacment word
    int word_len = 0;
    const char *temp_word = word;
    const char *temp_replace = replacement;
    int replace_len = 0;

    while (*temp_word++)
    {
        word_len++;
    }
    while (*temp_replace++)
    {
        replace_len++;
    }

     //error if replacement exceeds the buffer size
    if (str_len - word_len + replace_len > buff_len) 
    {
        return -3;
    } 

    /*
    memcpy(temp, buff, i);
    memcpy(temp + i, replacement, replace_len)
    */


    //temp buffer for the new string
    char temp[BUFFER_SZ];
    char *temp_buff = temp;
    
    
    //copies first part of buffer
    for (int j = 0; j < i; j++) 
    {
        *temp_buff++ = *(buff + j);
    }

    //appending the replacement word
    for (int j = 0; j < replace_len; j++) 
    {
        *temp_buff++ = *(replacement + j);
    }

    //then appending rest of of buffer
    for (int j = i + word_len; *(buff + j) != '\0'; j++) 
    {
        *temp_buff++ = *(buff + j);
    }
    
    //terminates buffer
    *temp_buff = '\0';
    temp_buff = temp;

    //copies result back into og buffer
    while (*temp_buff) 
    {
        *buff++ = *temp_buff++;
    }
     
    *buff = '\0';
    return str_len - word_len + replace_len;
    
}

int print(char *buff, int buff_len, int str_len) 
{

    //str len is longer than buufer
    if (str_len > buff_len) 
    {
        return -1;
    }
    //no words to output
    if (str_len == 0) 
    {
        return 0;
    }

    int word_count = 0;
    int char_counter = 0;
    bool at_start = true;

    printf("Word Print\n----------\n");

    // loops through the buffer to print words and how long they are
    while (*buff != '\0') 
    {
        if (*buff != ' ' && at_start) 
        {
            word_count++;
            at_start = false;
            printf("%d. ", word_count);
        }

        if (*buff == ' ' && !at_start) 
        {
            printf(" (%d)\n", char_counter);
            char_counter = 0;
            at_start = true;
        } 
        else 
        {
            putchar(*buff);
            char_counter++;
        }
        buff++;
    }

    // prints length of last word and the total word count
    if (!at_start) 
    {
        printf(" (%d)\n", char_counter);
    }

    return word_count;
}

int main(int argc, char *argv[]) {
    char *buff;
    char *input_string;
    char opt;
    int rc;
    int user_str_len;
    char *choice;
    char *replacement;

    // TODO:  #1. WHY IS THIS SAFE, aka what if argv[1] does not exist?
    /* This is safe because if argv[1] doesn't exist, the program wouldn't know how to proceed. 
       But because of the section below, it would move to the OR part of the statement and can proceed. */
    if ((argc < 2) || (*argv[1] != '-')) {
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1] + 1); // get the option flag

    // handle the help flag and then exit normally
    if (opt == 'h') {
        usage(argv[0]);
        exit(0);
    }

    // WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    // TODO:  #2 Document the purpose of the if statement below
    /* The if statement below checks if the number of arguments is 
       less than 3 and prints the usage of the program and then exits.
    */ 
    if (argc < 3) {
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; // capture the user input string

    // TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
    if (opt == 'x' && argc == 5) 
    {
        choice = argv[3];
        replacement = argv[4];
    } 
    else if (opt == 'x') 
    {
        printf("Error: invalid number of arguments\n");
        exit(2);
    }

    buff = malloc(sizeof(char) * BUFFER_SZ);
    if (buff == NULL) 
    {
        printf("Error: memory allocation failure\n");
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);
    if (user_str_len < 0) {
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt) {
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);
            if (rc < 0) {
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        case 'r':
            rc = reverse(buff, BUFFER_SZ, user_str_len);
            if (rc < 0) 
            {
                printf("Error reversing words, rc = %d\n", rc);
                exit(2);
            }
            printf("Reversed String: %s\n", buff);
            break;

        case 'w':
            rc = print(buff, BUFFER_SZ, user_str_len);
            if (rc < 0) 
            {
                printf("Error printing words, rc = %d\n", rc);
                exit(2);
            }
            break;

        case 'x':
            rc = replace(buff, choice, replacement, BUFFER_SZ, user_str_len);
            if (rc < 0) 
            {
                printf("Error replacing words, rc = %d\n", rc);
                exit(2);
            }
            printf("Modified String: %s\n", buff);
            break;
        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        default:
            usage(argv[0]);
            exit(1);
    }

    print_buff(buff, BUFFER_SZ);
    // TODO:  #6 Don't forget to free your buffer before exiting
    free(buff);
    exit(0);
}

// TODO:  #7  Notice all of the helper functions provided in the 
//          at_starter take both the buffer as well as the length. Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          I think providing both the pointer and length is good practice because you
//          because it is a good way to make sure that you can handle the program without overflow, 
//          and also can be easily updated with different buffer sizes. I think it is also good practice
//          to working with pointers and managing limited memory.
