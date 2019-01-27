#include "ShSDK/ShSDK.h"

#include "PathFinding/Graph.h"
#include "World.h"

static const float tower_radius = 30.0f;
static const float half_tower_radius = tower_radius * 0.5f;

/**
 * @brief Constructor
 */
World::World(void)
: m_fGameSpeed(1.0f)
, m_iHP(DEFAULT_HP_DIFFICULTY_MEDIUM)
, m_iMoney(DEFAULT_MONEY_DIFFICULTY_MEDIUM)
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

	ShSoundResource * pMusicMain = ShSoundResource::Find(CShIdentifier("music_main"));
	ShSound::PlayMusic(pMusicMain, m_soundHandle);

	m_inputManager.Initialize(pUser);

	m_enemyManager.Initialize(levelIdentifier);
	m_waveManager.Initialize(levelIdentifier, &m_enemyManager);
	m_towerManager.Initialize(levelIdentifier, &m_enemyManager);

	ShDummyAABB2* pDummy = ShDummyAABB2::Find(levelIdentifier, CShIdentifier("dummy_aabb2_auto_001"));
	SH_ASSERT(shNULL != pDummy);

	g_graph.Initialize(pDummy);

	m_waveManager.Start();

	m_levelIdentifier = levelIdentifier;
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

	ShSound::Stop(m_soundHandle);
}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();
	m_waveManager.Update(dt * m_fGameSpeed);
	m_enemyManager.Update(dt * m_fGameSpeed);
	m_towerManager.Update(dt * m_fGameSpeed);
}

/**
 * @brief RegisterWorldListener
 */
bool World::RegisterWorldListener(IWorldListener * pListener)
{
	if (shNULL == pListener)
	{
		return false;
	}

	m_pWorldListener = pListener;

	return true;
}

/**
 * @brief UnregisterWorldListener
 */
bool World::UnregisterWorldListener(IWorldListener * pListener)
{
	if (shNULL == pListener)
	{
		return false;
	}
	else if (m_pWorldListener != pListener)
	{
		return false;
	}
	else
	{
		m_pWorldListener = shNULL;

		return true;
	}
}

/**
 * @brief World::IsTowerAtPos
 * @param position
 * @return
 */
bool World::IsTowerAtPos(const CShVector2 & position, TowerBase * & pTowerOut)
{
	CShArray<TowerBase*> aTowers;
	m_towerManager.GetTowerList(aTowers);

	int iTowerCount = aTowers.GetCount();
	for (int iTowerIndex = 0; iTowerIndex < iTowerCount; ++iTowerIndex)
	{
		TowerBase * pTower = aTowers[iTowerIndex];
		ShEntity2 * pEntity2 = pTower->GetCurrentEntity2();
		CShRectangle2 rect;
		rect.SetPosition(aTowers[iTowerIndex]->GetPosition());
		rect.SetHeight(ShEntity2::GetHeight(pEntity2));
		rect.SetWidth(ShEntity2::GetWidth(pEntity2));

		if (rect.Contains(position))
		{
			pTowerOut = pTower;

			return true;
		}
	}

	pTowerOut = shNULL;

	return false;
}

/**
 * @brief World::CanCreateTowerAtPos
 * @param position
 * @return
 */
