#pragma once

#include "Node.h"

#define DEBUG_PATHFINDING 0

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
	Node *							GetCurrent							(const CShArray<Node*> & openSet);
	void							ResetAll							(void);

public:

protected:
	
private:

	CShArray<Node*>	m_aWayPoint;

	struct Blocker
	{
		CShVector2 position;
		float radius;
	};

	CShArray<Blocker> m_aBlockers;
};

extern Graph g_graph;
