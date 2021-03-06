#include "Wave.h"

#include "../Enemy/Enemy.h"

/**
 * @brief Constructor
 */
Wave::Wave(void)
: m_pEnemyManager(shNULL)
, m_apRemainingActiveEnemy()
, m_vStartPosition()
, m_vDestination()
, m_iRemainingEnemy()
, m_fStartTime(0.0f)
, m_fWaveSpeed(0.0f)
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
void Wave::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager, const CShArray<CShVector2> & aStartPosition, const CShVector2 & vDestination, int iEnemyCount, float fEnemySpeed, float fApparitionTime, float fStartTime)
{
	m_fWaveSpeed = fEnemySpeed;
	m_fStartTime = fStartTime;
	m_aStartPosition = aStartPosition;
	m_vDestination = vDestination;

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
	m_vStartPosition = m_aStartPosition[rand() % m_aStartPosition.GetCount()];

	m_eState = e_state_on;
	m_apRemainingActiveEnemy.Add(m_pEnemyManager->SpawnEnemy(EnemyManager::e_enemy_01, m_vStartPosition, m_vDestination, m_fWaveSpeed));
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
 * @brief GetStartTime
 */
float Wave::GetStartTime(void)
{
	return m_fStartTime;
}

/**
 * @brief GetState
 */
Wave::EState Wave::GetState(void)
{
	return(m_eState);
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
				m_vStartPosition = m_aStartPosition[rand() % m_aStartPosition.GetCount()];
				m_apRemainingActiveEnemy.Add(m_pEnemyManager->SpawnEnemy(EnemyManager::e_enemy_01, m_vStartPosition, m_vDestination, m_fWaveSpeed));
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