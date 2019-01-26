#include "Player2EventTypeWords.h"
#include "Player2EventManager.h"

/*static*/ CShArrayMap<EPlayer2EventDifficulty, CShArray<CShString> > Player2EventTypeWords::s_aastrDictionnary;

/**
 * @brief Constructor
 */
/*explicit*/ Player2EventTypeWords::Player2EventTypeWords(void)
: Player2Event()
, m_strWordToType("")
, m_aIAIdWordToType()
, m_iCurrentIndex(0)
{
	// ...
}

/**
 * @brief Constructor
 */
/*explicit*/ Player2EventTypeWords::Player2EventTypeWords(const CShString & strWordToType)
: Player2Event()
, m_strWordToType(strWordToType)
, m_aIAIdWordToType()
, m_iCurrentIndex(0)
{
	// ...
}

/**
 * @brief Destructor
 */
/*virtual*/ Player2EventTypeWords::~Player2EventTypeWords(void)
{
	// ...
}


/**
 * @brief Update
 */
/*virtual*/ void Player2EventTypeWords::Initialize(void)
{
	//
	// Get User
	m_pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != m_pUser);

	//
	// Initialize directory
	SerializeDictionnary();
}

/**
 * @brief Update
 */
/*virtual*/ void Player2EventTypeWords::Release(void)
{
	// ...
}

/**
 * @brief Update
 */
/*virtual*/ void Player2EventTypeWords::Update(float dt)
{
	if (!IsFinished())
	{
		if (ShUser::HasTriggeredAction(m_pUser, m_aIAIdWordToType[m_iCurrentIndex]))
		{
			++m_iCurrentIndex;

			m_bFinished = (m_iCurrentIndex >= m_aIAIdWordToType.GetCount());
		}
	}
}

/**
 * @brief GetType
 */
/*virtual*/ EPlayer2EventType Player2EventTypeWords::GetType(void)
{
	return e_player2_event_type_type_words;
}

/**
 * @brief SetWordToType
 */
void Player2EventTypeWords::SetWordToType(const CShString & strWordToType)
{
	m_strWordToType = strWordToType;

	int iWordLength = strWordToType.GetLength();
	for (int iCharIndex = 0; iCharIndex < iWordLength; ++iCharIndex)
	{
		const char character[] = { strWordToType[iCharIndex] };
		m_aIAIdWordToType.Add(CShIdentifier(character));
	}
}

/**
 * @brief ResetInternal
 */
/*virtual*/ void Player2EventTypeWords::ResetInternal(void)
{
	const CShArray<CShString> * aDifficulty = s_aastrDictionnary.Find(m_eDifficulty);
	int iWordsCount = aDifficulty->GetCount();
	int iIndex	= -1;
	int iLength	= -1;
	do
	{
		iIndex	= static_cast<int>(std::rand() * (iWordsCount - 1));	// [0;count[
		iLength	= static_cast<int>(std::rand() * (iWordsCount*0.5f));	// [0;count/2[
	}
	while (iIndex + iLength > iWordsCount);

	const int iFinalIndex = static_cast<int>(std::rand() * (iLength - 1));	// [0;iLength[
	SetWordToType(aDifficulty->At(iFinalIndex));
}

/**
 * @brief SerializeDictionnary
 */
/*static*/ void Player2EventTypeWords::SerializeDictionnary(void)
{
	//
	// xml serialization
	if(0)
	{
		// ...
	}
	
	//
	// Fallback : static dictionnary initialization
	{
		//
		// Create entries
		s_aastrDictionnary.Add(e_player2_event_difficulty_low,		CShArray<CShString>());
		s_aastrDictionnary.Add(e_player2_event_difficulty_medium,	CShArray<CShString>());
		s_aastrDictionnary.Add(e_player2_event_difficulty_high,		CShArray<CShString>());
		s_aastrDictionnary.Add(e_player2_event_difficulty_hardcore,	CShArray<CShString>());

		//
		// Add string to low entry
		CShArray<CShString> * aDifficultyLow = s_aastrDictionnary.Find(e_player2_event_difficulty_low);
		aDifficultyLow->Add(CShString("banana"));
		aDifficultyLow->Add(CShString("pineapple"));
		aDifficultyLow->Add(CShString("apple"));
		aDifficultyLow->Add(CShString("beans"));
		aDifficultyLow->Add(CShString("leek"));
		aDifficultyLow->Add(CShString("buy"));
		aDifficultyLow->Add(CShString("sell"));
		aDifficultyLow->Add(CShString("treasurable"));
		aDifficultyLow->Add(CShString("turtledoving"));
		aDifficultyLow->Add(CShString("ultracentenarianism"));
		aDifficultyLow->Add(CShString("unbend"));
		aDifficultyLow->Add(CShString("uncontemptuousness"));
		aDifficultyLow->Add(CShString("underplanting"));
		aDifficultyLow->Add(CShString("unsuppositional"));
		aDifficultyLow->Add(CShString("unwillingly"));
		aDifficultyLow->Add(CShString("uptown"));
		aDifficultyLow->Add(CShString("vacation"));
		aDifficultyLow->Add(CShString("vandalize"));
		aDifficultyLow->Add(CShString("violent"));
		aDifficultyLow->Add(CShString("wine"));
		aDifficultyLow->Add(CShString("woeful"));
		aDifficultyLow->Add(CShString("woman"));
		aDifficultyLow->Add(CShString("wraps"));
		aDifficultyLow->Add(CShString("wrinkles"));
		aDifficultyLow->Add(CShString("wrongfully"));
		aDifficultyLow->Add(CShString("xenophile"));
		aDifficultyLow->Add(CShString("xerxes"));
		aDifficultyLow->Add(CShString("zeal"));
		aDifficultyLow->Add(CShString("zenocentric"));
		aDifficultyLow->Add(CShString("zestfulnesses"));
		aDifficultyLow->Add(CShString("zesty"));
		aDifficultyLow->Add(CShString("ZIP"));
		aDifficultyLow->Add(CShString("zodiac"));
		aDifficultyLow->Add(CShString("zombie"));
		aDifficultyLow->Add(CShString("Zonurus"));
		aDifficultyLow->Add(CShString("zoo"));
		aDifficultyLow->Add(CShString("zoo"));
		aDifficultyLow->Add(CShString("zoonomia"));
		aDifficultyLow->Add(CShString("zoonomic"));
		aDifficultyLow->Add(CShString("zoophysicist"));

		//
		// Add string to medium entry
		CShArray<CShString> * aDifficultyMedium = s_aastrDictionnary.Find(e_player2_event_difficulty_medium);
		aDifficultyMedium = aDifficultyLow;

		//
		// Add string to high entry
		CShArray<CShString> * aDifficultyHigh = s_aastrDictionnary.Find(e_player2_event_difficulty_high);
		aDifficultyHigh = aDifficultyLow;

		//
		// Add string to hardcore entry
		CShArray<CShString> * aDifficultyHardcore = s_aastrDictionnary.Find(e_player2_event_difficulty_hardcore);
		aDifficultyHardcore = aDifficultyLow;
	}
}
