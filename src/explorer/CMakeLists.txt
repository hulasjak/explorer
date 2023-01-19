
# set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
# set(SFML)
# find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)

add_executable(${PROJECT_NAME}
               main.cpp
               location.cpp
               player.cpp
               game_manager.cpp
               physics_engine.cpp
               character.cpp
               enemy.cpp)

# add_executable(a_star 
#                 a_star_impl.cpp)

# target_include_directories(a_star PUBLIC
#                 ${PROJECT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} PUBLIC
${PROJECT_SOURCE_DIR}/src
${PROJECT_SOURCE_DIR}/SFML
)

MESSAGE(STATUS CMakePrintSystemInformation)
target_link_libraries(${PROJECT_NAME} PUBLIC
sfml-graphics
sfml-audio
sfml-window 
sfml-system
)
MESSAGE(STATUS ${CMAKE_BINARY_DIR})


install(TARGETS 
            ${PROJECT_NAME}
            # a_star
        DESTINATION 
            ${CMAKE_BINARY_DIR})