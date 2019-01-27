#include "WaveManager.h"
#include "Wave.h"

#include "../../Plugin.h"
#include "../../PluginFactory.h"

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

	InitWave(aStartPosition, vEndPosition, 1, 50.0f, 1.0f, 0.0f);
	InitWave(aStartPosition, vEndPosition, 2, 50.0f, 1.0f, 3.0f);

	InitWave(aStartPosition, vEndPosition, 5, 50.0f, 1.5f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 2, 120.0f, 1.0f, 3.0f);
	
	aStartPosition.Add(CShVector2(175.0f, 288.0f));

	InitWave(aStartPosition, vEndPosition, 4, 50.0f, 0.6f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 10, 50.0f, 1.0f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 5, 120.0f, 1.0f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 2, 250.0f, 1.0f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 15, 60.0f, 0.5f, 10.0f);

	aStartPosition.Add(CShVector2(-32.0f, -90.0f));

	InitWave(aStartPosition, vEndPosition, 4, 50.0f, 1.0f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 10, 50.0f, 1.0f, 3.0f);
	InitWave(aStartPosition, vEndPosition, 20, 50.0f, 1.0f, 1.0f);
	InitWave(aStartPosition, vEndPosition, 10, 120.0f, 1.0f, 1.0f);
	InitWave(aStartPosition, vEndPosition, 15, 50.0f, 0.2f, 10.0f);
	
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
void WaveManager::InitWave(CShArray<CShVector2>aStartPosition, CShVector2 vEndPosition, int iEnemyCount, float fWaveSpeed, float fApparitionTime, float fStartTime)
{
	Wave wave;
	wave.Initialize(m_levelIdentifier, m_pEnemyManager, aStartPosition, vEndPosition, iEnemyCount, fWaveSpeed, fApparitionTime, fStartTime);
	m_aWave.Add(wave);
}

/**
 * @brief Update
 */
void WaveManager::Update(float dt)
{
	if (e_state_on == m_eState)
	{
		if (m_iCurrentWave < m_aWave.GetCount() - 1)
		{
			if (m_aWave[m_iCurrentWave].GetState() == Wave::e_state_off)
			{
				m_fTime += dt;

				float fNextWaveStartTime = m_aWave[m_iCurrentWave+1].GetStartTime();
				if (m_fTime > fNextWaveStartTime)
				{
					AddNextWave();
					m_fTime = 0.0f;
				}
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
	//AddNextWave();
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
	m_iCurrentWave++;

	//
	// Notify Plugin
	static_cast<Plugin*>(GetPlugin())->GetWorld().SetWave(m_iCurrentWave);
	SH_TRACE("WAVE %d \n", m_iCurrentWave);

	Wave & wave = m_aWave[m_iCurrentWave];
	m_apActiveWave.Add(&wave);
	wave.Start();


	
}