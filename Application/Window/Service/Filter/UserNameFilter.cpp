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
    if (message->getNick() == m_userName){
        return !isAntiFilter();
    }
    return isAntiFilter();
}
} /* namespace CornStarch */