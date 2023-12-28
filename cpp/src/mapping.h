#include <SDL.h>
#include <array>
#pragma once


class Mapping {
    private:
        // Atributos
        int width;
        int height;
        SDL_Renderer* renderer;
        SDL_Window* window;
        std::array<int, 3> prime_color;
        std::array<int, 3> background_color;

    public:
        float scale;

        // Constructor
        Mapping(int width, int height, float scale);

        Mapping();

        // Métodos
        std::array<int, 2> mapToScreen(std::array<int, 2> point);

        std::array<int, 2> screenToMap(std::array<int, 2> point);

        std::array<int, 2> rotateVector(std::array<int, 2> point, float angle);

        void drawPoint(std::array<int, 2> point);

        void drawMultiplePoints(std::vector<std::array<int, 2>> points, int number_of_points);

        void setColors(std::array<int, 3> prime_color, std::array<int, 3> background_color);

        void update();

        void quit(); // Terminar la ventana de SDL

        // Getters
        int getWidth();

        int getHeight();

        float getScale();
};