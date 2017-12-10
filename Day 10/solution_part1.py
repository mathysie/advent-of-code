def hash(lengths):
    N = 256
    chain = range(N)
    skip_size = 0
    current = 0

    for length in lengths:
        temp = []

        for i in range(0, length):
            temp.append(chain[(current + i) % N])
        temp = temp[::-1]
        for i in range(0, length):
            chain[(current + i) % N] = temp[i]

        current = (current + length + skip_size) % N
        skip_size += 1

    return chain[0] * chain[1]

lengths = [int(i) for i in raw_input().split(",")]
print hash(lengths)
