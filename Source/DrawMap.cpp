#include "SFML/Graphics.hpp"
#include <array>

#include "../Headers/Global.hpp"
#include "../Headers/DrawMap.hpp"

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map, sf::RenderWindow &i_window) {
    sf::Sprite sprite;

    sf::Texture texture;
    texture.loadFromFile("Resources/Images/Map" + std::to_string(CELL_SIZE) + ".png");

    sprite.setTexture(texture);

    for (unsigned char a = 0; a < MAP_WIDTH; a++) {
        for (unsigned char b = 0; b < MAP_HEIGHT; b++) {
            sprite.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
            switch (i_map[a][b]) {
                case Cell::Door: {
                    sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                    i_window.draw(sprite);
                    break;
                }
                case Cell::Energizer: {
                    sprite.setTextureRect(sf::IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                    i_window.draw(sprite);
                    break;
                }
                case Cell::Pellet: {
                    sprite.setTextureRect(sf::IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                    i_window.draw(sprite);
                    break;
                }
                case Cell::Wall: {
                    bool down = false;
                    bool left = false;
                    bool right = false;
                    bool up = false;

                    if (b < MAP_HEIGHT - 1) {
                        if (Cell::Wall == i_map[a][1 + b]) {
                            down = true;
                        }
                    }
                    if (0 < a) {
                        if (Cell::Wall == i_map[a - 1][b]) {
                            left = true;
                        }
                    } else {
                        left = true;
                    }

                    if (a < MAP_WIDTH - 1) {
                        if (Cell::Wall == i_map[1 + a][b]) {
                            right = true;
                        }
                    } else {
                        right = true;
                    }

                    if (0 < b) {
                        if (Cell::Wall == i_map[a][b - 1]) {
                            up = true;
                        }
                    }

                    //--------------------------------------------<         DISTRIBUTIVE PROPERTY!         >----------------------------
                    sprite.setTextureRect(sf::IntRect(CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CELL_SIZE, CELL_SIZE));

                    i_window.draw(sprite);
                }
            }
        }
    }
}