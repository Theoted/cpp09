#include <iostream>
#include <stack>
#include <sstream>

void printStack(std::stack<int> tmp)
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

int evaluateRPN(std::string rpnExpr)
{
    std::stack<int> st;
    std::stringstream ss(rpnExpr);

    while (!ss.eof())
    {
        std::string token;
        ss >> token;

        if (isDigits(token)
            && (token != "*" && token != "/" && token != "+" && token != "-"))
        {
            std::cerr << "Error: bad input\n";
            return (-1);
        }

        std::cout << "token = " << token << std::endl;
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            int op2 = st.top();
            st.pop();
            int op1 = st.top();
            st.pop();

            std::cout << "op1 = " << op1 << " op2 = " << op2 << std::endl;

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
            int operand;
            std::stringstream(token) >> operand;
            st.push(operand);
        }
        printStack(st);
        std::cout << "\n\n";
    }
    return (st.top());
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "./RPN [expression]" << std::endl;
        return (-1);
    }
    int result = evaluateRPN(av[1]);
    std::cout << result << std::endl;
    return (0);
}