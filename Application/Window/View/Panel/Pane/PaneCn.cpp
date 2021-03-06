﻿#include "PaneCn.hpp"
#include "TreeChannelItem.hpp"

using namespace std;

namespace CornStarch
{
;

const wxColour CPaneCn::COLOR_LIGHT_ORANGE = wxColour(200, 0, 0);
const wxColour CPaneCn::COLOR_LIGHT_RED = wxColour(100, 0, 0);
// イベントテーブルの登録
BEGIN_EVENT_TABLE(CPaneCn, wxTreeCtrl)

// チャンネルツリーの項目を選択
EVT_TREE_SEL_CHANGED(wxID_ANY, CPaneCn::onChannelSelected)

// チャンネルツリーの項目を右クリック
EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, CPaneCn::onItemRightClicked)

// ツリーの項目がアクティベートされた
EVT_TREE_ITEM_ACTIVATED(wxID_ANY, CPaneCn::onActivated)

END_EVENT_TABLE();

CPaneCn::CPaneCn(void)
{
}

CPaneCn::~CPaneCn(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPaneCn::init(wxWindow* parent)
{
    // スクロールバー(水平、垂直を必要に応じて)、ソート
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxTR_HIDE_ROOT | wxTR_NO_BUTTONS);

    // Rootノードを追加
    AddRoot("Root");
}

// 選択済み項目を決める
void CPaneCn::selectChannel(int serviceId, const wxString& channel)
{
    wxTreeItemId node = findChannelNode(serviceId, channel);
    if (node.IsOk()){
        this->SelectItem(node);
    }
}

// 一つ先のチャンネルを選択します。
void CPaneCn::selectNextChannel()
{
    wxTreeItemId selectedId = GetSelection();
    if (selectedId.IsOk()){
        wxTreeItemIdValue cookie;
        wxTreeItemId root = GetRootItem();
        wxTreeItemId server = GetFirstChild(root, cookie);
        wxTreeItemId firstFoundId;
        bool isFound = false;
        while (server.IsOk()) // サーバーノードを探索
        {
            // 選択しているサーバーを見つけた。
            if (server == selectedId){
                isFound = true;
            }
            wxTreeItemId channel = this->GetFirstChild(server, cookie);
            while (channel.IsOk()) // チャンネルノードを探索
            {
                // 一つ目のチャンネル
                if (firstFoundId.IsOk() == false){
                    firstFoundId = channel;
                }
                // 選択を見つけた以降でのチャンネルがあれば選択して終了
                if (isFound){
                    SelectItem(channel);
                    return;
                }
                // 選択しているチャンネルをみつける。
                if (channel == selectedId){
                    isFound = true;
                }
                channel = this->GetNextSibling(channel);
            }
            server = this->GetNextSibling(server);
        }
        // 選択している以降にチャンネルが見つからないなら、選択前に見つけたものを選択
        if (firstFoundId.IsOk()){
            SelectItem(firstFoundId);
        }
    }
}

// 一つ前のチャンネルを選択します。
void CPaneCn::selectPreviousChannel()
{
    wxTreeItemId selectedId = GetSelection();
    if (selectedId.IsOk()){
        wxTreeItemIdValue cookie;
        wxTreeItemId root = GetRootItem();
        wxTreeItemId server = GetFirstChild(root, cookie);
        wxTreeItemId lastFoundId;
        while (server.IsOk()) // サーバーノードを探索
        {
            // 選択しているサーバーを見つけたら、最後に見つけたノードを選択。
            if (server == selectedId){
                if (lastFoundId.IsOk()){
                    SelectItem(lastFoundId);
                    return;
                }
            }
            wxTreeItemId channel = this->GetFirstChild(server, cookie);
            while (channel.IsOk()) // チャンネルノードを探索
            {
                // 選択しているチャンネルをみつけたら、最後に見つけたノードを選択。
                if (channel == selectedId){
                    if (lastFoundId.IsOk()){
                        SelectItem(lastFoundId);
                        return;
                    }
                }
                lastFoundId = channel;
                channel = this->GetNextSibling(channel);
            }
            server = this->GetNextSibling(server);
        }
        // 最後に見つけたものを選択
        if (lastFoundId.IsOk()){
            SelectItem(lastFoundId);
        }
    }
}
// 所属チャンネル一覧を表示
void CPaneCn::displayChannels(const map<int, CChatServiceBase*>& connections)
{
    // 項目を削除
    wxTreeItemId rootId = GetRootItem();
    DeleteChildren(rootId);

    // 各サーバについてループ
    map<int, CChatServiceBase*>::const_iterator it;
    for (it = connections.begin(); it != connections.end(); it++){

        // サーバ情報をセット
        CTreeServerItem* data = new CTreeServerItem();
        data->setServerId((*it).second->getId());

        // サーバ名をセット
        wxString name(wxString::Format(wxT("▼%s"), (*it).second->getName()));
        wxTreeItemId id = AppendItem(rootId, name, -1, -1, data);
        if ((*it).second->IsConnected() == false){
            this->SetItemTextColour(id, *wxLIGHT_GREY);
        }
        // 各チャンネルについてループ
        vector<CChannelStatus*>::const_iterator cit;
        vector<CChannelStatus*> channels = (*it).second->getChannels();
        for (cit = channels.begin(); cit != channels.end(); cit++){

            CTreeChannelItem* channel = new CTreeChannelItem();
            channel->setUnreadCount((*cit)->getUnreadCount());
            channel->setChannelName((*cit)->getChannelName());

            wxString channelText = (*cit)->getChannelName();
            if ((*cit)->getUnreadCount() != 0){
                channelText = wxString::Format(wxT("%s (%d)"),
                        (*cit)->getChannelName(), (*cit)->getUnreadCount());
            }
            // チャンネルをセット
            wxTreeItemId childId = AppendItem(id, channelText, -1, -1, channel);
            if ((*it).second->IsConnected() == false){
                this->SetItemTextColour(childId, *wxLIGHT_GREY);
            }
            //　背景を色を返る。
            if ((*cit)->getUnreadCount() != 0){
                this->SetItemBackgroundColour(childId, *wxLIGHT_GREY);
            }
        }

        Expand(id);
    }
}

