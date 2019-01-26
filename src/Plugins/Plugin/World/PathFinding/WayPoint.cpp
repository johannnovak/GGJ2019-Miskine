#include "ShSDK/ShSDK.h"
#include "WayPoint.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ WayPoint::WayPoint(const CShVector2 & vPosition)
: m_vPosition(0.0f,0.0f)
, m_f(0.0f)
, m_g(0.0f)
, m_h(0.0f)
, m_pWPCameFrom(shNULL)
{
	m_vPosition = vPosition;

#if DEBUG_PATHFINDING
	m_pEntity = ShEntity2::Create(CShIdentifier("level_test_pathfinding"), GID(NULL), CShIdentifier("layer_default"), CShIdentifier("game"), CShIdentifier("white_square"), vWPPosition, CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f));
#endif //DEBUG_PATHFINDING

	for (int i = 0; i < e_direction_max; ++i)
	{
		m_aNeighbor[i] = shNULL;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ WayPoint::~WayPoint(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
const CShVector2 & WayPoint::GetPosition(void) const
{
	return(m_vPosition);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void WayPoint::SetNeighbour(EDirection direction, WayPoint* pWP)
{
	m_aNeighbor[direction] = pWP;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
WayPoint* WayPoint::GetNeighbour(EDirection direction)
{
	return(m_aNeighbor[direction]);
}

#if DEBUG_PATHFINDING
void WayPoint::SetColor(const CShRGBAf & color)
{
	ShEntity2::SetColor(m_pEntity, color);
}
#endif //DEBUG_PATHFINDING

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void WayPoint::GetNeighbor(CShArray<WayPoint*> & aWP)
{
	for (int i = 0; i < e_direction_max; i++)
	{
		if (m_aNeighbor[i] != shNULL)
		{
			aWP.Add(m_aNeighbor[i]);
		}
	}
}