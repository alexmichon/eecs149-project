from DataGetter import TestDataGetter
from DataGetter import DataSpliter
from LDA_PCA_FA_Simulation import DimensionReduction
from sklearn.naive_bayes import GaussianNB


def test_GNB(X_train, y_train, X_test, y_test):
    gnb = GaussianNB()
    y_pred = gnb.fit(X_train, y_train).predict(X_test)
    print("Number of mislabeled points out of a total %d points : %d"
          % (X_test.shape[0], (y_test != y_pred).sum()))
    print("Error Rate of GNB classifier: %s%%" % ((y_test != y_pred).sum()/X_test.shape[0]*100))

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)
    X_lda_2d = dimred.lda_2D_data()

    # Shuffle the data and split it
    spliter = DataSpliter(X_lda_2d, y, 0.6, 0, 0.4)
    X_train, y_train = spliter.get_training_set()

    # Tester
    X_test, y_test = spliter.get_testing_set()
    test_GNB(X_train, y_train, X_test, y_test)


if __name__ == "__main__":
    main()
