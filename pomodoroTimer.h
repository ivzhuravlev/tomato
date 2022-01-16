#pragma once
#include <QObject>
#include <QTime>

class QTimer;

struct TimerSettings
{
    int pomoLength = 25;         // 25 min
    int shortRestLength = 5;    // 5 min
    int longRestLength = 15;     // 15 min
    int pomoTillRest = 5;       // 5 items
};


class PomodoroTimer : public QObject
{
    Q_OBJECT
public:
    PomodoroTimer(const TimerSettings& s, QObject* parent = nullptr);

signals:
    void currentTime(const QString& time);

public slots:
    void start();
    void stop();
    //void pause();

private slots:
    void onTimer();


private:
    void init();

    QTime currentTime_;
    QTimer* timer_;
    TimerSettings settings_;
};