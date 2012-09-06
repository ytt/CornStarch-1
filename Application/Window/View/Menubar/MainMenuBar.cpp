#include "MainMenuBar.hpp"

namespace CornStarch
{;

CMainMenuBar::CMainMenuBar(void)
    : m_menuFile(NULL), m_menuEdit(NULL), m_menuServer(NULL), m_menuChannel(NULL)
{
}


CMainMenuBar::~CMainMenuBar(void)
{
}


///////////////////////////////////


// メニューバーを初期化する
void CMainMenuBar::init(void)
{
    // 【ファイル】
    m_menuFile = new CMenuFile();
    m_menuFile->init();
    // 【編集】
    m_menuEdit = new CMenuEdit();
    m_menuEdit->init();
    // 【登録】
    m_menuServer = new CMenuServer();
    m_menuServer->init();

    // 【チャンネル】
    m_menuChannel = new CMenuChannel();
    m_menuChannel->init();

    // 【表示】
    m_menuView = new CMenuView();
    m_menuView->init();
    // メニューバーに項目を追加する
    Append(m_menuFile, m_menuFile->getTitle());
    Append(m_menuEdit, m_menuEdit->getTitle());
    Append(m_menuView, m_menuView->getTitle());
    Append(m_menuServer, m_menuServer->getTitle());
    Append(m_menuChannel, m_menuChannel->getTitle());
}

}
