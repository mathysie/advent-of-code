import numpy as np


def amount_cycles(sequence):
    memory = [sequence]
    cycle = False

    while not cycle:
        newsequence = list(memory[len(memory) - 1])
        max_index = np.argmax(newsequence)
        blocks = newsequence[max_index]

        # Redistribute blocks
        newsequence[max_index] = 0
        for i in range(0, blocks):
            newsequence[(max_index + i + 1) % len(newsequence)] += 1

        # Add new sequence to memory
        memory.append(newsequence)

        # Check if new sequence has been found before
        for i in range(0, len(memory) - 1):
            if (memory[i] == memory[len(memory) - 1]):
                print len(memory) - 1  # Print the amount of cycles before loop
                print len(memory) - 1 - i  # Print the length of the loop
                cycle = True


sequence = raw_input().split('\t')
sequence = [int(i) for i in sequence]
amount_cycles(sequence)
