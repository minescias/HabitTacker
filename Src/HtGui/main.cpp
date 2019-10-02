#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "HtGui/RecentDatabasesModel.h"

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));

	// zarejestrowanie modelu
	qmlRegisterType<Gui::RecentDatabasesModel>(
		"Ht.RecentDatabasesModel", 1, 0, "RecentDatabasesModel");

	engine.load(url);
	return app.exec();
}
