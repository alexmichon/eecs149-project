#ifndef LDA_PARAMETERS_H
#define LDA_PARAMETERS_H

#define LDA_CLASSES 3
#define LDA_FEATURES 30
#define LDA_DIMENSIONS 2

const float LDA_XBAR[LDA_FEATURES] = {-1.63515717092, -1.05606090373, 7.27114931238, 22.3579862475, 2.54654223969, 41.1679764244, -1.44188605108, -1.0695481336, 7.27836935167, -10.9757662083, 2.2547151277, -3.33029469548, -1.38190569745, -1.07304518664, 7.38709233792, -10.4968369352, -4.6494302554, -5.30961689587, -1.43654223969, -0.969616895874, 7.2825540275, -9.22150294695, -10.0430058939, -8.13148330059, -1.57942043222, -0.823546168959, 7.13041257367, -4.74652259332, -20.133388998, -14.9731237721};
const float LDA_SCALINGS[LDA_FEATURES][LDA_DIMENSIONS] = {{0.0333473186893, -0.0147809341514}, {-0.306977566629, -0.0934075136154}, {-0.0217542086758, 0.199474970812}, {-0.00287406244647, -6.29922879275e-05}, {0.000694294472764, 0.00619183274411}, {0.0029403020188, 0.00121154066759}, {0.0758110586675, -0.0191040594657}, {-0.16191406888, 0.0898609476338}, {-0.0387327565717, 0.123678738614}, {-0.000179669829279, 2.94134993428e-05}, {-0.0015529750056, -0.00163159881085}, {-0.00213828285377, -0.00156052125361}, {-0.0819107415463, -0.0681331248706}, {-0.0751769928404, 0.0972095207758}, {0.0149509137742, 0.0495385852027}, {0.00362224078666, -0.000652545286057}, {0.000700275670263, 0.000302695721773}, {0.00115099342291, 0.000525713584899}, {0.0190539857244, 0.00980767010338}, {-0.0647708374685, 0.0676885948513}, {0.0247283628694, 0.0272905838485}, {0.00279082495551, -0.00553826782931}, {0.000315111870475, 0.000580915376095}, {0.000531797900571, 0.00265318192021}, {0.042479308571, -0.0814684628565}, {-0.0570045094664, -0.271782242486}, {-0.00864748772866, 0.208901824208}, {0.00760098967116, 0.000434992243437}, {-0.00166661803148, -0.00577669931446}, {-8.47600131363e-05, -0.00206173660223}};

#endif