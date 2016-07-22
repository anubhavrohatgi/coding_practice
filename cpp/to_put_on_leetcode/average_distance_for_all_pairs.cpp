/** 
 * Question :   Given a string s, a valid pair is defined as ('a', 'b') where s[i]='a' and s[j]='b' and i<j
 *              The distance of a pair is defined as j-i-1.
 *             	Calculate the average distance of all pairs
 * Sample input :
 *              s = "aacabcaba" 
 *              => pairs : (s[0], s[4]) dis = 3, (s[1], s[4]) dis = 2, (s[3], s[4]) dis = 0, 
 *                         (s[0], s[7]) dis = 6, (s[1], s[7]) dis = 5, (s[3], s[7]) dis = 3, (s[6], s[7]) dis = 0
 *              => (3+2+0+6+5+3+0) 19 / 7 =
 *
 * O(n) approach :
 *              s = "aacabcaba"
 *              a  a  c  a  b  c  a  b  a
 *              a1 1  1  1  b1
 *                 a2 1  1  b1
 *                       a3 b1
 *              Total sum of distance till b1 is 3 + 2 + 0
 *              We add the sum "horizontally"
 */

#include <iostream>
#include <vector>

using namespace std;

double avgPairsDistance(const string &s) {
	int total_dis_sum = 0, curr_dis_sum = 0, total_pair = 0, cnt_a = 0;

	for(int i=0; i<s.size(); i++) {
		if(s[i] == 'b') {
			total_dis_sum += curr_dis_sum;
			total_pair += cnt_a;
		}
		
		curr_dis_sum += cnt_a;

		if(s[i] == 'a')
			cnt_a++;
	}
	return (total_pair == 0) ? 0 : double(total_dis_sum)/total_pair;
}

int main() {
	string s1 = "aacabcaba";
	cout << avgPairsDistance(s1) << endl;
	string s2 = "bbbba";
	cout << avgPairsDistance(s2) << endl;
	string s3 = "aaaab";
	cout << avgPairsDistance(s3) << endl;
}
