#include "fenetreprincipale.h"
#include "arete.h"


//CONSTRUCTEUR...............................................
fenetrePrincipale::fenetrePrincipale(){
    afficheMenu();//affiche le menubar
    affichetoolTop();//affiche le toolbar
    affichetoolbox();//ajout de toolbox
    ajoutVue();
    ajoutValeur();
    afficheWidgetPrincipale();//affiche widget Principale
    this->setMinimumHeight(550);
    vue->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    vue->setDragMode(QGraphicsView::RubberBandDrag);
}

//FONCTION AFFICHE LE MENUBAR...........................................
void fenetrePrincipale::afficheMenu(){

    fichier = menuBar()->addMenu("&Fichier");
    //*************************************************
    nouveau = new QAction("&Nouveau fichier",this);
    nouveau->setShortcut(QKeySequence("Ctrl+B"));
    //signal_nouvelle_page
    connect(nouveau, SIGNAL(triggered()), this, SLOT(nouvelPage()));
    QPixmap imagedisplaynouveau(":/img/img/nouveau.png");
    QIcon icon_nouveau(imagedisplaynouveau);
    nouveau->setIcon(icon_nouveau);
    fichier ->addAction(nouveau);
    //**************************************************
    ouvrir = new QAction("&Ouvrir un fichier",this);
    ouvrir->setShortcut(QKeySequence("Ctrl+O"));
    QPixmap imagedisplayouvrir(":/img/img/ouvrir.png");
    QIcon iconouvrir(imagedisplayouvrir);
    ouvrir->setIcon(iconouvrir);
    connect (ouvrir, SIGNAL (triggered()), this , SLOT (ouvrirSlot()));
    fichier ->addAction(ouvrir);
    //**************************************************
    enregistrer = new QAction("&Enregistrer fichier",this);
    enregistrer->setShortcut(QKeySequence("Ctrl+S"));
    //signal_enregistrer
    connect(enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerSlot()));
    QPixmap imagedisplayenregistrer(":/img/img/enregistre.png");
    QIcon iconenregistrer(imagedisplayenregistrer);
    enregistrer->setIcon(iconenregistrer);
    fichier ->addAction(enregistrer);
    //**************************************************
    quitter = new QAction("&Quitter",this);
    quitter->setShortcut(QKeySequence("Ctrl+Q"));
    QPixmap imagedisplayquitter(":/img/img/quitter.png");
    QIcon iconquitter(imagedisplayquitter);
    quitter->setIcon(iconquitter);
    //signal_quitter
    connect(quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    fichier ->addAction(quitter);
    //*****************************************************
    //*****************************************************
    edition = menuBar()->addMenu("&Edition");
    revenir = new QAction("&Revenir en arriere",this);
    revenir->setShortcut(QKeySequence("Ctrl+Z"));
    QPixmap imagedisplayrevenir(":/img/img/back.png");
    QIcon iconrevenir(imagedisplayrevenir);
    revenir->setIcon(iconrevenir);
    //signal_revenir_arriere
    connect(revenir,SIGNAL(triggered()),this,SLOT(revenirSlot()));
    edition ->addAction(revenir);
    //**************************************************
    aller = new QAction("&Aller en avant",this);
    aller->setShortcut(QKeySequence("Ctrl+Y"));
    QPixmap imagedisplayaller(":/img/img/forwards.png");
    QIcon iconaller(imagedisplayaller);
    aller->setIcon(iconaller);
    //signal_revenir_arriere
    connect(aller,SIGNAL(triggered()),this,SLOT(allezSlot()));
    edition ->addAction(aller);
    //*********************************************************
    //*********************************************************
    affichage = menuBar()->addMenu("&Affichage");
    //*********************************************************
    //*********************************************************
    aide = menuBar()->addMenu("A&ide");
    visiter = new QAction("&besoin d'aide",this);
    visiter->setShortcut(QKeySequence("Ctrl+V"));
    QPixmap imagedisplayvisiter(":/img/img/help.png");
    QIcon iconvisiter(imagedisplayvisiter);
    visiter->setIcon(iconvisiter);
    aide ->addAction(visiter);
    //*********************************************************
    //*********************************************************
    propos = menuBar()->addMenu("A &propos");
    Apropos = new QAction("&A propos",this);
    Apropos->setShortcut(QKeySequence("Ctrl+P"));
    QPixmap imagedisplaypropos(":/img/img/help.png");
    QIcon iconpropos(imagedisplaypropos);
    Apropos->setIcon(iconpropos);
    propos->addAction(Apropos);
    //signal_apropos
    connect(Apropos, SIGNAL(triggered()), this, SLOT(explication()));
}

