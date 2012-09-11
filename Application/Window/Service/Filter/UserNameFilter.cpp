#include "UserNameFilter.hpp"

namespace CornStarch
{

CUserNameFilter::CUserNameFilter()
{
}

CUserNameFilter::~CUserNameFilter()
{
}
bool CUserNameFilter::isValid(const CMessage* message) const
{
    // ユーザー名、ニックネーム、一時ニックネームのどれかが指定した値かどうか
    if (message->getNick() == m_userName|| message->getTempNick() == m_userName
            || message->getUserName() == m_userName){
        return !isAntiFilter();
    }
    return isAntiFilter();
}
} /* namespace CornStarch */
