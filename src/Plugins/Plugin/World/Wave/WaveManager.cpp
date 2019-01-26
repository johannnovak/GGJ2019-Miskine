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
, m_eState(e_state_off)
, m_fTimeBetweenWave(TIME_BETWEEN_WAVE)
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
void WaveManager::Initialize(void)
{
	for (int i = 0; i < WAVE_MAX; i++)
	{
		Wave wave;
		wave.Initialize(10, 1.0f);
		m_aWave.Add(wave);
	}

	m_iCurrentWave = 0;
}

/**
 * @brief Release
 */
void WaveManager::Release(void)
{
	for (int i = 0; i < WAVE_MAX; i++)
	{
		Wave & wave = m_aWave[i];
		wave.Release();
	}
}

/**
 * @brief Update
 */
void WaveManager::Update(float dt)
{
	if (e_state_on == m_eState)
	{
		m_fTime += dt;

		if (m_iCurrentWave < WAVE_MAX - 1)
		{
			if (m_fTime > m_fTimeBetweenWave)
			{
				AddWave();
				m_fTime = m_fTime - m_fTimeBetweenWave;
			}
		}

		int iActiveWaveCount = m_apActiveWave.GetCount();
		for (int iWave = 0; iWave < iActiveWaveCount; iWave++)
		{
			Wave * pWave = m_apActiveWave[iWave];
			pWave->Update(dt);
		}
	}
}

/**
 * @brief Start
 */
void WaveManager::Start(void)
{
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
void WaveManager::AddWave(void)
{
	Wave & wave = m_aWave[m_iCurrentWave];
	m_apActiveWave.Add(&wave);
	m_iCurrentWave++;
}