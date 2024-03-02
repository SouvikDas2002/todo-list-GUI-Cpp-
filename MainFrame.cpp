#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.h"

MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	CreateControls();
	BindEvents();
	AddSavedTasks();
}

void MainFrame::CreateControls()
{

	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 20)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);
	//panel->SetBackgroundColour(*wxLIGHT_GREY);

	headlineText = new wxStaticText(panel, wxID_ANY, "TO-Do List", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);
	//headlineText->SetBackgroundColour(*wxRED);

	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35),wxTE_PROCESS_ENTER); //precess_enter helps to process input text after press enter
	addButton = new wxButton(panel, wxID_ANY, "Add Task", wxPoint(600, 80), wxSize(100, 35));
	checkBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));

	addButton->SetBackgroundColour(*wxCYAN);
}

void MainFrame::BindEvents()
{
	addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddClick, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	checkBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onListKeyDown, this);
	clearButton->Bind(wxEVT_BUTTON,&MainFrame::OnClearButtonClicked,this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onWindowClosed, this);
}

void MainFrame::AddSavedTasks()
{
	std::vector<Task>tasks = loadTaskFromFile("tasks.txt");

	for (const Task& task : tasks) {
		int index = checkBox->GetCount();
		checkBox->Insert(task.description, index);
		checkBox->Check(index, task.done);
	}
}

void MainFrame::OnAddClick(wxCommandEvent& evt)
{
	AddTaskFromInput();
}
void MainFrame::OnInputEnter(wxCommandEvent& evt) {
	AddTaskFromInput();
}

void MainFrame::onListKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) { //return which key is pressed
	case WXK_DELETE:
		DeleteTask(); //handle the delete function
		break;
	case WXK_UP:
		MoveSelectedTask(-1); //upper arrow direction
		break;
	case WXK_DOWN:
		MoveSelectedTask(1);//down arrow direction
		break;
	}
}


void MainFrame::AddTaskFromInput()
{
	wxString desc = inputField->GetValue(); //get value from input
	if (!desc.IsEmpty()) {
		checkBox->Insert(desc, checkBox->GetCount());
		inputField->Clear();
	}
	inputField->SetFocus();
}

void MainFrame::DeleteTask()
{
	int selectInd = checkBox->GetSelection();
	if (selectInd == wxNOT_FOUND) {
		return;
	}
	checkBox->Delete(selectInd);
}

void MainFrame::MoveSelectedTask(int offset)
{
	int index = checkBox->GetSelection(); //return the index of checked box
	if (index == wxNOT_FOUND) {
		return;
	}
	int newIndex = index + offset;

	if (newIndex >= 0 && newIndex < checkBox->GetCount()) {
		SwapTasks(index, newIndex);
		checkBox->SetSelection(newIndex, true);
	}
}

void MainFrame::SwapTasks(int i, int j) //swap selected task
{
	Task taskI{ checkBox->GetString(i).ToStdString(),checkBox->IsChecked(i) };
	Task taskJ{ checkBox->GetString(j).ToStdString(),checkBox->IsChecked(j) };

	checkBox->SetString(i, taskJ.description);
	checkBox->Check(i, taskJ.done);

	checkBox->SetString(j, taskI.description);
	checkBox->Check(j, taskI.done);

}

void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (checkBox->IsEmpty()) {
		return;
	}
	wxMessageDialog dialog(this, "Are you sure you want to clear all tasks?", "Clear",wxYES_NO | wxCANCEL);
	int res = dialog.ShowModal();

	if (res == wxID_YES) {
		checkBox->Clear();
	}
}

void MainFrame::onWindowClosed(wxCloseEvent& evt){
	std::vector<Task>tasks;
	for (int i = 0; i < checkBox->GetCount(); i++) {
		Task task;
		task.description = checkBox->GetString(i);
		task.done = checkBox->IsChecked(i);
		tasks.push_back(task);
	}
	saveTaskToFile(tasks, "tasks.txt"); //if the file exists then save input to the file or it will create
	evt.Skip();
}
