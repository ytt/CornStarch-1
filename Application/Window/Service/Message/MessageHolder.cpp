#include "MessageHolder.hpp"
using namespace std;

namespace CornStarch
{
;

CMessageHolder::CMessageHolder(void) :
        m_isOriginalSource(false)
{
}

CMessageHolder::~CMessageHolder(void)
{
    clear();
}

//////////////////////////////////////////////////////////////////////

void CMessageHolder::clear(void)
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
vector<CMessage*> CMessageHolder::getLogs(void) const
{
    return m_logs;
}

//////////////////////////////////////////////////////////////////////

// ログを追加する
void CMessageHolder::pushLog(CMessage* log)
{
    // ログの追加
    m_logs.push_back(log);

    // 多すぎたら先頭削除
    if (m_logs.size() > MAX_LENGTH){
        vector<CMessage*>::iterator it = m_logs.begin();
        if (m_isOriginalSource){
            delete *it;
        }
        m_logs.erase(it);
    }
}

}
