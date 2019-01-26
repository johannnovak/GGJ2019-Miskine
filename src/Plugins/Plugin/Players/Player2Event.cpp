#include "ShSDK/ShSDK.h"

#include "Player2EventManager.h"

/**
 * @brief Player2Event::IsFinished
 */
bool Player2Event::IsFinished(void)
{
	return m_bFinished;
}

/**
 * @brief Player2Event::GetDifficulty
 */
void Player2Event::Reset(int iStreak)
{
	ResetInternal();

	m_bFinished		= false;
	m_iErrorNb		= 0;
	m_eDifficulty	= static_cast<EPlayer2EventDifficulty>(shMin(iStreak % 3, static_cast<int>(e_player2_event_difficulty_hardcore)));
}

/**
 * @brief Player2Event::GetDifficulty
 */
EPlayer2EventDifficulty Player2Event::GetDifficulty(void)
{
	return m_eDifficulty;
}

/**
 * @brief Player2Event::GetErrorNb
 */
int Player2Event::GetErrorNb(void)
{
	return m_iErrorNb;
}

/**
 * @brief Player2Event::Constructor
 */
/*explicit*/ Player2Event::Player2Event(void)
: m_eDifficulty(e_player2_event_difficulty_medium)
, m_bFinished(false)
, m_iErrorNb(0)
{
	// ...
}

/**
 * @brief Player2Event::Constructor
 */
/*explicit*/ Player2Event::Player2Event(EPlayer2EventDifficulty eDifficulty)
: m_eDifficulty(eDifficulty)
, m_bFinished(false)
{
	// ...
}

/**
 * @brief Player2Event::Destructor
 */
/*virtual*/ Player2Event::~Player2Event(void)
{
	// ...
}
