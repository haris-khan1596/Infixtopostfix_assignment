#include <iostream>
#include <cmath>

using namespace std;

class Stack
{
    /*
    A stack class implemented using dynamic string array
    */
private:
    int size = 2;
    string *array = new string[size];
    int length = 0;

    bool isEmpty()
    {
        return length == 0;
    }

    bool isFull()
    {
        return length == size - 1;
    }

    string *increaseSize()
    {
        // create a new array
        string *newArray = new string[size];
        // copy the data from the old array to the new array
        for (int i = 0; i <= length; i++)
        {
            newArray[i] = array[i];
        }
        return newArray;
    }

    void growArray()
    {
        size *= 2;
        array = increaseSize();
    }

public:
    int len()
    {
        return length;
    }
    string peak()
    {
        if (isEmpty())
            return "";

        return array[length];
    }

    void push(string element)
    {
        if (isFull())
            growArray();
        array[++length] = element;
    }

    void push(char element)
    {
        if (isFull())
            growArray();
        array[++length] += element;
    }

    void pop()
    {
        if (!isEmpty())
        {
            array[length] = "";
            length--;
        }
    }
};

// checks if the character is a digit
bool isDigit(char character)
{
    return (character >= 48 && character <= 57); //ascii (48) = 0 and ascii(57)=9
}

// checks if the character is an operator
bool isOperator(char character)
{
    if ((character == '^') || (character == '/') || (character == '*') || (character == '+') || (character == '-'))
        return true;
    else
        return false;
}

// returns the precedance of the operator
int getPrecedance(char character)
{
    if (character == '^')
        return 3;
    if ((character == '/') || (character == '*'))
        return 2;
    if ((character == '+') || (character == '-'))
        return 1;
    return 0;
}

// converts the infix to postfix expression
string infixToPostfix(string infix)
{

    Stack stack;
    string postfix;

    for (int i = 0; i < infix.length(); i++)
    {
        // var to keep track of current number (numbers with 2 or more digits)
        string current = "";
        current += infix[i];

        // for digit append to the output string
        if (isDigit(infix[i]))
            postfix += current;

        // for opening brace push to the stack
        else if (infix[i] == '(')
            stack.push("(");

        // for closing brace append all operators to the postfix
        else if (infix[i] == ')')
        {
            while (stack.peak() != "(")
            {
                postfix += stack.peak();
                stack.pop();
            }
            // remove opening brace from stack
            stack.pop();
        }
        // on operator compare precedence and push the operator to stack
        else if (isOperator(infix[i]))
        {
            // on equal precendance remove previous operator and add current to the stack
            while (stack.peak() != "" && getPrecedance(infix[i]) <= getPrecedance(stack.peak()[0]))
            {
                postfix += stack.peak();
                stack.pop();
            }
            stack.push(current);
            postfix += " ";
        }
    }

    // empty the opeartors in the stack and append them to postfix expression
    while (stack.peak() != "")
    {
        postfix += stack.peak();
        stack.pop();
    }
    // return the postfix expression
    return postfix;
}

int performOperation(int left, int right, char operation)
{
    switch (operation)
    {
    case '^':
        return pow(double(left), double(right));
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    default:
        return 0;
    }
}

int toInteger(string intstring)
{
    int number = 0;
    for (int i = 0; i < intstring.length(); i++)
    {
        int integer = 0;
        if (isdigit(intstring[i]))
        {
            integer = intstring[i] - 48;
        }
        number = number * 10 + integer;
    }
    return number;
}

// evalutes the postfix expression and returns the result
int evaluatePostFix(string postfix)
{
    string prev = "";
    Stack stack;
    int right, left;
    int result = 0;
    for (int i = 0; i < postfix.length(); i++)
    {
        if (isdigit(postfix[i]))
        {
            if (prev != "")
            {
                stack.pop();
            }
            prev += postfix[i];
            stack.push(prev);
        }
        else if (postfix[i] == ' ')
        {
            prev = "";
        }

        else if (isOperator(postfix[i]))
        {
            prev = "";
            right = toInteger(stack.peak());
            stack.pop();
            left = toInteger(stack.peak());
            result = performOperation(left, right, postfix[i]);
            stack.pop();
            stack.push(to_string(result));
        }
    }
    return toInteger(stack.peak());
}

