import numpy as np
import csv


# Parse data line by line
# Each line is a sample
# Params:	path: path to the data file
#			type: type of the values (left, right or stop)
def parse(path, type):
	print("Parsing data from " + path)

	data = np.empty((0,6))

	with open(path, newline='') as file:
		reader = csv.reader(file, delimiter=',')
		for row in reader:
			# if row is not empty
			if row:
				# append the row to the list of samples
				a = np.array([row[:-1]])
				data = np.append(data, a, axis=0)

	# Create a target array full of the given type
	target = np.full((data.shape[0],), type)

	return data.astype(np.float), target


# Parse data by batch
# Each first 'nb_rows' rows are aligned to be a unique sample of 6*nb_rows values
# Params: 	path: path to the data file
#			type: type of the values (left, right or stop)
#			nb_rows: Number of rows used to create one sample
def parse_batch(path, type, nb_rows):
	data = np.empty((0,6*nb_rows))

	index = 0
	row_count = 0
	sample = np.zeros((1, 6*nb_rows))

	with open(path, newline='') as file:
		reader = csv.reader(file, delimiter=',')
		for row in reader:
			# if row is not empty and if the batch is not full
			if row and (row_count < nb_rows):
				# append the data to the sample
				sample[0][row_count * 6:(row_count+1)*6] = np.array([row[:-1]])
				row_count += 1
			elif not row:
				# if row empty it is the end of the sample
				# the sample is added to the list
				data = np.append(data, sample, axis=0)
				index += 1
				row_count = 0
				sample = np.zeros((1, 6*nb_rows))

	# Create a target array full of the given type
	target = np.full((data.shape[0],), type)

	return data.astype(np.float), target


if __name__ == "__main__":
	parse("TestData/left", "left")
	parse("TestData/right", "right")
	parse("TestData/stop", "stop")

	parse_batch("TestData/left", "left", 5)