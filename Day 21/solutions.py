def read_input():
    rules = dict()
    while True:
        try:
            line = input().split(" => ")
            rules[line[0]] = line[1]
        except EOFError:
            break

    return rules


def initial_grid():
    return ".#./..#/###"


def flip(grid):
    rows = grid.split("/")
    newgrid = []
    for i in range(1, len(rows) + 1):
        newgrid.append(rows[-i])

    return "/".join(newgrid)


def rotate(grid):
    rows = grid.split("/")
    newgrid = []
    newgrid.append([grid[0][2], grid[1][2], grid[2][2]])


def find_rule(grid):
    for rule in rules:
        for i in range(0, 8):
            if (grid == rule):
                return rule
            else:
                if (i == 4):
                    grid = flip(grid)
                else:
                    grid = rotate(grid)

    print("No rule found!")


def enhance_grids(grids):
    for grid in grids:
        grid = rules[find_rule(grid)][1]


def size_after_5():
    grid = initial_grid()
    grids = []

    for i in range(0, 5):
        enhance_grids(grid)

    return len(grid[0])

rules = read_input()
print(size_after_5())
