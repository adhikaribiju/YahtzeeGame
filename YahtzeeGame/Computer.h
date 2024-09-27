#pragma once

#include "stdafx.h"
#include "Player.h"

class Computer : public Player {

public:
	Computer();
	~Computer();

	void playComputer();

private:
	const int max_rolls = 3;
	int num_rolls;
	 
};
