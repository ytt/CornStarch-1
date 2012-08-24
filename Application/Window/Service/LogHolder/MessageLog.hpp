#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{
;

// メッセージのログ
class CMessageLog: public CServiceLog
{
private:
    bool m_isReaded;
    int m_id;
    wxString m_body;

public:
    CMessageLog(void);
    ~CMessageLog(void);
    void init(const CMessageData* message);

    wxString getBody() const
    {
        return m_body;
    }

    void setBody(wxString body)
    {
        m_body = body;
    }

    int getId() const
    {
        return m_id;
    }

    void setId(int id)
    {
        m_id = id;
    }

    bool isReaded() const
    {
        return m_isReaded;
    }

    void setReaded(bool isReaded)
    {
        m_isReaded = isReaded;
    }
};

}
