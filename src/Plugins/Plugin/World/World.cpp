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
 * @brief World::CanCreateTowerAtPos
 * @param position
 * @return
 */
bool World::CanCreateTowerAtPos(const CShVector2 & position)
{
	ShDummyAABB2 * pDummy = ShDummyAABB2::Find(m_levelIdentifier, CShIdentifier("dummy_aabb2_auto_001"));

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

	return !bObstacle;
}

/**
 * @brief CreateTower
 */
void World::CreateTower(const CShVector2 & position, TowerBase::ETowerType towerType)
{
	if (CanCreateTowerAtPos(position))
	{
		m_towerManager.CreateTower(towerType, TowerBase::focus_nearest, position, 20, 3.0f);
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
}

/**
 * @brief SetGameSpeed
 */
void World::GainHP(void)
{
	++m_iHP;
}

/**
 * @brief SetGameSpeed
 */
void World::LooseMoney(int iAmountToLoose)
{
	m_iMoney = shMax(0, m_iMoney - iAmountToLoose);
}

/**
 * @brief SetGameSpeed
 */
void World::GainMoney(int iAmountToGain)
{
	m_iMoney += iAmountToGain;
}
