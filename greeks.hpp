#pragma once
#include "ProductInfo.hpp"
class Greeks:public ProductInfo{
    public:
    double computeBSMPriceOfOption(double market_price);
    double computeIV();
    double computeDelta();
    double computeGamma();
    double computeVega();
    double computeTheta();
};