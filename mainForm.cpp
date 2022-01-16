#include "mainForm.h"
#include "ui_mainForm.h"
#include "pomodoroTimer.h"

MainForm::MainForm(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->timerDisplay->display(QString("25:00"));

    TimerSettings settings;
    PomodoroTimer* pomoTimer = new PomodoroTimer(settings, this);

    connect(pomoTimer, &PomodoroTimer::currentTime,
            ui->timerDisplay, qOverload<const QString&>(&QLCDNumber::display));
    connect(ui->startButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::start);
    connect(ui->stopButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::stop);
}

MainForm::~MainForm()
{
    delete ui;
}