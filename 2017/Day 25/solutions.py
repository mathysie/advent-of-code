def read_input():
    blueprint = dict()
    input()
    blueprint["N"] = int(input().split(" ")[-2])
    input()
    for i in ["A", "B", "C", "D", "E", "F"]:
        input()
        blueprint[i] = []
        instr0 = []
        input()
        instr0.append(int(input().split(" ")[-1][0:-1]))
        instr0.append(input().split(" ")[-1][0:-1])
        instr0.append(input().split(" ")[-1][0:-1])
        blueprint[i].append(instr0)
        instr1 = []
        input()
        instr1.append(int(input().split(" ")[-1][0:-1]))
        instr1.append(input().split(" ")[-1][0:-1])
        instr1.append(input().split(" ")[-1][0:-1])
        blueprint[i].append(instr1)
        input()
    return blueprint


def checksum():
    state = "A"
    steps = blueprint["N"]
    N = 11400
    tape = [0 for i in range(0, N)]
    i = int(N / 2)

    for M in range(0, steps):
        value = tape[i]
        tape[i] = blueprint[state][value][0]
        if blueprint[state][value][1] == "right":
            i += 1
        else:
            i -= 1
        state = blueprint[state][value][2]

    return sum(tape)


blueprint = read_input()
print(checksum())
