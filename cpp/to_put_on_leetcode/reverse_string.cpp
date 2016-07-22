/**
 * Question:
 * Given a string, reverse the words sequence but not punctuations 
 *
 * For example:
 * input  = "Hello, world! How are you?"
 * output = "you, are! How world Hello?" 
 */ 

#include <iostream>

using namespace std;

bool isPunctuation(char c) {
	return (c==' ' || c=='?' || c=='!' || c=='.' || c==',');
}

string reverseStr(string s) {
	int L = 0, U = s.size()-1;
	string front, tail;

	while(L<=U) {
		// append the punctuation
		while(L<=U && isPunctuation(s[L]))
			front += s[L++];
		while(L<=U && isPunctuation(s[U]))
			tail = s[U--] + tail;

		// append the words
		string endWord;
		while(L<=U && !isPunctuation(s[L]))
			endWord += s[L++];
		tail = endWord + tail;
		string startWord;
		while(L<=U && !isPunctuation(s[U]))
			startWord = s[U--] + startWord;
		front += startWord;

	}
	return front + tail;
}

int main()
{
	cout << reverseStr("Hello, world! How are you?") << endl;
}
