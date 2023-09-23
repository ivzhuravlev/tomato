#include <QApplication>
#include "mainForm.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("IZhuravlev");
	QCoreApplication::setApplicationName("tomato");
	// QCoreApplication::setApplicationVersion("1.1.0");

    MainForm mainForm;
    mainForm.show();
    return app.exec();
}