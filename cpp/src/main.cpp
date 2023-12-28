#include <SDL.h>
#include <array>
#include <cmath>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "mapping.h"
#include "prime_computing.h"
#include "json_handler.h"


// Constantes
const int WIDTH = 800;
const int HEIGHT = 800;
const float SCALE = 1.0;
const std::array<int, 3> PRIME_COLOR = {0, 101, 169};
const std::array<int, 3> BACKGROUND_COLOR = {51, 51, 51};
const std::string JSON_PATH = "../../primes.json";


class PrimeSpiral {
    private:
        int width;
        int height;
        float scale;
        std::array<int, 3> prime_color;
        std::array<int, 3> background_color;
        std::string json_path;

    public:
        int prime_start;
        std::vector<int> primes_list;
        int primes_to_draw;
        Mapping mapping;
        PrimeComputing prime_computing;
        JsonHandler json_handler;

        PrimeSpiral(int width, int height, float scale, std::array<int, 3> prime_color, std::array<int, 3> background_color, std::string json_path) {
            this->width = width;
            this->height = height;
            this->scale = scale;
            this->prime_color = prime_color;
            this->background_color = background_color;
            this->json_path = json_path;

            this->mapping = Mapping(this->width, this->height, this->scale);
            this->prime_computing = PrimeComputing();
            this->json_handler = JsonHandler();

            this->prime_start = json_handler.readMaxNumberJson(this->json_path);
            this->primes_list = json_handler.readPrimesListJson(this->json_path);
            this->primes_to_draw = this->primes_list.size();
        }

        void draw() {
            std::vector<std::array<int, 2>> temp_list;
            for (int i = 0; i < this->primes_to_draw; i++) {
                int prime = this->primes_list[i];
                std::array<int, 2> point = this->mapping.rotateVector({prime, 0}, (float) prime);
                std::array<int, 2> screenPoint = this->mapping.mapToScreen(point);
                temp_list.push_back(screenPoint);
                this->mapping.drawPoint(point);
            }
            // another way to draw multiple points, still don't know which one is better
            // this->mapping.drawMultiplePoints(temp_list, this->primes_to_draw);
        }

        void computePrimes(int prime_end) {
            std::vector<int> temp_vector = this->prime_computing.getPrimes(prime_end, this->prime_start);
            if (!temp_vector.empty()) {
                // Si el vector retornado no es vacio, extender el vector de primos con el vector retornado
                this->primes_list.insert(this->primes_list.end(), temp_vector.begin(), temp_vector.end());
            }
            if (prime_end > this->prime_start) {
                this->prime_start = prime_end;
            }
            this->json_handler.writeJson(this->json_path, this->primes_list, this->prime_start);
        }

        void updateZoom(float zoom_factor) {
            this->scale *= zoom_factor;
            this->mapping.scale = this->scale;
        }

        void updateScreen() {
            this->mapping.setColors(this->prime_color, this->background_color);
            this->draw();
            this->mapping.update();
        }
};


int main(int argc, char* argv[]) {
    // Ciclo principal
    bool quit = false;
    int n = 100;
    PrimeSpiral prime_spiral = PrimeSpiral(WIDTH, HEIGHT, SCALE, PRIME_COLOR, BACKGROUND_COLOR,
                                           JSON_PATH);
    prime_spiral.primes_to_draw = std::min(n, (int) prime_spiral.primes_list.size());
    prime_spiral.computePrimes(n);
    prime_spiral.updateScreen();

    while (!quit) {
        // Manejar eventos
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_UP:
                        prime_spiral.updateZoom(1.1);
                        std::cout << "Zoomed in: " << prime_spiral.mapping.scale << std::endl;
                        break;
                    case SDLK_DOWN:
                        prime_spiral.updateZoom(0.9);
                        std::cout << "Zoomed out: " << prime_spiral.mapping.scale << std::endl;
                        break;
                    case SDLK_RIGHT:
                        prime_spiral.primes_to_draw = (int) prime_spiral.primes_to_draw * 1.25 + 1;
                        if (prime_spiral.primes_to_draw > prime_spiral.primes_list.size()) {
                            prime_spiral.computePrimes(prime_spiral.primes_to_draw + prime_spiral.prime_start);
                        }
                        prime_spiral.primes_to_draw = std::min(prime_spiral.primes_to_draw, (int) prime_spiral.primes_list.size());
                        std::cout << "Showing " << prime_spiral.primes_to_draw << " primes" << std::endl;
                        break;
                    case SDLK_LEFT:
                        prime_spiral.primes_to_draw = (int) prime_spiral.primes_to_draw * 0.8;
                        prime_spiral.primes_to_draw = std::max(prime_spiral.primes_to_draw, 3);
                        std::cout << "Showing " << prime_spiral.primes_to_draw << " primes" << std::endl;
                }
                prime_spiral.updateScreen();
            }
        }
    }

    prime_spiral.mapping.quit();

    return 0;
}
