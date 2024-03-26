/**
 * BusyButton is a QWidget that helps a user start and stop a long-
 * running UI operation.
 *
 *  SPDX-FileCopyrightText:  Copyright (C) 2024 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef KDEDUDE_BUSYBUTTON_H
#define KDEDUDE_BUSYBUTTON_H

#include <QPushButton>

class BusyButton : public QPushButton
{
public:
    BusyButton(const QString & text, const QString & busyText, QWidget * parent = nullptr);

public Q_SLOTS:
    void operationStart();
    void operationDone();
    void operationCanceled();

private:
    QString m_text;
    QString m_busyText;
};

#endif
