/*
	Given a string consisting of brackets, parenthesis, braces. Check if the brackets are balanced or not. 
	A bracket is balanced if there is a closing bracket for its opening bracket,
	Input: string
	Output: string

	Solution:
		The point to note is that for each right bracket if we see a left bracket before it which is not
		of the same type then it cannot be balanced.
		We scan from left to right. If it is a left bracket we push it to a stack.
		If it is a right bracket then check if the stack is empty or not.
		If it is empty means that there is no left bracket to match, return false.
		If it is not empty check what type of bracket is there, if different type return false
		
		Also if after scanning the left bracket stack is not empty, return false since there is no right bracket for it
		TC: O(n), n: no. of elements
		SC: O(n) 
*/

#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

// checks if the brackets are balanced or not
bool isBalanced(const string& brackets) {
	// for storing the left brackets
	stack<char> s;

	// start scanning from left
	for(int i = 0; i < brackets.size(); i++) {
		// if it is a left bracket push
		if(brackets[i] == '(' || brackets[i] == '[' || brackets[i] == '{') {
			s.emplace(brackets[i]);
		}	
		else {	//right bracket encountered
			// if there is no left bracket to match, then unbalanced
			if(s.empty())
				return false;
				
			// if the left bracket is of different type
			if(brackets[i] == ')' && s.top() != '(')
				return false;
			else if(brackets[i] == ']' && s.top() != '[')
				return false;
			else if(brackets[i] == '}' && s.top() != '{')
				return false;
			else
				s.pop();	// matching opening and closing brackets
		}
	}
	
	return s.empty() ? true : false;
}

int main() {
	
	string expr = "{}(){({)}{}";
	cout << isBalanced(expr);
	return 0;
}
 
