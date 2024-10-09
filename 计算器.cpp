
#include <bits/stdc++.h>

using namespace std;

// ��������ȼ�
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ִ������
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // ����δ�������������
    }
    return 0;
}

// ������ʽ
double evaluateExpression(const string& expression) {
    stack<double> values; // �洢��ֵ
    stack<char> ops; // �洢�����
    int n = expression.length();

    for (int i = 0; i < n; i++) {
        // �����ո�
        if (isspace(expression[i])) continue;

        // �������֣�����С����
        if (isdigit(expression[i]) || expression[i] == '.') {
            stringstream ss;
            while (i < n && (isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i];
                i++;
            }
            double value;
            ss >> value; // ת��Ϊ������
            values.push(value);
            i--; // �˻�һ���ַ�
        }
        // ����������
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        // ����������
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(a, b, op));
            }
            ops.pop(); // �Ƴ�������
        }
        // ���������
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

    // ����ʣ��������
    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top(); // �������ս��
}

int main() {
    string expression;

    cout << "������һ�����ʽ��";
    getline(cin, expression);

    double result = evaluateExpression(expression);
    cout << "�����: " << fixed << setprecision(2) << result << endl;

    return 0;
}
