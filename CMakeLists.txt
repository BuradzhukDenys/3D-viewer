#Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

#Назва проекту
project(My3DViewer)

#Встановлення стандарту C++
set(CMAKE_CXX_STANDARD 20)

#Пошук необхідних пакетів
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

#Додавання виконуваного файлу
add_executable(My3DViewer
    main.cpp
    ViewerWindow.h
    ViewerWindow.cpp
    glad.c)

#Підключення бібліотек
target_link_libraries(My3DViewer PRIVATE glfw)

#Підключення папки із проектом, як джерело де шукати .h та .hpp файли
target_include_directories(My3DViewer PRIVATE ${CMAKE_SOURCE_DIR})

#Додавання директиви GLFW_INCLUDE_NONE щоб використовувати функції OpenGL через glad
target_compile_definitions(My3DViewer PRIVATE GLFW_INCLUDE_NONE)

#Відключення попередження щодо обробки виключень з стандартними функціями c++ у MSVC
if(MSVC)
    add_compile_options(/EHsc)
endif()