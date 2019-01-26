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
, m_vPosition(CShVector3::ZERO)
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
void Enemy::Initialize(const CShArray<ShEntity2*> aEntity, int iBaseHealth)
{
	m_eState = e_state_off;
	m_aMoveAnimation = aEntity;
	m_baseHealth = iBaseHealth;
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
void Enemy::Start(const CShVector3 & position, const CShVector2 & vDestination)
{
	m_currentHealth = m_baseHealth;
	m_vPosition = position;
	m_vStartPosition = CShVector2(m_vPosition.m_x, m_vPosition.m_y);
	ShEntity2::SetPosition(m_aMoveAnimation[m_currentSprite], position);

	CShArray<Node*> aNodes;
	g_graph.FindPath(g_graph.FindNearestWayPoint(CShVector2(position.m_x, position.m_y)), g_graph.FindNearestWayPoint(vDestination), aNodes);

	SetPath(aNodes);
	SetTargetNode(aNodes[m_iDestinationNode]);

	SetState(e_state_on);
}

/**
 * @brief Stop
 */
void Enemy::Stop(void)
{
	SetState(e_state_off);
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
}

/**
 * @brief SetPath
 */
void Enemy::SetTargetNode(Node * pNode)
{
	m_vStartPosition = CShVector2(m_vPosition.m_x, m_vPosition.m_y);
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
		case e_state_on: ShEntity2::SetShow(m_aMoveAnimation[m_currentSprite], true); break;

		case e_state_off: ShEntity2::SetShow(m_aMoveAnimation[m_currentSprite], false); break;

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

	if (e_state_on == m_eState)
	{	
		if (m_iDestinationNode < m_aNodes.GetCount() - 1)
		{
			m_fCompletion += dt;

			if (m_fCompletion < 1.0f)
			{
				m_vPosition.m_x = m_vStartPosition.m_x + m_fCompletion * m_v.m_x;
				m_vPosition.m_y = m_vStartPosition.m_y + m_fCompletion * m_v.m_y;
				ShEntity2::SetPosition(m_aMoveAnimation[m_currentSprite], m_vPosition);
			}
			else
			{
				m_vPosition.m_x = m_vStartPosition.m_x + m_v.m_x;
				m_vPosition.m_y = m_vStartPosition.m_y + m_v.m_y;
				ShEntity2::SetPosition(m_aMoveAnimation[m_currentSprite], m_vPosition);

				m_iDestinationNode++;
				SetTargetNode(m_aNodes[m_iDestinationNode]);
				m_fCompletion -= 1.0f;
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
	SH_TRACE("take damage %d, %d\n", m_currentHealth, damages);
	m_currentHealth -= damages;
	if (0 > m_currentHealth)
	{ // Dead
		Stop();
	}
}

const CShVector3 & Enemy::GetPosition(void) const
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
	return m_eState == e_state_off;
}
