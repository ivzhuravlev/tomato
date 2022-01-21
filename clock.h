#pragma once
#include <QObject>
#include <QTime>

class QTimer;

class Clock : public QObject
{
    Q_OBJECT
public:
    explicit Clock(const QTime& time, QObject* parent = nullptr);
    void setTime(const QTime&);
    QTime time() const;

signals:
    void time(const QTime&);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    QTime time_;
    QTimer* timer_;
};