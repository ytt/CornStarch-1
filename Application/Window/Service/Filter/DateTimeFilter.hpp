
#ifndef DATETIMEFILTER_HPP_
#define DATETIMEFILTER_HPP_
#include <wx/datetime.h>
#include "FilterBase.hpp"

namespace CornStarch
{

class CDateTimeFilter:public CFilterBase
{
    wxDateTime m_date;
public:
    CDateTimeFilter();
    virtual ~CDateTimeFilter();
    bool isValid(const CMessage* message)const;

    wxDateTime getDate() const
    {
        return m_date;
    }

    void setDate(wxDateTime date)
    {
        m_date = date;
    }


};

} /* namespace CornStarch */
#endif /* DATETIMEFILTER_HPP_ */
