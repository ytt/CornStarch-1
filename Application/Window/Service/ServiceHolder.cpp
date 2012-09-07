#include "ServiceHolder.hpp"
#include "../Serializer/ServiceSerializer.hpp"
#include "../Serializer/ServiceSerializerWin.hpp"
namespace CornStarch
{

CServiceHolder::CServiceHolder() :
        m_uniqueServiceId(0), m_currentServiceId(0)
{
}

CServiceHolder::~CServiceHolder()
{
    deleteServices();
}
void CServiceHolder::deleteServices()
{
    map<int, CChatServiceBase*>::iterator it = m_services.begin();
    while (it != m_services.end()){
        delete (*it).second;
        ++it;
    }
}
// チャンネルを削除する
void CServiceHolder::deleteChannel(int serviceId, wxString channel)
{
    CChatServiceBase* contents = getService(serviceId);
    if (contents != NULL){
        contents->partChannel(channel);
    }
}
// サービスの読み込み
void CServiceHolder::load(wxEvtHandler* handler)
{
    // シリアライズされたサービスを読み込み
    CServiceSerializer serializer;
    serializer.init();
    serializer.loadService(handler, m_services, m_uniqueServiceId);
}
// サービスの保存
void CServiceHolder::save()
{
    // ファイルに保存
    CServiceSerializer serializer;
    serializer.init();
    serializer.saveService(m_services);
}

// サービスの保存
void CServiceHolder::exportService(const wxString& path)
{
    // ファイルに保存
    CServiceSerializer serializer;
    serializer.init();
    serializer.saveService(m_services, path);
}
// サービスの読み込み
void CServiceHolder::importService(wxEvtHandler* handler, const wxString& path)
{
    deleteServices();
    m_services.clear();
    m_uniqueServiceId = 0;
    m_currentServiceId = 0;
    // ファイルから読み込み
    CServiceSerializer serializer;
    serializer.init();
    serializer.loadService(handler, m_services, m_currentServiceId, path);
}
// IDからサービスを取得する
CChatServiceBase* CServiceHolder::getService(int serviceId) const
{
    map<int, CChatServiceBase*>::const_iterator it = m_services.find(serviceId);
    if (it != m_services.end()){
        return (*it).second;
    }
    return NULL;
}
// 新規サービスの追加
void CServiceHolder::addNewService(CChatServiceBase* service,
        wxEvtHandler* hander)
{
    service->setId(m_uniqueServiceId);
    m_uniqueServiceId++;
    service->init(hander);
    m_services.insert(
            map<int, CChatServiceBase*>::value_type(service->getId(), service));
    if (service->getConfiguration()->isAutoConnect()){
        service->connect();
    }
}

// チャンネルを削除する
void CServiceHolder::deleteService(int serviceId)
{
    CChatServiceBase* service = getService(serviceId);
    if (service){
        delete service;
        m_services.erase(serviceId);
    }
}
} /* namespace CornStarch */
