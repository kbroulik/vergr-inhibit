/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2021 Kai Uwe Broulik <kde@broulik.de>
*/

#include "notificationinhibition.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDebug>
#include <QPointer>

static const auto s_notificationService = QStringLiteral("org.freedesktop.Notifications");
static const auto s_notificationPath = QStringLiteral("/org/freedesktop/Notifications");
static const auto s_notificationInterface = QStringLiteral("org.freedesktop.Notifications");

NotificationInhibition::NotificationInhibition(const QString &appId, const QString &reason, QObject *parent)
    : QObject(parent)
{
    QDBusMessage msg = QDBusMessage::createMethodCall(s_notificationService,
                                                      s_notificationPath,
                                                      s_notificationInterface,
                                                      QStringLiteral("Inhibit"));
    msg.setArguments({
        appId,
        reason,
        QVariantMap() // reserved
    });

    QPointer<NotificationInhibition> guard(this);

    QDBusPendingCall pendingCall = QDBusConnection::sessionBus().asyncCall(msg);
    // There is no "this" context/parent as the watcher is supposed to outlive us so it can release
    // the inhibition should it get revoked before the call has finished
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall);
    connect(watcher, &QDBusPendingCallWatcher::finished, [guard, appId, reason](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<uint> reply = *watcher;
        watcher->deleteLater();

        if (reply.isError()) {
            qWarning() << "Failed to inhibit" << reply.error().message();
            return;
        }

        const auto cookie = reply.value();

        if (guard) {
            qDebug() << "Inhibited notifications for" << appId << "with reason" << reason << "and cookie" << cookie;
            guard->m_cookie = cookie;
        } else {
            uninhibit(cookie);
        }
    });
}

NotificationInhibition::~NotificationInhibition()
{
    if (m_cookie) {
        uninhibit(m_cookie);
    }
}

void NotificationInhibition::uninhibit(uint cookie)
{
    qDebug() << "Releasing inhibition with cookie" << cookie;
    QDBusMessage msg = QDBusMessage::createMethodCall(s_notificationService,
                                                      s_notificationPath,
                                                      s_notificationInterface,
                                                      QStringLiteral("UnInhibit"));
    msg.setArguments({cookie});
    QDBusConnection::sessionBus().call(msg, QDBus::NoBlock); // fire-and-forget
}
