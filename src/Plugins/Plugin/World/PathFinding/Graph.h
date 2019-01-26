#pragma once

#include "WayPoint.h"

#define DEBUG_PATHFINDING 1

class Graph
{
public:

	//
	// Construction / Destruction
	explicit						Graph								(void);
	virtual							~Graph								(void);

	void							Initialize							(ShDummyAABB2 * pDummyAABB2);
	void							Release								(void);

	bool							FindPath							(WayPoint* pWPStart, WayPoint* pWPEnd, CShArray<WayPoint*> & aPathPoint);
	WayPoint*						FindNearestWayPoint					(const CShVector2 & vPosition);
	WayPoint*						GetWayPoint							(int index);

protected:

private:
	float							ComputeHeuristicValue				(WayPoint* pWPStart, WayPoint* pWPEnd);
	void							ReconstructPath						(WayPoint* pWP, CShArray<WayPoint*> & aPathPoint);
	WayPoint*						GetCurrent							(void);
	void							ResetAll							(void);

public:

protected:
	
private:

	CShArray<WayPoint*> m_openSet;
	CShArray<WayPoint*> m_closedSet;
	CShArray<WayPoint*>	m_aWayPoint;

};

extern Graph g_graph;
