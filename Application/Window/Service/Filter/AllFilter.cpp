
#include "AllFilter.hpp"

namespace CornStarch
{

CAllFilter::CAllFilter()
{

}

CAllFilter::~CAllFilter()
{
}
bool CAllFilter::isValid(const CMessage* message)const
{
    // どのメッセージの有効です。
    return true;
}
} /* namespace CornStarch */
