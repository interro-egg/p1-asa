import sys

for i in range(1, int(sys.argv[1])+1):
    print(i, end="")
    if i != int(sys.argv[1]):
        print(" ", end="")