def read_input():
    lines = []

    while True:
        try:
            line = raw_input().split(" ")
            lines.append(line)
        except EOFError:
            break

    return lines


def build_register(lines):
    register = dict()

    for line in lines:
        register[line[0]] = 0

    return register


def update_register(register, line):
    if (line[1] == "inc"):
        register[line[0]] += int(line[2])
    elif (line[1] == "dec"):
        register[line[0]] -= int(line[2])


def fill_register(register, lines):
    for line in lines:
        if (line[5] == "=="):
            if (register[line[4]] == int(line[6])):
                update_register(register, line)
        elif (line[5] == "!="):
            if (register[line[4]] != int(line[6])):
                update_register(register, line)
        elif (line[5] == "<="):
            if (register[line[4]] <= int(line[6])):
                update_register(register, line)
        elif (line[5] == "<"):
            if (register[line[4]] < int(line[6])):
                update_register(register, line)
        elif (line[5] == ">="):
            if (register[line[4]] >= int(line[6])):
                update_register(register, line)
        elif (line[5] == ">"):
            if (register[line[4]] > int(line[6])):
                update_register(register, line)


def largest_value(lines):
    register = build_register(lines)
    fill_register(register, lines)

    return max(register.values())


lines = read_input()
print largest_value(lines)
