#include <stdio.h>

// Define a function pointer type for the callback
typedef void (*CallbackFunction)();

// Function that performs an operation and calls back the provided callback function
void wait_for_c(CallbackFunction callback) {
    char input;
    printf("Enter a character: ");
    scanf(" %c", &input);

    if (input == 'C') {
        callback();
    } else {
        printf("Character '%c' entered. Callback not triggered.\n", input);
    }
}

// Callback function implementation
void callback_function() {
    printf("Callback function triggered because 'C' was entered!\n");
}

int main() {
    // Example usage: Registering and invoking the callback
    wait_for_c(callback_function);

    return 0;
}
