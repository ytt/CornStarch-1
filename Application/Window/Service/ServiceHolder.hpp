#ifndef SERVICEHOLDER_HPP_
#define SERVICEHOLDER_HPP_
#include <map>
#include "ChatServiceBase.hpp"
#include "wx/wx.h"

using namespace std;

namespace CornStarch
{

class CServiceHolder
{
    // 最後に割り振った一意なサービスID
    int m_uniqueServiceId;
    // 現在選択しているさービスID
    int m_currentServiceId;
    // 通信要素
    map<int, CChatServiceBase*> m_services;

public:
    CServiceHolder();
    virtual ~CServiceHolder();

    // チャンネルを削除する
    void deleteService(int serviceId);
    // チャンネルを削除する
    void deleteChannel(int serviceId, wxString channel);
    // 新規サービスを追加
    void addNewService(CChatServiceBase* service);
    // サービスを再読み込みする。
    void updateService(int serviceId);
    // サービスを切断する
    void disconnect(int serviceId);
    // IDからサービスを取得する
    CChatServiceBase* getService(int serviceId);

    int getCurrentServiceId() const
    {
        return m_currentServiceId;
    }

    void setCurrentServiceId(int currentServiceId)
    {
        m_currentServiceId = currentServiceId;
    }

    int getUniqueServiceId() const
    {
        return m_uniqueServiceId;
    }

    void setUniqueServiceId(int uniqueServiceId)
    {
        m_uniqueServiceId = uniqueServiceId;
    }
};

} /* namespace CornStarch */
#endif /* SERVICEHOLDER_HPP_ */
