#include <SDL.h>

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Crear una ventana
    SDL_Window* window = SDL_CreateWindow("SDL2 Star Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear un renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Ciclo principal
    bool quit = false;
    while (!quit) {
        // Manejar eventos
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Limpiar el renderizador y rellenar la pantalla de blanco
        SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
        SDL_RenderClear(renderer);

        // Establecer el color de dibujo en rojo
        SDL_SetRenderDrawColor(renderer, 0, 101, 169, 255);

        // Dibujar una estrella (forma simple)
        SDL_RenderDrawLine(renderer, 320, 50, 370, 200);
        SDL_RenderDrawLine(renderer, 370, 200, 250, 150);
        SDL_RenderDrawLine(renderer, 250, 150, 420, 150);
        SDL_RenderDrawLine(renderer, 420, 150, 300, 200);
        SDL_RenderDrawLine(renderer, 300, 200, 320, 50);

        // Presentar el renderizador
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
