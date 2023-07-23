#include "calculator.hpp"
#include <iostream>
#include <sstream>

/**
 * The main function reads an input one character at a time until a symbol is
 * found.  When found, the precomputed actions determine if the symbol is pushed
 * onto the stack, or if the stack is reduced by a rule of the grammar.
 */
int
main(int argc, const char * argv[])
{    
    Table table;

    Calculator calculator;
    calculator.start();
    std::cout << "> ";

    while (!table.done) 
    {
        int c = std::cin.get();
        if (c == '\n') {
            std::unique_ptr<Value> result = calculator.scan_end(&table);
            if (!result) {
                std::cerr << "Unexpected end of the input.\n";
                return 1;
            }
            if (!table.done) {
                std::unique_ptr<Num> num(dynamic_cast<Num*>(result.release()));

                std::cout << num->value << "\n";
                calculator.start();
                std::cout << "> ";
            }
        } 
        else {
            bool ok = calculator.scan(&table, c);
            if (!ok) {
                std::cerr << "Unexpected character '" << c <<  "'.\n";
                return 1;
            }
        }
    }
    
    return 0;
}

