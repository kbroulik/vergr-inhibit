/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: 2021 Kai Uwe Broulik <kde@broulik.de>
*/

#pragma once

#include <QObject>

class QString;

/**
 * @brief RAII wrapper for Notification inhibitions
 *
 * This class inhibits notifications on creation and releases
 * it again on destruction
 */
class NotificationInhibition : public QObject
{
    Q_OBJECT

public:
    explicit NotificationInhibition(const QString &appId,
                                    const QString &reason,
                                    QObject *parent = nullptr);
    ~NotificationInhibition() override;

private:
    static void uninhibit(uint cookie);
    uint m_cookie = 0;
};