bool World::CanCreateTowerAtPos(const CShVector2 & position)
{
	ShDummyAABB2 * pDummy = ShDummyAABB2::Find(m_levelIdentifier, CShIdentifier("dummy_aabb2_auto_001"));

	{
		CShVector2 vParentPosition = ShObject::GetWorldPosition2(pDummy);

		const CShAABB2 & AABB = ShDummyAABB2::GetAABB(pDummy);

		const CShVector2 Min = vParentPosition + AABB.GetMin();
		const CShVector2 Max = vParentPosition + AABB.GetMax();

		if (!((position.m_x+half_tower_radius) > shMin(Min.m_x, Max.m_x) && (position.m_y+half_tower_radius) > shMin(Min.m_y, Max.m_y) && (position.m_x-half_tower_radius) < shMax(Min.m_x, Max.m_x) && (position.m_y-half_tower_radius) < shMax(Min.m_y, Max.m_y)))
		{
			return false;
		}
	}

	CShArray<ShObject*> aChildren;
	ShDummyAABB2::GetChildArray(pDummy, aChildren);

	bool bObstacle = false;

	for (int i = 0; i < aChildren.GetCount(); ++i)
	{
		CShVector2 vChildPosition = ShObject::GetWorldPosition2(aChildren[i]);

		if (ShDummyAABB2 * pDummyAABB = ShObject::Cast<ShDummyAABB2>(aChildren[i]))
		{
			const CShAABB2 & AABB = ShDummyAABB2::GetAABB(pDummyAABB);

			const CShVector2 Min = vChildPosition + AABB.GetMin();
			const CShVector2 Max = vChildPosition + AABB.GetMax();

			if ((position.m_x+half_tower_radius) > shMin(Min.m_x, Max.m_x) && (position.m_y+half_tower_radius) > shMin(Min.m_y, Max.m_y) && (position.m_x-half_tower_radius) < shMax(Min.m_x, Max.m_x) && (position.m_y-half_tower_radius) < shMax(Min.m_y, Max.m_y))
			{
				bObstacle = true;
				break;
			}
		}
		else if (ShDummyCircle * pDummyCircle = ShObject::Cast<ShDummyCircle>(aChildren[i]))
		{
			const CShCircle & Circle = ShDummyCircle::GetCircle(pDummyCircle);

			if (position.Distance(vChildPosition + CShVector2(Circle.GetCenter().m_x, Circle.GetCenter().m_y)) < (half_tower_radius+Circle.GetRadius()))
			{
				bObstacle = true;
				break;
			}
		}
	}

	if (!bObstacle)
	{
		CShArray<TowerBase*> aTowerList;
		m_towerManager.GetTowerList(aTowerList);

		for (int i = 0; i < aTowerList.GetCount(); ++i)
		{
			if (position.Distance(aTowerList[i]->GetPosition()) < (tower_radius))
			{
				bObstacle = true;
				break;
			}
		}
	}

	if (bObstacle)
	{
		return false;
	}

	unsigned int index = g_graph.AddBlocker(position, 30.0f);

	g_graph.UpdateGraph();
	g_graph.ResetAll();

	CShVector2 vEndPosition(196.0f, -305.0f);

	CShArray<CShVector2> aStartPosition;
	aStartPosition.Add(CShVector2(-325.0f, 268.0f));
	aStartPosition.Add(CShVector2(175.0f, 288.0f));
	aStartPosition.Add(CShVector2(-32.0f, -90.0f));
	aStartPosition.Add(CShVector2(-292.0f, -14.0f));

	bool bBlocking = false;

	for (int i = 0; i < aStartPosition.GetCount(); ++i)
	{
		CShArray<Node*> aNodes;
		if (!g_graph.FindPath(g_graph.FindNearestWayPoint(aStartPosition[i]), g_graph.FindNearestWayPoint(vEndPosition), aNodes))
		{
			bBlocking = true;
			break;
		}
	}

	g_graph.RemoveBlocker(index);

	g_graph.UpdateGraph();
	g_graph.ResetAll();

	if (bBlocking)
	{
		return false;
	}

	return true;
}

/**
 * @brief CreateTower
 */
void World::CreateTower(const CShVector2 & position, TowerBase::ETowerType towerType)
{
	if (CanCreateTowerAtPos(position) && m_iMoney >= TowerManager::GetCostByType(towerType))
	{
		TowerBase * pTower = m_towerManager.CreateTower(towerType, TowerBase::focus_nearest, position, 20, 3.0f);
		g_graph.AddBlocker(position, tower_radius);
		g_graph.UpdateGraph();

		CShArray<Enemy*> aEnemyList;
		m_enemyManager.GetEnemyList(aEnemyList);

		for (int i = 0; i < aEnemyList.GetCount(); ++i)
		{
			CShArray<Node*> aNodes;
			g_graph.FindPath(g_graph.FindNearestWayPoint(aEnemyList[i]->GetPosition()), g_graph.FindNearestWayPoint(CShVector2(196.0f, -305.0f)), aNodes);
			aEnemyList[i]->SetPath(aNodes);
		}
		
		//
		// Notify listener
		if (shNULL != m_pWorldListener)
		{
			m_pWorldListener->OnTowerCreated(pTower);
		}
	}
}

/**
 * @brief SetGameSpeed
 */
void World::SetGameSpeed(float fGameSpeed)
{
	m_fGameSpeed = fGameSpeed;
}

/**
 * @brief SetGameSpeed
 */
void World::LooseHP(void)
{
	m_iHP = shMax(0, m_iHP - 1);

	//
	// Notify listener
	if (shNULL != m_pWorldListener)
	{
		m_pWorldListener->OnHPUpdated(m_iHP);
	}
}

/**
 * @brief SetGameSpeed
 */
void World::GainHP(void)
{
	++m_iHP;

	//
	// Notify listener
	if (shNULL != m_pWorldListener)
	{
		m_pWorldListener->OnHPUpdated(m_iHP);
	}
}

/**
 * @brief SetGameSpeed
 */
void World::LooseMoney(int iAmountToLoose)
{
	m_iMoney = shMax(0, m_iMoney - iAmountToLoose);

	//
	// Notify listener
	if (shNULL != m_pWorldListener)
	{
		m_pWorldListener->OnMoneyUpdated(m_iMoney);
	}
}

/**
 * @brief SetGameSpeed
 */
void World::GainMoney(int iAmountToGain)
{
	m_iMoney += iAmountToGain;

	//
	// Notify listener
	if (shNULL != m_pWorldListener)
	{
		m_pWorldListener->OnMoneyUpdated(m_iMoney);
	}
}

/**
 * @brief World::GetEnemyManager
 * @return
 */
EnemyManager & World::GetEnemyManager(void)
{
	return m_enemyManager;
}

