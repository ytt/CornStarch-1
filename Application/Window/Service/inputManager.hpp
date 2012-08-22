#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#include <vector>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "ChatServiceBase.hpp"
using namespace std;
namespace CornStarch
{

class CInputManager
{
    wxString m_predicateFirstInput;
    vector<wxString> m_inputHistory;
    wxString getNextCandidate(const wxString& currentInput,
            vector<wxString>& items, const wxString& predicte);
    wxString getCandidate(const wxString& currentInput,
            vector<wxString>& items);
    wxString getNextInputCandidate(const wxString& currentInput,
            const CChatServiceBase* service,const vector<wxString>& commands);
public:
    CInputManager();
    virtual ~CInputManager();

    wxString getAutoCompletionText(const wxString& content,
            const CChatServiceBase* service,const vector<wxString>& commands);
    void addHistory(const wxString& content);
    wxString getHistory(const wxString& currentInput);
};

} /* namespace CornStarch */
#endif /* INPUTMANAGER_HPP_ */
