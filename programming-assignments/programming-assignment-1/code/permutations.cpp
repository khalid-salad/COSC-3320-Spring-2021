#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

unsigned long long factorial(const unsigned long long);
vector<vector<int> > permutations(vector<int>);
vector<vector<int> > insertions(int, vector<int>, bool);

int main()
{
	vector<int> nums{ 1, 2, 3, 4 };
	for (auto perm : permutations(nums)) {
		for (auto i : perm) {
			cout << i << " ";
		}
		cout << endl;
	}
	return EXIT_SUCCESS;
}

unsigned long long factorial(const unsigned long long n)
{
	if (n == 0) {
		return 1;
	} else {
		return n * factorial(n - 1);
	}
}

vector<vector<int> > permutations(vector<int> nums)
{
	unsigned long long len = factorial(nums.size());
	vector<vector<int> > perms;
	if (len == 1) {
		perms.push_back(nums);
	} else {
		bool start_from_left = false;
		vector<int> old_nums(nums.begin(), nums.end() - 1);
		int val = nums[nums.size() - 1];
		for (auto perm : permutations(old_nums)) {
			vector<vector<int> > inserts = insertions(val, perm, start_from_left);
			perms.insert(end(perms), begin(inserts), end(inserts));
			start_from_left = not start_from_left;
		}
	}
	return perms;
}

vector<vector<int> > insertions(int val, vector<int> nums, bool start_from_left)
{
	int n = nums.size() + 1;
	vector<vector<int> > vectors;
	vectors.resize(n);
	for (int i = 0; i < n; i++) {
		vector<int> inserted_vec;
		inserted_vec.insert(end(inserted_vec), begin(nums), begin(nums) + i);
		inserted_vec.insert(end(inserted_vec), val);
		inserted_vec.insert(end(inserted_vec), begin(nums) + i, end(nums));
		if (start_from_left) {
			vectors[i] = inserted_vec;
		} else {
			vectors[n - i - 1] = inserted_vec;
		}
	}
	return vectors;
}