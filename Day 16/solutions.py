def read_input():
    return raw_input().split(",")


def spin(positions, total):
    total = int(total)
    positions = positions[-total:] + positions[0:16 - total]
    return positions


def exchange(positions, pos):
    pos = [int(i) for i in pos.split("/")]
    positions[pos[0]], positions[pos[1]] = positions[pos[1]], positions[pos[0]]


def partner(positions, programs):
    programs = programs.split("/")
    index1 = positions.index(programs[0])
    index2 = positions.index(programs[1])
    positions[index1], positions[index2] = positions[index2], positions[index1]


def dance_round(positions):
    for move in moves:
        if (move[0] == "s"):
            positions = spin(positions, move[1:])
        elif (move[0] == "x"):
            exchange(positions, move[1:])
        elif (move[0] == "p"):
            partner(positions, move[1:])

    return positions


def order():
    N = 0
    new_positions = list(positions)

    while True:
        new_positions = dance_round(new_positions)
        N += 1
        if new_positions == positions:
            break

    return N


def dance():
    N = order()

    new_positions = list(positions)
    for i in range(0, 10 ** 9 % N):
        new_positions = dance_round(list(new_positions))

    return "".join(new_positions)

moves = read_input()
positions = ["a", "b", "c", "d", "e", "f", "g",
             "h", "i", "j", "k", "l", "m", "n", "o", "p"]
print "".join(dance_round(positions))
print dance()
