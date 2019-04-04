#ifndef FENETREPROPOS_H
#define FENETREPROPOS_H
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
class fenetrePropos : public QMainWindow{
public :
    fenetrePropos();
protected :
    QTextEdit *txt = new QTextEdit();
    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *wid = new QWidget;
};
#endif // FENETREPROPOS_H
