
/*
Cú pháp nhập:
cd D:\24120139\24120139\x64\Debug\
.\24120139.exe tests.txt output_24120139.txt
*/


#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <sstream>
using namespace std;
struct BigInt {
	string digits;
	bool isNegative = false;
};
BigInt createBigInt(string num) {
	BigInt result;
	result.isNegative = false;
	int i = 0;
	while (i < num.size() && num[i] == ' ') i++;
	if (i < num.size() && num[i] == '-') {
		result.isNegative = true;
		i++;
	}
	while (i < num.size() && num[i] == ' ') i++;
	result.digits = num.substr(i);
	while (result.digits.size() > 1 && result.digits[0] == '0') {
		result.digits.erase(0, 1);
	}
	if (result.digits.empty()) result.digits = "0";
	return result;
}
void printBigInt(BigInt a) {
	if (a.isNegative && a.digits != "0") cout << "-";
	cout << a.digits << endl;
}
int compareAbs(string a, string b) {
	if (a.size() != b.size()) return (a.size() > b.size()) ? 1 : -1;
	return a.compare(b);
}
string stringAdd(string x, string y) {
	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());
	string result = "";
	int carry = 0;
	int i = 0;
	while (i < x.size() || i < y.size() || carry) {
		int sum = carry;
		if (i < x.size()) {
			sum += x[i] - '0';
		}
		if (i < y.size()) {
			sum += y[i] - '0';
		}
		carry = sum / 10;
		result += (sum % 10) + '0';
		i++;
	}
	reverse(result.begin(), result.end());
	return result;
}
string stringSub(string x, string y) {
	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());
	string result = "";
	int borrow = 0;
	int i = 0;
	while (i < x.size()) {
		int diff = borrow;
		if (i < x.size()) {
			diff += (x[i] - '0');
		}
		if (i < y.size()) {
			diff -= (y[i] - '0');
		}
		if (diff < 0) {
			diff += 10;
			borrow = -1; 
		}
		else {
			borrow = 0;
		}
		result += (diff + '0');
		i++;
	}
	while (result.size() > 1 && result.back() == '0') {
		result.pop_back();
	}
	reverse(result.begin(), result.end());
	if (result.empty()) result = "0";
	return result;
}
BigInt addBigInt(BigInt a, BigInt b) {
	BigInt result;
	if (a.isNegative == b.isNegative) {
		result.digits = stringAdd(a.digits, b.digits);
		result.isNegative = a.isNegative;
	}
	else {
		int cmp = compareAbs(a.digits, b.digits);
		if (cmp == 0) {
			result.digits = "0";
			result.isNegative = false;
		}
		else if (cmp > 0) {
			result.digits = stringSub(a.digits, b.digits);
			result.isNegative = a.isNegative;
		}
		else {
			result.digits = stringSub(b.digits, a.digits);
			result.isNegative = b.isNegative;
		}
	}
	return result;
}
BigInt subtractBigInt(BigInt a, BigInt b) {
	// a - b = a + (-b)
	b.isNegative = !b.isNegative;
	return addBigInt(a, b);
}
BigInt multiplyBigInt(BigInt a, BigInt b) {
	int lenA = static_cast<int>(a.digits.size());
	int lenB = static_cast<int>(b.digits.size());
	string result(lenA + lenB, '0');
	for (int i = lenA - 1; i >= 0; i--) {
		int carry = 0;
		for (int j = lenB - 1; j >= 0; j--) {
			int mul = (a.digits[i] - '0') * (b.digits[j] - '0') + carry + (result[i + j + 1] - '0');
			result[i + j + 1] = (mul % 10) + '0';
			carry = mul / 10;
		}
		result[i] = (result[i] - '0' + carry) + '0';
	}
	int start = 0;
	while (start < result.size() - 1 && result[start] == '0') start++;
	result = result.substr(start);

	BigInt ans;
	ans.digits = result;
	ans.isNegative = (a.isNegative != b.isNegative && result != "0");
	return ans;
}
BigInt subtractAbs(BigInt a, BigInt b) {
	string x = a.digits, y = b.digits;
	// Padding số 0 cho y
	while (y.size() < x.size())
		y = "0" + y;

	string result = "";
	int borrow = 0;
	for (int i = (int)x.size() - 1; i >= 0; --i) {
		int d1 = x[i] - '0';
		int d2 = y[i] - '0' + borrow;

		if (d1 < d2) {
			d1 += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}

		result.push_back((d1 - d2) + '0');
	}

	// Đảo chuỗi và xoá số 0 đầu
	reverse(result.begin(), result.end());
	result.erase(0, result.find_first_not_of('0'));
	if (result.empty()) result = "0";

	BigInt res;
	res.digits = result;
	res.isNegative = false;
	return res;
}
BigInt divide(BigInt a, BigInt b, ostream& out) {
	BigInt result;
	result.isNegative = (a.isNegative != b.isNegative);
	result.digits = "";
	if (b.digits == "0") {
		cout << "Error: Divide by zero!\n";
		out << "Error: Divide by zero!\n";
		exit(1);
	}
	if (compareAbs(a.digits, b.digits) < 0) {
		result.digits = "0";
		result.isNegative = false; 
		return result;
	}
	BigInt cur;
	cur.digits = "";
	cur.isNegative = false;
	string quotient = "";
	for (int i = 0;i < a.digits.size();i++) {
		cur.digits += a.digits[i];
		while (cur.digits.size() > 1 && cur.digits[0] == '0') {
			cur.digits.erase(0, 1);
		}
		int x = 0;
		while (compareAbs(cur.digits, b.digits) >= 0) {
			cur = subtractAbs(cur, b);
			x++;
		}
		quotient += (x + '0');
	}
	int i = 0;
	while (i < quotient.size() - 1 && quotient[i] == '0') i++;
	result.digits = quotient.substr(i);
	if (result.digits == "0") result.isNegative = false;
	return result;
}
// Hàm kiểm tra độ ưu tiên của toán tử
int precedence(char op) {
	if (op == '+' || op == '-') return 1; // Ưu tiên thấp
	if (op == '*' || op == '/') return 2; // Ưu tiên cao
	return 0; // Không phải toán tử
}
// Hàm kiểm tra xem ký tự có phải là toán tử không
bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}
string infixToPostfix(string expr) {
	stack<char> operators;
	string postfix = "";
	string number = "";
	bool expectOperand = true;
	for (size_t i = 0; i < expr.size(); i++) {
		char c = expr[i];
		if (c == ' ') continue;
		// Xử lý số hoặc số âm
		if (isdigit(c) || (c == '-' && (expectOperand || (i > 0 && expr[i - 1] == '(')))) {
			number += c;
			i++;
			while (i < expr.size() && isdigit(expr[i])) {
				number += expr[i];
				i++;
			}
			postfix += number + " ";
			number = "";
			expectOperand = false;
			i--; // Quay lại để xử lý ký tự tiếp theo
		}
		else {
			if (!number.empty()) {
				postfix += number + " ";
				number = "";
			}

			if (c == '(') {
				operators.push(c);
				expectOperand = true;
			}
			else if (c == ')') {
				while (!operators.empty() && operators.top() != '(') {
					postfix += operators.top();
					postfix += " ";
					operators.pop();
				}
				if (operators.empty()) {
					return "Error: Mismatched parentheses";
				}
				operators.pop(); // Bỏ '('
				expectOperand = false;
			}
			else if (isOperator(c)) {
				if (expectOperand && c != '-') {
					return "Error: Invalid operator position";
				}
				while (!operators.empty() && operators.top() != '(' &&
					precedence(operators.top()) >= precedence(c)) {
					postfix += operators.top();
					postfix += " ";
					operators.pop();
				}
				operators.push(c);
				expectOperand = true;
			}
			else {
				return "Error: Invalid character: " + string(1, c);
			}
		}
	}

	if (!number.empty()) {
		postfix += number + " ";
	}

	while (!operators.empty()) {
		if (operators.top() == '(') {
			return "Error: Mismatched parentheses";
		}
		postfix += operators.top();
		postfix += " ";
		operators.pop();
	}

	if (!postfix.empty() && postfix.back() == ' ') {
		postfix.pop_back();
	}

	return postfix;
}

