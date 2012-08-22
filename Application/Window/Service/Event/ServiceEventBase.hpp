

#ifndef MESSAGEEVENT_HPP_
#define MESSAGEEVENT_HPP_
#include "../../LogHolder/ServiceLog.hpp"
#include "ConnectionEventBase.hpp"

namespace CornStarch
{

class CServiceEventBase:public CConnectionEventBase
{
    CServiceLog* serviceLog;
public:
    CServiceEventBase();
    virtual ~CServiceEventBase();

    CServiceLog* getServiceLog() const
    {
        return serviceLog;
    }

    void setServiceLog(CServiceLog* serviceLog)
    {
        this->serviceLog = serviceLog;
    }
};

} /* namespace CornStarch */
#endif /* MESSAGEEVENT_HPP_ */
