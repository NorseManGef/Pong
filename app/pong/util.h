#ifndef PONG_UTILS
#define PONG_UTILS

static float accelerator(float accel, float vmax, float vinit) {
    float velocity = vinit + accel;
    if(velocity < vmax) {
        return velocity;
    }
    return vmax;
}

#endif
