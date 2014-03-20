#pragma once


#include <QString>
#include <QDataStream>
#include <QMetaType>
#include <QDateTime>
#include <QDir>
#include <QApplication>

struct DialyData
{
	QString title;
	QString time;
	int	level;
	QString path;
	int modify;
	QString content;

	DialyData()
	{
		title = "Untitle";
		time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		level = 0;
		modify = 0;
	}
};
typedef QList<DialyData> DialyDatas;
Q_DECLARE_METATYPE(DialyData)
QDataStream& operator >> (QDataStream &in, DialyData &data);
QDataStream& operator << (QDataStream &out, const DialyData &data);



