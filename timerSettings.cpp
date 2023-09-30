#include "timerSettings.h"

bool TimerSettings::valid() const
{
    return pomoLength.isValid()
        && shortRestLength.isValid()
        && longRestLength.isValid()
        && pomoTillRest > 0;
}

bool operator==(const TimerSettings& lhs, const TimerSettings& rhs)
{
    return lhs.pomoLength == rhs.pomoLength
        && lhs.shortRestLength == rhs.shortRestLength
        && lhs.longRestLength == rhs.longRestLength
        && lhs.pomoTillRest == rhs.pomoTillRest;
}

bool operator!=(const TimerSettings& lhs, const TimerSettings& rhs)
{
    return !(lhs == rhs);
}