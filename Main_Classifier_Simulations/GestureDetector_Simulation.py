from DataGetter import TestDataGetter
from LDA_PCA_FA_Simulation import DimensionReduction
from Plotter import plot_gst_detector_2D

def main():
    # Get Data
    data_getter = TestDataGetter(5, 4)
    X = data_getter.get_x_data(False)
    y = data_getter.get_y_data(False)

    # Dimensionality Reduction
    dimred = DimensionReduction(X, y)
    X_lda_2d = dimred.lda_2D_data()

    # Draw Graphs
    plot_gst_detector_2D(X_lda_2d, y, '2D-LDA of Gestures Detector')

if __name__ == "__main__":
    # stuff only to run when not called via 'import' here
    main()