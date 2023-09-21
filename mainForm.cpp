#include "mainForm.h"
#include "ui_mainForm.h"
#include <QTime>

static const QString timeFormat = QString("mm:ss");

static const QString clockStylePomo = QString(
    "QLCDNumber { background: rgba(208,70,67,255); color: white }"
);
static const QString clockStyleBreak = QString(
    "QLCDNumber { background: rgba(86,189,86,255); color: white }"
);
static const QString clockStyleStop = QString();

MainForm::MainForm(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->timerDisplay->display(QString("--:--"));
    ui->timerDisplay->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

    TimerSettings settings;
    PomodoroTimer* pomoTimer = new PomodoroTimer(settings, this);

    connect(pomoTimer, &PomodoroTimer::status, this, &MainForm::setState);
    connect(ui->startButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::start);
    connect(ui->stopButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::pause);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::setState(const QTime &time, PomodoroState state)
{
    ui->timerDisplay->display(time.toString(timeFormat));

    switch (state) {
        case PomodoroState::Pomo:
            ui->timerDisplay->setStyleSheet(clockStylePomo);
            break;
        case PomodoroState::Break:
            ui->timerDisplay->setStyleSheet(clockStyleBreak);
            break;
        case PomodoroState::Stop:
            ui->timerDisplay->setStyleSheet(clockStyleStop);
            break;
    }
}