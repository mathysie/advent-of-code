def count_score(stream):
    score = 0
    level = 0
    is_comment = False
    garbage_count = 0

    it = iter(range(0, len(stream)))
    for i in it:
        if (stream[i] == "!"):
            it.next()
        elif (stream[i] == "<" and not is_comment):
            is_comment = True
        elif (stream[i] == ">" and is_comment):
            is_comment = False
        elif (is_comment):
            garbage_count += 1
        elif (stream[i] == "{"):
            level += 1
        elif (stream[i] == "}"):
            score += level
            level -= 1

    print score
    print garbage_count

stream = raw_input()
count_score(stream)
