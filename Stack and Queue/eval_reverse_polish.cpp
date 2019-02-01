/*
	Given a reverse polish expression, evaluate it. In simple terms operators are placed after the operands for each operation
	in reverse polish.
	Input: string
	Output: int/string

	Solution:
		This can be done using a stack. We start scanning from left to right. If we encounter a number/alphabet we push it to
		the stack. If we get an operator (/, *, +, -) we pop the top two operands from stack, apply the operator and again
		push the result.

		TC: O(n), n: no. of elements
		 
*/

#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <string>
using namespace std;

// returns the reverse polish result
int evaulateReversePolish(const string& expr) {
	// the input has ',' for separating chars, so we parse it 
	// taking ',' as delimiter
	stringstream ss(expr);
	string token;
	const char delimiter = ',';

	// for storing the operand tokens
	stack<int> operands;
	while(getline(ss, token, delimiter)) {
		// if the token is operator then apply on top two 
		// operands else push to operands stack
		if(token == "*" || token == "/" || token == "-" || token == "+") {
			// get the top two operands
			int a = operands.top();
			operands.pop();
			int b = operands.top();
			operands.pop();

			switch(token.front()) {
				case '*':
					operands.emplace(a*b);
					break;
				case '/':
					operands.emplace(a/b);
					break;
				case '+':
					operands.emplace(a+b);
					break;
				case '-':
					operands.emplace(a-b);
					break;
			}
		}
		else {
			operands.emplace(stoi(token));
		}
	}
	return operands.top();
}

int main() {
	
	string expr = "3,4,+";
	cout << evaulateReversePolish(expr);
	return 0;
}
 
