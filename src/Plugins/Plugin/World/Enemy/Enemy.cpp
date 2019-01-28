#include "Enemy.h"
#include "../PathFinding/Graph.h"

#include "../World.h"
#include "../../../../Game/Game.h"
#include "../../Plugin.h"
#include "../../PluginFactory.h"

/**
 * @brief Constructor
 */
Enemy::Enemy(void)
: m_eState(e_state_off)
, m_fStateTime(0.0f)
, m_fSpeed(10.0f)
, m_fSlowEffect(1.0f)
, m_fSlowTime(5.0f)
, m_fSlowDt(0.0f)
, m_pEntityLifeBar(shNULL)
, m_vPosition(CShVector2::ZERO)
, m_vStartPosition(CShVector2::ZERO)
, m_v(CShVector2::ZERO)
, m_fCompletion(0.0f)
, m_baseHealth(DEFAULT_ENEMY_HP_DIFFICULTY_MEDIUM)
, m_currentHealth(DEFAULT_ENEMY_HP_DIFFICULTY_MEDIUM)
, m_aNodes()
, m_iDestinationNode(0)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.2f)
, m_currentSprite(0)
, m_eCurrentAnimationType(animation_top)
, m_eCurrentAnimationState(state_normal)
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
void Enemy::Initialize(const CShArray<ShEntity2*> aEntity[state_max][animation_max], ShEntity2* pEntityLifebar, int iBaseHealth)
{
	m_eState = e_state_off;
	for (int j = 0; j < state_max; ++j)
	{
		for (int i = 0; i < animation_max; ++i)
		{
			m_aMoveAnimation[j][i] = aEntity[j][i];
		}
	}

	m_baseHealth = iBaseHealth;
	m_pEntityLifeBar = pEntityLifebar;
}

/**
 * @brief Release
 */
void Enemy::Release(void)
{
	for (int k = 0; k < state_max; ++k)
	{
		for (int i = 0; i < animation_max; ++i)
		{
			int nAnimCount = m_aMoveAnimation[k][i].GetCount();
			for (int j = 0; j < nAnimCount; ++j)
			{
				ShEntity2::Destroy(m_aMoveAnimation[k][i][j]);
			}
			m_aMoveAnimation[k][i].Empty();
		}
	}
}

/**
 * @brief Start
 */
