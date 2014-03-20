#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include "data.h"

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QTextEdit>
#include <QSortFilterProxyModel>


class ListView;

class ContentWidget : public QWidget
{
	Q_OBJECT
public:
	ContentWidget(QWidget *parent = NULL);

public slots:
	void New();
	void Remvoe();
	void Save();


	//void SlotDisplayChanged(int current,int previous);
	void SlotDisplayChanged(QString content);
	void SlotTextChanged();
private:
	ListView	*m_listView;
	QTextEdit	*m_textEdit;

	DialyDatas	m_data;
};


enum StateType{State_TextChanged,};
class ListModel;
class SortFilterModel;
class ListView : public QTableView
{
	Q_OBJECT
public:
	ListView(QWidget *parent = NULL);

	void New();
	void Remove();
	//void Save(int row, const QString &content);
	void Save();

	void CurrentTextChanged(const QString &content);

signals:
	//void SigDisplayChanged(int current, int previous);
	void SigDisplayChanged(QString);
private slots:
	void SlotCurrentChanged(const QModelIndex &current,const QModelIndex &previous);
	void SlotSortIndicatorChanged(int section, Qt::SortOrder order);
protected:
	void keyPressEvent(QKeyEvent *event);

private:
	ListModel	*m_model;
	DialyDatas	*m_data;
	SortFilterModel *m_sortFilterModel;
};



class ListModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	enum {TITLE, TIME, LEVEL, PATH, MODIFY};
public:
	ListModel( QObject *parent = NULL);
	~ListModel();

	void AddRow(const DialyData &data);
	void SaveRow(int row);
	void Remove(int row);

	DialyData RowData(int row);

	void TextChanged(int row, const QString &content );

	virtual QVariant	headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual Qt::ItemFlags	flags ( const QModelIndex & index ) const;
	virtual int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual bool	setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

private:
	DialyDatas	m_data;
};



class Controller : public QObject
{
	Q_OBJECT
public:
	Controller(QObject *object);

	void Load(DialyDatas &datas);
	void Save(const DialyDatas &datas);

	void SaveContent(const QString &path, const QString &content);
	void LoadContent(const QString &path, QString &content);
	void RemovePath(const QString &path);

private:
	QString m_savePath;
	QString m_configPath;
};


Controller *GetController(QObject *parent = NULL);




class SortFilterModel : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	SortFilterModel(QObject *parent);
	~SortFilterModel();


	 bool	lessThan ( const QModelIndex &left, const QModelIndex &right ) const;

};





#endif // CONTENTWIDGET_H
