#include <vector>
#include <algorithm>
#include <stdlib.h> // for testing
#include <time.h> // for random seed
#include <algorithm> // also for testing
#include <iostream>

class Point {
public:
	int x, y;
	int distance_from_origin;

	Point(int x1, int y1)
	{
		x = x1;
		y = y1;
		distance_from_origin = x * x + y * y;
	}
	bool operator<(const Point& p)
	{
		return distance_from_origin < p.distance_from_origin;
	}

	bool operator!=(const Point& p)
	{
		return x != p.x or y != p.y;
	}
};

using namespace std;

Point median(vector<Point> points)
{
	/* median of vector of points by distance to origin
	 * assume O(1) length
     */
	int n = points.size();
	std::sort(points.begin(), points.end());
	return points[n / 2];
}

vector<Point> medians(vector<Point>& points)
{
	/*Returns the set of medians of disjoint subarrays of length 5*/
	vector<Point> ret;
	for (auto i = 0; i < points.size(); i += 5) {
		auto start = points.begin() + i;
		auto end = (start + 5 < points.end()) ? start + 5 : points.end();
		vector<Point> sub_vec(start, end);
		auto median_of_5 = median(sub_vec);
		ret.push_back(median_of_5);
	}
	return ret;
}

Point median_of_medians(vector<Point> points, int k)
{
	if (points.size() == 1) {
		return points[0];
	} else {
		auto meds = medians(points);
		auto pivot = median_of_medians(meds, meds.size() / 2);
		vector<Point> L, P, R;
		for (auto p : points) {
			if (p < pivot) {
				L.push_back(p);
			} else if (pivot < p) {
				R.push_back(p);
			} else {
				P.push_back(p);
			}
		}
		if (L.size() == k - 1) { // pivot is the kth smallest
			return pivot;
		} else if (L.size() > k - 1) { // kth smallest is in left
			return median_of_medians(L, k);
		} else { // kth smallest is in right
			return median_of_medians(R, k - L.size() - 1);
		}
	}
}

int main()
{
	/* Generate random points and a random k and test correctness
     * by comparing output against the built-in sorting algorithm
     */
	srand(time(NULL));
	for (int _ = 0; _ < 100; _++) {
		int n = rand() % 100 + 100;
		int k = rand() % n + 1;
		vector<Point> points;
		for (int __ = 0; __ < n; __++) {
			points.push_back(Point(rand(), rand()));
		}
		Point select_answer = median_of_medians(points, k);
		sort(points.begin(), points.end());
		Point sort_answer = points[k - 1];
		if (sort_answer != select_answer) { // found a possible error
			for (int i = 0; i < n; i++) {
				cout << "(" << points[i].x << ", " << points[i].y << ") ";
			}
			cout << endl;
			cout << "(" << sort_answer.x << ", " << sort_answer.y << ") ";
			cout << "(" << select_answer.x << ", " << select_answer.y << ") ";
			return -1;
		}
	}
	cout << "Success" << endl;
	return 0;
}
