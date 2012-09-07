#pragma once
#ifndef _WIN32
#include <wx/xml/xml.h>
#include <map>
#include "../Service/IRCService/IRCService.hpp"
#include "../Service/SCService/SCService.hpp"
#include <sys/stat.h>

namespace CornStarch
{
;

// サービスのシリアライズを行うクラス
class CServiceSerializer
{
private:
    wxXmlDocument* m_doc;
    static const wxString PATH;

public:
    CServiceSerializer(void);
    ~CServiceSerializer(void);

    // 初期化を行う
    void init(void);
    // サービスを受け取り、ファイルに保存する
    void saveService(const std::map<int, CChatServiceBase*>& services,
            const wxString& path = "");

    // 保存されたサービス情報を基に、vectorにpushする
    void loadService(wxEvtHandler* handler,
            std::map<int, CChatServiceBase*>& services, int& serviceId);

private:
    void createNode(wxXmlNode* parent, wxString name, wxString content);
    // XMLNodeからサービスを作成する
    CChatServiceBase* deserializeServce(wxXmlNode* node, wxEvtHandler* handler,
            int& serviceId);
    // XMLノードから設定を作成する
    CServiceConfiguration* deserializeConfiguration(const wxXmlNode* node);
    // サービス情報をRootノードに追加
    void serializeService(wxXmlNode* root, const CChatServiceBase* service);
    // 設定をサービスノードに追加
    void serializeConfiguration(wxXmlNode* root,
            const CChatServiceBase* service);
};

}
#endif
