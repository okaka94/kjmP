#pragma once
#include "Std.h"

class Score_manager : public Singleton<Score_manager>
{
private:
	friend class Singleton<Score_manager>;
public:
	int		TotalScore = 0;
	int		ComboChain = 0;
	int		MaxCombo = 0;

public:
	virtual void Reset_score() { TotalScore = 0, ComboChain = 0, MaxCombo = 0; }
private:
	Score_manager() {};
public:
	~Score_manager() {};
};



