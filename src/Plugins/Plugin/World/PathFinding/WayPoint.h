#pragma once

#define DEBUG_PATHFINDING 1

enum EDirection
{
	e_direction_up,
	e_direction_down,
	e_direction_left,
	e_direction_right,
	e_direction_up_left,
	e_direction_up_right,
	e_direction_down_left,
	e_direction_down_right,
	e_direction_max
};

class WayPoint
{
public:

	//
	// Construction / Destruction
	explicit				WayPoint							(const CShVector2 & vPosition);
	virtual					~WayPoint							(void);

	const CShVector2 &		GetPosition							(void) const;

	void					SetNeighbour						(EDirection direction, WayPoint* pWP);

	WayPoint*				GetNeighbour						(EDirection direction);
	void					GetNeighbor							(CShArray<WayPoint*> & aWP);

#if DEBUG_PATHFINDING
	void					SetColor							(const CShRGBAf & color);
#endif //DEBUG_PATHFINDING

protected:

private:

public:

protected:
	
private:

	CShVector2 m_vPosition;
	float m_f;
	float m_g;
	float m_h;

	WayPoint*					m_aNeighbor[e_direction_max];
	WayPoint*					m_pWPCameFrom;

#if DEBUG_PATHFINDING
	ShEntity2*					m_pEntity;
#endif //DEBUG_PATHFINDING

	friend class Graph;
};
