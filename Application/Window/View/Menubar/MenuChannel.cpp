#include "MenuChannel.hpp"

namespace CornStarch
{
;

CMenuChannel::CMenuChannel(void)
{
}

CMenuChannel::~CMenuChannel(void)
{
}

///////////////////////////////////

void CMenuChannel::init(void)
{
    setTitle(wxT("チャンネル(&C)"));
    Append(MENU_CHANNEL_JOIN, wxT("チャンネルに参加\tCTRL+J"));
    Append(MENU_CHANNEL_PART, wxT("チャンネルから離脱\tCTRL+L"));
    Append(MENU_CHANNEL_TOPIC_CHANGE, wxT("トピックを変更\tCTRL+T"));
    AppendSeparator();
    Append(MENU_CHANNEL_ADD_TAB, wxT("タブの追加"));
    Append(MENU_CHANNEL_REMOVE_TAB, wxT("タブの削除"));
}

}
