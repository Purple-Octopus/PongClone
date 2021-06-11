#include <SDL2/SDL.h>

#include "../Vec2.hpp"

class Ball
{
public:
    Vec2 position;

    Ball(Vec2 position)
        : position(position)
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = BALL_WIDTH;
        rect.h = BALL_HEIGHT;
    }

    void Draw(SDL_Renderer *renderer)
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);

        SDL_RenderFillRect(renderer, &rect);
    }


    SDL_Rect rect{};
};
