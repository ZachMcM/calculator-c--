#include <iostream>
#include <stack>
#include <string>
using namespace std;

int getPrecedence(char op) {
    if (op == '-' || op == '+') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }    
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

double evaluate(string expression) {
    stack<double> values;
    stack<char> ops;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (isdigit(expression[i])) {
            double num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(num);
        }
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (ops.top() != '(') {
                double v2 = values.top();
                values.pop();

                double v1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(v1, v2, op));
            }
            ops.pop();
        } 
        else {
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expression[i])) {
                double v2 = values.top();
                values.pop();

                double v1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();
                
                values.push(applyOp(v1, v2, op));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        double v2 = values.top();
        values.pop();

        double v1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();
        
        values.push(applyOp(v1, v2, op));
    }

    return values.top();
}

int main() {
    cout << "Enter your expression! \n";
    string userExpression;
    cin >> userExpression;
    cout << evaluate(userExpression);
    return 0;
}