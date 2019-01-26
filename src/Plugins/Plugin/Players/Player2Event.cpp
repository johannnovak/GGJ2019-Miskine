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
EPlayer2EventDifficulty Player2Event::GetDifficulty(void)
{
	return m_eDifficulty;
}

/**
 * @brief Player2Event::Constructor
 */
/*explicit*/ Player2Event::Player2Event(EPlayer2EventType eType)
: m_eDifficulty(e_player2_event_difficulty_low)
, m_bFinished(false)
{
	// ...
}

/**
 * @brief Player2Event::Constructor
 */
/*explicit*/ Player2Event::Player2Event(EPlayer2EventType eType, EPlayer2EventDifficulty eDifficulty)
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