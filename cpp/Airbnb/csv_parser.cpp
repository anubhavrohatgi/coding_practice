// http://buttercola.blogspot.com/2015/11/airbnb-csv-parser.html
/*
 * For this problem, there are several cases need to consider:
 * 1. For comma, transform to |
 * 2. If comma is inside a quote, don't treat the comma as separated. 
 *    Remove the comma and print the entire token. 
 *    e.g. "San Francisco, CA" => San Francisco, CA
 * 3. If there are double quotes, remove one. 
 *    e.g. "Alexandra ""Alex""" => Alexandra "Alex". 
 * 
 * Note that """Alexandra Alex""" becomes "Alexandra Alex" because we first remove 
 * the outer-most quote, and then remove one quote of the double quote.
 *
 * The outter '"' should be removed, and the inner ones are treated as escape char
 */


#include <iostream>
#include <vector>

using namespace std;

void printStrs(const vector<string> &strs) {
	for(int i=0; i<strs.size(); i++) {
		cout << strs[i];
		if(i != strs.size()-1)
			cout << "|";
	}
	cout << endl;
}

void parseCSV(const string &s) {
	vector<string> ret;
	bool inQuote = false;
	string tmp;

	for(int i=0; i<s.size(); i++) {
		char c = s[i];
		
		if(inQuote) {
			if(c == '\"') {
				// last token, just strip the outter '"'
				if(i == s.size()-1) {
					ret.push_back(tmp);
					tmp.clear();
				}
				// i is in the middle of current token, and there are consecutive '"', treat as escapes
				else if(s[i+1] == '\"') {
					tmp += '\"';
					i++;	// skip next '"'
				}
				// end of token
				else {
					ret.push_back(tmp);
					inQuote = false;
					tmp.clear();
					i++;	// next character must be ",", skip it
				}
			}
			else {
				tmp += c;
			}
		}
		else {
			if(c == '\"') {
				inQuote = true;
			}
			else if(c == ',') {
				ret.push_back(tmp);
				tmp.clear();
			}
			else {
				tmp += c;
			}
		}
	}

	if(!tmp.empty())
		ret.push_back(tmp);
	
	printStrs(ret);
}

int main() {
	string input1 = "John,Smith,john.smith@gmail.com,Los Angeles,1";
	parseCSV(input1);

	string input2 = "Jane,Roberts,janer@msn.com,\"San Francisco, CA\",0";
	parseCSV(input2);

	string input3 = "\"Alexandra \"\"Alex\"\"\",Menendez,alex.menendez@gmail.com,Miami,1";
	parseCSV(input3);

	string input4 = "\"\"\"Alexandra Alex\"\"\"";
	parseCSV(input4);
}
