    #include "arete.h"
    #include "sommet.h"
    #include <math.h>
    #include <QPainter>
    #include <QDebug>

    static const double Pi = 3.14159265358979323846264338327950288419717;
    static double TwoPi = 2.0 * Pi;

//CONSTRUCTEUR ARETE
arete::arete(sommet *sourceSommet, sommet *destSommet)
{
    areteSize = 10;//valeur d'arete minimale

    source = sourceSommet;
    dest = destSommet;

    setFlag(QGraphicsItem::ItemIsSelectable, true);//pour la selection
    text->setPos(boundingRect ().center ());//pour l'entourage de l'arete
    text->setTextInteractionFlags(Qt::TextEditorInteraction);//pouvoir interagir avec la valeur d'arete
    adjustement();
    updatePosition();
}


sommet *arete::sourceSommet()
{
    return source;
}

sommet *arete::destSommet()
{
    return dest;
}

void arete::adjustement()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    setLine(line);
    text->setPos(this->boundingRect ().center ());//la position de qtextgraphicsitem est au centre de l'arete
    qreal length = line.length();//la distance de larete

    prepareGeometryChange();

    if (length > qreal(20)) {//l'arete disparait si on approche les deux sommets de moins de 20px
        QPointF areteOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + areteOffset;
        destPoint = line.p2() - areteOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF arete::boundingRect() const{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + areteSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);

}

void arete::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF ligne(sourcePoint, destPoint);
    if (qFuzzyCompare(ligne.length(), qreal(0)))
        return;

    // arete (line)
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawLine(ligne);

    // arete (triangle)
    double angle = ::acos(ligne.dx() / ligne.length());
    if (ligne.dy() >= 0)
        angle = TwoPi - angle;

    //CREATION DES FLECHES
        QPointF sourceflecheP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * areteSize,
                                                      cos(angle + Pi / 3) * areteSize);
        QPointF sourceflecheP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * areteSize,
                                                      cos(angle + Pi - Pi / 3) * areteSize);
        QPointF destflecheP1 = destPoint + QPointF(sin(angle - Pi /3 ) * areteSize,
                                                  cos(angle - Pi /3) * areteSize);
        QPointF destflecheP2 = destPoint + QPointF(sin(angle - Pi + Pi /3) * areteSize,
                                                  cos(angle - Pi + Pi /3) * areteSize);

        painter->setBrush(Qt::black);
        painter->drawPolygon(QPolygonF() << ligne.p1() << sourceflecheP1 << sourceflecheP2);
        painter->drawPolygon(QPolygonF() << ligne.p2() << destflecheP1 << destflecheP2);
        updatePosition();
}


void arete::updatePosition()
{
    QLineF ligne(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    setLine(ligne);
    text->setPos(this->boundingRect ().center ());

}

//********************************************************

//CONSTRUCTEUR ARC
arc::arc(sommet *sourceSommet, sommet *destSommet)
{
    arcSize = 10;

    source = sourceSommet;
    dest = destSommet;

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    text->setPos(boundingRect ().center ());
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    adjustement();
    updatePosition();
}

sommet *arc::sourceSommet()
{
    return source;
}

sommet *arc::destSommet()
{
    return dest;
}

void arc::adjustement()
{
    if (!source || !dest)
        return;

    QLineF ligne(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    setLine(ligne);
    text->setPos(this->boundingRect ().center ());
    qreal length = ligne.length();

    prepareGeometryChange();

    if (length > qreal(20)) {
        QPointF arcOffset((ligne.dx() * 10) / length, (ligne.dy() * 10) / length);
        sourcePoint = ligne.p1() + arcOffset;
        destPoint = ligne.p2() - arcOffset;
    } else {
        sourcePoint = destPoint = ligne.p1();
    }
    //updatePosition();
}

QRectF arc::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arcSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);

}

void arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF ligne(sourcePoint, destPoint);
    if (qFuzzyCompare(ligne.length(), qreal(0)))
        return;

    // arc (line)
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawLine(ligne);

    // arc (triangle)
    double angle = ::acos(ligne.dx() / ligne.length());
   if (ligne.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destflecheP1 = destPoint + QPointF(sin(angle - Pi /3 ) * arcSize,
                                              cos(angle - Pi /3) * arcSize);
    QPointF destflecheP2 = destPoint + QPointF(sin(angle - Pi + Pi /3) * arcSize,
                                              cos(angle - Pi + Pi /3) * arcSize);

    painter->setBrush(Qt::black);

    painter->drawPolygon(QPolygonF() << ligne.p2() << destflecheP1 << destflecheP2);
    updatePosition();
}

void arc::updatePosition()
{
    QLineF ligne(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    setLine(ligne);
    text->setPos(this->boundingRect ().center ());

}
