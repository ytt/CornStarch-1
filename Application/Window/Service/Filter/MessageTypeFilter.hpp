
#ifndef MESSAGETYPEFILTER_HPP_
#define MESSAGETYPEFILTER_HPP_
#include "FilterBase.hpp"
namespace CornStarch
{
// メッセージタイプでのフィルタ
class CMessageTypeFilter:public CFilterBase
{
    wxString m_typeInfoName;
public:
    CMessageTypeFilter();
    virtual ~CMessageTypeFilter();
    bool isValid(const CMessage* message)const;

    wxString getTypeInfoName() const
    {
        return m_typeInfoName;
    }

    void setTypeInfoName(wxString typeInfoName)
    {
        m_typeInfoName = typeInfoName;
    }
};

} /* namespace CornStarch */
#endif /* MESSAGETYPEFILTER_HPP_ */
