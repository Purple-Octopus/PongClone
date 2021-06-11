#include <SDL2/SDL.h>
#include "constants.hpp"

class Vec2
{
public:
    Vec2()
        : x(0.0f), y(0.0f)
    {
    }

    Vec2(float x, float y)
        : x(x), y(y)
    {
    }

    Vec2 operator+(Vec2 const &rhs)
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 &operator+=(Vec2 const &rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    Vec2 operator*(float rhs)
    {
        return Vec2(x * rhs, y * rhs);
    }

    float x, y;
};

class Ball
{
public:
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

    Vec2 position;
    SDL_Rect rect{};
};

void destroy_window(SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char const *argv[])
{
    // Initalize SDL components
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Ball ball(Vec2((WINDOW_WIDTH / 2.0f) - (BALL_HEIGHT / 2.0f), (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)));

    // Basic structure of a game
    {
        bool running = true;

        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                }
            }

            //Clear the Window to black
            SDL_SetRenderDrawColor(renderer, 30, 35, 41, 255);
            SDL_RenderClear(renderer);

            // Set the draw color to be white
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            // Draw the net
            for (int i = 0; i < WINDOW_HEIGHT; i++)
            {
                if (i % 5)
                {
                    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, i);
                }
            }

            // Draw the ball
            ball.Draw(renderer);
            /**
             * Renderingwill happen here
             * Present the backbuffer
             */
            SDL_RenderPresent(renderer);
        }
    }

    // Cleanup
    destroy_window(renderer, window);

    return 0;
}
