#include <QFileDialog>
#include <algorithm>
#include "graphscene.h"
#include "arete.h"
#include "sommet.h"
#include "fenetreprincipale.h"
//CONSTRUCTEUR................................
graphscene::graphscene(){
    //qApp->setStyleSheet("QLineEdit#nameEdit {  }");
    //on n'a rien fait en constructeur afin d'appeler le constructeur de la class QGraphicsScene
}

//MODE CHOISI EN GRAPHSCENE
void graphscene::setModechoisi(modechoisi mode){
    _mode = mode;//_mode est private
}

//**********************************************************
//FONCTION POUR CREER DES SOMMETS
void graphscene::creerSommet(QPointF position , QString valSommet , QString valMachine , bool selected , int valJob ,int modde, bool enregistrer){
    _sommet = new sommet();//definition du pointeur
    sommetListe << _sommet;
    _sommet->indexSommet = sommetListe.indexOf(_sommet);
    _sommet->setPos(position);
    addItem(_sommet);//pour ajouter à la scene
    if(enregistrer == false)
        _sommet->valSommet.append(QString("%1").arg(valSommet));
    else _sommet->valSommet = valSommet;
    _sommet->pLineEdit = new QLineEdit(_sommet->valSommet);
    _sommet->pMyProxy = new QGraphicsProxyWidget(_sommet);
    _sommet->pLineEdit->setMaximumWidth(50);
    _sommet->pMyProxy->setWidget(_sommet->pLineEdit);
    _sommet->pMyProxy->hide();
    _sommet->valMachine = valMachine;
    _sommet->pLineEdit2 = new QLineEdit(_sommet->valMachine);
    _sommet->pMyProxy2 = new QGraphicsProxyWidget(_sommet);
    _sommet->pLineEdit2->setMaximumWidth(30);
    _sommet->pMyProxy2->setWidget(_sommet->pLineEdit2);
    _sommet->setSelected(selected);
    _sommet->pMyProxy2->hide();
    _sommet->sommetJob = valJob;
    if(valJob != -1)
        jobSommet << _sommet;
    _sommet->modde = modde;
    revenirArriere.append(0);
}

//FONCTION POUR CREER DES ARETES
void graphscene::creerArete(sommet * sourceSommet , sommet * destSommet,QString text)
{
    _arete = new arete(sourceSommet, destSommet);
    areteliste.append(_arete);
    sourceSommet->ajouterArete(_arete);
    destSommet->ajouterArete(_arete);
    _arete->text->setPlainText(text);
    _arete->valArete = _arete->text->toPlainText().toDouble();
    addItem(_arete);
    _arete->adjustement();
    revenirArriere.append(1);
}

//FONCTION POUR CREER DES ARCS
void graphscene::creerArc(sommet * sourceSommet , sommet * destSommet , QString valarc){
    _arc = new arc(sourceSommet, destSommet);
    arcliste.append(_arc);
    sourceSommet->ajouterArc(_arc);
    destSommet->ajouterArc(_arc);
    _arc->text->setPlainText(valarc);
    _arc->valarc = _arc->text->toPlainText().toDouble();
    addItem(_arc);
    _arc->adjustement();
    revenirArriere.append(2);
}
//**********************************************************

//FONCTION POUR COMPARER ENTRE DEUX QPOINTS
bool graphscene::compare(QPoint a, QPoint b){
    return b.y() < a.y();
}

//FONCTION POUR DETECTER LE MAX ENTRE DEUX VALEURS
int graphscene::max(int a , int b){
    if(a > b)
        return a;
    else return b;
}

//MOUSE PRESS EVENT AU MOMENT DE CLICK................................
void graphscene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() != Qt::LeftButton)//click != click_gauche
        return;

    //AFFECTER LES VALEURS AU SOMMETS EN CHAQUE CLICK...!!!!!!!!!
    foreach (sommet *som, sommetListe) {
        if (som->isSelected()){
            som->valSommet = som->pLineEdit->text();
            som->valMachine = som->pLineEdit2->text();
            update();
        }
    }

    //TRAITEMENT DES DIFFERENTS CAS POSSIBLES
    switch (_mode ) {
    case insererArete://areteSlot
        foreach (sommet *som, sommetListe) {//faire disparaitre les QlineEdit
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        addItem(line);
        break;

    case insererArc://arcslot
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        addItem(line);
        break;

    default:

        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);

}

