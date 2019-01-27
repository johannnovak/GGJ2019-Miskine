cmake_minimum_required(VERSION 3.10)

# main files
set(SOURCES_main main.cpp)
source_group("" FILES ${SOURCES_main})

# Application files
set(SOURCES_Application Application.cpp Application.h Inputs.cpp Inputs.h)
source_group("" FILES ${SOURCES_Application})

# Game files
set(SOURCES_Game Game.cpp Game.h Game.inl)
source_group("Game" FILES ${SOURCES_Game})

# State files
set(SOURCES_GameState GameStates/GameState.cpp GameStates/GameState.h)
source_group("State" FILES ${SOURCES_GameState})

# Main menu
set(SOURCES_GameStateMainMenu GameStates/GameStateMainMenu.cpp GameStates/GameStateMainMenu.h)
source_group("State\\MainMenu" FILES ${SOURCES_GameStateMainMenu})

# Characters introduction
set(SOURCES_GameStateCharacterIntro GameStates/GameStateCharacterIntro.cpp GameStates/GameStateCharacterIntro.h)
source_group("State\\MainMenu" FILES ${SOURCES_GameCharacterIntro})

# Characters introduction
set(SOURCES_GameStateSettings GameStates/GameStateSettings.cpp GameStates/GameStateSettings.h)
source_group("State\\MainMenu" FILES ${SOURCES_GameSettings})

# Characters introduction
set(SOURCES_GameStateCredits GameStates/GameStateCredits.cpp GameStates/GameStateCredits.h)
source_group("State\\MainMenu" FILES ${SOURCES_GameCredits})

# Game
set(SOURCES_GameStateGame GameStates/GameStateGame.cpp GameStates/GameStateGame.h)
source_group("State\\Game" FILES ${SOURCES_GameStateGame})

# Game Over
set(SOURCES_GameStateGameOver GameStates/GameStateGameOver.cpp GameStates/GameStateGameOver.h)
source_group("State\\Game" FILES ${SOURCES_GameStateGameOver})

# Put everything together before adding platform-specific files
set(SOURCES 
${SOURCES_main}
${SOURCES_Application}
${SOURCES_Game}
${SOURCES_GameState}
${SOURCES_GameStateMainMenu}
${SOURCES_GameStateCharacterIntro}
${SOURCES_GameStateSettings}
${SOURCES_GameStateCredits}
${SOURCES_GameStateGame}
${SOURCES_GameStateGameOver}
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_executable(Game WIN32 ${SOURCES})
ELSE()
	add_executable(Game ${SOURCES})
ENDIF()

if (MSVC)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
	set_target_properties(Game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Cooking/Windows")
endif (MSVC)

set_property(TARGET Game PROPERTY FOLDER "Runtime")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

target_link_libraries(Game PRIVATE ${SHSDK_LIBRARIES})
target_link_libraries(Game PRIVATE Plugin)
target_include_directories(Game PRIVATE "${SHSDK_INCLUDE_DIR}" "$<TARGET_PROPERTY:Plugin,INCLUDE_DIRECTORIES>")
