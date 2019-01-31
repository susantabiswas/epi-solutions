/*
	Given a text file which contains scores and student id in new line. So each record is there on a new line.
	Find the top scoring student. Consider using only the top 3 scores for computing the avg., students with
	atleast 3 test scores are only considered.

	Input: file
	Output: string 

	Solution:
		Use a hash table for storing the student id and their scores.
		We use a priority queue of 3 elements as value for keys, whose creation is O(3)~O(1).
		Now for after going through all the scores, we traverse through the table once and
		compute the avg, while keeping track of max.
		Since heapifying takes O(n), so in worst case it will take O(n), n: no. of test scores

		TC: O(n)
		SC: O(m), m: no. of distinct students, worst case: O(n), no. of scores=no. of students
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// finds the top scoring student
string findStudentWithHighestScore(ifstream* in) {
	unordered_map<string, priority_queue<int, vector, greater<>>> student_records;
	int score;
	string name;

	// make the student score record hash table
	while(in >> name >> score) {
		student_records[name].emplace(score);
		// if there are more than 3 scores, remove 1
		if(student_records[name].size() > 3)
			student_records[name].pop();
	}

	// find the top scoring student
	string top_student;
	int top_score = 0;
	int curr_score = 0;

	for(auto& record: student_records) {
		// only consider student with 3 scores
		if(record->second.size() == 3) {
			// take the sum of top 3 test scores from heap
			while(!record->second.empty()) {
				curr_score += record->second.top();
				record->second.pop();
			}

			// check if it is the highest score
			if(curr_score > top_score) {
				top_score = curr_score;
				top_student = record->first;
			}
		}
	}

	return top_student;
}



