#pragma once

#include "ShSDK/ShSDK.h"

class Node;

class Enemy
{

public:
	enum EState
	{
		e_state_on,
		e_state_appear,
		e_state_disappear,
		e_state_off
	};

	explicit			 Enemy				(void);
	virtual				~Enemy				(void);

	void				Initialize			(const CShArray<ShEntity2*> aEntity, ShEntity2* pEntityLifebar, int iBaseHealth);
	void				Release				(void);

	void				Start				(const CShVector3 & vPosition, const CShVector2 & vDestination);
	void				Stop				(void);

	void				SetPath				(const CShArray<Node*> & aNodes);
	void				SetTargetNode		(Node * pNode);

	void				SetState			(EState state);
	EState				GetState			(void);

	void				Update				(float dt);

	void				TakeDamages			(int damages);

	const CShVector3 &	GetPosition			(void) const;
	const int &			GetBaseHealth		(void) const;
	const int &			GetCurrentHealth	(void) const;

	bool				IsDead				(void);

private:
	
private:
	EState					m_eState;
	float					m_fStateTime;
	float					m_fSpeed;

	ShEntity2 *				m_pEntityLifeBar;

	CShVector3				m_vPosition;
	CShVector2				m_vStartPosition;
	CShVector2				m_v;
	float					m_fCompletion;

	int						m_baseHealth;
	int						m_currentHealth;

	CShArray<Node*>			m_aNodes;
	int						m_iDestinationNode;

	float					m_fAnimationDt;
	float					m_fAnimationSpeed;
	int						m_currentSprite;
	CShArray<ShEntity2 *>	m_aMoveAnimation;
};

