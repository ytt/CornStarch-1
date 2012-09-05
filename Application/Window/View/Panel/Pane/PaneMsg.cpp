#include "PaneMsg.hpp"
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wx/event.h>
using namespace std;

namespace CornStarch
{
;
//const int CPaneMsg::PANE_MSG_ID = 10000;
// イベントテーブル
BEGIN_EVENT_TABLE(CPaneMsg, CLinkableRichTextCtrl) //
EVT_SCROLLWIN( CPaneMsg::OnScroll)
END_EVENT_TABLE()
;

const wxColour CPaneMsg::COLOR_LIGHT_YELLOW = wxColour(255, 255, 180);
CPaneMsg::CPaneMsg(void) :
        m_beforeScroolHeight(0), m_isScrollingBack(false), m_lastDrawDateLine(
                "")
{
}

CPaneMsg::~CPaneMsg(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPaneMsg::init(wxWindow* parent)
{
    // 画面の初期化
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL);

    // フォント設定
    this->SetFont(wxFont(12, wxDEFAULT, wxNORMAL, wxNORMAL));

    this->setNavigateHaldler();

    GetCaret()->Hide();
}
void CPaneMsg::OnScroll(wxScrollWinEvent &event)
{
    if (event.GetPosition() != 0){
        m_isScrollingBack = true;
        // 一番下まですくロールしていれば、スクロール中を終了。
        if (m_beforeScroolHeight <= event.GetPosition()){
            m_beforeScroolHeight = event.GetPosition() - 1;
            m_isScrollingBack = false;
        } else{
        }
    }
    event.Skip(true);
}

void CPaneMsg::clearUnreadBackgroundColor()
{
    int index = this->GetLastPosition();

    this->SetStyle(0, index,
            wxTextAttr(wxNullColour,
                    wxSystemSettings::GetColour(wxSYS_COLOUR_MENU)));
}
void CPaneMsg::pushLog(const CMessage* messageLog)
{
//    vector<IFilter*> filters = m_configuration->getFilters(
//            messageLog->getChannelName());
    if (m_filter->isValid(messageLog)){
        GetCaret()->Hide();
        this->MoveEnd();
        CLogTextCtrl::pushLog(messageLog);
        if (m_isScrollingBack == false){
            this->ShowPosition(this->GetLastPosition());
        }
    }
}
//bool CPaneMsg::isFilterPassed(const CMessage* message,
//        const vector<IFilter*>& filters)
//{
//    vector<IFilter*>::const_iterator it = filters.begin();
//    while (it != filters.end()){
//        if ((*it)->isValid(message) == false){
//            return false;
//        }
//        it++;
//    }
//    return true;
//}

void CPaneMsg::pushLog(const CChatMessage* messageLog)
{
    drawDateLine(messageLog->getTime("%Y/%m/%d(%a)"));
    wxString name = messageLog->getNick();
    wxString body = messageLog->getBody();
    wxString channel = messageLog->getChannelName();
    wxString time = messageLog->getTime("%H:%M");
    if (messageLog->isReaded() == false){
        this->BeginStyle(wxTextAttr(*wxBLACK, COLOR_LIGHT_YELLOW));
    } else{
        this->BeginStyle(wxTextAttr(*wxBLACK));
    }
    writeLinkableText(time + " "); // 時間を灰で表示
    this->EndAllStyles();
    wxString nick = messageLog->getTempNick();
    if (nick != ""){
        writeColoredText("(" + nick + ") : ", COLOR_RED); // テンポラリー名を赤で表示
    } else{
        writeColoredText("(" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    }
    writeColoredText(body, *wxBLACK);

}

// 必要に応じて日付変更線を描画
void CPaneMsg::drawDateLine(const wxString& now)
{
    if (m_lastDrawDateLine == ""){
        m_lastDrawDateLine = now;
    }
    if (now == m_lastDrawDateLine){
        return;
    }

    this->Newline();
    AppendText("------" + now + "--------");
    this->Newline();
    this->Newline();
    m_lastDrawDateLine = now;
}

void CPaneMsg::setConfiguration(const CServiceConfiguration* configuration)
{
    if (configuration != NULL){
        m_configuration = configuration;
        // フォント設定
        this->SetFont(
                wxFont(m_configuration->getFontSize(), wxDEFAULT, wxNORMAL,
                        wxNORMAL));
    }
}
}
