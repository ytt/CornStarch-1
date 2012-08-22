#include "MainLogHolder.hpp"
#include "MessageLog.hpp"
#include "MemberLog.hpp"
#include "JoinLog.hpp"
#include "PartLog.hpp"
#include "TopicLog.hpp"
#include "InviteLog.hpp"
#include "KickLog.hpp"

using namespace std;

namespace CornStarch
{;

CMainLogHolder::CMainLogHolder(void)
{
}


CMainLogHolder::~CMainLogHolder(void)
{
    size_t size = m_logs.size();
    for (size_t i = 0; i < size; i++){
        delete m_logs[i];
    }
}


//////////////////////////////////////////////////////////////////////


// ログ一覧を取得する
vector<CServiceLog*> CMainLogHolder::getLogs(void) const
{
    return m_logs;
}

// ニックネームの更新を行う
void CMainLogHolder::onUpdateNickName(const CMemberData& member)
{
    vector<CServiceLog*>::iterator it = m_logs.begin();
    for (; it != m_logs.end(); it++){

        // ニックネームが未知の時、更新を行う
        if ((*it)->isUnknownNick(member.m_name)){
            (*it)->updateNick(member.m_nick);
        }
    }
}


//////////////////////////////////////////////////////////////////////


// ログを追加する
void CMainLogHolder::pushLog(CServiceLog* log,const wxString& serviceName)
{
    log->setServiceName(serviceName);
    // ログの追加
    m_logs.push_back(log);

    // 多すぎたら先頭削除
    if (m_logs.size() > MAX_LENGTH){
        vector<CServiceLog*>::iterator it = m_logs.begin();
        delete *it;
        m_logs.erase(it);
    }
}

}
