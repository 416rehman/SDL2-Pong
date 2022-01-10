#ifndef SDDS_GAME_H
#define SDDS_GAME_H
#include <SDL.h>

namespace Core {

    struct Vector2 {
        float x, y;
    };

    class Game {
        //Window
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        //Ball
        Vector2 m_ballPos;
        Vector2 m_ballVel;

        //Player 1
        Vector2 m_paddlePos;
        float m_PaddleDir;

        //Player 2
        Vector2 m_paddlePos2;
        float m_PaddleDir2;

        //Game State
        bool m_isRunning;
        float m_ticksCount;

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
