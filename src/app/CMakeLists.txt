cmake_minimum_required(VERSION 3.12)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp app_config.cpp
  logger.cpp home_assistant.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_libraries(${CMAKE_PROJECT_NAME}
  PRIVATE
    common_event common_executor poller device
    home-assistant-adapter main_board event
    common_utils
)

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)
