def unsafe_division(num1, num2):
    result = num1 / num2
    return result

def safe_division(num1, num2):
    try:
        result = num1 / num2
        print(f"The result of {num1} divided by {num2} is: {result}")
    except ZeroDivisionError:
        print("Error: Cannot divide by zero!")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

def main():
    print("--- Division Program ---")

    try:
        n1 = float(input("Enter the first number: "))
        n2 = float(input("Enter the second number: "))
    except ValueError:
        print("Invalid input")
        return

    print("\nChoose mode:")
    print("1. Unsafe Division")
    print("2. Safe Division")
    mode = input("Select 1 or 2: ")

    if mode == '1':
        print("\nAttempting unsafe division...")
        print(f"Result: {unsafe_division(n1, n2)}")

    elif mode == '2':
        print("\nAttempting safe division...")
        safe_division(n1, n2)

    else:
        print("Invalid selection.")

if __name__ == "__main__":
    main()