#include "SFML/Graphics.hpp"
#include <array>
#include <cmath>

#include "../Headers/Global.hpp"
#include "../Headers/Pacman.hpp"
#include "../Headers/MapCollision.hpp"

Pacman::Pacman() : animation_over(false),
                   dead(false),
                   direction(0),
                   energizer_timer(0),
                   position({0, 0}),
                   life(3),
                   score(0) {
}

bool Pacman::get_animation_over() const {
    return animation_over;
}

bool Pacman::get_dead() const {
    return dead;
}

short Pacman::get_life() const {
    return life;
}

unsigned short Pacman::get_score() const {
    return score;
}

unsigned char Pacman::get_direction() const {
    return direction;
}

unsigned short Pacman::get_energizer_timer() const {
    return energizer_timer;
}

void Pacman::set_life() {
    --life;
}

void Pacman::set_score() {
    score += 10;
}

void Pacman::draw(bool i_victory, sf::RenderWindow &i_window) {
    auto frame = static_cast<unsigned char>(std::floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));

    sf::Sprite sprite;

    sf::Texture texture;

    sprite.setPosition(position.x, position.y);

    if (1 == dead || 1 == i_victory) {
        if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED) {
            animation_timer++;

            texture.loadFromFile("Resources/Images/PacmanDeath" + std::to_string(CELL_SIZE) + ".png");

            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, 0, CELL_SIZE, CELL_SIZE));

            i_window.draw(sprite);
        } else {

            animation_over = true;
        }
    } else {
        texture.loadFromFile("Resources/Images/Pacman" + std::to_string(CELL_SIZE) + ".png");

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

        i_window.draw(sprite);

        animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
    }
}

void Pacman::reset() {
    animation_over = false;
    dead = false;
    direction = 0;

    animation_timer = 0;
    energizer_timer = 0;
}

void Pacman::reset_ls() {
    score = 0;
    life = 3;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer) {
    animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead) {
    dead = i_dead;

    if (1 == dead) {

        animation_timer = 0;
    }
}

void Pacman::set_position(short i_x, short i_y) {
    position = {i_x, i_y};
}

void Pacman::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map) {
    std::array<bool, 4> walls{};
    walls[0] = map_collision(false, false, PACMAN_SPEED + position.x, position.y, i_map);
    walls[1] = map_collision(false, false, position.x, position.y - PACMAN_SPEED, i_map);
    walls[2] = map_collision(false, false, position.x - PACMAN_SPEED, position.y, i_map);
    walls[3] = map_collision(false, false, position.x, PACMAN_SPEED + position.y, i_map);

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (0 == walls[0]) {
            direction = 0;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (0 == walls[1]) {
            direction = 1;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (0 == walls[2]) {
            direction = 2;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (0 == walls[3]) {
            direction = 3;
        }
    }

    if (0 == walls[direction]) {
        switch (direction) {
            case 0: {
                position.x += PACMAN_SPEED;

                break;
            }
            case 1: {
                position.y -= PACMAN_SPEED;

                break;
            }
            case 2: {
                position.x -= PACMAN_SPEED;

                break;
            }
            case 3: {
                position.y += PACMAN_SPEED;
            }
        }
    }

    if (-CELL_SIZE >= position.x) {
        position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
    } else if (CELL_SIZE * MAP_WIDTH <= position.x) {
        position.x = PACMAN_SPEED - CELL_SIZE;
    }

    int check = map_collision(true, false, position.x, position.y, i_map);
    if (check == 1) {

        set_score();
        energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));
    } else if (check == 2) {
        set_score();
    } else {
        energizer_timer = std::max(0, energizer_timer - 1);
    }
}

Position Pacman::get_position() {
    return position;
}