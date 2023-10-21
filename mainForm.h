#pragma once
#include <QMainWindow>

namespace Ui {
    class MainForm;
}

class QLabel;
class QAction;
class QSystemTrayIcon;
class SettingsSerializer;
class PomodoroTimer;
class PomoListWidget;
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
    void openPomoList();

private:
    Ui::MainForm* ui;
    PomodoroTimer* pomoTimer_;
    PomoListWidget* pomoList_;
    QLabel* pomoCount_;
    SettingsSerializer* settingsSeializer_;
    QSystemTrayIcon* tray_;
    QAction* trayInfo_;
};