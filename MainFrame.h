#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
private:
    void OnButtonClick(wxCommandEvent& evt);
};

/*
    To compile
    g++ App.cpp  MainFrame.cpp `wx-config --cxxflags` `wx-config --libs` -o ScriptLauncher
*/