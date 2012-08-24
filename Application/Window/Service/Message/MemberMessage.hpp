#pragma once
#include "Message.hpp"

namespace CornStarch
{
;

// メンバー情報更新ログ
class CMemberMessage: public CMessage
{
private:
    wxString m_nickName;

public:
    CMemberMessage(void);
    ~CMemberMessage(void);

    wxString getNickName() const
    {
        return m_nickName;
    }

    void setNickName(wxString nickName)
    {
        m_nickName = nickName;
    }
};

}
