#include <QApplication>
#include <thread>
#include "widget.h"

int main ( int argc , char * argv [])
{
    QApplication a(argc , argv );
    Widget w;
    w.show();
    a.exec();

}
