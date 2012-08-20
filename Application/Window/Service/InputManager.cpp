#include "InputManager.hpp"
using namespace std;
namespace CornStarch
{

CInputManager::CInputManager() :
        m_currentInput("")
{

}

CInputManager::~CInputManager()
{

}

wxString CInputManager::getNextInputCandidate(const wxString& currentInput,
        const CChatServiceBase* service)
{
    vector<wxString> candidates;
    if (currentInput.find("/") == 0){
        candidates = service->getCommandInvoker()->getCommandList();

    } else{
        wxString channelName = service->getCurrentChannel();
        CChannelStatus* channel = service->getChannel(channelName);
        vector<CMemberData*> members = channel->getMembers();
        vector<wxString> memberNames;
        vector<CMemberData*>::iterator it = members.begin();
        while (it != members.end()){
            memberNames.push_back((*it)->m_nick + ": ");
            it++;
        }
        candidates = memberNames;
    }
    wxString result = getNextCandidate(currentInput, candidates,
            m_currentInput);
    if (result != ""){
        return result;
    }
    m_currentInput = currentInput;
    result = getCandidate(currentInput, candidates);
    if (result != ""){
        return result;
    }
    return currentInput;
}
void CInputManager::addHistory(const wxString& content)
{
    m_inputHistory.push_back(content);
    if (m_inputHistory.size() > 10){
        vector<wxString>::iterator it = m_inputHistory.begin();
        m_inputHistory.erase(it);
    }
}
wxString CInputManager::getCandidate(const wxString& currentInput,
        vector<wxString>& items)
{
    for (int i = 0; i < (int)items.size(); i++){
        if (items[items.size() - i - 1].find(currentInput) == 0){
            return items[items.size() - i - 1];
        }
    }
    return "";
}
wxString CInputManager::getNextCandidate(const wxString& currentInput,
        vector<wxString>& items, const wxString& predicte)
{
    bool isFoundCurrentInput = false;
    for (int i = 0; i < (int)items.size(); i++){
        wxString value = items[items.size() - i - 1];
        if (isFoundCurrentInput){
            if (predicte== ""||value.find(predicte) == 0){
                return value;
            }
        }
        if (value == currentInput){
            isFoundCurrentInput = true;
        }
    }
    return "";
}
wxString CInputManager::getHistory(const wxString& currentInput)
{
    if (m_inputHistory.size() > 0){
        wxString content = getNextCandidate(currentInput, m_inputHistory,"");
        if (content != ""){
            return content;
        }
        return m_inputHistory[m_inputHistory.size() - 1];
    }
    return currentInput;
}

} /* namespace CornStarch */
