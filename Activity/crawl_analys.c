#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define BUFFER_SIZE 1024

int main(void)
{
    FILE *file;
    char buffer[BUFFER_SIZE];

    regex_t regex;
    regmatch_t match;

    /*
     * Pattern for a binary number:
     * One or more 0s or 1s surrounded by word boundaries.
     */
    const char *pattern = "\\b[01]+\\b";

    /* Open the text file */
    file = fopen("../textfile2.txt", "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    /* Compile the regular expression */
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Error compiling regular expression.\n");
        fclose(file);
        return 1;
    }

    printf("Scanning file...\n\n");

    /* Read the file line by line */
    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        char *text = buffer;

        /*
         * Continue searching until there are
         * no more matches in the current line.
         */
        while (regexec(&regex, text, 1, &match, 0) == 0)
        {
            int length = match.rm_eo - match.rm_so;

            printf("Binary number found: ");

            for (int i = 0; i < length; i++)
            {
                putchar(text[match.rm_so + i]);
            }

            printf("\n");

            /*
             * Move the search position after
             * the current match.
             */
            text += match.rm_eo;
        }
    }

    /* Free regex resources */
    regfree(&regex);

    /* Close the file */
    fclose(file);

    return 0;
}