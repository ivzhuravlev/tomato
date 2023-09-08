#include "mainForm.h"
#include "ui_mainForm.h"
#include "pomodoroTimer.h"

MainForm::MainForm(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->timerDisplay->display(QString("--:--"));

    TimerSettings settings;
    PomodoroTimer* pomoTimer = new PomodoroTimer(settings, this);

    // TODO вынести изменения в форме в отдельный слот
    connect(pomoTimer, &PomodoroTimer::currentTime,
            ui->timerDisplay, qOverload<const QString&>(&QLCDNumber::display));
    connect(ui->startButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::start);
    connect(ui->stopButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::pause);
}

MainForm::~MainForm()
{
    delete ui;
}