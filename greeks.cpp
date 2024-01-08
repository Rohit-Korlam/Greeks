#include "greeks.hpp"
double normalCdf(double x){
    return std::erfc(-x / std::sqrt(2)) / 2;
}
double Greeks::computeOptionPrice(double spot_price, double sigma)
{
    double time_expiry = this->getTimeToExpiryInYears();
    double d1 = (log((spot_price)/(this->contract_desc.strike_price)) + (interest_rate + ((sigma*sigma)/2))*time_expiry)/(sigma*sqrt(time_expiry));
    double d2 = d1 - sigma*sqrt(time_expiry);
    if(this->opt_type==OPTION_TYPE::EUROPEAN_CALL)
        return normalCdf(d1)*(spot_price) - normalCdf(d2)*this->contract_desc.strike_price*exp(-interest_rate*time_expiry);
    else
        return (this->contract_desc.strike_price)*exp(-interest_rate*time_expiry)*normalCdf(-d2) - spot_price*normalCdf(-d1);
}
double Greeks::getTimeToExpiryInYears()
{
    auto current_time = std::chrono::system_clock::now();
    auto time_expiry = this->contract_desc.expiry;
    std::chrono::duration<double> difference = time_expiry - current_time;
    return (difference)/(365*24*60*60);
}
double Greeks::computeBsmIVOfOption(double spot_price,double current_market_price)
{
    double strike_price = this->contract_desc.strike_price;
    double time_expiry = this->getTimeToExpiryInYears();
    double epsilon = 0.001;
    double sigma = 0.1;
    double option_price = computeOptionPrice(spot_price,sigma);
    int iterations = 0;
    const int MAX_ITERATIONS = 100;
    while(abs(option_price - current_market_price) > epsilon && iterations <= MAX_ITERATIONS){
        double d1 = (log((spot_price)/(this->contract_desc.strike_price)) + (interest_rate + ((sigma*sigma)/2))*time_expiry)/(sigma*sqrt(time_expiry));
        double vega = exp(-(d1*d1)/2)/(sqrt(2*M_PI));
        double difference = current_market_price - option_price;
        sigma = sigma - (difference)/vega;
        option_price = computeOptionPrice(spot_price,sigma);
        iterations += 1;
    }
    return sigma;

}

