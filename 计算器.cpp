
#include <bits/stdc++.h>

using namespace std;

// 运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 执行运算
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // 这里未处理除以零的情况
    }
    return 0;
}

// 计算表达式
double evaluateExpression(const string& expression) {
    stack<double> values; // 存储数值
    stack<char> ops; // 存储运算符
    int n = expression.length();

    for (int i = 0; i < n; i++) {
        // 跳过空格
        if (isspace(expression[i])) continue;

        // 处理数字（包括小数）
        if (isdigit(expression[i]) || expression[i] == '.') {
            stringstream ss;
            while (i < n && (isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i];
                i++;
            }
            double value;
            ss >> value; // 转换为浮点数
            values.push(value);
            i--; // 退回一个字符
        }
        // 处理左括号
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        // 处理右括号
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(a, b, op));
            }
            ops.pop(); // 移除左括号
        }
        // 处理运算符
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(a, b, op));
            }
            ops.push(expression[i]);
        }
    }

    // 处理剩余的运算符
    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top(); // 返回最终结果
}

int main() {
    string expression;

    cout << "请输入一个表达式：";
    getline(cin, expression);

    double result = evaluateExpression(expression);
    cout << "结果是: " << fixed << setprecision(2) << result << endl;

    return 0;
}
