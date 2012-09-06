#ifndef PANEMESSAGE_HPP_
#define PANEMESSAGE_HPP_
#include "../../../../DataStruct/MemberData.hpp"
#include <wx/wxprec.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>
#include <vector>
#include <wx/notebook.h>
#include <map>
#include <wx/panel.h>
#include "../../../Service/NickTable.hpp"
#include "LogTextCtrl.hpp"
#include "PaneMsg.hpp"
#include "../../../Service/Filter/AllFilter.hpp"

namespace CornStarch
{
class CPaneMessage : public wxNotebook
{
    // 「全て表示」用ペイン
    CPaneMsg* m_allLogCtrl;
    // 「全て表示」用フィルター
    CAllFilter* m_allFilter;
    // すべての表示用ペインを保持
    vector<CPaneMsg*> m_messagePanels;
    // タブの作成
    CPaneMsg* createTab(const IFilter* filter, const CServiceConfiguration* configuration);
public:
    CPaneMessage();
    virtual ~CPaneMessage();
    // 初期化
    void init(wxWindow* parent);
    // メッセージの表示
    void displayMessages(const std::vector<CMessage*>& messages,
        const CNickTable& nickTable,const wxString& channelName,const CServiceConfiguration* configuration);
    // 文字のクリア
    void clear();
    // メッセージの追加
    void pushLog(const CMessage* message);
    // 背景のクリア
    void clearUnreadBackgroundColor();
};

} /* namespace CornStarch */
#endif /* PANEMESSAGE_HPP_ */
