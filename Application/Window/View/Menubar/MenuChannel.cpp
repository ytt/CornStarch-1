#include "MenuChannel.hpp"

namespace CornStarch
{;

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
    append(
        MENU_CHANNEL_JOIN,
        wxT("チャンネルに参加\tCTRL+J"));
    append(
        MENU_CHANNEL_PART,
        wxT("チャンネルから離脱\tCTRL+L"));
    append(
        MENU_CHANNEL_TOPIC_CHANGE,
        wxT("トピックを変更\tCTRL+T"));
}

}
