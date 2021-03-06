#include "pomodoroTimer.h"
#include <QTime>
#include <QTimer>
#include <QStateMachine>
#include <QFinalState>

static const QString timeFormat_ = QString("mm:ss");

void PomodoroTimer::resetTime()
{
    currentTime_.setHMS(0, settings_.pomoLength, 0);
    emit currentTime(currentTime_.toString(timeFormat_));
}

PomodoroTimer::PomodoroTimer(const TimerSettings& s, QObject* parent) :
    settings_(s), QObject(parent)
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &PomodoroTimer::onTimer);

    stateMachine_ = new QStateMachine(this);

    QState* pomoState = new QState();
    QState* restState = new QState();
    QFinalState* stopState = new QFinalState();

    connect(pomoState, &QAbstractState::entered, this, &PomodoroTimer::setPomoState);
    connect(restState, &QAbstractState::entered, this, &PomodoroTimer::setRestState);
    connect(stopState, &QAbstractState::entered, this, &PomodoroTimer::setStopState);

    pomoState->addTransition(this, &PomodoroTimer::nextState, restState);
    restState->addTransition(this, &PomodoroTimer::nextState, stopState);

    stateMachine_->addState(pomoState);
    stateMachine_->addState(restState);
    stateMachine_->addState(stopState);
    stateMachine_->setInitialState(pomoState);
}

void PomodoroTimer::onTimer()
{
    static const QTime zero(0, 0);
    currentTime_ = currentTime_.addSecs(-1);
    if (currentTime_.addSecs(-1) == zero) {
        emit nextState();
    }
    emit currentTime(currentTime_.toString(timeFormat_));
}

void PomodoroTimer::setPomoState()
{
    currentTime_.setHMS(0, settings_.pomoLength, 0);
    emit currentTime(currentTime_.toString(timeFormat_));
    timer_->start();
}

void PomodoroTimer::setRestState()
{
    currentTime_.setHMS(0, settings_.shortRestLength, 0);
    emit currentTime(currentTime_.toString(timeFormat_));
    timer_->start();
}

void PomodoroTimer::setStopState()
{
    currentTime_.setHMS(0, settings_.pomoLength, 0);
    emit currentTime(currentTime_.toString(timeFormat_));
    timer_->stop();
}

void PomodoroTimer::start()
{
    stateMachine_->start();

    // resetTime();
    // emit currentTime(currentTime_.toString(timeFormat_));
    // timer_->start();
}

void PomodoroTimer::stop()
{
    stateMachine_->stop();
    // timer_->stop();
    // resetTime();
    // emit currentTime(currentTime_.toString(timeFormat_));
}


