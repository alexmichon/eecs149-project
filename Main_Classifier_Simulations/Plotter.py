from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

target_names = ["Left-Gesture", "Right-Gesture", "Stop-Gesture"]
colors = ['navy', 'turquoise', 'darkorange']

def plot_2D_scatter(X, y, title):
    plt.figure()

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X[y == i, 0], X[y == i, 1], alpha=.8, color=color, label=target_name)

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