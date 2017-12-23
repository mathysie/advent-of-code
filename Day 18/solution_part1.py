def read_input():
    commands = []
    while True:
        try:
            line = input().split(" ")
            if line[0] in ["set", "add", "mul", "mod", "jgz"] and line[2].lstrip("-").isdigit():
                line[2] = int(line[2])
            commands.append(line)
        except EOFError:
            break

    return commands


def do_program():
    sound = 0
    registers = dict()
    i = 0

    while True:
        if not (commands[i][1].isnumeric() or commands[i][1] in registers):
            registers[commands[i][1]] = 0

        if commands[i][0] == "snd":
            sound = registers[commands[i][1]]
        elif commands[i][0] == "set":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] = commands[i][2]
            else:
                registers[commands[i][1]] = registers[commands[i][2]]
        elif commands[i][0] == "add":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] += commands[i][2]
            else:
                registers[commands[i][1]] += registers[commands[i][2]]
        elif commands[i][0] == "mul":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] *= commands[i][2]
            else:
                registers[commands[i][1]] *= registers[commands[i][2]]
        elif commands[i][0] == "mod":
            if isinstance(commands[i][2], int):
                registers[commands[i][1]] %= commands[i][2]
            else:
                registers[commands[i][1]] %= registers[commands[i][2]]
        elif commands[i][0] == "rcv":
            if registers[commands[i][1]] > 0:
                return sound

        if commands[i][0] == "jgz" \
                and ((commands[i][1].isnumeric() and int(commands[i][1]) > 0) \
                or registers[commands[i][1]] > 0):
            if isinstance(commands[i][2], int):
                i += commands[i][2]
            else:
                i += registers[commands[i][2]]
        else:
            i += 1

        if i < 0 or i >= len(commands):
            break

    print("Program terminated unexpectedly.")


commands = read_input()
print(do_program())
