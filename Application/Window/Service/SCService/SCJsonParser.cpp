#include "SCJsonParser.hpp"
#include "SCResponseData.hpp"

using namespace std;
using namespace picojson;

namespace CornStarch
{
;
namespace StarChat
{
;

CSCJsonParser::CSCJsonParser(void)
{
}

CSCJsonParser::~CSCJsonParser(void)
{
}

//////////////////////////////////////////////////////////////////////

// メンバの一覧をvectorとして返す
vector<CMemberData*> CSCJsonParser::getMembers(const string& json) const
{
    vector<CMemberData*> result;

    // jsonを解析したarrayを取得
    array arr = getArray(parseSCJson(json));

    // 各メンバについてループ
    int size = (int) arr.size();
    for (int i = 0; i < size; i++){

        // パラメータの取得
        CMemberData* mem = new CMemberData();
        mem->m_name = wxString(arr[i].get("name").get<string>().c_str(),
                wxConvUTF8); // 名前(name)
        mem->m_nick = wxString(arr[i].get("nick").get<string>().c_str(),
                wxConvUTF8); // ニックネーム(name)

        // vectorに追加
        result.push_back(mem);
    }

    return result;
}

// チャンネル一覧をvectorとして返す
vector<CChannelData*> CSCJsonParser::getChannels(const string& json) const
{
    vector<CChannelData*> result;

    // jsonを解析したarrayを取得
    array arr = getArray(parseSCJson(json));

    // 各チャンネルについてループ
    int size = (int) arr.size();
    for (int i = 0; i < size; i++){

        // パラメータの取得
        CChannelData* cn = new CChannelData();
        cn->m_name = wxString(arr[i].get("name").get<string>().c_str(),
                wxConvUTF8); // チャンネル名(name)
        if (arr[i].get("topic")){ // topic(あれば)
            cn->m_topic = wxString(
                    arr[i].get("topic").get("body").get<string>().c_str(),
                    wxConvUTF8);
        } else{
            cn->m_topic = "";
        }

        // vectorに追加
        result.push_back(cn);
    }

    return result;
}

// メッセージ一覧をvectorとして返す
vector<CResponseData*> CSCJsonParser::getMessages(const string& json) const
{
    vector<CResponseData*> result;

    // jsonを解析したarrayを取得
    array arr = getArray(parseSCJson(json));

    // 各メッセージについてループ
    int size = (int) arr.size();
    for (int i = 0; i < size; i++){

        // パラメータの取得
        CResponseData* msg = new CResponseData();
        msg->m_id = arr[i].get("id").get<double>(); // メッセージID
        msg->m_username = wxString(
                arr[i].get("user_name").get<string>().c_str(), wxConvUTF8); // 発言者
        msg->m_body = wxString(arr[i].get("body").get<string>().c_str(),
                wxConvUTF8); // 本文
        msg->m_channel = wxString(
                arr[i].get("channel_name").get<string>().c_str(), wxConvUTF8); // 投稿チャンネル
        msg->m_time = (time_t) arr[i].get("created_at").get<double>(); // 作成UNIX時
        if (arr[i].get("temporary_nick")){ // テンポラリニックネーム(あれば)
            msg->m_tempNick = wxString(
                    arr[i].get("temporary_nick").get<string>().c_str(),
                    wxConvUTF8);
        }

        // vectorに追加
        result.push_back(msg);
    }

    return result;
}

// メンバ情報を返す
CMemberData CSCJsonParser::getMember(const string& json) const
{
    // jsonの解析
    value v = parseSCJson(json);

    CMemberData member;

    // パラメータの取得
    member.m_name = wxString(v.get("name").get<string>().c_str(), wxConvUTF8); // 名前
    member.m_nick = wxString(v.get("nick").get<string>().c_str(), wxConvUTF8); // ニックネーム

    if (v.get("keywords")){
        array arr = v.get("keywords").get<array>();
        size_t size = arr.size();
        for (size_t i = 0; i < size; i++){
            member.m_keywords.push_back(
                    wxString(arr[i].get<string>().c_str(), wxConvUTF8)); // キーワード
        }
    }

    return member;
}

// ストリームを返す
CSCResponseData* CSCJsonParser::getStreamData(const string& json) const
{

    // 文字列が空の場合
    if (json == ""){
        // ストリームはないと判断する
        return NULL;
    }

    // ストリームの種類を取得
    value content = parseSCJson(json);
    CSCMessageType::SC_MESSAGE_TYPE type = getStreamType(content);

    CSCResponseData* result = new CSCResponseData();
    value val;
    // ストリームの種類により分岐
    switch (type) {
    case CSCMessageType::MESSAGE: // メッセージの投稿があった
        // メッセージの取得
        val= content.get("message");

        // 値を取得する
        result->m_type = CSCMessageType::MESSAGE;
        result->m_id = val.get("id").get<double>();
        result->m_username = wxString(
                val.get("user_name").get<string>().c_str(), wxConvUTF8);
        result->m_body = wxString(
                val.get("body").get<string>().c_str(), wxConvUTF8);
        result->m_channel = wxString(
                val.get("channel_name").get<string>().c_str(), wxConvUTF8);
        result->m_time =
                (time_t) val.get("created_at").get<double>();
        if (val.get("temporary_nick")){ // テンポラリニックネーム(あれば)
            result->m_tempNick = wxString(
                    val.get("temporary_nick").get<string>().c_str(),
                    wxConvUTF8);
        }
        break;

    case CSCMessageType::JOIN: // チャンネルにメンバー追加

        result->m_type =CSCMessageType::JOIN;
        result->m_username = wxString(
                content.get("user_name").get<string>().c_str(), wxConvUTF8);
        result->m_channel = wxString(
                content.get("channel_name").get<string>().c_str(), wxConvUTF8);
        break;

    case CSCMessageType::PART: // チャンネルからメンバー離脱

        result->m_type  =CSCMessageType::PART;
        result->m_username= wxString(
                content.get("user_name").get<string>().c_str(), wxConvUTF8);
        result->m_channel= wxString(
                content.get("channel_name").get<string>().c_str(), wxConvUTF8);
        break;

    case CSCMessageType::TOPIC: // チャンネル情報更新

        val = content.get("channel");

        result->m_type  =CSCMessageType::TOPIC;
        result->m_channelData.m_name= wxString(
                val.get("name").get<string>().c_str(), wxConvUTF8);
        result->m_channelData.m_topic= wxString(
                val.get("topic").get("body").get<string>().c_str(),
                wxConvUTF8);
        break;

    case CSCMessageType::NICK: // ユーザ情報更新

        val= content.get("user");

        result->m_type  =CSCMessageType::NICK;
        result->m_member.m_name = wxString(
                val.get("name").get<string>().c_str(), wxConvUTF8);
        result->m_member.m_nick = wxString(
                val.get("nick").get<string>().c_str(), wxConvUTF8);
        break;

    default: // 解析不能
        delete result;
        return NULL;
    }
    return result;

}

// pingが成功したか否かを返す
bool CSCJsonParser::isPingSucceeded(const string& body) const
{
    // pongが見つからなければ
    if (body.find("pong") == string::npos){
        return false;
    }
    return true;
}

// 複数行のJSONを、vector形式に変換する
vector<string> CSCJsonParser::getJsonVec(const string& jsons)
{
    vector<string> result;
    string buffer = jsons;

    // 空文字列のとき
    if (jsons == ""){
        return result;
    }

    while (1){

        // これ以上JSON部分がない
        if (buffer.find("\r\n") == 0){
            break;
        }

        // JSON部分をresultにセット
        int pos = buffer.find("\n");
        result.push_back(buffer.substr(0, pos));

        // bufferを更新
        buffer = buffer.substr(pos + 1);
    }
    return result;
}

//////////////////////////////////////////////////////////////////////

// ストリームのvalueから、ストリームタイプを得る
CSCMessageType::SC_MESSAGE_TYPE CSCJsonParser::getStreamType(const value& val) const
{
    // 形式が不正
    if (!val.is<object>()){
        return CSCMessageType::UNKNOWN;
    }

    // タイプを文字列で取得
    wxString str = val.get("type").get<string>();
    if (str == "message"){ // メッセージが投稿
        return CSCMessageType::MESSAGE;
    } else if (str == "delete_subscribing"){ // チャンネルにメンバー参加
        return CSCMessageType::JOIN;
    } else if (str == "subscribing"){ // チャンネルからメンバー離脱
        return CSCMessageType::PART;
    } else if (str == "channel"){ // チャンネル情報更新
        return CSCMessageType::TOPIC;
    } else if (str == "user"){ // ユーザ情報変更
        return CSCMessageType::NICK;
    }

    // 解析できなかった
    return CSCMessageType::UNKNOWN;
}

// valueを解析してarrayとして返す
array CSCJsonParser::getArray(const value& val) const
{
    // array形式であれば
    if (val.is<array>()){

        // arrayを返す
        return val.get<array>();
    }

    // 空のarrayを返す
    return array();
}

// jsonを解析してvalueとして返す
value CSCJsonParser::parseSCJson(const string& json) const
{
    // 文字列の解析
    value v;
    const char* str = json.c_str();
    picojson::parse(v, str, str + strlen(str));

    // 解析結果
    return v;
}

}
}
