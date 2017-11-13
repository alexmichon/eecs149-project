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
            buffer = [] # Store the overlap data
            reader = csv.reader(testfile, delimiter=',')

            for row in reader:
                if row:
                    # Not a empty line, which means it still comes from the same batch of sample
                    buffer.append(row[:-1])
                    if len(buffer) == self.config.batch_size:
                        result_matrix.append([])
                        for sample in buffer:
                            result_matrix[-1] += sample
                        buffer = buffer[self.config.new_data_size:]
                else:
                    # Empty line, which means the data will change to another batch
                    buffer = []

                current_test_row_index += 1
            else:
                # Empty line, which means the data will change to another batch
                current_test_row_index = 0
                buffer = []

        return np.array(result_matrix).astype(np.float)
