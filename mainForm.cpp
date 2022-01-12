#include "mainForm.h"

MainForm::MainForm(QWidget* parent) :
    QWidget(parent), ui(std::make_unique<Ui::MainForm>())
{
    ui->setupUi(this);
}