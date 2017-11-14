from DataGetter import TestDataGetter
from PCA_LDA_Simulation import DimensionReduction
import numpy as np
import matplotlib.pyplot as plt
from sklearn.gaussian_process import GaussianProcessClassifier
from sklearn.gaussian_process.kernels import RBF
from sklearn import datasets

def plot_GPC(X, y, h = .5):
    """
    Plot the result of Gesture Classification after Gaussian Process

    :param X: data set
    :param y: targets
    :param h: step size in the mesh
    """
    kernel = 1.0 * RBF([1.0])
    gpc_rbf_isotropic = GaussianProcessClassifier(kernel=kernel).fit(X, y)
    kernel = 1.0 * RBF([1.0, 1.0])
    gpc_rbf_anisotropic = GaussianProcessClassifier(kernel=kernel).fit(X, y)

    # Create a mesh to plot in
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                         np.arange(y_min, y_max, h))

    titles = ["Isotropic RBF", "Anisotropic RBF"]
    plt.figure(figsize=(10, 5))
    for i, clf in enumerate((gpc_rbf_isotropic, gpc_rbf_anisotropic)):
        # Plot the predicted probabilities. For that, we will assign a color to
        # each point in the mesh [x_min, m_max]x[y_min, y_max].
        plt.subplot(1, 2, i + 1)

        Z = clf.predict_proba(np.c_[xx.ravel(), yy.ravel()])

        # Put the result into a color plot
        Z = Z.reshape((xx.shape[0], xx.shape[1], 3))
        plt.imshow(Z, extent=(x_min, x_max, y_min, y_max), origin="lower")

        # Plot also the training points
        plt.scatter(X[:, 0], X[:, 1], c=np.array(["r", "g", "b"])[y], edgecolors=(0, 0, 0))
        plt.xlabel('First Component')
        plt.ylabel('Second Component')
        plt.xlim(xx.min(), xx.max())
        plt.ylim(yy.min(), yy.max())
        plt.xticks(())
        plt.yticks(())
        plt.title("%s, LML: %.3f" %
                  (titles[i], clf.log_marginal_likelihood(clf.kernel_.theta)))

    plt.tight_layout()
    plt.show()

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data()
    y = data_getter.get_y_data()

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)
    X_lda_2d = dimred.lda_2D_data()

    # GPC Plotter
    plot_GPC(X_lda_2d, y, 0.125)

if __name__ == "__main__":
    main()