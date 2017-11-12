from DataGetter import TestDataGetter

from Plotter import *

from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis

class DimensionReduction(object):
    def __init__(self, X, y):
        self.X = X
        self.y = y

    def lda_2D_data(self):
        return LinearDiscriminantAnalysis(n_components=2).fit(self.X, self.y).transform(self.X)

    def pca_2D_data(self):
        return PCA(n_components=2).fit(self.X).transform(self.X)

    def pca_3D_data(self):
        return PCA(n_components=3).fit(self.X).transform(self.X)



def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)
    X_lda_2d = dimred.lda_2D_data()

    # Draw Graphs
    plot_2D_scatter(X_lda_2d, y, '2D-LDA of Three Basic Gestures')

if __name__ == "__main__":
    # stuff only to run when not called via 'import' here
    main()