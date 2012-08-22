#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{
;

// メンバー情報更新ログ
class CMemberLog: public CServiceLog
{
private:
    wxString m_nickName;
    //CMemberData* m_member;

public:
    CMemberLog(void);
    ~CMemberLog(void);

    wxString getNickName() const
    {
        return m_nickName;
    }

    void setNickName(wxString nickName)
    {
        m_nickName = nickName;
    }
//    // 初期化を行う
//    void init(const CMemberData& member);
//
//    // ログを取得する
//    CMemberData getLog(void) const;
};

}
