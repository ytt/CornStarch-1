#include "LinkableRichTextCtrl.hpp"

namespace CornStarch
{

CLinkableRichTextCtrl::CLinkableRichTextCtrl()
{
}

CLinkableRichTextCtrl::~CLinkableRichTextCtrl()
{

}
void CLinkableRichTextCtrl::setNavigateHaldler()
{
    // リンククリック時
    this->Connect(this->GetId(), wxEVT_COMMAND_TEXT_URL,
            wxTextUrlEventHandler(CLinkableRichTextCtrl::onNavigate));
}
void CLinkableRichTextCtrl::onNavigate(wxTextUrlEvent& event)
{
    wxString url = event.GetString();
    wxString command = "open " + url;
    system(command.c_str());
}
void CLinkableRichTextCtrl::writeLinkableText(const wxString& content)
{
    int urlIndex = content.find("http", 0);
    if (urlIndex != wxString::npos){
        // リンクが始まるまでの文字を表示
        if (urlIndex != 0){
            WriteText(content.substr(0, urlIndex));
        }
        int endIndex = 0;
        while (urlIndex != wxString::npos){
            endIndex = content.find(" ", urlIndex);

            wxString url;
            if (endIndex != wxString::npos){
                url = content.substr(urlIndex, endIndex - urlIndex);
            } else{
                url = content.substr(urlIndex);
            }
            this->BeginUnderline();
            this->BeginURL(url);
            WriteText(url);
            this->EndURL();
            this->EndUnderline();

            if (endIndex != wxString::npos){
                urlIndex = content.find("http", endIndex);
                // 次のリンクまでの文字を表示
                if (urlIndex != wxString::npos){
                    WriteText(content.substr(endIndex, urlIndex - endIndex));
                }
            } else{
                // 継続文字がなければ終了。
                return;
            }
        }
        // 残りの文字を表示
        WriteText(content.substr(endIndex));
    } else{

        WriteText(content);
    }
}
} /* namespace CornStarch */
