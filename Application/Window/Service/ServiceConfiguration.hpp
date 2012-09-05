#ifndef SERVICECONFIGURATION_HPP_
#define SERVICECONFIGURATION_HPP_
#include <vector>
#include <map>
#include "Filter/IFilter.hpp"
#include "wx/wx.h"

using namespace std;
namespace CornStarch
{

class CServiceConfiguration
{
    // 自動接続するか
    bool m_isAutoConnect;
    // 文字サイズ
    int m_fontSize;
    // フィルター
    map<wxString, vector<IFilter*>*> m_filters;

public:
    CServiceConfiguration();
    virtual ~CServiceConfiguration();

    void addDefaultFilter(const wxString& channelName);
    vector<IFilter*>* getFilters(const wxString& channelName) const
    {
        map<wxString, vector<IFilter*>*>::const_iterator it = m_filters.find(
                channelName);
        if (it != m_filters.end()){
            return (*it).second;
        }
        return NULL;
    }

    bool isAutoConnect() const
    {
        return m_isAutoConnect;
    }

    void setAutoConnect(bool isAutoConnect)
    {
        m_isAutoConnect = isAutoConnect;
    }
    int getFontSize() const
    {
        return m_fontSize;
    }

    void setFontSize(int fontSize)
    {
        m_fontSize = fontSize;
    }
    // フィルターの追加
    void addFilter(const wxString& channelName, IFilter* filter);
    // フィルターの削除
    void removeFilter(const wxString& channelName, const wxString filterName);

};

} /* namespace CornStarch */
#endif /* SERVICECONFIGURATION_HPP_ */
