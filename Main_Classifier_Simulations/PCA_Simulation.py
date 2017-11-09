from Data_Getter import get_data_matrix
from sklearn.decomposition import PCA

import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

X_left = get_data_matrix("TestData/left")
X_right = get_data_matrix("TestData/right")
X_stop = get_data_matrix("TestData/stop")

X = np.concatenate((X_left, X_right, X_stop))


def plot_lda_2D():
    y = []
    for i in range(X_left.shape[0]):
        y.append(0)
    for i in range(X_right.shape[0]):
        y.append(1)
    for i in range(X_stop.shape[0]):
        y.append(2)

    y = np.array(y)
    lda = LinearDiscriminantAnalysis(n_components=2)
    X_all = lda.fit(X, y).transform(X)

    target_names = ["Left-Gesture", "Right-Gesture", "Stop-Gesture"]
    colors = ['navy', 'turquoise', 'darkorange']

    plt.figure()
    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X_all[y == i, 0], X_all[y == i, 1], alpha=.8, color=color,
                    label=target_name)
    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('LDA of Three Basic Gestures')

    plt.show()


def plot_pca_2D():
    pca = PCA(n_components=2)
    pca_model = pca.fit(X)
    print('Explained variance ratio (first two components): %s' % str(pca.explained_variance_ratio_))

    X_l = pca_model.transform(X_left)
    X_r = pca_model.transform(X_right)
    X_s = pca_model.transform(X_stop)

    plt.figure()
    plt.scatter(X_l[:, 0], X_l[:, 1], color="navy", alpha=.8, label="Left-Gesture")
    plt.scatter(X_r[:, 0], X_r[:, 1], color="turquoise", alpha=.8, label="Right-Gesture")
    plt.scatter(X_s[:, 0], X_s[:, 1], color="darkorange", alpha=.8, label="Left-Gesture")
    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('2-D PCA of Three Basic Gestures')

    plt.show()


def plot_pca_3D():
    pca = PCA(n_components=3)
    pca_model = pca.fit(X)
    print('Explained variance ratio (first three components): %s' % str(pca.explained_variance_ratio_))

    X_l = pca_model.transform(X_left)
    X_r = pca_model.transform(X_right)
    X_s = pca_model.transform(X_stop)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(X_l[:, 0], X_l[:, 1], X_l[:, 2], c="navy", marker='o', label="Left-Gesture")
    ax.scatter(X_r[:, 0], X_r[:, 1], X_r[:, 2], c="turquoise", marker='^', label="Right-Gesture")
    ax.scatter(X_s[:, 0], X_s[:, 1], X_s[:, 2], c="darkorange", marker='s', label="Stop-Gesture")

    ax.legend()
    plt.title('3D-PCA of Three Basic Gestures', y=1.08)
    plt.show()


plot_lda_2D()
