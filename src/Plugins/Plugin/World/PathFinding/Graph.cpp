#include "ShSDK/ShSDK.h"
#include "Graph.h"
#include "Node.h"

Graph g_graph;

#define WP_SPACE_WIDTH 10.0f
#define WP_SPACE_HEIGHT 10.0f

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ Graph::Graph(void)
: m_aWayPoint()
, m_openSet()
, m_closedSet()
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ Graph::~Graph(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Graph::Initialize(ShDummyAABB2 * pDummyAABB2)
{
	CShVector2 vPosition = ShDummyAABB2::GetWorldPosition2(pDummyAABB2);
	float fWidth = ShDummyAABB2::GetAABB(pDummyAABB2).GetWidth();
	float fHeight = ShDummyAABB2::GetAABB(pDummyAABB2).GetHeight();

	CShArray<ShObject*> aChildren;
	ShDummyAABB2::GetChildArray(pDummyAABB2, aChildren);

	int iCols = (fWidth / WP_SPACE_WIDTH);
	int iRows = (fHeight / WP_SPACE_HEIGHT);

	m_aWayPoint.SetCount(iCols * iRows);

	CShVector2 vStartPosition(ShDummyAABB2::GetAABB(pDummyAABB2).GetMin());

	for (int i = 0; i < (iCols * iRows); ++i)
	{
		int iRow = i / iCols;
		int iCol = i % iCols;

		const CShVector2 vWPPosition = CShVector2(vStartPosition) + CShVector2(iCol * (fWidth / iCols), iRow * (fHeight / iRows));

		bool bObstacle = false;

		const int ChildCount = aChildren.GetCount();

		for (int i = 0; i < ChildCount; ++i)
		{
			if (ShDummyAABB2 * pDummyAABB = ShObject::Cast<ShDummyAABB2>(aChildren[i]))
			{
				const CShAABB2 & AABB = ShDummyAABB2::GetAABB(pDummyAABB);
				CShVector2 vChildPosition = ShDummyAABB2::GetWorldPosition2(pDummyAABB);

				const CShVector2 Min = vChildPosition + AABB.GetMin();
				const CShVector2 Max = vChildPosition + AABB.GetMax();

				if (vWPPosition.m_x > shMin(Min.m_x, Max.m_x) && vWPPosition.m_y > shMin(Min.m_y, Max.m_y) && vWPPosition.m_x < shMax(Min.m_x, Max.m_x) && vWPPosition.m_y < shMax(Min.m_y, Max.m_y))
				{
					bObstacle = true;
					break;
				}
			}
			else if (ShDummyCircle * pDummyCircle = ShObject::Cast<ShDummyCircle>(aChildren[i]))
			{
				const CShCircle & Circle = ShDummyCircle::GetCircle(pDummyCircle);
			}
		}

		if (!bObstacle)
		{
			m_aWayPoint[i] = new Node(vWPPosition);
		}
		else
		{
			m_aWayPoint[i] = shNULL;
		}
	}

	for (int i = 0; i < (iCols * iRows); ++i)
	{
		if (m_aWayPoint[i] != shNULL)
		{
			m_aWayPoint[i]->m_aNeighbor[e_direction_up] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_down] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_left] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_right] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_up_left] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_up_right] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_down_left] = shNULL;
			m_aWayPoint[i]->m_aNeighbor[e_direction_down_right] = shNULL;

			//
			// Up
			if (i > iCols)
			{
				m_aWayPoint[i]->m_aNeighbor[e_direction_up] = m_aWayPoint[i - iCols];

				//
				// Up Left
				if (i % iCols != 0)
				{
					m_aWayPoint[i]->m_aNeighbor[e_direction_up_left] = m_aWayPoint[i - iCols - 1];
				}

				//
				// Up Right
				if (i % iCols != (iCols - 1))
				{
					m_aWayPoint[i]->m_aNeighbor[e_direction_up_right] = m_aWayPoint[i - iCols + 1];
				}
			}

			//
			// Down
			if (i < iCols * iRows - iCols)
			{
				m_aWayPoint[i]->m_aNeighbor[e_direction_down] = m_aWayPoint[i + iCols];

				//
				// Down Right
				if (i % iCols != (iCols - 1))
				{
					m_aWayPoint[i]->m_aNeighbor[e_direction_down_right] = m_aWayPoint[i + iCols + 1];
				}

				//
				// Down Left
				if (i % iCols != 0)
				{
					m_aWayPoint[i]->m_aNeighbor[e_direction_down_left] = m_aWayPoint[i + iCols - 1];
				}
			}

			if (i % iCols != 0)
			{
				m_aWayPoint[i]->m_aNeighbor[e_direction_left] = m_aWayPoint[i - 1];
			}

			if (i % iCols != (iCols - 1))
			{
				m_aWayPoint[i]->m_aNeighbor[e_direction_right] = m_aWayPoint[i + 1];
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Graph::Release(void)
{
	int iWPCount = m_aWayPoint.GetCount();
	for (int iWP = 0; iWP < iWPCount; ++iWP)
	{
		SH_SAFE_DELETE(m_aWayPoint[iWP]);
	}

	m_aWayPoint.Empty();
	m_openSet.Empty();
	m_closedSet.Empty();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
bool Graph::FindPath(Node * pWPStart, Node * pWPEnd, CShArray<Node*> & aPathPoint)
{
	ResetAll();

	aPathPoint.Add(pWPStart);

	m_openSet.Add(pWPStart);
	pWPStart->m_h = ComputeHeuristicValue(pWPStart, pWPEnd);

	while (!m_openSet.IsEmpty())
	{
		Node * pCurrent = GetCurrent();

		if (pCurrent == pWPEnd)
		{
			ReconstructPath(pCurrent, aPathPoint);

			for (int i = 0; i < aPathPoint.GetCount(); i++)
			{
				Node * pWP = aPathPoint[i];
#if DEBUG_PATHFINDING
				pWP->SetColor(CShRGBAf(1.0f, 0.0f, 0.0f, 1.0f));
#endif //DEBUG_PATHFINDING
			}

			return(true);
		}

		m_openSet.RemoveAll(pCurrent);
		m_closedSet.Add(pCurrent);

		CShArray<Node*> aWP;
		pCurrent->GetNeighbor(aWP);

		int iNeighborCount = aWP.GetCount();
		for (int iNeighbour = 0; iNeighbour < iNeighborCount; ++iNeighbour)
		{
			Node * pWayPoint = aWP[iNeighbour];
			if (m_closedSet.Find(pWayPoint) > -1)
			{
				continue;
			}

			float tmpG = pCurrent->m_g + pCurrent->m_vPosition.Distance(pWayPoint->m_vPosition);

			if (m_openSet.Find(pWayPoint) == -1)
			{
				m_openSet.Add(pWayPoint);
			}
			else if (tmpG >= pWayPoint->m_g)
			{
				continue;
			}

			pWayPoint->m_pWPCameFrom = pCurrent;
			pWayPoint->m_g = tmpG;
			pWayPoint->m_f = pWayPoint->m_g + ComputeHeuristicValue(pWayPoint, pWPEnd);
		}
	}

	return(false);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
Node * Graph::FindNearestWayPoint(const CShVector2 & vPosition)
{
	Node * pNearestWP = m_aWayPoint[0];
	float fDistanceMin = pNearestWP->m_vPosition.Distance(vPosition);

	int iWPCount = m_aWayPoint.GetCount();
	for (int iWP = 0; iWP < iWPCount; ++iWP)
	{
		Node * pWP = m_aWayPoint[iWP];
		if (pWP)
		{
			float fDistance = pWP->m_vPosition.Distance(vPosition);

			if (fDistance < fDistanceMin)
			{
				pNearestWP = pWP;
				fDistanceMin = fDistance;
			}
		}
	}

	return pNearestWP;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
Node * Graph::GetWayPoint(int index)
{
	return(m_aWayPoint[index]);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
float Graph::ComputeHeuristicValue(Node * pWPStart, Node * pWPEnd)
{
	return(pWPStart->m_vPosition.Distance(pWPEnd->m_vPosition));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Graph::ReconstructPath(Node * pWP, CShArray<Node*> & aPathPoint)
{
	CShArray<Node*> aTmp;

	aTmp.Add(pWP);

	Node * pWPCurrent = pWP;

	while (pWPCurrent->m_pWPCameFrom != shNULL)
	{
		pWPCurrent = pWPCurrent->m_pWPCameFrom;
		aTmp.Add(pWPCurrent);
	}

	//revert array
	for (int i = aTmp.GetCount() - 2; i >= 0; --i) // aTmp.GetCount() - 2 => we don't add the first wp
	{
		aPathPoint.Add(aTmp[i]);
	}

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
Node * Graph::GetCurrent(void)
{
	int iWPCount = m_openSet.GetCount();

	Node * pCurrent = m_openSet[0];

	for (int iWP = 0; iWP < iWPCount; ++iWP)
	{
		Node * pWayPoint = m_openSet[iWP];
		if (pWayPoint->m_f < pCurrent->m_f)
		{
			pCurrent = pWayPoint;
		}
	}

	return pCurrent;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Graph::ResetAll(void)
{
	m_openSet.Empty();
	m_closedSet.Empty();

	int iWPCount = m_aWayPoint.GetCount();
	for (int i = 0; i < iWPCount; ++i)
	{
		Node * pWP = m_aWayPoint[i];
		if (pWP)
		{
			pWP->m_f = 0;
			pWP->m_g = 0;
			pWP->m_h = 0;
			pWP->m_pWPCameFrom = shNULL;

#if DEBUG_PATHFINDING
			ShEntity2::SetColor(pWP->m_pEntity, CShRGBAf(1.0f, 1.0f, 1.0f, 1.0f));
#endif //DEBUG_PATHFINDING
		}
	}
}
