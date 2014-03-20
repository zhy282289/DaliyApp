#ifndef DALIYAPP_H
#define DALIYAPP_H

#include "contentwidget.h"
#include <QtGui/QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QCloseEvent>

class DaliyApp : public QMainWindow
{
	Q_OBJECT

public:
	DaliyApp(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DaliyApp();

private slots:
	void SlotAction();
	void SlotNewActEnable();

protected:
	void closeEvent(QCloseEvent *event);

private:
	ContentWidget	*m_contentWidget;

	QMenu	*m_fileMenu;
	QAction	*m_actNew;
	QAction	*m_actRemove;

	QAction	*m_actExit;

	QToolBar	*m_fileBar;
};

#endif // DALIYAPP_H
