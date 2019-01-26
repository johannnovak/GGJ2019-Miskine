#include "Player2EventTypeWords.h"
#include "Player2EventManager.h"

/*static*/ CShArrayMap<EPlayer2EventDifficulty, CShArray<CShWString> > Player2EventTypeWords::s_aawstrDictionnary;

/**
 * @brief Constructor
 */
/*explicit*/ Player2EventTypeWords::Player2EventTypeWords(void)
: Player2Event(e_player2_event_type_type_words)
, m_wstrWordToType(L"")
, m_iCurrentIndex(0)
{
	// ...
}

/**
 * @brief Constructor
 */
/*explicit*/ Player2EventTypeWords::Player2EventTypeWords(const CShWString & wstrWordToType)
: Player2Event(e_player2_event_type_type_words)
, m_wstrWordToType(wstrWordToType)
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
/*virtual*/ void Player2EventTypeWords::Update(float dt, ShGUIControlEditBox * pEditBoxHidden)
{
	if (!IsFinished())
	{
		if (shNULL != pEditBoxHidden)
		{
			const CShWString & wstrInputText = ShGUIControlEditBox::GetText(pEditBoxHidden);
			int iInputLength = wstrInputText.GetLength();
			int iCorrectStrLength = m_wstrWordToType.GetLength();
			for (int iInputCharIndex = 0; iInputCharIndex < iInputLength; ++iInputCharIndex)
			{
				if (m_iCurrentIndex+1 < iCorrectStrLength && m_wstrWordToType[m_iCurrentIndex+1] == wstrInputText[iInputCharIndex])
				{
					++m_iCurrentIndex;
				}
				else
				{
					++m_iErrorNb;
				}
			}
		
			m_bFinished = (m_iCurrentIndex >= iCorrectStrLength);
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
void Player2EventTypeWords::SetWordToType(const CShWString & wstrWordToType)
{
	m_wstrWordToType = wstrWordToType;
	
	m_iCurrentIndex = 0;
}

/**
 * @brief ResetInternal
 */
/*virtual*/ void Player2EventTypeWords::ResetInternal(void)
{
	const CShArray<CShWString> * aDifficulty = s_aawstrDictionnary.Find(m_eDifficulty);
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
		s_aawstrDictionnary.Add(e_player2_event_difficulty_low,		CShArray<CShWString>());
		s_aawstrDictionnary.Add(e_player2_event_difficulty_medium,	CShArray<CShWString>());
		s_aawstrDictionnary.Add(e_player2_event_difficulty_high,		CShArray<CShWString>());
		s_aawstrDictionnary.Add(e_player2_event_difficulty_hardcore,	CShArray<CShWString>());

		//
		// Add string to low entry
		CShArray<CShWString> * aDifficultyLow = s_aawstrDictionnary.Find(e_player2_event_difficulty_low);
		aDifficultyLow->Add(CShWString(L"banana"));
		aDifficultyLow->Add(CShWString(L"pineapple"));
		aDifficultyLow->Add(CShWString(L"apple"));
		aDifficultyLow->Add(CShWString(L"beans"));
		aDifficultyLow->Add(CShWString(L"leek"));
		aDifficultyLow->Add(CShWString(L"buy"));
		aDifficultyLow->Add(CShWString(L"sell"));
		aDifficultyLow->Add(CShWString(L"treasurable"));
		aDifficultyLow->Add(CShWString(L"turtledoving"));
		aDifficultyLow->Add(CShWString(L"ultracentenarianism"));
		aDifficultyLow->Add(CShWString(L"unbend"));
		aDifficultyLow->Add(CShWString(L"uncontemptuousness"));
		aDifficultyLow->Add(CShWString(L"underplanting"));
		aDifficultyLow->Add(CShWString(L"unsuppositional"));
		aDifficultyLow->Add(CShWString(L"unwillingly"));
		aDifficultyLow->Add(CShWString(L"uptown"));
		aDifficultyLow->Add(CShWString(L"vacation"));
		aDifficultyLow->Add(CShWString(L"vandalize"));
		aDifficultyLow->Add(CShWString(L"violent"));
		aDifficultyLow->Add(CShWString(L"wine"));
		aDifficultyLow->Add(CShWString(L"woeful"));
		aDifficultyLow->Add(CShWString(L"woman"));
		aDifficultyLow->Add(CShWString(L"wraps"));
		aDifficultyLow->Add(CShWString(L"wrinkles"));
		aDifficultyLow->Add(CShWString(L"wrongfully"));
		aDifficultyLow->Add(CShWString(L"xenophile"));
		aDifficultyLow->Add(CShWString(L"xerxes"));
		aDifficultyLow->Add(CShWString(L"zeal"));
		aDifficultyLow->Add(CShWString(L"zenocentric"));
		aDifficultyLow->Add(CShWString(L"zestfulnesses"));
		aDifficultyLow->Add(CShWString(L"zesty"));
		aDifficultyLow->Add(CShWString(L"ZIP"));
		aDifficultyLow->Add(CShWString(L"zodiac"));
		aDifficultyLow->Add(CShWString(L"zombie"));
		aDifficultyLow->Add(CShWString(L"Zonurus"));
		aDifficultyLow->Add(CShWString(L"zoo"));
		aDifficultyLow->Add(CShWString(L"zoo"));
		aDifficultyLow->Add(CShWString(L"zoonomia"));
		aDifficultyLow->Add(CShWString(L"zoonomic"));
		aDifficultyLow->Add(CShWString(L"zoophysicist"));

		//
		// Add string to medium entry
		CShArray<CShWString> * aDifficultyMedium = s_aawstrDictionnary.Find(e_player2_event_difficulty_medium);
		aDifficultyMedium = aDifficultyLow;

		//
		// Add string to high entry
		CShArray<CShWString> * aDifficultyHigh = s_aawstrDictionnary.Find(e_player2_event_difficulty_high);
		aDifficultyHigh = aDifficultyLow;

		//
		// Add string to hardcore entry
		CShArray<CShWString> * aDifficultyHardcore = s_aawstrDictionnary.Find(e_player2_event_difficulty_hardcore);
		aDifficultyHardcore = aDifficultyLow;
	}
}