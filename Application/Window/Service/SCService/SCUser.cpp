#include "SCUser.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

const wxString CSCUser::BASIC_KEY = "basic";
const wxString CSCUser::NAME_KEY = "username";

CSCUser::CSCUser(void)
{
}


CSCUser::~CSCUser(void)
{
}

//////////////////////////////////////////////////////////////////////



// ユーザ名をセット
void CSCUser::setUserInfo(const wxString& username, const wxString& password)
{
    m_username = username;
    m_basic = crypt(username, password);
}

// ニックネームをセット
void CSCUser::setNickName(const wxString& nickName)
{
    m_nick = nickName;
}

// キーワードをセット
void CSCUser::setKeywords(const vector<wxString> keywords)
{
    m_keywords = keywords;
}

// 現在見ているチャンネルをセット
void CSCUser::setChannelName(const wxString& channel)
{
    m_currentCn = channel;
}

// ユーザ名をゲット
wxString CSCUser::getUserName(void) const
{
    return m_username;
}

// ニックネームをゲット
wxString CSCUser::getNickName(void) const
{
    return m_nick;
}

// キーワードをゲット
vector<wxString> CSCUser::getKeywords(void) const
{
    return m_keywords;
}

// basic暗号化された文字列を取得
wxString CSCUser::getBasic(void) const
{
    return m_basic;
}

// 現在見ているチャンネル名を取得する
wxString CSCUser::getChannelName(void) const
{
    return m_currentCn;
}

// メッセージ中にキーワードが含まれているか
bool CSCUser::isCalled(const wxString& message) const
{
    size_t size = m_keywords.size();
    for (size_t i = 0; i < size; i++){

        if (message.find(m_keywords[i]) != wxString::npos){
            return true;
        }
    }

    return false;
}

// basic認証用文字列をセット
void CSCUser::setBasic(const wxString& basic)
{
    m_basic = basic;
}

// ユーザ名をセット
void CSCUser::setUserName(const wxString& name)
{
    m_username = name;
}

// basic文字列を保存する際のキー名を取得
wxString CSCUser::getBasicKey(void) const
{
    return BASIC_KEY;
}

// 名前を保存する際のキー名を取得
wxString CSCUser::getNameKey(void) const
{
    return NAME_KEY;
}


//////////////////////////////////////////////////////////////////////


// basicエンコードする
wxString CSCUser::crypt(const wxString& username, const wxString& password)
{
    wxString str = m_username + ":" + password;

    // 文字列が長い場合
    if (str.size() > MAX_LENGTH / 4){
        return "";
    }

    return wxBase64Encode(str, str.size());
}

}
}
