import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + str(v))
    return 100;

def SquareValue(v):
    return v * v

def MultTable(v):
    for i in range(12):
        print(str(i + 1) + " * " + str(v) + " = " + (str((i + 1) * v)))

    print("\n")
    return 0

def DoubleInt(v):
    return (v * 2)

"""
import re
import string

def printsomething():
	print("Hello from Python!")
"""