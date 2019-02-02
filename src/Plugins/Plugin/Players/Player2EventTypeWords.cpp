#include "Player2EventTypeWords.h"
#include "Player2EventManager.h"

/*static*/ CShArrayMap<EPlayer2EventDifficulty, CShArray<CShWString> > Player2EventTypeWords::s_aawstrDictionnary;

/**
 * @brief Constructor
 */
/*explicit*/ Player2EventTypeWords::Player2EventTypeWords(void)
: Player2Event()
, m_wstrWordToType(L"")
, m_iCurrentIndex(0)
{
	// ...
}

/**
 * @brief Constructor
 */
/*explicit*/ Player2EventTypeWords::Player2EventTypeWords(const CShWString & wstrWordToType)
: Player2Event()
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
				if (m_iCurrentIndex < iCorrectStrLength && m_wstrWordToType[m_iCurrentIndex] == wstrInputText[iInputCharIndex])
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
 * @brief Player2EventTypeWords::GetWordToType
 * @return
 */
const CShWString &Player2EventTypeWords::GetWordToType(void)
{
	return m_wstrWordToType;
}

/**
 * @brief ResetInternal
 */
/*virtual*/ void Player2EventTypeWords::ResetInternal(void)
{
	const CShArray<CShWString> * aDifficulty = s_aawstrDictionnary.Find(m_eDifficulty);
	int iWordsCount = aDifficulty->GetCount();
	int iIndex	= -1;

	iIndex	= static_cast<int>(std::rand() % (iWordsCount - 1));	// [0;count[
	SetWordToType(aDifficulty->At(iIndex));
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

		//
		// Add string to medium entry
		CShArray<CShWString> * aDifficultyMedium = s_aawstrDictionnary.Find(e_player2_event_difficulty_medium);
		aDifficultyMedium->Add(CShWString(L"underplanting"));
		aDifficultyMedium->Add(CShWString(L"unsuppositional"));
		aDifficultyMedium->Add(CShWString(L"unwillingly"));
		aDifficultyMedium->Add(CShWString(L"uptown"));
		aDifficultyMedium->Add(CShWString(L"vacation"));
		aDifficultyMedium->Add(CShWString(L"vandalize"));
		aDifficultyMedium->Add(CShWString(L"violent"));

		//
		// Add string to high entry
		CShArray<CShWString> * aDifficultyHigh = s_aawstrDictionnary.Find(e_player2_event_difficulty_high);
		aDifficultyHigh->Add(CShWString(L"wine"));
		aDifficultyHigh->Add(CShWString(L"woeful"));
		aDifficultyHigh->Add(CShWString(L"woman"));
		aDifficultyHigh->Add(CShWString(L"wraps"));
		aDifficultyHigh->Add(CShWString(L"wrinkles"));
		aDifficultyHigh->Add(CShWString(L"wrongfully"));
		aDifficultyHigh->Add(CShWString(L"xenophile"));
		aDifficultyHigh->Add(CShWString(L"xerxes"));
		aDifficultyHigh->Add(CShWString(L"zeal"));
		aDifficultyHigh->Add(CShWString(L"zenocentric"));
		aDifficultyHigh->Add(CShWString(L"zestfulnesses"));

		//
		// Add string to hardcore entry
		CShArray<CShWString> * aDifficultyHardcore = s_aawstrDictionnary.Find(e_player2_event_difficulty_hardcore);
		aDifficultyHardcore->Add(CShWString(L"zesty"));
		aDifficultyHardcore->Add(CShWString(L"ZIP"));
		aDifficultyHardcore->Add(CShWString(L"zodiac"));
		aDifficultyHardcore->Add(CShWString(L"zombie"));
		aDifficultyHardcore->Add(CShWString(L"Zonurus"));
		aDifficultyHardcore->Add(CShWString(L"zoo"));
		aDifficultyHardcore->Add(CShWString(L"zoo"));
		aDifficultyHardcore->Add(CShWString(L"zoonomia"));
		aDifficultyHardcore->Add(CShWString(L"zoonomic"));
		aDifficultyHardcore->Add(CShWString(L"zoophysicist"));
	}
}
