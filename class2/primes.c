#include <stdio.h>

int main(void) {
    printf("Enter a number to factorize:\n");
    int number = 0;
    int vals_read = scanf("%d", &number);
    if (vals_read != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return 1;
    }

    return 0;
}
