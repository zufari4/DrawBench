#include "CircleShape.h"

int getCircleNumSegments(float radius)
{
    if (radius < 2) {
        return 3;
    }
    else if (radius < 6) {
        return 9;
    }
    else if (radius < 10) {
        return 14;
    }
    else if (radius < 20) {
        return 18;
    }
    else if (radius < 30) {
        return 24;
    }
    else if (radius < 50) {
        return 32;
    }
    else if (radius < 80) {
        return 38;
    }
    else
        return 64;
}