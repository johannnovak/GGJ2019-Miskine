#include "Enemy.h"
#include "../PathFinding/Graph.h"

/**
 * @brief Constructor
 */
Enemy::Enemy(void)
: m_eState(e_state_off)
, m_fStateTime(0.0f)
, m_fSpeed(1.0f)
, m_pEntityLifeBar(shNULL)
, m_vPosition(CShVector2::ZERO)
, m_vStartPosition(CShVector2::ZERO)
, m_v(CShVector2::ZERO)
, m_fCompletion(0.0f)
, m_baseHealth(0)
, m_currentHealth(0)
, m_aNodes()
, m_iDestinationNode(0)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.0f)
, m_currentSprite(0)
, m_aMoveAnimation()
{
	// ...
}

/**
 * @brief Destructor
 */
Enemy::~Enemy(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void Enemy::Initialize(const CShArray<ShEntity2*> aEntity, ShEntity2* pEntityLifebar, int iBaseHealth)
{
	m_eState = e_state_off;
	m_aMoveAnimation = aEntity;
	m_baseHealth = iBaseHealth;

	m_pEntityLifeBar = pEntityLifebar;
}

/**
 * @brief Release
 */
void Enemy::Release(void)
{
	int nMoveAnimCount = m_aMoveAnimation.GetCount();
	for (int i = 0; i < nMoveAnimCount; ++i)
	{
		ShEntity2::Destroy(m_aMoveAnimation[i]);
	}
	m_aMoveAnimation.Empty();
}

/**
 * @brief Start
 */
void Enemy::Start(const CShVector2 & position, const CShVector2 & vDestination)
{
	m_currentHealth = m_baseHealth;
	m_vPosition = position;
	m_vStartPosition = CShVector2(m_vPosition.m_x, m_vPosition.m_y);

	ShEntity2::SetPosition2(m_aMoveAnimation[m_currentSprite], position);
	ShEntity2::SetPositionZ(m_pEntityLifeBar, ShEntity2::GetWorldPositionZ(m_aMoveAnimation[m_currentSprite]) + 0.01f);

	CShArray<Node*> aNodes;
	g_graph.FindPath(g_graph.FindNearestWayPoint(position), g_graph.FindNearestWayPoint(vDestination), aNodes);

	SetPath(aNodes);

	SetState(e_state_appear);
}

/**
 * @brief Stop
 */
void Enemy::Stop(void)
{
	SetState(e_state_disappear);
}

/**
 * @brief SetPath
 */
void Enemy::SetPath(const CShArray<Node*> & aNodes)
{
	m_aNodes.Empty();

	int iNodeCount = aNodes.GetCount();
	for (int iNode = 0; iNode < iNodeCount; iNode++)
	{
		m_aNodes.Add(aNodes[iNode]);
	}

	m_iDestinationNode = 0;
	SetTargetNode(m_aNodes[m_iDestinationNode]);
}

/**
 * @brief SetPath
 */
void Enemy::SetTargetNode(Node * pNode)
{
	m_vStartPosition = m_vPosition;
	const CShVector2 & vNodePosition = pNode->GetPosition();

	m_v = vNodePosition - m_vStartPosition;
}

/**
 * @brief SetState
 */
void Enemy::SetState(EState state)
{
	m_eState = state;
	m_fStateTime = 0.0f;

	switch (state)
	{
		case e_state_appear: 
		{
			ShEntity2::SetShow(m_aMoveAnimation[m_currentSprite], true);
			ShEntity2::SetScale(m_pEntityLifeBar, 0.4f, 0.4f, 1.0f);
		}
		break;

		case e_state_disappear : 
		{
			
		}
		break;

		case e_state_on: break;
		case e_state_off: 
		{
			ShEntity2::SetShow(m_aMoveAnimation[m_currentSprite], false); break;
		}

		default: SH_ASSERT_ALWAYS();
	}
}

/**
 * @brief GetState
 */
Enemy::EState Enemy::GetState(void)
{
	return m_eState;
}

/**
 * @brief Update
 */
void Enemy::Update(float dt)
{
	m_fStateTime += dt;

	if (e_state_appear == m_eState)
	{
		if (m_fStateTime < 1.0f)
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_currentSprite], m_fStateTime);
		}
		else
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_currentSprite], 1.0f);
			SetState(e_state_on);
		}
	}
	else if (e_state_disappear == m_eState)
	{
		if (m_fStateTime < 1.0f)
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_currentSprite], 1.0f - m_fStateTime);
		}
		else
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_currentSprite], 0.0f);
			SetState(e_state_off);
		}
	}

	if (e_state_on == m_eState)
	{	
		if (m_iDestinationNode < m_aNodes.GetCount())
		{
			m_fCompletion += dt * (50.0f / (1.0f + m_v.GetLength()));

			if (m_fCompletion < 1.0f)
			{
				m_vPosition.m_x = m_vStartPosition.m_x + m_fCompletion * m_v.m_x;
				m_vPosition.m_y = m_vStartPosition.m_y + m_fCompletion * m_v.m_y;
				ShEntity2::SetPosition2(m_aMoveAnimation[m_currentSprite], m_vPosition);
			}
			else
			{
				m_vPosition.m_x = m_vStartPosition.m_x + m_v.m_x;
				m_vPosition.m_y = m_vStartPosition.m_y + m_v.m_y;
				ShEntity2::SetPosition2(m_aMoveAnimation[m_currentSprite], m_vPosition);

				if (m_iDestinationNode < m_aNodes.GetCount() - 1)
				{
					m_iDestinationNode++;
					SetTargetNode(m_aNodes[m_iDestinationNode]);
					m_fCompletion -= 1.0f;
				}
				else
				{
					SetState(e_state_disappear);
				}
			}
		}

		// Update anim
		m_fAnimationDt += dt;
		if (m_fAnimationDt >= m_fAnimationSpeed)
		{
			// m_currentSprite++ % nb sprites
		}
	}
}

void Enemy::TakeDamages(int damages)
{
	if (m_eState == e_state_on)
	{
		m_currentHealth = shMax(0, m_currentHealth - damages);

		ShEntity2::SetScale(m_pEntityLifeBar, CShVector3(0.4f * (m_currentHealth / (float)m_baseHealth), 0.4f, 1.0f));

		if (0 >= m_currentHealth)
		{ // Dead
			Stop();
		}
	}
}

const CShVector2 & Enemy::GetPosition(void) const
{
	return m_vPosition;
}

const int & Enemy::GetBaseHealth(void) const
{
	return m_baseHealth;
}

const int & Enemy::GetCurrentHealth(void) const
{
	return m_currentHealth;
}

bool Enemy::IsDead(void)
{
	return (m_eState == e_state_disappear || m_eState == e_state_off);
}
