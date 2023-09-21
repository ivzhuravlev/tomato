#include "pomodoroTimer.h"
#include "clock.h"
#include <QTime>
#include <QTimer>
#include <QStateMachine>
#include <QFinalState>
#include <QMediaPlayer>
#include <QFileInfo>

namespace {

void initPlayer(QMediaPlayer* p, bool first)
{
    if (first) {
        p->setMuted(true);
        p->play();
    } else {
        p->stop();
        p->setMuted(false);
    }
}

} // anonymous

void PomodoroTimer::resetTime()
{
    clock_->setTime(QTime(0, settings_.pomoLength));
    emit currentTime(clock_->getTime(), state_);
}

PomodoroTimer::PomodoroTimer(const TimerSettings& s, QObject* parent) :
    QObject(parent), settings_(s)
{
    // Clock Init   
    clock_ = new Clock(this);
    connect(clock_, &Clock::time, this, &PomodoroTimer::setTime);

    // State Machine Init
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

    state_ = PomodoroState::Stop;

    // Media Player Init
    player_ = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    QUrl bellFile = QUrl::fromLocalFile(QFileInfo("bell_long.wav").absoluteFilePath());
    player_->setMedia(bellFile);
    connect(restState, &QAbstractState::entered, player_, &QMediaPlayer::play);
    connect(stopState, &QAbstractState::entered, player_, &QMediaPlayer::play);
    initPlayer(player_, true);
}

void PomodoroTimer::setTime(const QTime&)
{
    emit currentTime(clock_->getTime(), state_);
    if (clock_->isZero()) {
        emit nextState();
    }
}

void PomodoroTimer::setPomoState()
{
    clock_->setTime(QTime(0, settings_.pomoLength));
    state_ = PomodoroState::Pomo;
    emit currentTime(clock_->getTime(), state_);
    clock_->start();
}

void PomodoroTimer::setRestState()
{
    clock_->setTime(QTime(0, settings_.shortRestLength));
    state_ = PomodoroState::Break;
    emit currentTime(clock_->getTime(), state_);
    clock_->start();
}

void PomodoroTimer::setStopState()
{
    clock_->stop();
    clock_->setTime(QTime(0, settings_.pomoLength));
    state_ = PomodoroState::Stop;
    emit currentTime(clock_->getTime(), state_);
}

void PomodoroTimer::start()
{
    initPlayer(player_, false);
    stateMachine_->start();
}

void PomodoroTimer::stop()
{
    stateMachine_->stop();
    setStopState();
}

void PomodoroTimer::pause()
{
    if (clock_->isActive()) {
        clock_->stop();
    } else {
        clock_->start();
    }
}

