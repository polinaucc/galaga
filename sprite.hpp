#pragma once
#include <memory>
#include "qimage.h"

class Sprite
{
private:
	QImage m_data;
public:
    Sprite(QString const& filename):
        m_data(filename)
    {}
    QImage const& get() const { return m_data; }
    QImage const& operator*() const { return m_data; } // вернет адрес (ссылку), которую монжо использовать как сам объект (Но никаких копий сделано не будет). *sprite можно использовать как strite.m
    QImage const* operator->() const { return &m_data; } //возможность вызвать метод класса QImage напрямую, используя ->.
	double width() const { return m_data.width(); }
	double height() const { return m_data.height(); }
};
