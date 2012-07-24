﻿
#include "SCService.h"
#include "SCConnection.hpp"
#include "SCUser.hpp"

CSCService::CSCService() {

}

CSCService::~CSCService() {
}

void CSCService::init(wxEvtHandler* handler)
{
	CChatServiceBase::init(handler);

    // スターチャットの通信
    m_connect = new CSCConnection();
    m_connect->init(this->m_id,m_handler);

    // スターチャットのユーザー
    m_user = new CSCUser();
    m_user->init();
    m_user->setChannel("");

    // 認証
    wxString basicKey = m_user->getBasicKey();
    wxString nameKey = m_user->getNameKey();
    if (m_persist->isKeySaved(basicKey) && m_persist->isKeySaved(nameKey)){

        // 保存されてデータから読み込み。
        m_user->setUserName(m_persist->loadValue(nameKey));
        m_user->setBasic(m_persist->loadValue(basicKey));

        // 認証を開始
        m_connect->startAuthTask( m_user);
    }
}