/**
 * Four function calculator built using a parser generator.  The parser reads
 * the grammar for a calculator and generates tables of actions.  These action
 * tables are compiled along with user provided functions to implement the
 * calculator.
 */

#ifndef calculator_hpp
#define calculator_hpp

#include <string>
#include <vector>
#include <memory>
#include <map>

/**
 * Value is the base class of all arguments passed to the user defined functions
 * of the calculator.  The class provides a virtual destructor for releasing
 * memory during parsing.  
 */
class Value {
  public:
    virtual ~Value() = default;
};

class Num : public Value {
  public:
    Num(int value) : value(value) {}
    int value;
};

class Ident : public Value {
  public:
    Ident(const std::string& name) : name(name) {}
    std::string name;
};

/**
 * The symbol table is also passed to each user defined function associated with 
 * a grammar rule.
 */
class Table {
  public:    
    std::map<std::string, int> vars;
    bool done = false;
};

/**
 * Classes defined by the parser generator to read the text input accourding to
 * the rules of the grammar.  The grammar rules are written as a nonterminal
 * followed by zero or more symbols.  The parser generates a set of nodes for
 * identifying symbols in the input and a state machine for reducing the input
 * symbols by rules of the grammar.
 */

struct Symbol;
extern Symbol endmark;

struct Node;
extern Node node0;

struct State;
extern State state0;

/**
 * Calculator built with an action table from with a parser generator.
 */
class Calculator {
  public:
    void start();
    
    // advance the parser with the next input character
    bool scan(Table* table, int c);
    
    // advance the parser at the end of the input
    std::unique_ptr<Value> scan_end(Table* table);
    
  private:
    
    // state of the lexer and input characters of the current symbol
    Node* node = &node0;
    std::string text;
    
    // stack of the shift reduce parser
    std::vector<State*>  states;
    std::vector<Symbol*> symbols;
    std::vector<Value*>  values;
    
    // utility methods for modifying to the stack
    void push(State* state, Symbol* sym, Value* val);
    void pop(size_t count);
    
    // either shift the symbol onto the stack, or reduce by a rule
    bool advance(Table* table, Symbol* sym, Value* val);
};

#endif
