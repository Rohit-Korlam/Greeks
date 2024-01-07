#include <iostream>
#include <string>
enum INSTRUMENT {
    STK_IDX,
    FUT_IDX,
    OPT_IDX
};
enum OPTION_TYPE{
    EUROPEAN_CALL,
    EUROPEAN_PUT,
    AMERICAN_CALL,
    AMERICAN_PUT
};
struct CONTRACT_DESC{
    std::string underlying;
    uint32_t strike_price;
    double expiry;
    uint32_t lot_size;
};
class ProductInfo {
    public:
        ProductInfo():{};
        bool isProductFuture(){
            return this->inst_type == INSTRUMENT::FUT_IDX;
        }
        bool isProductOption(){
            return this->inst_type == INSTRUMENT::OPT_IDX;
        }
    public:
    int32_t token;
    INSTRUMENT inst_type;
    OPTION_TYPE opt_type;
    CONTRACT_DESC contract_desc;
};