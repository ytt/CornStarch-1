

#ifndef ALLFILTER_HPP_
#define ALLFILTER_HPP_

#include "FilterBase.hpp"
namespace CornStarch
{
// 全てを通すフィルタ
class CAllFilter:public CFilterBase
{
public:
    CAllFilter();
    virtual ~CAllFilter();
    bool isValid(const CMessage* message)const;
};

} /* namespace CornStarch */
#endif /* ALLFILTER_HPP_ */
