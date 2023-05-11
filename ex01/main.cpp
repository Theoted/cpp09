#include <iostream>
#include <stack>
#include <sstream>

void printStack(std::stack<float> tmp)
{
    std::cout << "stack: \n";
    while (!tmp.empty())
    {
        std::cout << tmp.top() << " ";
        tmp.pop();
    }
    std::cout << std::endl;
}

int isDigits(const std::string &str)
{
    for (int i = 0; str[i]; i++)
    {
        if (!(str[i] >= 48 && str[i] <= 57))
        {
            return (1);
        }
    }
    return (0);
}

bool stackSizeError(std::stack<float> st)
{
    if (st.size() == 0)
    {
        std::cerr << "Error: bad input" << std::endl;
        return (false);
    }
    return (true);
}

float evaluateRPN(std::string rpnExpr)
{
    std::stack<float> st;
    std::stringstream ss(rpnExpr);

    while (!ss.eof())
    {
        std::string token;
        ss >> token;

        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (!stackSizeError(st))
                return (-1);
            float op2 = st.top();
            st.pop();

            if (!stackSizeError(st))
                return (-1);
            float op1 = st.top();
            st.pop();


            if (token == "+")
                st.push(op1 + op2);
            else if (token == "-")
                st.push(op1 - op2);
            else if (token == "*")
                st.push(op1 * op2);
            else if (token == "/")
                st.push(op1 / op2);
        }
        else
        {
            int operand = 0;
            std::stringstream(token) >> operand;

            if (isDigits(token) || operand > 9 || operand < 0)
            {
                std::cerr << "Error: bad input" << std::endl;
                return (-1);
            }

            if (operand == 0 && token == "")
                continue;

            st.push(operand);
        }
    }
    if (st.size() == 1)
        std::cout << st.top() << std::endl;
    else
        std::cout << "Error: bad notation" << std::endl;
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "./RPN [expression]" << std::endl;
        return (-1);
    }
    evaluateRPN(av[1]);
    return (0);
}