//////////////////////////////////////////////////////////////////////

// チャンネルが選択された際のイベント処理
void CPaneCn::onChannelSelected(wxTreeEvent& event)
{
    wxTreeItemId id = event.GetItem();
    // 未読数の初期化
    CTreeChannelItem* channel = dynamic_cast<CTreeChannelItem*>(GetItemData(id)); //
    if (channel != NULL){
        channel->setUnreadCount(0);
        wxString channelText = channel->getChannelName();
        this->SetItemText(id, channelText);
    }

    CChannelSelectEvent* chEvent = newSelectEvent(id);

    if (chEvent == NULL){
        return;
    }
    // イベント送信
    chEvent->SetEventType(myEVT_SELECT_TREE_NODE); // イベントタイプ
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetEventHandler(),
            chEvent);
}

// 項目が右クリックされた際のイベント処理
void CPaneCn::onItemRightClicked(wxTreeEvent& event)
{
    SelectItem(event.GetItem());
    wxTreeItemId id = event.GetItem();
    CChannelSelectEvent* chEvent = newSelectEvent(id);

    if (chEvent == NULL){
        return;
    }

    // イベント送信
    chEvent->SetEventType(myEVT_SELECT_TREE_NODE_RIGHT); // イベントタイプ
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetEventHandler(),
            chEvent);
}

// チャンネルを選択したというイベントを返す
CChannelSelectEvent* CPaneCn::newSelectEvent(const wxTreeItemId& id)
{
    // 自分と親のツリーIDを取得
    wxTreeItemId parentId = GetItemParent(id);

    // フォント設定
    this->SetItemTextColour(id, *wxBLACK);
    // アイテム名の取得
    wxString itemName = GetItemText(id);

    // Mac番で、ルートノードが選択されるケースがある
    if (parentId == NULL){
        return NULL;
    }

    // コントローラへ投げるイベントを作成
    CChannelSelectEvent* chEvent = new CChannelSelectEvent();

    // 選択されたのがチャンネルなら
    if (parentId != GetRootItem()){

        // イベントの初期化
        int serverId =
                ((CTreeServerItem*) GetItemData(parentId))->getServerId();
        chEvent->setServerOrNot(false);
        chEvent->setServerId(serverId);
        chEvent->setServer(GetItemText(parentId));

    } else{

        // 選択されたのがサーバなら
        int serverId = ((CTreeServerItem*) GetItemData(id))->getServerId();
        chEvent->setServerId(serverId);

        // イベントの初期化
        chEvent->setServerOrNot(true);
    }

    // イベントを返す
    chEvent->setChannelName(itemName);
    return chEvent;
}

// アクティベートされた
void CPaneCn::onActivated(wxTreeEvent& event)
{
    return;
}
wxTreeItemId CPaneCn::findChannelNode(int serviceId,
        const wxString& channleName)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId root = GetRootItem();
    wxTreeItemId server = GetFirstChild(root, cookie);
    while (server.IsOk()) // サーバーノードを探索
    {
        if (((CTreeServerItem*) GetItemData(server))->getServerId()
                == serviceId){
            wxTreeItemId channel = this->GetFirstChild(server, cookie);
            while (channel.IsOk()) // チャンネルノードを探索
            {
                CTreeChannelItem* channleItem =
                        ((CTreeChannelItem*) GetItemData(channel));
                if (channleItem->getChannelName() == channleName){
                    return channel;
                }
                channel = this->GetNextSibling(channel);
            }
        }
        server = this->GetNextSibling(server);
    }
    return server;
}
// Messageが追加された時に呼ばれます。
void CPaneCn::addUnreadMessage(const CChatMessage* message)
{
    wxTreeItemId node = findChannelNode(message->getServiceId(),
            message->getChannelName());
    if (node.IsOk()){
        CTreeChannelItem* channleItem = ((CTreeChannelItem*) GetItemData(node));
        channleItem->addUnreadCount();
        wxString channelText = wxString::Format(wxT("%s (%d)"),
                channleItem->getChannelName(), channleItem->getUnreadCount());
        this->SetItemText(node, channelText);

        // フォント設定
        this->SetItemTextColour(node, CPaneCn::COLOR_LIGHT_ORANGE);
    }
}

}
