

#ifndef IFILTER_HPP_
#define IFILTER_HPP_
#include "../Message/Message.hpp"

namespace CornStarch
{

class IFilter
{
public:
    IFilter(){};
    virtual ~IFilter(){};
    virtual bool isValid(const CMessage* message) const = 0;
};

} /* namespace CornStarch */
#endif /* IFILTER_HPP_ */