//DEPLACEMENT DE SOURIS....................................
void graphscene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){

    //qDebug() << mouseEvent->scenePos();
    if(!sommetListe.empty()){
        foreach (sommet *som, sommetListe) {
            if (som->isSelected()){
                som->valSommet = som->pLineEdit->text();
                som->valMachine = som->pLineEdit2->text();
            }
        }
    }

    if (_mode == insererArete && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }

    else if (_mode == insererArc && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }

    else if (_mode == selectionner) {//SELECTIONNER
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

}

//RELEASE DE SOURIS..........................................
void graphscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){

    if(_mode == insererJob && creerjob == false){
        return;
    }

    else if(_mode == insererSommet){//creation de sommet
        if(!isItemChange(sommet::Type)){
            foreach (sommet *som, sommetListe) {
                if(som->isSelected()){
                    som->setSelected(false);
                }
            }
            creerSommet(mouseEvent->scenePos(),QString::number(val),"0" ,true,-1,0,false);
            val++;
        }
    }

    else if(_mode == insererJob  && creerjob == true){
        if(mouseEvent->button() != Qt::RightButton){
            if(!isItemChange(sommet::Type)){
                foreach (sommet *som, sommetListe) {
                    if(som->isSelected()){
                        som->setSelected(false);
                    }
                }
                creerSommet(mouseEvent->scenePos(),QString::number(val),QString::number(val2),true,this->nb_Job,0,false);
                val++;
                val2++;
                cliqueGauche = true;
            }
        }
        else if(mouseEvent->button() == Qt::RightButton){
           if(cliqueGauche){
            creerjob = false;
            qDebug() << "rightbutton";
            int i = 0;
            sommetInitial.append(jobSommet.at(0));
            sommetFinal.append(jobSommet.last());
            if(usedinit){
                if(!sommetinit.isEmpty())
                creerArc(sommetinit.first(),sommetInitial.last(),"1");
            }
            if(usedFin){
                if(!sommetFin.isEmpty())
                creerArc(sommetFinal.last(), sommetFin.first(),"1");
            }
            if(jobSommet.length()!=1)
            while(i != (jobSommet.length()-1)){
                creerArc(jobSommet.at(i) , jobSommet.at(i+1),"1");
                i++;
            }
            val2=1;
            jobSommet.clear();
            cliqueGauche = false;
        }
        }
    }

    else if(_mode == insererDebut && usedinit == false){
        if(mouseEvent->button() != Qt::RightButton){
            if(!isItemChange(sommet::Type)){
                foreach (sommet *som, sommetListe) {
                    if(som->isSelected()){
                        som->setSelected(false);
                    }
                }
                creerSommet(mouseEvent->scenePos(),"initial","-1" ,true,-1,1,false);
                sommetinit << _sommet;
                usedinit = true;
                foreach(sommet *somet,sommetInitial){
                    creerArc(_sommet,somet,"0");
                    sommetInitial.clear();
                }
            }
        }
    }

    else if(_mode == insererFin && usedFin == false){
        if(mouseEvent->button() != Qt::RightButton){
            if(!isItemChange(sommet::Type)){
                foreach (sommet *som, sommetListe) {
                    if(som->isSelected()){
                        som->setSelected(false);
                    }
                }
                creerSommet(mouseEvent->scenePos(),"final","-1" ,true,-1,2,false);
                usedFin = true;
                sommetFin << _sommet;
                foreach(sommet * somet,sommetFinal){
                    creerArc(somet,_sommet,"1");
                    sommetFinal.clear();
                }
            }
        }
    }

    else if (line != 0 && _mode == insererArete) {//creation de l'arete
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();
        removeItem(line);
        delete line;


        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == sommet::Type &&
                endItems.first()->type() == sommet::Type &&
                startItems.first() != endItems.first()) {
            sommet *startItem = qgraphicsitem_cast<sommet *>(startItems.first());
            sommet *endItem = qgraphicsitem_cast<sommet *>(endItems.first());
            foreach (arete * ar, areteliste){
                if((ar->sourceSommet() == startItem && ar->destSommet() == endItem)
                        || (ar->sourceSommet() == endItem && ar->destSommet() ==startItem)){
                    exist = true;
                }

            }
            foreach (arc * ac, arcliste){
                if((ac->sourceSommet() == startItem && ac->destSommet() == endItem)
                        || (ac->sourceSommet() == endItem && ac->destSommet() ==startItem)){
                    exist2 = true;
                }

            }

            if(exist ==false && exist2 == false){
                creerArete(startItem,endItem,"1");
            }
            else if(exist == true && exist2 == false){
                exist = false;
            }
            else if(exist == false && exist2 == true){
                exist2 = false;
                foreach(arc * ac,arcliste){
                    if((ac->sourceSommet() == startItem && ac->destSommet() == endItem) ||
                            (ac->sourceSommet() == endItem && ac->destSommet() == startItem)){
                        int index = arcliste.indexOf(ac);
                        this->removeItem(ac);
                        ac->sourceSommet()->supprimerArc(ac);
                        ac->destSommet()->supprimerArc(ac);
                        if (index != -1)
                            arcliste.removeAt(index);
                        delete ac;
                    }
                }
                creerArete(startItem,endItem,"1");
            }
        }
    }

    else if (line != 0 && _mode == insererArc) {//creation de l'arc
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();
        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == sommet::Type &&
                endItems.first()->type() == sommet::Type &&
                startItems.first() != endItems.first()) {
            sommet *startItem = qgraphicsitem_cast<sommet *>(startItems.first());
            sommet *endItem = qgraphicsitem_cast<sommet *>(endItems.first());

                foreach (arc * ac, arcliste){
                    if((ac->sourceSommet() == startItem && ac->destSommet() == endItem)){
                        exist = true;
                    }
                }
                foreach (arete * ar, areteliste) {
                    if((ar->sourceSommet() == startItem && ar->destSommet() == endItem) ||
                            (ar->sourceSommet() == endItem && ar->destSommet() == startItem)){
                        exist = true;
                        qDebug() << "oki";
                    }

                }

            if(exist == false){
                creerArc(startItem,endItem,"1");
            }
            else{
                exist = false;
            }
        }
    }

    else if(_mode == supprimmer){//mode supprimer
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();

        }
        foreach (QGraphicsItem *item, this->selectedItems()) {
            if (item->type() == arc::Type) {
                removeItem(item);
                arc * _arc = qgraphicsitem_cast<arc *>(item);  // (item) why
                _arc->sourceSommet()->supprimerArc(_arc);
                _arc->destSommet()->supprimerArc(_arc);
                int index_arc = arcliste.indexOf(_arc);
                if (index_arc != -1)
                    arcliste.removeAt(index_arc);
                qDebug() << "supprimmer arc";
                delete _arc;
            }
        }
        foreach (QGraphicsItem *item, this->selectedItems()) {
            if (item->type() == arete::Type) {

                removeItem(item);
                arete * _arete = qgraphicsitem_cast<arete *>(item);  // (item) why
                _arete->sourceSommet()->supprimerArete(_arete);
                _arete->destSommet()->supprimerArete(_arete);
                int index_arete = areteliste.indexOf(_arete);
                if (index_arete != -1)
                    areteliste.removeAt(index_arete);
                qDebug() << "supprimmer arete";
                delete _arete;
            }
        }
        foreach (QGraphicsItem *item, this->selectedItems()) {
            if (item->type() == sommet::Type){
                foreach(sommet *som , sommetListe){
                    if(som->isSelected()){
                        int index = sommetListe.indexOf(som);
                        if (index != -1)
                            sommetListe.removeAt(index);
                        if(som->modde == 1 ){
                          sommetinit.clear();
                          usedinit = false;
                        }
                        else if(som->modde == 2)
                        {
                            sommetFin.clear();
                            usedFin = false;
                        }
                        else {
                            int index_sommetFinal = sommetFinal.indexOf(som);
                            if(index_sommetFinal != -1)
                                sommetFinal.removeAt(index_sommetFinal);
                            int index_sommetInitial = sommetInitial.indexOf(som);
                            if(index_sommetInitial != -1)
                                sommetInitial.removeAt(index_sommetInitial);
                        }
                    }
                    else {
                        som->indexSommet = sommetListe.indexOf(som);
                    }
                }

                sommet * somm = qgraphicsitem_cast<sommet *>(item);
                tmpSommetArriere.append(somm->scenePos());
                revenirArriere.append(3);
                foreach(arete *_arete ,somm->aretelist){
                    int index_arete = areteliste.indexOf(_arete);
                    if (index_arete != -1)
                        areteliste.removeAt(index_arete);
                }
                foreach(arc * _arc , somm->arclist){
                    int index_arc = arcliste.indexOf(_arc);
                    if (index_arc != -1)
                        arcliste.removeAt(index_arc);
                }
                somm->supprimerArcs();
                somm->supprimerAretes();
                this->removeItem(item);
                delete item;
            }
        }
    }

    if(!areteliste.empty()){
        foreach (arete *art, areteliste) {

            art->valArete = art->text->toPlainText().toDouble();

        }
    }

    if(!arcliste.empty()){
        foreach (arc *arx, arcliste) {
            arx->valarc = arx->text->toPlainText().toDouble();
        }
    }

    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

