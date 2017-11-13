# This simulation is designated to give a graphical intuition to KNN
# Basically from Scikit-learn
from DataGetter import TestDataGetter
from PCA_LDA_Simulation import DimensionReduction

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn import neighbors, datasets

# Create color maps
cmap_light = ListedColormap(['#FFAAAA', '#AAFFAA', '#AAAAFF'])
cmap_bold = ListedColormap(['#FF0000', '#00FF00', '#0000FF'])

def plot_kNN(X, y, n_neighbors=10, h=0.02):
    # For sake of Integrity, we show two methods here, but in practice, one is enough
    # And that one would probably be 'distance'

    for weights in ['uniform', 'distance']:
        # we create an instance of Neighbours Classifier and fit the data.
        clf = neighbors.KNeighborsClassifier(n_neighbors, weights=weights)
        clf.fit(X, y)

        # Plot the decision boundary. For that, we will assign a color to each
        # point in the mesh [x_min, x_max]x[y_min, y_max].
        x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
        y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1

        xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
        Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])

        # Put the result into a color plot
        Z = Z.reshape(xx.shape)

        plt.figure()
        plt.pcolormesh(xx, yy, Z, cmap=cmap_light)

        # Plot also the training points
        plt.scatter(X[:, 0], X[:, 1], c=y, cmap=cmap_bold, edgecolor='k', s=20)
        plt.xlim(xx.min(), xx.max())
        plt.ylim(yy.min(), yy.max())

        plt.title("3-Class classification (k = %i, weights = '%s')" % (n_neighbors, weights))
        plt.show()


def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)
    X_lda_2d = dimred.lda_2D_data()

    # kNN Plotter
    plot_kNN(X_lda_2d, y)

if __name__ == "__main__":
    # stuff only to run when not called via 'import' here
    main()
