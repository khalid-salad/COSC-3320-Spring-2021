#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

unsigned long long factorial(unsigned long long);
int** permutations(int*, int);
int** insertions(int, int*, int, bool);

int main(int argc, char* argv[argc + 1])
{
	if (argc == 1) {
		fputs("Pass a positive integer as a command line argument.", stderr);
		return EXIT_FAILURE;
	}
	int len = strtol(argv[1], NULL, 10);
	int* nums = malloc(len * sizeof(*nums));
	if (!nums) {
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < len; i++) {
		nums[i] = i + 1;
	}
	int** test = permutations(nums, len);
	for (unsigned long long i = 0; i < factorial(len); i++) {
		// for (int j = 0; j < len; j++) {
		// printf("%d ", test[i][j]);
		// }
		// printf("\n");
		free(test[i]);
	}
	free(nums);
	free(test);
	return EXIT_SUCCESS;
}

unsigned long long factorial(unsigned long long n)
{
	if (n == 0) {
		return 1;
	} else {
		return n * factorial(n - 1);
	}
}

int** permutations(int* nums, int num_size)
{
	/* Return pointer to array containing all permutations of nums
     * such that each permutation is a single swap of its predecessor.
     * Note that the elements of nums must be distinct.
     */
	unsigned long long len = factorial(num_size);
	int** perms = malloc(len * sizeof(*perms));
	if (!perms) {
		exit(EXIT_FAILURE);
	}
	for (unsigned long long i = 0; i < len; i++) {
		perms[i] = malloc(num_size * sizeof(*perms[i]));
		if (!perms[i]) {
			exit(EXIT_FAILURE);
		}
	}
	if (num_size == 1) { // base case, permutations([1]) => [[1]]
		memcpy(perms[0], nums, num_size);
	} else {
		bool start_from_left = true;
		int* old_nums = malloc((num_size - 1) * sizeof(*old_nums));
		if (!old_nums) {
			exit(EXIT_FAILURE);
		}
		int a = nums[num_size - 1];
		memcpy(old_nums, nums, (num_size - 1) * sizeof(*old_nums));
		int** old_perms = permutations(old_nums, num_size - 1);
		for (unsigned long long i = 0; i < len / num_size; i++) {
			int* perm = old_perms[i];
			int** inserts = insertions(a, perm, num_size - 1, start_from_left);
			for (int j = 0; j < num_size; j++) {
				memcpy(perms[i * num_size + j], inserts[j], num_size * sizeof(**perms));
				free(inserts[j]);
			}
			start_from_left = !start_from_left;
			free(inserts);
			free(perm);
		}
		free(old_perms);
		free(old_nums);
	}
	return perms;
}

int** insertions(int val, int* nums, int num_size, bool start_from_left)
{
	/* Return pointer to array of all possible insertions of val into nums.
     * If start_from_left is true, insert from left, else insert from right.
     */
	int n = num_size + 1;
	int** arrays = malloc(n * sizeof(*arrays));
	if (!arrays) {
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < n; i++) {
		int* inserted_arr = malloc(n * sizeof(*inserted_arr));
		if (!inserted_arr) {
			exit(EXIT_FAILURE);
		}
		memcpy(inserted_arr, nums, i * sizeof(*inserted_arr));
		inserted_arr[i] = val;
		memcpy(&inserted_arr[i + 1], &nums[i], (num_size - i) * sizeof(*inserted_arr));
		if (start_from_left) {
			arrays[i] = inserted_arr;
		} else {
			arrays[n - i - 1] = inserted_arr;
		}
	}
	return arrays;
}