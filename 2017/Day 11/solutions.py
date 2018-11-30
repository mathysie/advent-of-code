from math import floor


def dist(x, y):
    if (x * y < 0):
        return max(abs(x), abs(y))
    else:
        return abs(x) + abs(y)


def max_dist(directions):
    x = 0
    y = 0
    steps = 0
    max_distance = 0

    for step in directions:
        if (step == 'n'):
            y += 1
        elif (step == 's'):
            y -= 1
        elif (step == 'ne'):
            x += 1
        elif (step == 'se'):
            y -= 1
            x += 1
        elif (step == 'nw'):
            y += 1
            x -= 1
        elif (step == 'sw'):
            x -= 1
        if (dist(x, y) > max_distance):
            max_distance = dist(x, y)

    print dist(x, y)
    return max_distance


directions = raw_input().split(",")
print max_dist(directions)
