#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

# define BOLD_BRIGHT_GREEN "\033[1;92m"
# define BOLD_BRIGHT_RED "\033[1;91m"
# define BACKGROUND_BRIGHT_RED "\033[0;101m"
# define BOLD_BRIGHT_YELLOW "\033[1;93m"
# define RESET "\x1B[0m" 

void trim_and_reduce_spaces(char *str) {
    char *src = str;
    char *dst;
    int len = strlen(src);

    // Step 1: Remove newline character at the end if it exists
    if (len > 0 && src[len - 1] == '\n') {
        src[len - 1] = '\0';
        len--;
    }

    // Step 2: Skip leading whitespaces
    while (isspace((unsigned char) *src)) {
        src++;
    }

    // Step 3: Allocate memory for the new string (same size as original for safety)
    dst = (char *)malloc(len + 1);
    if (dst == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    // Step 4: Copy and reduce spaces
    char *write_ptr = dst;
    int space_found = 0;

    while (*src != '\0') {
        if (isspace((unsigned char) *src)) {
            space_found = 1;
            src++; // Move to the next character
        } else {
            if (*src == ',') {
                // Handle spaces around commas
                if (write_ptr != dst && isspace((unsigned char) *(write_ptr - 1))) {
                    write_ptr--; // Remove space before comma
                }
                *write_ptr++ = *src++; // Copy the comma and move to the next character
                while (isspace((unsigned char) *src)) {
                    src++; // Skip spaces after comma
                }
                space_found = 0;
            } else {
                if (space_found && write_ptr != dst) {
                    *write_ptr++ = ' ';
                }
                *write_ptr++ = *src++;
                space_found = 0;
            }
        }
    }

    // Step 5: Remove trailing spaces
    *write_ptr = '\0';
    if (write_ptr != dst) {
        write_ptr--;
        while (write_ptr >= dst && isspace((unsigned char) *write_ptr)) {
            *write_ptr-- = '\0';
        }
    }

    // Step 6: Copy t_result back to original string
    strcpy(str, dst);
    free(dst);
}

// int main() {
//     char str[] = "     Color           255      ,  32                        ,               213                 \n";
//     printf("Original: '%s'\n", str);
//     trim_and_reduce_spaces(str);
//     printf("Processed: '%s'\n", str);
//     return 0;
// }

int main() {
    char str1[] = "  	NO	  		 	./textures/test/north.xpm\n			  	";
    printf("Original: '%s'\n", str1);
    trim_and_reduce_spaces(str1);
    printf("\xE2\x9C\x94 Processed: '%s'\n", str1);

    char str2[] = "     Color           255      ,  32                        ,               213                 \n";
    printf("Original: '%s'\n", str2);
    trim_and_reduce_spaces(str2);
    printf(BOLD_BRIGHT_GREEN" \xE2\x9C\x94 Processed: '%s'\n" RESET, str2);
	printf(" \xE2\x9C\x94 check mark\n");
	printf(" \u2713 light check mark\n");

	printf(BOLD_BRIGHT_GREEN " \u2714 " RESET);
	printf("heavy check mark\n");

	printf(BOLD_BRIGHT_RED " \u2718 " RESET);
	printf("heavy cross mark\n");
	printf(" \u2717 light cross mark\n");
	printf(" \u274c red cross mark\n");

	printf(BOLD_BRIGHT_YELLOW " \xE2\x9A\xA0 " RESET);
	printf ("Warning mark\n");
    return 0;
}