﻿#include "JoinStreamEvent.hpp"

using namespace std;

namespace CornStarch
{;
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
CJoinStreamEvent::CJoinStreamEvent(void)
{
   this->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
}


CJoinStreamEvent::~CJoinStreamEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// チャンネル名をセット
void CJoinStreamEvent::setChannelName(const wxString& channel)
{
    m_channel = channel;
}

// ユーザ名をセット
void CJoinStreamEvent::setUserName(const wxString& userName)
{
    m_user = userName;
}

// チャンネル名を取得
wxString CJoinStreamEvent::getChannelName(void) const
{
    return m_channel;
}

// ユーザ名を取得
wxString CJoinStreamEvent::getUserName(void) const
{
    return m_user;
}

}
