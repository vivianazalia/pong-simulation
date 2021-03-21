#pragma once
using namespace std;

class Score
{
	int xScore;
	int yScore;
public:
	Score(int a, int b) {
		xScore = a;
		yScore = b;
	}

	void ScoreX() {
		xScore++;
	}

	void ScoreY() {
		yScore++;
	}

	int GetScoreX() {
		return xScore;
	}

	int GetScoreY() {
		return yScore;
	}

	string CheckWin() {
		if (xScore == 10)
		{
			return "Player X is winner!";
		}
		else if (yScore == 10)
		{
			return "Player Y is winner!";
		}
		else
		{
			return "Game still running.";
		}
	}
};

