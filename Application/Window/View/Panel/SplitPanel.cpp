﻿#include "SplitPanel.hpp"

namespace CornStarch
{;

// イベントテーブル
BEGIN_EVENT_TABLE(CSplitPanel, wxSplitterWindow)

    // 各分割ウィンドウから送られてくるイベント
    EVT_SPLITTER_SASH_POS_CHANGED(LEFT_WINDOW_ID, CSplitPanel::onLeftSashPosChanged)

END_EVENT_TABLE();


CSplitPanel::CSplitPanel(void) : m_spHorL(NULL), m_spMsg(NULL), m_spHorR(NULL)
{
}


CSplitPanel::~CSplitPanel(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSplitPanel::init(wxWindow* parent)
{
    // 左右に分割
    this->Create(parent, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE);

    // 左を(メッセージ表示＋投稿画面)と(一覧表示)に分割
    m_spHorL = new wxSplitterWindow(this, LEFT_WINDOW_ID, wxDefaultPosition,
            wxDefaultSize,wxSP_3D| wxSP_LIVE_UPDATE);
    // タブ受け取り用コントロール
    m_spMsgTabTarget = new wxSplitterWindow(m_spHorL, wxID_ANY, wxDefaultPosition,
            wxSize(-1,1), wxSP_NOSASH);
    // (メッセージ表示)と(投稿画面)に分割
    m_spMsg = new wxSplitterWindow(m_spMsgTabTarget, MSG_WINDOW_ID, wxDefaultPosition,
		wxSize(-1,30), wxSP_NOSASH);

	
    // 右を(メンバ表示)と(チャンネル表示)に分割
    m_spHorR = new wxSplitterWindow(this, RIGHT_WINDOW_ID, wxDefaultPosition,
            wxDefaultSize,wxSP_3D| wxSP_LIVE_UPDATE);


    // 各領域の設定
    setSplitParam();
	this->Update();
	this->Layout();
	int position = m_spHorL->GetSashPosition();
	//
}


//////////////////////////////////////////////////////////////////////


// 分割を行う際のパラメータを設定する
void CSplitPanel::setSplitParam(void)
{
    // sash位置の調整
    this->SetSashGravity(0.7); // 左右のバランス
    m_spHorR->SetSashGravity(0.6); // 右画面上下のバランス
    m_spHorL->SetSashGravity(0.6); // 左画面上下のバランス
}

// メッセージ表示パネルを取得する
wxSplitterWindow* CSplitPanel::getMsgPane(void)
{
    return m_spMsg;
}

// メンバー表示パネルを取得する
wxSplitterWindow* CSplitPanel::getMemPane(void)
{
    return m_spHorR;
}

// チャンネル表示パネルを取得する
wxSplitterWindow* CSplitPanel::getCnPane(void)
{
    return m_spHorR;
}

// メッセージ投稿パネルを取得する
wxSplitterWindow* CSplitPanel::getPostPane(void)
{
    return m_spMsg;
}

// 一覧表示パネルを取得する
wxSplitterWindow* CSplitPanel::getRecordPane(void)
{
    return m_spHorL;
}

// 一覧表示パネルを取得する
wxSplitterWindow* CSplitPanel::getTabTargetPane(void)
{
    return m_spMsgTabTarget;
}
//////////////////////////////////////////////////////////////////////


// 左のsash位置が変更された
void CSplitPanel::onLeftSashPosChanged(wxSplitterEvent& event)
{
    Show(false);
    
    // 左画面のsash位置を調整する
    int newPos = event.GetSashPosition();
    m_spMsg->SetSashPosition(newPos - 28);

    m_spMsgTabTarget->SetSashPosition(newPos);
    Show(true);
}

}
