#include "Element.h"


Element::Element(std::string data) : m_data(data)
{
	m_state = Actual;
}

Element::Element() : m_data()
{
	m_state = Empty;
}

std::string Element::GetData()
{
	return m_data;
}

State Element::GetState()
{
	return m_state;
}

void Element::SetState(State state)
{
	m_state = state;
}

void Element::SetData(std::string data)
{
	m_data = data;
}