#include "ShSDK/ShSDK.h"
#include "Node.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ Node::Node(const CShVector2 & vPosition)
: m_bAccessible(true)
, m_vPosition(0.0f,0.0f)
, m_f(0.0f)
, m_g(0.0f)
, m_h(0.0f)
, m_pWPCameFrom(shNULL)
{
	m_vPosition = vPosition;

#if DEBUG_PATHFINDING
	m_pEntity = ShEntity2::Create(CShIdentifier("level_test_pathfinding2"), GID(NULL), CShIdentifier("layer_default"), CShIdentifier("game"), CShIdentifier("white_square"), CShVector3(m_vPosition, 10.0f), CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f));
#endif //DEBUG_PATHFINDING

	for (int i = 0; i < e_direction_max; ++i)
	{
		m_aNeighbor[i] = shNULL;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ Node::~Node(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
const CShVector2 & Node::GetPosition(void) const
{
	return(m_vPosition);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Node::SetNeighbour(EDirection direction, Node * pWP)
{
	m_aNeighbor[direction] = pWP;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
Node * Node::GetNeighbour(EDirection direction)
{
	return(m_aNeighbor[direction]);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Node::GetNeighbor(CShArray<Node*> & aWP)
{
	for (int i = 0; i < e_direction_max; i++)
	{
		if (m_aNeighbor[i] != shNULL)
		{
			aWP.Add(m_aNeighbor[i]);
		}
	}
}

#if DEBUG_PATHFINDING
void Node::SetColor(const CShRGBAf & color)
{
	ShEntity2::SetColor(m_pEntity, color);
}
#endif //DEBUG_PATHFINDING

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Node::Enable(void)
{
	if (!m_bAccessible)
	{
		m_bAccessible = true;
		ShEntity2::SetShow(m_pEntity, true);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Node::Disable(void)
{
	if (m_bAccessible)
	{
		m_bAccessible = false;
		ShEntity2::SetShow(m_pEntity, false);
	}
}
