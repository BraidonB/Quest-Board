# CMakeList.txt : CMake project for QuestBoard, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (QuestBoard "QuestBoard.cpp" "QuestBoard.h" "Quest.h" "Quest.cpp" "Board.h" "Board.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET QuestBoard PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
