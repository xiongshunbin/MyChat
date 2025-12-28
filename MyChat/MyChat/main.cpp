#include "Widget.h"
#include <QtWidgets/QApplication>
#include "LRDialog.h"

#include "TestFramelessWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	LRDialog dialog;
	dialog.setStyleSheet(ResourcesManager::instance()->getStylePool().find(ResID::Style_LRDialog)->second);
	dialog.show();
    //TestFramelessWindow test;
    //test.show();
    return a.exec();
}
