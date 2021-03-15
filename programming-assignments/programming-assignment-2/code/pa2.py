#!/usr/bin/env python3

from random import random, randint  # for testing


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.tup = (self.x, self.y)
        self.square_distance_from_origin = self.x ** 2 + self.y ** 2

    def __lt__(self, q):
        return self.square_distance_from_origin < q.square_distance_from_origin


def medians(A, size=5):
    """Returns the set of medians of disjoint subarrays of length size """
    partition = [sorted(A[i : i + size]) for i in range(0, len(A), size)]
    return [subarr[len(subarr) // 2] for subarr in partition]


def median_of_medians(points, k, size=5):
    if len(points) == 1:
        return points[0]
    meds = medians(points, size)
    pivot = median_of_medians(medians(points), len(meds) // 2)
    left, right = [], []
    for p in points:
        if p < pivot:
            left.append(p)
        elif pivot < p:
            right.append(p)
    if len(left) == k - 1:  # pivot is the kth smallest
        return pivot
    elif len(left) > k - 1:  # kth smallest is in left
        return median_of_medians(left, k)
    else:  # kth smallest is in right
        return median_of_medians(right, k - len(left) - 1)


def main():
    """Generate random points and a random k and test correctness
    by comparing output against the built-in sorting algorithm
    """
    for _ in range(100):
        n = randint(100, 200)
        k = randint(1, n)
        points = [Point(random(), random()) for _ in range(n)]
        sort_answer = sorted(points)[k - 1]
        select_answer = median_of_medians(points, k)
        if sort_answer != select_answer:  # found a possible error
            print(points)
            print(sort_answer)
            print(select_answer)
            return
    print("Success!")


if __name__ == "__main__":
    main()
