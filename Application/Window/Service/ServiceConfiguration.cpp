#include "ServiceConfiguration.hpp"
#include "Filter/AllFilter.hpp"
#include "Filter/MessageTypeFilter.hpp"
#include "Message/ChatMessage.hpp"

using namespace std;
namespace CornStarch
{

CServiceConfiguration::CServiceConfiguration() :
        m_fontSize(12), m_isAutoConnect(true)
{

}

CServiceConfiguration::~CServiceConfiguration()
{
    map<wxString, vector<IFilter*> >::iterator it = m_filters.begin();
    while (it != m_filters.end()){
        int size = (int) (*it).second.size();
        for (int i = 0; i < size; i++){
            delete (*it).second[i];
        }
        ++it;
    }
}
void CServiceConfiguration::addDefaultFilter(const wxString& channelName)
{
    map<wxString, vector<IFilter*> >::const_iterator it = m_filters.find(
            channelName);
    if (it == m_filters.end()){
        vector<IFilter*> filters;

        CMessageTypeFilter* filterChat = new CMessageTypeFilter();
        filterChat->setName("Chat");
        filterChat->setTypeInfoName(wxString(typeid (CChatMessage).name()));
        filters.push_back(filterChat);

        CMessageTypeFilter* filterSystem = new CMessageTypeFilter();
        filterSystem->setName("System");
        filterSystem->setTypeInfoName(wxString(typeid (CChatMessage).name()));
        filterSystem->setAntiFilter(true);
        filters.push_back(filterSystem);

        m_filters.insert(
                map<wxString, vector<IFilter*> >::value_type(channelName,
                        filters));
    }
}
} /* namespace CornStarch */
