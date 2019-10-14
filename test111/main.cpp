#include "mainwindow.h"
#include <QApplication>
#include "qtservice.h"
#include <qDebug>

class MyWindowServiceAPP : public QtService<QApplication>
{
public:
    MyWindowServiceAPP(int argc, char **argv)
    : QtService<QApplication>(argc, argv, "HNXACAssistService")
    {
        setServiceDescription("证书钥匙辅助服务");
        setServiceFlags(QtServiceBase::CanBeSuspended);
    }

protected:
    void start()
    {
        QApplication *app = application();

        qDebug() << "MyWindowServiceAPP::start";

        m_w = new MainWindow();
        m_w->hide();
    }

    void pause()
    {

    }

    void resume()
    {

    }

private:
    MainWindow *m_w;
};


int main(int argc, char **argv)
{
    bool bflaglog = false;
    for (int i=0; i < argc; i++)
    {
        QString ss = QString::fromLocal8Bit(argv[i]);
        if (ss.contains("log",Qt::CaseInsensitive))
        {
            bflaglog = true;
        }
    }
//    if (bflaglog)
//        qInstallMessageHandler(myMessageOutput);

    MyWindowServiceAPP a(argc, argv);


//    QApplication a(argc,argv);

//    MainWindow w;
//    w.show();

    return a.exec();
}