string preprocess(string expr) {
	string res = "";
	bool inParentheses = false;
	for (size_t i = 0; i < expr.length(); i++) {
		if (expr[i] == ' ') continue; // Bỏ qua khoảng trắng
		if (expr[i] == '(') {
			inParentheses = true;
			res += expr[i];
		}
		else if (expr[i] == ')') {
			inParentheses = false;
			res += expr[i];
		}
		else if (isOperator(expr[i]) || expr[i] == '(' || expr[i] == ')') {
			if (!res.empty() && res.back() != ' ' && res.back() != '(' && expr[i] != ')') {
				res += " ";
			}
			res += expr[i];
			if (expr[i] != '(' && expr[i] != ')') {
				res += " ";
			}
		}
		else {
			res += expr[i];
		}
	}
	// Xóa khoảng trắng thừa và hợp nhất số âm trong dấu ngoặc
	string finalRes = "";
	bool inNegative = false;
	for (size_t i = 0; i < res.length(); i++) {
		if (res[i] == '-' && i > 0 && res[i - 1] == '(') {
			inNegative = true;
			continue;
		}
		if (inNegative && isdigit(res[i])) {
			finalRes += '-';
			inNegative = false;
		}
		finalRes += res[i];
	}
	size_t start = finalRes.find_first_not_of(' ');
	size_t end = finalRes.find_last_not_of(' ');
	if (start == string::npos) return "";
	return finalRes.substr(start, end - start + 1);
}

