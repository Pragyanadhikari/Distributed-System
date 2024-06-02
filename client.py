
#Client

import Pyro4

uri = input("Enter the URI of the server: ")

calc = Pyro4.Proxy(uri)

def perform_addition():
    x = float(input("Enter the first number: "))
    y = float(input("Enter the second number: "))
    result = calc.add(x,y)
    print("Result of the addition: ", result)


def perform_subtraction():
    x = float(input("Enter the first number: "))
    y = float(input("Enter the second number: "))
    result = calc.subtract(x,y)

    print("Result of subtraction: ",result)

while True:
    print("\nChoose an operation: ")
    print("1. Addition")
    print("2. Subtraction")
    print("3. Exit")

    choice = input("Enter your choice (1/2/3): ")

    if choice == "1":
        perform_addition()
    elif choice == "2":
        perform_subtraction()
    elif choice == "3":
        print("Exixting client.")
        break
    else:
        print("Invalid choice. Please enter 1,2 or 3.")
        
