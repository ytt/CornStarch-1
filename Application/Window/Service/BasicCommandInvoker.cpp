#include "BasicCommandInvoker.hpp"

namespace CornStarch
{

const wxString CBasicCommandInvoker::JOIN = "/join ";
const wxString CBasicCommandInvoker::PART = "/part";
const wxString CBasicCommandInvoker::TOPIC = "/topic ";
const wxString CBasicCommandInvoker::NICK = "/nick ";
using namespace std;

CBasicCommandInvoker::CBasicCommandInvoker(CChatServiceBase* service)
{
    m_service= service;
}

CBasicCommandInvoker::~CBasicCommandInvoker()
{

}
bool CBasicCommandInvoker::invoke(const wxString& text)
{
    if (text.StartsWith(CBasicCommandInvoker::JOIN)){
        wxString channle = text;
        wxString argument = channle.Remove(0,
                CBasicCommandInvoker::JOIN.size());
        m_service->joinChannel(argument);
        return true;
    } else if (text.StartsWith(CBasicCommandInvoker::TOPIC)){
        wxString channle = text;
        wxString argument = channle.Remove(0,
                CBasicCommandInvoker::TOPIC.size());
        m_service->onChangeTopic(argument);
        return true;
    } else if (text.StartsWith(CBasicCommandInvoker::NICK)){
        wxString channle = text;
        wxString argument = channle.Remove(0,
                CBasicCommandInvoker::NICK.size());
        m_service->onNickChange(argument);
        return true;
    } else if (text.StartsWith(CBasicCommandInvoker::PART)){
        wxString argument = m_service->getCurrentChannel();
        m_service->partChannel(argument);
        return true;
    }
    return false;
}
vector<wxString> CBasicCommandInvoker::getCommandList()
{
    vector<wxString> vector;
    return vector;
}

} /* namespace CornStarch */
