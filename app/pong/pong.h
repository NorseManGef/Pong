#ifndef __PONG__
#define __PONG__

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>

static float makeRandSmall() {
    float source = rand() % 100 + 1;

    source /= 50;
    source += -0.5;

    return source;
}

static float accelerator(float accel, float vmax, float vinit) {
    float velocity = vinit + accel;
    if(velocity < vmax) {
        return velocity;
    }
    return vmax;
}

struct Object : Argon::Node {
    Argon::Vector3f velocity;
    float friction;
    Argon::Sprite sprite;

    float top() const {
        return position[1]+dimensions[1]/2;
    }

    float bottom() const {
        return position[1]-dimensions[1]/2;
    }

    float right() const {
        return position[0]+dimensions[0]/2;
    }

    float left() const {
        return position[0]-dimensions[0]/2;
    }

    bool inXRange(float x) const {
        return x <= right() && x >= left();
    } 

    bool inYRange(float y) const {
        return y <= top() && y >= bottom();
    }

    void collide(const Object &other) {
        bool l = false;
        bool r = false;
        bool t = false;
        bool b = false;

        if(other.inXRange(right()) && (other.inYRange(top()) || other.inYRange(bottom()))) {
            r = true;
        }
        if(other.inXRange(left()) && (other.inYRange(top()) || other.inYRange(bottom()))) {
            l = true;
        }

        if(other.inYRange(top()) && (other.inXRange(right()) || other.inXRange(left()))) {
            t = true;
        }
        if(other.inYRange(bottom()) && (other.inXRange(right()) || other.inXRange(left()))) {
            b = true;
        }

        if(!l && !r && !t && !b) {

        } else {
            onCollide(other, l, r, t, b);
        }
    }

protected:
    virtual void onCollide(const Object& source, bool l, bool r, bool t, bool b) {

    }
};

struct Paddle : public Object {
    Argon::Sprite sprite;
    Argon::Input input;

    float accel;

    Paddle() {
        sprite.parent = this;

        velocity[0] = 0;
        velocity[1] = 0;
        velocity[2] = 0;

        friction = 10;

        dimensions.set(1,3,0);

        color = Argon::kWhiteColor;

        sprite.scale.set_all(1);
    }

    void move(char u, char d) {
        if(input[u] && position[1]+dimensions[1]/2 < 10) {
            if(velocity[1] < 0) {
                velocity[1] = 0;
            }

            velocity[1] = accelerator(0.5, 0.5, velocity[1]);
            position[1] += velocity[1];
        }
        if(input[d] && position[1]-dimensions[1]/2 > -10) {
            if(velocity[1]>0) {
                velocity[1] = 0;
            }

            velocity[1] = -accelerator(0.5, 0.5, -velocity[1]);
            position[1] += velocity[1];
        }
    }

std::shared_ptr<Argon::Node> animate(float time) {
        return nullptr;
    }
};

struct Ball : public Object {
    Argon::Sprite sprite; 

    Argon::Vector2f speed;
    const float colorChangeTime = 50;

    bool isRight = true;

    Ball() {
        sprite.parent = this;

        velocity[2] = 0;
        velocity[0] = speed[0] = 5;
        velocity[1] = speed[1] = 3;

        friction = 0;

        dimensions.set(1,1,0);
        position.set(0, 0, -10);
        sprite.scale.set_all(1);
        sprite.texture = "resource://Ball.png";
    }

    void accelerate() {
        if(isRight) {
            velocity[0] = accelerator(0.2, 50, velocity[0]);
        } else {
            velocity[0] = -accelerator(0.2, 50, -velocity[0]);
        }
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        accelerate();
        position[0]+=velocity[0]*time;
        position[1]+=velocity[1]*time;

        

        Argon::Vector4f colorChangeRate;
        colorChangeRate[0] = (1-color[0]) / colorChangeTime;
        colorChangeRate[1] = (1-color[1]) / colorChangeTime;
        colorChangeRate[2] = (1-color[2]) / colorChangeTime;
        colorChangeRate[3] = (1-color[3]) / colorChangeTime;

        color[0] += colorChangeRate[0]+0.001;
        color[1] += colorChangeRate[1]+0.001;
        color[2] += colorChangeRate[2]+0.001;
        color[3] += colorChangeRate[3]+0.001;

        return nullptr;
    }

protected:
    void onCollide(const Object& other, bool l, bool r, bool t, bool b) {
        if(r && !l && velocity[0] > 0) {
            velocity[0] = -velocity[0]/2;
            velocity[1] += other.velocity[1]*(other.friction+friction);
            isRight = false;
        }
        if(l && !r && velocity[0] < 0) {
            velocity[0] = -velocity[0]/2;
            velocity[1] += other.velocity[1]*(other.friction+friction);
            isRight = true;
        }

        if(t && !b && velocity[1] > 0) {
            velocity[1] = -velocity[1]*.90;
        }
        if(b && !t && velocity[1] < 0) {
            velocity[1] = -velocity[1]*.90;
        }
    }
};



struct Pong : Argon::Node {
    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;

    Object topWall;
    Object bottomWall;
    Object leftWall;
    Object rightWall;

    Pong() {
        ball.parent = this;
        name="pong";
        srand(time(nullptr));
        leftPaddle.position.set(-10/Argon::Screen::ratio(), 0, -10);
        rightPaddle.position.set(10/Argon::Screen::ratio(), 0, -10);

        topWall.dimensions[1] = 2;
        topWall.dimensions[0] = 20/Argon::Screen::ratio();
        topWall.position[1] = 11;
        topWall.position[0] = 0;
        topWall.position[2] = -10;

        bottomWall.dimensions[1] = 2;
        bottomWall.dimensions[0] = 20/Argon::Screen::ratio();
        bottomWall.position[1] = -11;
        bottomWall.position[0] = 0;
        bottomWall.position[2] = -10;

        leftWall.dimensions[1] = 20;
        leftWall.dimensions[0] = 2;
        leftWall.position[1] = 0;
        leftWall.position[0] = -3/Argon::Screen::ratio();
        leftWall.position[2] = -10;

        rightWall.dimensions[1] = 20;
        rightWall.dimensions[0] = 2;
        rightWall.position[1] = 0;
        rightWall.position[0] = 10/Argon::Screen::ratio();
        rightWall.position[2] = -10;

        leftPaddle.sprite.texture = "resource://Paddle1.png";
        rightPaddle.sprite.texture = "resource://Paddle2.png";
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        rightPaddle.position[0] = 9/Argon::Screen::ratio();
        leftPaddle.position[0] = -9/Argon::Screen::ratio();

        topWall.dimensions[0] = 20/Argon::Screen::ratio();
        bottomWall.dimensions[0] = 20/Argon::Screen::ratio();

        leftWall.position[0] = -10.5/Argon::Screen::ratio();
        rightWall.position[0] = 10.5/Argon::Screen::ratio();

        rightPaddle.move('k', 'j');
        leftPaddle.move('w', 's');


        ball.collide(rightPaddle);
        ball.collide(leftPaddle);
        ball.collide(topWall);
        ball.collide(bottomWall);
        ball.collide(leftWall);
        ball.collide(rightWall);
        ball.animate(time);
        
        return nullptr;
    }
};

#endif
