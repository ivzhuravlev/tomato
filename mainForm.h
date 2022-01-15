#pragma once
#include <QMainWindow>

namespace Ui {
    class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

private:
    Ui::MainForm* ui;
};