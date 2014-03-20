#include "daliyapp.h"
#include <QtGui/QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));

	DaliyApp w;
	w.showMaximized();
	return a.exec();
}
