cmake_minimum_required(VERSION 3.10)
project(WebServer C)

set(CMAKE_C_STANDARD 99)

# Список исходников
set(SOURCES
    config.c
    main.c
    request.c
    response.c
    server.c
    utils.c
)

# Собрать исполняемый файл
add_executable(webserver ${SOURCES})

# Линковка с нужными библиотеками (для Linux)
target_link_libraries(webserver PRIVATE m)