#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>

namespace CornStarch
{;

class CMenuPart : public wxMenu
{
public:
    // メニュー番号
    enum MENU{
        MENU_FILE_QUIT = 100,
        MENU_FILE_SAVE,
        MENU_FILE_LOAD,
        MENU_EDIT_SELECT_ALL,
        MENU_EDIT_FIND,

        MENU_SERVER_ADD,
        MENU_SERVER_DELETE,
        MENU_SERVER_NICK_CHANGE,
        MENU_SERVER_MOVETO_UNREAD,

        MENU_VIEW_ZOOM,
        MENU_VIEW_SHRINK,
        MENU_VIEW_SELECT_NEXT_TAB,
        MENU_VIEW_SELECT_PREVOUS_TAB,

        MENU_UPDATE,
        MENU_CHANNEL_JOIN,
        MENU_CHANNEL_PART,
        MENU_CHANNEL_TOPIC_CHANGE,

        MENU_CHANNEL_ADD_TAB,
        MENU_CHANNEL_REMOVE_TAB,
    };

protected:
    wxString m_title; // タイトル文字列

public:
    CMenuPart(void);
    virtual ~CMenuPart(void);

    // タイトルを取得する
    wxString getTitle(void);

protected:


    // タイトルをセットする
    void setTitle(const wxString& title);

};

}
