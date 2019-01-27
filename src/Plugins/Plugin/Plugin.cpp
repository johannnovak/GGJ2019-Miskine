#include "Plugin.h"

const CShIdentifier plugin_identifier("PluginGGJ2019");

/**
 * @brief Constructor
 */
Plugin::Plugin(void)
: CShPlugin(plugin_identifier)
, m_world()
, m_pSelectionCircle(shNULL)
, m_vSelectionPosition(0.0f, 0.0f)
, m_pHoveredTower(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
/*virtual*/ Plugin::~Plugin(void)
{
	// ...
}

/**
 * @brief OnPlayStart
 */
/*virtual*/ void Plugin::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	srand(time_t(NULL));

	m_world.Initialize(levelIdentifier);

	Player2EventManager::GetInstance().Initialize();

	m_pSelectionCircle = ShPrefab::Find(levelIdentifier, CShIdentifier("selection_circle_001"));

	m_apEntitesAvailable[0] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_pere_idle_01_001"));
	m_apEntitesAvailable[1] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_mere_idle_01_001"));
	m_apEntitesAvailable[2] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_fils_idle_01_001"));
	m_apEntitesAvailable[3] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_fille_idle_01_001"));

	m_apEntitesUnavailable[0] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_pere_unavailable_001"));
	m_apEntitesUnavailable[1] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_mere_unavailable_001"));
	m_apEntitesUnavailable[2] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_fils_unavailable_001"));
	m_apEntitesUnavailable[3] = (ShEntity2*)ShPrefab::FindObjectInPrefab(m_pSelectionCircle, CShIdentifier("sprite_game_fille_unavailable_001"));
}

/**
 * @brief OnPlayStop
 */
/*virtual*/ void Plugin::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	SH_UNUSED(levelIdentifier);
	m_world.Release();

	Player2EventManager::GetInstance().Release();
}

/**
 * @brief OnPlayPause
 */
/*virtual*/ void Plugin::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
 * @brief OnPlayResume
 */
/*virtual*/ void Plugin::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
 * @brief OnPreUpdate
 */
/*virtual*/ void Plugin::OnPreUpdate(float dt)
{
	// ...
}

/**
 * @brief OnPostUpdate
 */
/*virtual*/ void Plugin::OnPostUpdate(float dt)
{
	m_world.Update(dt);
	Player2EventManager::GetInstance().Update(dt);
}

/**
 * @brief OnTouchDown
 */
void Plugin::OnTouchDown(int iTouch, float positionX, float positionY)
{
	const CShVector2 pos(positionX, positionY);

	if (m_pSelectionCircle)
	{
		if (m_world.CanCreateTowerAtPos(pos))
		{
			m_vSelectionPosition = pos;
			ShPrefab::SetWorldPosition2(m_pSelectionCircle, m_vSelectionPosition);
			ShPrefab::SetShow(m_pSelectionCircle, true);

			if (TowerManager::GetCostByType(TowerBase::tower_pere) > m_world.GetMoney())
			{
				ShEntity2::SetShow(m_apEntitesAvailable[0], false);
				ShEntity2::SetShow(m_apEntitesUnavailable[0], true);
			}
			else
			{
				ShEntity2::SetShow(m_apEntitesAvailable[0], true);
				ShEntity2::SetShow(m_apEntitesUnavailable[0], false);
			}

			if (TowerManager::GetCostByType(TowerBase::tower_mere) > m_world.GetMoney())
			{
				ShEntity2::SetShow(m_apEntitesAvailable[1], false);
				ShEntity2::SetShow(m_apEntitesUnavailable[1], true);
			}
			else
			{
				ShEntity2::SetShow(m_apEntitesAvailable[1], true);
				ShEntity2::SetShow(m_apEntitesUnavailable[1], false);
			}

			if (TowerManager::GetCostByType(TowerBase::tower_fils) > m_world.GetMoney())
			{
				ShEntity2::SetShow(m_apEntitesAvailable[2], false);
				ShEntity2::SetShow(m_apEntitesUnavailable[2], true);
			}
			else
			{
				ShEntity2::SetShow(m_apEntitesAvailable[2], true);
				ShEntity2::SetShow(m_apEntitesUnavailable[2], false);
			}

			if (TowerManager::GetCostByType(TowerBase::tower_fille) > m_world.GetMoney())
			{
				ShEntity2::SetShow(m_apEntitesAvailable[3], false);
				ShEntity2::SetShow(m_apEntitesUnavailable[3], true);
			}
			else
			{
				ShEntity2::SetShow(m_apEntitesAvailable[3], true);
				ShEntity2::SetShow(m_apEntitesUnavailable[3], false);
			}
		}
	}
}

/**
 * @brief OnTouchUp
 */
void Plugin::OnTouchUp(int iTouch, float positionX, float positionY)
{
	const CShVector2 pos(positionX, positionY);

	if (m_pSelectionCircle)
	{
		if (ShPrefab::IsShow(m_pSelectionCircle))
		{
			CShVector2 dir = pos - m_vSelectionPosition;
			if (m_vSelectionPosition.Distance(pos) > 10.0f)
			{
				CShVector2 normalizedDir = dir.getNormalized();
				float fCos = normalizedDir.DotProduct(CShVector2(1.0f, 0.0f));
				float angle = acos(fCos);
				if (normalizedDir.m_y > 0.0f && angle > SHC_PI_ON_4 && angle < SHC_3PI_ON_4)
				{
					m_world.CreateTower(m_vSelectionPosition, TowerBase::tower_pere);
				}
				else if (normalizedDir.m_y < 0.0f && angle > SHC_PI_ON_4 && angle < SHC_3PI_ON_4)
				{
					m_world.CreateTower(m_vSelectionPosition, TowerBase::tower_fils);
				}
				else if (normalizedDir.m_x < 0.0f && angle > SHC_3PI_ON_4)
				{
					m_world.CreateTower(m_vSelectionPosition, TowerBase::tower_fille);
				}
				else if (normalizedDir.m_x > 0.0f && angle < SHC_PI_ON_4)
				{
					m_world.CreateTower(m_vSelectionPosition, TowerBase::tower_mere);
				}
			}
			ShPrefab::SetShow(m_pSelectionCircle, false);
		}
	}
}

/**
 * @brief OnTouchMove
 */
void Plugin::OnTouchMove(int iTouch, float positionX, float positionY)
{
	TowerBase * pTower = shNULL;
	if(m_world.IsTowerAtPos(CShVector2(positionX, positionY), pTower))
	{
		if (shNULL == m_pHoveredTower)
		{
			m_pHoveredTower = pTower;
			m_pHoveredTower->SetShowDebugInfo(true);
		}
		else if (pTower != m_pHoveredTower)
		{
			m_pHoveredTower->SetShowDebugInfo(false);
			m_pHoveredTower = pTower;
			m_pHoveredTower->SetShowDebugInfo(true);
		}
	}
	else
	{
		if (shNULL != m_pHoveredTower)
		{
			m_pHoveredTower->SetShowDebugInfo(false);
			m_pHoveredTower = shNULL;
		}
	}
}

/**
 * @brief GetDistanceSquared
 */
float Plugin::GetDistanceSquared(const CShVector2 & start, const CShVector2 & dest)
{
	//TODO Test me

	CShVector2 A(dest);
	CShVector2 B(start);
	CShVector2 delta = A - B;

	return delta.DotProduct(delta);
}


/**
 * @brief GetWorld
 */
World & Plugin::GetWorld(void)
{
	return m_world;
}
