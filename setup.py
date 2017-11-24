#!/usr/bin/env python

import os
import sys
#sys.path.append(os.path.abspath('Main_Classifier_Simulations'))

from Main_Classifier_Simulations import GaussianNaiveBayes_Simulation, LDA_PCA_FA_Simulation

from string import Template

SRC_DIR = 'flashing-jacket/src/'
TEST_DIR = 'flashing-jacket/test/'


def fill_lda_template():
    lda = LDA_PCA_FA_Simulation.get_LDA(only_gst_data=True)

    values = {
        'LDA_CLASSES'    : lda.classes_.shape[0],
        'LDA_DIMENSIONS' : lda.n_components,
        'LDA_FEATURES'   : lda.xbar_.shape[0],
        'LDA_XBAR'       : '{' + ', '.join(map(str, lda.xbar_)) + '}',
        'LDA_SCALINGS'   : '{' + ', '.join(['{' + ', '.join(map(str, x[:lda.n_components])) + '}' for x in lda.scalings_]) + '}',
    }

    filein = open(SRC_DIR + 'templates/LDA_Parameters.txt')
    tmp = Template(filein.read())
    tmp = tmp.substitute(values)
          
    src = open(SRC_DIR + 'LDA_Parameters.h', 'w')
    src.write(tmp)
    src.close()


def fill_gaussian_template():
    gnb = GaussianNaiveBayes_Simulation.get_GNB(only_gst_data=True)

    values = {
        'GNB_CLASS_PRIOR': '{' + ', '.join(map(str, gnb.class_prior_)) + '}',
        'GNB_MEANS'      : '{' + ', '.join(['{' + ', '.join(map(str, x)) + '}' for x in gnb.theta_.tolist()]) + '}',
        'GNB_STDEVS'     : '{' + ', '.join(['{' + ', '.join(map(str, x)) + '}' for x in gnb.sigma_.tolist()]) + '}',
    }

    filein = open(SRC_DIR + 'templates/GaussianNB_Parameters.txt')
    tmp = Template(filein.read())
    tmp = tmp.substitute(values)
          
    src = open(SRC_DIR + 'GaussianNB_Parameters.h', 'w')
    src.write(tmp)
    src.close()


def fill_test_template():
    points, predictions = GaussianNaiveBayes_Simulation.get_GNB_test_points(only_gst_data=True)

    nb_tests = points.shape[0];

    values = {
        'NB_TEST_POINTS'   : nb_tests,
        'TEST_POINTS'      : '{' + ', '.join(['{' + ', '.join(map(str, x)) + '}' for x in points[:nb_tests, :]]) + '}',
        'TEST_PREDICTIONS' : '{' + ', '.join(map(str, predictions[:nb_tests])) + '}',
    }

    filein = open(TEST_DIR + 'templates/test_points.txt')
    tmp = Template(filein.read())
    tmp = tmp.substitute(values)
          
    src = open(TEST_DIR + 'test_points.h', 'w')
    src.write(tmp)
    src.close()


def main():
    fill_gaussian_template()
    fill_lda_template()
    fill_test_template()

if __name__ == "__main__":
  sys.exit(main())
