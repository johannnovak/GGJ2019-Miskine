#include "Enemy.h"

/**
 * @brief Constructor
 */
Enemy::Enemy(void)
: m_eState(e_state_off)
, m_fStateTime(0.0f)
, m_pEntity(shNULL)
, m_pEntityLifeBar(shNULL)
, m_vPosition(CShVector3::ZERO)
, m_baseHealth(0)
, m_currentHealth(0)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.0f)
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
void Enemy::Initialize(ShEntity2* pEntity, int iBaseHealth)
{
	m_eState = e_state_off;
	m_pEntity = pEntity;
	m_baseHealth = iBaseHealth;
}

/**
 * @brief Release
 */
void Enemy::Release(void)
{
	m_aMoveAnimation.Empty();
}

/**
 * @brief Start
 */
void Enemy::Start(const CShVector3 & position)
{
	m_currentHealth = m_baseHealth;
	m_vPosition = position;

	ShEntity2::SetPosition(m_pEntity, position);

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
 * @brief SetState
 */
void Enemy::SetState(EState state)
{
	m_eState = state;
	m_fStateTime = 0.0f;

	switch (state)
	{
		case e_state_on: ShEntity2::SetShow(m_pEntity, true); break;

		case e_state_off: ShEntity2::SetShow(m_pEntity, false); break;

		default: SH_ASSERT_ALWAYS();
	}
}

/**
 * @brief Update
 */
void Enemy::Update(float dt)
{
	m_fStateTime += dt;

	if (e_state_on == m_eState)
	{
		// Test move
		m_vPosition.m_x += 20.0f * dt;
		ShEntity2::SetPosition(m_pEntity, m_vPosition);

		// Update anim
		m_fAnimationDt += dt;
		if (m_fAnimationDt >= m_fAnimationSpeed)
		{

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
