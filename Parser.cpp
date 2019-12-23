#include "Parser.h"

double Parser::Calculate(const std::string &op, double value1, double value2) {
    if (mapOperators.count(op) == 0) {
        return 0.0;
    }

    double result;

    switch (mapOperators[op]) {
        case Plus:
            result = value1 + value2;
            break;
        case Minus:
            result = value1 - value2;
            break;
        case Multiply:
            result = value1 * value2;
            break;
        case Divide:
            result = value1 / value2;
            break;
        case Modulo:
            result = fmod(value1, value2);
            break;
        case Power:
            result = pow(value1, value2);
            break;
        case Cos:
            result = cos(value1 * PI / 180);
            break;
        case Sin:
            result = sin(value1 * PI / 180);
            break;
        case Tan:
            result = tan(value1 * PI / 180);
            break;
        case Arccos:
            result = acos(value1 * PI / 180);
            break;
        case Arcsin:
            result = asin(value1 * PI / 180);
            break;
        case Arctan:
            result = atan(value1 * PI / 180);
            break;
        case Sqrt:
            result = sqrt(value1);
            break;
        default:
            result = 0.0;
            break;
    }

    return result;
}

std::pair<double, double> Parser::GetNumbers(std::string op, std::stack<double> *numbers) {
    if (numbers->empty()) {
        return std::make_pair(0.0, 0.0);
    }

    double value1 = numbers->top();
    numbers->pop();
    double value2 = 0.0;

    if (!numbers->empty() && mapNumbers[op] == 2) {
        value2 = numbers->top();
        numbers->pop();
    }

    return std::make_pair(value1, value2);
}

std::string Parser::GetOperator(std::stack<std::string> *operators) {
    if (operators->empty()) {
        return "Empty";
    }

    std::string op = operators->top();
    operators->pop();

    return op;
}

bool Parser::LowerPrecedence(const std::string &op1, const std::string &op2) {
    return mapPrecedence[op2] < mapPrecedence[op1];
}