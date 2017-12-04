def count_valid_passphrases():
    counter = 0
    while True:
        try:
            line = raw_input().split(" ")
            counter += passphrase_isvalid(line)
        except EOFError:
            break

    return counter


def passphrase_isvalid(passphrase):
    valid = True
    for i in range(0, len(passphrase)):
        for j in range(i + 1, len(passphrase)):
            if (passphrase[i] == passphrase[j]):
                valid = False
                break
        if (not valid):
            break

    return int(valid)

print count_valid_passphrases()
