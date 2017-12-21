from numpy import rot90


def read_input():
    rules = list()
    while True:
        try:
            line = input().split(" => ")
            line[0] = line[0].split("/")

            grid_in = []
            for i in range(0, len(line[0])):
                grid_in.append([list(line[0])[i]])

            line[1] = line[1].split("/")
            grid_out = []
            for i in range(0, len(line[0])):
                grid_out.append([list(line[1])[i]])

            rules.append([grid_in, grid_out])
        except EOFError:
            break

    return rules


def initial_grid():
    return [
        [".", "#", "."],
            [".", ".", "#"],
            ["#", "#", "#"]
    ]


def find_rule(grid):
    for rule in rules:
        temp = rule[0]
        print(temp)
        if (grid == temp or grid == rot90(temp, 1) or grid == rot90(temp, 2) or grid == rot90(temp, 3)):
            return rule
        temp = temp[::-1]
        if (grid == temp or grid == rot90(temp, 1) or grid == rot90(temp, 2) or grid == rot90(temp, 3)):
            return rule

    print("No rule found!")


def enhance_grids(grids):
    for grid in grids:
        grid = rules[find_rule(grid)][1]


def size_after_5():
    grid = initial_grid()
    grids = []

    for i in range(0, 5):
        if (len(grid[0]) % 2):
            N = 2
        elif (len(grid[0]) % 3):
            N = 3

        for k in range(0, int(len(grid[0]) / N)):
            for j in range(0, int(len(grid[0]) / N)):
                grids.append(grid[N * k:N * k + 1][N * j:N * j + 1])
        enhance_grids(grids)
        grid = []
        for k in range(0, int(len(grid[0]) / N)):
            for j in range(0, int(len(grid[0]) / N)):
                grid[N * k:N * k + 1][N * j:N * j + 1] = grids[N * k + j]

    return len(grid[0])

rules = read_input()
print(size_after_5())
