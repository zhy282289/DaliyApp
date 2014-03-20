#include "contentwidget.h"

#include <QtGui/Qtgui>
#include <QtCore/QtCore>


ContentWidget::ContentWidget(QWidget *parent)
	:QWidget(parent)
{

	m_listView = new ListView;
	m_textEdit = new QTextEdit;

	
	connect(m_listView, SIGNAL(SigDisplayChanged(int,int)), this, SLOT(SlotDisplayChanged(int,int)));
	connect(m_listView, SIGNAL(SigDisplayChanged(QString)), this, SLOT(SlotDisplayChanged(QString)));

	connect(m_textEdit, SIGNAL(	textChanged()), this, SLOT(SlotTextChanged()));

	QSplitter	*m_splitter = new QSplitter(Qt::Horizontal);
	m_splitter->addWidget(m_listView);
	m_splitter->addWidget(m_textEdit);
	m_splitter->setCollapsible(0, false);
	m_splitter->setCollapsible(1, false);
	m_splitter->setStretchFactor(0, 30);
	m_splitter->setStretchFactor(1, 70);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_splitter);
	layout->setContentsMargins(0, 0, 0, 0);
	
	setLayout(layout);
}

void ContentWidget::New()
{
	m_listView->New();
}

void ContentWidget::Save()
{
	m_listView->Save();
}

//void ContentWidget::SlotDisplayChanged( int current,int previous)
//{
//
//	//if (!previous.path.isEmpty())
//	//{
//	//	GetController()->SaveContent(previous.path, m_textEdit->toPlainText());
//	//}
//
//	//QString content;
//	//GetController()->LoadContent(current.path, content);
//	//m_textEdit->setPlainText(content);
//	
//}


void ContentWidget::SlotDisplayChanged( QString content )
{
	m_textEdit->blockSignals(true);
	m_textEdit->setPlainText(content);
	m_textEdit->blockSignals(false);
}

void ContentWidget::Remvoe()
{
	m_listView->Remove();
}

void ContentWidget::SlotTextChanged()
{
	m_listView->CurrentTextChanged(m_textEdit->toPlainText());
}






//////////////////////////////////////////////////////////////////////////
ListView::ListView(QWidget *parent /*= NULL*/ )
	:QTableView(parent)
{
	m_model = new ListModel(this);
	m_sortFilterModel = new SortFilterModel(this);
	m_sortFilterModel->setSourceModel(m_model);
	setModel(m_sortFilterModel);


	setSelectionBehavior(QAbstractItemView::SelectRows);
	horizontalHeader()->resizeSection(ListModel::TIME, 170);
	//horizontalHeader()->setStretchLastSection(true);


	connect(selectionModel(), SIGNAL(currentChanged(const QModelIndex&,const QModelIndex&)),  this, SLOT(SlotCurrentChanged(const QModelIndex&,const QModelIndex&)));
	connect(horizontalHeader(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),  this, SLOT(SlotSortIndicatorChanged(int,Qt::SortOrder)));

}

void ListView::New()
{
	DialyData data;
	data.path = QDir::toNativeSeparators(QApplication::applicationDirPath() +  "/content/" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") + ".daily");
	GetController()->SaveContent(data.path, "");
	m_model->AddRow(data);
	
}

//void ListView::Save()
//{
//	//QModelIndex curIndex = currentIndex();
//	//if (curIndex.isValid())
//	//{
//	//	m_model->UpdateState(curIndex, 1);
//	//}
//}

void ListView::Remove()
{
	QModelIndexList selectList = selectionModel()->selectedRows();
	if (!selectList.isEmpty())
	{
		int remainRow = 0;
		if (QMessageBox::Yes == QMessageBox::information(this, "提示", "是否删除日志", QMessageBox::Yes | QMessageBox::No))
		{
			remainRow = selectList.last().row();
			int lastPos = selectList.size() - 1;
			for (lastPos; lastPos >= 0; --lastPos)
			{
				QModelIndex index = selectList.at(lastPos);
				m_model->Remove(index.row());
			}

			// 高亮一行
			QModelIndex index = m_model->index(remainRow, 0);
			if (!index.isValid())
			{
				index = m_model->index(m_model->rowCount()-1, 0);

			}
			setCurrentIndex(index);

		}		

	}
}



void ListView::SlotCurrentChanged( const QModelIndex &current,const QModelIndex &previous )
{
	DialyData curData;
	QString content;
	if (current.isValid())
	{
		curData = m_model->RowData(current.row());
		if (curData.modify == 0)
		{
			GetController()->LoadContent(curData.path, content);
		}
		else
		{
			content = curData.content;
		}
	}

	emit SigDisplayChanged(content);
}



//void ListView::SlotDataChanged( const QModelIndex &current,const QModelIndex &previous )
//{
//	if (current.row() == 0)
//	{
//		UpdateState(State_TextChanged, 0);
//	}
//}

void ListView::keyPressEvent( QKeyEvent *event )
{
	switch (event->key())
	{
	case Qt::Key_Delete:
		{
			Remove();
		}

		break;
	case Qt::Key_S:
		{
			if (event->modifiers() & Qt::Key_Control)
			{
				//Save();
			}
		}

		break;

	}


	QTableView::keyPressEvent(event);
}

//void ListView::Save( int row, const QString &content )
//{
//	m_model->SaveRow(row, content);
//}

void ListView::Save()
{
	QModelIndexList selectList = selectionModel()->selectedRows();
	for (int i = 0; i < selectList.size(); ++i)
	{
		QModelIndex index = selectList.at(i);
		m_model->SaveRow(index.row());
	}
	
}

void ListView::CurrentTextChanged(const QString &content)
{
	if (currentIndex().isValid())
	{
		m_model->TextChanged(currentIndex().row(), content);
	}
}

void ListView::SlotSortIndicatorChanged( int section, Qt::SortOrder order )
{
	m_sortFilterModel->sort(section, order);
}




//////////////////////////////////////////////////////////////////////////
ListModel::ListModel(  QObject *parent /*= NULL*/ )
	:QAbstractTableModel(parent)
{
	GetController()->Load(m_data);
}


ListModel::~ListModel()
{
	GetController()->Save(m_data);
}

Qt::ItemFlags ListModel::flags( const QModelIndex & index ) const
{
	if (index.column() == TITLE)
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
	else
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

}

int ListModel::columnCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	return 2;
}

