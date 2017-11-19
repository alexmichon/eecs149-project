# This simulation is designated to give a graphical intuition to KNN
# Basically from Scikit-learn
from DataGetter import TestDataGetter
from PCA_LDA_Simulation import DimensionReduction
from DataGetter import DataSpliter

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

def tune_kNN(X, y):
    """
    This function is used to tune the hyperprameter K of K-NN to be optimal

    :param X: all the data whose dimensionality has been reducted to 2
    :param y: the target array
    """
    for weights in ['uniform', 'distance']:
        # Shuffle the data and split it
        spliter = DataSpliter(X, y, 0.8, 0.2, 0.2)
        X_training, y_training = spliter.get_training_set()
        X_tune, y_tune = spliter.get_evaluation_set()

        training_errors = []
        tuning_errors = []
        k_list = list(range(1, 50))

        plt.figure()
        for k in range(1, 50):
            # We create an instance of Neighbours Classifier and fit the data.
            clf = neighbors.KNeighborsClassifier(k, weights=weights)
            clf.fit(X_training, y_training)

            Z_training = clf.predict(X_training)
            Z_tuning = clf.predict(X_tune)

            training_errors.append(np.mean(Z_training != y_training))
            tuning_errors.append(np.mean(Z_tuning != y_tune))

        plt.plot(k_list, training_errors, linestyle='--', color='navy', label='training error')
        plt.plot(k_list, tuning_errors, linestyle='-', color='turquoise', label='tuning error')
        plt.xlabel('k in k-NN')
        plt.ylabel('error rate')
        plt.legend(loc='upper right')
        plt.title("Effects of k in k neariest neighbours - %s" % weights)
        plt.show()

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)
    X_lda_2d = dimred.lda_2D_data()

    # K-NN Tuner
    tune_kNN(X_lda_2d, y)

if __name__ == "__main__":
    main()
