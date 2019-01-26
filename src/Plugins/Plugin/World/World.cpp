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

	g_graph.Initialize(pDummy);

	WayPoint * pWPStart = g_graph.FindNearestWayPoint(CShVector2(-200.0f, 200.0f));
	WayPoint * pWPEnd = g_graph.FindNearestWayPoint(CShVector2(200.0f, -200.0f));

	CShArray<WayPoint*> aPoints;
	g_graph.FindPath(pWPStart, pWPEnd, aPoints);
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
