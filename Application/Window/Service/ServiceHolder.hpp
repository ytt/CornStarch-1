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
    int m_uniqueServiceId;
    int m_currentServiceId;
    map<int, CChatServiceBase*> m_services;

public:
    CServiceHolder();
    virtual ~CServiceHolder();
    // サービスの削除
    void deleteService(int serviceId);
    // チャンネルの削除
    void deleteChannel(int serviceId, wxString channel);
    // 新規サービスの追加
    void addNewService(CChatServiceBase* service, wxEvtHandler* hander);
    // サービスの取得
    CChatServiceBase* getService(int serviceId) const;

    map<int, CChatServiceBase*> getServices() const
    {
        return m_services;
    }

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
    // 設定の読み込み
    void load(wxEvtHandler* handler);
    // 設定の書き込み
    void save();

    // サービスの保存
    void exportService(const wxString& path);
    // サービスの読み込み
    void importService();
};

} /* namespace CornStarch */
#endif /* SERVICEHOLDER_HPP_ */
