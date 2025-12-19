def analyze_name():
    # 1. Setup: Define the name variable
    # You can hardcode your name here or ask for input.
    # I will use input() to make the program dynamic.
    name = input("Enter your name: ")

    # --- Operation 1: Display n characters from the left ---
    # We need to accept 'n' as an integer input from the user.
    # We use a try-except block to handle cases where input is not a number.
    try:
        n = int(input("Enter the number of characters to display (n): "))

        # String Slicing: We access the substring starting at index 0 up to (but not including) n.
        # Syntax: string[start:stop]
        print(f"First {n} characters: {name[:n]}")

    except ValueError:
        print("Please enter a valid integer for n.")

    # --- Operation 2: Count the number of vowels ---
    # We utilize a 'for' loop to iterate through the string (Chapter 8: Traversal).
    vowels = "aeiouAEIOU"
    vowel_count = 0

    for char in name:
        # Check if the current character is present in our vowels string
        if char in vowels:
            vowel_count = vowel_count + 1

    print(f"Number of vowels: {vowel_count}")

    # --- Operation 3: Reverse the name ---
    # We use slicing with a negative step value to reverse the string.
    # Syntax: string[start:stop:step]
    reversed_name = name[::-1]
    print(f"Reversed name: {reversed_name}")

# Execute the function
analyze_name()
