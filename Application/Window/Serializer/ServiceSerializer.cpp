#include <wx/filedlg.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "ServiceSerializer.hpp"
#include "../Service/ServiceConfiguration.hpp"
#include "../Service/Filter/UserNameFilter.hpp"
#include "../Service/Filter/MessageTypeFilter.hpp"
#include "../Service/Filter/DateTimeFilter.hpp"


using namespace std;

namespace CornStarch
{
;
#ifdef _WIN32
const wxString CServiceSerializer::PATH = wxString(getenv("USERPROFILE"))
        + "/.CornStarch";
#endif
#ifndef _WIN32
const wxString CServiceSerializer::PATH = wxString(getenv("HOME"))
        + "/.CornStarch";

#endif
CServiceSerializer::CServiceSerializer(void) :
        m_doc(NULL)
{
}

CServiceSerializer::~CServiceSerializer(void)
{
    delete m_doc;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CServiceSerializer::init(void)
{
    m_doc = new wxXmlDocument();
}
// サービスを受け取り、ファイルに保存する
void CServiceSerializer::saveService(
        const map<int, CChatServiceBase*>& services, const wxString& path)
{
    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, "root");

    // 各サービスについて
    map<int, CChatServiceBase*>::const_reverse_iterator it;
    for (it = services.rbegin(); it != services.rend(); it++){

        // サービス情報をRootノードに追加
        serializeService(root, it->second);
    }

    m_doc->SetRoot(root);
    if (path == ""){
        m_doc->Save(PATH);

#ifndef _WIN32
chmod(PATH, S_IRUSR | S_IWUSR);
#endif
    } else{
        m_doc->Save(path);
    }
}

// 保存されたサービス情報を基に、vectorにpushする
void CServiceSerializer::loadService(wxEvtHandler* handler,
        map<int, CChatServiceBase*>& services, int& serviceId,
        const wxString& path)
{
    wxString location = path;
    if (path == ""){
        location = PATH;
    }

    // ファイルが存在しない時
    if (!wxFileExists(location)){
        return;
    }

    // ファイルの読み込みに失敗
    if (!m_doc->Load(location)){
        return;
    }

    // ファイルからサーバ情報を読み込み、サービスを作成
    wxXmlNode* child = m_doc->GetRoot()->GetChildren();
    while (child){

        // サービスを作成して追加
        CChatServiceBase* service = deserializeServce(child, handler,
                serviceId);
        services.insert(
                map<int, CChatServiceBase*>::value_type(service->getId(),
                        service));

        // 次のサーバ情報の読み込み
        serviceId++;
        child = child->GetNext();
    }
}

//////////////////////////////////////////////////////////////////////

// XMLNodeからサービスを作成する
CChatServiceBase* CServiceSerializer::deserializeServce(wxXmlNode* node,
        wxEvtHandler* handler, int& serviceId)
{
    // サービス作成
    CChatServiceBase* service;
    if (node->GetName() == "StarChat"){ // StarChat
        service = new StarChat::CSCService();
    } else if (node->GetName() == "IRC"){ // IRC
        service = new IRC::CIRCService();
    }

    // 各タグの情報を取得
    wxXmlNode* status = node->GetChildren();
    wxString nick, name, pass, host, user;
    long port;
    CServiceConfiguration* configuration = NULL;
    vector<wxString> channels;
    while (status){

        // タグ情報の読み込み
        wxString tag = status->GetName();
        if (tag == "user"){
            user = status->GetNodeContent();
        } else if (tag == "pass"){
            pass = status->GetNodeContent();
        } else if (tag == "name"){
            name = status->GetNodeContent();
        } else if (tag == "host"){
            host = status->GetNodeContent();
        } else if (tag == "port"){
            status->GetNodeContent().ToLong(&port);
        } else if (tag == "configuration"){
            configuration = deserializeConfiguration(status);
        } else if (tag == "channels"){
            wxXmlNode* channel = status->GetChildren();
            while (channel){
                channels.push_back(channel->GetNodeContent());
                channel = channel->GetNext();
            }
        }
        // 次のタグへ
        status = status->GetNext();
    }
    if (configuration == NULL){
        configuration = new CServiceConfiguration();
    }
    // サービスのパラメータを代入
    service->setId(serviceId);
    service->init(handler);
    service->setName(name);
    service->setPort(port);
    service->setHost(host);
    service->setConfiguration(configuration);
    service->setSavedChannels(channels);
    service->registerUserBasiscEncoded(user, pass);
    if (configuration->isAutoConnect()){
        service->connect();
    }
    return service;
}

CServiceConfiguration* CServiceSerializer::deserializeConfiguration(
        const wxXmlNode* node)
{
    CServiceConfiguration* configuration = new CServiceConfiguration();

    wxXmlNode* child = node->GetChildren();
    while (child){
        if (child->GetName() == "isAuto"){
            // 自動接続
            configuration->setAutoConnect(child->GetNodeContent() == "1");
        }
        if (child->GetName() == "fontsize"){
            // フォントサイズ
            long size;
            child->GetNodeContent().ToLong(&size);
            configuration->setFontSize(size);
        }
        if (child->GetName() == "filters"){
            // フィルター
            wxXmlNode* filterNode = child->GetChildren();

            while (filterNode){
                wxString channelName = filterNode->GetAttribute("name", "");
                wxXmlNode* filterChild = filterNode->GetChildren();
                CFilterBase* filter = NULL;
                bool isAnti;
                wxString filterName;
                wxString filterValue;

                while (filterChild){
                    wxXmlNode* filterElement = filterChild->GetChildren();
                    while (filterElement){
                        if (filterElement->GetName() == "name"){
                            filterName = filterElement->GetNodeContent();
                        } else if (filterElement->GetName() == "isAnti"){
                            isAnti = (filterElement->GetNodeContent() == "1");
                        } else if (filterElement->GetName() == "target"){
                            filterValue = filterElement->GetNodeContent();
                        } else if (filterElement->GetName() == "type"){
                            // typeidからのインスタンス生成
                            if (filterElement->GetNodeContent()
                                    == typeid(CUserNameFilter).name()){
                                CUserNameFilter* nameFilter =
                                        new CUserNameFilter();
                                nameFilter->setUserName(filterValue);
                                filter = nameFilter;

                            } else if (filterElement->GetNodeContent()
                                    == typeid(CMessageTypeFilter).name()){
                                CMessageTypeFilter* nameFilter =
                                        new CMessageTypeFilter();
                                nameFilter->setTypeInfoName(filterValue);
                                filter = nameFilter;
                            } else if (filterElement->GetNodeContent()
                                    == typeid(CDateTimeFilter).name()){

                                long time;
                                filterValue.ToLong(&time);
                                CDateTimeFilter* nameFilter =
                                        new CDateTimeFilter();
                                nameFilter->setDate(wxDateTime((time_t) time));
                                filter = nameFilter;
                            }
                        }
                        filterElement = filterElement->GetNext();

                    }
                    filterChild = filterChild->GetNext();
                    if (filter != NULL){
                        filter->setAntiFilter(isAnti);
                        filter->setName(filterName);
                        configuration->addFilter(channelName, filter);
                    }
                }

                filterNode = filterNode->GetNext();
            }
        }
        child = child->GetNext();
    }
    return configuration;
}

void CServiceSerializer::createNode(wxXmlNode* parent, wxString name,
        wxString content)
{
    wxXmlNode* server1 = new wxXmlNode(parent, wxXML_ELEMENT_NODE, name);
    new wxXmlNode(server1, wxXML_TEXT_NODE, "text", content);
}
// サービス情報をRootノードに追加
void CServiceSerializer::serializeService(wxXmlNode* root,
        const CChatServiceBase* service)
{
    wxXmlNode* serverRoot;
    if (service->getChatType() == CChatServiceBase::STAR_CHAT){

        // StarChatのとき
        serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "StarChat");

    } else{
        // IRCのとき
        serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "IRC");
    }
    createNode(serverRoot, "name", service->getName());
    createNode(serverRoot, "host", service->getHost());
    wxString portString;
    portString << service->getPort();
    createNode(serverRoot, "port", portString);

    createNode(serverRoot, "user", service->getUser()->getUserName());
    createNode(serverRoot, "pass", service->getUser()->getBasic());
    createNode(serverRoot, "nick", service->getUser()->getUserName());

    if (service->getChatType() == CChatServiceBase::IRC){

        wxXmlNode* server4 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE,
                "channels");
        vector<CChannelStatus*> channels = service->getChannels();
        vector<CChannelStatus*>::iterator it = channels.begin();
        while (it != channels.end()){
            wxXmlNode* channel = new wxXmlNode(server4, wxXML_ELEMENT_NODE,
                    "channel");
            new wxXmlNode(channel, wxXML_TEXT_NODE, "text",
                    (*it)->getChannelName());
            it++;
        }
    }
    serializeConfiguration(serverRoot, service);
}
// 設定をサービスノードに追加
void CServiceSerializer::serializeConfiguration(wxXmlNode* root,
        const CChatServiceBase* service)
{
    wxXmlNode* parentNode = new wxXmlNode(root, wxXML_ELEMENT_NODE,
            "configuration");
    // 自動接続
    wxString autoString;
    autoString << service->getConfiguration()->isAutoConnect();
    createNode(parentNode, "isAuto", autoString);
    // フォントサイズ
    wxString fontString;
    fontString << service->getConfiguration()->getFontSize();
    createNode(parentNode, "fontsize", fontString);

    // フィルター一覧
    wxXmlNode* filtersNode = new wxXmlNode(parentNode, wxXML_ELEMENT_NODE,
            "filters");
    vector<CChannelStatus*> channels = service->getChannels();
    vector<CChannelStatus*>::iterator it = channels.begin();
    while (it != channels.end()){

        wxXmlNode* channelNode = new wxXmlNode(filtersNode, wxXML_ELEMENT_NODE,
                "channel");
        channelNode->SetAttributes(
                new wxXmlAttribute("name", (*it)->getChannelName()));

        // フィルター
        vector<IFilter*>* filters = service->getConfiguration()->getFilters(
                (*it)->getChannelName());
        vector<IFilter*>::reverse_iterator itFilter = filters->rbegin();
        while (itFilter != filters->rend()){
            wxXmlNode* filterNode = new wxXmlNode(channelNode,
                    wxXML_ELEMENT_NODE, "filter");

            createNode(filterNode, "type", typeid(*(*itFilter)).name());
            createNode(filterNode, "name", (*itFilter)->getName());
            wxString isAntiString;
            isAntiString << (*itFilter)->isAntiFilter();
            createNode(filterNode, "isAnti", isAntiString);
            if (typeid(*(*itFilter)) == typeid(CMessageTypeFilter)){
                // メッセージフィルター
                CMessageTypeFilter* filter =
                        dynamic_cast<CMessageTypeFilter*>(*itFilter);
                createNode(filterNode, "target", filter->getTypeInfoName());
            } else if (typeid(*(*itFilter)) == typeid(CUserNameFilter)){
                // ユーザーフィルター
                CUserNameFilter* filter =
                        dynamic_cast<CUserNameFilter*>(*itFilter);
                createNode(filterNode, "target", filter->getUserName());
            } else if (typeid(*(*itFilter)) == typeid(CDateTimeFilter)){
                // 日付フィルター
                CDateTimeFilter* filter =
                        dynamic_cast<CDateTimeFilter*>(*itFilter);
                wxString time;
                time << filter->getDate().GetTicks();
                createNode(filterNode, "target", time);
            }
            itFilter++;
        }

        it++;
    }

}
}
