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
	
	CShIdentifier levelIdentifier("level_test_pathfinding");

	m_enemyManager.Initialize(levelIdentifier);
	m_towerManager.Initialize(levelIdentifier, &m_enemyManager);

	ShDummyAABB2* pDummy = ShDummyAABB2::Find(levelIdentifier, CShIdentifier("dummy_aabb2_auto_001"));
	SH_ASSERT(shNULL != pDummy);

	g_graph.Initialize(pDummy);

	Node * pWPStart = g_graph.FindNearestWayPoint(CShVector2(-200.0f, 200.0f));
	Node * pWPEnd = g_graph.FindNearestWayPoint(CShVector2(200.0f, -200.0f));

	CShArray<Node*> aPoints;
	g_graph.FindPath(pWPStart, pWPEnd, aPoints);
}

/**
 * @brief Release
 */
void World::Release(void)
{
	m_inputManager.Release();

	m_enemyManager.Release();
	m_towerManager.Release();
}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();
}

/**
 * @brief CreateTower
 */
void World::CreateTower(const CShVector2 & position)
{
	m_towerManager.CreateTower(TowerBase::tower_melee, TowerBase::focus_nearest, CShVector3(position, 5.0f), 10.0f, 3.0f);
}
