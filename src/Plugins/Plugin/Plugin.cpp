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
	m_world.Initialize(levelIdentifier);

	Player2EventManager::GetInstance().Initialize();

	m_pSelectionCircle = ShPrefab::Find(levelIdentifier, CShIdentifier("selection_circle_001"));
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
					m_world.CreateTower(m_vSelectionPosition, TowerBase::tower_mere);
				}
				else if (normalizedDir.m_x > 0.0f && angle < SHC_PI_ON_4)
				{
					m_world.CreateTower(m_vSelectionPosition, TowerBase::tower_fille);
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
	// ...
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
