#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX_ERRORS 10
#define MAX_MESSAGE_LENGTH 256

typedef struct {
    int code;
    char message[MAX_MESSAGE_LENGTH];
} Error;

Error error_list[MAX_ERRORS];
int error_count = 0;

#define SET_ERROR(code, ...) \
    set_error_message(code, __VA_ARGS__)

void set_error_message(int code, const char* format, ...) {
    for (int i = 0; i < error_count; i++) {
        if (error_list[i].code == code) {
            printf("Error code %d already has a message: %s\n", code, error_list[i].message);
            return;
        }
    }

    if (error_count >= MAX_ERRORS) {
        printf("Error limit reached.\n");
        return;
    }

    va_list args;
    va_start(args, format);

    error_list[error_count].code = code;
    vsnprintf(error_list[error_count].message, MAX_MESSAGE_LENGTH, format, args);

    error_count++;
    va_end(args);
}

void print_error(int code) {
    for (int i = 0; i < error_count; i++) {
        if (error_list[i].code == code) {
            printf("Error Code %d: %s\n", code, error_list[i].message);
            return;
        }
    }
    printf("Error Code %d: Unknown error\n", code);
}

int main() {
   
    SET_ERROR(404, "File %s %s", "not", "found");
    SET_ERROR(500, "Internal %s %s", "server", "error");
    SET_ERROR(403, "%s %s", "Access", "denied");
    SET_ERROR(401, "Authorization %s %s", "failed", "user");

    
    SET_ERROR(404, "Duplicate error");

    print_error(404); 
    print_error(500); 
    print_error(403); 
    print_error(401); 
    print_error(402); 

    return 0;
}
