
#include <string>
#include "Game.h"

namespace Core {

    const uint16_t WIDTH = 1280, HEIGHT = 720,
    PADDLE_HEIGHT=150, PADDLE_WIDTH = 15, WALL_THICKNESS = 30;

    Game::Game()
    {
        this->m_window = nullptr;
        this->m_renderer = nullptr;

        m_ballPos = {WIDTH/2, (HEIGHT - PADDLE_HEIGHT) / 2}; //Center of Screen
        m_ballVel = {350.0, 400};

        m_PaddleDir = {};
        m_paddlePos = {0, HEIGHT/2}; //Middle Left of Screen

        m_PaddleDir2 = {};
        m_paddlePos2 = {WIDTH - PADDLE_WIDTH, HEIGHT/2}; //Middle Left of Screen

        this->m_isRunning = true;
        m_ticksCount = {};
    }

    bool Game::Initialize()
    {
        //Initialize SDL
        int sdl_result = SDL_Init(SDL_INIT_VIDEO);
        if (sdl_result != 0) {
            SDL_Log("Unable to Initialize SDL: %s", SDL_GetError());
            return false;
        }

        //Create an SDL Window
        this->m_window = SDL_CreateWindow("SDL Ping Pong :)", //Title of the game
                         100, 100,  //Top Left Corner Position of the window
                         WIDTH, HEIGHT,    //Size of the window
                         0
                         );

        if (!this->m_window) {
            SDL_Log("Failed to create SDL Window: %s", SDL_GetError());
            return false;
        }

        //Create an SDL Renderer
        this->m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!this->m_renderer) {
            SDL_Log("Failed to create a Renderer: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    void Game::Shutdown()
    {
        SDL_DestroyRenderer(this->m_renderer);
        SDL_DestroyWindow(this->m_window);
        SDL_Quit();
        this->m_isRunning = false;
    }

    void Game::BeginPlay()
    {
        while (this->m_isRunning) {
            this->ProcessInput();
            this->Update();
            this->GenerateOutput();
        }
    }

    Game::~Game()
    {
        if (this->m_isRunning) {
            this->Shutdown();
        }
    }

    void Game::ProcessInput()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT: {
                    m_isRunning = false;
                    break;
                }
            }
        }

        const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
        if (keyboard[SDL_SCANCODE_ESCAPE]) {
            m_isRunning = false;
        }

        m_PaddleDir = 0;
        if (keyboard[SDL_SCANCODE_W])
        {
            m_PaddleDir -= 1.5;
        }
        if (keyboard[SDL_SCANCODE_S])
        {
            m_PaddleDir += 1.5;
        }

        m_PaddleDir2 = 0;
        if (keyboard[SDL_SCANCODE_I])
        {
            m_PaddleDir2 -= 1.5;
        }
        if (keyboard[SDL_SCANCODE_K])
        {
            m_PaddleDir2 += 1.5;
        }

    }

    void Game::Update()
    {
        // Frame limiting
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16)) {
            //Wait until 16ms has passed
        }

        // Set the delta time to seconds passed since last frame
        float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;
        m_ticksCount = SDL_GetTicks();

        // Clamp deltaTime to a maximum value of 0.5f
        deltaTime = (deltaTime > 0.5f) ? 0.5f : deltaTime;

        if (m_PaddleDir != 0)
        {
            m_paddlePos.y += m_PaddleDir * deltaTime * 300.0f;
            if (m_paddlePos.y < WALL_THICKNESS)
            {
                m_paddlePos.y = WALL_THICKNESS;
            }
            if (m_paddlePos.y > HEIGHT - (PADDLE_HEIGHT + WALL_THICKNESS))
            {
                m_paddlePos.y = HEIGHT - (PADDLE_HEIGHT + WALL_THICKNESS);
            }
        }

        if (m_PaddleDir2 != 0)
        {
            m_paddlePos2.y += m_PaddleDir2 * deltaTime * 300.0f;
            if (m_paddlePos2.y < WALL_THICKNESS)
            {
                m_paddlePos2.y = WALL_THICKNESS;
            }
            if (m_paddlePos2.y > HEIGHT - (PADDLE_HEIGHT + WALL_THICKNESS))
            {
                m_paddlePos2.y = HEIGHT - (PADDLE_HEIGHT + WALL_THICKNESS);
            }
        }

        m_ballPos.x += m_ballVel.x * deltaTime;
        m_ballPos.y += m_ballVel.y * deltaTime;


        // Handle collision with the paddle 1
        if (m_ballPos.x <= PADDLE_WIDTH)
        {
            if ((m_ballPos.y <= m_paddlePos.y + PADDLE_HEIGHT && m_ballPos.y >= m_paddlePos.y) && m_ballVel.x < 0) {
                m_ballPos.x = PADDLE_WIDTH;
                m_ballVel.x *= -1;
            }
            else {
                m_isRunning = false;
            }
        }

        // Handle collision with the paddle 1
        if (m_ballPos.x >= WIDTH - PADDLE_WIDTH)
        {
            if ((m_ballPos.y <= m_paddlePos2.y + PADDLE_HEIGHT && m_ballPos.y >= m_paddlePos2.y) && m_ballVel.x > 0) {
                m_ballPos.x = WIDTH - PADDLE_WIDTH;
                m_ballVel.x *= -1;
            }
            else {
                m_isRunning = false;
            }
        }

        //Handle collision with the top wall
        if (m_ballPos.y <= WALL_THICKNESS && m_ballVel.y < 0) {
            m_ballPos.y = WALL_THICKNESS;
            m_ballVel.y *= -1;
        }
        //Handle collision with the bottom wall
        else if (m_ballPos.y >= (HEIGHT - WALL_THICKNESS) && m_ballVel.y > 0) {
            m_ballPos.y = (HEIGHT - WALL_THICKNESS);
            m_ballVel.y *= -1;
        }
    }

    void Game::GenerateOutput()
    {
        //Background
        SDL_SetRenderDrawColor(this->m_renderer, 28, 28, 43, 255);
        SDL_RenderClear(m_renderer);

        SDL_SetRenderDrawColor(this->m_renderer, 188, 69, 69, 255);

        //Top wall
        SDL_Rect top_wall {0, 0, WIDTH, WALL_THICKNESS};
        SDL_RenderFillRect(this->m_renderer, &top_wall);

        //Bottom wall
        SDL_Rect bottom_wall {0, HEIGHT - WALL_THICKNESS, WIDTH, WALL_THICKNESS};
        SDL_RenderFillRect(this->m_renderer, &bottom_wall);

        SDL_Rect ball{
                static_cast<int>(m_ballPos.x - WALL_THICKNESS/2),
                static_cast<int>(m_ballPos.y - WALL_THICKNESS/2),
                WALL_THICKNESS/3,
                WALL_THICKNESS/3
        };

        SDL_SetRenderDrawColor(this->m_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(this->m_renderer, &ball);

        SDL_Rect paddle {
            0, static_cast<int>(m_paddlePos.y), PADDLE_WIDTH, PADDLE_HEIGHT
        };

        SDL_Rect paddle2 {
            WIDTH - PADDLE_WIDTH, static_cast<int>(m_paddlePos2.y), PADDLE_WIDTH, PADDLE_HEIGHT
        };

        SDL_SetRenderDrawColor(this->m_renderer, 127, 127, 181, 255);
        SDL_RenderFillRect(this->m_renderer, &paddle);

        SDL_SetRenderDrawColor(this->m_renderer, 100, 250, 100, 255);
        SDL_RenderFillRect(this->m_renderer, &paddle2);

        SDL_RenderPresent(m_renderer);
    }
}