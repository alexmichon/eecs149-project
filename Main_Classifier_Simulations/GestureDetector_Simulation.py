from DataGetter import TestDataGetter
from DataGetter import DataSpliter

from LDA_PCA_FA_Simulation import DimensionReduction
from sklearn.naive_bayes import GaussianNB


class GestureDetector(object):
    """
    The classifier to determine whether it is a gesture or not.
    """
    def __init__(self, X_train, y_train):
        self.X_train = X_train
        self.y_train = y_train
        self.predictor = GaussianNB().fit(X_train, y_train)

    def predict(self, X):
        return self.predictor.predict(X)

def gnb_detector(X_train, y_train, X_test, y_test):
    gesture_detector = GestureDetector(X_train, y_train)
    y_pred = gesture_detector.predict(X_test)
    print("GBN - Percentage of mislabeled points: %.2f%%" % (float((y_test != y_pred).sum())/X_test.shape[0]*100))

def main():
    # Get Data
    data_getter = TestDataGetter(10, 9)
    X = data_getter.get_x_data(used_for="detector")
    y = data_getter.get_y_data(used_for="detector")

    # Data Spliter
    spliter = DataSpliter(X, y, 0.7, 0, 0.3)
    X_train, y_train = spliter.get_training_set()
    X_test, y_test = spliter.get_testing_set()

    # Dimensionality Reduction
    dimred = DimensionReduction(X_train, y_train, X_test)
    X_reduced_train, X_reduced_test = dimred.lda_data()

    # Gaussian Naive Bayes Classifier

    gnb_detector(X_reduced_train, y_train, X_reduced_test, y_test)


if __name__ == "__main__":
    main()
