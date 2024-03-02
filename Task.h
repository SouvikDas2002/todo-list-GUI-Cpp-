#pragma once
#include <string>
#include <vector>

struct Task
{
	std::string description;
	bool done;
};
void saveTaskToFile(const std::vector<Task>& tasks, const std::string& filename);

std::vector<Task>loadTaskFromFile(const std::string& filename);