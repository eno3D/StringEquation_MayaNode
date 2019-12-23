#include "StringEquation.h"
#include "Parser.h"

MTypeId StringEquation::id = SIMPLE_EQUATION_ID;
MString StringEquation::name = SIMPLE_EQUATION_NAME;
MObject StringEquation::equation_mobj;
MObject StringEquation::a_mobj;
MObject StringEquation::b_mobj;
MObject StringEquation::c_mobj;
MObject StringEquation::d_mobj;
MObject StringEquation::e_mobj;
MObject StringEquation::output_mobj;

StringEquation::StringEquation() = default;

StringEquation::~StringEquation() = default;

void *StringEquation::creator() {
    return new StringEquation();
}

MStatus StringEquation::initialize() {
    MStatus status;

    MFnTypedAttribute fn_typed;
    MFnNumericAttribute fn_numeric;

    equation_mobj = fn_typed.create("equation", "eq", MFnData::kString, MObject::kNullObj, &status);
    fn_numeric.setStorable(true);
    fn_numeric.setWritable(true);
    fn_numeric.setKeyable(true);

    a_mobj = fn_numeric.create("a", "a", MFnNumericData::kDouble, 0.0, &status);
    fn_numeric.setStorable(true);
    fn_numeric.setWritable(true);
    fn_numeric.setKeyable(true);

    b_mobj = fn_numeric.create("b", "b", MFnNumericData::kDouble, 0.0, &status);
    fn_numeric.setStorable(true);
    fn_numeric.setWritable(true);
    fn_numeric.setKeyable(true);

    c_mobj = fn_numeric.create("c", "c", MFnNumericData::kDouble, 0.0, &status);
    fn_numeric.setStorable(true);
    fn_numeric.setWritable(true);
    fn_numeric.setKeyable(true);

    d_mobj = fn_numeric.create("d", "d", MFnNumericData::kDouble, 0.0, &status);
    fn_numeric.setStorable(true);
    fn_numeric.setWritable(true);
    fn_numeric.setKeyable(true);

    e_mobj = fn_numeric.create("e", "e", MFnNumericData::kDouble, 0.0, &status);
    fn_numeric.setStorable(true);
    fn_numeric.setWritable(true);
    fn_numeric.setKeyable(true);

    output_mobj = fn_numeric.create("output", "out", MFnNumericData::kDouble, 0.0, &status);
    fn_numeric.setStorable(false);
    fn_numeric.setWritable(false);
    fn_numeric.setKeyable(false);

    addAttribute(equation_mobj);
    addAttribute(a_mobj);
    addAttribute(b_mobj);
    addAttribute(c_mobj);
    addAttribute(d_mobj);
    addAttribute(e_mobj);
    addAttribute(output_mobj);

    attributeAffects(equation_mobj, output_mobj);
    attributeAffects(a_mobj, output_mobj);
    attributeAffects(b_mobj, output_mobj);
    attributeAffects(c_mobj, output_mobj);
    attributeAffects(d_mobj, output_mobj);
    attributeAffects(e_mobj, output_mobj);

    return status;
}

MStatus StringEquation::compute(const MPlug &plug, MDataBlock &dataBlock) {
    if (plug == output_mobj) {
        MStatus status;

        // Get input data
        MDataHandle a_hdl = dataBlock.inputValue(a_mobj, &status);
        double a = a_hdl.asDouble();
        MDataHandle b_hdl = dataBlock.inputValue(b_mobj, &status);
        double b = b_hdl.asDouble();
        MDataHandle c_hdl = dataBlock.inputValue(c_mobj, &status);
        double c = c_hdl.asDouble();
        MDataHandle d_hdl = dataBlock.inputValue(d_mobj, &status);
        double d = d_hdl.asDouble();
        MDataHandle e_hdl = dataBlock.inputValue(e_mobj, &status);
        double e = e_hdl.asDouble();

        MDataHandle equation_hdl = dataBlock.inputValue(equation_mobj, &status);
        MString equation = equation_hdl.asString();

        // Convert string equation
        MStringArray equation_array;
        equation.split(' ', equation_array);

        MStringArray reverse_equation_array;
        if (equation_array.length() != 0) {
            for (int i = equation_array.length() - 1; i >= 0; i--) {
                reverse_equation_array.append(equation_array[i]);
            }
        }

        // shunting yard
        std::stack<double> numbers_stack;
        std::stack<std::string> operators_stack;

        for (const MString &element : reverse_equation_array) {
            // If element is a number push on the numbers stack
            if (element.isDouble() || element.isFloat() || element.isInt() ||
                element.isShort()) {
                numbers_stack.push(element.asDouble());
                continue;
            }

            // If element is one of the possible variables push the corresponding number on the numbers stack
            if (element == MString("a")) {
                numbers_stack.push(a);
                continue;
            }
            if (element == MString("b")) {
                numbers_stack.push(b);
                continue;
            }
            if (element == MString("c")) {
                numbers_stack.push(c);
                continue;
            }
            if (element == MString("d")) {
                numbers_stack.push(d);
                continue;
            }
            if (element == MString("e")) {
                numbers_stack.push(e);
                continue;
            }

            // If element is one of the possible operators, either push directly on the operator stack or calculate first
            if (Parser::mapOperators.find(element.asChar()) != Parser::mapOperators.end()) {
                if (!operators_stack.empty() && Parser::LowerPrecedence(operators_stack.top(), element.asChar())) {
                    std::string op = Parser::GetOperator(&operators_stack);
                    std::pair<double, double> nextNumbers = Parser::GetNumbers(op, &numbers_stack);

                    numbers_stack.push(Parser::Calculate(op, nextNumbers.first, nextNumbers.second));
                }
                operators_stack.push(element.asChar());
                continue;
            }

            // If element is a closing bracket push to the operator stack
            if (element == MString(")")) {
                operators_stack.push(element.asChar());
                continue;
            }

            // If element is a opening bracket, calculate the equation until the closing bracket is found
            if (element == MString("(")) {
                while (!operators_stack.empty() && operators_stack.top() != ")") {
                    std::string op = Parser::GetOperator(&operators_stack);
                    std::pair<double, double> nextNumbers = Parser::GetNumbers(op, &numbers_stack);

                    numbers_stack.push(Parser::Calculate(op, nextNumbers.first, nextNumbers.second));
                }
                operators_stack.pop();
                continue;
            }
            return MStatus::kInvalidParameter;
        }

        // Calculate
        while (!operators_stack.empty()) {
            std::string op = Parser::GetOperator(&operators_stack);
            std::pair<double, double> nextNumbers = Parser::GetNumbers(op, &numbers_stack);

            numbers_stack.push(Parser::Calculate(op, nextNumbers.first, nextNumbers.second));
        }

        // Set output
        MDataHandle output_hdl = dataBlock.outputValue(output_mobj, &status);
        if (!numbers_stack.empty()) {
            output_hdl.setDouble(numbers_stack.top());
        } else {
            output_hdl.setDouble(0);
        }

        output_hdl.setClean();

        return status;
    } else {
        return MStatus::kUnknownParameter;
    }
}