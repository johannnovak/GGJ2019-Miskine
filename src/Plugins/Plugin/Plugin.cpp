#include "Plugin.h"

const CShIdentifier plugin_identifier("PluginGGJ2019");

/**
* @brief Constructor
*/
Plugin::Plugin(void)
: CShPlugin(plugin_identifier)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ Plugin::~Plugin(void)
{
	// ...
}

/**
* @brief OnPlayStart
*/
/*virtual*/ void Plugin::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	m_world.Initialize();
}

/**
* @brief OnPlayStop
*/
/*virtual*/ void Plugin::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_world.Release();
}

/**
* @brief OnPlayPause
*/
/*virtual*/ void Plugin::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayResume
*/
/*virtual*/ void Plugin::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPreUpdate
*/
/*virtual*/ void Plugin::OnPreUpdate(float dt)
{
	// ...
}

/**
* @brief OnPostUpdate
*/
/*virtual*/ void Plugin::OnPostUpdate(float dt)
{
	m_world.Update(dt);
}

/**
* @brief OnTouchDown
*/
void Plugin::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief OnTouchUp
*/
void Plugin::OnTouchUp(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief OnTouchMove
*/
void Plugin::OnTouchMove(int iTouch, float positionX, float positionY)
{
	// ...
}

float Plugin::GetDistanceSquared(const CShVector3 & start, const CShVector3 & dest)
{
	//TODO Test me

	CShVector2 A(dest.m_x, dest.m_y);
	CShVector2 B(start.m_x, start.m_y);
	CShVector2 delta = A - B;

	return delta.DotProduct(delta);
}
