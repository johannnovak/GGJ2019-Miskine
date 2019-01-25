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

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void WayPoint::GetNeighbor(CShArray<WayPoint*> & aWP)
{
	if (m_aNeighbor[e_direction_up] != shNULL)
	{
		aWP.Add(m_aNeighbor[e_direction_up]);
	}

	if (m_aNeighbor[e_direction_left] != shNULL)
	{
		aWP.Add(m_aNeighbor[e_direction_left]);
	}

	if (m_aNeighbor[e_direction_right] != shNULL)
	{
		aWP.Add(m_aNeighbor[e_direction_right]);
	}

	if (m_aNeighbor[e_direction_down] != shNULL)
	{
		aWP.Add(m_aNeighbor[e_direction_down]);
	}
}