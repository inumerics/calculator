# Parser Generators

A parser generator simplifies the development of programs, such as calculators 
and compilers, by generating the source code needed for parsing input text. The 
generator accepts a user-defined grammar and constructs tables which dictate 
which functions to invoke while processing the input. These tables, combined 
with user-provided functions, are then compiled to produce the final program.

A popular method for defining a context-free grammar is the Backus-Naur Form. 
This grammar is characterized by two types of symbols: terminals and 
nonterminals. Terminals are enclosed in quotes and are represented by regular 
expressions, while nonterminals consist of sequences of symbols known as 
production rules. Below is an example grammar for a four-function calculator.

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

## Example Calculator Program

This source code serves as an example program that includes both a grammar and 
functions to implement a four-function calculator. Given the language of the 
calculator as input, the parser program generates action tables. These tables 
are then compiled alongside user-defined functions to construct the calculator 
program.

- [Grammar](https://github.com/inumerics/calculator/blob/main/source/calculator.bnf)
- [Header ](https://github.com/inumerics/calculator/blob/main/source/calculator.hpp)
- [Source ](https://github.com/inumerics/calculator/blob/main/source/calculator.cpp)

## Parser Generator Binary

The first step in building this calculator is to download the parser generator 
program. This program reads the grammar and generates the source code that 
defines which functions to call when processing user input.

- [Island Numerics Parser](https://islandnumerics.com)

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

