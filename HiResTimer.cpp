#include "HiResTimer.h"
#pragma warning(push, 0) 
#include <SDL2/SDL_timer.h>
#pragma warning(pop)

 HiResTimer::HiResTimer() 
     : frequency_((double)SDL_GetPerformanceFrequency())
 {
 }

double HiResTimer::now() const 
{
    return double(SDL_GetPerformanceCounter())/frequency_;
}
