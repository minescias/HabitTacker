#include "HtGui/RecentDatabasesModel.h"

namespace Gui
{
RecentDatabasesModel::RecentDatabasesModel(QObject* parent)
	: QAbstractListModel(parent)
{
	// i'll add some real files once i know how to store
	// data like recent files in ubuntu
	m_data = {"/home/example.db", "/home/example_old.db", "asdfdf"};
}

RecentDatabasesModel::~RecentDatabasesModel()
{
}

int RecentDatabasesModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
	return m_data.count();
}

QVariant RecentDatabasesModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	if (row < 0 || row >= m_data.count())
	{
		return QVariant();
	}

	// dzięki temu, że używam Qt::DisplayRole mam dostęp do dacnych
	// za pomocą model.display (w pliku .qml)
	switch (role)
	{
	case Qt::DisplayRole:
		return m_data.value(row);
	}

	return QVariant();
}

} // namespace Gui
