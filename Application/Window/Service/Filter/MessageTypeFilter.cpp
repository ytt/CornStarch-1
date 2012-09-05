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
    wxString typeName =wxString(typeid ( *message ).name());
    if (typeName == m_typeInfoName)
    {
        return !isAntiFilter();
    }
    return isAntiFilter();
}
} /* namespace CornStarch */
