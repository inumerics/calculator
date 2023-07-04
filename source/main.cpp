#include "calculator.hpp"
#include <iostream>
#include <sstream>

/**
 * The main function reads an input one character at a time until a symbol is
 * found.  When found, the precomputed actions determine if the symbol is pushed
 * onto the stack, or if the stack is reduced by a rule of the grammar.
 */
int
main(int argc, const char* argv[])
{
    if (argc != 2) {
        std::cerr << "Expected a single input string.\n";
        return 1;
    }

    Calculator calculator;
    calculator.start();

    Table table;

    std::stringstream in(argv[1]);

    std::unique_ptr<Value> result;

    while (true) {
        int c = in.get();
        if (c == EOF) {
            result = calculator.scan_end(&table);
            if (!result) {
                std::cerr << "Unexpected end of the input.\n";
                return 1;
            }
            break;
        }
        else {
            bool ok = calculator.scan(&table, c);
            if (!ok) {
                std::cerr << "Unexpected character.\n";
                return 1;
            }
        }
    }

    return 0;
}

