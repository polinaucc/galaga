#pragma once
#include "qwidget.h"
#include "qtimer.h"
#include <memory>
#include "Game.hpp"
#include "gamefacade.h"
#include "sprite.hpp"
#include "GameObject.hpp"

class Window : public QWidget
{
	Q_OBJECT
public:
	Window(QWidget *parent = Q_NULLPTR);
protected:
	void paintEvent(QPaintEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
    void draw(QPainter &painter, double _x, double _y, shared_ptr<Sprite> sprite);
	void draw(QPainter &painter, GameObject const& obj);
private:
    shared_ptr<GameFacade> game;
	QTimer timer;

	static int const m_width = 960;
	static int const m_height = 960;
};
