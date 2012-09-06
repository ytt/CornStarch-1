

#ifndef IFILTER_HPP_
#define IFILTER_HPP_
#include "../Message/Message.hpp"

namespace CornStarch
{
// フィルタのインターフェース
class IFilter
{
public:
    IFilter(){};
    virtual ~IFilter(){};
    // メッセージが適当かを調べる。
    virtual bool isValid(const CMessage* message) const = 0;
    // 逆条件かを取得
    virtual bool isAntiFilter() const= 0;
    // 名前を取得する
    virtual wxString getName() const = 0;
};

} /* namespace CornStarch */
#endif /* IFILTER_HPP_ */
