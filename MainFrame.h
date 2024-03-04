#pragma once
#include <wx/wx.h>
class MainFrame:public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void BindEvents();
	void AddSavedTasks();
	void SetupSizers();

	void OnAddClick(wxCommandEvent& evt);
	void OnInputEnter(wxCommandEvent& evt);
	void onListKeyDown(wxKeyEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void onWindowClosed(wxCloseEvent& evt);

	void AddTaskFromInput();
	void DeleteTask();
	void MoveSelectedTask(int offset);
	void SwapTasks(int i, int j);

	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checkBox;
	wxButton* clearButton;
};

