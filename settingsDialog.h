#pragma once

#include <QDialog>

#include "timerSettings.h"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(const TimerSettings& s, QWidget* parent = nullptr);

    TimerSettings timerSettings() const;

private:
    Ui::SettingsDialog* ui;
};