BigInt evaluatePostfix(string postfix, ostream& out) {
	stack<BigInt> operands;
	stringstream ss(postfix);
	string token;

	while (ss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (operands.size() < 2) {
				out << "Error: Invalid expression" << endl;
				return createBigInt("0");
			}
			BigInt b = operands.top(); operands.pop();
			BigInt a = operands.top(); operands.pop();
			BigInt result;
			if (token == "+") result = addBigInt(a, b);
			else if (token == "-") result = subtractBigInt(a, b);
			else if (token == "*") result = multiplyBigInt(a, b);
			else if (token == "/") result = divide(a, b, out);

			operands.push(result);
		}
		else {
			BigInt num = createBigInt(token);
			operands.push(num);
		}
	}

	if (operands.size() != 1) {
		out << "Error: Invalid expression" << endl;
		return createBigInt("0");
	}

	return operands.top();
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " input_file output_file\n";
		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) {
		cerr << "Error: Cannot open input file: " << argv[1] << endl;
		return 1;
	}

	ofstream outputFile(argv[2]);
	if (!outputFile.is_open()) {
		cerr << "Error: Cannot open output file: " << argv[2] << endl;
		inputFile.close();
		return 1;
	}

	string expr;
	while (getline(inputFile, expr)) {
		if (expr.empty()) {
			outputFile << "Error: Empty expression!" << endl;
			continue;
		}

		expr = preprocess(expr);
		string postfix = infixToPostfix(expr);
		if (postfix.find("Error") != string::npos) {
			outputFile << postfix << endl;
			continue;
		}

		BigInt result = evaluatePostfix(postfix, outputFile);
		if (result.digits == "0" && postfix.find("Error") == string::npos) {
			continue; // Bỏ qua nếu có lỗi nhưng không phải lỗi cú pháp
		}
		printBigInt(result); // In kết quả ra console
		if (result.isNegative && result.digits != "0") outputFile << "-";
		outputFile << result.digits << endl;
	}
	inputFile.close();
	outputFile.close();
	cin.get(); 
	return 0;
}