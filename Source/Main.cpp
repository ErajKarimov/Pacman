#include "SFML/Graphics.hpp"
#include <array>
#include <chrono>
#include <ctime>

#include "../Headers/Global.hpp"
#include "../Headers/DrawText.hpp"
#include "../Headers/Pacman.hpp"
#include "../Headers/Ghost.hpp"
#include "../Headers/GhostManager.hpp"
#include "../Headers/ConvertSketch.hpp"
#include "../Headers/DrawMap.hpp"

int main() {

    bool game_won = false;


    unsigned lag = 0;

    unsigned char level = 0;


    std::chrono::time_point<std::chrono::steady_clock> previous_time;


    std::array<std::string, MAP_HEIGHT> map_sketch = {
            " ################### ",
            " #........#........# ",
            " #o##.###.#.###.##o# ",
            " #.................# ",
            " #.##.#.#####.#.##.# ",
            " #....#...#...#....# ",
            " ####.### # ###.#### ",
            "    #.#   0   #.#    ",
            "#####.# ##=## #.#####",
            "     .  #123#  .     ",
            "#####.# ##### #.#####",
            "    #.#       #.#    ",
            " ####.# ##### #.#### ",
            " #........#........# ",
            " #.##.###.#.###.##.# ",
            " #o.#.....P.....#.o# ",
            " ##.#.#.#####.#.#.## ",
            " #....#...#...#....# ",
            " #.######.#.######.# ",
            " #.................# ",
            " ################### "};

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};


    std::array<Position, 4> ghost_positions{};


    sf::Event event{};

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);

    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

    GhostManager ghost_manager;

    Pacman pacman;


    srand(static_cast<unsigned>(time(nullptr)));

    map = convert_sketch(map_sketch, ghost_positions, pacman);

    ghost_manager.reset(level, ghost_positions);


    previous_time = std::chrono::steady_clock::now();

    while (window.isOpen()) {

        unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

        lag += delta_time;

        previous_time += std::chrono::microseconds(delta_time);


        while (FRAME_DURATION <= lag) {

            lag -= FRAME_DURATION;

            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed: {

                        window.close();
                    }
                }
            }

            if (!game_won && !pacman.get_dead()) {
                game_won = true;

                pacman.update(level, map);

                ghost_manager.update(level, map, pacman);


                for (const std::array<Cell, MAP_HEIGHT> &column: map) {
                    for (const Cell &cell: column) {
                        if (Cell::Pellet == cell) {
                            game_won = false;
                            break;
                        }
                    }

                    if (!game_won) {
                        break;
                    }
                }

                if (game_won) {
                    pacman.set_animation_timer(0);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                game_won = false;

                if (pacman.get_dead()) {
                    level = 0;
                } else {
                    level++;
                }

                map = convert_sketch(map_sketch, ghost_positions, pacman);

                ghost_manager.reset(level, ghost_positions);
                pacman.reset_ls();
                pacman.reset();
            }

            if (FRAME_DURATION > lag) {
                window.clear();

                if (0 == game_won && 0 == pacman.get_dead()) {
                    draw_map(map, window);

                    ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), window);

                    draw_text(false, 0, CELL_SIZE * MAP_HEIGHT, "Level: " + std::to_string(1 + level), window);
                }

                pacman.draw(game_won, window);
                draw_text(false, 0, 0, "    Score:" + std::to_string(pacman.get_score()), window);
                draw_text(false, 150, 0, "Life:" + std::to_string(pacman.get_life()), window);
                if (1 == pacman.get_animation_over()) {
                    if (1 == game_won) {
                        draw_text(true, 0, 0, "Next level!", window);
                    } else {
                        if (pacman.get_life() > 1) {
                            pacman.set_life();
                            pacman.set_dead(false);
                            game_won = false;

                            ghost_manager.reset(level, ghost_positions);

                            pacman.reset();
                        } else if (pacman.get_life() == 1) pacman.set_life();
                        if (pacman.get_life() < 1) {
                            draw_text(true, 0, 0, "Game over", window);
                        }
                    }
                }

                window.display();
            }
        }
    }
}