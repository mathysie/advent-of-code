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


def used_squares(key_string):
    squares = 0
    for i in range(0, 128):
        string = key_string + ['-'] + list(str(i))
        hash = calc_hash(string)
        bits = convert_to_bits(hash)
        squares += count_ones(bits)

    return squares


key_string = list(raw_input())
print used_squares(key_string)
