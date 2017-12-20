def read_input():
    particles = []
    while True:
        try:
            particle = dict()
            line = input().split(", ")
            position = [int(i) for i in line[0][3:-1].split(",")]
            velocity = [int(i) for i in line[1][3:-1].split(",")]
            acceleration = [int(i) for i in line[2][3:-1].split(",")]
            particle["p"] = position
            particle["v"] = velocity
            particle["a"] = acceleration
            particles.append(particle)
        except EOFError:
            break

    return particles


def closest_to_zero():
    for i in range(0, len(particles)):
        if(particles[i]["a"][0] == 0 and particles[i]["a"][1] == 0 and particles[i]["a"][2] == 0):
            return i

    return "No non-moving particle found."


particles = read_input()
print(closest_to_zero())
