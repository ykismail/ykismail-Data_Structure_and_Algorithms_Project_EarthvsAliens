#ifndef PRINT_CONTROL_H
#define PRINT_CONTROL_H

#include <iostream>

extern bool SilentMode;

#define MY_COUT(message) \
    do { if (!SilentMode) {std::cout << message;} }while(0)

#endif // PRINT_CONTROL_H
