#include "GameObject.hpp"

void GameObject::move(double x, double limit)
{
	m_x += x;
	if (x < 0 && m_x < limit)
		m_x = limit;
	if (x > 0 && m_x > limit)
		m_x = limit;
}
void GameObject::move(double x, double x_limit, double y, double y_limit)
{
	m_x += x;
	if (x < 0 && m_x < x_limit)
		m_x = x_limit;
	if (x > 0 && m_x > x_limit)
		m_x = x_limit;

	m_y += y;
	if (y < 0 && m_y < y_limit)
		m_y = y_limit;
	if (y > 0 && m_y > y_limit)
		m_y = y_limit;
}
