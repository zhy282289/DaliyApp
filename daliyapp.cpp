#include "daliyapp.h"

#include <QMenuBar>
#include <QMessageBox>
#include <QTimer>


DaliyApp::DaliyApp(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setWindowTitle("Jetsen 日志");


	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_actNew = m_fileMenu->addAction("New");
	m_actRemove = m_fileMenu->addAction("Remove");
	m_actExit = m_fileMenu->addAction("Exit");

	m_actNew->setIcon(QPixmap(":/DaliyApp/Resources/new.png"));
	m_actRemove->setIcon(QPixmap(":/DaliyApp/Resources/delete.png"));
	m_actExit->setIcon(QPixmap(":/DaliyApp/Resources/exit.png"));

	m_actNew->setToolTip("New");
	m_actRemove->setToolTip("Delete");
	m_actExit->setToolTip("Exit");


	connect(m_actNew, SIGNAL(triggered()), this, SLOT(SlotAction()));
	connect(m_actRemove, SIGNAL(triggered()), this, SLOT(SlotAction()));
	connect(m_actExit, SIGNAL(triggered()), this, SLOT(SlotAction()));

	m_fileBar = addToolBar(tr("File"));
	m_fileBar->addAction(m_actNew);
	m_fileBar->addAction(m_actRemove);



	m_contentWidget = new ContentWidget;
	setCentralWidget(m_contentWidget);
}

DaliyApp::~DaliyApp()
{

}

void DaliyApp::SlotAction()
{
	QAction *act = static_cast<QAction*>(sender());

	if (act == m_actNew)
	{
		m_contentWidget->New();
		act->setEnabled(false);
		QTimer::singleShot(1000, this, SLOT(SlotNewActEnable()));
	}
	else if (m_actRemove == act)
	{
		m_contentWidget->Remvoe();
	}
	else if (m_actExit == act)
	{
		close();
	}
}

void DaliyApp::closeEvent( QCloseEvent *event )
{
	if (QMessageBox::Yes == QMessageBox::information(this, "退出", "是否退出程序", QMessageBox::Yes | QMessageBox::No))
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void DaliyApp::SlotNewActEnable()
{
	m_actNew->setEnabled(true);
}