//DOUBLE CLICK.................................................
void graphscene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() != Qt::LeftButton)//click != click_gauche
        return;

    if(_mode == selectionner && job == false){
        if(!sommetListe.empty()){
            foreach (sommet *som, sommetListe) {
                if (som->isSelected()){
                    som->pMyProxy->show();
                    som->valSommet = som->pLineEdit->text();
                }
                else{
                    som->pMyProxy->hide();
                }
            }
        }
    }

    else if(_mode == selectionner && job == true){
        if(!sommetListe.empty()){
            foreach (sommet *som, sommetListe) {
                if (som->isSelected()){
                    som->pMyProxy2->show();
                    som->valMachine = som->pLineEdit2->text();
                }
                else{
                    som->pMyProxy2->hide();
                }
            }
        }
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

//SI L'ELEMENT EST SELECTIONNEE
bool graphscene::isItemChange(int type){//verifie si l'item estselectionner

    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type){
            return true;
        }
    }

    return false;
}

//FONCTION ALEATOIRE
void graphscene::fonctionAleatoire(){
    if(this->items().isEmpty()){
        int k,l,m,n;
        d=0;
        for(int j=0;j<a;j++){
            l = (qrand() % 570)+10;
            k = (qrand() % 1000)+10;

            creerSommet(QPointF(k,l),QString::number(val),"-1",true,-1,0,false); //il faut verifier si -1 ou bien aleatoire
            val++;
        }

        for(int j=0;j<b;j++){
            m = (qrand() % a);
            n = (qrand() % a);
            while(n==m){
                m = (qrand() % a);
                n = (qrand() % a);
            }

            creerArete(sommetListe.at(m),sommetListe.at(n),"1");

        }
        for(int j=0;j<c;j++){
            m = (qrand() % a);
            n = (qrand() % a);
            while(n==m){
                m = (qrand() % a);
                n = (qrand() % a);
            }

            creerArc(sommetListe.at(m),sommetListe.at(n),"1");

        }

    }

}

//FONCTION SUPPRESSEION TOUT LES SOMMETS
void graphscene::supprimmerSommets(){
    foreach(arc * _arc , arcliste){
        _arc->sourceSommet()->supprimerArc(_arc);
        _arc->destSommet()->supprimerArc(_arc);
        int index_arc = arcliste.indexOf(_arc);
        if (index_arc != -1)
            arcliste.removeAt(index_arc);
        removeItem(_arc);
        delete _arc;
    }

    foreach(arete * _arete , areteliste){
        _arete->sourceSommet()->supprimerArete(_arete);
        _arete->destSommet()->supprimerArete(_arete);
        int index_arete = areteliste.indexOf(_arete);
        if (index_arete != -1)
            areteliste.removeAt(index_arete);
        removeItem(_arete);
        delete _arete;

    }

    foreach(sommet * _sommet ,sommetListe ){
        _sommet->supprimerArcs();
        _sommet->supprimerAretes();
        int index = sommetListe.indexOf(_sommet);
        if (index != -1)
            sommetListe.removeAt(index);
        if(_sommet->modde == 1 ){
          sommetinit.clear();
          usedinit = false;
        }
        else if(_sommet->modde == 2)
        {
            sommetFin.clear();
            usedFin = false;
        }
        else {
            int index_sommetFinal = sommetFinal.indexOf(_sommet);
            if(index_sommetFinal != -1)
                sommetFinal.removeAt(index_sommetFinal);
            int index_sommetInitial = sommetInitial.indexOf(_sommet);
            if(index_sommetInitial != -1)
                sommetInitial.removeAt(index_sommetInitial);
        }
        removeItem(_sommet);
        delete _sommet;
    }
}

//FONCTION D'ENREGISTREMENT DE LA SCENE DANS LE FICHIER(.grp)
void graphscene::structure_scene(QString nom_de_fichier){

    int j = sommetListe.size();

    QString **matrice_adjacence = new QString*[j];
    for(int i = 0  ;i < j;i++){
        matrice_adjacence[i] = new QString[j];
        for(int k = 0; k < j ; k++){
            if(i == k)
                matrice_adjacence[i][k] = "0";
            else
                matrice_adjacence[i][k] = "-";
        }
    }

    foreach(QGraphicsItem *item, items()){

        if (item->type() == arete::Type){
            arete *_arete = qgraphicsitem_cast<arete *>(item);
            matrice_adjacence[_arete->sourceSommet()->indexSommet][_arete->destSommet()->indexSommet] = _arete->text->toPlainText();
            matrice_adjacence[_arete->destSommet()->indexSommet][_arete->sourceSommet()->indexSommet] = _arete->text->toPlainText();
        }

        if (item->type() == arc::Type){
            arc *_arc = qgraphicsitem_cast<arc *>(item);
            matrice_adjacence[_arc->sourceSommet()->indexSommet][_arc->destSommet()->indexSommet] = _arc->text->toPlainText();
        }
    }


    QFile fichier( nom_de_fichier );
    if ( fichier.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream stream( &fichier );
        stream << nb_Job << endl;
        stream << sommetListe.size() << endl;

        foreach (sommet *pos, sommetListe) {
            stream << pos->x() << ";" << pos->y() << ";" << pos->valSommet << ";"<<pos->valMachine <<";"<<pos->sommetJob <<";"<<pos->modde<<";"<<endl;
        }

        for(int i = 0 ; i < j ; i++ ){
            for (int k = 0; k < j ; k++){
                stream << matrice_adjacence[i][k]<<" ";
            }
            stream << endl;
        }

        fichier.close();

    }else {
        qDebug() << "impossible d'enregister le fichier";
    }
}

