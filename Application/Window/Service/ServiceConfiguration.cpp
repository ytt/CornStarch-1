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
    map<wxString, vector<IFilter*>*>::iterator it = m_filters.begin();
    while (it != m_filters.end()){
        int size = (int) (*it).second->size();
        for (int i = 0; i < size; i++){
            delete (*(*it).second)[i];
        }
        delete (*it).second;
        ++it;
    }
}
void CServiceConfiguration::addDefaultFilter(const wxString& channelName)
{
    map<wxString, vector<IFilter*>*>::const_iterator it = m_filters.find(
            channelName);
    if (it == m_filters.end()){
        vector<IFilter*>* filters = new vector<IFilter*>();

        CMessageTypeFilter* filterChat = new CMessageTypeFilter();
        filterChat->setName("Chat");
        filterChat->setTypeInfoName(wxString(typeid(CChatMessage).name()));
        filters->push_back(filterChat);

        CMessageTypeFilter* filterSystem = new CMessageTypeFilter();
        filterSystem->setName("System");
        filterSystem->setTypeInfoName(wxString(typeid(CChatMessage).name()));
        filterSystem->setAntiFilter(true);
        filters->push_back(filterSystem);

        m_filters.insert(
                map<wxString, vector<IFilter*>*>::value_type(channelName,
                        filters));
    }
}

void CServiceConfiguration::addFilter(const wxString& channelName,
        IFilter* filter)
{
    map<wxString, vector<IFilter*>*>::const_iterator it = m_filters.find(
            channelName);
    if (it != m_filters.end()){
        vector<IFilter*>* filtesrs = (*it).second;
        filtesrs->push_back(filter);
    } else{
        vector<IFilter*>* filters = new vector<IFilter*>();
        filters->push_back(filter);
        m_filters.insert(
                map<wxString, vector<IFilter*>*>::value_type(channelName,
                        filters));
    }
}
void CServiceConfiguration::removeFilter(const wxString& channelName,
        const wxString filterName)
{
    map<wxString, vector<IFilter*>*>::const_iterator it = m_filters.find(
            channelName);
    if (it != m_filters.end()){
        vector<IFilter*>::iterator itFilter = (*it).second->begin();
        while (itFilter != (*it).second->end()){
            if ((*itFilter)->getName() == filterName){
                delete (*itFilter);
                (*it).second->erase(itFilter);
                break;
            }
            itFilter++;
        }
    }
}
} /* namespace CornStarch */
