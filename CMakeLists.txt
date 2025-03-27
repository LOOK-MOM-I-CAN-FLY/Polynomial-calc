cmake_minimum_required(VERSION 3.10)
project(PolynomialCalc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

# Основные исходные файлы
set(SOURCES
    main.cpp
    polynomial.h
    modint.h
    factor_ring.h
)

add_executable(PolynomialCalc ${SOURCES})

# Подключаем Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# Для Windows: предотвращает переопределение настроек компилятора/линкера
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включаем тестирование
enable_testing()

# Тестовый исполняемый файл (файл с тестами должен находиться в папке tests)
add_executable(PolynomialCalcTests
    tests/test_polynomial.cpp
    polynomial.h
    modint.h
    factor_ring.h
)
target_link_libraries(PolynomialCalcTests gtest_main)
include(GoogleTest)
gtest_discover_tests(PolynomialCalcTests)

# Конфигурация упаковки через CPack (будет собирать deb и rpm пакеты)
set(CPACK_PACKAGE_NAME "PolynomialCalc")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name")
include(CPack)
