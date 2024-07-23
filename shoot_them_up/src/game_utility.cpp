#include <SDL_timer.h>
void capFrameRate(long* then, double* remainder) {
  long wait = 16 + *remainder;
  *remainder -= static_cast<int>(*remainder);
  long frameTime = SDL_GetTicks() - *then;
  wait -= frameTime;
  wait = (wait < 1 ? 1 : wait);
  SDL_Delay(wait);
  *remainder += 0.667;
  *then = SDL_GetTicks();
}