//SLOT POUR CREER NOUVELLE PAGE(declaration ligne 146)
void fenetrePrincipale::nouvelPage(){
    fenetrePrincipale *nouvelFenetre = new fenetrePrincipale();//class fenetrePrincipale
    nouvelFenetre->show();
}

//SLOT POUR OUVRIR UN DOSSIER EXISTANT(declaration ligne 147)
void  fenetrePrincipale :: ouvrirSlot () {
    QString nom_de_fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QDir::home().absolutePath(), "Graph fichier (*.grp)");
    qDebug() << nom_de_fichier;
    sene->ouvrir_scene(nom_de_fichier);
}

//SLOT POUR ENREGISTRER LE GRAPHE DANS UN NOUVEAU FICHIER
void  fenetrePrincipale::enregistrerSlot(){
    QString nom_de_fichier = QFileDialog::getSaveFileName(this, "Enregistrer sous", QDir::home().absolutePath(), "Graph fichier (*.grp)");
    qDebug() << nom_de_fichier;
    sene->structure_scene(nom_de_fichier);
}

//SLOT POUR REVENIR EN ARRIERE
void fenetrePrincipale::revenirSlot(){
    sene->revenir();
}

//SLOT POUR ALLER EN AVANT
void fenetrePrincipale::allezSlot(){
    sene->alleravant();
}

//SLOT POUR A PROPOS
void fenetrePrincipale::explication(){
    fenetrePropos *Prs = new fenetrePropos;//class fenetrePropos deja definie
}

