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
 */
void World::Initialize(const CShIdentifier & levelIdentifier)
{
	ShUser * pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != pUser);

	m_inputManager.Initialize(pUser);

	m_enemyManager.Initialize(levelIdentifier);
	m_waveManager.Initialize(levelIdentifier, &m_enemyManager);
	m_towerManager.Initialize(levelIdentifier, &m_enemyManager);

	ShDummyAABB2* pDummy = ShDummyAABB2::Find(levelIdentifier, CShIdentifier("dummy_aabb2_auto_001"));

	SH_ASSERT(shNULL != pDummy);

	g_graph.Initialize(pDummy);

	Node * pWPStart = g_graph.FindNearestWayPoint(CShVector2(-200.0f, 200.0f));
	Node * pWPEnd = g_graph.FindNearestWayPoint(CShVector2(200.0f, -200.0f));

	CShArray<Node*> aPoints;
	g_graph.FindPath(pWPStart, pWPEnd, aPoints);

	m_waveManager.Start();
}

/**
 * @brief Release
 */
void World::Release(void)
{
	m_inputManager.Release();
	m_waveManager.Release();
	m_enemyManager.Release();
	m_towerManager.Release();
}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();
	m_waveManager.Update(dt);
	m_enemyManager.Update(dt);
	m_towerManager.Update(dt);
}

/**
 * @brief CreateTower
 */
void World::CreateTower(const CShVector2 & position)
{
	m_towerManager.CreateTower(TowerBase::tower_pere, TowerBase::focus_nearest, position, 20, 3.0f);
	g_graph.AddBlocker(position, 30.0f);
	g_graph.UpdateGraph();
}
