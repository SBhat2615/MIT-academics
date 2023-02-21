
def operation(x, y, op):
    if op == '+':
        return f"Sum of numbers: {x + y}"
    elif op == '-':
        return f"Difference of numbers: {x - y}"
    elif op == '*':
        return f"Product of numbers: {x * y}"
    elif op == '/':
        return f"Division of numbers: {x / y}"
    else:
        return None


if __name__=="__main__":
    x, y = map(int, input("Enter two numbers: " ).split())
    op = input("Enter operation: ")
    solution = operation(x, y, op)
    print(solution)
