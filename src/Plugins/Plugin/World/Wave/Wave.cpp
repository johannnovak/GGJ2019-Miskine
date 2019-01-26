#include "Wave.h"

/**
 * @brief Constructor
 */
Wave::Wave(void)
: m_enemyManager()
, m_iRemainingEnemy()
, m_eState(e_state_off)
, m_fApparitionTime(0.0f)
, m_fTime(0.0f)
{
	// ...
}

/**
 * @brief Destructor
 */
Wave::~Wave(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void Wave::Initialize(int iEnemyCount, float fApparitionTime)
{
	m_iRemainingEnemy = iEnemyCount;
	m_fApparitionTime = fApparitionTime;
}

/**
 * @brief Release
 */
void Wave::Release(void)
{

}

/**
 * @brief Start
 */
void Wave::Start(void)
{
	m_eState = e_state_on;
}

/**
 * @brief Stop
 */
void Wave::Stop(void)
{
	m_eState = e_state_off;
}

/**
 * @brief Update
 */
void Wave::Update(float dt)
{
	if (e_state_on == m_eState)
	{
		m_fTime += dt;

		if (m_fTime > m_fApparitionTime)
		{
			m_enemyManager.SpawnEnemy(EnemyManager::e_enemy_01, CShVector3(0.0f, 0.0f, 1.0f));
			m_fTime = m_fTime - m_fApparitionTime;
		}

		m_enemyManager.Update(dt);
	}
}