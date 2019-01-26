#include "Inputs.h"

#include <ShSDK/ShSDK.h>

#include "Game.h"

/**
 * @brief OnTouchDown
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchDown(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::GetInstance();
		game.touchBegin(pos);
	}
}

/**
 * @brief OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchUp(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::GetInstance();
		game.touchEnd(pos);
	}
}

/**
 * @brief OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchMove(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::GetInstance();
		game.touchMove(pos);
	}
}

