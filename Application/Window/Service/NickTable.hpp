﻿#pragma once
#include <map>
#include <vector>
#include "../../DataStruct/MemberData.hpp"

namespace CornStarch
{;

// 本名とニックネームの対応付けを行うためのテーブルクラス
class CNickTable : public std::map<wxString, wxString>
{
public:
    CNickTable(void);
    ~CNickTable(void);

    // テーブルに追加する
    void addTableFromMembers(const std::vector<CMemberData*>& members);

    // 本名に対応するニックネームを取得する
    wxString getNickname(const wxString& name) const;

    // ニックネームが登録されているか
    bool isExist(const wxString& name) const;

    // ニックネームから本名を検索する
    wxString getRealName(const wxString& nick);
};

}
