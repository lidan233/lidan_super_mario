/*
 * game.h
 * Copyright (C) 2013 sagar <sagar@sagar-liquid>
 *
 */

#ifndef __GAME_H__
#define __GAME_H__

class Level{

    public:
        int baseWall[22];
        int pipe[22];


        //画云朵
        int *questions ;
        int *newquestions ;
        int *new_newquestions ;

        // 4代表画云朵
        // 3代表画城堡
        // 2代表灌木丛
        // 1代表小山包
        // 0 代表什么都不画

        int *paint_main ;
        int *new_paint_main ;
        int *new_newpaint_main ;

        int position_point_begin = 0;
//        int position_paint_
        // 4 代表画 烟囱
        // 3 代表画 普通木箱
        // 2 代表画 带奖的木箱
        // 1 代表画 敌人
        //0 代表啥也不画
};

class Mario{
    public:
        int mariox;
        int marioy;
        int base;
};

class Status{
    public:
        int x = 0;
        int y = 0;
        int time = 0 ;
        int underx = 0 ;
        int undery = 0 ;

        int frontx = 0 ;
        int fronty = 0 ;


};

#endif /* !__GAME_H__ */

