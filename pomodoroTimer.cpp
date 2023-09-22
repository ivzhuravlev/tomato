#include "pomodoroTimer.h"
#include "clock.h"
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
    emit status({clock_->getTime(), state_, pomo_});
    if (clock_->isZero()) {
        emit nextState();
    }
}

void PomodoroTimer::setPomoState()
{
    state_ = PomodoroState::Pomo;
    ++pomo_;
    clock_->setTime(QTime(0, settings_.pomoLength));
    clock_->start();
}

void PomodoroTimer::setRestState()
{
    state_ = PomodoroState::Break;
    clock_->setTime(QTime(0, restLength()));
    clock_->start();
}

void PomodoroTimer::setStopState()
{
    clock_->stop();
    state_ = PomodoroState::Stop;
    clock_->setTime(QTime(0, settings_.pomoLength));
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

int PomodoroTimer::restLength() const
{
    int rest = 0;
    if (pomo_ % settings_.pomoTillRest == 0) {
        rest = settings_.longRestLength;
    } else {
        rest = settings_.shortRestLength;
    }
    return rest;
}

