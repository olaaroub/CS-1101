def countdown(n):
    """
    Counts down from a positive number to zero.
    Source: Section 5.8 of textbook.
    """
    if n <= 0:
        print('Blastoff!')
    else:
        print(n)
        countdown(n-1)

def countup(n):
    """
    Counts up from a negative number to zero.
    """
    if n >= 0:
        print('Blastoff!')
    else:
        print(n)
        countup(n+1)

def main():

    user_input = input("Enter a number: ")

    try:
        n = int(user_input)
    except ValueError:
        print("Please enter a valid integer.")
        return

    if n > 0:
        print(f"Counting down from {n}:")
        countdown(n)
    elif n < 0:
        print(f"Counting up from {n}:")
        countup(n)
    else:
        print("Input is zero:")
        countdown(n)

if __name__ == "__main__":
    main()

