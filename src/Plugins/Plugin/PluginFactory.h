#pragma once

#if defined(_WIN32)
#	if defined(PluginST_Editor_EXPORTS)
#		define PLUGIN_FACTORY_EXPORT __declspec(dllexport)
#	else
#		define PLUGIN_FACTORY_EXPORT //__declspec(dllimport)
#	endif // PluginST_Editor_EXPORTS
#else // defined(_WIN32)
#	define PLUGIN_FACTORY_EXPORT
#endif

class Plugin;

extern "C"
{
	PLUGIN_FACTORY_EXPORT void					RegisterPlugin		(void);
	PLUGIN_FACTORY_EXPORT void					UnRegisterPlugin	(void);
	PLUGIN_FACTORY_EXPORT Plugin *				GetPlugin			(void);
	
	PLUGIN_FACTORY_EXPORT void					TouchDownPlugin		(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchUpPlugin		(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchMovePlugin		(int iTouch, float positionX, float positionY);
}
