from cs50 import get_string

texto = get_string("Text: ").strip()
letra, palabras, oraciones = 0,0,0

for i in range(len(texto)):
    if (i == 0 and texto[i] != ' ') or (i != len(texto) - 1 and texto[i] == ' ' and texto[i + 1] != ' '):
        letra += 1
    if texto[i].isalpha():
        palabras += 1
    if texto[i] == '.' or texto[i] == '?' or texto[i] == '!':
        oraciones += 1

L = palabras / letra * 100
S = oraciones / letra * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")