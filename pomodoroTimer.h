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
    QTime pomoLength = QTime(0,1);      // 25 min
    QTime shortRestLength = QTime(0,1); // 5 min
    QTime longRestLength = QTime(0,15); // 15 min
    int pomoTillRest = 5;               // 5 items
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
    QTime restLength() const;

    PomodoroState state_;
    TimerSettings settings_;
    int pomo_ = 0;

    QStateMachine* stateMachine_;
    QMediaPlayer* player_;
    Clock* clock_;
};