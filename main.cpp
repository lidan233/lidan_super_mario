#include <iostream>
#include <SDL/SDL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "./src/textures.h"
#include "./src/game.h"
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define MAX 22
#define sudu 10
using namespace std;

Textures *texture = new Textures();
Level *level1 = new Level();
Mario *mario = new Mario();
Status *status = new Status() ;




int jumpFlag=0,up=0,down;
bool direction[4] = {0,0,0,0};

void die(){
    exit(1);
}

void swap(int* a , int *b)
{
//    int temp = 0 ;
//    for(int i = 0 ;i < MAX;i++)
//    {
//        temp = a[i] ;
//        a[i] = b[i] ;
//        b[i] = temp ;
//    }

}

void createLevel(){
    level1->position_point_begin = 0 ;
    level1->questions = (int*)malloc(sizeof(int)*MAX) ;
    level1->newquestions = (int*)malloc(sizeof(int)*MAX) ;
    level1->new_newquestions = (int*)malloc(sizeof(int)*MAX) ;

    level1->paint_main = (int*)malloc(sizeof(int)*MAX) ;
    level1->new_paint_main = (int*)malloc(sizeof(int)*MAX);
    level1->new_newpaint_main = (int*)malloc(sizeof(int)*MAX) ;

    for(int i=0;i<MAX;i++){
        // level1->baseWall[i] = (i%7);
        level1->baseWall[i] = 1;
        level1->pipe[i] = (i%5==0);
        if(level1->pipe[i-1]==1 && ((i-1)%5==0))
            level1->pipe[i]=1;
        if(i%8==0  )
        {
            level1->questions[i] = (int)(rand()%5) ;
            level1->newquestions[i] = (int)(rand()%5) ;
            level1->new_newquestions[i] = (int)(rand()%5) ;
//            level1->newquestions[i] = level1->questions[i] ;
            cout<<"lidan"<<level1->questions[i]<<endl ;
        }


        if(i%6==0 )
        {
            level1->paint_main[i] = (int)(rand()%5) ;
            level1->new_paint_main[i] = (int)(rand()%5) ;
            level1->new_newpaint_main[i] = (int)(rand()%5) ;
//            level1->new_paint_main[i] = level1->paint_main[i];
        }
    }
    level1->pipe[0]=0;

    level1->questions[0] =0 ;
    level1->newquestions[0] = 0 ;
    level1->new_newquestions[0] = 0 ;

    level1->paint_main[0] = 0 ;
    level1->new_paint_main[0] = 0 ;
    level1->new_newpaint_main[0] = 0;


}

void moveBack(){
    if(level1->pipe[(mario->mariox)/64]==0 && mario->base)
        direction[3]=1;
    if(level1->pipe[(mario->mariox-1)/64]){
        if(mario->marioy/64>=3)
            mario->mariox-=8;
        else
            mario->mariox=mario->mariox;
    }
    else if(level1->baseWall[(mario->mariox+31)/64])
        mario->mariox-=8;
    else
        die();
}

void moveFront(){
    if(level1->pipe[(mario->mariox)/64]==0 && mario->base)
        direction[3]=1;
    if(level1->pipe[(mario->mariox+65)/64]){
        if(mario->marioy/64>=3)
            mario->mariox+=8;
        else
            mario->mariox=mario->mariox;
    }
    else if(level1->baseWall[(mario->mariox+33)/64])
        mario->mariox+=8;
    else if(mario->marioy)
        mario->mariox+=8;
    else
        die();
}

void moveUp(){
    if(!jumpFlag){
        jumpFlag=mario->marioy+224;
        up=1;
    }
    if(jumpFlag && (mario->marioy<=jumpFlag) && up)
        mario->marioy+=8;

    else
        up=0;

    if(!up)
    {

        if(mario->marioy>0)
        {
            mario->marioy-=8;

        }else{
            direction[2] = 0 ;
            jumpFlag = 0;
        }


//        if(mario->marioy>=188)
//        if(level1->paint_main[(50+status->x+64)/64] || level1->paint_main[(50+status->x+4)/64]){
//            mario->base=1;
//            if(mario->marioy>=188)
//                mario->marioy-=8;
//            if(mario->marioy==192){
//                direction[2]=0;
//                jumpFlag=0;
//            }
//        }
//        else if(!(level1->paint_main[(50+status->x+64)/64]) || !(level1->paint_main[(50+status->x+4)/64]) ){
//            mario->base=0;
//            if(mario->marioy>=4)
//                mario->marioy-=8;
//            if(mario->marioy==0){
//                direction[2]=0;
//                jumpFlag=0;
//            }
//        }
    }
}

