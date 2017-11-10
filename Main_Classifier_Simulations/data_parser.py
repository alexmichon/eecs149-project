import numpy as np
import csv


def parse(path, type):
	print("Parsing data from " + path)

	data = np.empty((0,6))

	with open(path, newline='') as file:
		reader = csv.reader(file, delimiter=',')
		for row in reader:
			if row:
				a = np.array([row[:-1]])
				data = np.append(data, a, axis=0)

	target = np.full((data.shape[0],), type)
	return data.astype(np.float), target


if __name__ == "__main__":
	parse("TestData/left", "left")
	parse("TestData/right", "right")
	parse("TestData/stop", "stop")