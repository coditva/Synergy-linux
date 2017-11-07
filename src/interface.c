#include <stdio.h>

#include "interface.h"

/*
 * Presents the user with a yes, no question
 * @param char * the question to be asked
 * @param char * yes option display string
 * @param char * no option display string
 * @return int 1 if yes, 0 otherwise
 */
int interface_ask_yes_no(char *question, char *option1, char *option2)
{
    char answer;

    printf("\n!! %s\n", question);
    printf("1. %s\t2. %s\n\n", option1, option2);

    while (1) {
        printf(">> ");

        answer = fgetc(stdin);
        fgetc(stdin);                       /* read the newline character */

        if (answer == '1') return 1;
        if (answer == '2') return 0;
    }
}
