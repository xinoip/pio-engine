#ifndef _Animation_h
#define _Animation_h

class Animation {
public:
    unsigned int index;
    unsigned int numFrames;
    unsigned int animationSpeed;
    Animation();
    Animation(unsigned int index, unsigned int numframes, unsigned int animationSpeed);
};

#endif

