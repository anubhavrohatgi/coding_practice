#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <climits>
#include <unordered_set>

using namespace std;

// http://www.1point3acres.com/bbs/thread-166129-1-1.html
// http://buttercola.blogspot.com/2015/11/airbnb-rectangle.html
class Rectangle {
public:
	int xs, xe, ys, ye;

	Rectangle(int x1, int x2, int y1, int y2) : xs(x1), xe(x2), ys(y1), ye(y2) {} 
};

class Tuple {
public:
	int x;
	bool is_end;
	int rec_num;

	Tuple(int x_value, bool end, int num) : x(x_value), is_end(end), rec_num(num) {}
};

pair<int, int> find_overlapping_rectangles(vector<Rectangle> &recs) {
	vector<Tuple> tuples;
	for(int i=0; i<recs.size(); i++) {
		tuples.push_back(Tuple(recs[i].xs, false, i));
		tuples.push_back(Tuple(recs[i].xe, true, i));
	}
	sort(tuples.begin(), tuples.end(), [](const Tuple &t1, const Tuple &t2) { return t1.x < t2.x; } );

	// key : x value
	// value : i-th rectangle that we will be hitting  if we draw a vertical line at the x
	map<int, set<int>> x_axis;
	// keep track of current overlapping rectangles
	set<int> existing_recs;
	for(Tuple t : tuples) {
		if(!t.is_end) {
			existing_recs.insert(t.rec_num);
			x_axis[t.x].insert(existing_recs.begin(), existing_recs.end());
		}
		else {
			x_axis[t.x].insert(existing_recs.begin(), existing_recs.end());
			existing_recs.erase(t.rec_num);
		}
	}

	int ret_x = 0, ret_y = 0;
	int max_overlap = INT_MIN;
	// every x could have different y, do a 1D meeting room on these y
	for(auto a : x_axis) {
		// key : y value
		// value : +1 if ys, -1 if ye
		map<int, int> m;
		for(int rec_num : a.second) {
			m[ recs[rec_num].ys ]++;
			m[ recs[rec_num].ye ]--;
		}
		
		int curr_overlap = 0;
		for(auto it : m) {
			curr_overlap += it.second;
			if(curr_overlap > max_overlap) {
				max_overlap = curr_overlap;
				ret_x = a.first;
				ret_y = it.first;
			}
		}
	}
	cout << "max_overlap = " << max_overlap << endl;
	return {ret_x, ret_y};
}

int main() {
	Rectangle r1(4, 8, 1, 4);
	Rectangle r2(-3, 2, 5, 7);
	Rectangle r3(3, 6, 3, 10);
	Rectangle r4(5, 6, 7, 9);
	Rectangle r5(1, 2, 2, 3);
	Rectangle r6(5, 7, -1, 11);

	vector<Rectangle> recs = {r1, r2, r3, r4, r5, r6};

	pair<int, int> p = find_overlapping_rectangles(recs);

	cout << "x = " << p.first << " y = " << p.second << endl;
}
