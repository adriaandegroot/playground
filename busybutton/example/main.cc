/**
 * BusyButton is a QWidget that helps a user start and stop a long-
 * running UI operation. This application demonstrates its use.
 *
 *  SPDX-FileCopyrightText:  Copyright (C) 2024 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: BSD-2-Clause
 */

#include "busybutton.h"

#include <QApplication>
#include <QCheckBox>
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow * mw = new QMainWindow;
    QWidget * central = new QWidget(mw);
    QVBoxLayout * layout = new QVBoxLayout(central);

    QCheckBox * resultCheck = new QCheckBox("Success?");
    BusyButton * button = new BusyButton("Do It!", "Busy ...");

    layout->addWidget(resultCheck);
    layout->addWidget(button);

    mw->setCentralWidget(central);
    mw->show();

    QObject::connect(button, &QPushButton::clicked,
                     [resultCheck, button]()
                     {
                         QTimer * t = new QTimer;
                         if (resultCheck->isChecked())
                         {
                             QObject::connect(t, &QTimer::timeout, [t, button]() { button->operationDone(); t->deleteLater(); });
                         }
                         else
                         {
                             QObject::connect(t, &QTimer::timeout, [t, button]() { button->operationCanceled(); t->deleteLater(); });
                         }
                         button->operationStart();
                         t->start(3000);
                     });

    return app.exec();
}
