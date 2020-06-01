//HW7 by Bo Li
//SU Net ID: bli158  SUID: 218717316

#include <iostream>
#include<vector>

using namespace std;
vector<vector<char>> vec;	// store H trees

int h = 5;
int w = 5;
int height = 5;
int width = 5;

int x_1 = 0;
int y_1 = 0;
int x_2 = 0;
int y_2 = 0;


void container(int n) {	// init height and width of 2D vector
	if (n <= 3) return;

	for (int i = 4; i <= n; i++) {
		if (i % 2 == 0)
			h = 2 * h + 1;
		else
			w = 2 * w + 1;
	}
}


void set_dimension(int n) {	// setup width and height based on current n
	if (n < 3) return;
	height = 5;
	width = 5;

	for (int i = 4; i <= n; i++) {
		if (i % 2 == 0)
			height = 2 * height + 1;
		else
			width = 2 * width + 1;
	}
}


void plot(int n) {
	if (n < 3)
		return;
	set_dimension(n);

	int x = (width - 1) / 2;
	int y = (height - 1) / 2;

	if (n == 3) {
		vec[y][x] = 'o';			// center

		// left side
		vec[y][x - 1] = '-';		// (1,2)
		vec[y][x - 2] = 'o';		// (0,2)
		vec[y - 1][x - 2] = '|';	// (0,1)
		vec[y - 2][x - 2] = 'o';	// (0,0)
		vec[y + 1][x - 2] = '|';	// (0,3)
		vec[y + 2][x - 2] = 'o';	// (0,4)

		// right side
		vec[y][x + 1] = '-';		// (3,2)
		vec[y][x + 2] = 'o';		// (4,2)
		vec[y - 1][x + 2] = '|';	// (4,1)
		vec[y - 2][x + 2] = 'o';	// (4,0)
		vec[y + 1][x + 2] = '|';	// (4,3)
		vec[y + 2][x + 2] = 'o';	// (4,4)
		return;
	}

	// Calculate x1, y1, x2, y2
	if (n % 2 == 0) {		// n is even
		x_1 = x;
		y_1 = y - ((height - 1) / 2 - 1) / 2 - 1;
		x_2 = x;
		y_2 = y + ((height - 1) / 2 - 1) / 2 + 1;
	}
	else {					// n is odd
		x_1 = x - ((width - 1) / 2 - 1) / 2 - 1;
		y_1 = y;
		x_2 = x + ((width - 1) / 2 - 1) / 2 + 1;
		y_2 = y;
	}

	// Connect with center and '-',  '|'
	vec[y][x] = 'o';

	if (n % 2 == 0) {		// n is even & using '|'
		for (int i = y_1 + 1; i < y; i++)
			vec[i][x] = '|';
	}
	else {					// n is odd & using '-'
		for (int i = x_1 + 1; i < x; i++)
			vec[y][i] = '-';
	}

	// recursion
	plot(n - 1);
	set_dimension(n);

	if (n % 2 == 0) {		// n is even
		for (int i = 0; i < y; i++) {
			int rotate = 2 * y - i;

			for (int j = 0; j < width; j++)
				vec[rotate][j] = vec[i][j];
		}
	}
	else {					// n is odd
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < x; j++) {
				int rotate = 2 * x - j;
				vec[i][rotate] = vec[i][j];
			}
		}
	}
}


void print(int n) {
	container(n);	// initialize size of 2D vector
	vec.resize(h);
	for (int i = 0; i < h; i++)
		vec[i].resize(w);

	for (int i = 0; i < h; i++) {       // initialize empty char into 2D vector
		for (int j = 0; j < w; j++)
			vec[i][j] = ' ';
	}

	plot(n);	// call plot

	cout << n << endl << endl;
	for (int i = 0; i < h; i++) {		// print out H tree by n
		for (int j = 0; j < w; j++)
			cout << vec[i][j] << " ";
		cout << "\n";
	}
	cout << endl;
}


int main()
{
	int num;
	cout << "Enter a number: ";
	cin >> num;
	print(num);

	getchar();
	getchar();
	return 0;
}