void moveDown(){
    if(level1->pipe[(mario->mariox)/64]==0 && level1->pipe[(mario->mariox+64)/64]==0){
        if(mario->marioy>0)
            mario->marioy-=8;
        else{
            mario->base=0;
            direction[3]=0;
        }
    }
}

void init()
{
    glClearColor(0.48,0.47,1.0,1.0);
    glOrtho(0.0,1360.0,0.0,760.0,-10.0,10.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}


void display_item()
{

    // 4 代表画 烟囱
    // 3 代表画 普通木箱
    // 2 代表画 带奖的木箱
    // 1 代表画 敌人
    //0 代表啥也不画


    GLint startx=0;
    int maxx = INT_MIN ;

    int count_change = 0;

    for(int i=0;i<MAX;i++)
    {
//        cout<<"jiancha"<<level1->questions[i]<<endl ;


        if(startx-status->frontx <= -64)
        {
            count_change = i ;
        }

        if(startx-status->frontx > maxx)
        {
            maxx = startx-status->frontx ;
        }

        if(level1->paint_main[i]!=0 && (i%6==0))
        {



            cout<<"huale"<<level1->paint_main[i]<<endl ;
            switch(level1->paint_main[i]){
                case 1:
                    texture->drawEnemy(startx-status->frontx, status->fronty);
                    break ;

                case 2:
                    texture->drawQuestion(startx-status->frontx, status->fronty) ;
                    break ;

                case 3:
                    texture->drawBrick(startx-status->frontx, status->fronty) ;
                    break;
            }



        }
        startx+=64;
    }

    if(count_change==MAX-1)
    {


        for(int i = 0; i<= count_change+1;i++)
        {
            cout<<i%8<<i <<endl;
            if(level1->new_paint_main[i]!=0 && (i%6==0))
            {
                cout<<"hualenext"<<level1->new_paint_main[i]<<endl ;
                cout<<maxx+(i+1)*64<<' '<<status->undery<<endl ;

                switch(level1->new_paint_main[i]){
                    case 1:
                        texture->drawEnemy(maxx+(i+1)*64, status->fronty);
                        break ;

                    case 2:
                        texture->drawQuestion(maxx+(i+1)*64, status->fronty) ;
                        break ;

                    case 3:
                        texture->drawBrick(maxx+(i+1)*64, status->fronty) ;
                        break;
                }



            }
        }
//        swap(level1->questions,level1->newquestions) ;
        int *temp = level1->paint_main ;
        level1->paint_main = level1->new_paint_main ;
        level1->new_paint_main = temp ;
        status->frontx = maxx+64  ;



    }else if(count_change>0)
    {
        for(int i = 0; i<= count_change+1;i++)
        {
            cout<<i%8<<i <<endl;
            if(level1->new_paint_main[i]!=0 && (i%6==0))
            {
                cout<<"hualenext"<<level1->new_paint_main[i]<<endl ;
                cout<<maxx+(i+1)*64<<' '<<status->undery<<endl ;

                switch(level1->new_paint_main[i]){
                    case 1:
                        texture->drawEnemy(maxx+(i+1)*64, status->fronty);
                        break ;

                    case 2:
                        texture->drawQuestion(maxx+(i+1)*64, status->fronty) ;
                        break ;

                    case 3:
                        texture->drawBrick(maxx+(i+1)*64, status->fronty) ;
                        break;
                }



            }
        }


    }


}




void display_under()
{


    // 4代表画云朵
    // 3代表画城堡
    // 2代表灌木丛
    // 1代表小山包
    // 0 代表什么都不画


    GLint startx=0;
    int maxx = INT_MIN ;

    int count_change = 0;

    for(int i=0;i<MAX;i++)
    {
//        cout<<"jiancha"<<level1->questions[i]<<endl ;


        if(startx-status->underx <= -64)
        {
            count_change = i ;
        }

        if(startx-status->underx > maxx)
        {
            maxx = startx-status->underx ;
        }

        if(level1->questions[i]!=0 && (i%8==0))
        {



            cout<<"huale"<<level1->questions[i]<<endl ;
            switch(level1->questions[i]){
                case 1:
                    texture->drawHill(startx-status->underx, status->undery);
                    break ;

                case 2:
                    texture->drawBush(startx-status->underx, status->undery) ;
                    break ;

                case 3:
                    texture->drawCloud(startx-status->underx, status->undery) ;
                    break;
            }



        }
        startx+=64;
    }

    if(count_change==MAX-1)
    {


        for(int i = 0; i<= count_change+1;i++)
        {
            cout<<i%8<<i <<endl;
            if(level1->newquestions[i]!=0 && (i%8==0))
            {
                cout<<"hualenext"<<level1->newquestions[i]<<endl ;
                cout<<maxx+(i+1)*64<<' '<<status->undery<<endl ;

                switch(level1->newquestions[i]){
                    case 1:
                        texture->drawHill(maxx+(i+1)*64, status->undery);
                        break ;

                    case 2:
                        texture->drawBush(maxx+(i+1)*64, status->undery) ;
                        break ;

                    case 3:
                        texture->drawCloud(maxx+(i+1)*64, status->undery) ;
                        break;
                }



            }
        }
//        swap(level1->questions,level1->newquestions) ;
        int *temp = level1->questions ;
        level1->questions = level1->newquestions ;
        level1->newquestions = temp ;
        status->underx = maxx +64 ;



    }else if(count_change>0)
    {
        for(int i = 0; i<= count_change+1;i++)
        {
            cout<<i%8<<i <<endl;
            if(level1->newquestions[i]!=0 && (i%8==0))
            {
                cout<<"hualenext"<<level1->newquestions[i]<<endl ;
                cout<<maxx+(i+1)*64<<' '<<status->undery<<endl ;

                switch(level1->newquestions[i]){
                    case 1:
                        texture->drawHill(maxx+(i+1)*64, status->undery);
                        break ;

                    case 2:
                        texture->drawBush(maxx+(i+1)*64, status->undery) ;
                        break ;

                    case 3:
                        texture->drawCloud(maxx+(i+1)*64, status->undery) ;
                        break;
                }



            }
        }


    }

}





void display_walls()
{
    GLint startx=0,starty=0;
    int maxx = INT_MIN ;

    int count_change = 0;
    int jilu = 0 ;

    for(int i=0;i<MAX;i++)
    {
        if(level1->baseWall[i])
        {
            texture->drawBaseWall(startx-status->x, starty);
            if(startx-status->x <= -64)
            {
                count_change = i ;
                jilu = startx-status->x+64 ;
            }

            if(startx-status->x > maxx)
            {
                maxx = startx-status->x ;
            }
        }

//        if(level1->pipe[i] && (i%5==0))
//        {
//            texture->drawPipe(startx-status->x, starty);
//
//        }
        startx+=64;
    }

    if(count_change==MAX-1)
    {
        status->x = maxx+64 ;
        cout<<"max 是"<< status->x <<endl;
        for(int i = 0; i<= count_change+1;i++)
        {
            texture->drawBaseWall(maxx+i*64,starty) ;
        }

    }else if(status->x >0)
    {
        for(int i = 0; i<= count_change+1;i++)
        {
            texture->drawBaseWall(maxx+(i+1)*64,starty) ;
        }
    }




}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    display_walls() ;
    display_item() ;
    display_under() ;
    // cout<<mario->marioy/64<<endl;

//    glPushMatrix();
//    glTranslatef(status->x,mario->marioy,0);
//
//    glPopMatrix();
    texture->drawMario(50, mario->marioy);
    glFlush();
}

