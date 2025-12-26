#Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

#Назва проекту
project(My3DViewer)

#Встановлення стандарту C++
set(CMAKE_CXX_STANDARD 17)

#Пошук необхідних пакетів
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

#Додавання виконуваного файлу
add_executable(My3DViewer main.cpp)

#Підключення бібліотек
target_link_libraries(My3DViewer PRIVATE glfw)

#Відключення попередження щодо обробки виключень з стандартними функціями c++ у MSVC
if(MSVC)
    add_compile_options(/EHsc)
endif()