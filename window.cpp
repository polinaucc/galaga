#include "window.hpp"
#include "qfile.h"
#include "qmessagebox.h"
#include "spritestorage.hpp"
#include "Game.hpp"
#include "qpainter.h"
#include "qevent.h"
#include "Player.hpp"

void game_end(bool is_a_win, unsigned int score)
{
    QMessageBox::information(nullptr, "Game over", (is_a_win ? "Congratulations on beating the game. " : "\n") + QString("Your score is ")
                             + QString::number(score) + " points.\nUse 1 to load saved game (if there is any).\n");
}


Window::Window(QWidget *parent)	: QWidget(parent)
{
	Game::initialize(m_width, m_height, game_end);
	setFixedSize(m_width, m_height);
	game = Game::get_instance();

	connect(&timer, &QTimer::timeout, this, [this]() {
		game->tick();
		update();
	});
	timer.start(15);

	QPalette temp = palette();

	QBrush background(Qt::TexturePattern);
	background.setTextureImage(SpriteStorage::space->get());
	temp.setBrush(QPalette::Background, background);

	setFont(QFont("Arial", 24));
	
	QBrush foreground(Qt::SolidPattern);
	foreground.setColor(QColor(255, 255, 255));
	temp.setBrush(QPalette::Foreground, foreground);
	setPalette(temp);
}


void Window::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	{
		for (auto projectile : game->projectiles())
			if (projectile) draw(painter, *projectile);
		for (auto bonus : game->bonuses())
			draw(painter, *bonus);
		for (auto animation : game->animations()) {
			auto sprite = animation->sprite();
			if (!animation->is_over())
				draw(painter, animation->x(), animation->y(), sprite);
		}
		for (auto enemy : game->enemies()) {
			auto sprite = enemy->sprite();
			if (enemy->is_alive())
				draw(painter, enemy->x(), enemy->y(), sprite);
		}
        if (game->player().is_alive())
			draw(painter, game->player());

		painter.drawText(QRect(0, 0, m_width, m_height),
						 "Score: " + QString::number(game->score()));// + "\nLives: " + QString::number(game->player().lives()));
        if (game->player().is_alive())
            for (unsigned int i = 0; i < game->player().lives() - 1; i++)
            {
                draw(painter, i * 34 + 17, m_height - 34, SpriteStorage::ship);
		}
	}
	painter.end();
	
	e->accept();
}


void Window::draw(QPainter &painter, double _x, double _y, std::shared_ptr<Sprite> sprite)
{
	auto width = sprite->width();
	auto height = sprite->height();
	auto x = _x - width / 2.0;
	auto y = _y - height / 2.0;
	painter.drawImage(QRect(x, y, width, height),
					  sprite->get());
}
void Window::draw(QPainter &painter, GameObject const& obj)
{
	return draw(painter, obj.x(), obj.y(), obj.sprite());
}

void Window::keyPressEvent(QKeyEvent *e) {
	switch (e->key()) {
		case Qt::Key_A:
		case Qt::Key_Left:
            game->left_event(true);
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
            game->right_event(true);
			break;
		case Qt::Key_L:
		case Qt::Key_X:
        case Qt::Key_Space:
            game->shoot_event(true);
			break;
			
        case Qt::Key_1:
			game->save("save.txt");
			break;
        case Qt::Key_2:
			game->load("save.txt");
			break;
		default:
			break;
	}
}
void Window::keyReleaseEvent(QKeyEvent *e) {
	switch (e->key()) {
		case Qt::Key_A:
		case Qt::Key_Left:
            game->left_event(false);
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
            game->right_event(false);
			break;
		case Qt::Key_L:        
		case Qt::Key_X:
        case Qt::Key_Space:
            game->shoot_event(false);
			break;
		default:
			break;
	}
}
