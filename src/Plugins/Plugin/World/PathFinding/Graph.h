#pragma once

#include "Node.h"

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

	bool							FindPath							(Node* pWPStart, Node* pWPEnd, CShArray<Node*> & aPathPoint);
	Node *							FindNearestWayPoint					(const CShVector2 & vPosition);
	Node *							GetWayPoint							(int index);

	bool							AddBlocker							(const CShVector2 & pos, float radius);
	bool							UpdateGraph							(void);

protected:

private:

	float							ComputeHeuristicValue				(Node* pWPStart, Node* pWPEnd);
	void							ReconstructPath						(Node* pWP, CShArray<Node*> & aPathPoint);
	Node *							GetCurrent							(void);
	void							ResetAll							(void);

public:

protected:
	
private:

	CShArray<Node*>	m_aWayPoint;
	CShArray<Node*> m_openSet;
	CShArray<Node*> m_closedSet;

	struct Blocker
	{
		CShVector2 position;
		float radius;
	};

	CShArray<Blocker> m_aBlockers;
};

extern Graph g_graph;
