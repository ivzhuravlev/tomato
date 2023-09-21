#include "clock.h"
#include <QTimer>

static const QTime zero(0, 0);

Clock::Clock(QObject* parent) : Clock(zero, parent) {}

Clock::Clock(const QTime& time, QObject* parent) :
    QObject(parent), time_(time)
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &Clock::onTimer);
}

void Clock::onTimer()
{
    time_ = time_.addSecs(-1);
    emit time(time_);
}

void Clock::start()
{
    timer_->start();
}

void Clock::stop()
{
    timer_->stop();
}

void Clock::setTime(const QTime& t)
{
    time_ = t;
    emit time(time_);
}

QTime Clock::getTime() const
{
    return time_;
}

bool Clock::isZero() const
{
    return time_ == zero;
}

bool Clock::isActive() const
{
    return timer_->isActive();
}
