def read_input():
    jumps = []
    while True:
        try:
            jumps.append(int(raw_input()))
        except EOFError:
            break

    return jumps


def steps_counter(jumps):
    steps = 0
    i = 0
    while (i >= 0 and i < len(jumps)):
        temp = i
        i += jumps[i]
        jumps[temp] += 1
        steps += 1

    return steps

jumps = read_input()
print steps_counter(jumps)