void Enemy::Start(const CShVector2 & position, const CShVector2 & vDestination, float fSpeed)
{
	m_currentHealth = m_baseHealth;
	m_vPosition = position;
	m_vStartPosition = CShVector2(m_vPosition.m_x, m_vPosition.m_y);
	m_fSpeed = fSpeed;

	ShEntity2::SetPosition2(m_aMoveAnimation[m_eCurrentAnimationType][m_eCurrentAnimationType][m_currentSprite], position);
	ShEntity2::SetPosition2(m_aMoveAnimation[0][0][0], position);
	ShEntity2::SetPositionZ(m_pEntityLifeBar, ShEntity2::GetWorldPositionZ(m_aMoveAnimation[0][0][0]) + 0.01f);

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
			ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], true);
			ShEntity2::SetScale(m_pEntityLifeBar, 0.4f, 0.4f, 1.0f);
		}
		break;

		case e_state_disappear : break;
		case e_state_on: break;

		case e_state_off: 
		{
			ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], false, false);
			ShEntity2::SetShow(m_aMoveAnimation[0][0][0], false, false);
		}
		break;

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

	if (m_eCurrentAnimationState == state_cg)
	{
		m_fSlowDt += dt;
		if (m_fSlowDt >= m_fSlowTime)
		{
			m_fSlowEffect = 1.0f;
			UpdateAnimationState(state_normal);
		}
	}

	if (e_state_appear == m_eState)
	{
		if (m_fStateTime < 1.0f)
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], m_fStateTime);
		}
		else
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], 1.0f);
			SetState(e_state_on);
		}
	}
	else if (e_state_disappear == m_eState)
	{
		if (m_fStateTime < 1.0f)
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], 1.0f - m_fStateTime);
			ShEntity2::SetAlpha(m_aMoveAnimation[0][0][0], 1.0f - m_fStateTime);
		}
		else
		{
			ShEntity2::SetAlpha(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], 0.0f);
			SetState(e_state_off);
		}
	}

	if (e_state_on == m_eState)
	{	
		if (m_iDestinationNode < m_aNodes.GetCount())
		{
			m_fCompletion += dt * ((m_fSpeed * m_fSlowEffect) / (1.0f + m_v.GetLength()));

			if (m_fCompletion < 1.0f)
			{
				m_vPosition.m_x = m_vStartPosition.m_x + m_fCompletion * m_v.m_x;
				m_vPosition.m_y = m_vStartPosition.m_y + m_fCompletion * m_v.m_y;

				EAnimationType newAnimType = m_eCurrentAnimationType;
				if (m_v.m_x >= 0 )
				{ // E
					if (m_v.m_y > 0)
					{ // N 
						newAnimType = animation_top;
					}
					else if (m_v.m_y < 0)
					{ // S
						newAnimType = animation_bottom;
					}
					else
						newAnimType = animation_right;
				}
				else
				{ // O
					if (m_v.m_y > 0)
					{ // N 
						newAnimType = animation_top;
					}
					else if (m_v.m_y < 0)
					{ // S
						newAnimType = animation_bottom;
					}
					else
						newAnimType = animation_left;
				}

				if (newAnimType != m_eCurrentAnimationType)
				{
					ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], false, false);

					m_eCurrentAnimationType = newAnimType;
					m_currentSprite = 0;
				}

				ShEntity2::SetPosition2(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], m_vPosition);
				ShEntity2::SetPosition2(m_aMoveAnimation[0][0][0], m_vPosition);
				ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], true);
			}
			else
			{
				m_vPosition.m_x = m_vStartPosition.m_x + m_v.m_x;
				m_vPosition.m_y = m_vStartPosition.m_y + m_v.m_y;
				
				ShEntity2::SetPosition2(m_aMoveAnimation[0][0][0], m_vPosition);
				ShEntity2::SetPosition2(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], m_vPosition);

				if (m_iDestinationNode < m_aNodes.GetCount() - 1)
				{
					m_iDestinationNode++;
					SetTargetNode(m_aNodes[m_iDestinationNode]);
					m_fCompletion -= 1.0f;
				}
				else
				{
					//
					// Destionation complete !
					SetState(e_state_disappear);

					//
					// Notify Plugin
					static_cast<Plugin*>(GetPlugin())->GetWorld().LooseHP();
				}
			}
		}

		// Update anim
		m_fAnimationDt += dt;
		if (m_fAnimationDt >= m_fAnimationSpeed)
		{
			ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], false, false);

			int nSprite = m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType].GetCount();
			m_currentSprite++;
			m_currentSprite %= nSprite;

			ShEntity2::SetPosition2(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], m_vPosition);
			ShEntity2::SetPosition2(m_aMoveAnimation[0][0][0], m_vPosition);
			ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], true);

			m_fAnimationDt = 0.0f;
		}
	}
}

/**
 * @brief Update
 */
void Enemy::TakeDamages(int damages)
{
	if (m_eState == e_state_on)
	{
		m_currentHealth = shMax(0, m_currentHealth - damages);

		ShEntity2::SetScale(m_pEntityLifeBar, CShVector3(0.4f * (m_currentHealth / (float)m_baseHealth), 0.4f, 1.0f));

		if (0 >= m_currentHealth)
		{ 
			//
			// Dead
			Stop();
	
			//
			// Notify Plugin
			static_cast<Plugin*>(GetPlugin())->GetWorld().GainMoney(DEFAULT_ENEMY_MONEY_GAIN_DIFFICULTY_MEDIUM);
		}
	}
}


/**
 * @brief TakeSlowEffect
 */
void Enemy::TakeSlowEffect(float ratio)
{
	m_fSlowEffect = ratio;
	m_fSlowDt = 0.0f;
	UpdateAnimationState(state_cg);
}

/**
 * @brief GetPosition
 */
const CShVector2 & Enemy::GetPosition(void) const
{
	return m_vPosition;
}

/**
 * @brief GetBaseHealth
 */
const int & Enemy::GetBaseHealth(void) const
{
	return m_baseHealth;
}

/**
 * @brief GetCurrentHealth
 */
const int & Enemy::GetCurrentHealth(void) const
{
	return m_currentHealth;
}

/**
 * @brief IsDead
 */
bool Enemy::IsDead(void)
{
	return (m_eState == e_state_disappear || m_eState == e_state_off);
}

/**
 * @brief UpdateAnimationState
 */
void Enemy::UpdateAnimationState(EAnimationState newState)
{
	if (newState == m_eCurrentAnimationState)
		return;

	ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], false, false);
	m_eCurrentAnimationState = newState;
	ShEntity2::SetPosition2(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], m_vPosition);
	ShEntity2::SetShow(m_aMoveAnimation[m_eCurrentAnimationState][m_eCurrentAnimationType][m_currentSprite], true);
}
