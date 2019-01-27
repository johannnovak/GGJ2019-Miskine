cmake_minimum_required(VERSION 3.10)

set(SHINE_EDITOR_EXT_DIR "" CACHE PATH "Extension directory")
set(SHSDK_EDITOR_LIBRARIES "" CACHE PATH "ShSDK (editor) path") # FIXME

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Plugin files
set(SOURCES_Plugin Plugin.cpp Plugin.h)
source_group("Plugin" FILES ${SOURCES_Plugin})

# Factory files
set(SOURCES_Factory PluginFactory.cpp PluginFactory.h)
source_group("Factory" FILES ${SOURCES_Factory})

# World files
set(SOURCES_World World/World.cpp World/World.h)
source_group("World" FILES ${SOURCES_World})

# Inputs files
set(SOURCES_Inputs World/InputManager.cpp World/InputManager.h)
source_group("World\\Inputs" FILES ${SOURCES_Inputs})

# Enemy files
set(SOURCES_Enemy World/Enemy/Enemy.cpp World/Enemy/Enemy.h World/Enemy/EnemyManager.cpp World/Enemy/EnemyManager.h)
source_group("World\\Enemy" FILES ${SOURCES_Enemy})

# Wave files
set(SOURCES_Wave World/Wave/Wave.cpp World/Wave/Wave.h World/Wave/WaveManager.cpp World/Wave/WaveManager.h)
source_group("World\\Wave" FILES ${SOURCES_Wave})

# Tower files
set(SOURCES_Towers 
World/Tower/TowerBase.cpp 
World/Tower/TowerBase.h 
World/Tower/TowerManager.cpp 
World/Tower/TowerManager.h 
World/Tower/TowerRange.cpp 
World/Tower/TowerRange.h
World/Tower/TowerMelee.cpp 
World/Tower/TowerMelee.h
World/Tower/TowerProjectile.cpp 
World/Tower/TowerProjectile.h)
source_group("World\\Tower" FILES ${SOURCES_Towers})

# Graph files
set(SOURCES_Graph World/PathFinding/Graph.cpp World/PathFinding/Graph.h)
source_group("World\\PathFinding" FILES ${SOURCES_Graph})

# Node files
set(SOURCES_Node World/PathFinding/Node.cpp World/PathFinding/Node.h)
source_group("World\\PathFinding" FILES ${SOURCES_Node})

set(SOURCES_Player2Event	Players/Player2Event.cpp Players/Player2Event.h
							Players/Player2EventManager.cpp Players/Player2EventManager.h)
source_group("Players\\Player2\\Event" FILES ${SOURCES_Player2Event})

set(SOURCES_Player2EventTypeWords	Players/Player2EventTypeWords.cpp Players/Player2EventTypeWords.h)
source_group("Players\\Player2\\Event\\TypeWords" FILES ${SOURCES_Player2EventTypeWords})

#set(SOURCES_Player2EventBoostTower	Players/Player2EventBoostTower.cpp Players/Player2EventBoostTower.h)
#source_group("Players\\Player2\\Event\\BoostTower" FILES ${SOURCES_Player2EventBoostTower})
#
#set(SOURCES_Player2EventGrantSpecialAttack	Players/Player2EventGrantSpecialAttack.cpp Players/Player2EventGrantSpecialAttack.h)
#source_group("Players\\Player2\\Event\\GrantSpecialAttack" FILES ${SOURCES_Player2EventGrantSpecialAttack})
#
#set(SOURCES_Player2EventControlEnemy	Players/Player2EventControlEnemy.cpp Players/Player2EventControlEnemy.h)
#source_group("Players\\Player2\\Event\\ControlEnemy" FILES ${SOURCES_Player2EventControlEnemy})
#
#set(SOURCES_Player2EventImmediateQTE	Players/Player2EventImmediateQTE.cpp Players/Player2EventImmediateQTE.h)
#source_group("Players\\Player2\\Event\\ImmediateQTE" FILES ${SOURCES_Player2EventImmediateQTE})
#
#set(SOURCES_Player2EventSuperMegaCombo	Players/Player2EventSuperMegaCombo.cpp Players/Player2EventSuperMegaCombo.h)
#source_group("Players\\Player2\\Event\\SuperMegaCombo" FILES ${SOURCES_Player2EventSuperMegaCombo})

set(SOURCES_Player2EventListener	Players/IPlayer2EventListener.h)
source_group("Players\\Player2\\Event" FILES ${SOURCES_Player2EventListener})

# Put everything together before adding platform-specific files
set(SOURCES 
${SOURCES_Plugin}
${SOURCES_Factory}
${SOURCES_World}
${SOURCES_Inputs}
${SOURCES_Enemy}
${SOURCES_Towers}
${SOURCES_Graph}
${SOURCES_Node}
${SOURCES_Wave}
${SOURCES_Player2Event}
${SOURCES_Player2EventTypeWords}
#${SOURCES_Player2EventBoostTower}
#${SOURCES_Player2EventGrantSpecialAttack}
#${SOURCES_Player2EventControlEnemy}
#${SOURCES_Player2EventImmediateQTE}
${SOURCES_Player2EventListener}
)

# Compile to use it on Runtime
add_library(Plugin STATIC ${SOURCES})
set_property(TARGET Plugin PROPERTY FOLDER "Runtime")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

if (NOT MSVC)
	set_property(TARGET Plugin APPEND PROPERTY COMPILE_FLAGS "-fno-exceptions -fno-rtti")
endif()

target_link_libraries(Plugin INTERFACE ${SHSDK_LIBRARIES})

target_include_directories(Plugin PUBLIC "${SHSDK_INCLUDE_DIR}")
target_include_directories(Plugin INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

# Compile to use it in the Shine Editor
add_library(Plugin_Editor SHARED ${SOURCES_main} ${SOURCES})
set_property(TARGET Plugin_Editor PROPERTY FOLDER "Editor")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET Plugin_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

if (NOT MSVC)
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_FLAGS " -fPIC -fno-exceptions -fno-rtti")
endif()

target_link_libraries(Plugin_Editor PRIVATE ${SHSDK_EDITOR_LIBRARIES})

target_include_directories(Plugin_Editor PUBLIC "${SHSDK_INCLUDE_DIR}")
target_include_directories(Plugin_Editor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
