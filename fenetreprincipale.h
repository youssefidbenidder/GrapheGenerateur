#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QToolBox>
#include <QComboBox>
#include <QGroupBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QLabel>
#include <QSpinBox>
#include <QPoint>
#include <QTimer>
#include <QFileDialog>
#include "fenetrepropos.h"
#include "graphscene.h"
#include "sommet.h"
#include "arete.h"

class fenetrePrincipale : public QMainWindow{
    Q_OBJECT
public :
    //CONSTRUCTEUR DE LA FENETRE PRINCIPALE
    fenetrePrincipale();

    //FONCTION APPELE EN CONSTRUCTEUR
    void afficheMenu();//affiche le menubar
    void affichetoolTop();//affiche le toolbar
    void afficheWidgetPrincipale();//widget Principale centrale
    void affichetoolbox();//ajout de toolbox
    void ajoutboutonBox();//ajout des bouttons dans la toolbox
    void ajoutVue();//ajout de view et definition de scene
    void ajoutModeAleatoire();
    void ajoutValeur();

    //NOMBRE DE JOBS
    int ii=1;

protected:
    //*********MENUBAR
    //*****************menu
    QMenu *fichier;
    QMenu *edition;
    QMenu *affichage;
    QMenu *aide;
    QMenu *propos;
    //******************sous_menu_fichier
    QAction *nouveau;
    QAction *ouvrir;
    QAction *enregistrer;
    QAction *quitter;
    //******************sous_menu_edition
    QAction *revenir;
    QAction *aller;
    //******************sous_menu_aide
    QAction *visiter;
    //******************fenetre_A_propos
    QAction *Apropos;
    //**********fin_menubar

    //************TOOLBAR
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* startAct;
    QAction* pauseAct;
    QAction* stopAct;
    QAction* backAct;
    QAction* forwardAct;
    QAction* deleteAct;
    QAction* copyAct;
    QAction* potentielAct;
    QAction* cycleAct;
    QComboBox* sceneScale;
    QAction* initialAct;
    QAction* finalAct;
    QAction* infoAct;
    QAction* helpAct;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QToolBar* debugToolBar;
    QToolBar* cylce_potentielToolBar;
    QToolBar* infos;
    //fin_toolbar
    //*********************************************************
    //*********************************************************

    //**********************************************************
    //************************************************************

    //INITIALISATION DU WIDGET PRINCIPALE.....................
    QWidget *centre = new QWidget;

    //TOOLBOX.................................................
    QToolBox *box1 = new QToolBox();
    QWidget *toolbox1 = new QWidget;
    //************Creation_de_bouttons
    QPushButton *b_sommet = new QPushButton();
    QPushButton *b_jobs = new QPushButton();
    QPushButton *b_arete = new QPushButton();
    QPushButton *b_arc = new QPushButton();
    QPushButton *b_supprimer = new QPushButton();
    QPushButton *b_select = new QPushButton();
    //Fin_toolbox
    //****************************************
    //****************************************

    //************CREATION DE LAYOUT
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *Hlayout = new QHBoxLayout;
    QVBoxLayout *vboxlayout = new QVBoxLayout;

    //************AJOUT DE VUE(VIEW)
    graphscene *sene = new graphscene();
    QGraphicsView *vue = new QGraphicsView(sene);

    //MODE ALEATOIRE...............................
    QGroupBox *aleatoirebox = new QGroupBox(tr("Aleatoire"));
    QLabel *text_sommet = new QLabel(tr("sommet:"));
    QSpinBox *spinaleatoireSommet = new QSpinBox;
    QLabel *text_arete = new QLabel(tr("arete:"));
    QSpinBox *spinaleatoireArete = new QSpinBox;
    QLabel *text_arc = new QLabel(tr("arc:"));
    QSpinBox *spinaleatoireArc = new QSpinBox;
    QPushButton *b_aleatoire = new QPushButton("GO!");
    //initialisation_de_layout_mode_aleatoire
    QVBoxLayout *vgroup = new QVBoxLayout;

    //VALEUR SOMMET_ARETE
    QFormLayout *valeurlayout = new QFormLayout;

    //VALEUR DE SOMMET(MACHINE,JOB...)............................
    QGroupBox *valeurbox = new QGroupBox(tr("Valeur :"));
    QLineEdit *valeur = new QLineEdit;
    QLineEdit *machine = new QLineEdit;
    QLineEdit *editJob = new QLineEdit;
    QPushButton *b_algorithme = new QPushButton("Problemes");
    QString mavaleur;
    QPushButton *b_job = new QPushButton("Creer job");

    //INITIALISER LE QTIMER QUI JOUERA LE ROLE D'INTERMEDIAIRE DE MISE A JOUR DES CHAMPS DE VALEURS(ligne:144->150)
    QTimer *timer;

    //TYPE DE PROBLEME TRAITEE
    bool probleme = false;
public slots:
    void nouvelPage();//pour ouvrir une nouvelle page
    void ouvrirSlot();//slot ouvrir un graphe deja enregistré
    void enregistrerSlot();//slot enregistrement de graphe
    void revenirSlot();//slot fleche revenir en arriere
    void allezSlot();//slot fleche aller en avant
    void explication();//slot à propos
    void sceneScaleslot(const QString &scale);//agrandi la scene
    void initialSlot();//slot qui permet de creer un sommet initial(marque en vert)
    void finalSlot();//slot qui permet de creer un sommet final(marqué en rouge)
    void debugSlot();//slot de debug
    void stopSlot();//slot qui arete l'algorithme
    void potentielSlot();//slot pour determiner la valeur de cout cmax et cmin d'un graphe grace a la methode potentiel
    void cycleSlot();//slot pour detecter les cycles
    void sommetSlot();//slot le boutton sommet
    void jobSlot();//slot boutton job
    void areteSlot();//slot boutton arete
    void arcSlot();//slot boutton arc
    void selectSlot();//slot pour selectionner sommet,arete et arc et pouvoir le deplacer
    void suppSlot();//slot suppression de sommet,arc et arete
    void aleatoireSlot();//slot de generation aleatoire de graphe
    void MyTimerSlot();//slot pour un setTimeout pour faire une mise à jour des champs valeurs toute les 10 ms
    void CreerJob();//slot qui permet de faciliter la creation de job
    void jobshopSlot();//slot qui active le jobshop
    void flowshopSlot();//slot qui active le flowshop

};

#endif // FENETREPRINCIPALE_H
