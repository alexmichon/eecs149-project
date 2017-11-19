from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

target_names = ["Left-Gesture", "Right-Gesture", "Stop-Gesture"]
colors = ['navy', 'turquoise', 'darkorange']

def plot_gst_clf_scatter_2D(X, y, title):
    plt.figure()

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X[y == i, 0], X[y == i, 1], alpha=.8, color=color, label=target_name)

    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title(title)
    plt.show()

def plot_gst_clf_scatter_3D(X, y, title):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    for color, i, target_name, shape in zip(colors, [0, 1, 2], target_names, ['o', '^', 's']):
        ax.scatter(X[y == i, 0], X[y == i, 1], X[y == i, 2], c=color, marker=shape, label=target_name)

    ax.legend()
    plt.title(title, y=1.08)
    plt.show()

def plot_gst_detector_2D(X, y, title):
    plt.figure()

    plt.scatter(X[y == -1, 0], X[y == -1, 1], alpha=.8, color='navy', label="NONE")
    plt.scatter(X[y >= 0 , 0], X[y >= 0, 1], alpha=.8, color='turquoise', label="GESTURING")

    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title(title)
    plt.show()