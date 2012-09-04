#ifndef SERVICECONFIGURATION_HPP_
#define SERVICECONFIGURATION_HPP_

namespace CornStarch
{

class CServiceConfiguration
{
    // 開始後すぐに接続するか
    bool m_isAutoConnect;
    // フォントサイズ
    int m_fontSize;
public:
    CServiceConfiguration();
    virtual ~CServiceConfiguration();

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
};

} /* namespace CornStarch */
#endif /* SERVICECONFIGURATION_HPP_ */
