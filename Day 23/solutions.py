from sympy import isprime


def read_input():
    commands = []
    while True:
        try:
            line = input().split(" ")
            if line[0] in ["set", "sub", "mul", "jnz"] and line[2].lstrip("-").isdigit():
                line[2] = int(line[2])
            commands.append(line)
        except EOFError:
            break

    return commands


def initial_registers():
    return {
        "a": 0,
        "b": 0,
        "c": 0,
        "d": 0,
        "e": 0,
        "f": 0,
        "g": 0,
        "h": 0,
    }


def times_mul():
    amount_mul = 0
    registers = initial_registers()
    i = 0

    while True:
        if i < 0 or i >= len(commands):
            break

        if commands[i][0] == "set":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] = commands[i][2]
            else:
                registers[commands[i][1]] = registers[commands[i][2]]
        elif commands[i][0] == "sub":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] -= commands[i][2]
            else:
                registers[commands[i][1]] -= registers[commands[i][2]]
        elif commands[i][0] == "mul":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] *= commands[i][2]
            else:
                registers[commands[i][1]] *= registers[commands[i][2]]
            amount_mul += 1
        elif commands[i][0] == "jnz" and \
                ((commands[i][1].isnumeric() and int(commands[i][1]) != 0)
                 or registers[commands[i][1]] != 0):
            if isinstance(commands[i][2], int):
                i += commands[i][2]
            else:
                i += registers[commands[i][2]]
            continue

        i += 1

    return amount_mul


def value_h():
    b = 109300
    c = 126300
    h = 0

    while b != c:
        if not isprime(b):
            h += 1
        b += 17
    if not isprime(b):
        h += 1

    return h

commands = read_input()
print(times_mul())
print(value_h())
