# Parser Generator

A parser generator simplifies the development of programs such as calculators
and compilers by writing the source code for parsing input text.  The generator
takes a user defined grammar and builds tables that define which functions
to call while reading the input.  These tables along with the user provided 
functions are then compiled together to build the final program.

A common way to define a context free grammar is the Backus-Naur Form.  The
grammar is defined by two types of symbols: terminals and nonterminals.  The
terminals are shown in quotes and are defined by a regular expression.  The
nonterminals are a sequence of symbols known as a production rule.  The
following text is an example grammar for a four function calculator.

```
'num'<Expr>  [0-9]+     &scan_num;

total<Expr>: add        &reduce_total
    ;
add<Expr>: mul
    | add '+' mul       &reduce_add_mul
    | add '-' mul       &reduce_sub_mul
    ;
mul<Expr>: num
    | mul '*' num       &reduce_mul_int
    | mul '/' num       &reduce_div_int
    | '(' add ')'       &reduce_paren
    ;
```

## Defining the Terminals
Terminals represent the smallest unit of the language, such as a number or an 
operator. This parser generator uses the regular expression syntax to provide an 
easy way to define terminals. As an example, the following line defines a 
number terminal whos string consists of one or more digits.

```
    'num' [0-9]+;
```
    
The regular expression syntax provides operators for matching patterns, such as 
repeated letters or numbers. The + operator indicates that the match contains 
one or more of the previous character and the \* operator matches zero or more.
Finally, the ? marks that the previous character is optional.

As shown with the previous definition of a number, the syntax also allows 
matching a range of characters by using brackets and a dash between the first 
and last characters in the range. To enable more complex patterns, the vertical 
bar, |, defines an expression that matches either one of patterns on the two 
sides of the bar. This operator is seen in the definition of a hexadecimal 
number, which is comprised of digits or the letters A through F.

```
    'hex'<Value>  0x([A-Z]|[0-9])+   &scan_hex;
```
    
The addition of parenthesis is the last operator needed to fully utilize the 
syntax of regular expressions. Since there is a defined operator precedence, the 
parenthesis allows the grouping of an expression to control the order of 
operations when reading the pattern.

## Defining the Nonterminals
The nonterminals are defined as a sequence of symbols known as a production 
rule.  These rules are written as a nonterminal followed by zero or more 
symbols. If there is more than one possible rule associated the same 
nonterminal, they are separated by a vertical bar. A semicolon indicates the end 
of the rules for a given nonterminal. The following statement defines a 
multiplication product to be either a number, or a previous product times a 
number.

```
    mult: 'num' | mult '*' 'num';
```

For convenience, terminals can also be defined within a production rule of the 
nonterminal. This is shown in the previous grammar when defining the rule for 
addition or multiplication using the + and \* infix operators. When written 
within a rule the terminal is not defined using a regular expression, but a 
series of printable characters. This simple definition allows characters which 
are normally regular expression operators to act as a terminal in the grammar. 

## Example Calculator Program

This source code includes an example program with a grammar and functions that
implement a four function calculator.  With the calculator's language as an
input, this parser program generates the tables of actions.  These action tables 
are then compiled along with the user defined functions to build a calculator
program.

- [Calculator Grammar](https://github.com/inumerics/calculator/blob/main/source/calculator.bnf)
- [Calculator Header ](https://github.com/inumerics/calculator/blob/main/source/calculator.hpp)
- [Calculator Source ](https://github.com/inumerics/calculator/blob/main/source/calculator.cpp)
