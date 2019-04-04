#include "fenetrepropos.h"
fenetrePropos::fenetrePropos(){
    txt->setText("<h1>Générateur de graphe :</h1>"
        "<b>Cette application présente une interface graphique qui permet de dessiner un graphe orienter (sommet + arcs ) ou un graphe non orienter (sommet + arrêts).</b><br\>"
       " <b>Vous pourrez facilement génerer un graphe aléatoire tout en entrant un nombre de sommet , nombre d'arcs et nombre d'arrêts , puis trouver une solution du probleme d'ordonancement des ateliers (job-shop ,flow-shop , open-shop ) en utilisant l'algorithme génétique et l'algorithme Nawaz,Enscore,Ham(NEH) .</b><br\>"
        "<b>La documentation et le code source sont disponibles via l'adresse :</b>  <font color=lightskyblue face=verdana > https://github//  </font><br\>"
        "<b>Développez avec c++ et et en utilisant le Framework Qt par :</b><br\>"
        "<b>Ouail</b><br\>"
         "<b>Youssef</b><br\>"
         "<b>Doha</b><br\>"
          "<b>Maryam</b><br\>"
          "<b>Hajar</b><br\>");
     txt->setReadOnly(true);
     layout->addWidget(txt);
     wid->setLayout(layout);
     this->setCentralWidget(wid);
     this->show();
     this->setFixedSize(500,500);
}
