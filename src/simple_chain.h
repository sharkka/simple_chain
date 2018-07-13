#ifndef __SIMPLE_CHAIN_H_
#define __SIMPLE_CHAIN_H_

#include <vector>
#include <string>


using StlString = std::string;

typedef struct _deal_proof {
    int32_t     type;
    float       sum;
    float       tradeSum;
    StlString   hashOldProof;
    StlString   hashNewProof;
    int32_t     blockId;
    int32_t     token;
    uint32_t    tradeTime;
    StlString   username;
    StlString   password;
} deal_proof;

class simple_trade {
public:
    int trade(StlString username, StlString password, float tradeSum);
    int update();
    int commit();
    int rollback();
    int pullBlock();
    int pushBlock();
private:
    deal_proof proof_;
};




















#endif


