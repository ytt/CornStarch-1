#pragma once
#include "Message.hpp"

namespace CornStarch
{;

// チャンネル参加ログ
class CJoinMessage : public CMessage
{
private:

public:
    CJoinMessage(void);
    ~CJoinMessage(void);
};

}
