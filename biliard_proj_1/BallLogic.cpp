#include "BallLogic.hpp"

#include <iostream>

const int Y_CENTER = 1080/2+20;
const int X_CENTER = 1920/2;
const int space = 35;
const float friction = 0.989;
const float friction2 = 0.985;
const float accuracy = 0.15;
#define X_RIGHT 1712
#define X_LEFT 206
#define Y_TOP 194
#define Y_BOT 949
#define LOW_SPEED 4
#define MAX_SPEED 25 
#define RADIUS 20
#define DIAMETER 40

struct StartPos
{
    float x;
    float y;
};

StartPos startPosArr[16] = {{X_CENTER-500, Y_CENTER}, {X_CENTER, Y_CENTER},
    {X_CENTER+space, Y_CENTER - 20}, {X_CENTER+space, Y_CENTER + 20}, {X_CENTER+space * 2, Y_CENTER - 40},
    {X_CENTER+space * 2, Y_CENTER }, {X_CENTER+space*2, Y_CENTER + 40}, {X_CENTER+space*3, Y_CENTER - 60},
    {X_CENTER+space*3, Y_CENTER - 20}, {X_CENTER+space*3, Y_CENTER + 20}, {X_CENTER+space*3, Y_CENTER + 60},
    {X_CENTER+space*4, Y_CENTER - 80}, {X_CENTER+space*4, Y_CENTER - 40}, {X_CENTER+space*4, Y_CENTER},
    {X_CENTER+space*4, Y_CENTER + 40}, {X_CENTER+space*4, Y_CENTER + 80}};

void setStartPos(Ball *ball)
{
    ball->set_pos(startPosArr[ball->get_number()].x, startPosArr[ball->get_number()].y);
}

bool isHole(Ball *temp)
{
    float y = temp->get_pos().y, x = temp->get_pos().x;
    if (y <= 216 && x <= 226)
        return true;
    if (x >= 920 && x <= 960)
        return true;
    if (x >= 1657 && y <= 212)
        return true;
    if (x >= 1652 && y >=893)
        return true;
    if (x <= 218 && y >= 891)
        return true;
    return false;
}

void deleteBall(Ball *temp)
{
    temp->set_not_active();
    temp->set_speed(0,0);
    temp->set_pos(0,0);
}

bool checkTheWall(Ball *temp)
{
    if (temp->get_pos().x + 40 > X_RIGHT)
    {
        float x_back = X_RIGHT - float(temp->get_pos().x + 40);
        float y_back = 0;//temp->dy * (temp->dx / x_back);
        temp->move_ball(x_back, y_back);
        temp->invert_dx();
        
        if (isHole(temp))
        {
            deleteBall(temp);
            return false;
        }
    }
    if (temp->get_pos().x < X_LEFT)
    {
        if (isHole(temp))
        {
            deleteBall(temp);
            return false;
        }
        float x_back = X_LEFT - float(temp->get_pos().x);
        float y_back = 0;//temp->dy * (temp->dx / x_back);
        temp->move_ball(x_back, y_back);
        temp->invert_dx();
    }
    if (temp->get_pos().y < Y_TOP)
    {
        if (isHole(temp))
        {
            deleteBall(temp);
            return false;
        }
        float y_back = Y_TOP - float(temp->get_pos().y);
        float x_back = 0;//temp->dx * (temp->dy / y_back);
        temp->move_ball(x_back, y_back);
        temp->invert_dy();
    }
    if (temp->get_pos().y + 40 > Y_BOT)
    {
        if (isHole(temp))
        {
            deleteBall(temp);
            return false;
        }
        float y_back = Y_BOT - (float(temp->get_pos().y) + 40);
        float x_back = 0;// temp->dx * (temp->dy / y_back);
        temp->move_ball(x_back, y_back);
        temp->invert_dy();
    }
    return true;
}

void checkTheConflict(Ball *ball, Ball *arr[16])
{
    float x1 = ball->get_pos().x + 20, y1 = ball->get_pos().y + 20;
    float dx1 = ball->get_speed().x, dy1 = ball->get_speed().y;
    for (int i = 0; i < 16; i++)
    {
        if (i == ball->get_number())
            continue;
        Ball *temp = arr[i];
        float x2 = temp->get_pos().x + 20;
        float y2 = temp->get_pos().y + 20;
        float dx2 = temp->get_speed().x;
        float dy2 = temp->get_speed().y;
        float Dx = x1 - x2;
        float Dy = y1 - y2;
        float d = sqrt(Dx*Dx+Dy*Dy); if (d == 0) d = 0.01;
        float s = Dx/d; // sin
        float e = Dy/d; // cos
        if (d < DIAMETER)
        {
            float Vn1 = dx2*s + dy2*e;
            float Vn2 = dx1*s + dy1*e;
            float dt = (DIAMETER-d)/(Vn1-Vn2);
            if (dt > 0.6)
                dt = 0.6;
            if (dt < -0.6)
                dt = -0.6;
            x1-=dx1*dt;
            y1-=dy1*dt;
            x2-=dx2*dt;
            y2-=dy2*dt;
            Dx = x1 - x2;
            Dy = y1 - y2;
            d = sqrt(Dx*Dx+Dy*Dy);
            if (d == 0)
                d = 0.01;
            s = Dx/d; // sin
            e = Dy/d; // cos
            Vn1 = dx2*s + dy2*e;
            Vn2 = dx1*s + dy1*e;
            float Vt1 = -dx2*e+dy2*s;
            float Vt2 = -dx1*e+dy1*s;
            
            float o = Vn2;
            Vn2 = Vn1;
            Vn1 = o;
            
            dx1 = Vn2*s-Vt2*e;
            dy1 = Vn2*e+Vt2*s;
            dx2 = Vn1*s-Vt1*e;
            dy2 = Vn1*e+Vt1*s;
            x1+=dx1*dt;
            y1+=dy1*dt;
            x2+=dx2*dt;
            y2+=dy2*dt;

            ball->set_pos(x1 - 20, y1 - 20);
            ball->set_speed(dx1, dy1);
            temp->set_pos(x2 - 20, y2 - 20);
            temp->set_speed(dx2, dy2);
        }
    }
}

bool updateBall(Ball *arr[16], int *scored)
{
    bool notMoving = true;
    for (int i = 0; i < 16; i++)
    {
        Ball *temp = (arr[i]);

        if (!temp->is_active())
            continue;

        if(temp->get_speed().x != 0 || temp->get_speed().y != 0)
            notMoving = false;
        
        temp->move_ball(temp->get_speed().x, temp->get_speed().y);
        
        if (!checkTheWall(temp))
        {
            if (temp->get_number()!=0)
                (*scored)++;
            continue;
        }

        checkTheConflict(temp, arr);

        if (temp->get_diag_speed() > LOW_SPEED)
        {
            temp->set_friction(friction);
        } else
        {
            temp->set_friction(friction2);
        }        
        
        if (fabs(temp->get_diag_speed()) < accuracy)
            temp->stop();
    }
    return notMoving;
}

void hittingTheBall(float x, float y, Ball *ball)
{
    float dx, dy;
    dx = (x - (ball->get_pos().x + 20)) / 10;
    dy = (y - (ball->get_pos().y + 20)) / 10;
    ball->set_speed(dx, dy);
    
    if (ball->get_diag_speed() > MAX_SPEED)
    {
        ball->set_friction(MAX_SPEED/ball->get_diag_speed());
    }
}