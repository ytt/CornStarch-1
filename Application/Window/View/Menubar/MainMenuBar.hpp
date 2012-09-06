#pragma once
#include "MenuFile.hpp"
#include "MenuServer.hpp"
#include "MenuChannel.hpp"
#include "MenuEdit.hpp"
#include "MenuView.hpp"

namespace CornStarch
{;

class CMainMenuBar : public wxMenuBar
{
private:

    CMenuFile* m_menuFile; // ファイル
    CMenuEdit* m_menuEdit; // 編集
    CMenuServer* m_menuServer; // サーバ
    CMenuChannel* m_menuChannel; // チャンネル
    CMenuView* m_menuView; // 表示

public:
    CMainMenuBar(void);
    ~CMainMenuBar(void);

    // メニューバーを初期化する
    void init(void);

};

}
