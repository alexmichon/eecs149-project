"""This file provides methods for getting the test data."""

import csv
import numpy as np
import random
import os

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
        self.X_none = self.__get_x_data_matrix("TestData/none")
        # self.X_switch = self.__get_x_data_matrix("FinalData/switch_sweep")


    def get_x_data(self, used_for="gesture"):
        """
        Get the x data from the data set by requirement set in the init function

        :param used_for: can only be one of the 3 values: "detector", "switch", "gesture"
        :return: parsed data matrix
        """
        if used_for == "detector":
            return np.concatenate((self.X_left, self.X_right, self.X_stop, self.X_switch, self.X_none))
        elif used_for == "switch":
            return np.concatenate((self.X_left, self.X_right, self.X_stop, self.X_switch))
        else:
            return np.concatenate((self.X_left, self.X_right, self.X_stop))

    def get_y_data(self, used_for="gesture"):
        """
        Get the target/y data from the data set by requirement set in the init function

        :param used_for: can only be one of the 3 values: "detector", "switch", "gesture"
        :return: parsed target class array
        """
        y = []

        if used_for == "detector":
            y = np.concatenate((np.full(self.X_left.shape[0] + self.X_right.shape[0] + self.X_stop.shape[0] + self.X_switch.shape[0], 1), np.full(self.X_none.shape[0], 0)))
        elif used_for == "switch":
            y = np.concatenate((np.full(self.X_left.shape[0] + self.X_right.shape[0] + self.X_stop.shape[0], 0), np.full(self.X_switch.shape[0], 1)))
        else:
            y = np.concatenate((np.full(self.X_left.shape[0], 0), np.full(self.X_right.shape[0], 1), np.full(self.X_stop.shape[0], 2)))
        return np.array(y)

    def __get_x_data_matrix(self, file_path):
        print("Getting Data From " + file_path + " ...")

        result_matrix = []
        file_path = os.path.join(os.path.dirname(__file__), file_path)

        with open(file_path) as testfile:
            buffer = []  # Store the overlap data
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

        testfile.close()

        return np.array(result_matrix).astype(np.float)


class DataSpliter(object):
    """
    This is the helper class to split the data into 3 parts:
    1. training data   - 50% - used to learn model weights
    2. tuning data - 20% - used to tune hyperparameters, choose among different models
    3. testing data    - 30% - used as FINAL evaluation of model. Keep in a vault. Run ONCE, at the very end.

    :param X: All feature data
    :param y: All corresponding target data
    :param training_p: percentage of training data
    :param tuning_p: percentage of tuning data
    :param testing_p: percentage of testing data
    """
    def __init__(self, X, y, training_p=.5, tuning_p=.2, testing_p=.3):
        if len(X) != len(y):
            raise ValueError("X and y must have the same size")
        self.size = len(X)
        composite = list(zip(X, y))
        random.shuffle(composite)
        self.X, self.y = zip(*composite)
        self.X = np.array(self.X)
        self.y = np.array(self.y)

        self.training_p = training_p
        self.tuning_p = tuning_p
        self.testing_p = testing_p
    def get_training_set(self):
        return self.X[:int(self.size * self.training_p)], self.y[:int(self.size * self.training_p)]

    def get_evaluation_set(self):
        return self.X[int(self.size * self.training_p) : int(self.size * (self.training_p + self.tuning_p))], self.y[int(self.size * self.training_p) : int(self.size * (self.training_p + self.tuning_p))]

    def get_testing_set(self):
        return self.X[int(self.size * (self.training_p + self.tuning_p)):], self.y[int(self.size * (self.training_p + self.tuning_p)):]