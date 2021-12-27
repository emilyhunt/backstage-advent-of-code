#!/bin/python3

"""Advent of Code Day 19 2021"""

import re
from itertools import permutations

import numpy as np
from scipy.spatial.transform import Rotation as R


def day_19(scanners):
    """Solve day 19"""
    best_angles = None
    best_distance = None
    best_sensitivity = 1.0

    for sub_set_a in permutations(scanners[0], 12):
        for sub_set_b in permutations(scanners[1], 12):
            angles, distance, sensitivity = R.align_vectors(
                sub_set_a, sub_set_b, return_sensitivity=True)
            if distance < 500**2:
                best_sensitivity = sensitivity.mean()
                best_angles = angles
                best_distance = distance
                print(best_angles.as_euler('XYZ', degrees=True), distance, sep='\t')

    best_angles = best_angles.as_euler('XYZ', degrees=True)
    print(best_angles)
    print(best_distance)


if __name__ == "__main__":
    FILE_NAME = "test.txt"
    scanners = []
    i = -1

    with open("data/19/" + FILE_NAME, encoding='utf-8') as file:
        for line in file:
            split_line = re.findall(r'-*\d+', line)
            if len(split_line) == 3:
                scanners[i] = np.append(
                    scanners[i], [float(item) for item in split_line])
            elif len(split_line) == 1:
                scanners.append(np.array([]))
                i += 1

    for i, scanner in enumerate(scanners):
        scanners[i] = np.reshape(scanner, (len(scanner) // 3, 3))

    day_19(scanners)
