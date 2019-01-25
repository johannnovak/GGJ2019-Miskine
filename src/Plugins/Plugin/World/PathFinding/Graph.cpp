#include "ShSDK/ShSDK.h"
#include "Graph.h"
#include "WayPoint.h"

Graph g_graph;

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
	CShVector2 vPosition = ShDummyAABB2::GetPosition2(pDummyAABB2);
	float fWidth = ShDummyAABB2::GetAABB(pDummyAABB2).GetWidth();
	float fHeight = ShDummyAABB2::GetAABB(pDummyAABB2).GetHeight();

	int iCols = fWidth / 10.0f;
	int iRows = fHeight / 10.0f;

	CShVector2 vStartPosition = vPosition + CShVector2(-fWidth * 0.5f, fHeight * 0.5f);
	for (int i = 0; i < (iCols * iRows); ++i)
	{
		int iCol = i / iRows;
		int iRow = i % iCols;
		CShVector3 vWPPosition = CShVector3(vStartPosition, 1.0f) + CShVector3(iCol * (fWidth / iCols), -iRow * (fHeight / iRows), 0.0f);

		ShEntity2::Create(CShIdentifier("level_test_pathfinding"), GID(NULL), CShIdentifier("layer_default"), CShIdentifier("game"), CShIdentifier("white_square"), vWPPosition, CShEulerAngles::ZERO, CShVector3(1.0f,1.0f,1.0f));
	}

	/*
	ShScriptTree * pScriptTree = ShScriptTree::Load(strFileName);
	SH_ASSERT(shNULL != pScriptTree);

	
	ShScriptTreeNode* pRootNode = ShScriptTree::GetRootNode(pScriptTree);
	if (!pRootNode)
	{
		ShScriptTree::Release(pScriptTree);
		SH_ASSERT_ALWAYS();
		return;
	}

	SH_ASSERT(ShScriptTreeNode::GetIdentifier(pRootNode) == CShIdentifier("graph"));

	int iNodeCount = -1;
	ShScriptTreeNode::GetAttributeValueAsInt(pRootNode, CShIdentifier("node_count"), iNodeCount);

	m_aWayPoint.SetCount(iNodeCount);

	for (int iWP = 0; iWP < iNodeCount; ++iWP)
	{
		char szDummyIdentifier[1024];
		sprintf(szDummyIdentifier, "dummy_circle_auto_%03d", iWP+1);
		ShDummyCircle* pDummy = ShDummyCircle::Find(levelIdentifier, CShIdentifier(szDummyIdentifier));
		SH_ASSERT(shNULL != pDummy);
		m_aWayPoint[iWP] = new WayPoint(pDummy, iWP);
	}

	for (int iRootChild = 0; iRootChild < ShScriptTreeNode::GetChildCount(pRootNode); ++iRootChild)
	{
		ShScriptTreeNode * pRootChildNode = ShScriptTreeNode::GetChild(pRootNode, iRootChild);

		if (ShScriptTreeNode::GetIdentifier(pRootChildNode) == CShIdentifier("nodes"))
		{
			int iLinksChildNodeCount = ShScriptTreeNode::GetChildCount(pRootChildNode);
			for (int iLinksChildNode = 0; iLinksChildNode < iLinksChildNodeCount; ++iLinksChildNode)
			{
				ShScriptTreeNode * pLinksChildNode = ShScriptTreeNode::GetChild(pRootChildNode, iLinksChildNode);

				int iNodeFrom, iNodeTo;

				if (ShScriptTreeNode::GetIdentifier(pLinksChildNode) == CShIdentifier("node"))
				{
					ShScriptTreeNode::GetAttributeValueAsInt(pLinksChildNode, CShIdentifier("id"), iNodeFrom);

					int iLinkFromChildNodeCount = ShScriptTreeNode::GetChildCount(pLinksChildNode);
					for (int iLinkFromChildNode = 0; iLinkFromChildNode < iLinkFromChildNodeCount; ++iLinkFromChildNode)
					{
						ShScriptTreeNode * pLinkFromChildNode = ShScriptTreeNode::GetChild(pLinksChildNode, iLinkFromChildNode);

						if (ShScriptTreeNode::GetIdentifier(pLinkFromChildNode) == CShIdentifier("node_up"))
						{
							ShScriptTreeNode::GetAttributeValueAsInt(pLinkFromChildNode, CShIdentifier("id"), iNodeTo);

							WayPoint* pWP = m_aWayPoint[iNodeTo-1];
							m_aWayPoint[iNodeFrom-1]->m_aNeighbor[e_direction_up] = pWP;
						}
						else if (ShScriptTreeNode::GetIdentifier(pLinkFromChildNode) == CShIdentifier("node_left"))
						{
							ShScriptTreeNode::GetAttributeValueAsInt(pLinkFromChildNode, CShIdentifier("id"), iNodeTo);

							WayPoint* pWP = m_aWayPoint[iNodeTo-1];
							m_aWayPoint[iNodeFrom-1]->m_aNeighbor[e_direction_left] = pWP;
						}
						else if (ShScriptTreeNode::GetIdentifier(pLinkFromChildNode) == CShIdentifier("node_right"))
						{
							ShScriptTreeNode::GetAttributeValueAsInt(pLinkFromChildNode, CShIdentifier("id"), iNodeTo);

							WayPoint* pWP = m_aWayPoint[iNodeTo-1];
							m_aWayPoint[iNodeFrom-1]->m_aNeighbor[e_direction_right] = pWP;
						}
						else if (ShScriptTreeNode::GetIdentifier(pLinkFromChildNode) == CShIdentifier("node_down"))
						{
							ShScriptTreeNode::GetAttributeValueAsInt(pLinkFromChildNode, CShIdentifier("id"), iNodeTo);

							WayPoint* pWP = m_aWayPoint[iNodeTo-1];
							m_aWayPoint[iNodeFrom-1]->m_aNeighbor[e_direction_down] = pWP;
						}
						else
						{
							SH_ASSERT_ALWAYS();
						}
					}
				}
			}
		}
	}
	*/
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
bool Graph::FindPath(WayPoint* pWPStart, WayPoint* pWPEnd, CShArray<WayPoint*> & aPathPoint)
{
	ResetAll();

	m_openSet.Add(pWPStart);
	pWPStart->m_h = ComputeHeuristicValue(pWPStart, pWPEnd);

	while (!m_openSet.IsEmpty())
	{
		WayPoint* pCurrent = GetCurrent();

		if (pCurrent == pWPEnd)
		{
			ReconstructPath(pCurrent, aPathPoint);
			return(true);
		}

		m_openSet.RemoveAll(pCurrent);
		m_closedSet.Add(pCurrent);

		CShArray<WayPoint*> aWP;
		pCurrent->GetNeighbor(aWP);

		int iNeighborCount = aWP.GetCount();
		for (int iNeighbour = 0; iNeighbour < iNeighborCount; ++iNeighbour)
		{
			WayPoint* pWayPoint = aWP[iNeighbour];
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
WayPoint* Graph::FindNearestWayPoint(const CShVector2 & vPosition)
{
	WayPoint* pNearestWP = m_aWayPoint[0];
	float fDistanceMin = pNearestWP->m_vPosition.Distance(vPosition);

	int iWPCount = m_aWayPoint.GetCount();
	for (int iWP = 0; iWP < iWPCount; ++iWP)
	{
		WayPoint* pWP = m_aWayPoint[iWP];
		float fDistance = pWP->m_vPosition.Distance(vPosition);

		if (fDistance < fDistanceMin)
		{
			pNearestWP = pWP;
			fDistanceMin = fDistance;
		}
	}

	return pNearestWP;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
WayPoint* Graph::GetWayPoint(int index)
{
	return(m_aWayPoint[index]);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
float Graph::ComputeHeuristicValue(WayPoint* pWPStart, WayPoint* pWPEnd)
{
	return(pWPStart->m_vPosition.Distance(pWPEnd->m_vPosition));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Graph::ReconstructPath(WayPoint* pWP, CShArray<WayPoint*> & aPathPoint)
{
	CShArray<WayPoint*> aTmp;

	aTmp.Add(pWP);

	WayPoint* pWPCurrent = pWP;

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
WayPoint* Graph::GetCurrent(void)
{
	int iWPCount = m_openSet.GetCount();

	WayPoint* pCurrent = m_openSet[0];

	for (int iWP = 0; iWP < iWPCount; ++iWP)
	{
		WayPoint* pWayPoint = m_openSet[iWP];
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
		WayPoint* pWP = m_aWayPoint[i];
		pWP->m_f = 0;
		pWP->m_g = 0;
		pWP->m_h = 0;
		pWP->m_pWPCameFrom = shNULL;
	}
}