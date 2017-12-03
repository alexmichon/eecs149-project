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

    def lda_data(self):
        reductor = LinearDiscriminantAnalysis(n_components=dim).fit(self.X_train, self.y_train)
        return reductor.transform(self.X_train), reductor.transform(self.X_div)

    def pca_data(self):
        reductor = PCA(n_components=dim).fit(self.X_train)
        return reductor.transform(self.X_train), reductor.transform(self.X_div)

    def fa_2D_data(self):
        reductor = FactorAnalysis(n_components=dim).fit(self.X_train, self.y_train)
        return reductor.transform(self.X_train), reductor.transform(self.X_div)

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)

    # Draw LDA Graphs
    X_lda_2d = dimred.lda_2D_data()
    plot_gst_clf_scatter_2D(X_lda_2d, y, '3D-LDA of Three Basic Gestures')

if __name__ == "__main__":
    # stuff only to run when not called via 'import' here
    main()