//FONCTION POUR OUVRIR LA SCENE ENREGISTRER(.grp)
void graphscene::ouvrir_scene(QString nom_de_fichier){

    bool deja = true;

    QFile fichier( nom_de_fichier );
    if ( fichier.open(QIODevice::ReadOnly | QIODevice::Text) )
    {

        supprimmerSommets();
        QString data;
        data = fichier.readLine();
        nb_Job = data.toInt();
        data = fichier.readLine();
        int r = data.toInt();
        val = r + 1;
        for(int i = 0 ; i < r; i++){

            data = fichier.readLine();

            QStringList list = data.split(';');
            qreal x = list.at(0).toDouble();
            qreal y = list.at(1).toDouble();
            QString valeur = list.at(2);
            QString valeurMachine = list.at(3);
            int z = list.at(4).toInt();
            int w = list.at(5).toInt();
            creerSommet(QPointF(x,y),valeur,valeurMachine,false,z,w,true);
        }
        for(int i = 0 ; i < r ;i++){

            data = fichier.readLine();

            QStringList list = data.split(" ");


            for(int K = 0;K < r ;K++){
                if(list.at(K) != "-"){

                    foreach(sommet *_sommet1, sommetListe){
                        if (_sommet1->indexSommet == i){
                            foreach(sommet *_sommet2, sommetListe){
                                if(_sommet2->indexSommet == K){
                                    foreach(arc *arx ,arcliste){
                                        if(arx->sourceSommet() == _sommet2 && arx->destSommet() == _sommet1 && arx->valarc == list.at(K).toDouble()){
                                            arx->sourceSommet()->supprimerArc(arx);
                                            arx->destSommet()->supprimerArc(arx);
                                            int index_arx = arcliste.indexOf(arx);
                                            if (index_arx != -1)
                                                arcliste.removeAt(index_arx);
                                            delete arx;
                                            deja = false;

                                        }}
                                    if(deja == false){
                                        if(_sommet1 != _sommet2)
                                            creerArete(_sommet1,_sommet2,list.at((K)));
                                    }


                                    else {
                                        if(_sommet1 != _sommet2)
                                            creerArc(_sommet1,_sommet2,list.at(K));
                                    }
                                    deja = true;

                                }
                            }
                        }

                    }
                }
            }
        }

        fichier.close();

    } else {
        qDebug() << "impossible d'ouvrir le fichier";
    }


}

//FONCTION POUR REVENIR EN ARRIERE
void graphscene::revenir(){
    int lengh = revenirArriere.length();
    if(lengh>0){
        if(revenirArriere.last() == 0){
            sommet * somm = qgraphicsitem_cast<sommet *>(sommetListe.last());
            foreach(arete *_arete ,somm->aretelist){
                int index_arete = areteliste.indexOf(_arete);
                if (index_arete != -1)
                    areteliste.removeAt(index_arete);
            }
            foreach(arc * _arc , somm->arclist){
                int index_arc = arcliste.indexOf(_arc);
                if (index_arc != -1)
                    arcliste.removeAt(index_arc);
            }
            somm->supprimerArcs();
            somm->supprimerAretes();
            allezAvant.append(0);
            tmpSommetAvant.append(somm->scenePos());
            this->removeItem(somm);
            sommetListe.removeLast();
            delete somm;
        }
        else if(revenirArriere.last() == 1 && areteliste.length()>0){
            arete * _aret = qgraphicsitem_cast<arete *>(areteliste.last());
            _aret->sourceSommet()->supprimerArete(_aret);
            _aret->destSommet()->supprimerArete(_aret);
            this->removeItem(_aret);
            areteliste.removeLast();
            delete(_aret);
        }
        else if(revenirArriere.last() == 2 && arcliste.length()>0){
            arc * _ar = qgraphicsitem_cast<arc *>(arcliste.last());
            _ar->sourceSommet()->supprimerArc(_ar);
            _ar->destSommet()->supprimerArc(_ar);
            this->removeItem(_ar);
            arcliste.removeLast();
            delete(_ar);
        }
        else if(revenirArriere.last() == 3){
            if(tmpSommetArriere.length()>0){
                allezAvant.append(1);
                creerSommet(tmpSommetArriere.last(),QString::number(val),"1" ,true,-1,0,false);
                tmpSommetArriere.removeLast();
            }
        }

        revenirArriere.removeLast();
    }

}

//FONCTION POUR ALLER EN AVANT
void graphscene::alleravant(){
    if(!allezAvant.empty()){
        if(allezAvant.last() == 0){
            creerSommet(tmpSommetAvant.last(),QString::number(val),"1" ,true,-1,0,false);
            tmpSommetAvant.removeLast();
            allezAvant.removeLast();
        }
        else if(allezAvant.last() == 1){
            sommet * somm = qgraphicsitem_cast<sommet *>(sommetListe.last());
            foreach(arete *_arete ,somm->aretelist){
                int index_arete = areteliste.indexOf(_arete);
                if (index_arete != -1)
                    areteliste.removeAt(index_arete);
            }
            foreach(arc * _arc , somm->arclist){
                int index_arc = arcliste.indexOf(_arc);
                if (index_arc != -1)
                    arcliste.removeAt(index_arc);
            }
            somm->supprimerArcs();
            somm->supprimerAretes();
            revenirArriere.append(3);
            tmpSommetArriere.append(somm->scenePos());
            this->removeItem(somm);
            sommetListe.removeLast();
            delete somm;
            allezAvant.removeLast();
        }

    }
}


//....................................................................................


