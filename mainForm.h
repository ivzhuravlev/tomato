#pragma once
#include <QMainWindow>
#include "pomodoroTimer.h"

namespace Ui {
    class MainForm;
}

class QLabel;

class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

public slots:
    void setState(const PomodoroStatus&);

private:
    Ui::MainForm* ui;
    QLabel* pomoCount;
};