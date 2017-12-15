from numpy import zeros


def convert_string(string):
    for i in range(0, len(string)):
        string[i] = ord(string[i])
    string += [17, 31, 73, 47, 23]


def hash_round(chain, string, skip_cur):
    for length in string:
        temp = []

        for i in range(0, length):
            temp.append(chain[(skip_cur[1] + i) % 256])
        temp = temp[::-1]
        for i in range(0, length):
            chain[(skip_cur[1] + i) % 256] = temp[i]

        skip_cur[1] = (skip_cur[1] + length + skip_cur[0]) % 256
        skip_cur[0] += 1


def convert_hash(dense_hash):
    output = ''
    for i in dense_hash:
        if (i < 16):
            output += '0' + hex(i)[2]
        else:
            output += hex(i)[2:4]

    return output


def create_dense_hash(chain):
    dense_hash = zeros(16)
    for i in range(0, 16):
        output = chain[16 * i]
        for j in range(1, 16):
            output ^= chain[16 * i + j]
        dense_hash[i] = output

    return convert_hash(dense_hash)


def calc_hash(string):
    chain = range(256)
    skip_cur = [0, 0]

    convert_string(string)
    for i in range(0, 64):
        hash_round(chain, string, skip_cur)

    dense_hash = create_dense_hash(chain)
    return dense_hash


def convert_to_bits(hash):
    bits = ""
    for i in hash:
        bits += bin(int(i, 16))[2:].zfill(4)

    return bits


def count_ones(bits):
    ones = 0
    for i in range(0, len(bits)):
        if (bits[i] == "1"):
            ones += 1

    return ones


def used_squares(grid):
    squares = 0
    for i in range(0, 128):
        for j in range(0, 128):
            if grid[i][j] == "#":
                squares += 1

    return squares


def create_grid(key_string):
    grid = []
    for i in range(0, 128):
        row = []
        string = key_string + ['-'] + list(str(i))
        hash = calc_hash(string)
        bits = convert_to_bits(hash)
        for i in range(0, len(bits)):
            if (bits[i] == "1"):
                row.append("#")
            else:
                row.append(".")
        grid.append(row)

    return grid


def fill_region(grid, regions, i, j):
    new = []
    grid[i][j] = regions
    if (i > 0 and grid[i - 1][j] == "#"):
        new.append([i - 1, j])
    if (i < 127 and grid[i + 1][j] == "#"):
        new.append([i + 1, j])
    if (j > 0 and grid[i][j - 1] == "#"):
        new.append([i, j - 1])
    if (j < 127 and grid[i][j + 1] == "#"):
        new.append([i, j + 1])

    for coord in new:
        fill_region(grid, regions, coord[0], coord[1])


def count_regions(key_string):
    regions = 0
    grid = create_grid(key_string)
    print used_squares(grid)

    for i in range(0, 128):
        for j in range(0, 128):
            if (grid[i][j] == "#"):
                regions += 1
                fill_region(grid, regions, i, j)

    return regions


key_string = list(raw_input())
print count_regions(key_string)
