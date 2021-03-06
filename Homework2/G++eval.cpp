#include <string>
#include <stack>

int evaluate(std::string infix, std::string& postfix, bool& result);
bool convertToPostfix(std::string infix, std::string& postfix);
bool precedence(char first, char second);
char smallEval(char op1, char op2, char operate);
bool isValid(std::string infix);

#include <cassert>
#include <iostream>

//EVAL TESTS
int main()
{
	std::string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	//new tests
	assert(evaluate("T&F", pf, answer) == 0 && pf == "TF&" && !answer);
	assert(evaluate("T(^F)", pf, answer) == 1);
	assert(evaluate("((T^F)", pf, answer) == 1);
	assert(evaluate("(T&T)^F", pf, answer) == 0 && pf == "TT&F^" && answer);

	std::cout << "Passed all tests" << std::endl;
}
int evaluate(std::string infix, std::string& postfix, bool& result)
{
	postfix = "";
	if (!convertToPostfix(infix,postfix))
		return 1;
	std::stack<char>operands;
	for (size_t i = 0; i < postfix.size(); i++) {
		char c = postfix[i];
		if (c == 'T' || c == 'F')
			operands.push(c);
		else if (!operands.empty()) {
			char operand2 = operands.top();
			operands.pop();
			if (!operands.empty()) {
				char operand1 = operands.top();
				operands.pop();
				operands.push(smallEval(operand1, operand2, c));
			}
			else
				operands.push(operand2);
		}
	}
	if (!operands.empty() && operands.top() == 'T')
		result = true;
	else
		result = false;
	return 0;
}
bool convertToPostfix(std::string infix, std::string& postfix) {
	if (!isValid(infix))
		return false;
	std::stack <char> ops;
	for (size_t i = 0; i < infix.size(); i++) {
		char c = infix[i];
		switch (c) {
		case 'T':
		case 'F':
			postfix += c;
			break;
		case '(':
			ops.push(c);
			break;
		case ')':
			while (ops.top() != '(') {
				postfix += ops.top();
				ops.pop();
			}
			ops.pop();
			break;
		case '^':
		case '&':
		case '!':
			while (!ops.empty() && ops.top() != '(' && !precedence(c, ops.top())) {
				postfix += ops.top();
				ops.pop();
			}
			ops.push(c);
			break;
		default:
			break;
		}
		}
	while (!ops.empty()) {
		postfix += ops.top();
		ops.pop();
	}
	return true;
}                        
bool precedence(char first, char second) {
	switch (first) {
	case '!':
		return true;
		break;
	case '&':
		if (second == '^')
			return true;
		else
			return false;
		break;
	case '^':
	default:
		return false;
		break;
	}
}
char smallEval(char op1, char op2, char operate) {
	bool flag = false;
	if (op1 == 'T')
		flag = true;
	if (operate == '&') {
		if (op1 == 'F' || op2 == 'F')
			flag = false;
	}
	else if (operate == '^') {
		if (op1 == op2)
			flag = false;
	}
	if (flag)
		return 'T';
	return 'F';
}
bool isValid(std::string infix) {
	std::string pre = "";
	for (size_t i = 0; i < infix.length(); i++) {
		if (infix[i] != ' ')
			pre += infix[i];
	}
	int parent = 0;
	bool operands = false;
	if (pre.length() == 0)
		return false;
	for (size_t i = 0; i < pre.length(); i++) {
		char c = pre[i];
		char p = ' ';
		char n = ' ';
		if (i!=0)
			p = pre[i - 1];
		if (i!=pre.length()-1)
			n = pre[i + 1];
		if (!(c == 'T' || c == '(' || c == ')' || c == 'F' || c == ' ' || c == '&' || c == '^' || c == '!'))
			return false;
		if (c == '(') {
			parent++;
			if (parent <= 0 || i == pre.length() - 1)
				return false;
			if (i != 0 && (p == 'T' || p == 'F'))
				return false;
			if (i != pre.length() - 1 && n == ')')
				return false;
		}
		if (c == ')') {
			parent--;
			if (i == 0 || parent < 0) 
				return false;
			if (i != pre.length() - 1 && n == '(')
				return false;
		}
		if (c == '&' || c == '^') {
			if (i == 0 || i == pre.length()-1)
				return false;
			if (p != 'F' && p != 'T' && p!= ')')
				return false;
			if (n != 'F' && n != 'T' && n != '!' && n != '(')
				return false;
		}
		if (c == '!') {
			if (n != '(' && n != 'F' && n != 'T' && n != '!')
				return false;
		}
		if (c == 'T' || c == 'F') {
			operands = true;
			if (pre.length() == 1)
				return true;
			if (i == 0 && (n != '^' && n != '&'))
				return false;
			if (i == pre.length() - 1 &&(p == '(' || p == ')'))
				return false;
			if (i != 0 && p != '!' && p != '&' && p != '^' && p != '(')
				return false;
			if (i != pre.length() - 1 && n != '&' && n != '^' && n != ')')
				return false;
		}
	}
	if (parent != 0 || !operands)
		return false;
	return true;
}