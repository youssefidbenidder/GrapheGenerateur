#include "sommet.h"
#include "fenetreprincipale.h"

    #include <QGraphicsScene>
    #include <QGraphicsSceneMouseEvent>
    #include <QPainter>
    #include <QStyleOption>

//CONSTRUCTEUR
sommet::sommet()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
}

void sommet::ajouterArete(arete *aret){
    aretelist.append(aret);
    aret->adjustement();
    aret->updatePosition();
}

void sommet::ajouterArc(arc *ac){
    arclist.append(ac);
    ac->adjustement();
    ac->updatePosition();

}

QRectF sommet::boundingRect() const
{
    qreal adjust = 16;
    return QRectF( -10 - adjust, -10 - adjust, 50 + adjust, 50 + adjust);
}

QPainterPath sommet::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}

void sommet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    if(this->modde == 1){
        painter->setBrush(QBrush(Qt::green));
    }
    if(this->modde == 2){
        painter->setBrush(QBrush(Qt::red));
    }
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

}

//CAS DE CHNGEMENT EN ARETE OU ARC OU SOMMET
QVariant sommet::itemChange(GraphicsItemChange change, const QVariant &value){
    switch (change) {
    case ItemPositionHasChanged:
        foreach (arete *aret, aretelist)
            aret->adjustement();
        foreach (arc *ar, arclist)
            ar->adjustement();
        break;
    default:
        break;
};

    return QGraphicsItem::itemChange(change, value);
}

//CAS DE SUPPRESSION D'ARETE
void sommet::supprimerArete(arete *aret){

    int index = aretelist.indexOf(aret);

    if (index != -1)
        aretelist.removeAt(index);

}

void sommet::supprimerAretes(){
    foreach(arete *aret ,aretelist){
        aret->sourceSommet()->supprimerArete(aret);
        aret->destSommet()->supprimerArete(aret);
        scene()->removeItem(aret);   //scene() Returns the current scene for the item, or 0 if the item is not stored in a scene.
        delete aret;
    }
}

void sommet::supprimerArc(arc *ac){
    int index = arclist.indexOf(ac);
    if (index != -1)
        arclist.removeAt(index);
}

void sommet::supprimerArcs(){
    foreach(arc *ac ,arclist){
        ac->sourceSommet()->supprimerArc(ac);
        ac->destSommet()->supprimerArc(ac);
        scene()->removeItem(ac);   //scene() Returns the current scene for the item, or 0 if the item is not stored in a scene.
        delete ac;
    }
}

