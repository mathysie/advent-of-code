def sum(sequence, offset):
    result = 0
    for i in range(0, len(sequence)):
        index2 = (i + offset) % len(sequence)
        if (sequence[i] == sequence[index2]):
            result = result + int(sequence[i])

    return result

sequence = list(raw_input())

print str(sum(sequence, 1))
print str(sum(sequence, len(sequence) / 2))
