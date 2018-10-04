# include <QApplication>
# include "widget.h"
#include "widget_ex3_4.h"

int main ( int argc , char * argv [])
{
    QApplication a(argc , argv );
    Widget w;
    widget_ex3_4 w2;
    w2.show();
    return a.exec ();

}
