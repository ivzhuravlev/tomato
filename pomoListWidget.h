#pragma once

#include <QWidget>

class PomoListWidget : public QWidget
{
public:
    PomoListWidget(QWidget* parent = nullptr);
    QSize sizeHint() const override;

    int specSize() const;
};