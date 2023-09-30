#include <QSettings>
#include "settingsSerializer.h"

SettingsSerializer::SettingsSerializer(const QString& org, const QString& app, QObject* parent)
    : QObject(parent), settings_(new QSettings(org, app, this))
{}

void SettingsSerializer::saveWindowSettings(const QByteArray& geom, bool max)
{
    settings_->beginGroup("WindowSettings");
    settings_->setValue("Maximized", max);
    if (!max) {
        settings_->setValue("Geometry", geom);
    }
    settings_->endGroup();
}

QByteArray SettingsSerializer::loadWindowSettings(bool& max) const
{
    settings_->beginGroup("WindowSettings");
    QByteArray result = settings_->value("Geometry").toByteArray();
    max = settings_->value("Maximized").toBool();
    settings_->endGroup();
    return result;
}

void SettingsSerializer::saveTimerSettings(const TimerSettings& s)
{
    settings_->beginGroup("TimerSettings");
    settings_->setValue("pomoLength", s.pomoLength);
    settings_->setValue("shortRestLength", s.shortRestLength);
    settings_->setValue("longRestLength", s.longRestLength);
    settings_->setValue("pomoTillRest", s.pomoTillRest);
    settings_->endGroup();
}

TimerSettings SettingsSerializer::loadTimerSettings() const
{
    TimerSettings result;
    return result;
}