//ALGORITHME GENERATION D'UNE POPULATION INITIALE(OPEN SHOP)
void graphscene::populationInitial(){
    //N.B dans cette algorithme on va utiliser arcliste2 (avec e2 à la fin) qui va contenir seulement
    //les arcs disjonctives puis on va l'ajoute a arclist de chaque sommet ,
    //et lorsque on termine et on va passe à un autre individu on va le supprimmer de l'arclist
    //affectation des valeurs des arcs à les sommets(temps de job sur machine)
    temps();

    //calcule de nombre de machines


    foreach(sommet *som ,sommetListe){
        if(som->valMachine.toInt() > nb_mach){
            nb_mach = som->valMachine.toInt();
        }

    }
    int i = 1;
    // la premiere proposition de solution
    //sommetParcourt designe individu qui va faire le parcourt pour remplir la population
    //tab un tableau pour les indices de fin-1 de chaque consécutif des machines
    while(i != nb_mach + 1 ){
        foreach(sommet *som , sommetListe){
            if(som->valMachine.toInt() == i){
                sommetParcourt.append(som);
            }
        }
        tab.append(sommetParcourt.length());
        i++;
    }

    if(!arcliste2.isEmpty()){
        arcliste2.clear();
    }

    // ajouter les arcs
    int n = 0;
    int j = 0;
    int k = tab.at(n) - 1;
    while(n != nb_mach){


        for(int i = j ; i < k ;i++){
            _arc = new arc(sommetParcourt.at(i), sommetParcourt.at(i+1));
            _arc->valarc = sommetParcourt.at(i)->temps;
            arcliste2.append(_arc);
        }

        j = tab.at(n);
        n++;
        if(n < tab.length())
            k = tab.at(n) - 1;
    }

    //ajoute des arcs de arcliste2 (disjonctives) au arclist de cahque sommet
    foreach(arc * ac , arcliste2){
        ac->destSommet()->arclist.append(ac);
        ac->sourceSommet()->arclist.append(ac);
    }

    int nmbre_population = 0;


    while (nmbre_population != 20) {

        //creation d'une liste des sommets temporaire qui contient les sommets de sommetParcourt
        //et les sommets de debut et fin
        QList<sommet *>sommetParcourt_tmp = sommetParcourt;
        foreach(sommet *som , sommetListe){
            if(som->modde == 1)
                sommetParcourt_tmp.prepend(som);
            else if (som->modde == 2)
                sommetParcourt_tmp.append(som);
        }

        //test de liste temporaire (indivisu)
        //Si valide on ajoute a la population

        if(!cycle(sommetParcourt_tmp) && population.contains(sommetParcourt) == false){
            qDebug() << sommetParcourt.length();
            //ajoute l'individu à la liste de population ainsi que leur makespan a liste de makespan
            population.append(sommetParcourt);
            makespan.append(algoPotentiel(sommetParcourt_tmp));
            nmbre_population++;
            qDebug() << nmbre_population;
        }

        //suppression des arcs disjonctives dans l'arclist de chaque sommet
        foreach(arc *ac, arcliste2){
            int indice_ac1 = ac->destSommet()->arclist.indexOf(ac);
            ac->destSommet()->arclist.removeAt(indice_ac1);
            int indice_ac2 = ac->sourceSommet()->arclist.indexOf(ac);
            ac->sourceSommet()->arclist.removeAt(indice_ac2);
            arcliste2.removeAt(arcliste2.indexOf(ac));
            delete ac;
        }


        if( nmbre_population != 20)  // stoper creation des individus et des arcs si le nombre de population est 20
        {

            int m3 = 0;//pour parcourt le nombre de machine
            int j3 = 0;//pour parcourt les indices de debut
            int k3 = tab.at(m3) - 1;//pour parcourt les indices de fin

            while(m3 != nb_mach){

                //choisir les indices de deux taches de la machine m3 aleatoiremet
                int rand1 = qrand() % (k3 + 1 - j3) + j3 ;
                int rand2 = qrand() % (k3 + 1 - j3) + j3 ;
                while(rand2 == rand1){
                    rand1 = qrand() % (k3 + 1 - j3) + j3 ;
                    rand2 = qrand() % (k3 + 1 - j3) + j3 ;
                }

                //PErmutation de deux taches
                sommetParcourt.swap(rand1,rand2);

                j3 = tab.at(m3);
                m3++;
                //verification de ne dépassement de taille de tab
                if(m3 < tab.length())
                    k3 = tab.at(m3) - 1;
            }

            // ajouter a nouveau les arcs
            int n2 = 0;
            int j2 = 0;
            int k2 = tab.at(n2) - 1;
            while(n2 != nb_mach){


                for(int i = j2 ; i < k2 ;i++){
                    _arc = new arc(sommetParcourt.at(i), sommetParcourt.at(i+1));
                    _arc->valarc = sommetParcourt.at(i)->temps;
                    arcliste2.append(_arc);
                }

                j2 = tab.at(n2);
                n2++;
                if(n2 < tab.length())
                    k2 = tab.at(n2) - 1;
            }
            //ajout les arcs dans arclist de chaque sommet
            foreach(arc * ac , arcliste2){
                ac->destSommet()->arclist.append(ac);
                ac->sourceSommet()->arclist.append(ac);
            }
        }
    }

}

//ALGORITHME DE SELECTION(JOB SHOP)
int  graphscene::selection(){
    //on va faire un selection par roulette tel que notre fitness est 1/makespan
    int random_individu_indice ;
    bool selectionner = false;
    while(selectionner == false){
        double somme_fitness = 0;
        //calcule de la somme de fitnesse
        foreach(double a , makespan){
            somme_fitness = somme_fitness + 1/a;
        }
        //choix d'indice d'individu aleatoirement
        random_individu_indice = qrand() % population.length();
        double fitness = 1/makespan.at(random_individu_indice);
        double proba_de_select = fitness/somme_fitness;//calcule de la probabilité
        double x =qrand() % 1;//nombre aleatoirement entre 0 et 1

        if(x < proba_de_select)
            selectionner = true;

    }
    return random_individu_indice;
}

