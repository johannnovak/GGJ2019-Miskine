#include "ShSDK/ShSDK.h"

#include "World.h"

/**
 * @brief Constructor
 */
World::World(void)
{
	// ...
}

/**
 * @brief Destructor
 */
World::~World(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void World::Initialize(void)
{
	ShUser * pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != pUser);

	m_inputManager.Initialize(pUser);
}

/**
 * @brief Release
 */
void World::Release(void)
{

}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();
}
