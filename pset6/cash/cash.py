from cs50 import get_float

while True:
    # gets change to be calculated and checks if its higher than 0
    change = get_float("Change owed:")
    if change > 0:
        # rounds it ups so it can be treated
        cents = round(change * 100)

        # uses module division as per pset1 in C
        quarters = cents // 25
        dimes = (cents % 25) // 10
        nickels = ((cents % 25) % 10) // 5
        pennies = ((cents % 25) % 10) % 5
        coins = quarters + dimes + nickels + pennies

        print(coins)
        break