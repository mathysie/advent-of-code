def read_input():
    components = dict()
    while True:
        try:
            line = input().split("/")
            component = [int(line[0]), int(line[1])]
            for i in [0, 1]:
                if int(line[i]) not in components:
                    components[int(line[i])] = []
                components[int(line[i])].append(component)
        except EOFError:
            break

    return components


def strength_bridge(bridge):
    length = 0
    for component in bridge:
        length += component[0] + component[1]

    return length


def build_bridge(bridges, bridge, last):
    bridges.append(bridge)
    if bridge[-1][0] == last:
        newlast = bridge[-1][1]
    else:
        newlast = bridge[-1][0]

    options = [option for option in components[newlast]
               if option not in bridge]
    for option in options:
        newbridge = list(bridge)
        newbridge.append(option)

        if (option[0] == newlast):
            build_bridge(bridges, newbridge, option[0])
        elif (option[1] == newlast):
            build_bridge(bridges, newbridge, option[1])


def build_bridges():
    bridges = []
    options = components[0]

    for option in options:
        build_bridge(bridges, [option], 0)

    return bridges


def strongest_bridge():
    strength = 0

    for bridge in bridges:
        if strength_bridge(bridge) > strength:
            strength = strength_bridge(bridge)

    return strength


def strongest_longest_bridge():
    strength = 0
    length = 0

    for bridge in bridges:
        if len(bridge) > length:
            length = len(bridge)
        if len(bridge) == length:
            if strength_bridge(bridge) > strength:
                strength = strength_bridge(bridge)

    return strength


components = read_input()
bridges = build_bridges()
print(strongest_bridge())
print(strongest_longest_bridge())
