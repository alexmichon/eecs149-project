import data_parser
from sklearn.naive_bayes import GaussianNB
import numpy as np
import matplotlib.pyplot as plt

from sklearn.model_selection import ShuffleSplit
from sklearn.model_selection import learning_curve
from sklearn.model_selection import train_test_split

from mlxtend.plotting import plot_decision_regions


def load_data(test_size, random_state):
	X_left, Y_left = data_parser.parse("TestData/left", 0)
	X_right, Y_right = data_parser.parse("TestData/right", 1)
	X_stop, Y_stop = data_parser.parse("TestData/stop", 2)

	X = np.concatenate((X_left, X_right, X_stop))
	Y = np.concatenate((Y_left, Y_right, Y_stop))

	return train_test_split(X, Y, test_size=test_size, random_state=random_state)



def plot_learning_curve(estimator, title, X, y, ylim=None, cv=None):
	plt.figure()
	plt.title(title)
	if ylim is not None:
		plt.ylim(ylim)
	plt.xlabel("Training examples")
	plt.ylabel("Score")
	train_size, train_scores, test_scores = learning_curve(estimator, X, y, cv=cv)
	train_scores_mean = np.mean(train_scores, axis=1)
	train_scores_std = np.std(train_scores, axis=1)
	test_scores_mean = np.mean(test_scores, axis=1)
	test_scores_std = np.std(test_scores, axis=1)
	plt.grid()

	plt.fill_between(train_size, train_scores_mean - train_scores_std, train_scores_mean + train_scores_std, alpha=0.1, color="r")
	plt.fill_between(train_size, test_scores_mean - test_scores_std, test_scores_mean + test_scores_std, alpha=0.1, color="g")
	plt.plot(train_size, train_scores_mean, 'o-', color="r", label="Training score")
	plt.plot(train_size, test_scores_mean, 'o-', color="g", label="Cross-validation score")

	plt.legend(loc="best")
	return plt


if __name__ == "__main__":
	X_train, X_test, Y_train, Y_test = load_data(0.3, 42)

	clf = GaussianNB()
	clf.fit(X_train, Y_train.ravel())

	print("Score: " + str(clf.score(X_test, Y_test)))


	title = "GaussianNB"
	cv = ShuffleSplit(n_splits=100, test_size=0.2, random_state=0)
	estimator = GaussianNB()

	plot_learning_curve(estimator, title, X_train, Y_train, cv=cv)
	plt.show()

	plot_decision_regions(X_train, Y_train, clf=clf, filler_feature_values={2: 1, 3: 1, 4: 1, 5: 1})
	plt.show()