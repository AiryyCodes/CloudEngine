#pragma once

#include <string>

class Window
{
public:
	Window(std::string title, int width, int height);

private:
	std::string title;
	int width;
	int height;
};
