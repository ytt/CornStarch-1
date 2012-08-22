#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{;

// メンバー情報更新ログ
class CMemberLog : public CServiceLog
{
private:
    CMemberData* m_member;

public:
    CMemberLog(void);
    ~CMemberLog(void);

    // 初期化を行う
    void init(const CMemberData& member);

    // ログを取得する
    CMemberData getLog(void) const;
};

}
