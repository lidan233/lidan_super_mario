/*
 * textures.h
 * Copyright (C) 2013 sagar <sagar@sagar-liquid>
 *
 */

#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


class Textures{

    unsigned int loadTexture(const char *filename);
    unsigned int marioy_current = 0 ;
    unsigned int marioy1_current = 0 ;

    public:

    void drawMario(int , int );
    void drawBaseWall(int , int );
    void drawBrick(int , int );
    void drawQuestion(int , int );
    void drawCloud(int , int );
    void drawBush(int , int );
    void drawHill(int , int );
    void drawPipe(int , int );
    void drawEnemy(int , int );

    bool collasp(int miny,int maxy  ) ;
    bool collasp1(int miny,int maxy  ) ;
};

#endif /* !__TEXTURES_H__ */

