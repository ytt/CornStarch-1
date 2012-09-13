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
    // テキストを変更中華
    bool m_isChangingText;
    // 現在入力中
    wxString m_currentInput;
    // 履歴の順位
    int m_historyIndex;
    // 入力補助しはじめた文字
    wxString m_predicateFirstInput;
    // 入力履歴
    vector<wxString> m_inputHistory;
    // 次の候補の取得
    wxString getNextCandidate(const wxString& currentInput,
            vector<wxString>& items, const wxString& predicte, bool canLoop);
    // 候補の取得
    wxString getCandidate(const wxString& currentInput,
            vector<wxString>& items);
    // 現在の入力からの次の候補の取得
    wxString getNextInputCandidate(const wxString& currentInput,
            const CChatServiceBase* service,const vector<wxString>& commands);
public:
    CInputManager();
    virtual ~CInputManager();

    // 入力補助の取得
    wxString getAutoCompletionText(const wxString& content,
            const CChatServiceBase* service,const vector<wxString>& commands);
    // 履歴の追加
    void addHistory(const wxString& content);
    // 履歴の取得
    wxString getHistory();
    // 一つ前の履歴の取得
    wxString getHistoryBefore();
    // 履歴取得位置のリセット
    void resetIndex();
    // 現在の入力文字の設定
    void setCurrentInput(wxString value);
	// 現在の入力文字の取得
	wxString getCurrentInput() const;
    bool isChangingText() const
    {
        return m_isChangingText;
    }

    void setChangingText(bool isChangingText)
    {
        m_isChangingText = isChangingText;
    }
};

} /* namespace CornStarch */
#endif /* INPUTMANAGER_HPP_ */
