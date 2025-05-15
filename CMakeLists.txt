cmake_minimum_required(VERSION 3.20) # Змінено на більш поширену версію, 3.30 ще не вийшла.
# Якщо ви використовуєте specific nightly build, можете повернути 3.30.
project(crmautoservice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) # Гарантує, що вказаний стандарт буде використано.
set(CMAKE_CXX_EXTENSIONS OFF)         # Вимикає розширення компілятора (GNU extensions), для кращої портабельності.

add_executable(crmautoservice
        main.cpp
        Menu.cpp
        ServiceManager.cpp
        Utils.cpp
)

# Для windows.h (SetConsoleCP, SetConsoleOutputCP) зазвичай не потрібні
# явні команди лінкування, оскільки kernel32.lib (де ці функції знаходяться)
# лінкується за замовчуванням компіляторами для Windows (MSVC, MinGW).
# if(WIN32)
#   target_link_libraries(crmautoservice PRIVATE kernel32) # Приклад, якщо б знадобилося
# endif()