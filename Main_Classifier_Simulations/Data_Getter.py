"""This file provides methods for getting the test data."""

import csv

class Config(object):
    """
    Define a class to store parameters
    NOTE:
        batch_size should larger or equal than 1
        overlap_size should smaller than batch_size but larger or equal than 0
    """

    def __init__(self, batch_size, overlap_size):
        self.batch_size = batch_size
        self.overlap_size = overlap_size
        self.new_data_size = batch_size - overlap_size


def get_data_matrix(file_path):
    print("Getting Data...")

    config = Config(5, 4)
    result_matrix = []

    with open(file_path, newline='') as testfile:
        current_batch_index = 0
        current_test_row_index = 0
        current_new_data_size = 0
        buffer = [] # Store the overlap data
        reader = csv.reader(testfile, delimiter=',')
        for row in reader:
            if row:
                # Not a empty line, which means it still comes from the same batch of sample
                if current_test_row_index < config.overlap_size:
                    buffer.append(row[:-1])
                else:
                    if current_new_data_size == config.new_data_size - 1:
                        buffer.append(row[:-1])

                        # Output the data from buffer to result matrix
                        result_matrix.append([])
                        for sample in buffer:
                            result_matrix[current_batch_index] += sample
                        current_batch_index += 1

                        # Get rid of the useless data, only preserve the overlap data
                        buffer = buffer[config.new_data_size:]

                        # Re-initial the new_data_size
                        current_new_data_size = 0
                    else:
                        buffer.append(row[:-1])
                        current_new_data_size += 1

                current_test_row_index += 1
            else:
                # Empty line, which means the data will change to another batch
                current_test_row_index = 0
                buffer = []
    testfile.close()

    return result_matrix

for item in get_data_matrix('TestData/left'):
    print(item)