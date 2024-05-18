# Инструкция по сборке

# Сборка проекта с использованием CMake
1. Создайте директорию для сборки проекта:

..
mkdir build
cd build
..

3. Сгенерируйте файлы проекта с помощью CMake (для Linux с использованием gcc):

..
cmake ..

..

4. Для Windows с использованием MinGW, используйте следующую команду:

..
cmake -G "MinGW Makefiles" ..
..

5. Соберите проект с помощью сгенерированных файлов проекта:
...
cmake --build .


# Сборка проекта без использования CMake
1. Собирите файлы проекта для Linux с использованием gcc командой:

..
gcc -o Task Main.cpp CompClub.cpp Client.cpp Table.cpp -lstdc++
..

  или с использованием g++:
 
  ..
  gcc -o Task Main.cpp CompClub.cpp Client.cpp Table.cpp
  ..

2. Собирите файлы проекта для Windows с использованием MinGW командой:

..
gcc -o Task.exe Main.cpp CompClub.cpp Client.cpp Table.cpp -lstdc++
..
