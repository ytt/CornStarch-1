
#ifndef MESSAGECONTROLDOUBLECLICKEDEVENT_HPP_
#define MESSAGECONTROLDOUBLECLICKEDEVENT_HPP_

#include "wx/treebase.h"
namespace CornStarch
{

class CMessageControlDoubleClickedEvent : public wxNotifyEvent
{
    int m_index;
public:
    CMessageControlDoubleClickedEvent();
    virtual ~CMessageControlDoubleClickedEvent();

    int getIndex() const
    {
        return m_index;
    }

    void setIndex(int index)
    {
        m_index = index;
    }
};

} /* namespace CornStarch */
#endif /* MESSAGECONTROLDOUBLECLICKEDEVENT_HPP_ */
