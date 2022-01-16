#include "pomodoroTimer.h"
#include <QTime>
#include <QTimer>

static const QString timeFormat_ = QString("mm:ss");

void PomodoroTimer::init()
{
    currentTime_.setHMS(0, settings_.pomoLength, 0);
}

PomodoroTimer::PomodoroTimer(const TimerSettings& s, QObject* parent) :
    settings_(s), QObject(parent)
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);

    init();
    connect(timer_, &QTimer::timeout, this, &PomodoroTimer::onTimer);
}

void PomodoroTimer::onTimer()
{
    static QTime zero(0, 0);
    currentTime_ = currentTime_.addSecs(-1);
    if (currentTime_.addSecs(-1) == zero) {
        this->stop();
    }
    emit currentTime(currentTime_.toString(timeFormat_));
}

void PomodoroTimer::start()
{
    init();
    timer_->start();
}

void PomodoroTimer::stop()
{
    timer_->stop();
    init();
    emit currentTime(currentTime_.toString(timeFormat_));
}