//AFFICHER LA TOOLBOX...........................................
void fenetrePrincipale::affichetoolTop(){
    newAct = new QAction(QIcon(":/img/img/nouveau.png"), "&Nouveau", this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct,SIGNAL(triggered()),this,SLOT(nouvelPage()));

    openAct = new QAction(QIcon(":/img/img/ouvrir.png" ), "&Ouvrir", this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct,SIGNAL(triggered()),this,SLOT(ouvrirSlot()));

    saveAct = new QAction(QIcon(":/img/img/enregistre.png" ), "&Enregistrer", this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct,SIGNAL(triggered()),this,SLOT(enregistrerSlot()));

    deleteAct = new QAction(QIcon(":/img/img/supp.ico" ), "&Supprimer", this);
    deleteAct->setShortcuts(QKeySequence::Delete);
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(suppSlot()));

    copyAct = new QAction(QIcon(":/img/img/couper.png"), "&Couper", this);
    copyAct->setShortcuts(QKeySequence::Cut);
    connect(copyAct,SIGNAL(triggered()),this,SLOT(selectSlot()));

    backAct = new QAction(QIcon(":/img/img/back2.png" ), "&Back", this);
    connect(backAct,SIGNAL(triggered()),this,SLOT(revenirSlot()));

    forwardAct = new QAction(QIcon(":/img/img/forward.png" ), "&Forward", this);
    connect(forwardAct,SIGNAL(triggered()),this,SLOT(allezSlot()));

    startAct = new QAction(QIcon(":/img/img/play.png" ), "&Debug", this);
    connect(startAct,SIGNAL(triggered()),this,SLOT(debugSlot()));

    stopAct = new QAction(QIcon(":/img/img/stop.png" ), "&Stop", this);
    connect(stopAct,SIGNAL(triggered()),this,SLOT(stopSlot()));

    potentielAct = new QAction(QIcon(":/img/img/potentiel.png" ), "&Potentiel", this);
    connect(potentielAct,SIGNAL(triggered()),this,SLOT(potentielSlot()));

    cycleAct = new QAction(QIcon(":/img/img/cycle.png" ), "&Detection de cycle", this);
    connect(cycleAct,SIGNAL(triggered()),this,SLOT(cycleSlot()));

    infoAct = new QAction(QIcon(":/img/img/info.png" ), "&Info", this);
    connect(infoAct,SIGNAL(triggered()),this,SLOT(explication()));

    helpAct = new QAction(QIcon(":/img/img/help.png" ), "&Help", this);

    initialAct = new QAction(QIcon(":/img/img/green.png"),"&Sommet initial" , this);
    connect(initialAct,SIGNAL(triggered()),this,SLOT(initialSlot()));

    finalAct = new QAction(QIcon(":/img/img/red.png"),"&Sommet final" , this);
    connect(finalAct,SIGNAL(triggered()),this,SLOT(finalSlot()));

    sceneScale = new QComboBox;//pour pouvoir agrandir la scene
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScale->addItems(scales);
    sceneScale->setCurrentIndex(2);
    //signal de scenescale
    connect(sceneScale, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleslot(QString)));


    //ajout de toolbar et de ces elements...
    fileToolBar = this->addToolBar("Fichier");
    fileToolBar->setFixedHeight(40);
    fileToolBar->addAction(newAct);
    fileToolBar->addSeparator();//separateur
    fileToolBar->addAction(openAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(saveAct);

    debugToolBar = this->addToolBar("Debug");
    debugToolBar->setFixedHeight(40);
    debugToolBar->addAction(startAct);
    debugToolBar->addSeparator();
    debugToolBar->addAction(stopAct);

    editToolBar = this->addToolBar("Edition" );
    editToolBar->setFixedHeight(40);
    editToolBar->addAction(backAct);
    editToolBar->addSeparator();
    editToolBar->addAction(forwardAct);
    editToolBar->addSeparator();
    editToolBar->addAction(initialAct);
    editToolBar->addSeparator();
    editToolBar->addAction(finalAct);
    editToolBar->addSeparator();
    editToolBar->addAction(deleteAct);
    editToolBar->addSeparator();
    editToolBar->addAction(copyAct);
    editToolBar->addSeparator();
    editToolBar->addWidget(sceneScale);
    sceneScale->setFixedHeight(25);

    cylce_potentielToolBar = this->addToolBar("cycle/potentiel");
    cylce_potentielToolBar->setFixedHeight(40);
    cylce_potentielToolBar->addAction(potentielAct);
    cylce_potentielToolBar->addAction(cycleAct);

    infos = this->addToolBar("information");
    infos->setFixedHeight(40);
    infos->addAction(infoAct);
    infos->addSeparator();
    infos->addAction(helpAct);
}

//SLOT POUT AGRANDIR UNE SCENE(par defaut 100%)
void fenetrePrincipale::sceneScaleslot(const QString &scale){
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldscale = vue->matrix();
    vue->resetMatrix();
    vue->translate(oldscale.dx(), oldscale.dy());
    vue->scale(newScale, newScale);
}

//SLOT DE CREATION DE SOMMET INITIAL(marqué en vert)
void fenetrePrincipale::initialSlot(){
    sene->setModechoisi(graphscene::insererDebut);
}

//SLOT DE CREATION FINAL(marqué en rouge)
void fenetrePrincipale::finalSlot(){
    sene->setModechoisi(graphscene::insererFin);
}

