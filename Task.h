#pragma once
#include <string>
#include <vector>

struct Task
{
	std::string description;
	bool done; //0 -task incomplete /1 -task complete   
};
void saveTaskToFile(const std::vector<Task>& tasks, const std::string& filename);

std::vector<Task>loadTaskFromFile(const std::string& filename);