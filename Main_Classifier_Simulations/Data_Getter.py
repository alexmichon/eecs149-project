"""This file provides methods for getting the test data."""

import csv
import numpy as np

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

class TestDataGetter(object):
    """
    Define a helper class to get all the data used for test
    NOTE:
        batch_size should larger or equal than 1
        overlap_size should smaller than batch_size but larger or equal than 0
    """

    def __init__(self, batch_size, overlap_size):
        self.config = Config(batch_size, overlap_size)
        self.X_left = self.__get_x_data_matrix("TestData/left")
        self.X_right = self.__get_x_data_matrix("TestData/right")
        self.X_stop = self.__get_x_data_matrix("TestData/stop")

    def get_x_data(self):

        X = np.concatenate((self.X_left, self.X_right, self.X_stop))

        return X


    def get_y_data(self):
        y = []
        for i in range(self.X_left.shape[0]):
            y.append(0)
        for i in range(self.X_right.shape[0]):
            y.append(1)
        for i in range(self.X_stop.shape[0]):
            y.append(2)

        y = np.array(y)

        return y


    def __get_x_data_matrix(self, file_path):
        print("Getting Data From " + file_path + " ...")

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
                    if current_test_row_index < self.config.overlap_size:
                        buffer.append(row[:-1])
                    else:
                        if current_new_data_size == self.config.new_data_size - 1:
                            buffer.append(row[:-1])

                            # Output the data from buffer to result matrix
                            result_matrix.append([])
                            for sample in buffer:
                                result_matrix[current_batch_index] += sample
                            current_batch_index += 1

                            # Get rid of the useless data, only preserve the overlap data
                            buffer = buffer[self.config.new_data_size:]

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

        return np.array(result_matrix).astype(np.float)


