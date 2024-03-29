#include <QtGui>
#include <QtWidgets>
#include "qtservice.h"

class InteractiveService : public QtService<QApplication> {
public:
	InteractiveService(int argc, char** argv);
	~InteractiveService();

protected:

	void start();
	void stop();
	void pause();
	void resume();
	void processCommand(int code);

private:
	QLabel* gui;
};

InteractiveService::InteractiveService(int argc, char** argv)
	: QtService<QApplication>(argc, argv, "Qt Interactive Service"), gui(0) {
	setServiceDescription("A Qt service with user interface.");
	setServiceFlags(QtServiceBase::CanBeSuspended);
}

InteractiveService::~InteractiveService() {
}

void InteractiveService::start() {
#if defined(Q_OS_WIN)

	if ((QSysInfo::WindowsVersion & QSysInfo::WV_NT_based) &&
			(QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA)) {
		logMessage("Service GUI not allowed on Windows Vista. See the documentation for this example for more information.", QtServiceBase::Error);
		return;
	}

#endif

	qApp->setQuitOnLastWindowClosed(false);

	gui = new QLabel("Service", 0, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	gui->move(QApplication::desktop()->availableGeometry().topLeft());
	gui->show();
}

void InteractiveService::stop() {
	delete gui;
}

void InteractiveService::pause() {
	if (gui) {
		gui->hide();
	}
}

void InteractiveService::resume() {
	if (gui) {
		gui->show();
	}
}

void InteractiveService::processCommand(int code) {
	gui->setText("Command code " + QString::number(code));
	gui->adjustSize();
}

int main(int argc, char** argv) {
#if !defined(Q_OS_WIN)
	// QtService stores service settings in SystemScope, which normally require root privileges.
	// To allow testing this example as non-root, we change the directory of the SystemScope settings file.
	QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
	qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif
	InteractiveService service(argc, argv);
	return service.exec();
}
