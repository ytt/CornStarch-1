#include "MenuServer.hpp"

namespace CornStarch
{
;

CMenuServer::CMenuServer(void)
{
}

CMenuServer::~CMenuServer(void)
{
}

///////////////////////////////////

void CMenuServer::init(void)
{
    setTitle(wxT("サーバ(&S)"));
    Append(MENU_SERVER_ADD, wxT("サーバの追加"));
    Append(MENU_SERVER_DELETE, wxT("サーバの削除"));
    Append(MENU_SERVER_NICK_CHANGE, wxT("ニックネーム変更\tCTRL+N"));

    AppendSeparator();
    Append(MENU_SERVER_MOVETO_UNREAD, wxT("未読チャンネルに移動"));

}

}
