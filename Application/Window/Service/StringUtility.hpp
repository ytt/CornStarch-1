
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
        static int findAny(wxString str, vector<wxString>& delim,int startIndex =0);
    };
}

#endif
