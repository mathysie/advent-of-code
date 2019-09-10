def count_valid_passphrases():
    counter = 0
    counter_new = 0
    while True:
        try:
            line = raw_input().split(" ")
            counter += passphrase_isvalid(line)
            counter_new += passphrase_isvalid_new(line)
        except EOFError:
            break

    print counter
    print counter_new


def passphrase_isvalid_new(passphrase):
    valid = True
    for i in range(0, len(passphrase)):
        passphrase[i] = ''.join(sorted(passphrase[i]))
        for j in range(i + 1, len(passphrase)):
            passphrase[j] = ''.join(sorted(passphrase[j]))
            if (passphrase[i] == passphrase[j]):
                valid = False
                break
        if (not valid):
            break

    return int(valid)


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

count_valid_passphrases()
