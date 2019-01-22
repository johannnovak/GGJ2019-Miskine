#include "Extension.h"

#include "ShSDK/ShSDK.h"

//
// Include plugins
#include "../Plugins/Plugin/Plugin.h"

typedef void(*register_fn)(void);
typedef void(*unregister_fn)(void);
typedef Plugin * (*get_instance_fn)(void);

static register_fn pRegister = shNULL;
static unregister_fn pUnRegister = shNULL;
static get_instance_fn pGetInstance = shNULL;

static FuncOnTouchDownPtr pOnTouchDown = shNULL;
static FuncOnTouchUpPtr pOnTouchUp = shNULL;
static FuncOnTouchMovePtr pOnTouchMove = shNULL;

#ifdef PLUGIN_PATH
static const CShString strPluginFilePath(PLUGIN_PATH);
#else
#	error "Plugin path not defined"
#endif

static CShDynamicLibrary plugin_library(strPluginFilePath);

extern "C"
{

EXTENSION_EXPORT void ExtensionInitialize(void)
{
	//
	// Load Library
	bool bInit = plugin_library.Initialize();

	//
	// Get Functions
	if (bInit)
	{
		pRegister = (register_fn)plugin_library.GetFunctionAddress(CShString("RegisterPlugin"));
		SH_ASSERT(shNULL != pRegister);

		pUnRegister = (register_fn)plugin_library.GetFunctionAddress(CShString("UnRegisterPlugin"));
		SH_ASSERT(shNULL != pUnRegister);

		pGetInstance = (get_instance_fn)plugin_library.GetFunctionAddress(CShString("GetPlugin"));
		SH_ASSERT(shNULL != pGetInstance);
	}

	//
	// Call factory (auto-register)
	if (shNULL != pRegister)
	{
		pRegister();
	}
}

EXTENSION_EXPORT void ExtensionRelease(void)
{
	//
	// Call factory (auto-unregister)
	if (shNULL != pUnRegister)
	{
		pUnRegister();
	}

	//
	// Reset function pointers
	{
		pGetInstance = shNULL;
		pUnRegister = shNULL;
		pRegister = shNULL;
	}

	//
	// Unload Library
	plugin_library.Release();
}

EXTENSION_EXPORT void ExtensionOnPluginStarted(const CShIdentifier & levelIdentifier)
{
	if (shNULL != pRegister)
	{
		pOnTouchDown = (FuncOnTouchDownPtr)plugin_library.GetFunctionAddress(CShString("TouchDownPlugin"));
		SH_ASSERT(shNULL != pOnTouchDown);

		pOnTouchUp = (FuncOnTouchUpPtr)plugin_library.GetFunctionAddress(CShString("TouchUpPlugin"));
		SH_ASSERT(shNULL != pOnTouchUp);

		pOnTouchMove = (FuncOnTouchMovePtr)plugin_library.GetFunctionAddress(CShString("TouchMovePlugin"));
		SH_ASSERT(shNULL != pOnTouchMove)

		ShInput::AddOnTouchDown(pOnTouchDown);
		ShInput::AddOnTouchUp(pOnTouchUp);
		ShInput::AddOnTouchMove(pOnTouchMove);
	}
}

EXTENSION_EXPORT void ExtensionOnPluginStopped(const CShIdentifier & levelIdentifier)
{
	if (shNULL != pRegister)
	{
		ShInput::RemoveOnTouchDown(pOnTouchDown);
		ShInput::RemoveOnTouchUp(pOnTouchUp);
		ShInput::RemoveOnTouchMove(pOnTouchMove);

		pOnTouchDown = shNULL;
		pOnTouchUp = shNULL;
		pOnTouchMove = shNULL;
	}
}

}
