"""This file provides methods for getting the test data."""

import csv
import numpy as np
import random
import os


DATA_DIR = '../data/'


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
        self.X_left = self.__get_x_data_matrix(DATA_DIR + "FinalData/left")
        self.X_right = self.__get_x_data_matrix(DATA_DIR + "FinalData/right")
        self.X_stop = self.__get_x_data_matrix(DATA_DIR + "FinalData/stop")
        self.X_none = self.__get_x_data_matrix(DATA_DIR + "FinalData/none")


    def get_x_data(self, only_gst_data=True):
        """
        Get the x data from the data set by requirement set in the init function

        :param only_gst_data: if set to false, then it will return all the data including non-gesture data
        :return: parsed data matrix
        """
        if only_gst_data:
            return np.concatenate((self.X_left, self.X_right, self.X_stop))
        else:
            return np.concatenate((self.X_none, self.X_left, self.X_right, self.X_stop))

    def get_y_data(self, only_gst_data=True):
        """
        Get the target/y data from the data set by requirement set in the init function

        :param only_gst_data: if set to false, then it will return all the data including non-gesture data
        :return: parsed target class array
        """
        y = []

        if not only_gst_data:
            for i in range(self.X_none.shape[0]):
                y.append(1)
            for i in range(self.X_left.shape[0]):
                y.append(0)
            for i in range(self.X_right.shape[0]):
                y.append(0)
            for i in range(self.X_stop.shape[0]):
                y.append(0)
        else:
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
