#ifndef	__HEADER_NEWPET_SYSTEM__
#define	__HEADER_NEWPET_SYSTEM__

class CHARACTER;

struct SNewPetAbility
{
};

class CNewPetActor
{
public:
	enum ENewPetOptions
	{
		EPetOption_Followable		= 1 << 0,
		EPetOption_Mountable		= 1 << 1,
		EPetOption_Summonable		= 1 << 2,
		EPetOption_Combatable		= 1 << 3,
	};


protected:
	friend class CNewPetSystem;

	CNewPetActor(LPCHARACTER owner, DWORD vnum, DWORD options = EPetOption_Followable | EPetOption_Summonable);

	virtual ~CNewPetActor();

	virtual bool	Update(DWORD deltaTime);

protected:
	virtual bool	_UpdateFollowAI();
	virtual bool	_UpdatAloneActionAI(float fMinDist, float fMaxDist);

private:
	bool Follow(float fMinDistance = 50.f);

public:
	LPCHARACTER		GetCharacter()	const					{ return m_pkChar; }
	LPCHARACTER		GetOwner()	const						{ return m_pkOwner; }
	DWORD			GetVID() const							{ return m_dwVID; }
	DWORD			GetVnum() const							{ return m_dwVnum; }

	bool			HasOption(ENewPetOptions option) const		{ return m_dwOptions & option; }

	void			SetName(const char* petName);
	void			SetLevel(DWORD level);

	bool			Mount();
	void			Unmount();

	DWORD			Summon(const char* petName, LPITEM pSummonItem, bool bSpawnFar = false);
	void			Unsummon();

	bool			IsSummoned() const			{ return 0 != m_pkChar; }
	void			SetSummonItem (LPITEM pItem);
	DWORD			GetSummonItemVID () { return m_dwSummonItemVID; }
	DWORD			GetSummonItemID () { return m_dwSummonItemID; }
	DWORD			GetEvolution() { return m_dwevolution; }
	DWORD			GetLevel() { return m_dwlevel; }
	void			SetEvolution(int lv);
	void			SetExp(DWORD exp, int mode);
	DWORD			GetExp() { return m_dwexp; }
	DWORD			GetExpI() { return m_dwexpitem; }
	int				GetSkillCount();
	void			SetNextExp(int nextExp);
	int				GetNextExpFromMob() { return m_dwExpFromMob; }
	int				GetNextExpFromItem() { return m_dwExpFromItem; }
	int				GetLevelStep() { return m_dwlevelstep; }
	int				GetPetType() { return m_dwPetType; }

	void			IncreasePetBonus();
	void			SetItemCube(int pos, int invpos);
	void			ItemCubeFeed(int type);
	void			DoPetSkill(int skillslot);
	void			UpdateTime();
	
	bool			ResetSkill(int skill);
	bool			IncreasePetSkill(int skill);
	bool			IncreasePetEvolution();

	void			GiveBuff();
	void			ClearBuff();

private:
	int			m_dwlevelstep;
	int			m_dwExpFromMob;
	int			m_dwExpFromItem;
	int			m_dwexpitem;
	int			m_dwevolution;
	int			m_dwTimePet;
	int			m_dwslotimm;
	int			m_dwPetType;

	DWORD		m_dwImmTime;

	int				m_dwpetslotitem[9];
	int				m_dwskill[3];
	int				m_dwskillslot[3];
	int				m_dwbonuspet[3][2];
	DWORD			m_dwVnum;
	DWORD			m_dwVID;
	DWORD			m_dwlevel;	
	DWORD			m_dwexp;
	DWORD			m_dwOptions;
	DWORD			m_dwLastActionTime;
	DWORD			m_dwSummonItemVID;
	DWORD			m_dwSummonItemID;
	DWORD			m_dwSummonItemVnum;

	DWORD			m_dwduration;
	DWORD			m_dwtduration;
	DWORD			m_dwdurationYas;

	short			m_originalMoveSpeed;

	std::string		m_name;

	LPCHARACTER		m_pkChar;
	LPCHARACTER		m_pkOwner;

};

class CNewPetSystem
{
public:
	typedef	boost::unordered_map<DWORD,	CNewPetActor*>		TNewPetActorMap;

public:
	CNewPetSystem(LPCHARACTER owner);
	virtual ~CNewPetSystem();

	CNewPetActor*	GetByVID(DWORD vid) const;
	CNewPetActor*	GetByVnum(DWORD vnum) const;

	bool		Update(DWORD deltaTime);
	void		Destroy();

	size_t		CountSummoned() const;

public:
	void		SetUpdatePeriod(DWORD ms);

	CNewPetActor*	Summon(DWORD mobVnum, LPITEM pSummonItem, const char* petName, bool bSpawnFar, DWORD options = CNewPetActor::EPetOption_Followable | CNewPetActor::EPetOption_Summonable);

	void		Unsummon(DWORD mobVnum, bool bDeleteFromList = false);
	void		Unsummon(CNewPetActor* petActor, bool bDeleteFromList = false);

	CNewPetActor*	AddPet(DWORD mobVnum, const char* petName, const SNewPetAbility& ability, DWORD options = CNewPetActor::EPetOption_Followable | CNewPetActor::EPetOption_Summonable | CNewPetActor::EPetOption_Combatable);

	bool		ResetSkill(int skill);
	bool		IncreasePetSkill(int skill);
	bool		IncreasePetEvolution();	
	
	void		DeletePet(DWORD mobVnum);
	void		DeletePet(CNewPetActor* petActor);
	void		RefreshBuff();
	bool		IsActivePet();
	DWORD		GetNewPetITemID();
	void		SetExp(int iExp, int mode);
	int			GetEvolution();
	int			GetLevel();
	int			GetExp();
	int			GetLevelStep();
	int			GetPetType();
	void		SetItemCube(int pos, int invpos);
	void		ItemCubeFeed(int type);
	void		DoPetSkill(int skillslot);
	void		UpdateTime();

private:
	TNewPetActorMap	m_petActorMap;
	LPCHARACTER		m_pkOwner;					///< 펫 시스템의 Owner
	DWORD			m_dwUpdatePeriod;			///< 업데이트 주기 (ms단위)
	DWORD			m_dwLastUpdateTime;
	LPEVENT			m_pkNewPetSystemUpdateEvent;
	LPEVENT			m_pkNewPetSystemExpireEvent;
};
#endif
