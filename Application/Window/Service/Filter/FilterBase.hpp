#ifndef FILTERBASE_HPP_
#define FILTERBASE_HPP_
#include "IFilter.hpp"

namespace CornStarch
{

class CFilterBase:public IFilter
{
    bool m_isAntiFilter;
public:
    CFilterBase();
    virtual ~CFilterBase();

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
