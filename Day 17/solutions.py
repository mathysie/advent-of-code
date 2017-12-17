def value():
    buffer = [0]
    current = 0

    for i in range(1, 2018):
        current = (current + steps) % len(buffer) + 1
        buffer.insert(current, i)

    return buffer[buffer.index(2017) + 1]


steps = int(raw_input())
print value()
