#pragma once

/**
 * @brief Game::get
 * @param state
 * @return
 */
inline GameState * Game::get(EState state)
{
	switch (state)
	{
		case MAIN_MENU:
		{
			return(&m_stateMainMenu);
		}
		break;

		case INGAME:
		{
			return(&m_stateGame);
		}
		break;

		default:
		{
			//SH_ASSERT_ALWAYS();
			return((GameState*)0); // this should never happen
		}
	}
}

