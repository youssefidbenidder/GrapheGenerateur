#ifndef SOMMET_H
#define SOMMET_H

    #include <QGraphicsItem>
    #include <QList>
    #include <QGraphicsSceneMouseEvent>
    #include <QLineEdit>
    #include "arete.h"
    #include <QMainWindow>
    #include <QApplication>

class sommet : public QGraphicsItem
{
public:
    sommet();//constructeur

    //AJOUTER LE ARETES ET ARCS AU SOMMET
        void ajouterArete(arete *aret);
        void ajouterArc(arc *ac);

    //SUPPRIMER LES ARETES ET ARCS
        void supprimerArete(arete *aret);//de aretelist
        void supprimerAretes();//supprimer du sommet
        void supprimerArc(arc *ac);//de arclist
        void supprimerArcs();//le supprimer du sommet

    //TYPE POUR LES SOMMETS
        enum { Type = UserType + 15 };
        int type() const Q_DECL_OVERRIDE { return Type; }

    //DATA PLUTOT ET PLUTARD POUR POTENTIEL
        int date_plutot;
        int date_plutard;

    //les listes
        QList<arete *> aretelist;
        QList<arc *> arclist;

    //temps de la fonction temps de la scene
        int temps;

    //les lines edits
        QLineEdit* pLineEdit;//pour sommets
        QGraphicsProxyWidget* pMyProxy;//pour sommets
        QLineEdit* pLineEdit2;//pour job
        QGraphicsProxyWidget* pMyProxy2;//pour job

    //les indices
        int indexSommet;
        int sommetJob;
        QString valSommet = "sommet";
        QString valMachine = "1";
        int modde = 0;//couleur de sommets
        int degre = 0;//degree de sommet par defaut(n'a pas de predecesseur et successeur)

protected:     
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    //CHANGER LE CURSEUR
        virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override
        {
          QGraphicsItem::hoverEnterEvent(event);
          QApplication::setOverrideCursor(Qt::PointingHandCursor);
        }

        virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) override
        {
          QGraphicsItem::hoverLeaveEvent(event);
          QApplication::setOverrideCursor(Qt::ArrowCursor);
        }

};

#endif // SOMMET_H
