#include "LogHolder.hpp"
#include "MessageLog.hpp"
#include "MemberLog.hpp"
#include "JoinLog.hpp"
#include "PartLog.hpp"
#include "TopicLog.hpp"
#include "InviteLog.hpp"
#include "KickLog.hpp"

using namespace std;

namespace CornStarch
{
;

CLogHolder::CLogHolder(void) :
        m_isOriginalSource(false)
{
}

CLogHolder::~CLogHolder(void)
{
    clear();
}

//////////////////////////////////////////////////////////////////////

void CLogHolder::clear(void)
{
    if (m_isOriginalSource){
        size_t size = m_logs.size();
        for (size_t i = 0; i < size; i++){
            delete m_logs[i];
        }
    }
    m_logs.clear();
}

// ログ一覧を取得する
vector<CServiceLog*> CLogHolder::getLogs(void) const
{
    return m_logs;
}

//////////////////////////////////////////////////////////////////////

// ログを追加する
void CLogHolder::pushLog(CServiceLog* log)
{
    // ログの追加
    m_logs.push_back(log);

    // 多すぎたら先頭削除
    if (m_logs.size() > MAX_LENGTH){
        vector<CServiceLog*>::iterator it = m_logs.begin();
        if (m_isOriginalSource){
            delete *it;
        }
        m_logs.erase(it);
    }
}

}
