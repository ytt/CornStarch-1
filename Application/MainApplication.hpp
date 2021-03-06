﻿#pragma once
#include "Window/MainWindow.hpp"
#include "header.hpp"

namespace CornStarch
{;

class CMainApplication : public wxApp
{
private:
    // フレームのサイズ
    static const int WIDTH = 600;
    static const int HEIGHT = 650;
    static const wxString TITLE;

    CMainWindow *m_window; // メインとなるウィンドウ

public:
    // アプリケーションの初期化を行う
    virtual bool OnInit();
};

}
