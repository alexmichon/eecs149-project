from Data_Getter import TestDataGetter
from sklearn.decomposition import PCA

import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

target_names = ["Left-Gesture", "Right-Gesture", "Stop-Gesture"]
colors = ['navy', 'turquoise', 'darkorange']

def plot_lda_2D(X, y):
    lda = LinearDiscriminantAnalysis(n_components=2)
    X_lda = lda.fit(X, y).transform(X)

    plt.figure()

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X_lda[y == i, 0], X_lda[y == i, 1], alpha=.8, color=color, label=target_name)

    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('LDA of Three Basic Gestures')
    plt.show()


def plot_pca_2D(X, y):
    pca = PCA(n_components=2)
    X_pca_2d = pca.fit(X).transform(X)

    print('Explained variance ratio (first two components): %s' % str(pca.explained_variance_ratio_))

    plt.figure()

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X_pca_2d[y == i, 0], X_pca_2d[y == i, 1], alpha=.8, color=color, label=target_name)

    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('2-D PCA of Three Basic Gestures')
    plt.show()


def plot_pca_3D(X, y):
    pca = PCA(n_components=3)
    X_pca_3d = pca.fit(X).transform(X)
    print('Explained variance ratio (first three components): %s' % str(pca.explained_variance_ratio_))

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    for color, i, target_name, shape in zip(colors, [0, 1, 2], target_names, ['o', '^', 's']):
        ax.scatter(X_pca_3d[y == i, 0], X_pca_3d[y == i, 1], X_pca_3d[y == i, 2], c=color, marker=shape, label=target_name)

    ax.legend()
    plt.title('3D-PCA of Three Basic Gestures', y=1.08)
    plt.show()


data_getter = TestDataGetter(5, 4)
X = data_getter.get_x_data()
y = data_getter.get_y_data()
plot_lda_2D(X, y)
