#include "DateTimeFilter.hpp"

namespace CornStarch
{

CDateTimeFilter::CDateTimeFilter()
{
}

CDateTimeFilter::~CDateTimeFilter()
{
}

bool CDateTimeFilter::isValid(const CMessage* message) const
{
    wxDateTime messageTime(message->getTime());
    if (messageTime.IsSameDate(m_date)){
        return !isAntiFilter();
    }
    return isAntiFilter();
}
} /* namespace CornStarch */
