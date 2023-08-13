#include <stdio.h>

// Function declarations
int get_size();           // Prompts user for size input
void print_block(int n);  // Prints a square block of '#' characters

int main(void) {
    int n = get_size();    // Get size from user
    print_block(n);        // Print square block
    return 0;
}

// Function to get size input from user
int get_size() {
    int n;
    do {
        printf("Insert size: ");   // Prompt the user for input
        scanf("%d", &n);           // Read an integer from user
    } while (n < 0);              // Continue until a non-negative integer is entered
    return n;
}

// Function to print square block of '#' characters
void print_block(int n) {
    for (int i = 0; i < n; i++) {   // Loop for each row
        for (int j = 0; j < n; j++) {   // Loop for each column in the row
            printf("#");               // Print a '#' character
        }
        printf("\n");   // Move to the next line after printing a row
    }
}
