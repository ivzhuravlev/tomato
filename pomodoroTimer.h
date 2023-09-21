#pragma once
#include <QObject>

class QTimer;
class QStateMachine;
class QMediaPlayer;
class Clock;

enum class PomodoroState
{
    Pomo,
    Break,
    Stop
};

struct TimerSettings
{
    int pomoLength = 1;         // 25 min
    int shortRestLength = 1;    // 5 min
    int longRestLength = 15;     // 15 min
    int pomoTillRest = 2;       // 5 items
};

class PomodoroTimer : public QObject
{
    Q_OBJECT
public:
    PomodoroTimer(const TimerSettings& s, QObject* parent = nullptr);

signals:
    void status(const QTime& time, PomodoroState state);
    void nextState();

public slots:
    void start();
    void stop();
    void pause();

private slots:
    void setTime(const QTime&);
    void setPomoState();
    void setRestState();
    void setStopState();

private:
    void resetTime();

    // QTime currentTime_;
    PomodoroState state_;
    TimerSettings settings_;

    // QTimer* timer_;
    QStateMachine* stateMachine_;
    QMediaPlayer* player_;
    Clock* clock_;
};