//SLOT DE DEBUG
void fenetrePrincipale::debugSlot(){
    if(sene->sommetListe.isEmpty()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("alert");
        msgBox.setText("La scene ne contient pas d'elements");
        msgBox.exec();
    }
    else{
        if(probleme == false){
            sene->jobshop();
        }
        else{
            sene->flow_shop();
        }
    }
}

//SLOT D'ARRET
void fenetrePrincipale::stopSlot(){

}

//SLOT DE METHODE POTENTIEL
void fenetrePrincipale::potentielSlot(){
    sene->algoPotentiel(sene->sommetListe);
    sene->text->show();
}

//SLOT DE DETECTION DE CYCLE
void fenetrePrincipale::cycleSlot(){
    QMessageBox msgBox;
    if(sene->cycle(sene->sommetListe)){
        msgBox.setText("Ce graphe contient des cycles");
        msgBox.exec();
    }
    else{
        msgBox.setText("Ce graphe ne contient pas de cycle");
        msgBox.exec();
    }

}

//FONCTION WIDGET PRINCIPALE QUI CONTIENT TOUT LE DESIGN...............
void fenetrePrincipale::afficheWidgetPrincipale(){
    centre->setLayout(Hlayout);
    setCentralWidget(centre);
}

//SLOT QUI AFFICHE LA TOOLBOX
void fenetrePrincipale::affichetoolbox(){
    ajoutboutonBox();//ajout des bouttons dans la toolbox
    ajoutModeAleatoire();
    toolbox1->setLayout(vlayout);
    box1->addItem(toolbox1,"Creation");
    box1->addItem(aleatoirebox,"Aleatoire");
    box1->setFixedWidth(80);
    Hlayout->addWidget(box1);
}

//SLOT AJOUT DES BOUTTON AU TOOLBOX
void fenetrePrincipale::ajoutboutonBox(){
    b_sommet->setIconSize(QSize(20,20));
    b_sommet->setGeometry(70,10,100,160);
    b_sommet->setFocusPolicy(Qt::TabFocus);
    QString ImagePath1;
    ImagePath1 = ":/img/img/point.png";
    QPixmap imagedisplay1(ImagePath1);
    QIcon icon1(imagedisplay1);
    b_sommet->setIcon(icon1);
    connect(b_sommet, SIGNAL(clicked()), this, SLOT(sommetSlot()));
    vlayout->addWidget(b_sommet);

    b_jobs->setIconSize(QSize(20,20));
    b_jobs->setGeometry(70,10,100,160);
    b_jobs->setFocusPolicy(Qt::TabFocus);
    QString ImagePath0;
    ImagePath0 = ":/img/img/job.png";
    QPixmap imagedisplay0(ImagePath0);
    QIcon icon0(imagedisplay0);
    b_jobs->setIcon(icon0);
    connect(b_jobs, SIGNAL(clicked()), this, SLOT(jobSlot()));
    vlayout->addWidget(b_jobs);

    b_arete->setIconSize(QSize(20,20));
    b_arete->setGeometry(70,10,100,160);
    b_arete->setFocusPolicy(Qt::TabFocus);
    QString ImagePath2;
    ImagePath2 = ":/img/img/ligne.png";
    QPixmap imagedisplay2(ImagePath2);
    QIcon icon2(imagedisplay2);
    b_arete->setIcon(icon2);
    connect(b_arete, SIGNAL(clicked()), this, SLOT(areteSlot()));
    vlayout->addWidget(b_arete);


    b_arc->setIconSize(QSize(20,20));
    b_arc->setGeometry(70,10,100,160);
    b_arc->setFocusPolicy(Qt::TabFocus);
    QString ImagePath3;
    ImagePath3 = ":/img/img/arc.png";
    QPixmap imagedisplay3(ImagePath3);
    QIcon icon3(imagedisplay3);
    b_arc->setIcon(icon3);
    connect(b_arc, SIGNAL(clicked()), this, SLOT(arcSlot()));
    vlayout->addWidget(b_arc);


    b_supprimer->setIconSize(QSize(20,20));
    b_supprimer->setGeometry(70,10,100,160);
    b_supprimer->setFocusPolicy(Qt::TabFocus);
    QString ImagePath;
    ImagePath = ":/img/img/supp.ico";
    QPixmap imagedisplay(ImagePath);
    QIcon icon(imagedisplay);
    connect(b_supprimer, SIGNAL(clicked()), this, SLOT(suppSlot()));
    b_supprimer->setIcon(icon);
    vlayout->addWidget(b_supprimer);


    b_select->setIconSize(QSize(20,20));
    b_select->setGeometry(70,10,100,160);
    b_select->setFocusPolicy(Qt::TabFocus);
    QString ImagePath4;
    ImagePath4 = ":/img/img/click.png";
    QPixmap imagedisplay4(ImagePath4);
    QIcon icon4(imagedisplay4);
    connect(b_select, SIGNAL(clicked()), this, SLOT(selectSlot()));
    b_select->setIcon(icon4);
    vlayout->addWidget(b_select);
    vlayout->addStretch(0);//pour organiser le vlayout
}

