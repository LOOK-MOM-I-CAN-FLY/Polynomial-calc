set(TESTS
    test_polynomial.cpp
    test_modint.cpp
    test_factor_ring.cpp
    test_addition.cpp
    test_subtraction.cpp
    test_multiplication.cpp
    test_division.cpp
)

# Создаем тестовый исполняемый файл
add_executable(run_tests ${TESTS})

# Устанавливаем зависимости для компиляции
target_link_libraries(run_tests gtest gtest_main)

# Добавляем тест в список тестов cmake
add_test(
    NAME polynomial_tests
    COMMAND run_tests
) 