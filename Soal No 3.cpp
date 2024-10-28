#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
using namespace std;

class Stack {
private:
    vector<double> elements;
public:
    void push(double value) {
        elements.push_back(value);
    }

    double pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }
        double value = elements.back();
        elements.pop_back();
        return value;
    }

    bool isEmpty() const {
        return elements.empty();
    }

    double top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }
        return elements.back();
    }
};

double evaluatePostfix(const string &expression) {
    Stack stack;
    istringstream iss(expression);
    string token;

    cout << "Langkah-langkah evaluasi ekspresi postfix:\n";
    
    while (iss >> token) {

        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            double number = stod(token);
            stack.push(number);
            cout << "Push " << number << " ke stack\n";
        } 
    
        else {
            double operand2 = stack.pop();
            double operand1 = stack.pop();
            double result;

            if (token == "+") {
                result = operand1 + operand2;
            } else if (token == "-") {
                result = operand1 - operand2;
            } else if (token == "*") {
                result = operand1 * operand2;
            } else if (token == "/") {
                result = operand1 / operand2;
            } else if (token == "^") {
                result = pow(operand1, operand2);
            } else {
                throw runtime_error("Unknown operator: " + token);
            }

            stack.push(result);
            cout << "Pop " << operand1 << " dan " << operand2 << ", lalu " << operand1 << " " << token << " " << operand2 << " = " << result << "\n";
        }
    }

    double finalResult = stack.pop();
    if (!stack.isEmpty()) {
        throw runtime_error("Ekspresi postfix tidak valid.");
    }
    return finalResult;
}

int main() {
    string expression;
    cout << "Masukkan ekspresi postfix (contoh: '3 4 + 2 * 7 /'): ";
    getline(cin, expression);

    try {
        double result = evaluatePostfix(expression);
        cout << "Hasil dari ekspresi postfix adalah: " << result << endl;
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}