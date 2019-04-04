#ifndef ARETE_H
#define ARETE_H

    #include <QGraphicsLineItem>
    #include <QGraphicsTextItem>
    #include <QString>

class sommet;

class arete : public QGraphicsLineItem
{
public:
    //CONSTRUCTEUR
        arete(sommet *sourceSommet, sommet *destSommet);

    sommet *sourceSommet();
    sommet *destSommet();

    //FONCTION QUI PERMET L'AJUSTEMENT DES SOMMETS DE GRAPH
        void adjustement();

    //ENUMERATION DU TYPE ARETE
    enum { Type = UserType + 4 }; // !!!!!!!!
    int type() const override { return Type; }//retourne le type

    //MISE A JOUR DE POSITION DES ARETES
        void updatePosition();

    //VALEUR POUR LARETE
        QGraphicsTextItem *text = new QGraphicsTextItem("1",this);
        qreal valArete;//pour changer la valeur d'arete


protected:
    //PAINTER QUI PERMETRA DE DESSINER L'ARC
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        QRectF boundingRect() const override;//entourage d'arete

private:
    sommet *source, *dest;
    QPointF sourcePoint;//position de sommet source
    QPointF destPoint;//position de sommet destination
    qreal areteSize;//distance d'arete
};


class arc : public QGraphicsLineItem
{
public:
    //CONSTRUCTEUR
        arc(sommet *sourceSommet, sommet *destSommet);

    sommet *sourceSommet();
    sommet *destSommet();

    //AJUSTEMENT D'ARETE
        void adjustement();

    //VALEUR POUR LE TYPE ARC
        enum { Type = UserType + 5 }; // !!!!!!!!
        int type() const override { return Type; }

    //MISE A JOUR DE LA POSITION D'ARETE
        void updatePosition();

    //VALEUR D'ARC PAR DEFAUT
        QGraphicsTextItem *text = new QGraphicsTextItem("1",this);
        qreal valarc;

protected:
    //QPAINTER QUI PERMET DE DESSINER LARC
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        QRectF boundingRect() const override;

private:
    sommet *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arcSize;
};
#endif // ARETE_H
