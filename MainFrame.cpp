#include "MainFrame.h"
#include "AwsFunctions.h"
#include <aws/core/Aws.h>
#include <iostream>
#include <string>
#include <string_view>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    // this is code
    wxPanel* panel = new wxPanel(this);
    wxButton* launchButton = new wxButton(panel, wxID_ANY, "Find Instances", wxPoint(300, 200), wxSize(200, 100));
    launchButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);

    CreateStatusBar();
}

void MainFrame::OnButtonClick(wxCommandEvent& evt)
{
    // sort the button press
    //wxLogStatus("Button clicked!");
    AwsFunctions awsFunction;
    Aws::String result = awsFunction.ListEc2Instances();
    //std::string_view resultCopy{result};
    wxLogStatus("%s", result);
}