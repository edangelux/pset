from cs50 import get_int

while True:
    a = get_int("heigth: ")
    if a >= 1 and a <= 8:
        break
for e in range(a):
    print(" " * (a - 1 - e), end="")
    print("#" * (e + 1), end="")
    print(" " * 2, end="")
    print("#" * (e + 1), end="")
    print(end="\n")