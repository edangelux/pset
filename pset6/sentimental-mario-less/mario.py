from cs50 import get_int

while  True:
    a = get_int("height: ")
    if a >= 1 and a <= 8:
        break

for e in range(a):
    print((a - 1 - e) * " ", end= "")
    print((e + 1) * "#")