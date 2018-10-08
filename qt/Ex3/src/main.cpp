#include <QApplication>
#include <thread>
#include "widget.h"
#include "widget_ex3_4.h"


void thread_gui(int argc , char * argv []){

    QApplication a(argc , argv );
    Widget w;
    widget_ex3_4 w2;
    w.show();
    w2.show();
    a.exec();
}

int main ( int argc , char * argv [])
{
    std::thread gui(thread_gui,argc,argv);
    if(gui.joinable()){
        gui.join();
    }
    return 1;

}
