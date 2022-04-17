#include <mainwindow.hh>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    window.resize(1080, 720);
    window.show();

    return app.exec();
}
