def read_input():
    components = []
    while True:
        try:
            line = input().split("/")
            components.append([int(line[0]), int(line[1])])
        except EOFError:
            break

    return components


def length_bridge(bridge):
    length = 0
    for component in bridge:
        length += component[0] + component[1]

    return length


def search_components(pins):
    options = []
    for component in components:
        if component[0] == pins or component[1] == pins:
            options.append(component)

    return options


def build_bridge(bridges, bridge, last):
    bridges.append(bridge)
    if bridge[-1][0] == last:
        newlast = bridge[-1][1]
    else:
        newlast = bridge[-1][0]
    options = search_components(newlast)

    options = [option for option in options if option not in bridge]
    for option in options:
        newbridge = list(bridge)
        newbridge.append(option)

        if (option[0] == newlast):
            build_bridge(bridges, newbridge, option[0])
        elif (option[1] == newlast):
            build_bridge(bridges, newbridge, option[1])


def strongest_bridge():
    bridges = []
    todo = []
    options = search_components(0)

    for option in options:
        build_bridge(bridges, [option], 0)

    strength = 0
    for bridge in bridges:
        if length_bridge(bridge) > strength:
            strength = length_bridge(bridge)

    return strength


components = read_input()
print(strongest_bridge())
