#include <stdio.h>
#include <ctype.h>

int main() {
    // Open the file in read mode
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1; // Exit with an error code
    }

    int ch;
    int in_word = 0; // Flag to check if we're inside a word
    int word_count = 0;

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == '\n' || ch == '\t') {
            // If the character is a space, newline, or tab, we are not in a word
            if (in_word) {
                word_count++; // Increment word count when exiting a word
                in_word = 0;  // Reset the in_word flag
            }
        } else {
            // If the character is not whitespace, we're inside a word
            in_word = 1;
        }
    }

    // If the file ends while still in a word, count the last word
    if (in_word) {
        word_count++;
    }

    fclose(file); // Close the file
    printf("The file contains %d words.\n", word_count);
    return 0;
}