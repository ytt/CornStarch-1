#pragma once
#include "Message.hpp"
#include <vector>

namespace CornStarch
{
;

// チャットのログを保持するクラス
class CMessageHolder
{
private:
    static const int MAX_LENGTH = 200;

    bool m_isOriginalSource;
    std::vector<CMessage*> m_logs;
    void clear(void);

public:
    CMessageHolder(void);
    ~CMessageHolder(void);
    std::vector<CMessage*> getLogs(void) const;
    void pushLog(CMessage* log);

    void setLogs(std::vector<CMessage*> logs)
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
