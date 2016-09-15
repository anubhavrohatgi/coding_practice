#include <iostream>
#include <vector>

using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void floor_fill(vector<vector<int>> &matrix, int x, int y) {
	int m = matrix.size(), n = matrix[0].size(); 

	if(x<0 || y<0 || x>=m || y>=n || matrix[x][y] == 1) {
		return;
	}

	matrix[x][y] = 1;
	for(int i=0; i<4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		floor_fill(matrix, nx, ny);
	}
}

void print_matrix(const vector<vector<int>> &matrix) {
	int m = matrix.size(), n = matrix[0].size();

	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	vector<vector<int>> matrix = {
		{1, 1, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 1},
		{1, 0, 0, 1, 1, 0}
	};

	int x = 2, y = 1;

	print_matrix(matrix);
	floor_fill(matrix, x, y);
	print_matrix(matrix);
}
