#ifndef MENUEDIT_HPP_
#define MENUEDIT_HPP_
#include "MenuPart.hpp"

namespace CornStarch
{

class CMenuEdit: public CMenuPart
{

public:
    CMenuEdit();
    virtual ~CMenuEdit();
    // 初期化を行う
    void init(void);
};

} /* namespace CornStarch */
#endif /* MENUEDIT_HPP_ */
