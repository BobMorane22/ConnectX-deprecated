#define PRINT_MACRO() std::cout << "macro"; // OK

#define PRINT_MESSAGE(__theMessage__) \
    std::cout << __theMessage__; // OK

#define printMessage(__theMessage__) \
    std::cout << __theMessage__; // Not OK, could be misinterpreted as a function name.

#define PRINT_MESSAGE(p_theMessage) \
    std::cout << p_message; // Not OK, same reason

