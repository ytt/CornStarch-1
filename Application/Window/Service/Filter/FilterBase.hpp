#ifndef FILTERBASE_HPP_
#define FILTERBASE_HPP_
#include "IFilter.hpp"

namespace CornStarch
{

class CFilterBase:public IFilter
{
    wxString m_name;
    bool m_isAntiFilter;

public:
    CFilterBase();
    virtual ~CFilterBase();

    wxString getName() const
    {
        return m_name;
    }

    void setName(wxString name)
    {
        m_name = name;
    }

    bool isAntiFilter() const
    {
        return m_isAntiFilter;
    }

    void setAntiFilter(bool isAntiFilter)
    {
        m_isAntiFilter = isAntiFilter;
    }
};

} /* namespace CornStarch */
#endif /* FILTERBASE_HPP_ */
