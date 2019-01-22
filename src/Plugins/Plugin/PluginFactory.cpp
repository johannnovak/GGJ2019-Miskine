#include "PluginFactory.h"

#include "Plugin.h"

static Plugin * g_pInstance = shNULL;

extern "C"
{

/**
 * @brief RegisterPlugin
 */
PLUGIN_FACTORY_EXPORT void RegisterPlugin(void)
{
	if (!g_pInstance)
	{
		g_pInstance = new Plugin();
	}

	ShApplication::RegisterPlugin(g_pInstance);
}

/**
 * @brief UnRegisterPlugin
 */
PLUGIN_FACTORY_EXPORT void UnRegisterPlugin(void)
{
	ShApplication::UnRegisterPlugin(g_pInstance);
}

/**
 * @brief GetPlugin
 * @return
 */
PLUGIN_FACTORY_EXPORT Plugin * GetPlugin(void)
{
	return(g_pInstance);
}

/**
* @brief TouchDownPlugin
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchDownPlugin(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchDown(iTouch, positionX, positionY);
}

/**
* @brief TouchUpPlugin
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchUpPlugin(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchUp(iTouch, positionX, positionY);
}

/**
* @brief TouchMovePlugin
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchMovePlugin(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchMove(iTouch, positionX, positionY);
}

}
