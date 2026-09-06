#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to check if a word consists ONLY of '0's and '1's
int is_binary_string(const char *word) {
    int len = strlen(word);

    if (len == 0) return 0;

    for (int i = 0; i < len; i++) {
        if (word[i] != '0' && word[i] != '1') {
            return 0; // Found a character that isn't 0 or 1
        }
    }
    return 1; // All characters are valid binary digits
}

// Function to clean punctuation around words (e.g., "10101," -> "10101")
void clean_token(char *dest, const char *src) {
    int start = 0, end = strlen(src) - 1;

    // Strip leading punctuation
    while (start <= end && ispunct((unsigned char)src[start])) {
        start++;
    }
    // Strip trailing punctuation
    while (end >= start && ispunct((unsigned char)src[end])) {
        end--;
    }

    int j = 0;
    for (int i = start; i <= end; i++) {
        dest[j++] = src[i];
    }
    dest[j] = '\0';
}

int main() {
    FILE *file = fopen("../textfile1.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char raw_word[256];
    char clean_word[256];
    int line_number = 1;

    // Read word by word across the text file
    while (fscanf(file, "%255s", raw_word) == 1) {
        // Strip out surrounding punctuation like commas or periods
        clean_token(clean_word, raw_word);

        // Analyze cleaned word
        if (is_binary_string(clean_word)) {
            printf("[Found Binary] \"%s\" (Original token: \"%s\")\n", clean_word, raw_word);
        }
    }

    fclose(file);
    return 0;
}
