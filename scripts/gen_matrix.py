#!/bin/python3

from random import randint
import os

INPUT_DIR =  "./inputs"
MATRIX_MAX = 10
MATRIX_C = 10


def matrix(row, column):
    a = []
    for i in range(0, row):
        b = []
        for j in range(0, column):
            b.append(randint(0, 10))
        a.append(b)
    return a

def folders():
    a = []
    for i in range(1, MATRIX_MAX + 1):
        for j in range(1, MATRIX_MAX + 1):
            a.append((i, j))
    return a

def gen_folders():
    a = folders()

    for ij in a:
        try:
            folder = f"{INPUT_DIR}/{ij[0]}x{ij[1]}"
            os.mkdir()
        except:
            pass

def write_matrix(file, matrix):
    file.writelines(f"{len(matrix)} {len(matrix[0])}\n")

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            file.writelines(f"{matrix[i][j]} ")
        file.writelines("\n")

def gen_matrix():
    a = folders()

    for ij in a:
        for i in range(0, MATRIX_C):
            folder = f"{INPUT_DIR}/{ij[0]}x{ij[1]}"
            with open(f"{folder}/{i}.txt", "w") as file:
                m = matrix(ij[0], ij[1])
                write_matrix(file, m)

if __name__ == "__main__":
    gen_folders()
    gen_matrix()