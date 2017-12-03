import math as m


def man_dist(number):
    # Define the N-th ring the number is laying on
    N = m.ceil((m.sqrt(number) - 1) / 2.0)

    # Define the numbers on the N-th ring lying on the plus with center 1
    N1 = 4 * N**2 - 3 * N + 1
    N2 = 4 * N**2 - N + 1
    N3 = 4 * N**2 + N + 1
    N4 = 4 * N**2 + 3 * N + 1

    # Calculate Manhattan-distance to plus
    minimum = min(abs(number - N1), abs(number - N2),
                  abs(number - N3), abs(number - N4))

    # The numbers on the plus have Manhattan distance N, so total distance is
    # N + distance to plus
    return minimum + N

number = int(raw_input())
print man_dist(number)
