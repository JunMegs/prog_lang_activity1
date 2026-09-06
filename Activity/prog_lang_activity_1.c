#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

int REGEX_EXPRESSION_FOUND_LETTER_NUMBER(char c){
     return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

int REGEX_EXPRESSION_FOUND_OPERATOR(char c)
{
    return  c == '(' || 
            c == ')' ||
            c == '|' ||
            c == '*' ||
            c == '+' ||
            c == '?';
}

int BINARY_NUMBER_FOUND(char c)
{
    return  c == '0' || c == '1';
}

void DISPLAY_POSSIBLE_COMBINATION(const char *regex)
{
    int start_parantesis = -1;
    int end_parantesis = -1;
    int pipe_index = -1;

    for (int i = 0; regex[i] != '\0'; i++)
    {
        if (regex[i] == '(')
        {
            start_parantesis = i;
            break;
        }
    }

    // FIND ')'
    if (start_parantesis != -1)
    {
        for (int i = start_parantesis + 1; regex[i] != '\0'; i++)
        {
            if (regex[i] == ')')
            {
                end_parantesis = i;
                break;
            }
        }
    }

    // FIND '|'
    if (start_parantesis != -1 && end_parantesis != -1)
    {
        for (int i = start_parantesis + 1; i < end_parantesis; i++)
        {
            if (regex[i] == '|')
            {
                pipe_index = i;
                break;
            }
        }
    }

    // IF DIDN'T FIND ALL THREE: (, |, AND ) THEN IT CONNOT GENERATE POSSIBLECOMBINATIONS
    if (start_parantesis == -1 || end_parantesis == -1 || pipe_index == -1)
    {
        return;
    }

    printf("Possible combinations:\n");
    for (int i = 0; i < start_parantesis; i++)
    {
        putchar(regex[i]);
    }

    for (int i = start_parantesis + 1; i < pipe_index; i++)
    {
        putchar(regex[i]);
    }

    for (int i = end_parantesis + 1; regex[i] != '\0'; i++)
    {
        putchar(regex[i]);
    }

    printf("\n");

    // POSSIBLE SECOND COMBINATION
    for (int i = 0; i < start_parantesis; i++)
    {
        putchar(regex[i]);
    }

    for (int i = pipe_index + 1; i < end_parantesis; i++)
    {
        putchar(regex[i]);
    }

    for (int i = end_parantesis + 1; regex[i] != '\0'; i++)
    {
        putchar(regex[i]);
    }

    printf("\n");
}

// BINARY NUMBER ANALYSIS
void DISPLAY_BINARY_NUMBER_TO_HEXADECIMAL(FILE *file, char *buffer, int buffer_size){

    printf("==============================================\n");
    printf("BINARY NUMBER ANALYSIS\n");
    printf("==============================================\n\n");

    while (fgets(buffer, buffer_size, file) != NULL)
    {
        int inside_parentheses = 0;
        int inside_binary_number = 0;

        char binary_number_index_identify[MAX_BUFFER_SIZE];
        int binary_number_index = 0;

        for(int i = 0; buffer[i] != '\0'; i++)
        {
            if (buffer[i] == '(')
            {
                inside_parentheses = 1;
            }
            else if (buffer[i] == ')')
            {
                inside_parentheses = 0;
            }
            else if (!inside_parentheses && BINARY_NUMBER_FOUND(buffer[i]))
            {
                if (!inside_binary_number)
                {
                    inside_binary_number = 1;
                    binary_number_index = 0;
                }

                binary_number_index_identify[binary_number_index] = buffer[i];
                binary_number_index++;
            }
            else
            {
                if (inside_binary_number){

                    binary_number_index_identify[binary_number_index] = '\0';

                    // CONVERT BINARY NUMBER TO HEXADECIMAL
                    long binary_number = strtol(binary_number_index_identify, NULL, 2);

                    printf("Binary number found: %s \n", binary_number_index_identify);
                    printf("Hexadecimal Equivalent: %lX\n\n", binary_number);
                    inside_binary_number = 0;
                    
                }
            }
        }
        if (inside_binary_number){

            binary_number_index_identify[binary_number_index] = '\0';

            // CONVERT BINARY NUMBER TO HEXADECIMAL
            long binary_number = strtol(binary_number_index_identify, NULL, 2);

            printf("Binary number found: %s \n", binary_number_index_identify);
            printf("Hexadecimal Equivalent: %lX\n\n", binary_number);

            inside_binary_number = 0;
        }
    }
}

// REGULAR EXPRESSION ANALYSIS
void DISPLAY_REGULAR_EXPRESSION_TO_PASSIBLE_STRING(FILE *file, char *buffer, int buffer_size)
{
    printf("==============================================\n");
    printf("REGULAR EXPRESSION ANALYSIS\n");
    printf("==============================================\n\n");

    while (fgets(buffer, buffer_size, file) != NULL)
    {
        int regex_start_index = -1;
        int regex_end_index = -1;

        for (int i = 0; buffer[i] != '\0'; i++)
        {
            // FIND '('
            if (buffer[i] == '(')
            {
                regex_start_index = i;

                // IF THERE IS A LETTER OR NUMBER IMMEDIATELY BEFORE '(', INCLUDE IT IN THE RE.
                if (i > 0)
                {
                    char before_start_index = buffer[i - 1];

                    if (REGEX_EXPRESSION_FOUND_LETTER_NUMBER(before_start_index))
                    {
                        regex_start_index = i - 1;
                    }
                }
            }

            // FIND ')' AFTER '('
            else if (buffer[i] == ')' && regex_start_index != -1)
            {
                regex_end_index = i;
                
                // CHECK AFTHER THE ')'                
                int after_index = i + 1;

                if (REGEX_EXPRESSION_FOUND_LETTER_NUMBER(buffer[after_index]))
                {
                    regex_end_index = after_index;
                }
                else if (REGEX_EXPRESSION_FOUND_OPERATOR(buffer[after_index]))
                {
                    regex_end_index = after_index;
                }

                // DISPLAY REGULAR EXPRESSION
                printf("Regular expression found: ");

                for (int j = regex_start_index; j <= regex_end_index; j++)
                {
                    putchar(buffer[j]);
                }

                printf("\n");

                // COPY RE INTO A SEPARATE STRING
                int regex_length = regex_end_index - regex_start_index + 1;

                char regex[MAX_BUFFER_SIZE];

                for (int j = 0;
                     j < regex_length;
                     j++)
                {
                    regex[j] = buffer[regex_start_index + j];
                }

                regex[regex_length] = '\0';


                // CALL THE FUNCTION TO GENERATE POSSIBLE COMBINATIONS
                DISPLAY_POSSIBLE_COMBINATION(regex);
                printf("\n");

                // RESET REGULAR EXPRESSION INDEXES
                regex_start_index = -1;
                regex_end_index = -1;
            }
        }
    }
}

int main(void)
{
    FILE *file;
    char buffer[MAX_BUFFER_SIZE];

    file = fopen("C:\\Users\\junward\\Desktop\\ProgLang_Activity\\Data\\textfile1.txt", "r");


    if (file == NULL)
    {
        printf("File doesn't exist!");
        return 1;
    }

    printf("\n");
    DISPLAY_BINARY_NUMBER_TO_HEXADECIMAL(file, buffer, sizeof(buffer));

    rewind(file); // Reset file pointer to the beginning of the file

    DISPLAY_REGULAR_EXPRESSION_TO_PASSIBLE_STRING(file, buffer, sizeof(buffer));
    printf("\n");

    fclose(file);
    
    return 0;
}