#ifndef __SIMPLE_CHAIN_H_
#define __SIMPLE_CHAIN_H_

#include <vector>
#include <string>


using StlString = std::string;
/**
 * @Brief    proof
 * @Class    deal_proof
 * @DateTime 2018-07-16T17:28:23+0800
 * @Modify   2018-07-16T17:28:23+0800
 * @Author   Anyz
 * @Keyword
 */
typedef struct _deal_proof {
    int32_t     type;
    float       sum;
    float       tradeSum;
    StlString   hashPrevProof;
    StlString   hashCurrProof;
    StlString   hashNextProof;
    int32_t     blockId;
    int32_t     token;
    uint32_t    tradeTime;
    StlString   username;
    StlString   password;
} deal_proof;
/**
 * @Brief    trade process
 * @Class    simple_trade
 * @DateTime 2018-07-16T17:28:23+0800
 * @Modify   2018-07-16T17:28:23+0800
 * @Author   Anyz
 * @Keyword
 */
class simple_trade {
public:
    simple_trade();
    ~simple_trade();
    int        trade(StlString username, StlString password, float tradeSum);
    int        commit();
    int        rollback();
    int        pullBlock();
    int        pushBlock();
    int        query();
    int        log();
private:
    deal_proof proof_;
};
/**
 * @Brief    chain database, simplest as local file
 * @Method   filedb
 * @DateTime 2018-07-16T17:28:23+0800
 * @Modify   2018-07-16T17:28:23+0800
 * @Author   Anyz
 * @Keyword
 */
class filedb {
public:
    filedb();
    ~filedb();
    int        insert(deal_proof dp);
    int        query();
    int64_t    count();
private:
    deal_proof dp_;
    int        dbId_;
    int        partitionId_;
};


















#endif


