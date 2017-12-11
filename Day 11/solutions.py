from math import floor


def amount_steps(directions):
    x = 0
    y = 0
    steps = 0

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

    if (x * y < 0):
        return max(abs(x), abs(y))
    else:
        return abs(x) + abs(y)


directions = raw_input().split(",")
print amount_steps(directions)
