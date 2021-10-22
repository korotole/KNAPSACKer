cmake_minimum_required(VERSION 3.16.3)

project(knapsack)

add_executable(${PROJECT_NAME} src/main.cpp)


add_subdirectory("src")

target_link_directories(${PROJECT_NAME} PRIVATE
                            "src"
)

target_include_directories(${PROJECT_NAME} PUBLIC
                            "src" 
)

target_link_libraries(${PROJECT_NAME} src)