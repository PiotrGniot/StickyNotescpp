#include "stickynotes.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StickyNotes w;
    w.show();
    return a.exec();
}
