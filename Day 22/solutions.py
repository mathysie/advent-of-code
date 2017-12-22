def read_input():
    map = []
    while True:
        try:
            map.append(list(input()))
        except EOFError:
            break

    print("Start!")
    return map


def build_grid(N):
    grid = []
    for i in range(0, N):
        row = []
        for j in range(0, N):
            row.append('.')
        grid.append(row)

    for i in range(0, len(map)):
        for j in range(0, len(map)):
            grid[int((N - len(map)) / 2) + i][
                int((N - len(map)) / 2) + j] = map[i][j]
    return grid


def infections():
    N = 999  # Pick a random uneven number with no out of bounds
    grid = build_grid(N)
    i = int((N - 1) / 2)
    j = int((N - 1) / 2)
    direction = "n"
    counter = 0

    for k in range(0, 10000):
        if grid[i][j] == ".":
            if direction == "n":
                direction = "w"
            elif direction == "w":
                direction = "s"
            elif direction == "s":
                direction = "e"
            elif direction == "e":
                direction = "n"
            grid[i][j] = "#"
            counter += 1
        elif grid[i][j] == "#":
            if direction == "n":
                direction = "e"
            elif direction == "e":
                direction = "s"
            elif direction == "s":
                direction = "w"
            elif direction == "w":
                direction = "n"
            grid[i][j] = "."
        if direction == "n":
            i -= 1
        elif direction == "e":
            j += 1
        elif direction == "s":
            i += 1
        elif direction == "w":
            j -= 1
        print(k)

    return counter


map = read_input()
print(infections())
