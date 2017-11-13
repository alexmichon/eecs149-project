import data_parser
from sklearn.naive_bayes import GaussianNB
import numpy as np
import matplotlib.pyplot as plt

from sklearn.model_selection import ShuffleSplit
from sklearn.model_selection import learning_curve
from sklearn.model_selection import train_test_split

from mlxtend.plotting import plot_decision_regions

import random


# Loads data 
# Each line is a sample
# Params:	test_size: percentage of samples used for testing
#			random_state: random value to split train and test samples
def load_data(test_size, random_state):
	# X are samples, Y are targets
	X_left, Y_left = data_parser.parse("TestData/left", 0)
	X_right, Y_right = data_parser.parse("TestData/right", 1)
	X_stop, Y_stop = data_parser.parse("TestData/stop", 2)

	# Concatentates values from each file
	X = np.concatenate((X_left, X_right, X_stop))
	Y = np.concatenate((Y_left, Y_right, Y_stop))

	return train_test_split(X, Y, test_size=test_size, random_state=random_state)


# Loads data by batches
# Params:	batch_size: number of lines to create one sample
#			test_size: percentage of samples used for testing
#			random_state: random value to split train and test samples
def load_batches(batch_size, test_size, random_state):
	# X are samples, Y are targets
	X_left, Y_left = data_parser.parse_batch("TestData/left", 0, batch_size)
	X_right, Y_right = data_parser.parse_batch("TestData/right", 1, batch_size)
	X_stop, Y_stop = data_parser.parse_batch("TestData/stop", 2, batch_size)

	# Concatentates values from each file
	X = np.concatenate((X_left, X_right, X_stop))
	Y = np.concatenate((Y_left, Y_right, Y_stop))

	return train_test_split(X, Y, test_size=test_size, random_state=random_state)


# Plot learning curbe
# Params: 	estimator: model (here GaussianNB)
#			title: title of the graph
#			X: samples
#			Y: targets
#			ylim: limit of the Y axis
#			cv: cross-validation generator
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


# Test with a given number of rows per sample
# Returns the score on the test samples
# Params: 	batch_size: number of lines to create one sample
def test_batches(batch_size):
	X_train, X_test, Y_train, Y_test = load_batches(batch_size, 0.3, random.randint(1,100))

	# Train model on train samples
	clf = GaussianNB()
	clf.fit(X_train, Y_train.ravel())

	# Test model on test samples
	return clf.score(X_test, Y_test)


if __name__ == "__main__":

	# Test on batch sizes from 1 to 10
	for i in range(1,11):
		# Run the test 100 times to get an average value 
		scores = 0
		for j in range(100):
			scores += test_batches(i)
		print("Batch size: {0}\tScore: {1:.2f}%".format(i, scores))

	'''
	X_train, X_test, Y_train, Y_test = load_batches(5, 0.3, 42)

	clf = GaussianNB()
	clf.fit(X_train, Y_train.ravel())

	print("Score: " + str(clf.score(X_test, Y_test)))


	title = "GaussianNB"
	cv = ShuffleSplit(n_splits=100, test_size=0.2, random_state=0)
	estimator = GaussianNB()

	plot_learning_curve(estimator, title, X_train, Y_train, cv=cv)
	plt.show()

	filler_feature_values = {}
	for i in range(2, X_train.shape[1]):
		filler_feature_values[i] = 2

	plot_decision_regions(X_train, Y_train, clf=clf, filler_feature_values=filler_feature_values)
	plt.show()
	'''