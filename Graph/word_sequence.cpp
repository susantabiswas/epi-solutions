/*
	Given a dictionary of words, starting string 's' and target string 't', check if there is 
	a sequence of words which starts with 's' and ends with 't'. The condition is that each
	adjacent word should differ only in one position and all the words in the sequence should 
	be of same length. Return the smallest sequence length if there are many, else return -1.
	
	Input: Dictionary of string, s, t
	Output: Return the smallest sequence length if there are many, else return -1
*/
#include <iostream>
#include<unordered_set>
#include<queue>
using namespace std;

// structure for each node
struct Node{
	string word;
	int dist = 0;
};

// checks for a sequence of words
/*
	We use BFS for finding the shortest distance. The vertex is the word and the edge
	exits between two words if they differ by only one character. But instead of creating the
	graph, which will take O(d^2) for d no. of words, we search for the word which can be a 
	adjacent vertex for the current vertex. Now since we will visit only O(d) words, so 
	the time complexity becomes O(n * d * time for finding element in set)
*/
int findSequence(unordered_set<string>& dict, const string& s, const string& t){
	// starting sequence
	Node start{s, 1};
	
	// for BFS
	queue<Node> q;
	// for current word
	Node curr;
	
	// make the starting word visited and add to queue
	dict.erase(s);
	q.push(start);
	
	while(!q.empty()){
		curr = q.front();
		q.pop();
		if(curr.word == t)
			return curr.dist;
			
		// now for finding the next word, we just try all the combinations and
		// search if they are there in dict or not
		string str = curr.word;
		for(int i = 0; i < curr.word.size(); i++){
			for(int j = 0; j < 26; j++){
				str[i] = 'a' + j;
			
				// check if the current word is there in dict or not
				if(dict.find(str) != dict.end()){
					// make the current word visited and add to queue
					dict.erase(str);
					q.push(Node{str, curr.dist + 1});
				}
			}
			// revert the word
			str[i] = curr.word[i];
		}
	}
	
	return -1;	
}


int main(){
	unordered_set<string> dict = {"mug", "dug", "jug", "lug", "lag"};
	
	cout << findSequence(dict, "dug", "lag");
	return 0;
}
