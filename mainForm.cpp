#include "mainForm.h"
#include "ui_mainForm.h"
#include "pomodoroTimer.h"
#include "settingsDialog.h"
#include "settingsSerializer.h"
#include <QTime>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QtDebug>

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

    settingsSeializer_= new SettingsSerializer(qApp->organizationName(), qApp->applicationName(), this);
    pomoTimer_ = new PomodoroTimer(settingsSeializer_->loadTimerSettings(), this);
    pomoTimer_->setPomo(settingsSeializer_->loadDaySettings());
    connect(pomoTimer_, &PomodoroTimer::status, this, &MainForm::setState);

    ui->timerDisplay->display(pomoTimer_->settings().pomoLength.toString(timeFormat));
    ui->timerDisplay->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);
    ui->timerDisplay->setStyleSheet(clockStyleStop);

    QLabel* pomoLabel = new QLabel(QString::fromUtf8("Pomo: "));
    pomoLabel->setStyleSheet(labelBarStyle);
    pomoCount_ = new QLabel(QString());
    pomoCount_->setStyleSheet(labelBarStyle);
    pomoCount_->setText(QString::number(pomoTimer_->pomo()));

    QStatusBar* statusBar = new QStatusBar();
    statusBar->addPermanentWidget(pomoLabel);
    statusBar->addPermanentWidget(pomoCount_, 1);
    statusBar->setStyleSheet(statusBarStyle);
    this->setStatusBar(statusBar);
    
    QToolBar* toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);

    QAction* startAct = new QAction(QIcon(":res/play.svg"), QString());
    startAct->setText("Start");
    startAct->setToolTip("Start pomo timer");
    connect(startAct, &QAction::triggered, pomoTimer_, &PomodoroTimer::start);
    toolBar->addAction(startAct);

    QAction* pauseAct = new QAction(QIcon(":res/pause.svg"), QString());
    pauseAct->setText("Pause");
    pauseAct->setToolTip("Pause pomo timer");
    connect(pauseAct, &QAction::triggered, pomoTimer_, &PomodoroTimer::pause);
    toolBar->addAction(pauseAct);

    QAction* stopAct = new QAction(QIcon(":res/stop.svg"), QString());
    stopAct->setText("Stop");
    stopAct->setToolTip("Stop pomo timer");
    connect(stopAct, &QAction::triggered, pomoTimer_, &PomodoroTimer::stop);
    toolBar->addAction(stopAct);
    
    QAction* resetAct = new QAction(QIcon(":/res/reset.svg"), QString());
    resetAct->setText("&Reset count");
    resetAct->setToolTip("Reset pomo count");
    connect(resetAct, &QAction::triggered, [this](){ this->pomoTimer_->setPomo(0); });
    toolBar->addAction(resetAct);
    
    QAction* settingsAct = new QAction(QIcon(":/res/settings.svg"), QString());
    settingsAct->setText("&Settings");
    settingsAct->setToolTip("Settings");
    connect(settingsAct, &QAction::triggered, this, &MainForm::openSettingsDialog);
    toolBar->addAction(settingsAct);

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        tray_ = new QSystemTrayIcon(QIcon(":/res/tray.svg"), this);
        trayInfo_ = new QAction(QIcon(":/res/circle_stop.svg"),
            pomoTimer_->settings().pomoLength.toString(timeFormat));
        QMenu* trayMenu = new QMenu(this);
        trayMenu->addAction(trayInfo_);
        trayMenu->addSeparator();
        trayMenu->addAction(startAct);
        trayMenu->addAction(pauseAct);
        trayMenu->addAction(stopAct);
        trayMenu->addAction(resetAct);
        trayMenu->addAction(settingsAct);
        tray_->setContextMenu(trayMenu);
        tray_->show();
    } else {
        qDebug() << "tray is unavailble";
    }

    bool max;
    restoreGeometry(settingsSeializer_->loadWindowSettings(max));
    if (max) {
        showMaximized();
    }
    setWindowIcon(QIcon(":/res/tray.svg"));
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::closeEvent(QCloseEvent * override)
{
    settingsSeializer_->saveTimerSettings(pomoTimer_->settings());
    settingsSeializer_->saveDaySettings(pomoTimer_->pomo());
    settingsSeializer_->saveWindowSettings(saveGeometry(), isMaximized());
}

void MainForm::setState(const PomodoroStatus& s)
{
    const QString time = s.time.toString(timeFormat);
    ui->timerDisplay->display(time);

    switch (s.state) {
        case PomodoroState::Pomo:
            ui->timerDisplay->setStyleSheet(clockStylePomo);
            if (tray_) trayInfo_->setIcon(QIcon(":/res/circle_pomo.svg"));
            break;
        case PomodoroState::Break:
            ui->timerDisplay->setStyleSheet(clockStyleBreak);
            if (tray_) trayInfo_->setIcon(QIcon(":/res/circle_rest.svg"));
            break;
        case PomodoroState::Stop:
            ui->timerDisplay->setStyleSheet(clockStyleStop);
            if (tray_) trayInfo_->setIcon(QIcon(":/res/circle_stop.svg"));
            break;
    }

    pomoCount_->setText(QString::number(s.pomo));

    if (tray_) {
        trayInfo_->setText(time);
    }
}

void MainForm::openSettingsDialog()
{
    const auto& curSettings = pomoTimer_->settings();
    SettingsDialog* dialog = new SettingsDialog(curSettings, this);
    if (dialog->exec() == QDialog::Accepted) {
        TimerSettings newSettings = dialog->timerSettings();
        if (curSettings != newSettings) {
            pomoTimer_->setSettings(newSettings);
            settingsSeializer_->saveTimerSettings(newSettings);
        }
    }
}