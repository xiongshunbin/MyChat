#ifndef _MYDIALOG_H_
#define _MYDIALOG_H_

#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QEvent>
#include "CustomDialog.h"
#include "resources_manager.h"

class MyDialog : public CustomDialog
{
	Q_OBJECT
public:
	static MyDialog* instance()
	{
		if (m_myDialog == nullptr)
			m_myDialog = new MyDialog;
		return m_myDialog;
	}
	void exec(QWidget* parent);

	void setMessage(QString message);

	void setDialogSize(int w, int h);

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	explicit MyDialog(QWidget* parent = nullptr);
	~MyDialog();
	MyDialog(const MyDialog&) = delete;
	MyDialog& operator=(const MyDialog&) = delete;

private:
	QPushButton* btnClose = nullptr;
	static MyDialog* m_myDialog;
	QWidget* mainDialog;
	QLabel* lblMessage;
	int mainDialog_w = 350;
	int mainDialog_h = 200;
};

#endif // !_MYDIALOG_H_