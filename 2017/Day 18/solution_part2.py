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


def duet():
    registers = [dict(), dict()]
    registers[0]["p"] = 0
    registers[1]["p"] = 1
    queue = [[], []]
    wait = [False, False]
    i = [0, 0]
    counter = 0
    player = 0

    while True:
        if wait[player]:
            if wait[(player + 1) % 2]:
                break
            elif len(queue[player]) == 0:
                player = (player + 1) % 2

        if not (commands[i[player]][1].isnumeric() \
                or commands[i[player]][1] in registers[player]):
            registers[player][commands[i[player]][1]] = 0

        if commands[i[player]][0] == "set":
            if isinstance(commands[i[player]][2], int):
                registers[player][
                    commands[i[player]][1]] = commands[i[player]][2]
            else:
                registers[player][commands[i[player]][1]] = registers[
                    player][commands[i[player]][2]]

        elif commands[i[player]][0] == "add":
            if isinstance(commands[i[player]][2], int):
                registers[player][
                    commands[i[player]][1]] += commands[i[player]][2]
            else:
                registers[player][commands[i[player]][1]] += registers[
                    player][commands[i[player]][2]]

        elif commands[i[player]][0] == "mul":
            if isinstance(commands[i[player]][2], int):
                registers[player][
                    commands[i[player]][1]] *= commands[i[player]][2]
            else:
                registers[player][commands[i[player]][1]] *= registers[
                    player][commands[i[player]][2]]

        elif commands[i[player]][0] == "mod":
            if isinstance(commands[i[player]][2], int):
                registers[player][
                    commands[i[player]][1]] %= commands[i[player]][2]
            else:
                registers[player][commands[i[player]][1]] %= registers[
                    player][commands[i[player]][2]]

        elif commands[i[player]][0] == "snd":
            queue[(player + 1) % 2].append(
                registers[player][commands[i[player]][1]])
            if player == 1:
                counter += 1

        elif commands[i[player]][0] == "rcv":
            if len(queue[player]) == 0:
                wait[player] = True
                continue
            else:
                registers[player][
                    commands[i[player]][1]] = queue[player].pop(0)
                wait[player] = False

        elif commands[i[player]][0] == "jgz" \
                and ((commands[i[player]][1].isnumeric() and int(commands[i[player]][1]) > 0) \
                or registers[player][commands[i[player]][1]] > 0):
            if isinstance(commands[i[player]][2], int):
                i[player] += commands[i[player]][2]
            else:
                i[player] += registers[player][commands[i[player]][2]]
            continue

        i[player] += 1

        if i[player] < 0 or i[player] >= len(commands):
            wait[player] = True

        player = (player + 1) % 2

    return counter


commands = read_input()
print(duet())
