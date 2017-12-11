from DataGetter import TestDataGetter
from DataGetter import DataSpliter
from LDA_PCA_FA_Simulation import DimensionReduction
from sklearn.naive_bayes import GaussianNB


def test_GNB(X_train, y_train, X_test, y_test, dim=2):
    gnb = GaussianNB()
    y_pred = gnb.fit(X_train, y_train).predict(X_test)
    # print("Number of mislabeled points out of a total %d points : %d"
    #       % (X_test.shape[0], (y_test != y_pred).sum()))
    print("Dim = %2d: Error Rate of GNB classifier: %s%%" % (dim, (float((y_test != y_pred).sum())/X_test.shape[0]*100)) )

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Shuffle the data and split it
    spliter = DataSpliter(X, y, 0.6, 0, 0.4)
    X_train, y_train = spliter.get_training_set()
    X_test, y_test = spliter.get_testing_set()

    # Dimensionality Reduction
    dimred = DimensionReduction(X_train, y_train, X_test)
    X_reduced_trian, X_reduced_test = dimred.lda_data()

    test_GNB(X_reduced_trian, y_train, X_reduced_test, y_test)

def test_dim():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Shuffle the data and split it
    spliter = DataSpliter(X, y, 0.7, 0, 0.3)
    X_train, y_train = spliter.get_training_set()
    X_test, y_test = spliter.get_testing_set()

    # Dimensionality Reduction
    for i in range(1,31):
        dimred = DimensionReduction(X_train, y_train, X_test, i)
        X_reduced_trian, X_reduced_test = dimred.pca_data()
        test_GNB(X_reduced_trian, y_train, X_reduced_test, y_test, i)

if __name__ == "__main__":
    test_dim()
