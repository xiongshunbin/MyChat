#pragma once

#include <QFontDatabase>
#include <unordered_map>
#include <QFile>
#include <QDebug>
#include "SingletonBase.h"

enum class ResID
{
	Font_TitleBar_iconfont,
	Font_PingFang,
	Font_MyLineEdit_iconfont,
	Style_LRFDialog,
	Style_TitleBar,
	Style_MyDialog
};

class ResourceManager : public SingletonBase<ResourceManager>
{
	friend class SingletonBase<ResourceManager>;

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

private:
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

	ResourceManager()
	{
		fontPool[ResID::Font_TitleBar_iconfont] = loadFont("TitleBar_iconfont", ":/src/fonts/TitleBar_iconfont.ttf");
		fontPool[ResID::Font_PingFang] = loadFont("PingFang", ":/src/fonts/PingFang.ttf");
		fontPool[ResID::Font_MyLineEdit_iconfont] = loadFont("MyLineEdit_iconfont", ":/src/fonts/MyLineEdit_iconfont.ttf");

		stylePool[ResID::Style_LRFDialog] = loadStyle(":/src/style/LRFDialog_style.qss");
		stylePool[ResID::Style_MyDialog] = loadStyle(":/src/style/MyDialog_style.qss");
		stylePool[ResID::Style_TitleBar] = loadStyle(":/src/style/TitleBar_style.qss");
	}

public:
	~ResourceManager() = default;

private:
	QFontDatabase fontDb;
	FontPool fontPool;
	StylePool stylePool;
};
