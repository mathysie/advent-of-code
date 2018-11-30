def read_input():
    spreadsheet = []
    while True:
        try:
            line = [int(i) for i in raw_input().split('\t')]
        except EOFError:
            break
        spreadsheet.append(line)

    return spreadsheet


def calc_minmaxsum(sheet):
    checksum = 0

    for i in range(0, len(sheet)):
        checksum += max(sheet[i]) - min(sheet[i])

    return checksum


def calc_evenlydevidesum(sheet):
    checksum = 0

    for i in range(0, len(sheet)):
        sheet[i].sort(reverse=True)
        Found = False
        for j in range(0, len(sheet[i])):
            for k in range(j + 1, len(sheet[i])):
                if (sheet[i][j] % sheet[i][k] == 0):
                    checksum += sheet[i][j] / sheet[i][k]
                    Found = True
                    break
            if (Found):
                break

    return checksum

sheet = read_input()
print calc_minmaxsum(sheet)
print calc_evenlydevidesum(sheet)
