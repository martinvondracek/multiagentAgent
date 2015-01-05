/*
 * File:   main.cpp
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:36
 */

#include <QApplication>
#include <qt4/QtGui/qwidget.h>

#include "agentForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    agentForm frm;
    frm.show();

    return app.exec();
}
