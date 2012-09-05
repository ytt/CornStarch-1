
#ifndef USERNAMEFILTER_HPP_
#define USERNAMEFILTER_HPP_

#include "FilterBase.hpp"
namespace CornStarch
{
// ユーザー名でのフィルタ
class CUserNameFilter: public CFilterBase
{
    //　ユーザー名
    wxString m_userName;
public:
    CUserNameFilter();
    virtual ~CUserNameFilter();
    bool isValid(const CMessage* message)const;

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }
};

} /* namespace CornStarch */
#endif /* USERNAMEFILTER_HPP_ */
