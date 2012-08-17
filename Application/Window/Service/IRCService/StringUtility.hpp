﻿

#ifndef _StringUtility_h
#define _StringUtility_h
#include "string"
#include "vector"
#include <wx/wxprec.h>
#include <wx/wx.h>
using namespace std;

namespace CornStarch {
    class CStringUtility
    {
    public:
        static vector<wxString> split(wxString str, wxString delim);
    };
}

#endif
