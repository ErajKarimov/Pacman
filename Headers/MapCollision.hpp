#ifndef HEADERS_MAPCOLLISION_HPP
#define HEADERS_MAPCOLLISION_HPP

int map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map);

#endif//HEADERS_MAPCOLLISION_HPP