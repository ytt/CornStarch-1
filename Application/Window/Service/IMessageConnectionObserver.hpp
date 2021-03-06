#ifndef IMESSAGEOBSERVER_HPP_
#define IMESSAGEOBSERVER_HPP_
#include "../../DataStruct/ResponseData.hpp"

namespace CornStarch
{
;

class IMessageConnectionObserver
{
public:
    IMessageConnectionObserver()
    {
    }

    virtual ~IMessageConnectionObserver()
    {
    }
    virtual void onCheckServiceStatus()=0;
    virtual void onMessageReceived(CResponseData* message) = 0;
    virtual void onDisconnected() = 0;
    virtual void onConnected() = 0;
    virtual void onConnectionFailed() = 0;
};
}

#endif /* IMESSAGEOBSERVER_HPP_ */
