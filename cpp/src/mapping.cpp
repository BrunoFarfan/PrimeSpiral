#include <SDL.h>
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "mapping.h"


Mapping::Mapping() = default;

Mapping::Mapping(int width, int height, float scale) {
    this->width = width;
    this->height = height;
    this->scale = scale;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("SDL could not initialize!");
    }

    // Crear una ventana
    SDL_Window* window = SDL_CreateWindow("SDL2 Prime Spiral", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, this->width, this->height,
                                          SDL_WINDOW_SHOWN);
    this->window = window;
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("Window could not be created!");
    }

    // Crear un renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->renderer = renderer;
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Renderer could not be created!");
    }
}

std::array<int, 2> Mapping::mapToScreen(std::array<int, 2> point) {
    int x = point[0];
    int y = point[1];
    int newX = x * this->scale + this->width / 2;
    int newY = -y * this->scale + this->height / 2;
    return {(int) newX, (int) newY};
}

std::array<int, 2> Mapping::screenToMap(std::array<int, 2> point) {
    int x = point[0];
    int y = point[1];
    int newX = (x - this->width / 2) / this->scale;
    int newY = (-y + this->height / 2) / this->scale;
    return {(int) newX, (int) newY};
}

std::array<int, 2> Mapping::rotateVector(std::array<int, 2> point, float angle) {
    int x = point[0];
    int y = point[1];
    float newX = x * cos(angle) - y * sin(angle);
    float newY = x * sin(angle) + y * cos(angle);
    return {(int) newX, (int) newY};
}

void Mapping::drawPoint(std::array<int, 2> point) {
    std::array<int, 2> screenPoint = this->mapToScreen(point);
    SDL_RenderDrawPoint(this->renderer, screenPoint[0], screenPoint[1]);
}

void Mapping::drawMultiplePoints(std::vector<std::array<int, 2>> points, int number_of_points) {
    SDL_RenderDrawPoints(this->renderer, (SDL_Point*) &points[0], number_of_points);
}

void Mapping::setColors(std::array<int, 3> prime_color, std::array<int, 3> background_color) {
    this->prime_color = prime_color;
    this->background_color = background_color;
    SDL_SetRenderDrawColor(this->renderer, this->background_color[0], this->background_color[1], this->background_color[2], 255);    
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor(this->renderer, this->prime_color[0], this->prime_color[1], this->prime_color[2], 255);
}

void Mapping::update() {
    SDL_RenderPresent(this->renderer);
}

void Mapping::quit() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

int Mapping::getWidth() {
    return this->width;
}

int Mapping::getHeight() {
    return this->height;
}