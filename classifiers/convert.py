#!/usr/bin/env python

import os
import sys

import data_getter
import gnb

from string import Template

from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.decomposition import FactorAnalysis

BASE_DIR = os.path.join(os.path.dirname(__file__), '../')

SRC_DIR = BASE_DIR + 'flashing-jacket/src/'
TEST_DIR = BASE_DIR + 'test/'

CLASSIFIERS_DIR = SRC_DIR + 'classifiers/'
TEMPLATE_DIR = CLASSIFIERS_DIR + 'templates/'

TEST_CLASSIFIERS_DIR = TEST_DIR + 'classifiers/'
TEST_TEMPLATE_DIR = TEST_CLASSIFIERS_DIR + 'templates/'


def fill_template(values, template_path, target_path):
    src = open(template_path)
    tmp = Template(src.read())
    tmp = tmp.substitute(values)
          
    target = open(target_path, 'w')
    target.write(tmp)
    target.close()




def get_lda_template_values(lda, prefix=""):
    return {
        prefix + 'CLASSES'    : lda.classes_.shape[0],
        prefix + 'DIMENSIONS' : lda.n_components,
        prefix + 'FEATURES'   : lda.xbar_.shape[0],
        prefix + 'XBAR'       : '{' + ', '.join(map(str, lda.xbar_)) + '}',
        prefix + 'SCALINGS'   : '{' + ', '.join(['{' + ', '.join(map(str, x[:lda.n_components])) + '}' for x in lda.scalings_]) + '}',
    }


def get_gnb_template_values(clf, prefix=""):
    return {
        prefix + 'GNB_CLASS_PRIOR': '{' + ', '.join(map(str, clf.class_prior_)) + '}',
        prefix + 'GNB_MEANS'      : '{' + ', '.join(['{' + ', '.join(map(str, x)) + '}' for x in clf.theta_.tolist()]) + '}',
        prefix + 'GNB_STDEVS'     : '{' + ', '.join(['{' + ', '.join(map(str, x)) + '}' for x in clf.sigma_.tolist()]) + '}',
    }

    


def fill_classifier_template(dr, clf, template_path, target_path, prefix=""):
    values = {}
    values.update(get_gnb_template_values(clf, prefix=prefix))
    values.update(get_lda_template_values(dr, prefix=prefix))
    fill_template(values, template_path, target_path)


def fill_test_template(X, y_predicted, template_path, target_path):
    nb_tests = X.shape[0];

    values = {
        'NB_FEATURES'      : X.shape[1],
        'NB_TEST_POINTS'   : nb_tests,
        'TEST_POINTS'      : '{' + ', '.join(['{' + ', '.join(map(str, x)) + '}' for x in X[:nb_tests, :]]) + '}',
        'TEST_PREDICTIONS' : '{' + ', '.join(map(str, y_predicted[:nb_tests])) + '}',
    }

    fill_template(values, template_path, target_path)


def main():
    getter = data_getter.TestDataGetter(5, 4)
    X = getter.get_x_data()
    y = getter.get_y_data()
    main_dr, main_gnb = gnb.best_gnb(X, y)

    if type(main_dr) is not LinearDiscriminantAnalysis:
        print("PCA NOT SUPPORTED")
        return

    getter = data_getter.TestDataGetter(5, 4)
    X = getter.get_x_data()
    y = getter.get_y_data()
    gesture_dr, gesture_gnb = gnb.best_gnb(X, y)

    fill_classifier_template(main_dr, main_gnb, TEMPLATE_DIR + 'main_parameters.txt', CLASSIFIERS_DIR + 'main_parameters.h', "MAIN_")
    fill_classifier_template(gesture_dr, gesture_gnb, TEMPLATE_DIR + 'gesture_parameters.txt', CLASSIFIERS_DIR + 'gesture_parameters.h', "GESTURE_")

    fill_test_template(X, main_gnb.predict(main_dr.transform(X)), TEST_TEMPLATE_DIR + 'test_points.txt', TEST_CLASSIFIERS_DIR + 'test_points.h')

if __name__ == "__main__":
  sys.exit(main())
