from Data_Getter import TestDataGetter
from sklearn.decomposition import PCA

import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

target_names = ["Left-Gesture", "Right-Gesture", "Stop-Gesture"]
colors = ['navy', 'turquoise', 'darkorange']

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


def plot_2D_scatter(X, y, title):
    lda = LinearDiscriminantAnalysis(n_components=2)
    X_lda = lda.fit(X, y).transform(X)

    plt.figure()

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X_lda[y == i, 0], X_lda[y == i, 1], alpha=.8, color=color, label=target_name)

    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title(title)
    plt.show()

def plot_3D_scatter(X, y):
    print('Explained variance ratio (first three components): %s' % str(pca.explained_variance_ratio_))

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    for color, i, target_name, shape in zip(colors, [0, 1, 2], target_names, ['o', '^', 's']):
        ax.scatter(X[y == i, 0], X[y == i, 1], X[y == i, 2], c=color, marker=shape, label=target_name)

    ax.legend()
    plt.title(title, y=1.08)
    plt.show()


# Get Data
data_getter = TestDataGetter(5, 4)
X = data_getter.get_x_data()
y = data_getter.get_y_data()

# Dimensionality Reduction
dimred = DimensionReduction(X, y)

# Draw Graphs
X_lda_2d = dimred.lda_2D_data()
plot_2D_scatter(X_lda_2d, y, '2D-LDA of Three Basic Gestures')
