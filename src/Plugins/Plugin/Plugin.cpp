#include "Plugin.h"

const CShIdentifier plugin_identifier("PluginGGJ2019");

/**
 * @brief Constructor
 */
Plugin::Plugin(void)
: CShPlugin(plugin_identifier)
, m_world()
, m_player2EventManager()
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
	m_world.Initialize(levelIdentifier);

	m_player2EventManager.Initialize();
}

/**
 * @brief OnPlayStop
 */
/*virtual*/ void Plugin::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_world.Release();

	m_player2EventManager.Release();
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
	m_player2EventManager.Update(dt);
}

/**
 * @brief OnTouchDown
 */
void Plugin::OnTouchDown(int iTouch, float positionX, float positionY)
{
	m_world.CreateTower(CShVector2(positionX, positionY));
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

/**
 * @brief GetPlayer2EventManager
 */
const Player2EventManager & Plugin::GetPlayer2EventManager(void)
{
	return m_player2EventManager;
}

/**
 * @brief GetDistanceSquared
 */
float Plugin::GetDistanceSquared(const CShVector2 & start, const CShVector2 & dest)
{
	//TODO Test me

	CShVector2 A(dest);
	CShVector2 B(start);
	CShVector2 delta = A - B;

	return delta.DotProduct(delta);
}
