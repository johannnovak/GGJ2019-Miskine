#pragma once

#include "ShSDK/ShSDK.h"

#define DEFAULT_ENEMY_MONEY_GAIN_DIFFICULTY_LOW 15
#define DEFAULT_ENEMY_MONEY_GAIN_DIFFICULTY_MEDIUM 10
#define DEFAULT_ENEMY_MONEY_GAIN_DIFFICULTY_HIGH 5

#define DEFAULT_ENEMY_HP_DIFFICULTY_LOW 15
#define DEFAULT_ENEMY_HP_DIFFICULTY_MEDIUM 10
#define DEFAULT_ENEMY_HP_DIFFICULTY_HIGH 5

class Node;

class Enemy
{

public:

	enum EAnimationType
	{
		animation_top,
		animation_bottom,
		animation_left,
		animation_right,

		animation_max
	};

	enum EState
	{
		e_state_on,
		e_state_appear,
		e_state_disappear,
		e_state_off
	};

	explicit			 Enemy				(void);
	virtual				~Enemy				(void);

	void				Initialize			(const CShArray<ShEntity2*> aEntity[animation_max], ShEntity2* pEntityLifebar, int iBaseHealth);
	void				Release				(void);

	void				Start				(const CShVector2 & vPosition, const CShVector2 & vDestination, float fSpeed);
	void				Stop				(void);

	void				SetPath				(const CShArray<Node*> & aNodes);
	void				SetTargetNode		(Node * pNode);

	void				SetState			(EState state);
	EState				GetState			(void);

	void				Update				(float dt);

	void				TakeDamages			(int damages);
	void				TakeSlowEffect		(float ratio);

	const CShVector2 &	GetPosition			(void) const;
	const int &			GetBaseHealth		(void) const;
	const int &			GetCurrentHealth	(void) const;

	bool				IsDead				(void);

private:
	
private:
	EState					m_eState;
	float					m_fStateTime;
	float					m_fSpeed;
	float					m_fSlowEffect;
	float					m_fSlowTime;
	float					m_fSlowDt;

	ShEntity2 *				m_pEntityLifeBar;

	CShVector2				m_vPosition;
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
	EAnimationType			m_eCurrentAnimationType;
	CShArray<ShEntity2 *>	m_aMoveAnimation[animation_max];
	CShArray<ShEntity2 *>	m_aMoveAnimationCG[animation_max];
};

