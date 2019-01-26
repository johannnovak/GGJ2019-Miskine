#pragma once

enum EPlayer2EventType
{
	e_player2_event_type_type_words				= 0,	// type words
	e_player2_event_type_boost_tower			= 1,	// random keys
	e_player2_event_type_grant_special_attack	= 2,	// dual key combinations streak
	e_player2_event_type_control_enemy			= 3,	// mental calculation
	e_player2_event_type_immediate_qte			= 4,	// key appearing randomly on the screen
	e_player2_event_type_super_mega_combo		= 5,	// mix with word-typing/qte/special-attack

	e_player2_event_type_count					= e_player2_event_type_type_words + 1,
	//e_player2_event_type_count				= e_player2_event_type_super_mega_combo + 1,
};

enum EPlayer2EventDifficulty
{
	e_player2_event_difficulty_low,
	e_player2_event_difficulty_medium,
	e_player2_event_difficulty_high,
	e_player2_event_difficulty_hardcore,

	e_player2_event_difficulty_count = e_player2_event_difficulty_hardcore + 1,
};

class Player2Event
{
public:
	virtual void					Initialize		(void) = 0;
	virtual void					Release			(void) = 0;

	virtual void					Update			(float dt) = 0;
	virtual void					Reset			(void) = 0;

	virtual EPlayer2EventType		GetType			(void) = 0;
	virtual EPlayer2EventDifficulty	GetDifficulty	(void);
	bool							IsFinished		(void);

protected:
	explicit						Player2Event	(EPlayer2EventType eType);
	explicit						Player2Event	(EPlayer2EventType eType, EPlayer2EventDifficulty eDifficulty);
	virtual							~Player2Event	(void);

private:
public:
protected:
	EPlayer2EventDifficulty			m_eDifficulty;
	bool							m_bFinished;
};


//class Player2EventBoostTower : public Player2Event
//{
//	explicit				Player2EventBoostTower		(void) : Player2Event(e_player2_event_type_boost_tower)	{}
//	virtual					~Player2EventBoostTower		(void)	{}
//	
//	virtual EPlayer2EventType		GetType			(void) = 0;
//public:
//	CShArray<char>			m_acRandomKeyStreak;
//	CShArray<CShIdentifier>	m_aIAIdRandomKeyStreak;
//};
//
//class Player2EventGrantSpecialAttack : public Player2Event
//{
//	explicit				Player2EventGrantSpecialAttack		(void) : Player2Event(e_player2_event_type_grant_special_attack)	{}
//	virtual					~Player2EventGrantSpecialAttack		(void)	{}
//
//public:
//	CShArray<CShArray<CShString> >		m_aastrKeyCombinationsStreak;
//	CShArray<CShArray<CShIdentifier> >	m_aaIAIdKeyCombinationsStreak;
//};
//
//class Player2EventControlEnemy : public Player2Event
//{
//	explicit				Player2EventControlEnemy	(void) : Player2Event(e_player2_event_type_control_enemy)	{}
//	virtual					~Player2EventControlEnemy	(void)	{}
//
//public:
//	CShString				m_strMentalCalculation;
//	CShArray<CShIdentifier>	m_aIAIdMentalCalculationResult;
//};