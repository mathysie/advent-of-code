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


def order(moves):
    positions = ["a", "b", "c", "d", "e", "f", "g",
                 "h", "i", "j", "k", "l", "m", "n", "o", "p"]

    for move in moves:
        if (move[0] == "s"):
            positions = spin(positions, move[1:])
        elif (move[0] == "x"):
            exchange(positions, move[1:])
        elif (move[0] == "p"):
            partner(positions, move[1:])

    return "".join(positions)

moves = read_input()
print order(moves)
