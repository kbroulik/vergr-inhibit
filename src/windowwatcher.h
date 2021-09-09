/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2021 Kai Uwe Broulik <kde@broulik.de>
*/

#pragma once

#include <QObject>

class QWindow;

/**
 * @brief Watch for creation/destruction of windows
 *
 * This class watches for toplevel windows being
 * created or destroyed (technically, watches for
 * the underlying platform surfaces)
 */
class WindowWatcher : public QObject
{
    Q_OBJECT

public:
    explicit WindowWatcher(QObject *parent = nullptr);
    ~WindowWatcher() override;

    Q_SIGNAL void windowAdded(QWindow *window);
    Q_SIGNAL void windowRemoved(QWindow *window);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

