#ifndef FILTERBASE_HPP_
#define FILTERBASE_HPP_
#include "IFilter.hpp"

namespace CornStarch
{
// フィルターの基底クラス
class CFilterBase:public IFilter
{
    // フィルタ名
    wxString m_name;
    // フィルタが有効時でないときのフィルタ
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
