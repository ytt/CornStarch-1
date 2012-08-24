#pragma once
#include "Message.hpp"
#include "../../../DataStruct/ResponseData.hpp"


namespace CornStarch
{
;

// メッセージのログ
class CChatMessage: public CMessage
{
private:
    bool m_isReaded;
    int m_id;
    wxString m_body;

public:
    CChatMessage(void);
    ~CChatMessage(void);
    void init(const CResponseData* message);

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
