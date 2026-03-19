#include "Text.h"
#include "Sprite.h"

#include <iostream>

#ifndef BORDERED_LABEL
#define BORDERED_LABEL

namespace Argon{
namespace Addons{
struct BorderedLabel : public Label, public Sprite {

    BorderedLabel();

    void render(const char* string,
                VirtualResource font,
                VirtualResource bgTexture,
                LineStyle style = kLineCenter,
                float dX = 0.5,
                float dY = 0.5);

    void setxPosition(float x){
        if(line_style == kLineLeft) {
            Label::position[0] = x - Label::scale[0]*Label::max_width/2 -
                                    (Label::bounds.size[0]/125)*Label::scale[0];
        } else if(line_style == kLineRight) {
            Label::position[0] = x + Label::scale[0]*Label::max_width/2 - 
                                    (Label::bounds.size[0]/125)*Label::scale[0];
        } else { //Center
            Label::position[0] = x - (Label::bounds.size[0]/125)*Label::scale[0];
        }
        Sprite::position[0] = x;
    }

    void setyPosition(float y){
        if(!Label::isMultiLine) {
            Label::position[1] = y - Label::bounds.size[1] * 
                                Label::scale[1]/(2+(1/(Label::scale[1]*10)));
        } else {
            Label::position[1] = y + Label::bounds.size[1] *
                                        Label::scale[1]/(4.8+(1/(Label::scale[1]*10)));
        }
        
        Sprite::position[1] = y;
    }

    void setzPosition(float z){
        Label::position[2] = z;
        Sprite::position[2] = z;
    }

    void setPosition(float x, float y, float z){
        setxPosition(x);
        setyPosition(y);
        setzPosition(z);
    }

    void setxScale(float x){
        Label::scale[0] = x;
        Sprite::scale[0] = Label::bounds.size[0]*Label::scale[0] + dX*Label::scale[0];
        setxPosition(Sprite::position[0]);
    }

    void setyScale(float y){
        Label::scale[1] = y;
        Sprite::scale[1] = Label::bounds.size[1]*Label::scale[1] + dY*Label::scale[1];
        setyPosition(Sprite::position[1]);
    }

    void setzScale(float z){
        Label::scale[2] = z;
        Sprite::scale[2] = Label::bounds.size[2]*Label::scale[2];
    }

    void setxDimensions(float x){
        Label::dimensions[0] = x;
        Sprite::dimensions[0] = x;
    }

    void setyDimensions(float y){
        Label::dimensions[1] = y;
        Sprite::dimensions[1] = y;
    }

    void setzDimensions(float z){
        Label::dimensions[2] = z;
        Sprite::dimensions[2] = z;
    }

    float xPosition(bool sprite = true){
        return Sprite::position[0] ? sprite : Label::position[0];
    }

    float yPosition(bool sprite = true){
        return Sprite::position[1] ? sprite : Label::position[1];
    }

    float zPosition(bool sprite = true){
        return Sprite::position[2] ? sprite : Label::position[2];
    }

    float xScale(bool sprite = true){
        return sprite ? Sprite::scale[0] : Label::scale[0];
    }

    float yScale(bool sprite = true){
        return sprite ? Sprite::scale[1] : Label::scale[1];
    }

    float zScale(bool sprite = true){
        return sprite ? Sprite::scale[2] : Label::scale[2];
    }

    float xDimensions(bool sprite = true){
        return sprite ? Sprite::dimensions[0] : Label::dimensions[0];
    }

    float yDimensions(bool sprite = true){
        return sprite ? Sprite::dimensions[1] : Label::dimensions[1];
    }

    float zDimensions(bool sprite = true){
        return sprite ? Sprite::dimensions[2] : Label::dimensions[2];
    }

    float red(bool sprite = false){
        return sprite ? Sprite::color[0] : Label::color[0];
    }

    float green(bool sprite = false){
        return sprite ? Sprite::color[1] : Label::color[1];
    }

    float blue(bool sprite = false){
        return sprite ? Sprite::color[2] : Label::color[2];
    }

    float alpha(bool sprite = false){
        return sprite ? Sprite::color[3] : Label::color[3];
    }
    
private:
    const float bgOffset = 1/100;
    float dX;
    float dY;

};
}
}

#endif
