/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2021 Kai Uwe Broulik <kde@broulik.de>
*/

#include "windowwatcher.h"

#include <QEvent>
#include <QGuiApplication>
#include <QPlatformSurfaceEvent>
#include <QWindow>

WindowWatcher::WindowWatcher(QObject *parent)
    : QObject(parent)
{
    qGuiApp->installEventFilter(this);
}

WindowWatcher::~WindowWatcher() = default;

bool WindowWatcher::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::PlatformSurface) {
        auto *pe = static_cast<QPlatformSurfaceEvent *>(event);

        // We don't care about offscreen surfaces
        if (auto *window = qobject_cast<QWindow *>(watched)) {
            switch (pe->surfaceEventType()) {
            case QPlatformSurfaceEvent::SurfaceCreated:
                Q_EMIT windowAdded(window);
                break;
            case QPlatformSurfaceEvent::SurfaceAboutToBeDestroyed:
                Q_EMIT windowRemoved(window);
                break;
            }
        }
    }

    return QObject::eventFilter(watched, event);
}
