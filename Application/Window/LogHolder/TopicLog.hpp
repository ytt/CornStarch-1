#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{;

// トピック変更のログ
class CTopicLog : public CServiceLog
{
private:
    CChannelData* m_channel;

public:
    CTopicLog(void);
    ~CTopicLog(void);

    // 初期化を行う
    void init(const CChannelData& channel);

    // ログを取得する
    CChannelData getLog(void) const;
};

}
