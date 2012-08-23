#pragma once
#include "ServiceLog.hpp"
#include <vector>

namespace CornStarch
{
;

// チャットのログを保持するクラス
class CLogHolder
{
private:
    static const int MAX_LENGTH = 200;

    bool m_isOriginalSource;
    std::vector<CServiceLog*> m_logs;
    void clear(void);

public:
    CLogHolder(void);
    ~CLogHolder(void);
    std::vector<CServiceLog*> getLogs(void) const;
    void pushLog(CServiceLog* log);

    void setLogs(std::vector<CServiceLog*> logs)
    {
        clear();
        m_logs = logs;
    }

    bool isOriginalSource(void) const
    {
        return m_isOriginalSource;
    }

    void setOriginalSource(bool isOriginalSource)
    {
        m_isOriginalSource = isOriginalSource;
    }
};

}
