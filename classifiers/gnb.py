from data_getter import TestDataGetter

from sklearn.model_selection import train_test_split

from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.decomposition import FactorAnalysis

from sklearn.naive_bayes import GaussianNB

import numpy as np

MAX_COMPONENTS = 20

def gnb(X, y):
    return GaussianNB().fit(X, y)


def gnb_with_dr(dr, X, y):
    X_reduced = dr.transform(X)
    return gnb(X_reduced, y)


def test_dr(dr, X, y):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
    X_reduced_train = dr.transform(X_train)
    X_reduced_test = dr.transform(X_test)
    return gnb(X_reduced_train, y_train).score(X_reduced_test, y_test)



def best_lda(X, y):
    best_dr = None
    best_score = 0

    for i in range(1, np.unique(y).shape[0]):
        dr = LinearDiscriminantAnalysis(n_components=i).fit(X, y)
        score = test_dr(dr, X, y)
        print("LDA dim=%d score=%.2f" % (i, score))
        
        if score > best_score:
            best_score = score
            best_dr = dr

    return best_dr, best_score

def best_pca(X, y):
    best_dr = None
    best_score = 0

    for i in range(1, min(X.shape[1], MAX_COMPONENTS)):
        dr = PCA(n_components=i).fit(X)
        score = test_dr(dr, X, y)
        print("PCA dim=%d score=%.2f" % (i, score))
        
        if score > best_score:
            best_score = score
            best_dr = dr

    return best_dr, best_score

def best_fa(X, y):
    best_dr = None
    best_score = 0

    for i in range(1, min(X.shape[1], MAX_COMPONENTS)):
        dr = FactorAnalysis(n_components=i).fit(X, y)
        score = test_dr(dr, X, y)
        print("FA dim=%d score=%.2f" % (i, score))
        
        if score > best_score:
            best_score = score
            best_dr = dr

    return best_dr, best_score


def best_dr(X, y):
    best_dr = None
    best_score = -1
    
    dr, score = best_lda(X, y)
    if score > best_score:
        best_score = score
        best_dr = dr

    # dr, score = best_pca(X, y)
    # if score > best_score:
    #     best_score = score
    #     best_dr = dr

    # dr, score = best_fa(X, y)
    # if score > best_score:
    #     best_score = score
    #     best_dr = dr

    print("BEST DR: type=%s dim=%d score=%.2f" % (type(best_dr), best_dr.n_components, best_score))

    return best_dr


def best_gnb(X, y):
    dr = best_dr(X, y)
    return dr, gnb_with_dr(dr, X, y)


if __name__ == "__main__":
    data_getter = TestDataGetter(10, 9)
    X = data_getter.get_x_data("gesture")
    y = data_getter.get_y_data("gesture")
    gesture_dr, gesture_gnb = best_gnb(X, y)

    data_getter = TestDataGetter(10, 9)
    X = data_getter.get_x_data("mode")
    y = data_getter.get_y_data("mode")
    mode_dr, mode_gnb = best_gnb(X, y)

    data_getter = TestDataGetter(10, 9)
    X = data_getter.get_x_data("signal")
    y = data_getter.get_y_data("signal")
    signal_dr, signal_gnb = best_gnb(X, y)