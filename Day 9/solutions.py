def count_score(stream):
    score = 0
    level = 0
    is_comment = False

    it = iter(range(0, len(stream)))
    for i in it:
        if (stream[i] == "!"):
            it.next()
        elif (stream[i] == "<"):
            is_comment = True
        elif (stream[i] == ">" and is_comment):
            is_comment = False
        elif (not is_comment):
            if (stream[i] == "{"):
                level += 1
            elif (stream[i] == "}"):
                score += level
                level -= 1

    return score

stream = raw_input()
print count_score(stream)
