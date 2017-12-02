def read_input ():
	spreadsheet = []
	while True:
	    try:
	        line = [int(i) for i in raw_input().split('\t')]
	    except EOFError:
	        break
	    spreadsheet.append(line)

	return spreadsheet

def calc_checksum(sheet):
	checksum = 0

	for i in range(0,len(sheet)):
		checksum += max(sheet[i]) - min(sheet[i]);

	return checksum

sheet = read_input()
print calc_checksum(sheet)