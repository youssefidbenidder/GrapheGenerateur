#include <QApplication>
#include <QWidget>
#include <QDateTime>
#include "fenetreprincipale.h"
#include "graphscene.h"
int main(int argc, char *argv[]){

    QDateTime cd = QDateTime::currentDateTime();
    qsrand(cd.toTime_t());

    QApplication app(argc,argv);

    fenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
