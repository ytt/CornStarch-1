#include "ChannelStatus.hpp"
#include "LogHolder/MessageLog.hpp"

using namespace std;

namespace CornStarch
{
;

CChannelStatus::CChannelStatus(void) :
        m_unreadCount(0), m_isLoaded(false)
{
}

CChannelStatus::~CChannelStatus(void)
{
    delete m_logHolder;
    delete m_members;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CChannelStatus::init(void)
{
    m_logHolder = new CLogHolder();
    m_logHolder->setOriginalSource(true);
    m_members = new CMemberVec();
}

// トピックをセットする
void CChannelStatus::setTopic(const wxString& topic)
{
    m_topic = topic;
}

// トピックを取得する
wxString CChannelStatus::getTopic(void) const
{
    return m_topic;
}

// メッセージ一覧を取得する
vector<CServiceLog*> CChannelStatus::getLog(void) const
{
    return m_logHolder->getLogs();
}

// メンバー一覧を取得する
vector<CMemberData*> CChannelStatus::getMembers(void) const
{
    return *m_members;
}

// メッセージを追加する
void CChannelStatus::pushLog(CServiceLog* log)
{
    m_logHolder->pushLog(log);
}

// メンバーを追加する
void CChannelStatus::pushMember(const CMemberData& member)
{
    CMemberVec::iterator it = m_members->begin();
    while (it != m_members->end()){
        if ((*it)->m_name == member.m_name){
            return;
        }
        it++;
    }
    m_members->push(member);
}

// メッセージ一覧をセットする
void CChannelStatus::setMessages(const vector<CServiceLog*>& messages)
{
    if (m_isLoaded == false){
        int size = messages.size();
        if (size != 0){
            size--;
            for (int i = 0; i < m_unreadCount; i++){
                CMessageLog* message = dynamic_cast<CMessageLog*>(messages[size
                        - i]);
                if (message != NULL){
                    message->getMessage()->m_isReaded = false;
                }
            }
        }
        m_logHolder->setLogs(messages);
        m_isLoaded = true;
    }
}
// メンバー一覧をセットする
void CChannelStatus::setMembers(const vector<CMemberData*>& members)
{
    m_members->setMembers(members);
}

// メッセージを取得し終えたか
bool CChannelStatus::hasReceivedMessage(void) const
{
    return m_isLoaded;
}

// メンバーを取得し終えたか
bool CChannelStatus::hasReceivedMember(void) const
{
    return m_members->hasSetMember();
}

// ID不明かつ同じ投稿内容のメッセージがあるか
bool CChannelStatus::hasSameMessage(const CMessageData& message) const
{
    vector<CServiceLog*> logs = m_logHolder->getLogs();
    size_t length = logs.size();
    for (size_t i = 0; i < length; i++){

        CMessageLog* log = dynamic_cast<CMessageLog*>(logs[i]);
        if (log != NULL){
            // 未知のIDでかつメッセージが同じだったら
            if (log->getMessage()->m_id == -1
                    && log->getMessage()->m_body == message.m_body){
                return true;
            }
        }
    }
    return false;
}

// 同じ内容のメッセージについてIDを更新
void CChannelStatus::updateMessageId(const CMessageData& message)
{
    if (!hasSameMessage(message)){
        return;
    }

    vector<CServiceLog*> logs = m_logHolder->getLogs();
    size_t length = logs.size();
    for (size_t i = 0; i < length; i++){

        CMessageLog* log = dynamic_cast<CMessageLog*>(logs[i]);
        if (log != NULL){
            // 未知のIDでかつメッセージが同じだったら
            if (log->getMessage()->m_id == -1
                    && log->getMessage()->m_body == message.m_body){
                log->getMessage()->m_id = message.m_id;
            }
        }
    }
}

// メンバー情報を更新する
void CChannelStatus::updateMember(const wxString& userName,
        const wxString& nick)
{
    m_members->updateStatus(userName, nick);
}

// メンバー情報を消す
void CChannelStatus::popMember(const wxString& userName)
{
    m_members->pop(userName);
}
// 未読をクリア
void CChannelStatus::clearUnreadCount()
{
    if (m_isLoaded){
        m_unreadCount = 0;
        vector<CServiceLog*> logs = m_logHolder->getLogs();
        vector<CServiceLog*>::iterator it = logs.begin();
        while (it != logs.end()){
            CMessageLog* message = dynamic_cast<CMessageLog*>(*it);
            if (message != NULL){
                message->getMessage()->m_isReaded = true;
            }
            it++;
        }
    }
}

}
