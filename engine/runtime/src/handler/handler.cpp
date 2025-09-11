#include "handler/input.h"

namespace runa::handler {
    input_c::input_c() {
    }

    input_c::~input_c() {
    }

    void input_c::update_event(SDL_Event &event) {
        if (event.type == SDL_EVENT_KEY_UP || event.type == SDL_EVENT_KEY_DOWN) {
            scancodes[event.key.scancode] = event.key;
        }
    }

    bool input_c::is_key_pressed(SDL_Scancode scancode) {
        if (scancodes.contains(scancode)) {
            return scancodes[scancode].down;
        }
        return false;
    }

    glm::vec2 input_c::get_input_vector(SDL_Scancode positive_y, SDL_Scancode negative_y,
                                        SDL_Scancode positive_x, SDL_Scancode negative_x) {
        glm::vec2 vec = glm::vec2(0.0f);

        if (scancodes.contains(positive_y)) {
            vec.y += scancodes[positive_y].down ? 1.0f : 0.0f;
        }
        if (scancodes.contains(negative_y)) {
            vec.y += scancodes[negative_y].down ? -1.0f : 0.0f;
        }
        if (scancodes.contains(positive_x)) {
            vec.x += scancodes[positive_x].down ? 1.0f : 0.0f;
        }
        if (scancodes.contains(negative_x)) {
            vec.x += scancodes[negative_x].down ? -1.0f : 0.0f;
        }
        vec = glm::clamp(vec, glm::vec2(-1.0f), glm::vec2(1.0f));

        return vec;
    }

    float input_c::get_input_axis(SDL_Scancode positive, SDL_Scancode negative) {
        float axis = 0.0f;

        if (scancodes.contains(positive)) {
            axis += scancodes[positive].down ? 1.0f : 0.0f;
        }
        if (scancodes.contains(negative)) {
            axis += scancodes[negative].down ? -1.0f : 0.0f;
        }
        axis = glm::clamp(axis, -1.0f, 1.0f);

        return axis;
    }
}
