#include "Player.h"
#include <curses.h>

int Player::readPlayerInputs()
{
    int touche = getch();                                                                                                               // Attend une touche du joueur.

    getDirection(touche);
}

//int Player::getDirection(int mouvement) {
//    int nouveauX = x;
//    int nouveauY = y;
//
//    if (mouvement == 'z' || mouvement == 'Z' || mouvement == KEY_UP)
//        nouveauY--;                                                                                                                             
//    else if (mouvement == 's' || mouvement == 'S' || mouvement == KEY_DOWN)
//        nouveauY++;                                                                                                                             
//    else if (mouvement == 'q' || mouvement == 'Q' || mouvement == KEY_LEFT)
//        nouveauX--;                                                                                                                             
//    else if (mouvement == 'd' || mouvement == 'D' || mouvement == KEY_RIGHT)
//        nouveauX++;                                                                                                                             
//    else
//        return;                                                                                                                                 
//
//    x = nouveauX;                                                                                                                       
//    y = nouveauY;
//}
