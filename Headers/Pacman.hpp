#ifndef HEADERS_PACMAN_HPP
#define HEADERS_PACMAN_HPP

class Pacman {
    //This is used for the death animation.
    bool animation_over;
    //Am I dead?
    bool dead;

    unsigned char direction;

    //More timers!
    unsigned short animation_timer{};
    unsigned short energizer_timer;

    //Current location of this creature, commonly known as Pacman.
    Position position;

    short life;
    unsigned int score;

public:
    Pacman();

    [[nodiscard]] bool get_animation_over() const;
    [[nodiscard]] bool get_dead() const;

    [[nodiscard]] unsigned char get_direction() const;

    [[nodiscard]] unsigned short get_energizer_timer() const;

    [[nodiscard]] short get_life() const;

    [[nodiscard]] unsigned short get_score() const;

    void draw(bool i_victory, sf::RenderWindow &i_window);
    void reset();
    void reset_ls();
    void set_animation_timer(unsigned short i_animation_timer);
    void set_dead(bool i_dead);
    void set_position(short i_x, short i_y);
    void set_life();
    void set_score();
    void update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map);

    Position get_position();
};

#endif//HEADERS_PACMAN_HPP