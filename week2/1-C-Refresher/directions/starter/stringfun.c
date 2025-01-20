//Alicia Ait-Seddik
//CS283
//Assignment 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
int  reverse(char *, int, int);
int  find(char *, char *);
int  replace(char *, char *, char *, int, int);
int  print(char *, int, int);

int setup_buff(char *buff, char *user_str, int len)
{
    //TODO: #4:  Implement the setup buff as per the directions
    if (len > BUFFER_SZ)
    {
        return -1;
    }

    
    //int str_len = 0;

    //temp points to the buffer
    char *temp = buff;
    //skips the leading spaces
    while (*user_str == ' ')
    {
        user_str++;
    }

    //goes thru the string while skiiping the spaces and copying characters into buffer(and updating pointer)
    for (int str_len = 0; *user_str != '\0' && str_len < len-1; user_str++)
    {
        if (*user_str == ' ' && (*(user_str + 1) == ' ' || *(user_str + 1) == '\0')) 
        {
            continue;
        }
        *temp++ = *user_str;
    }

    //filling remaiing buffer w/ dots and returns length of string
    while(temp < buff + BUFFER_SZ -1)
    {
        *temp++ = '.';
    }
    *temp = '\0';

    return temp -buff;
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len)
{
    //YOU MUST IMPLEMENT
    int counter = 0;
    bool counted = false;

    //loops until the end of the string to chrck if the current character is a space or not
    //if it is not a space and not in a word, then increase the word counter
    //if it is a space and in a word, do not count
    //at the end, increase the buffer and return the total word count
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

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int reverse(char *buff, int buff_len, int str_len)
{
    //throws error if the length of buffer is 0 
    if (buff_len == 0) 
    { 
        printf("Error: String Empty\n"); 
        return -1; 
    }

    //points to end of the string
    char *str_end = buff + str_len - 1;
    char temp;
    
    //reverses string and resturns 0 if done sucessfully
    while (buff < str_end) 
    {
        temp = *buff;
        *buff++ = *str_end;
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

    //goes thru buffer to find the word and returns the index if found or -1 if not found
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
                b_ptr++;
            }
        return -1;
        }
    }
}

int replace(char *buff, char *word, char *replacement, int buff_len, int str_len) 
{
    //finds the index of the word in buffer, returns -1 if not found
    int i = find(buff, word); 
    if (i == -1) 
    { 
        return -1;
    }

    //both lengths intialized to 0
    int word_len = 0;
    int replace_len = 0; 

    //calculates legnth of the current word and the length of the replacement word
    while (word[word_len] != '\0')
    {
        word_len++;
    }
    while (replacement[replace_len] != '\0') 
    {
        replace_len++;
    }

    //returns an error if replacement exeeds the buffer size
    if (str_len - word_len + replace_len > buff_len) 
    {
        return -3;
    }

    //points to the characater after the word in the buffer
    char *og = buff + i + word_len; 
    //points to the end of the replacement 
    char *rep = buff + i + replace_len;

    //moves the characters to make some space for the replacement if its length is greate
    if (replace_len > word_len) 
    {
        while (buff + str_len >= og)
        {
            *(rep--) = *(og--);
        } 
    }
    //moves the characters to close the space if replacement is lesser
    else
    {
        while (*og)
        {
            *(rep++) = *(og++);
        }
        
    //cpys replacment into buffer and returns 0 if sucessful
    while (*replacement) 
    {
        buff[i++] = *(replacement++);
    }
    return 0;

    }
}

int print(char *buff, int buff_len, int str_len)
{
    int word_count = 0; 
    int char_counter = 0; 
    bool start = true;

    printf("Word Print\n----------\n");

    //loops thru the buffer to print words and how long they are t
    for (; *buff; buff++) 
    {
        if (*buff != ' ' && start) 
        {
            start = false;
            printf("%d. ", ++word_count);
        }

        if (*buff == ' ' && !start) 
        {
            printf(" (%d)\n", char_counter);
            char_counter = 0;
            start = true;
        }
        else 
        {
            putchar(*buff);
            char_counter++; 
        }
    }
    //prints len of last word and the total word count
    if (!start) 
    {
        printf(" (%d)\n", char_counter);
    }
    return word_count;
}


int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string
    char *choice;
    char *replacement;


    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?

    /*This is safe because if argv[1] doesn't exist, the program wouldn't know how to proceed. 
      But because of the section below, it would move to the OR part of the statement and can proceed. */
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    /*   The if statement below checks if the number of arguments is 
         less than 3 and prints the usage of the program and then exits.
    */ 
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = malloc(sizeof(char) * BUFFER_SZ);
    if (buff == NULL) 
    {
        printf("Error: memory allocation failure\n");
        exit(99);
    }


    if (opt == 'x' && argc == 5) 
    {
        choice = argv[3];
        replacement = argv[4];
    }
    else //if (opt == 'x')
    {
        printf("Error: invalid number of arguments\n");
        exit(2);
    }

    
    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
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
            break;
        
        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          I think providing both the pointer and length is good practice because you
//          becauase it is a good way to make sure that you can handle the program without overflow, 
//          and also can be easily updated with different buffer sizes. I think it is also good practice
//          to working with pointers and managing limited memory.