#pragma once
#include "../../../Service/ChatServiceBase.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/treectrl.h>
#include "ChannelSelectEvent.hpp"
#include "TreeServerItem.hpp"
#include <map>

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_SELECT_TREE_NODE_RIGHT, CChannelSelectEvent);
wxDECLARE_EVENT(myEVT_SELECT_TREE_NODE, CChannelSelectEvent);

class CPaneCn : public wxTreeCtrl
{
    // wxWindowイベントを処理させたいクラスに利用するマクロ
    DECLARE_EVENT_TABLE()

    static const wxColour COLOR_LIGHT_ORANGE;
    static const wxColour COLOR_LIGHT_RED;
public:
    CPaneCn(void);
    ~CPaneCn(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // 選択済み項目を決める
    void selectChannel(int serviceId, const wxString& channel);

    // 所属チャンネル一覧を表示
    void displayChannels(const std::map<int, CChatServiceBase*>& services);

    // 選択してないチャンネルにMessageが追加された時に呼ばれます。
    void addUnreadMessage(const CChatMessage* message);

    // 一つ先のチャンネルを選択します。
    void selectNextChannel();

    // 一つ前のチャンネルを選択します。
    void selectPreviousChannel();
private:
    wxTreeItemId findChannelNode(int serviceId, const wxString& channleName);
    // チャンネルが選択された際のイベント処理
    void onChannelSelected(wxTreeEvent& event);

    // 項目が右クリックされた際のイベント処理
    void onItemRightClicked(wxTreeEvent& event);

    // チャンネルを選択したというイベントを返す
    CChannelSelectEvent* newSelectEvent(const wxTreeItemId& id);

    // アクティベートされた
    void onActivated(wxTreeEvent& event);

};

}
