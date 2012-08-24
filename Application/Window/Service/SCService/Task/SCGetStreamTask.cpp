#include "SCGetStreamTask.hpp"

using namespace std;
#include "../../ConnectionStatusChecker.h"
namespace CornStarch
{
;
namespace StarChat
{
;

CSCGetStreamTask::CSCGetStreamTask(void) :
        CSCTask(wxTHREAD_JOINABLE)
{
}

CSCGetStreamTask::~CSCGetStreamTask(void)
{
}

// メインループ
wxThread::ExitCode CSCGetStreamTask::Entry()
{
    // クライアントの初期化
    CSCClient* client = new CSCClient();
    client->init();
    client->setHost(m_host);
    client->setPort(m_port);
    client->connect();
    client->sendGetStreamRequest(m_userName, m_basic);
    client->recvHttpResponseBody();

    // Statusチェックの間隔計測
    //CConnectionStatusChecker checker(m_observer);
    // Deleteされるまでループ
    while (!TestDestroy()){

        // CPUを休ませる(100msec)
        wxUsleep(100);

        // ストリーム(JSON形式)を受信
        CSCJsonParser parser;
        string jsons = client->getStreamJson();
        vector<string> jsonVec = parser.getJsonVec(jsons);

        // 各JSONを解析して、イベントを送信する
        size_t size = jsonVec.size();
        if (size != 0){
            for (size_t i = 0; i < size; i++){
                CSCResponseData* message = parseStream(jsonVec[i]);
                if (message != NULL){
                    m_observer->onMessageReceived(message);
                    delete message;
                }
            }
            // サーバーのステータスチェック計測のリセット
            //checker.refreshCount();
        }
        //checker.tick();
    }

    // 後処理
    client->close();
    delete client;

    // 成功時
    return (wxThread::ExitCode) 0;
}

//////////////////////////////////////////////////////////////////////

// Streamの内容からイベントを作成する
CSCResponseData* CSCGetStreamTask::parseStream(const string& json)
{
    // JSONのパース
    CSCJsonParser parser;
    CSCResponseData* message = parser.getStreamData(json);
    return message;
}

}
}
