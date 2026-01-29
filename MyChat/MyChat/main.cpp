#include "Widget.h"
#include <QtWidgets/QApplication>
#include "LRFDialog.h"

#include "FramelessWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//LRFDialog dialog;
	//dialog.setStyleSheet(ResourceManager::getInstance()->getStylePool().find(ResID::Style_LRFDialog)->second);
	//dialog.show();
	FramelessWindow test;
	test.show();
    return a.exec();
}
