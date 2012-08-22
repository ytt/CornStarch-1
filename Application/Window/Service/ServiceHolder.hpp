#ifndef SERVICEHOLDER_HPP_
#define SERVICEHOLDER_HPP_
#include <map>
#include "ChatServiceBase.hpp"
#include "wx/wx.h"

using namespace std;

namespace CornStarch
{

class CServiceHolder
{
    int m_uniqueServiceId;
    int m_currentServiceId;
    map<int, CChatServiceBase*> m_services;

public:
    CServiceHolder();
    virtual ~CServiceHolder();
    void deleteService(int serviceId);
    void deleteChannel(int serviceId, wxString channel);
    void addNewService(CChatServiceBase* service, wxEvtHandler* hander);

    CChatServiceBase* getService(int serviceId) const;

    map<int, CChatServiceBase*> getServices() const
    {
        return m_services;
    }

    int getCurrentServiceId() const
    {
        return m_currentServiceId;
    }

    void setCurrentServiceId(int currentServiceId)
    {
        m_currentServiceId = currentServiceId;
    }

    int getUniqueServiceId() const
    {
        return m_uniqueServiceId;
    }

    void setUniqueServiceId(int uniqueServiceId)
    {
        m_uniqueServiceId = uniqueServiceId;
    }

    void load(wxEvtHandler* handler);
    void save();
};

} /* namespace CornStarch */
#endif /* SERVICEHOLDER_HPP_ */
