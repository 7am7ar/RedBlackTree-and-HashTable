#pragma once

#include "Globals.h"

#include <string>

class Element
{
public:
	Element(std::string data);
	Element();
	std::string GetData();
	State GetState();
	void SetState(State state);
	void SetData(std::string data);
private:
	std::string m_data;
	State m_state;
};