//ALGORITHME DE CROISSEMENT(JOB SHOP)
void graphscene::croisement(){
    int essai = 0;
    int repeter = 0;

    //selectionne de deux individus parents
    int indice_parent1 = selection();
    int indice_parent2 = selection();

    while(indice_parent1 == indice_parent2){
        indice_parent2 = selection();
    }

    QList<sommet *> parent1 = population.at(indice_parent1);
    QList<sommet *> parent2 = population.at(indice_parent2);

    while(repeter != 2 && essai != 20){
        //cross-over et creation de deux enfants (repeter != 2 )
        //choix d'une machine aleatoire
        QList<sommet *> enfant;
        int indice_debut;
        int indice_fin;
        int mach_aleat = qrand() % nb_mach;
        for(int i = 0 ; i < nb_mach ; i++ ){
            if(i == 0){
                indice_debut = 0;
            }
            else
                indice_debut = tab.at(i-1);

            indice_fin = tab.at(i) - 1;
            //le 1er enfant reçoit les mêmes affectations que parent1.
            //le 2eme enfant reçoit les mêmes affectations que indiv2.
            if(i != mach_aleat){
                for(int j = indice_debut; j <= indice_fin ; j++){
                    if(repeter == 0)
                        enfant.append(parent1.at(j));
                    else enfant.append(parent2.at(j));
                }
            }
            //le 1er enfant reçoit les affectations de parent2.
            //le 2eme enfant reçoit les affectations de parent1.

            else if(i == mach_aleat){
                for(int j = indice_debut; j <= indice_fin ; j++){
                    if(repeter == 0)
                        enfant.append(parent2.at(j));
                    else
                        enfant.append(parent1.at(j));
                }
            }
        }
        //ajout des arcs et test de realisabilité
        int  n = 0;
        int j = 0;
        int k = tab.at(n) - 1;
        while(n != nb_mach){
            for(int i = j ; i < k ;i++){
                _arc = new arc(enfant.at(i), enfant.at(i+1));
                _arc->valarc = enfant.at(i)->temps;
                arcliste2.append(_arc);
            }

            j = tab.at(n);
            n++;
            if(n < tab.length())
                k = tab.at(n) - 1;
        }

        foreach(arc * ac , arcliste2){
            ac->destSommet()->arclist.append(ac);
            ac->sourceSommet()->arclist.append(ac);
        }

        QList<sommet *>enfant_tmp = enfant;

        foreach(sommet * som,sommetListe){
            if(som->modde == 1)
                enfant_tmp.prepend(som);
            else if(som->modde == 2)
                enfant_tmp.append(som);

        }

        if(!cycle(enfant_tmp)){
            population.append(enfant);
            makespan.append(algoPotentiel(enfant_tmp));
            repeter++;
        }
        //supression des arcs disjonctives de arclist
        foreach(arc *ac, arcliste2){
            int indice_ac1 = ac->destSommet()->arclist.indexOf(ac);
            ac->destSommet()->arclist.removeAt(indice_ac1);
            int indice_ac2 = ac->sourceSommet()->arclist.indexOf(ac);
            ac->sourceSommet()->arclist.removeAt(indice_ac2);
            arcliste2.removeAt(arcliste2.indexOf(ac));
            delete ac;
        }
        essai++;

    }

}

//ALGORITHME DE MUTATION(JOB SHOP)
void graphscene::mutation(){
    bool repeter = true;
    int max_iteration = 0;//nombre max d'iteration
    for(int i = 0;i <population.length() ;i++){
    while(repeter && max_iteration != 20){

        //selectionne un individu
        QList<sommet *>individu = population.at(i);
        int mach_aleat = qrand() % nb_mach;
        int indice_debut;
        int indice_fin;

        QList<sommet *> individu_mute;

        for(int i = 0 ; i < nb_mach ; i++ ){
            if(i == 0){
                indice_debut = 0;
            }
            else
                indice_debut = tab.at(i-1);

            indice_fin = tab.at(i) - 1;

            if(i != mach_aleat){
                for(int j = indice_debut; j <= indice_fin ; j++){
                    individu_mute.append(individu.at(j));
                }
            }
            //permuter deux taches dans machine chosi
            else if(i == mach_aleat){
                int rand1 = qrand() % (indice_fin + 1 - indice_debut) + indice_debut ;
                int rand2 = qrand() % (indice_fin + 1 - indice_debut) + indice_debut ;
                while(rand2 == rand1){
                    rand1 = qrand() % (indice_fin + 1 - indice_debut) + indice_debut ;
                    rand2 = qrand() % (indice_fin + 1 - indice_debut) + indice_debut ;
                }
                for(int j = indice_debut; j <= indice_fin ; j++){
                    if(j == rand1){
                        individu_mute.append(individu.at(rand2));
                    }
                    else if(j == rand2){
                        individu_mute.append(individu.at(rand1));
                    }
                    else
                        individu_mute.append(individu.at(j));
                }

            }
        }

        //creation des arcs disjonctives

        int  n = 0;
        int j = 0;
        int k = tab.at(n) - 1;
        while(n != nb_mach){
            for(int i = j ; i < k ;i++){
                _arc = new arc(individu_mute.at(i), individu_mute.at(i+1));
                _arc->valarc = individu_mute.at(i)->temps;
                arcliste2.append(_arc);
            }

            j = tab.at(n);
            n++;
            if(n < tab.length())
                k = tab.at(n) - 1;
        }

        foreach(arc * ac , arcliste2){
            ac->destSommet()->arclist.append(ac);
            ac->sourceSommet()->arclist.append(ac);
        }

        //test de realisabilité d'individu_mute

        QList<sommet *>individu_mute_tmp = individu_mute;

        foreach(sommet * som,sommetListe){
            if(som->modde == 1)
                individu_mute_tmp.prepend(som);
            else if(som->modde == 2)
                individu_mute_tmp.append(som);

        }

        if(!cycle(individu_mute_tmp)){
            int makespan_tmp = algoPotentiel(individu_mute_tmp);
            if(makespan.at(i) > makespan_tmp){
            population[i] = individu_mute;
            makespan[i] = makespan_tmp;
            repeter = false;
            }
        }
        foreach(arc *ac, arcliste2){
            int indice_ac1 = ac->destSommet()->arclist.indexOf(ac);
            ac->destSommet()->arclist.removeAt(indice_ac1);
            int indice_ac2 = ac->sourceSommet()->arclist.indexOf(ac);
            ac->sourceSommet()->arclist.removeAt(indice_ac2);
            arcliste2.removeAt(arcliste2.indexOf(ac));
            delete ac;
        }

        max_iteration++;

    }
}
}

//ALGORITHME DE RANGEMENT(JOB SHOP)
void graphscene::rangement(){
    //ranger les individus par leur makespan et choisir les meilleures
    QList< QList<sommet *> > population_tempo;
    QList<int > makespan_tempo;

    while(!population.isEmpty()){
        int indice = 0;

        for(int i = 1 ; i < population.length() ; i++){
            if(makespan.at(indice) > makespan.at(i))  // fitness doit remplir dans population initial
                indice = i;
        }

        population_tempo.append(population.at(indice));
        population.removeAt(indice);
        makespan_tempo.append(makespan.at(indice));
        makespan.removeAt(indice);

    }

    for(int i = 0; i < 20 ;i++){
        population.append(population_tempo.at(i));
        makespan.append(makespan_tempo.at(i));
    }

}

