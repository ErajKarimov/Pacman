# Pacman
![img.png](Screenshots%2Fimg.png)
![img_1.png](Screenshots%2Fimg_1.png)

"Pacman" - это игра, созданная на языке программирования C++20 с использованием библиотеки SFML. Игрок управляет персонажем под названием «Пакмен», который должен съесть все точки в лабиринте, избегая при этом призраков.

## Требования

- C++ 20
- Библиотека SFML (2.5 или выше)
- CMake (3.10 или выше)

## Установка(Windows)
-Убедитесь что у вас установлен Make, Cmake, SFML, MinGW.

Скачайте SFML по этой [ссылке](https://www.sfml-dev.org/download/sfml/2.5.1/)(По умолчанию она добавлена в проект) можете не скачивать

GCC 7.3.0 MinGW (SEH) - 64-bit

MinGw можете скачать по этой же ссылке

Make- ссылка на [туториал](https://leangaurav.medium.com/how-to-setup-install-gnu-make-on-windows-324480f1da69)(используйте VPN)

- Создайте директорию `build` в корневой папке проекта
- Перейдите в директорию `build`
- Запустите cmake с параметрами: `cmake -G "MinGW Makefiles" ..`
- Соберите проект: `make`

## Установка(Linux)
-Убедитесь что у вас установлен Make, Cmake, SFML, MinGW.

Скачайте SFML по этой [ссылке](https://www.sfml-dev.org/download/sfml/2.5.1/)

GCC - 64-bit

Разархивировать, у поменять SFML, на папку которую вы получили

У вас должно получиться Pacman/SFML/(include lib share)

Раскомментировать 21ю строку в файле CMakeLists.txt

И закомментировать 22ю строчку в файле CMakeLists.txt 

- Создайте директорию `build` в корневой папке проекта
- Перейдите в директорию `build`
- Запустите cmake с параметрами: `cmake ..`
- Соберите проект: `make`


## Использование

- Запустите файл `Pacman.exe`, находящийся в директории `build`.
- Запустите файл `Pacman`, находящийся в директории `build`.(В терминале ./Pacman)
