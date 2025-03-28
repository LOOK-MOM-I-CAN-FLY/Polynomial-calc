# Настройки CPack
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "polynomial-calculator")
set(CPACK_PACKAGE_VENDOR "Student")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Polynomial Calculator - калькулятор многочленов")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_CONTACT "student@example.com")

# Настройки для RPM
set(CPACK_RPM_PACKAGE_REQUIRES "glibc >= 2.17")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Applications/Science")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Polynomial Calculator - программа для выполнения операций над многочленами и работы с фактор-кольцами.")

# Настройки для DEB
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.17)")
set(CPACK_DEBIAN_PACKAGE_SECTION "math")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/student/polynomial_calc")

# Настройки для обоих типов пакетов
set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

# Файлы, которые должны быть установлены
install(TARGETS calculator DESTINATION bin)
install(FILES polynomial.h modint.h factor_ring.h DESTINATION include/polynomial_calc)

include(CPack) 