//ALGORITHME GENETIC POUR PROBLEME JOB SHOP
void graphscene::jobshop(){
    QTextEdit *txt = new QTextEdit();
    txt->setReadOnly(true);
    txt->append("<h2>Resultat du probleme job shop :</h2>");
    if(!sommetListe.isEmpty()){
        int iteration = 0;
        populationInitial();

        while (iteration != 10) { //10 generations
            for(int i = 0 ;i < 10 ;i++){
                croisement();
            }
            mutation();
            rangement();
            iteration++;
        }
        for(int i = 0; i<population.at(0).length() ; i++){
            qDebug()<< population.at(0).at(i)->sommetJob <<";" <<population.at(0).at(i)->valMachine;
            if(population.at(0).at(i)->temps != 0)
                txt->append("Machine :" + population.at(0).at(i)->valMachine + " ,job :" + QString::number(population.at(0).at(i)->sommetJob)) ;
        }
        txt->append("le cout(makespan) est de : " + QString::number(makespan.at(0)));
        qDebug()<< "makespan est :"<<makespan.at(0);
        population.clear();
        makespan.clear();
        tab.clear();
        sommetParcourt.clear();
        nb_mach = 1;
    }

    txt->show();
}

//DEGREE d-
void graphscene::calcul_degre(QList<sommet *> Liste){
    //cette fonction calcule les degres d-
    foreach(sommet *som , Liste){
        som->degre = 0;
    }

    foreach(sommet * som , Liste){
        foreach(arc * ac , som->arclist)
        {
            if(ac->sourceSommet() == som){
                ac->destSommet()->degre++;
            }
        }
    }
}

//ALGORITHME DE DETECTION DE CYCLE
bool graphscene::cycle(QList<sommet *> Liste){

    calcul_degre(Liste);//les desgres d-

    QList<sommet *> a_traiter;
    int nmbr = 0;
    //le premier niveau
    foreach(sommet * som,Liste){
        if(som->degre == 0){
            a_traiter.append(som);
            nmbr++;
        }
    }

    while(!a_traiter.isEmpty()){
        sommet *som = a_traiter.first();
        a_traiter.removeAt(0);
        foreach(arc * ac , som->arclist){
            if(ac->sourceSommet() == som ){
                ac->destSommet()->degre--;
                if(ac->destSommet()->degre == 0){
                    a_traiter.append(ac->destSommet());
                    nmbr++;
                }
            }
        }

    }

    if (nmbr == Liste.length() && areteliste.isEmpty() ){
        qDebug() << "sans cycle";
        return false;
    }
    else{
        qDebug() << "cycle";
        return true;
    }
}

//CALCULE DE TEMPS POUR PROBLEME DE FLOW SHOP
void graphscene::temps(){
    //le temps d'execution de chaque tache est la valeur dans l'arc successeur
    foreach(sommet *som ,sommetListe){
        foreach(arc * ac , som->arclist){
            if(som == ac->sourceSommet()){
                som->temps = ac->valarc;
            }
        }
    }
}

//IMPLEMENTATION DE L'ALGORITHME DE FLOW SHOP
void graphscene::flow_shop(){
    QTextEdit *txt = new QTextEdit();
    txt->setReadOnly(true);
    txt->append("<h2>Resultat du probleme flow shop :</h2>");
    temps();
    int T_solution = 10000000;
    QList<QPoint > solution;
    int permuter = 0;

    foreach(sommet *som ,sommetListe){
        if(som->valMachine.toInt() > nb_mach){
            nb_mach = som->valMachine.toInt();
        }
    }

    int **job_temps = new int*[nb_mach];//matrice de temps
    for (int i = 0; i < nb_mach; i++)
        job_temps[i] = new int[nb_Job];

    for(int i = 0; i < nb_mach; i++){   //initialisataion de matrice de temps
        for(int j = 0; j < nb_Job; j++){
            foreach(sommet * som , sommetListe){
                if(som->valMachine.toInt() == i+1 && som->sommetJob == j+1){
                    job_temps[i][j] = som->temps;
                    qDebug() << job_temps[i][j];
                }
            }
        }
    }

    QList<QPoint > temps_total;    // y est le temps total pour chaque job et x le numero de job
    for(int i = 0; i < nb_Job ; i++){
        int s = 0;
        for(int j = 0 ; j < nb_mach ; j++){
            s = s + job_temps[j][i];
        }
        QPoint tmp;
        tmp.setX(i);
        tmp.setY(s);
        temps_total.append(tmp);
    }
    qSort(temps_total.begin(),temps_total.end() , compare);// tri decroissant

    QList<QPoint > jobs; // les job pour traiter
    jobs.append(temps_total.at(0));
    jobs.append(temps_total.at(1));
    temps_total.removeAt(0);
    temps_total.removeAt(0);


    //le cas de deux jobs
    while(permuter != jobs.length()){

        qDebug() << "---------"<<permuter<<"--------";

        int **diagramme_matrice = new int*[nb_mach];//matrice de diagramme
        for (int i = 0; i < nb_mach; i++)
            diagramme_matrice[i] = new int[jobs.length()];

        for(int i = 0; i < jobs.length(); i++){   //initialisataion de matrice de diagramme
            for(int j = 0; j < nb_mach; j++){
                if(i == 0 && j == 0){
                    diagramme_matrice[j][i] = job_temps[j][jobs.at(i).x()];
                    qDebug() << diagramme_matrice[j][i];
                }
                else if(i == 0 && j !=0){
                    diagramme_matrice[j][i] = diagramme_matrice[j-1][i] + job_temps[j][jobs.at(i).x()];
                    qDebug() << diagramme_matrice[j][i];
                }
                else if(i != 0 && j == 0){
                    diagramme_matrice[j][i] = diagramme_matrice[j][i-1]+job_temps[j][jobs.at(i).x()];
                    qDebug() << diagramme_matrice[j][i];
                }
                else {
                    diagramme_matrice[j][i] = max(diagramme_matrice[j-1][i] , diagramme_matrice[j][i-1]) + job_temps[j][jobs.at(i).x()];
                    qDebug()<< "le max ext:" << max(diagramme_matrice[j-1][i] , diagramme_matrice[j][i-1]);
                    qDebug() << diagramme_matrice[j][i];
                }
            }

        }

        int T = diagramme_matrice[nb_mach - 1][jobs.length()-1];
        qDebug() << diagramme_matrice[nb_mach - 1][jobs.length()-1];
        if(T < T_solution){
            T_solution = T;
            solution = jobs;
        }
        jobs.swap(0,1);
        permuter++;

        for (int i = 0; i < nb_mach; i++)
            delete[] diagramme_matrice[i];
        delete[] diagramme_matrice;

    }

    while(!temps_total.isEmpty()){
        T_solution = 10000000;
        permuter = 0;
        jobs = solution;
        jobs.insert(permuter,temps_total.first());
        temps_total.removeFirst();
        while (permuter != jobs.length()) {

            int **diagramme_matrice = new int*[nb_mach];//matrice de diagramme
            for (int i = 0; i < nb_mach; i++)
                diagramme_matrice[i] = new int[jobs.length()];

            for(int i = 0; i < jobs.length(); i++){   //initialisataion de matrice de diagramme
                for(int j = 0; j < nb_mach; j++){
                    if(i == 0 && j == 0){
                        diagramme_matrice[j][i] = job_temps[j][jobs.at(i).x()];
                        qDebug() << diagramme_matrice[j][i];
                    }
                    else if(i == 0 && j !=0){
                        diagramme_matrice[j][i] = diagramme_matrice[j-1][i] + job_temps[j][jobs.at(i).x()];
                        qDebug() << diagramme_matrice[j][i];
                    }
                    else if(i != 0 && j == 0){
                        diagramme_matrice[j][i] = diagramme_matrice[j][i-1]+job_temps[j][jobs.at(i).x()];
                        qDebug() << diagramme_matrice[j][i];
                    }
                    else {
                        diagramme_matrice[j][i] = max(diagramme_matrice[j-1][i] , diagramme_matrice[j][i-1]) + job_temps[j][jobs.at(i).x()];
                        qDebug()<< "le max ext:" << max(diagramme_matrice[j-1][i] , diagramme_matrice[j][i-1]);
                        qDebug() << diagramme_matrice[j][i];
                    }
                }

            }

            int T = diagramme_matrice[nb_mach - 1][jobs.length()-1];
            if(T < T_solution){
                T_solution = T;
                solution = jobs;
            }
            permuter++;
            qDebug() << permuter<<"--"<<jobs.length();
            if(permuter < jobs.length())
                jobs.swap(permuter -1 , permuter);

            for (int i = 0; i < nb_mach; i++)
                delete[] diagramme_matrice[i];
            delete[] diagramme_matrice;
        }
        qDebug()<< T_solution;
        for(int i = 0;i < solution.length() ; i++){
            qDebug()<< "job" <<solution.at(i).x()+1 <<endl ;
        }
    }
    qDebug()<< T_solution;
    txt->append("le temps de la solution est : " + QString::number(T_solution));
    txt->append("la solution est :");
    for(int i = 0;i < solution.length() ; i++){
        txt->append("job :" + QString::number(solution.at(i).x()+1));
        qDebug()<< "job" <<solution.at(i).x()+1 <<endl ;
    }
    txt->show();
}

