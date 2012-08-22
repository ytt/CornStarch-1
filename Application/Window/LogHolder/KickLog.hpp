#ifndef KICKLOG_HPP_
#define KICKLOG_HPP_
#include "ServiceLog.hpp"
namespace CornStarch
{;

class CKickLog:public CServiceLog
{

    wxString m_target; // ユーザ名
public:
    CKickLog();
    virtual ~CKickLog();


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
