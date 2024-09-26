#pragma once
#pragma once

#include "stdafx.h"
#include "Scorecard.h"
#include "Player.h"

class Human : public Player {
	Human();
	~Human();

	void setScore(int score);
	void setScorecard(Scorecard* scorecard);
	int getScore();



};