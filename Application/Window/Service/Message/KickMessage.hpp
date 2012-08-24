#ifndef KICKLOG_HPP_
#define KICKLOG_HPP_
#include "Message.hpp"
namespace CornStarch
{;

class CKickMessage:public CMessage
{

    wxString m_target; // ユーザ名
public:
    CKickMessage();
    virtual ~CKickMessage();


    wxString getTarget() const
    {
        return m_target;
    }

    void setTarget(wxString target)
    {
        m_target = target;
    }
};
}
#endif /* KICKLOG_HPP_ */
