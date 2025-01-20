#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
int reverse_str(char *, int, int); 
int find_word(char *, char *); 
int replace_word(char *, char *, char *, int, int); 
int print_words(char *, int, int);

int setup_buff(char *buff, char *user_str, int len)
{
    //TODO: #4:  Implement the setup buff as per the directions
    if len > BUFFER_SZ 
    {
        return -1;
    }

    //inistalizes the string to 0 and has temp point to buff 
    //int str_len = 0;
    char *temp = buff;

    while (*user_str == ' ')
    {
        user_str++;
    }

    //process the string while skipping the spaces  
    //also copies characters into the buffer while updating the pointers 
    for (int str_len = 0; *user_str != '0/' && str_len < len-1; user_str++;)
    {
        if (*user_str == ' ' && (*(user_str + 1) == ' ' || *(user_str + 1) == '\0')) 
        {
            continue;
        }
        *temp++ = *user_str;
    }

    while(temp <buff + BUFFER_SZ -1)
    {
        *temp++ = '.'
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
    //throws out an error code if buffer is null or the  string length is larger than beffer legnth 
    if (buff = NULL || str_len > len)
    {
        return -1;
    }

    int counter = 0;
    bool counted = false;

    //loops until the end of the string to chrck if the current character is a space or not
    //if it is not a space and not in a word, then increase the word counter
    //if it is a space and in a word, do not count
    //at the end, increase the buffer and return the total word count
    while (*buff != '/0')
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
       buff++
    }

    return counter;

}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int reverse_str(char *buff, int buff_len, int str_len)
{
    //throws error if the length of buffer is 0 
    if (buff_len == 0) 
    { 
        printf("Error : Empty String\n"); 
        return -1; 
    }

    char *str_end = buff + str_len - 1;
    char *temp;
    
    while (buff < end) 
    {
        temp = *buff;
        *buff++ = *end;
        *end-- = temp;
    }
    return 0;
}


int find_word(char *buff, char *word)
{
    const char *bf= buff, 
    const char *wd = word;
    while (*bf)
    {
        if (*bf == *wd)
        {
            const char *bf_temp = bf;
            const char *wd_temp = wd;
            while (wd*temp && *bf_temp == *wd_temp && *bf_temp )
            {
                bf_temp++;
                wd_temp++;
                if (!*wd_temp)
                {
                    return bf - buff;
                }
    
            }

        }
        return -1;
    }

}
int replace_word(char *buff, char *word, char *replacement, int buff_len, int str_len) 
{
    int index = find_word(buff, word); 
    if (index == -1) 
    { 
        return -1;
    }

    int word_len = 0
    int replacement_len = 0; 
    while (word[word_len])
    {
        word_len++;
    }
    while (replacement[replacement_len]) 
    {
        replacement_len++;
    }

    if (str_len - word_len + replacement_len > buff_len) 
    {
        return -3;
    }

    char *src = buff + index + word_len; 
    char*dest = buff + index + replacement_len;

    if (replacement_len > word_len) 
    {
        while (buff + str_len >= src)
        {
            *(--dest) = *(--src);
        } 
    }
    else
    {
        (*src) 
    
    while (*replacement) buff[index++] = *(replacement++);

    return 0;

    }
}

int print_words(char *buff, int buff_len, int str_len)
{
    int word_count = 0, char_ctr = 0; 
    bool at_start = true;

    printf("Word Print\n----------\n");

    for (; *buff; buff++) 
    {
        if (*buff != ' ' && at_start) 
        {
            at_start = false;
            printf("%d. ", ++word_count);
        }

        if (*buff == ' ' && !at_start) 
        {
            printf(" (%d)\n", char_ctr);
            char_ctr = 0;
            at_start = true;
        }
        else 
        {
            putchar(*buff);
            char_ctr++; 
        }
    }
    if (!at_start) printf(" (%d)\n", char_ctr);
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

    //This is safe because if argv[1] doesn't exist, it moves to the OR part of the statement where argv cannot be equal to '-'
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
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
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
            rc = reverse_str(buff, BUFFER_SZ, user_str_len);
            if (rc < 0)
            {
               printf("Error reversing words, rc = %d\n", rc); 
               exit(2); 
            }
            printf("Reversed String: %s\n", buff);
            break;
        case 'w': 
            rc = print_words(buff, BUFFER_SZ, user_str_len); 
            if (rc < 0) 
            { 
                printf("Error printing words, rc = %d\n", rc); 
                exit(2); 
            } 
            break;
        case 'x':
            rc = replace_word(buff, choice, replacement, BUFFER_SZ, user_str_len); 
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
//          PLACE YOUR ANSWER HERE