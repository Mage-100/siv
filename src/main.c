#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

int cell_size = 50;
int scale_val = 100;

void handle_scroll_event(SDL_Event *event);
void draw_checker_pattern(SDL_Renderer *renderer);

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL_Video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("siv", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Couldn't create SDL_Window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, "software");
    if (!renderer) {
        SDL_Log("Couldn't create SDL_Renderer: %s\n", SDL_GetError());
        return 1;
    }

    int image_width, image_height, n;
    unsigned char *image_data;
    if (argc > 1) {
        image_data = stbi_load(argv[1], &image_width, &image_height, &n, 4);
        printf("Width: %d, Height: %d\n", image_width, image_height);
    }

    SDL_Event event;
    bool siv_running_status = true;
    while (siv_running_status) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                siv_running_status = false;
            } else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
                handle_scroll_event(&event);
                if (event.wheel.integer_y > 0) {
                    scale_val += 100;
                }

                if (event.wheel.integer_y < 0 && scale_val > 100) {
                    scale_val -= 100;
                }
            }
        }
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_SetRenderViewport(renderer, NULL);
        SDL_RenderClear(renderer);
        draw_checker_pattern(renderer);

        SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, image_width, image_height);
        SDL_UpdateTexture(texture, NULL, image_data, image_width * 4);

        int divide_factor = image_width * image_width + image_height * image_height;
        int texture_width =  image_width / SDL_sqrt(divide_factor) * scale_val;
        int texture_height = image_height / SDL_sqrt(divide_factor) * scale_val;

        SDL_Rect texture_coord = {DEFAULT_WINDOW_WIDTH / 2 - texture_width / 2, DEFAULT_WINDOW_HEIGHT / 2 - texture_height /2, texture_width, texture_height};
        SDL_SetRenderViewport(renderer, &texture_coord);
        SDL_RenderTexture(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(texture);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void handle_scroll_event(SDL_Event *event) {
    if (event->wheel.integer_y > 0) {
        cell_size += 10;
        if (cell_size > 150) {
            cell_size -= cell_size - 150;
        }
    } else if (event->wheel.integer_y < 0) {
        cell_size -= 10;
        if (cell_size < 10) {
            cell_size += 10 - cell_size;
        }
    }
}

void draw_checker_pattern(SDL_Renderer *renderer) {
    for (int y = 0; y < DEFAULT_WINDOW_HEIGHT; y++) {
        for (int x = 0; x < DEFAULT_WINDOW_WIDTH; x++) {
            int col = x / cell_size;
            int row = y / cell_size;

            if ((col + row) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x22, SDL_ALPHA_OPAQUE);
            } else {
                SDL_SetRenderDrawColor(renderer, 0x44, 0x44, 0x44, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderPoint(renderer, x, y);
        }
    }
}