int ListModel::rowCount( const QModelIndex & parent /*= QModelIndex() */ ) const
{
	return m_data.size();
}

QVariant ListModel::data( const QModelIndex & index, int role /*= Qt::DisplayRole */ ) const
{

	int row = index.row();
	int column = index.column();
	if (row > m_data.size() || !index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)
	{
		if (column == TITLE)
		{
			return m_data.at(row).title;
		}
		else if (column == TIME)
		{
			return m_data.at(row).time;
		}
	}
	else if (role == Qt::EditRole)
	{
		if (column == TITLE)
		{
			return m_data.at(row).title;
		}
		else if (column == TIME)
		{
			return m_data.at(row).time; 
		}
	}
	//else if (role == Qt::BackgroundRole)
	//{
	//	if (m_data.at(row).modify == 1)
	//	{
	//		return QBrush(QColor(250, 25, 25));
	//	}
	//}



	return QVariant();
}

bool ListModel::setData( const QModelIndex & index, const QVariant & value, int role /*= Qt::EditRole */ )
{
	if (role == Qt::EditRole)
	{
		if (index.column() == TITLE)
		{
			m_data[index.row()].title = value.toString();
			return true;
		}
	}

	return false;
}

QVariant ListModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			if (section == TITLE)
			{
				return "标题";
			}
			else if (section == TIME)
			{
				return "创建时间";
			}

		}
	}

	return QVariant();
}

void ListModel::AddRow( const DialyData &data )
{
	beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
	m_data.push_back(data);
	endInsertRows();
}

void ListModel::Remove( int row )
{
	if (row >=0 && row < m_data.size())
	{
		GetController()->RemovePath(m_data.at(row).path);
		beginRemoveRows(QModelIndex(), row, row);
		m_data.removeAt(row);
		endRemoveRows();	
	}
}



//void ListModel::SaveRow( int row, const QString &content )
//{
//	GetController()->SaveContent(m_data.at(row).path, content);
//}

void ListModel::SaveRow( int row )
{
	if (m_data[row].modify == 1)
	{
		m_data[row].modify = 0;
		GetController()->SaveContent(m_data.at(row).path, m_data.at(row).content);
	}

}

DialyData ListModel::RowData( int row )
{
	return m_data.at(row);
}

void ListModel::TextChanged( int row, const QString &content )
{
	m_data[row].modify = 1;
	m_data[row].content = content;
}


//////////////////////////////////////////////////////////////////////////
Controller::Controller( QObject *object )
	:QObject(object)
{
	qRegisterMetaTypeStreamOperators<DialyData>("DialyDatas");

	m_savePath = QDir::toNativeSeparators(QApplication::applicationDirPath() +  "/content/");
	m_configPath = QDir::toNativeSeparators(QApplication::applicationDirPath() +  "/config.daily");
	QDir dir;
	dir.mkpath(m_savePath);
}

void Controller::Load( DialyDatas &datas )
{
	QFile file(m_configPath);
	if (file.open(QIODevice::ReadOnly))
	{
		QDataStream stream(&file);
		stream.setVersion(QDataStream::Qt_4_0);
		stream >> datas;
	}
}


void Controller::Save( const DialyDatas &datas )
{
	DialyDatas datasTemp = datas;
	for (int i = 0; i < datas.size(); ++i)
	{
		DialyData &data = datasTemp[i];
		if (data.modify == 1)
		{
			SaveContent(data.path, data.content);
			data.modify = 0;
		}
	}

	QFile file(m_configPath);
	if (file.open(QIODevice::WriteOnly))
	{
		QDataStream stream(&file);
		stream.setVersion(QDataStream::Qt_4_0);
		stream << datasTemp;
	}
}


void Controller::SaveContent( const QString &path, const QString &content )
{
	QFile file(path);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(content.toLocal8Bit());
		file.close();
	}
}




void Controller::RemovePath( const QString &path )
{
	qDebug() << path;
	qDebug() << QFile::remove(path);
}

void Controller::LoadContent( const QString &path, QString &content )
{
	QByteArray array;
	QFile file(path);
	if (file.open(QIODevice::ReadOnly))
	{
		array = file.readAll();
		file.close();
	}
	content = QString::fromLocal8Bit(array);
}



Controller	*g_controller = NULL;
Controller * GetController( QObject *parent )
{
	if (g_controller == NULL)
	{
		g_controller = new Controller(parent);
	}

	return g_controller;
}



//////////////////////////////////////////////////////////////////////////
SortFilterModel::SortFilterModel( QObject *parent )
	:QSortFilterProxyModel(parent)
{

}

SortFilterModel::~SortFilterModel()
{

}


bool SortFilterModel::lessThan( const QModelIndex &left, const QModelIndex &right ) const
{
	if (left.column() == 0)
	{
		return left.data().toString() < right.data().toString();

	}
	else if (left.column() == 1)
	{
		return left.data().toString() < right.data().toString();
	}
}

