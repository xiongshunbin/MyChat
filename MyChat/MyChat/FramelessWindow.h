#ifndef _FRAMELESSWINDOW_H_
#define _FRAMELESSWINDOW_H_

#include <QWidget>

class FramelessWindow : public QWidget
{
	Q_OBJECT

public:
	explicit FramelessWindow(QWidget* parent = nullptr);

	~FramelessWindow();

protected:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private:

};

#endif // !_FRAMELESSWINDOW_H_