// string validation funcitons
bool valid_num_of_Brackets(string input)
{
    Stack stack;
    // checking the string input
    for (int i = 0; i < input.length(); i++)
    {
        // if the character is opening brace then add it to the stack
        if (input[i] == '{' || input[i] == '[' || input[i] == '(')
            stack.push(input[i]);

        // if the character is a closing brace and matches with character in the stack then pop character from the stack
        if ((input[i] == ')' && stack.peak() == "(") || (input[i] == '}' && stack.peak() == "{") || (input[i] == ']' && stack.peak() == "["))
        {
            stack.pop();
        }
        // if the expression contains closing braces without matching closing brace in stack then expression is invalid
        else if ((input[i] == ')') || (input[i] == '}') || (input[i] == ']'))
        {
            return false;
        }
    }
    // if the expression contains any opening braces without matching closing braces in stack then expression is invalid
    if (stack.peak() != "")
    {
        return false;
    }
    return true;
}

// checks if the string consists of valid characters
bool valid_Characters(string infix)
{
    for (int i = 0; i < infix.length(); i++)
    {
        if (!((isDigit(infix[i])) || (infix[i] == '(' || infix[i] == ')') || (isOperator(infix[i])) || infix[i] == ' '))
            return false;
    }
    return true;
}

// checks the number of operators and operands in the infix string
bool valid_num_of_Operators(string infix)
{
    string prev = "";
    Stack numberstack;
    Stack opreatorstack;
    // convert the stirng to stack
    for (int i = 0; i < infix.length(); i++)
    {
        if (isDigit(infix[i]) && isDigit(infix[i - 1]))
        {
            numberstack.pop();
            prev += infix[i];
            numberstack.push(prev);
        }
        else if (isDigit(infix[i]))
        {
            prev = "";
            prev += infix[i];
            numberstack.push(prev);
        }
        else if (infix[i] == ' ')
        {
            prev = "";
        }
        else if (isOperator(infix[i]))
        {
            prev = "";
            prev += infix[i];
            opreatorstack.push(prev);
        }
    }
    if (opreatorstack.len() == (numberstack.len() - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// function that calls all the test cases and ensures that the string is valid
bool vaildateInfix(string infix)
{
    bool flag = true;
    // infix string should not be empty
    if ((infix == "") || (infix == " "))
    {
        cout << "Error!\nInfix string cannot be empty";
        flag = false;
    }
    // infix string should not begin with operator
    if (isOperator(infix[0]))
    {
        cout << "Error!\nInfix string cannot begin with an operator";
        flag = false;
    }
    // infix string should have valid number of braces
    if (!valid_num_of_Brackets(infix))
    {
        cout << "Error!\nInfix string contains invalid number of brackets";
        flag = false;
    }
    // infix string should not have invalid characters
    if (!valid_Characters(infix))
    {
        cout << "Error!\nInfix string contains invalid characters\nNote that special only numbers, operators (+,-,*,/) and brackets ('()')";
        flag = false;
    }
    // infix string should have number of operators (two operators for every operand)
    if (!valid_num_of_Operators(infix))
    {
        cout << "Error!\nInfix string contains invalid number of operators and operands";
        flag = false;
    }
    return flag;
}

// main function to test the class
int main()
{

    string infix;
    string postfix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);
    if (vaildateInfix(infix))
    {
        postfix = infixToPostfix(infix);
        cout << "Infix Expression: " << infix << "\n\n"
             << "Postfix Expression: " << postfix << endl
             << "Evaluation: " << evaluatePostFix(postfix) << "\n\n";
    }

    return 0;
}
