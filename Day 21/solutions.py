from math import sqrt


def read_input():
    rules = dict()
    while True:
        try:
            line = input().split(" => ")
            rules[line[0]] = line[1]
        except EOFError:
            break

    return rules


def parse_grid(grid):
    string = ""
    rows = []
    for row in grid:
        rows.append("".join(row))

    return "/".join(rows)


def format_grid(string):
    grid = []
    rows = string.split("/")
    for row in rows:
        grid.append(list(row))

    return grid


def initial_grid():
    return ".#./..#/###"


def break_grids(grid):
    len_grid = grid.find("/")
    if len_grid % 2 == 0:
        M = 2
    elif len_grid % 3 == 0:
        M = 3

    grids = []
    N = int(grid.find("/") / M)
    grid = format_grid(grid)
    for x in range(0, N):
        for y in range(0, N):
            newgrid = []
            for i in range(0, M):
                row = []
                for j in range(0, M):
                    row.append(grid[M * x + i][M * y + j])
                newgrid.append(row)
            grids.append(parse_grid(newgrid))

    return grids


def flip(grid):
    rows = grid.split("/")
    newgrid = []
    for i in range(1, len(rows) + 1):
        newgrid.append(rows[-i])

    return "/".join(newgrid)


def rotate(grid):
    rows = grid.split("/")
    newgrid = []
    for i in range(0, len(rows)):
        newrow = []
        for j in range(0, len(rows[i])):
            newrow.append(rows[len(rows) - j - 1][i])
        newgrid.append(newrow)

    return parse_grid(newgrid)


def find_rule(grid):
    for rule in rules:
        if len(rule) != len(grid):
            continue
        for i in range(0, 8):
            if (grid == rule):
                return rule
            else:
                if (i == 3):
                    grid = flip(grid)
                else:
                    grid = rotate(grid)

    print("No rule found for {}!".format(grid))


def form_grid(grids):
    result = []
    N = int(sqrt(len(grids)))
    for k in range(0, N):
        columns = []
        for j in range(0, len(grids[0])):
            rows = []
            for i in range(0, N):
                rows.append(grids[k * N + i][j])
            columns.append("".join(rows))
        result.append("/".join(columns))

    return "/".join(result)


def pixels(grid):
    counter = 0
    for i in range(0, len(grid)):
        if grid[i] == "#":
            counter += 1

    return counter


def size_after(M):
    grid = initial_grid()

    for N in range(0, M):
        grids = break_grids(grid)

        for i in range(0, len(grids)):
            grids[i] = rules[find_rule(grids[i])].split("/")

        grid = form_grid(grids)

    return pixels(grid)

rules = read_input()
print(size_after(5))
print(size_after(18))
