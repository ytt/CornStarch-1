#ifndef SCEVENTFACTORY_HPP_
#define SCEVENTFACTORY_HPP_
#include "../Event/ConnectionEventBase.hpp"
#include "SCMessageData.hpp"
namespace CornStarch
{
namespace StarChat
{
class CSCEventFactory
{
    int m_connectionId;
public:
    CSCEventFactory();
    virtual ~CSCEventFactory();

    CConnectionEventBase* Create(CSCMessageData message);

    int getConnectionId() const
    {
        return m_connectionId;
    }

    void setConnectionId(int connectionId)
    {
        m_connectionId = connectionId;
    }

};
}
}
#endif /* SCEVENTFACTORY_HPP_ */
