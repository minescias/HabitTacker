#ifndef __RECENT_DATABASES_MODEL_H
#define __RECENT_DATABASES_MODEL_H

#include <QtCore>
#include <QtGui>

namespace Gui
{
// http://qmlbook.github.io/ch16-qtcpp/qtcpp.html#a-simple-model
class RecentDatabasesModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit RecentDatabasesModel(QObject* parent = nullptr);
	~RecentDatabasesModel();

public:
	virtual QVariant data(const QModelIndex& index, int role) const;
	virtual int rowCount(const QModelIndex& parent) const;

private:
	QList<QString> m_data;
};

} // namespace Gui

#endif // __RECENT_DATABASES_MODEL_H
