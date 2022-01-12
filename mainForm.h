#pragma once
#include <QWidget>
#include <memory>

class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget* parent = nullptr);

private:
    std::unique_ptr<Ui::MainForm> ui;
}