#include "pomodoroTimer.h"
#include <QTime>
#include <QTimer>
#include <QStateMachine>
#include <QFinalState>

static const QString timeFormat_ = QString("mm:ss");

void PomodoroTimer::resetTime()
{
    currentTime_.setHMS(0, settings_.pomoLength, 0);
    emit currentTime(currentTime_.toString(timeFormat_), currentState_);
}

PomodoroTimer::PomodoroTimer(const TimerSettings& s, QObject* parent) :
    settings_(s), QObject(parent)
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &PomodoroTimer::onTimer);

    currentState_ = PomodoroState::Stop;

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
    emit currentTime(currentTime_.toString(timeFormat_), currentState_);
    if (currentTime_ == zero) {
        emit nextState();
    }
}

void PomodoroTimer::setPomoState()
{
    currentTime_.setHMS(0, settings_.pomoLength, 0);
    currentState_ = PomodoroState::Pomo;
    emit currentTime(currentTime_.toString(timeFormat_), currentState_);
    timer_->start();
}

void PomodoroTimer::setRestState()
{
    currentTime_.setHMS(0, settings_.shortRestLength, 0);
    currentState_ = PomodoroState::Break;
    emit currentTime(currentTime_.toString(timeFormat_), currentState_);
    timer_->start();
}

void PomodoroTimer::setStopState()
{
    timer_->stop();
    currentTime_.setHMS(0, settings_.pomoLength, 0);
    currentState_ = PomodoroState::Stop;
    emit currentTime(currentTime_.toString(timeFormat_), currentState_);
}

void PomodoroTimer::start()
{
    stateMachine_->start();
}

void PomodoroTimer::stop()
{
    stateMachine_->stop();
    setStopState();
}

void PomodoroTimer::pause()
{
    if (timer_->isActive()) {
        timer_->stop();
    } else {
        timer_->start();
    }
}

