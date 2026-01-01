#include "Widget.h"
#include <QtWidgets/QApplication>
#include "LRFDialog.h"

#include "TestFramelessWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	LRFDialog dialog;
	dialog.setStyleSheet(ResourcesManager::instance()->getStylePool().find(ResID::Style_LRFDialog)->second);
	dialog.show();
    //TestFramelessWindow test;
    //test.show();
    return a.exec();
}
