#ifndef HEADERS_CONVERTSKETCH_HPP
#define HEADERS_CONVERTSKETCH_HPP

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT> &i_map_sketch, std::array<Position, 4> &i_ghost_positions, Pacman &i_pacman);

#endif//HEADERS_CONVERTSKETCH_HPP