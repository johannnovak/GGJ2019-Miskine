#include "Application.h"
#include "Game.h"

#include <ShSDK/ShSDK.h>

#include "PluginFactory.h"
#include "Plugin.h"

extern "C"
{

/**
 * @brief OnPreInitialize
 */
void OnPreInitialize(void)
{
	ShInput::AddOnTouchDown(OnTouchDown);
	ShInput::AddOnTouchUp(OnTouchUp);
	ShInput::AddOnTouchMove(OnTouchMove);

	ShUser::RegisterLoginCallback(OnLogin);
	ShUser::RegisterLogoutCallback(OnLogout);
}

/**
 * @brief OnPostInitialize
 */
void OnPostInitialize(void)
{
	RegisterPlugin();

	Game & game = Game::GetInstance();
	game.Initialize();
}

/**
 * @brief OnPreUpdate
 * @param dt
 */
void OnPreUpdate(float dt)
{
	Game & game = Game::GetInstance();
	game.Update(dt);
}

/**
 * @brief OnPostUpdate
 * @param dt
 */
void OnPostUpdate(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief OnPreRelease
 */
void OnPreRelease(void)
{
	Game & game = Game::GetInstance();
	game.Release();

	UnRegisterPlugin();
}

/**
 * @brief OnPostRelease
 */
void OnPostRelease(void)
{
}

/**
 * @brief OnActivate
 */
void OnActivate(void)
{
	// ...
}

/**
 * @brief OnDeactivate
 * @param bAllowBackgroundUpdates
 * @param bAllowBackgroundInputs
 */
void OnDeactivate(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs)
{
	bAllowBackgroundUpdates = false;
	bAllowBackgroundInputs = false;
}

/**
* @brief OnLogin
* @param pUser
*/
void OnLogin(ShUser * pUser)
{
	//Game::instance().login(pUser);
}

/**
* @brief OnLogout
* @param pUser
*/
void OnLogout(ShUser * pUser)
{
	//Game::instance().logout(pUser);
}

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
		//Game & game = Game::instance();
		//game.touchBegin(pos);

		GetPlugin()->OnTouchDown(iTouch, positionX, positionY);
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
		//Game & game = Game::instance();
		//game.touchEnd(pos);

		GetPlugin()->OnTouchUp(iTouch, positionX, positionY);
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
		//Game & game = Game::instance();
		//game.touchMove(pos);

		GetPlugin()->OnTouchMove(iTouch, positionX, positionY);
	}
}

}
