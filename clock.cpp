#include "clock.h"
#include <QTimer>

Clock::Clock(const QTime& time, QObject* parent = nullptr) :
    time_(time)
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &Clock::onTimer);
}

void Clock::onTimer()
{
    emit time(time_);
    time_ = time_.addSecs(-1);
}

void Clock::start()
{
    timer_->start();
}

void Clock::stop()
{
    timer_->stop();
}

void Clock::setTime(const QTime& time)
{
    time_ = time;
}

QTime Clock::time() const
{
    return time_;
}