//SLOT BOUTTON SOMMET
void fenetrePrincipale::sommetSlot(){
    stopAct->setEnabled(false);
    startAct->setEnabled(false);
    potentielAct->setEnabled(true);
    cycleAct->setEnabled(true);
    sene->job = false;
    foreach (sommet *som, sene->sommetListe) {
        som->pLineEdit2->hide();
    }
    sene->setModechoisi(graphscene::insererSommet);
}

//SLOT BOUTTON JOB
void fenetrePrincipale::jobSlot(){
    stopAct->setEnabled(true);
    startAct->setEnabled(true);
    potentielAct->setEnabled(false);
    cycleAct->setEnabled(false);
    sene->job = true;
    foreach (sommet *som, sene->sommetListe) {
        som->pLineEdit->hide();
    }
    sene->setModechoisi(graphscene::selectionner);
}

//SLOT BOUTTON ARETE
void fenetrePrincipale::areteSlot(){
    vue->setDragMode(QGraphicsView::NoDrag);
    sene->setModechoisi(graphscene::insererArete);
}

//SLOT BOUTTON ARC
void fenetrePrincipale::arcSlot(){
    vue->setDragMode(QGraphicsView::NoDrag);
    sene->setModechoisi(graphscene::insererArc);
}

//SLOT BOUTTON SELECT
void fenetrePrincipale::selectSlot(){
    sene->setModechoisi(graphscene::selectionner);
    vue->setDragMode(QGraphicsView::RubberBandDrag);
}

//SLOT BOUTTON SUPPRIMER
void fenetrePrincipale::suppSlot(){
    sene->setModechoisi(graphscene::supprimmer);
    vue->setDragMode(QGraphicsView::RubberBandDrag);
}

//FONTION D'AJOUT DES BOUTTONS DU MODE ALEATOIRE AU GENERATEUR
void fenetrePrincipale::ajoutModeAleatoire(){
    spinaleatoireSommet->setRange(0,100);
    spinaleatoireSommet->setSingleStep(1);
    spinaleatoireSommet->setValue(0);
    spinaleatoireSommet->setFixedWidth(60);
    spinaleatoireArete->setRange(0, 100);
    spinaleatoireArete->setSingleStep(1);
    spinaleatoireArete->setValue(0);
    spinaleatoireArete->setFixedWidth(60);
    spinaleatoireArc->setRange(0, 100);
    spinaleatoireArc->setSingleStep(1);
    spinaleatoireArc->setValue(0);
    spinaleatoireArc->setFixedWidth(60);
    vgroup->addWidget(text_sommet);
    vgroup->addWidget(spinaleatoireSommet);
    vgroup->addWidget(text_arete);
    vgroup->addWidget(spinaleatoireArete);
    vgroup->addWidget(text_arc);
    vgroup->addWidget(spinaleatoireArc);
    b_aleatoire->setFixedWidth(60);
    connect(b_aleatoire, SIGNAL(clicked()), this, SLOT(aleatoireSlot()));
    vgroup->addWidget(b_aleatoire);
    vgroup->addStretch(0);
    aleatoirebox->setLayout(vgroup);
}

