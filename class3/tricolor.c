#include <stdlib.h>

#define N_TRITS 243
char *trit_encodings[N_TRITS];

int main(void) {
    // at the very beginning of your program, making the table
    for (int i = 0; i < N_TRITS; i++) {
        trit_encodings[i] = calloc(sizeof(char), 6);
        // ADD YOUR CODES HERE
    }

    // ADD YOUR CODES HERE

    // at the very end of your program, cleaning up memory
    for (int i = 0; i < N_TRITS; i++) {
        free(trit_encodings[i]);
    }
    return 0;
}
