import numpy as np


def amount_cycles(sequence):
    count = 0
    memory = [sequence]
    cycle = False
    while True:
        newsequence = list(memory[count])
        index = np.argmax(newsequence)
        blocks = newsequence[index]
        newsequence[index] = 0
        for i in range(0, blocks):
            newsequence[(index + i + 1) % len(newsequence)] += 1
        memory.append(newsequence)
        count += 1
        for i in range(0, count):
            if (memory[i] == memory[count]):
                cycle = True
                break
        if (cycle):
            break

    return count


sequence = raw_input().split('\t')
sequence = [int(i) for i in sequence]
print amount_cycles(sequence)