//IMPLEMENTATION DE METHODE POTENTIEL
double graphscene::algoPotentiel(QList<sommet *> Liste){
    text->clear();
    text->setReadOnly(true);
    text->append("<h2>Resultat de la methode Potentiel :</h2>");
    calcul_degre(Liste);
    QList< QList<sommet *> > niveaux;//une liste de listes de niveaux
    QList<sommet *>tmp;//liste temporaire qui va contenir un niveau
    foreach (sommet *som, Liste) {
        //le premier niveau
        if(som->degre == 0)
            tmp.append(som);
    }

    niveaux.append(tmp);
    tmp.clear();
    int i=1;
    while(i == niveaux.length()){
        //les autres n niveaux
        foreach(sommet * som,niveaux.at(i-1))
        {
            foreach(arc *ac,som->arclist)
            {
                if(ac->sourceSommet() == som){
                    ac->destSommet()->degre--;
                    if(ac->destSommet()->degre == 0){
                        tmp.append(ac->destSommet());
                    }
                }
            }
        }

        if(!tmp.isEmpty()){
            niveaux.append(tmp);
            tmp.clear();
        }
        i++;
    }

    //on collecte la liste de liste de niveaux dans une suele liste
    QList<sommet *> sommet_de_potentiel;
    for(int i = 0;i < niveaux.length() ; i++){
        sommet_de_potentiel+=niveaux[i];
    }

    foreach(sommet *som, sommet_de_potentiel){
        som->date_plutot = 0;
        som->date_plutard = 100000000;
    }


    //clacule des dates de debut au plus tot

    foreach(sommet * som,sommet_de_potentiel){
        foreach(arc * ac,som->arclist){
            if(som == ac->destSommet()){
                int date = ac->valarc + ac->sourceSommet()->date_plutot;
                if(date > som->date_plutot){
                    som->date_plutot = date;

                    qDebug()<< sommet_de_potentiel.indexOf(som);
                    qDebug()<< som->date_plutot;

                }
            }
        }
    }
    std::reverse(sommet_de_potentiel.begin(), sommet_de_potentiel.end());//reverser l'orde

    //clacule des dates de debut au plus tard
    sommet_de_potentiel.at(0)->date_plutard = sommet_de_potentiel.at(0)->date_plutot;

    foreach (sommet *som, sommet_de_potentiel) {
        foreach(arc * ac,som->arclist){
            if(som == ac->sourceSommet()){
                int date =  ac->destSommet()->date_plutard - ac->valarc;
                if(date < som->date_plutard)
                    som->date_plutard = date;
            }
        }
    }
    std::reverse(sommet_de_potentiel.begin(), sommet_de_potentiel.end());//retourne à l'orde original

    //duréé de l'ordonnancement
    text->append("Les taches critiques sont :");
    QList<sommet *>tachecritiques;
    foreach (sommet * som, sommet_de_potentiel) {
        if(som->date_plutard == som->date_plutot){
            tachecritiques.append(som);
            text->append("* " + som->valSommet);
        }
    }

    double cmax=0;

    foreach(sommet *som,tachecritiques){
        if(som->date_plutot > cmax)
            cmax = som->date_plutot;
    }
    qDebug() <<"la date est:" <<cmax;
    for(int i = 0 ;i < tachecritiques.length() ;i++) {
        qDebug() <<"les taches critiques sont :" << tachecritiques.at(i)->valMachine <<";" <<tachecritiques.at(i)->sommetJob;
    }
    text->append("Le cout max est :" + QString::number(cmax));
    return cmax;
}
