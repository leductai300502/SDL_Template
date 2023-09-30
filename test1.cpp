#define _USE_MATH_DEFINES
#include <iostream>
#include "common.h"
#include <cstdlib>
#include <cmath>
#include "base_object.h"
#include "Player_Object.h"
#include "Ball_Object.h"
#include "ImpTimer.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Text Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf for rendering text
    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("path_to_your_font.ttf", 24); // Change the font path and size as needed
    if (font == NULL) {
        SDL_Log("Unable to load font: %s", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL2!", {255, 255, 255}); // Text, color
    if (textSurface == NULL) {
        SDL_Log("Unable to render text: %s", TTF_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture from the text surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface); // Free the surface since we have the texture

    if (textTexture == NULL) {
        SDL_Log("Unable to create texture from surface: %s", SDL_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the text texture
        SDL_RenderCopy(renderer, textTexture, NULL, NULL);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
