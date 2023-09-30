#pragma once
#include <QObject>
#include "timerSettings.h"

class QSettings;

class SettingsSerializer : public QObject
{
    Q_OBJECT
public:
    SettingsSerializer(const QString& org, const QString& app, QObject* parent = nullptr);

    void saveTimerSettings(const TimerSettings& s);
    TimerSettings loadTimerSettings() const;

    void saveWindowSettings(const QByteArray& geom, bool max);
    QByteArray loadWindowSettings(bool& max) const;

private:
    QSettings* settings_;
};