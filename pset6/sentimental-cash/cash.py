from cs50 import get_float

while True:
    dolar = get_float("cambio: ")
    if dolar >= 0:
        break

centavos = round(dolar * 100)
monedas = 0
denominaciones = [25, 10, 5, 1]

for denominar in denominaciones:
    monedas += centavos // denominar
    centavos %= denominar

print(monedas)