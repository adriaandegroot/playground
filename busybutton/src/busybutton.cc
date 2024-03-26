/**
 * BusyButton is a QWidget that helps a user start and stop a long-
 * running UI operation.
 *
 *  SPDX-FileCopyrightText:  Copyright (C) 2024 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: BSD-2-Clause
 */

#include "busybutton.h"

BusyButton::BusyButton(const QString & text, const QString & busyText, QWidget * parent) : QPushButton(text, parent),
m_text(text), m_busyText(busyText)
{}


void BusyButton::operationStart()
{
    setText(m_busyText);
}

void BusyButton::operationDone()
{
    setText(m_text);
}

void BusyButton::operationCanceled()
{
    setText(m_text);
}
