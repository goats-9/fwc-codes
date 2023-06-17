for file in ['acce_chop.txt', 'acce_wrist.txt', 'gyro_chop.txt', 'gyro_wrist.txt']:
	fh = open(file, 'r')
	L = fh.readlines()
	fh.close()
	fh1 = open(file, 'w')
	for line in L:
		fh1.write(line.strip() + '\n')
	fh1.close()