#include "udiskdetectwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Qt检测U盘插入拔出Demo
    // https://blog.csdn.net/u014597198/article/details/72820737

    UDiskDetectWidget w;
    w.show();
    return a.exec();
}
