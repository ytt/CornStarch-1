#ifndef MENUVIEW_HPP_
#define MENUVIEW_HPP_

#include "MenuPart.hpp"
namespace CornStarch
{

class CMenuView: public CMenuPart
{
public:
    CMenuView();
    virtual ~CMenuView();

    // 初期化を行う
    void init(void);
};

} /* namespace CornStarch */
#endif /* MENUVIEW_HPP_ */
