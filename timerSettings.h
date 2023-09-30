#pragma once
#include <QTime>

struct TimerSettings
{
    QTime pomoLength = QTime(0,1);      // 25 min
    QTime shortRestLength = QTime(0,1); // 5 min
    QTime longRestLength = QTime(0,15); // 15 min
    int pomoTillRest = 5;               // 5 items

    bool valid() const;

    friend bool operator==(const TimerSettings& lhs, const TimerSettings& rhs);
    friend bool operator!=(const TimerSettings& lhs, const TimerSettings& rhs);
};
