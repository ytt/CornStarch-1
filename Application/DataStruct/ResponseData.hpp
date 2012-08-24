#pragma once
#include <wx/string.h>
#include <time.h>

namespace CornStarch
{;

// 投稿メッセージの内容を表すクラス
class CResponseData
{
private:
    static const int MAX_LENGTH = 256; // 時間表示形式の最大文字数

public:

    int m_id; // メッセージID
    wxString m_username; // ユーザ名
    wxString m_body; // メッセージ本文
    time_t m_time; // UNIX時間
    wxString m_channel; // チャンネル名
    wxString m_tempNick; // 一時ニックネーム

    CResponseData(){}
    virtual ~CResponseData(){}
    CResponseData(int id, const wxString& name, const wxString& body,
        const wxString& channel, const time_t& t)
        : m_id(id), m_username(name), m_channel(channel), m_time(t), m_body(body){}

};

}
