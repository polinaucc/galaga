#include "window.hpp"
#include <QtWidgets/QApplication>
#include "spritestorage.hpp"
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	SpriteStorage::load();
	Window w;
	w.show();
	return a.exec();
}
