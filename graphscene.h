#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QPointF>
#include <QLineEdit>
#include <random>
#include <QFileDialog>
#include <QTextEdit>
#include <QDebug>
#include "sommet.h"

//CLASS SCENE PRINCIPALE
class graphscene : public QGraphicsScene
{
    Q_OBJECT
public:
    graphscene();//CONSTRUCTEUR
    enum modechoisi {insererSommet ,insererArete,
                     selectionner,insererArc,supprimmer,insererJob,insererDebut,
                        insererFin};//afin d'etudier les cas des bouttons_slots
    void setModechoisi(modechoisi mode);//retourner le mode choisi
    bool isItemChange(int type);//afin de determiner si l'item est selectionner

    void revenir();//FONCTION REVENIR EN ARRIERE
    void alleravant();//FONTION ALLEZ EN AVANT

    QList <sommet *> sommetListe;//QLIST CONTENANT TOUT LES SOMMETS
    QList<arete *> areteliste;//QLIST CONTENANTS TOUTES LES ARETES
    QList<arc *> arcliste;//QLIST CONTENANTS TOUT LES ARCS
    QList<arc *> arcliste2;//QLIST TEMPORAIRE POUR RESOLUTION DU PROBLEME JOBSHOP
    QList<sommet *> sommetInitial;//QLIST CONTENANT LE SOMMETS INITIAL(vert)
    QList<sommet *> sommetFinal;//QLIST CONTENANT LE SOMMET FINAL(rouge)
    QList<sommet *> sommetinit;
    QList<sommet *>sommetFin;

    //algo potentiel
        double algoPotentiel(QList<sommet *> Liste);

    //fonction et valriables de la fonction aleatoire
        int a , b ,c ,d;//variable aleatoire
        void fonctionAleatoire();

    //fonctions de (enregistrer/ouvrir)
        void structure_scene(QString nom_de_fichier);//FONCTION D'ENREGISREMENT
        void ouvrir_scene(QString nom_de_fichier);//FONCTION POUR OUVRIR UN GRAPHE DEJA SAUVEGARDEE
        bool exist = false;
        bool exist2 = false;
        bool usedinit = false;
        bool usedFin = false;
        bool cliqueGauche;
        int nb_mach = 1;

    //pour mode job/machines
        QList<sommet *> jobSommet;
        bool job = false;
        bool creerjob = false;
        int nb_Job;
        void temps();

    //fonctions et variables de job shop
        QList<sommet *> sommetParcourt;
        QList< QList<sommet *> > population;
        void populationInitial();
        QList<int > tab;   //Liste pour les indices de fin et debut de chaque machines par rapport a les jobs
        QList<double >makespan;
        int selection();
        void croisement();
        void mutation();
        void rangement();
        bool cycle(QList<sommet *> Liste);
        void calcul_degre(QList<sommet *> Liste);
        void jobshop();

    //fonctions et variables de flow shop
        void flow_shop();
        static bool compare(QPoint a, QPoint b);
        int max(int a , int b);

    //POUR LA METHODE POTENTIEL
        QTextEdit *text = new QTextEdit();
protected:
    //FONCTIONS DE CREATION DES DIFERENTS ELEMENT DE GRAPHE
        void creerSommet(QPointF position, QString valSommet, QString valMachine, bool selected, int nb_Job, int modde, bool enregistrer);
        void creerArete(sommet * sourceSommet , sommet * destSommet, QString text);
        void creerArc(sommet * sourceSommet , sommet * destSommet, QString valarc);
        void supprimmerSommets();

    //LES DIFFERENTS EVENTS
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    modechoisi _mode;//mode choisi
    sommet *_sommet;//declaration de poiteur de sommet
    arete * _arete;//declaration de poiteur arete
    arc * _arc;//declaration de poiteur arc
    QGraphicsLineItem *line;//pour creation d'arete
    QLineEdit* pLineEdit;
    QGraphicsProxyWidget* pMyProxy;
    int val=0;//pour numeroter les sommets
    int val2=1;//pour numeroter les machines
    //LISTE UTILISE POUR RETOUR EN ARRIERE ET ALLER EN AVANT
        QList<int >revenirArriere;
        QList<int >allezAvant;
        QList<QPointF > tmpSommetArriere;
        QList<QPointF > tmpSommetAvant;

signals:

    void itemSelected(QGraphicsItem *item);
    void itemInserted(sommet *item);
};

#endif // GRAPHSCENE_H
