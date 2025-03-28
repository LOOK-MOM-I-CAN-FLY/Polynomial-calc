cmake_minimum_required(VERSION 3.10)
project(Polynomial_Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Главный исполняемый файл
add_executable(calculator main.cpp)

# Добавляем Google Test как подмодуль
add_subdirectory(googletest)

# Включаем включаемые директории для тестов
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Включаем текущую директорию для включения заголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Включаем поддержку тестирования
enable_testing()

# Добавляем директорию с тестами
add_subdirectory(tests) 