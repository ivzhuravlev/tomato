#pragma once
#include <QMainWindow>
#include "pomodoroTimer.h"

namespace Ui {
    class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

public slots:
    void setState(const QTime& time, PomodoroState state);

private:
    Ui::MainForm* ui;
};