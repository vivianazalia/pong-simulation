#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include<stdlib.h>
#include<time.h>
#include"Score.h"
#include"Player.h"

using namespace std;

Score score(0, 0);
mutex m;
condition_variable cv;
Player playerX("Player X");
Player playerY = playerX;
int hit;

void DisplayScore() {
	cout << "================================" << endl;
	cout << "Player X score : " << score.GetScoreX() << endl;
	cout << "Player Y score : " << score.GetScoreY() << endl;
	cout << "================================" << endl;
}

void PlayerX() {
	this_thread::sleep_for(1s);
	unique_lock<mutex> ul(m);
	xp:
	hit = playerX.GetHit();

	while (hit <= 50)
	{
		cout << "==> Player X Hit : " << hit << endl;
		score.ScoreY();
		DisplayScore();
		hit = playerX.GetHit();

		if (score.GetScoreX() >= 10 || score.GetScoreY() >= 10)
		{
			ul.unlock();
			cv.notify_one();
			return;
		}
	}

	//if hit > 50
	cv.notify_one();
	hit = 0;
	cv.wait(ul, [] {return (hit > 50) ? true : false;});
	goto xp;
}

void PlayerY() {
	this_thread::sleep_for(1s);
	unique_lock<mutex> ul(m);
	yp:
	hit = playerY.GetHit();
	
	while (hit <= 50)
	{
		cout << "==> Player Y Hit : " << hit << endl;
		score.ScoreX();
		DisplayScore();
		hit = playerY.GetHit();

		if (score.GetScoreX() >= 10 || score.GetScoreY() >= 10)
		{
			ul.unlock();
			cv.notify_one();
			return;
		}
	}

	//if hit > 50
	cv.notify_one();
	cv.wait(ul, [] {return (hit <= 50) ? true : false;});
	goto yp;
}

int main() {
	
	playerY.SetName("Player Y");
	int firstTurn;

	thread t1(PlayerX);
	thread t2(PlayerY);

	firstTurn = rand() % 2;

	if (firstTurn == 0)
	{
		t1.join();
		this_thread::sleep_for(1s);
		t2.join();
	}
	else
	{
		t2.join();
		this_thread::sleep_for(1s);
		t1.join();
	}

	unique_lock<mutex> ul(m);
	cv.wait(ul, [] {return (score.GetScoreX() >= 10 || score.GetScoreY() >= 10);});

	cout << "===== " << score.CheckWin() << " =====" << endl; 
	DisplayScore();

	ul.unlock();

	return 0;
}