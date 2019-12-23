#ifndef PARSER_GUARD
#define PARSER_GUARD

#include <string>
#include <tuple>
#include <map>
#include <stack>

namespace Parser {
    static double PI = 3.14159265;

    enum Operators {
        Plus,
        Minus,
        Multiply,
        Divide,
        Modulo,
        Power,
        Sin,
        Cos,
        Tan,
        Arcsin,
        Arccos,
        Arctan,
        Sqrt,
    };

    static std::map<std::string, Operators> mapOperators{
            {"+",      Plus},
            {"-",      Minus},
            {"*",      Multiply},
            {"/",      Divide},
            {"%",      Modulo},
            {"^",      Power},
            {"sin",    Sin},
            {"cos",    Cos},
            {"tan",    Tan},
            {"arcsin", Arcsin},
            {"arccos", Arccos},
            {"arctan", Arctan},
            {"sqrt",   Sqrt},
    };

    static std::map<std::string, int> mapPrecedence{
            {"+",      1},
            {"-",      1},
            {"*",      2},
            {"/",      2},
            {"%",      2},
            {"^",      3},
            {"sin",    4},
            {"cos",    4},
            {"tan",    4},
            {"arcsin", 4},
            {"arccos", 4},
            {"arctan", 4},
            {"sqrt",   4},
    };

    static std::map<std::string, int> mapNumbers{
            {"+",      2},
            {"-",      2},
            {"*",      2},
            {"/",      2},
            {"%",      2},
            {"^",      2},
            {"sin",    1},
            {"cos",    1},
            {"tan",    1},
            {"arcsin", 1},
            {"arccos", 1},
            {"arctan", 1},
            {"sqrt",   1},
    };

    double Calculate(const std::string &op, double value1, double value2 = 0.0);

    std::pair<double, double> GetNumbers(std::string op, std::stack<double> *numbers);

    std::string GetOperator(std::stack<std::string> *operators);

    bool LowerPrecedence(const std::string &op1, const std::string &op2);
};

#endif