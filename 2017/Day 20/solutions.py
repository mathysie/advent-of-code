def read_input():
    particles = []
    while True:
        try:
            particle = dict()
            line = input().split(", ")
            position = [int(i) for i in line[0][3:-1].split(",")]
            velocity = [int(i) for i in line[1][3:-1].split(",")]
            acceleration = [int(i) for i in line[2][3:-1].split(",")]
            particle["p0"] = position[0]
            particle["p1"] = position[1]
            particle["p2"] = position[2]
            particle["v0"] = velocity[0]
            particle["v1"] = velocity[1]
            particle["v2"] = velocity[2]
            particle["a0"] = acceleration[0]
            particle["a1"] = acceleration[1]
            particle["a2"] = acceleration[2]
            particles.append(particle)
        except EOFError:
            break

    return particles


def update_particles():
    for par in particles:
        par["v0"] += par["a0"]
        par["v1"] += par["a1"]
        par["v2"] += par["a2"]
        par["p0"] += par["v0"]
        par["p1"] += par["v1"]
        par["p2"] += par["v2"]


def amount_collisions(particles):
    N = 100

    for i in range(0, N):
        collided = set([])
        update_particles()

        particles = sorted(particles, key=lambda k: k["p2"])
        particles = sorted(particles, key=lambda k: k["p1"])
        particles = sorted(particles, key=lambda k: k["p0"])
        for j in range(0, len(particles) - 1):
            if (particles[j]["p0"] == particles[j + 1]["p0"] and particles[j]["p1"] == particles[j + 1]["p1"] and particles[j]["p2"] == particles[j + 1]["p2"]):
                collided.add(j)
                collided.add(j + 1)

        collided = sorted(collided, reverse=True)
        for j in collided:
            del particles[j]

    return len(particles)


def closest_to_zero():
    for i in range(0, len(particles)):
        if(particles[i]["a0"] == 0 and particles[i]["a1"] == 0 and particles[i]["a2"] == 0):
            return i

    return "No non-moving particle found."


particles = read_input()
print(closest_to_zero())
print(amount_collisions(particles))
