#pragma once
#include <QMainWindow>

namespace Ui {
    class MainForm;
}

class QLabel;
class SettingsSerializer;
class PomodoroTimer;
struct PomodoroStatus;

class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget* parent = nullptr);
    ~MainForm();

protected:
    void closeEvent(QCloseEvent* override);

private slots:
    void setState(const PomodoroStatus&);
    void openSettingsDialog();

private:
    Ui::MainForm* ui;
    PomodoroTimer* pomoTimer_;
    QLabel* pomoCount_;
    SettingsSerializer* settingsSeializer_;
};