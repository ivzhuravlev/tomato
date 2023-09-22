#pragma once
#include <QObject>
#include <QTime>

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
    int pomoTillRest = 5;       // 5 items
};

struct PomodoroStatus
{
    QTime time;
    PomodoroState state;
    int pomo = 0;
};

class PomodoroTimer : public QObject
{
    Q_OBJECT
public:
    PomodoroTimer(const TimerSettings& s, QObject* parent = nullptr);

signals:
    void status(const PomodoroStatus& status);
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
    int restLength() const;

    PomodoroState state_;
    TimerSettings settings_;
    int pomo_ = 0;

    QStateMachine* stateMachine_;
    QMediaPlayer* player_;
    Clock* clock_;
};