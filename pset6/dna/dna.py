from csv import reader, DictReader
from sys import argv

try:
    #read the dna sequence
    with open(argv[2]) as dnaFile:
        dnaReader = reader(dnaFile)
        for row in dnaReader:
            dnaSequence = row

    #store the dna sequence and create an empty dictionary
    dna = dnaSequence[0]
    sequences = {}

    #open the database.csv and store each row into a list
    with open(argv[1]) as databaseFile:
        people = reader(databaseFile)
        for row in people:
            dnaSequences = row
            dnaSequences.pop(0)
            break
    for item in dnaSequences:
        sequences[item] = 1

    #iterate through the dnaSequence counting repetitions
    for key in sequences:
        l = len(key)
        maxCount = 0
        temp = 0
        for i in range(len(dna)):
            #after having counted a sequence it skips at the end of it to avoid counting again
            while temp > 0:
                temp -= 1
                continue

            if dna[i: i + l] == key:
                while dna[i - l: i] == dna[i: i + l]:
                    temp += 1
                    i += l

                #it compares the value to the previous longest sequence and if it is longer it overrides it
                if temp > maxCount:
                    maxCount = temp

        #store the longest sequences in the dictionary using the correspondent key
        sequences[key] += maxCount

    #go through the database comparing the counted numbers to the registered numbers
    with open(argv[1], newline='') as databaseFile:
        people = DictReader(databaseFile)
        for person in people:
            match = 0
            #if it matches it gets the name and prints it
            for dna in sequences:
                if sequences[dna] == int(person[dna]):
                    match += 1
            if match == len(sequences):
                print(person['name'])
                exit()

        print("No match")
        exit()
except:
    print("Usage: dna.py database/database.csv sequences/sequence.txt")
    exit()