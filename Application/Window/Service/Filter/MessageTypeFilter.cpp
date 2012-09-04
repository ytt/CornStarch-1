#include "MessageTypeFilter.hpp"
#include<typeinfo>
namespace CornStarch
{

CMessageTypeFilter::CMessageTypeFilter()
{

}

CMessageTypeFilter::~CMessageTypeFilter()
{
}

bool CMessageTypeFilter::isValid(const CMessage* message)const
{
    if (wxString(typeid ( *message ).name()) == m_typeInfoName)
    {
        return !isAntiFilter();
    }
    return isAntiFilter();
}
} /* namespace CornStarch */
