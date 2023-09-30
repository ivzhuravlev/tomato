#include "settingsDialog.h"
#include "ui_settingsDialog.h"

SettingsDialog::SettingsDialog(const TimerSettings& s, QWidget* parent)
    : QDialog(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->pomoLengthEdit->setTime(s.pomoLength);
    ui->shortRestEdit->setTime(s.shortRestLength);
    ui->longRestEdit->setTime(s.longRestLength);
    ui->tillLongSpin->setValue(s.pomoTillRest);
}

TimerSettings SettingsDialog::timerSettings() const
{
    return TimerSettings {
        ui->pomoLengthEdit->time(),
        ui->shortRestEdit->time(),
        ui->longRestEdit->time(),
        ui->tillLongSpin->value()
    };
}
