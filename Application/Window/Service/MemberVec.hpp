﻿#pragma once
#include <vector>
#include "../../DataStruct/MemberData.hpp"

namespace CornStarch
{;

class CMemberVec : public std::vector<CMemberData*>
{
private:
	bool m_isLoaded;
public:
    CMemberVec(void);
    ~CMemberVec(void);

    // メンバー一覧を登録する
    void setMembers(const std::vector<CMemberData*>& members);

    // メンバーを受信済みか
    bool hasSetMember(void) const;

    // メンバー情報を更新する
    void updateStatus(const wxString& userName,const wxString& nick);

    // メンバーを追加する
    void push(const CMemberData& member);

    // メンバーを削除する
    void pop(const wxString& userName);

    // 全メンバーを削除する
    void deleteAllMembers(void);
};

}
