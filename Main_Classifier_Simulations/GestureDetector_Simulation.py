from DataGetter import TestDataGetter
from DataGetter import DataSpliter

from LDA_PCA_FA_Simulation import DimensionReduction
from sklearn.naive_bayes import GaussianNB
from sklearn.discriminant_analysis import  LinearDiscriminantAnalysis
from Plotter import plot_gst_detector_2D

def gnb_detector(X_train, y_train, X_test, y_test):
    gnb = GaussianNB()
    y_pred = gnb.fit(X_train, y_train).predict(X_test)
    print("GBN - Percentage of mislabeled points: %d%%" % ((y_test != y_pred).sum()/X_test.shape[0] *100))

def lda_detector(X_train, y_train, X_test, y_test):
    clf = LinearDiscriminantAnalysis()
    clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    print("LDA - Percentage of mislabeled points: %d%%" % ((y_test != y_pred).sum() / X_test.shape[0] * 100))

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data(False)
    y = data_getter.get_y_data(False)

    # Data Spliter
    spliter = DataSpliter(X, y, 0.6, 0, 0.4)
    X_train, y_train = spliter.get_training_set()
    X_test, y_test = spliter.get_testing_set()

    # Dimensionality Reduction
    dimred = DimensionReduction(X_train, y_train, X_test)
    X_reduced_train, X_reduced_test = dimred.lda_data()

    # Gaussian Naive Bayes Classifier

    gnb_detector(X_reduced_train, y_train, X_reduced_test, y_test)
    lda_detector(X_reduced_train, y_train, X_reduced_test, y_test)

if __name__ == "__main__":
    # stuff only to run when not called via 'import' here
    main()