//SLOT BOUTTON GO QUI PERMET DE GENERER UN GRAPHE ALEATOIRE
void fenetrePrincipale::aleatoireSlot(){
    sene->a = spinaleatoireSommet->value();
    sene->b = spinaleatoireArete->value();
    sene->c = spinaleatoireArc->value();
    sene->fonctionAleatoire();
}

//AJOUT D'UNE VIEW................................
void fenetrePrincipale::ajoutVue(){
    sene->setSceneRect(QRect(100,40,800,450));
    vue->setScene(sene);
    connect(sene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    vue->setMouseTracking(false);
    vue->setMinimumWidth(730);
    Hlayout->addWidget(vue);
}

//PARTIE AFFICHAGE VALEURS
void fenetrePrincipale::ajoutValeur(){
    valeur->setReadOnly(true);
    valeurlayout->addRow("Valeur:", valeur);
    b_algorithme->setFocusPolicy(Qt::TabFocus);

    QMenuBar *barre_algorithme = new QMenuBar; // On crée notre QMenuBar
    QMenu *menualgo = barre_algorithme->addMenu("&Sommet");
    QAction *actionalgo1 = menualgo->addAction("Job Shop");
    QAction *actionalgo2 = menualgo->addAction("Flow Shop");
    b_algorithme->setMenu(menualgo);
    //slots du menualgo
    connect(actionalgo1,SIGNAL(triggered()),this,SLOT(jobshopSlot()));
    connect(actionalgo2,SIGNAL(triggered()),this,SLOT(flowshopSlot()));

    valeurlayout->addRow(b_algorithme);
    valeurlayout->addRow("job :" , editJob);
    valeurlayout->addRow("machines : " , machine);
    valeurlayout->addRow(b_job);
    connect(b_job,SIGNAL(clicked()),this,SLOT(CreerJob()));
    valeurbox->setMaximumWidth(200);
    valeurbox->setLayout(valeurlayout);
    Hlayout->addWidget(valeurbox);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(MyTimerSlot()));
    timer->start(10);
}

//FONCTION QUI PERMET DE FAIRE UNE MISE A JOUR DES VALEURS
void fenetrePrincipale::MyTimerSlot(){
    if(sene->job == false){
        foreach (sommet *som, sene->sommetListe) {
            if(som->isSelected()){
                valeur->setText(som->valSommet);
            }
        }
        machine->setText("------------");
        editJob->setText("------------");
    }
    else if(sene->job == true){
        foreach(sommet *som,sene->sommetListe){
            if(som->isSelected()){
                machine->setText(som->valMachine);
                QString s = QString::number(som->sommetJob);
                editJob->setText(s);
            }
        }
        valeur->setText("------------");
    }
}

//SLOT DE CREATION DE JOB
void fenetrePrincipale::CreerJob(){
    stopAct->setEnabled(true);
    startAct->setEnabled(true);
    potentielAct->setEnabled(false);
    cycleAct->setEnabled(false);
    sene->creerjob = true;
    sene->job = true;
    sene->nb_Job = ii;
    ii++;
    sene->setModechoisi(graphscene::insererJob);
}

//SLOT DE L'ACTION JOB SHOP
void fenetrePrincipale::jobshopSlot(){
    probleme = false;
}

//SLOT DE L'ACTION DE FLOW SHOP
void fenetrePrincipale::flowshopSlot(){
    probleme = true;
}
