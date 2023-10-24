#include "pomoListWidget.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QTableView>

PomoListWidget::PomoListWidget(QWidget* parent) :
    QWidget(parent)
{
    QAction* addAct = new QAction("Add");
    QAction* delAct = new QAction("Delete");

    QToolBar* tBar = new QToolBar();
    tBar->addAction(addAct);
    tBar->addAction(delAct);

    QTableView* tView = new QTableView();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tBar);
    layout->addWidget(tView);

    setLayout(layout);
}