#include <stdio.h>

int main() {
    // Initialize variables
    int *p;
    int x;
    
    // Assign the value 10 to variable x
    x = 10;
    
    // Print the value of x
    printf("%d\n", x);
    
    // Assign the address of variable x to pointer p
    p = &x;
    
    // Print the address of variable x
    printf("%p\n", (void *)&x);
    
    // Using the dereference operator, directly modify the value at the address of x to 2
    *p = 2;
    
    // Print the value of x after modifying it using a pointer
    printf("%d\n", x);

    return 0;
}