#include "desktoptool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopTool w;
    w.show();

    return a.exec();
}
