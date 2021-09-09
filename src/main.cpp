/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2021 Kai Uwe Broulik <kde@broulik.de>
*/

#include "notificationinhibition.h"
#include "windowwatcher.h"

#include <QDebug>
#include <QGuiApplication>
#include <QPointer>
#include <QWindow>

namespace {

static const auto s_shareToolbarTitle = QLatin1String("as_toolbar");

static QPointer<NotificationInhibition> s_inhibition;

void loadVergrInhibit()
{
    auto *watcher = new WindowWatcher(qGuiApp);
    QObject::connect(watcher, &WindowWatcher::windowAdded, [](QWindow *window) {
        if (window->title() == s_shareToolbarTitle) {
            qDebug() << "Share toolbar detected";
            if (s_inhibition) {
                qCritical() << "Already inhibiting, this should not happen!";
                return;
            }

            // Boo, Zoom does not set QGuiApplication::desktopFileName
            s_inhibition = new NotificationInhibition(QStringLiteral("Zoom"),
                                                      QCoreApplication::translate("vergrinhibit", "Screen share in progress"),
                                                      // TODO check if gc of that window might be delayed
                                                      window);
        }
    });

    qDebug() << "vergr-inhibit initialized!";
}

} // namespace

Q_COREAPP_STARTUP_FUNCTION(loadVergrInhibit)
