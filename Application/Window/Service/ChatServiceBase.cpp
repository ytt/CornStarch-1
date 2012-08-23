#include "ChatServiceBase.hpp"

using namespace std;

namespace CornStarch
{
;

CChatServiceBase::CChatServiceBase(void) :
        m_handler(NULL), m_channel(NULL), m_user(NULL), m_nickTable(NULL), m_connect(
                NULL), m_state(DISCONNECT)
{
}

CChatServiceBase::~CChatServiceBase(void)
{
    delete m_connect;
    delete m_channel;
    delete m_user;
    delete m_nickTable;
    delete m_commandInvoker;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CChatServiceBase::init(wxEvtHandler* handler)
{
    // イベントハンドラの登録
    m_handler = handler;

    // データ保持部の初期化
    m_channel = new CChannelHolder(); // チャンネル
    m_channel->init();

    // ニックネームテーブルの初期化
    m_nickTable = new CNickTable();
}
// 切断を行う。
void CChatServiceBase::disconnect(void)
{
    m_connect->disconnect();
    m_state = DISCONNECT;
}
// ユーザがログインしているか
bool CChatServiceBase::isUserLogin(void) const
{
    return m_user->isLogin();
}

// ユーザ登録を行った際のデータ更新
void CChatServiceBase::registerUser(const wxString& userName,
        const wxString& pass)
{
    // ユーザ情報をセット
    m_user->setUserInfo(userName, pass);
}

// ユーザ登録を行った際のデータ更新
void CChatServiceBase::registerUserBasiscEncoded(const wxString& userName,
        const wxString& pass)
{
    m_user->setBasic(pass);
    m_user->setUserName(userName);
}
void CChatServiceBase::connect(void)
{
    // 認証タスクの開始
    m_state = CONNECTING;
    m_connect->startAuthTask(m_user);
}
// チャンネルに参加を行う際
void CChatServiceBase::joinChannel(const wxString& channel)
{
    // チャンネル参加タスクの開始
    m_connect->startJoinTask(m_user, channel);
}

// チャンネルから離脱する際
void CChatServiceBase::partChannel(const wxString& channel)
{
    // チャンネル離脱タスクを開始
    m_connect->startPartTask(m_user, channel);
}

// 各チャンネルの情報を破棄
void CChatServiceBase::clearChannels(void)
{
    delete m_channel;
    m_channel = new CChannelHolder(); // チャンネル
    m_channel->init();

}

// ニックネームテーブルを破棄
void CChatServiceBase::clearNickTable(void)
{
    delete m_nickTable;
    m_nickTable = new CNickTable();
}

// 現在のチャンネル名を取得
wxString CChatServiceBase::getCurrentChannel(void) const
{
    return m_user->getChannelName();
}

// メッセージを生成
CMessageData CChatServiceBase::generateMessage(const wxString& body)
{
    return CMessageData(-1, m_user->getUserName(), body,
            m_user->getChannelName(), time(NULL));
}

// ニックネームを取得
wxString CChatServiceBase::getNickName(void) const
{
    return m_user->getNickName();
}

// メッセージを投稿した際
void CChatServiceBase::postMessage(CMessageLog* log)
{
    CMessageData* message = log->getMessage();
    // メッセージ投稿タスクの開始
    wxString channel = m_user->getChannelName();
    m_connect->startPostMessageTask(m_user, message->m_body, channel);

    m_channel->pushLog(log->getChannelName(), log);
}

// チャンネルを選択した際
void CChatServiceBase::selectChannel(const wxString& channel)
{
    m_user->setChannelName(channel);
}

// チャンネル一覧を取得
vector<CChannelStatus*> CChatServiceBase::getChannels(void) const
{
    return m_channel->getChannels();
}
// チャンネルを取得
CChannelStatus* CChatServiceBase::getChannel(const wxString& channelName) const
{
    return m_channel->getChannel(channelName);
}
// メッセージ一覧を取得
vector<CServiceLog*> CChatServiceBase::getLogs(
        const wxString& channel) const
{
    return m_channel->getLogs(channel);
}

// メンバー一覧を取得
vector<CMemberData*> CChatServiceBase::getMembers(const wxString& channel) const
{
    return m_channel->getMembers(channel);
}

// ニックネームテーブルを取得
CNickTable CChatServiceBase::getNickTable(void) const
{
    return *m_nickTable;
}

// ユーザが呼ばれたか
bool CChatServiceBase::isUserCalled(const wxString& message)
{
    return m_user->isCalled(message);
}

// メンバーのニックネームを取得
wxString CChatServiceBase::getMemberNick(const wxString& member)
{
    return m_nickTable->getNickname(member);
}

// メンバーの本名を取得
wxString CChatServiceBase::getMemberRealName(const wxString& nick) const
{
    return m_nickTable->getRealName(nick);
}

// チャンネルのトピックを取得
wxString CChatServiceBase::getTopic(const wxString& channel)
{
    return m_channel->getTopic(channel);
}

// このクライアントから投稿されたメッセージか
bool CChatServiceBase::isPostedThisClient(const CMessageData* message)
{
    return m_channel->hasSameMessage(message)
            && message->m_username == m_user->getUserName();
}

// メッセージ表示を行う際
void CChatServiceBase::onUpdateMessageView(const wxString& channel)
{
    // メッセージが受信済み
    if (!m_channel->hasReceivedMessage(channel)){

        // メッセージ取得タスクを開始
        m_connect->startGetMessageTask(m_user, channel);
    }
}

// メンバー表示を行う際
void CChatServiceBase::onUpdateMemberView(const wxString& channel)
{
    // メンバー受信済み
    if (!m_channel->hasReceivedMember(channel)){

        // メンバー取得タスクを開始
        m_connect->startGetMemberTask(m_user, channel);
    }
}

// チャンネル表示を行う際
void CChatServiceBase::onUpdateChannelView(void)
{
    // チャンネル受信済みなら
    if (!m_channel->hasReceivedChannel()){

        // チャンネル取得タスクを開始
        m_connect->startGetChannelTask(m_user);
    }
}

// ニックネームの変更を行う際
void CChatServiceBase::onNickChange(const wxString& nick)
{
    // 自身のニックネーム変更
    m_user->setNickName(nick);

    // ニックネーム変更タスクを開始
    m_connect->startNickChangeTask(m_user, nick);
}

// トピックの変更を行う際
void CChatServiceBase::onChangeTopic(const wxString& topic)
{
    m_connect->startChangeTopicTask(m_user, topic);
}

/////////////////////////////////////////

// 認証が成功した場合
void CChatServiceBase::onAuthSucceeed(void)
{
    this->setConnected(true);
    // ユーザをログイン状態にする
    m_user->setLogin(true);

    // ニックネーム取得タスク
    m_connect->startGetMemberInfoTask(m_user, m_user->getUserName());

    // ストリーム受信タスク
    m_connect->startStreamTask(m_user);
}

// メッセージ一覧を取得した場合
void CChatServiceBase::onGetMessages(const wxString channleName,
        const vector<CMessageData*>& messages)
{
    vector<CServiceLog*> logs;
    vector<CMessageData*>::const_iterator it = messages.begin();
    while (it != messages.end()){

        CMessageLog* log = new CMessageLog();
        log->setServiceId(getId());
        log->init(*(*it));
        log->setUserName((*it)->m_username);
        log->setChannelName((*it)->m_channel);
        log->setTime((*it)->m_time);
        logs.push_back(log);
        it++;
    }
    m_channel->setLogs(channleName, logs);
}

// メンバー一覧を取得した場合
void CChatServiceBase::onGetMembers(const wxString& channel,
        const vector<CMemberData*>& members)
{
    m_channel->setMembers(channel, members);
    m_nickTable->addTableFromMembers(members);
}

// チャンネル一覧を取得した場合
void CChatServiceBase::onGetChannels(const vector<CChannelData*>& channels)
{
    m_channel->setChannels(channels);

    if (m_user->getChannelName() == ""){
        m_user->setChannelName(m_channel->getFirstChannel());
    }
}

// チャンネル参加成功時
void CChatServiceBase::onJoinChannel(const wxString& channel)
{
    // ユーザの現在のチャンネルを変更
    m_user->setChannelName(channel);

    // チャンネル一覧取得タスクの開始
    m_connect->startGetChannelTask(m_user);
}

// チャンネル離脱成功時
void CChatServiceBase::onPartChannel(const wxString& channel)
{
    // チャンネル情報を削除
    m_channel->popChannel(channel);

    if (m_user->getChannelName() == channel){
        // ユーザの現在のチャンネルを変更
        m_user->setChannelName(m_channel->getFirstChannel());
    }
}

// メンバー情報を取得した場合
void CChatServiceBase::onGetMemberStatus(const CMemberData& member)
{
    // 自分の情報だったら
    if (member.m_name == m_user->getUserName()){
        m_user->setNickName(member.m_nick);
        m_user->setKeywords(member.m_keywords);
    }

    m_channel->updateMember(member.m_name, member.m_nick);
    (*m_nickTable)[member.m_name] = member.m_nick;
}

// メッセージストリームを取得した場合
void CChatServiceBase::onGetMessageStream(CMessageLog* message)
{
    // 別クライアントからのメッセージだったら、データ更新のみ
    if (m_channel->hasSameMessage(message->getMessage())
            && message->getUserName() == m_user->getUserName()){
        m_channel->onUpdateMessageId(message->getMessage());
        return;
    }

    // ニックネームが未知の場合、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(message->getUserName())){
        m_connect->startGetMemberInfoTask(m_user, message->getUserName());
    }

    // 既に受信を行っていたチャンネルであればデータ追加
    if (m_channel->hasReceivedMessage(message->getChannelName())){
        m_channel->pushLog(message->getChannelName(), message);
    }
}

// チャンネル参加ストリームを受信
void CChatServiceBase::onGetJoinStream(const wxString& channel,
        const wxString& name)
{
    // 処理待ちに追加

    wxString nick = m_nickTable->getNickname(name);

    // ニックネームが未知の場合、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(name)){
        m_connect->startGetMemberInfoTask(m_user, name);
    }

    // 既に受信を行っていたチャンネルであればメンバーを追加
    if (m_channel->hasReceivedMember(channel)){
        m_channel->pushMember(channel, CMemberData(name, nick));
    }

    // 自分が参加したとき(別クライアントソフトから)
    if (name == m_user->getUserName()){

        // チャンネル情報取得タスクの開始
        m_connect->startGetChannelTask(m_user);
    }
}

// チャンネル離脱ストリームを受信
void CChatServiceBase::onGetPartStream(const wxString& channel,
        const wxString& name)
{
    // データ更新
    m_channel->popMember(channel, name);

    // ニックネームが未知の時、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(name)){
        m_connect->startGetMemberInfoTask(m_user, name);
    }
}

// チャンネル情報更新ストリームを受信
void CChatServiceBase::onGetChannelStream(const wxString& channelName,
        const wxString& topic)
{
    m_channel->setChannel(channelName, topic);
}

// ユーザ情報更新ストリームの受信
void CChatServiceBase::onGetUserStream(const wxString& userName,
        const wxString& nick)
{
    m_channel->updateMember(userName, nick);
    (*m_nickTable)[userName] = nick;
}

}
