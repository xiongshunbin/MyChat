#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include <QFontDatabase>

#include <unordered_map>
#include <QFile>
#include <QDebug>
#include "manager.h"

enum class ResID
{
	Font_TitleBar_iconfont,
	Font_PingFang,
	Style_LRDialog,
	Style_TitleBar,
	Style_MyDialog
};

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:
	typedef std::unordered_map<ResID, QFont> FontPool;
	typedef std::unordered_map<ResID, QString> StylePool;

public:
	const FontPool& getFontPool()
	{
		return fontPool;
	}
	
	const StylePool& getStylePool()
	{
		return stylePool;
	}

protected:
	QFont loadFont(QString fontName, QString filePath)
	{
		QFont font;
		if (!fontDb.families().contains(fontName)) {
			int fontId = fontDb.addApplicationFont(filePath);
			QStringList fontName = fontDb.applicationFontFamilies(fontId);
			if (fontName.count() == 0) {
				qDebug() << "load iconfont.ttf error";
			}
		}
		if (fontDb.families().contains(fontName)) {
			font = QFont(fontName);
			font.setHintingPreference(QFont::PreferNoHinting);
		}
		return font;
	}

	QString loadStyle(QString filePath)
	{
		QString style;
		QFile qss(filePath);
		if (qss.open(QFile::ReadOnly))
		{
			qDebug() << "Loading stylesheet successful!";
			style = QString(qss.readAll());
			qss.close();
		}
		else
			qDebug() << "Loading stylesheet failed!";
		return style;
	}

protected:
	ResourcesManager()
	{
		fontPool[ResID::Font_TitleBar_iconfont] = loadFont("TitleBar_iconfont", ":/src/fonts/TitleBar_iconfont.ttf");
		fontPool[ResID::Font_PingFang] = loadFont("PingFang", ":/src/fonts/PingFang.ttf");

		stylePool[ResID::Style_LRDialog] = loadStyle(":/src/style/LRDialog_style.qss");
		stylePool[ResID::Style_MyDialog] = loadStyle(":/src/style/MyDialog_style.qss");
		stylePool[ResID::Style_TitleBar] = loadStyle(":/src/style/TitleBar_style.qss");
	}
	~ResourcesManager() = default;


private:
	QFontDatabase fontDb;
	FontPool fontPool;
	StylePool stylePool;
};

#endif // !_RESOURCES_MANAGER_H_