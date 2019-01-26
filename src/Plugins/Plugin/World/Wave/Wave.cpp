#include "Wave.h"

#include "../Enemy/Enemy.h"

/**
 * @brief Constructor
 */
Wave::Wave(void)
: m_pEnemyManager(shNULL)
, m_apRemainingActiveEnemy()
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
void Wave::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, int iEnemyCount, float fApparitionTime)
{
	m_iRemainingEnemy = iEnemyCount;
	m_fApparitionTime = fApparitionTime;

	m_pEnemyManager = pEnemyManager;
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
	m_apRemainingActiveEnemy.Add(m_pEnemyManager->SpawnEnemy(EnemyManager::e_enemy_01, CShVector3(0.0f, 0.0f, 1.0f)));
	m_iRemainingEnemy--;
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

		if (m_iRemainingEnemy > 0)
		{
			if (m_fTime > m_fApparitionTime)
			{
				m_apRemainingActiveEnemy.Add(m_pEnemyManager->SpawnEnemy(EnemyManager::e_enemy_01, CShVector3(0.0f, 0.0f, 1.0f)));
				m_iRemainingEnemy--;
				m_fTime = m_fTime - m_fApparitionTime;
			}
		}

		CShArray<Enemy*> apEnemyToRemove;

		int iEnemyCount = m_apRemainingActiveEnemy.GetCount();
		for (int iEnemy = 0; iEnemy < iEnemyCount; ++iEnemy)
		{
			Enemy * pEnemy = m_apRemainingActiveEnemy[iEnemy];
			if (Enemy::e_state_off == pEnemy->GetState())
			{
				apEnemyToRemove.Add(pEnemy);
			}
		}

		iEnemyCount = apEnemyToRemove.GetCount();
		for (int iEnemy = 0; iEnemy < iEnemyCount; ++iEnemy)
		{
			m_apRemainingActiveEnemy.RemoveAll(apEnemyToRemove[iEnemy]);
		}

		if (m_apRemainingActiveEnemy.IsEmpty())
		{
			Stop();
		}
	}
}