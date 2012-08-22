#pragma once
#include "ServiceLog.hpp"
#include <vector>

namespace CornStarch
{;

// チャットのログを保持するクラス
class CMainLogHolder
{
private:
    std::vector<CServiceLog*> m_logs; // ログを保存する
    static const int MAX_LENGTH = 200; //ログの最大個数

public:
    CMainLogHolder(void);
    ~CMainLogHolder(void);

    // ログ一覧を取得する
    std::vector<CServiceLog*> getLogs(void) const;

    // ニックネームの更新を行う
//    void onUpdateNickName(const CMemberData& member);

    // ログを追加する
    void pushLog(CServiceLog* log);
private:

};

}
