#include "ShSDK/ShSDK.h"

#include "World.h"
#include "Enemy.h";

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

	CShIdentifier levelIdentifier = CShIdentifier("level_test_path");

	ShPath * pPath = ShPath::Find(levelIdentifier, CShIdentifier("path_auto_001"));

	m_pEnemy = new Enemy();
	m_pEnemy->Initialize(levelIdentifier, CShIdentifier("sprite_player_walk_01_001"), pPath);
}

/**
 * @brief Release
 */
void World::Release(void)
{
	m_pEnemy->Release();
	SH_SAFE_DELETE(m_pEnemy);

	m_inputManager.Release();
}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();
	m_pEnemy->Update(dt);

}
