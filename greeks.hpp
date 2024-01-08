#pragma once
#include "ProductInfo.hpp"
#include <cmath>
class Greeks:public ProductInfo{
    public:
    double computeBsmIVOfOption(double spot_price,double market_price);
    double computeOptionPrice(double spot_price, double sigma);
    double getTimeToExpiryInYears();
    double computeDelta();
    double computeGamma();
    double computeVega();
    double computeTheta();
    double interest_rate;
};