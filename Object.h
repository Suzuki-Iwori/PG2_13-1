#pragma once

struct Vector2 {
	float x;
	float y;
};

class Object {
protected:
	Vector2 position_;
	Vector2 radius_;
	Vector2 speed_;
	unsigned int color_;

public:
	Vector2 GetPosition();
	Vector2 GetRadius();

	void SetDraw();

};

class Bullet : public Object {
private:
	bool isExist_;

public:
	Bullet();
	void SetBullet(Vector2 putPosition);
	void ResetBullet();
	void SetMove();

	bool GetIsExist();

};

class Enemy : public Object {
public:
	static bool isExist_;

	Enemy(Vector2 firstPosition);

	void SetMove();
	void SetCollision(Bullet* bullet);

};

class Player : public Object {
private:
	Bullet* playerBullet_[6];

public:
	Player();
	void SetPlayerMove(char inputKeys[], char preInputKeys[]);
	~Player() {
		for (int i = 0; i < 6; i++) {
			delete playerBullet_[i];
		}
	}

	Bullet* GetPlayerBullet(int i);

};