#include "ShSDK/ShSDK.h"

#include "PathFinding/Graph.h"
#include "World.h"

/**
 * @brief Constructor
 */
World::World(void)
{
	// ...
}

/**
 * @brief Destructor
 */
World::~World(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void World::Initialize(void)
{
	ShUser * pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != pUser);

	m_inputManager.Initialize(pUser);

	ShDummyAABB2* pDummy = ShDummyAABB2::Find(CShIdentifier("level_test_pathfinding"), CShIdentifier("dummy_aabb2_auto_001"));
	SH_ASSERT(shNULL != pDummy);
	
	ShEntity2* pEntity = ShEntity2::Find(CShIdentifier("level_test_pathfinding"), CShIdentifier("sprite_player_walk_01_001"));
	CShVector2 vPosition = ShEntity2::GetWorldPosition2(pEntity);

	g_graph.Initialize(pDummy);
}

/**
 * @brief Release
 */
void World::Release(void)
{

}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();
}
