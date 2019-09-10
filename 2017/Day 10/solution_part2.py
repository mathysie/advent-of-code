from numpy import zeros


def convert_lengths(lengths):
    for i in range(0, len(lengths)):
        lengths[i] = ord(lengths[i])
    lengths += [17, 31, 73, 47, 23]


def hash_round(chain, lengths, skip_cur):
    for length in lengths:
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


def hash(lengths):
    chain = range(256)
    skip_cur = [0, 0]

    convert_lengths(lengths)
    for i in range(0, 64):
        hash_round(chain, lengths, skip_cur)

    dense_hash = create_dense_hash(chain)
    return dense_hash


lengths = list(raw_input())
print hash(lengths)
