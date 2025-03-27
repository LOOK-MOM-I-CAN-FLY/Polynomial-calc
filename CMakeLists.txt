cmake_minimum_required(VERSION 3.10)
project(PolynomialCalc)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем корневой каталог для поиска заголовков
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Основные исходные файлы
set(SOURCES
    main.cpp
    polynomial.h
    modint.h
    factor_ring.h
)

add_executable(PolynomialCalc ${SOURCES})

# Настройка Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# Для Windows: предотвращает переопределение настроек компилятора/линкера
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Добавляем тесты (файл tests/test_polynomial.cpp)
set(TEST_SOURCES tests/test_polynomial.cpp)
add_executable(PolynomialCalcTests ${TEST_SOURCES})
target_link_libraries(PolynomialCalcTests gtest_main)
# Обязательно добавляем корневую директорию для поиска заголовков
target_include_directories(PolynomialCalcTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(PolynomialCalcTests)
