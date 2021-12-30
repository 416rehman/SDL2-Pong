/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Name: Hayaturehman Ahmadzai
   Email: hahmadzai3@myseneca.ca
   Student ID: 122539166
   Created on 2021-12-28.*/

#ifndef SDDS_GAME_H
#define SDDS_GAME_H
#include <SDL.h>

namespace Core {

    struct Vector2 {
        float x, y;
    };

    class Game {
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        Vector2 m_ballPos;
        Vector2 m_paddlePos;
        Vector2 m_ballVel;

        bool m_isRunning;
        float m_ticksCount;
        float m_PaddleDir;

    public:
        Game();
        bool Initialize();
        void BeginPlay();
        void Shutdown();
        ~Game();

    private:
        void ProcessInput();
        void Update();
        void GenerateOutput();
    };
}


#endif //SDDS_GAME_H
