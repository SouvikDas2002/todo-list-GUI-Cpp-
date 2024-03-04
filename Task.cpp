#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void saveTaskToFile(const std::vector<Task>& tasks, const std::string& filename)
{
	std::ofstream ostream(filename);  //ofstream class describes an output stream and it is used to create files and write data to files
	ostream << tasks.size();

	for (const Task& task : tasks) {
		std::string description = task.description;
		std::replace(description.begin(), description.end(), ' ', '_');

		ostream << "\n" << description << ' ' << task.done;
	}
}

std::vector<Task> loadTaskFromFile(const std::string& filename)
{
	if (!std::filesystem::exists(filename)) { //check if file exist or not
		return std::vector<Task>();
	}
	std::vector<Task>tasks;
	std::ifstream istream(filename); //input file stream

	//first line contains nmber of tasks

	int n;
	istream >> n; //number of tasks

	for (int i = 0; i < n; i++) {
		std::string desc; //tasks description
		bool done; //complete(1) or not(0)

		istream >> desc >> done; //take input

		std::replace(desc.begin(), desc.end(), '_', ' ');
		tasks.push_back(Task{ desc,done });
	}
	return tasks;
}
