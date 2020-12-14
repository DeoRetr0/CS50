from cs50 import get_string
text = get_string("Text: ")
letters = 0
words = 1
sentences = 0
# checks the words/letters/sentences in the text and filters everything
for i in range(len(text)):
    if (text[i] >= 'A' and text[i] <= 'z'):
        letters += 1
    if (text[i] == ' ' or text[i] == '\0'):
        words += 1
    if (text[i] == '.' or text[i] == '?' or text[i] == '!'):
        sentences += 1
# calculates the grade as in pset2 in C
L = 100 * letters / words
S = 100 * sentences / words
grade = round(0.0588 * L - 0.296 * S - 15.8)
# shows results
if (grade < 1):
    print("Before Grade 1")
elif (grade > 16):
    print("Grade 16+")
else:
    print(f"Grade {grade}")
