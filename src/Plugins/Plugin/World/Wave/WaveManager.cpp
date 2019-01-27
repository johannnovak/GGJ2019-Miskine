#include "WaveManager.h"
#include "Wave.h"

#include "../../Plugin.h"

/**
 * @brief Constructor
 */
WaveManager::WaveManager(void)
: m_aWave()
, m_apActiveWave()
, m_iCurrentWave(0)
, m_levelIdentifier()
, m_pEnemyManager(shNULL)
, m_eState(e_state_off)
, m_fTime(0.0f)
{
	// ...
}

/**
 * @brief Destructor
 */
WaveManager::~WaveManager(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void WaveManager::Initialize(const CShIdentifier & levelIdentifier, EnemyManager * pEnemyManager)
{
	m_pEnemyManager = pEnemyManager;
	m_levelIdentifier = levelIdentifier;

	CShArray<CShVector2> aStartPosition;
	aStartPosition.Add(CShVector2(-325.0f, 268.0f));

	CShVector2 vEndPosition(196.0f, -305.0f);

	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 0.0f);
	InitWave(aStartPosition, vEndPosition, 2, 1.0f, 7.0f);

	InitWave(aStartPosition, vEndPosition, 5, 1.5f, 20.0f);
	InitWave(aStartPosition, vEndPosition, 2, 0.7f, 35.0f);
	
	aStartPosition.Add(CShVector2(175.0f, 288.0f));

	InitWave(aStartPosition, vEndPosition, 1, 0.5f, 35.0f);
	InitWave(aStartPosition, vEndPosition, 5, 1.0f, 45.0f);
	InitWave(aStartPosition, vEndPosition, 10, 1.0f, 50.0f);
	InitWave(aStartPosition, vEndPosition, 4, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);

	aStartPosition.Add(CShVector2(-32.0f, -90.0f));

	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);

	aStartPosition.Add(CShVector2(-292.0f, -14.0f));

	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	InitWave(aStartPosition, vEndPosition, 1, 1.0f, 500.0f);
	
	m_iCurrentWave = 0;
}

/**
 * @brief Release
 */
void WaveManager::Release(void)
{
	for (int i = 0; i < m_aWave.GetCount(); i++)
	{
		Wave & wave = m_aWave[i];
		wave.Release();
	}
}

/**
 * @brief InitWave
 */
void WaveManager::InitWave(CShArray<CShVector2>aStartPosition, CShVector2 vEndPosition, int iEnemyCount, float fApparitionTime, float fStartTime)
{
	Wave wave;
	wave.Initialize(m_levelIdentifier, m_pEnemyManager, aStartPosition, vEndPosition, iEnemyCount, fApparitionTime, fStartTime);
	m_aWave.Add(wave);
}

/**
 * @brief Update
 */
void WaveManager::Update(float dt)
{
	if (e_state_on == m_eState)
	{
		m_fTime += dt;

		if (m_iCurrentWave < m_aWave.GetCount() - 1)
		{
			float fNextWaveStartTime = m_aWave[m_iCurrentWave].GetStartTime();
			if (m_fTime > fNextWaveStartTime)
			{
				AddNextWave();
				//m_fTime = m_fTime - fNextWaveStartTime;
			}
		}

		CShArray<Wave*> apWaveToRemove;

		int iActiveWaveCount = m_apActiveWave.GetCount();
		for (int iWave = 0; iWave < iActiveWaveCount; iWave++)
		{
			Wave * pWave = m_apActiveWave[iWave];
			pWave->Update(dt);

			if (pWave->GetState() == Wave::e_state_off)
			{
				apWaveToRemove.Add(pWave);
			}
		}

		for (int iWave = 0; iWave < apWaveToRemove.GetCount(); ++iWave)
		{
			m_apActiveWave.RemoveAll(apWaveToRemove[iWave]);
		}
	}
}

/**
 * @brief Start
 */
void WaveManager::Start(void)
{
	AddNextWave();
	m_eState = e_state_on;
	m_fTime = 0.0f;
}

/**
 * @brief Stop
 */
void WaveManager::Stop(void)
{
	m_eState = e_state_off;
}

/**
 * @brief AddWave
 */
void WaveManager::AddNextWave(void)
{
	SH_TRACE("WAVE %d \n", m_iCurrentWave + 1);

	Wave & wave = m_aWave[m_iCurrentWave];
	m_apActiveWave.Add(&wave);
	wave.Start();
	m_iCurrentWave++;
}