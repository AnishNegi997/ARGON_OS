#include "../kernel/screen.h"
#include "../kernel/keyboard.h"
#include "shell.h"
#include "commands.h"
#include <stddef.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 16

// Buffer for command input
static char input[MAX_COMMAND_LENGTH];
static int pos = 0;

// Handle keyboard input
void handle_input(char c) {
    if (c == '\n') {
        print_string("\n");
        input[pos] = '\0';
        
        // Execute command
        execute_command(input);
        
        // Reset input buffer
        pos = 0;
        print_string("$ ");
    }
    else if (c == '\b') {
        if (pos > 0) {
            pos--;
            backspace();
        }
    }
    else if (pos < MAX_COMMAND_LENGTH - 1) {
        input[pos++] = c;
        print_char(c);
    }
}

// Initialize shell
void init_shell(void) {
    clear_screen();
    print_string("Welcome to AGRAN OS v0.1\n");
    print_string("Type 'help' for a list of commands\n\n");
    print_string("$ ");
    pos = 0;
}

// Run the shell
void run_shell(void) {
    while (1) {
        handle_input(getchar());
    }
}

// Move cursor back and clear character
void backspace(void) {
    print_char('\b');  // Move cursor back
    print_char(' ');   // Clear the character
    print_char('\b');  // Move cursor back again
} 