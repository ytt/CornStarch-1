#include "InputManager.hpp"
using namespace std;
namespace CornStarch
{

CInputManager::CInputManager() :
        m_predicateFirstInput("")
{

}

CInputManager::~CInputManager()
{

}
wxString CInputManager::getAutoCompletionText(const wxString& content,
        const CChatServiceBase* service)
{
    if (content.find("/") != 0 && content.find(" ") != wxString::npos){
        // コマンドでない＆＆スペースを含む場合は、スペース以降で入力補助
        int index = content.rfind(" ");
        wxString preText = content.substr(0,index);
        wxString targetText = content.substr(index + 1);
        wxString result = getNextInputCandidate(targetText, service);

        return wxString::Format(wxT("%s %s") ,preText, result);
    } else{
        return getNextInputCandidate(content, service);
    }
}
// 現在の入力から次の候補を取得
wxString CInputManager::getNextInputCandidate(const wxString& currentInput,
        const CChatServiceBase* service)
{
    vector<wxString> candidates;
    if (currentInput.find("/") == 0){
        // コマンドの取得
        candidates = service->getCommandInvoker()->getCommandList();
    } else{
        // 参加者の取得
        wxString channelName = service->getCurrentChannel();
        CChannelStatus* channel = service->getChannel(channelName);
        vector<CMemberData*> members = channel->getMembers();
        vector<wxString> memberNames;
        vector<CMemberData*>::iterator it = members.begin();
        while (it != members.end()){
            memberNames.push_back((*it)->m_nick + ":");
            it++;
        }
        candidates = memberNames;
    }
    // 完全一致のものがある場合は、初期入力に合う、その次の候補を探す。
    wxString result = getNextCandidate(currentInput, candidates,
            m_predicateFirstInput);
    if (result != ""){
        return result;
    }
    // 初期入力の値を保存。
    m_predicateFirstInput = currentInput;
    // 候補を探す。
    result = getCandidate(currentInput, candidates);
    if (result != ""){
        return result;
    }
    return currentInput;
}
// 入力履歴を追加
void CInputManager::addHistory(const wxString& content)
{
    m_inputHistory.push_back(content);
    if (m_inputHistory.size() > 10){
        vector<wxString>::iterator it = m_inputHistory.begin();
        m_inputHistory.erase(it);
    }
}
// 入力履歴を取得
wxString CInputManager::getCandidate(const wxString& currentInput,
        vector<wxString>& items)
{
    for (int i = 0; i < (int) items.size(); i++){
        if (items[items.size() - i - 1].find(currentInput) == 0){
            return items[items.size() - i - 1];
        }
    }
    return "";
}
// 現在の入力値と条件値から次の候補を取得
wxString CInputManager::getNextCandidate(const wxString& currentInput,
        vector<wxString>& items, const wxString& predicte)
{
    bool isFoundCurrentInput = false;
    for (int i = 0; i < (int) items.size(); i++){
        wxString value = items[items.size() - i - 1];
        if (isFoundCurrentInput){
            if (predicte == "" || value.find(predicte) == 0){
                return value;
            }
        }
        if (value == currentInput){
            isFoundCurrentInput = true;
        }
    }
    return "";
}
// 履歴の取得
wxString CInputManager::getHistory(const wxString& currentInput)
{
    if (m_inputHistory.size() > 0){
        wxString content = getNextCandidate(currentInput, m_inputHistory, "");
        if (content != ""){
            return content;
        }
        return m_inputHistory[m_inputHistory.size() - 1];
    }
    return currentInput;
}

} /* namespace CornStarch */
