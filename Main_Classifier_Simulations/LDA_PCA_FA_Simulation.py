from DataGetter import TestDataGetter
from DataGetter import DataSpliter

from Plotter import *

from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.decomposition import FactorAnalysis

class DimensionReduction(object):
    def __init__(self, X_train, y_train, X_div, dim=2):
        self.X_train = X_train
        self.y_train = y_train
        self.X_div   = X_div
        self.dim     = dim

    def lda_data(self):
        reductor = LinearDiscriminantAnalysis(n_components=self.dim).fit(self.X_train, self.y_train)
        return reductor.transform(self.X_train), reductor.transform(self.X_div)

    def pca_data(self):
        reductor = PCA(n_components=self.dim).fit(self.X_train)
        return reductor.transform(self.X_train), reductor.transform(self.X_div)

    def fa_2D_data(self):
        reductor = FactorAnalysis(n_components=self.dim).fit(self.X_train, self.y_train)
        return reductor.transform(self.X_train), reductor.transform(self.X_div)

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Shuffle the data and split it
    spliter = DataSpliter(X, y, 1, 0, 0)
    X_train, y_train = spliter.get_training_set()

    # Dimensionality Reduction
    dimred = DimensionReduction(X_train, y_train, X_train)

    # Draw LDA Graphs
    X_lda_2d, _ = dimred.lda_data()
    plot_gst_clf_scatter_2D(X_lda_2d, y_train, '32-LDA of Three Basic Gestures')

def test_explained_variance_LDA():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Shuffle the data and split it
    spliter = DataSpliter(X, y, 1, 0, 0)
    X_train, y_train = spliter.get_training_set()

    # Dimensionality Reduction
    for i in range(1, 31):
        reductor = LinearDiscriminantAnalysis(n_components=i).fit(X_train, y_train)
        print("Dim = %2d: explained variance ratio:" % i, sum(reductor.explained_variance_ratio_))

if __name__ == "__main__":
    test_explained_variance_LDA()
