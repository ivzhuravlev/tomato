#include "mainForm.h"
#include "ui_mainForm.h"
#include <QTime>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QToolBar>
#include <QMenu>

static const QString timeFormat = QString("mm:ss");

static const QString clockStylePomo  = "QLCDNumber { background: rgba(208,70,67,255); color: white }";
static const QString clockStyleBreak = "QLCDNumber { background: rgba(86,189,86,255); color: white }";
static const QString clockStyleStop  = "QLCDNumber { background: #DDA129; color: white }";
static const QString labelBarStyle   = "QLabel { font-family: FreeMono }";
static const QString statusBarStyle  = "QStatusBar { border-top: 1px outset grey; }";

MainForm::MainForm(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->timerDisplay->display(QString("--:--"));
    ui->timerDisplay->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

    TimerSettings settings;
    PomodoroTimer* pomoTimer = new PomodoroTimer(settings, this);

    QLabel* pomoLabel = new QLabel(QString::fromUtf8("Pomo: "));
    pomoLabel->setStyleSheet(labelBarStyle);
    pomoCount = new QLabel(QString());
    pomoCount->setStyleSheet(labelBarStyle);

    QStatusBar* statusBar = new QStatusBar();
    statusBar->addPermanentWidget(pomoLabel);
    statusBar->addPermanentWidget(pomoCount, 1);
    statusBar->setStyleSheet(statusBarStyle);
    this->setStatusBar(statusBar);
    
    QToolBar* toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);
    QAction* settingsAct = new QAction(QIcon(":/res/settings.png"), QString(), this);
    toolBar->addAction(settingsAct);

    connect(pomoTimer, &PomodoroTimer::status, this, &MainForm::setState);
    connect(ui->startButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::start);
    connect(ui->stopButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, pomoTimer, &PomodoroTimer::pause);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::setState(const PomodoroStatus& s)
{
    ui->timerDisplay->display(s.time.toString(timeFormat));

    switch (s.state) {
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

    pomoCount->setText(QString::number(s.pomo));
}