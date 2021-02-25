#!/usr/bin/env python3


def permutations(arr):
    """Recursively return list of permutations of arr so that successive permutations differ by
    a single swap. Note that elements of arr must be distinct.
    """
    n = len(arr)
    if n == 1:
        return [arr]
    else:
        perms = []
        start_from_left = False
        sub_arr, a = arr[:-1], arr[-1]
        for perm in permutations(sub_arr):
            perms.extend(insertions(a, sub_arr, start_from_left))
            start_from_left = not start_from_left
        return perms


def insertions(val, arr, start_from_left):
    """Return list of arrays arr with element val inserted at each position from
    0 to len(arr). If start_from_left is True, returns them inserted from left,
    else returns them inserted from right.
    """
    n = len(arr) + 1
    iter = range(n)
    if not start_from_left:
        iter = reversed(iter)
    return [arr[:i] + [val] + arr[i:] for i in iter]


def main():
    """Really lazy testing function."""
    permutations([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])


if __name__ == "__main__":
    main()