int main(int argc, char** argv)
{
    srand(time(NULL)) ;
    mario->mariox=0;
    mario->marioy=0;
    mario->base=0;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1344, 768, 32, SDL_SWSURFACE|SDL_OPENGL | SDL_FULLSCREEN);
    // screen = SDL_SetVideoMode(1344, 768, 32, SDL_SWSURFACE|SDL_OPENGL );
    bool running = true;
    const int FPS = 30;
    Uint32 start;
    SDL_Event event;

    createLevel();

    init();

    while(running) {
        start = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_LEFT:
                            direction[0]=1;
                            break;
                        case SDLK_RIGHT:
                            direction[1]=1;
                            break;
                        case SDLK_UP:
                            // jumpFlag=0;
                            direction[2]=1;
                            break;
                        case SDLK_DOWN:
                            // if(direction[2]==0)
                            direction[3]=1;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            direction[0]=0;
                            break;
                        case SDLK_RIGHT:
                            direction[1]=0;
                            break;
                        case SDLK_UP:
                            // direction[2]=0;
                            // jumpFlag=0;
                            break;
                        case SDLK_DOWN:
                            // if(jumpFlag==1)
                            direction[3]=0;
                            break;
                    }
                    break;
            }
        }

        if(direction[0])
            moveBack();
        // mariox-=5;

        if(direction[1])
            moveFront();
        // mariox+=5;

        if(direction[2])
            moveUp();

        if(direction[3])
            moveDown();

        display();
        SDL_GL_SwapBuffers();
        // angle += 0.9;
        // if(angle > 360)
        // 	angle -= 360;

        if(1000/FPS > SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        status->x +=sudu ;
        status->underx +=sudu ;
        status->frontx +=sudu ;
    }
    //SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}
