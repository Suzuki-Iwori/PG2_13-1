#include"Object.h"
#include <Novice.h>

Vector2 Object::GetPosition() {
	return position_;
}
Vector2 Object::GetRadius() {
	return radius_;
}
void Object::SetDraw() {
	Novice::DrawEllipse((int)position_.x, (int)position_.y, (int)radius_.x, (int)radius_.y, 0.0f, color_, kFillModeSolid);
}

Bullet::Bullet() {
	position_ = { -200.0f,-200.0f };
	radius_ = { 12.0f,12.0f };
	speed_ = { 0.0f,0.0f };
	color_ = 0xFF0000FF;
	isExist_ = false;
}
void Bullet::SetBullet(Vector2 putPosition) {
	position_ = putPosition;
	speed_.y = -8.0f;
	isExist_ = true;
}
void Bullet::ResetBullet() {
	position_ = { -200.0f,-200.0f };
	speed_ = { 0.0f,0.0f };
	isExist_ = false;
}
void Bullet::SetMove() {
	position_.y += speed_.y;

	if (position_.y < 0) {
		this->ResetBullet();
	}

}
bool Bullet::GetIsExist() {
	return isExist_;
}

Enemy::Enemy(Vector2 firstPosition) {
	position_ = firstPosition;
	radius_ = { 20.0f,20.0f };
	speed_ = { 4.0f,0.0f };
	color_ = 0x0000FFFF;
	isExist_ = true;
}
void Enemy::SetMove() {
	if (isExist_) {
		position_.x += speed_.x;
		position_.y += speed_.y;

		if (position_.x < 0 || position_.x > 1280) {
			speed_.x *= -1.0f;
		}
	}
	else {
		position_ = { -200.0f,-200.0f };
	}

}
void Enemy::SetCollision(Bullet* bullet) {
	if (position_.x > bullet->GetPosition().x - bullet->GetRadius().x
		&& position_.x < bullet->GetPosition().x + bullet->GetRadius().x
		&& position_.y > bullet->GetPosition().y - bullet->GetRadius().y
		&& position_.y < bullet->GetPosition().y + bullet->GetRadius().y) {

		isExist_ = false;

	}
}

Player::Player() {
	position_ = { 540.0f,600.0f };
	radius_ = { 12.0f,12.0f };
	speed_ = { 4.0f,4.0f };
	color_ = 0xFFFFFFFF;

	for (int i = 0; i < 6; i++) {
		playerBullet_[i] = new Bullet;
	}

}
void Player::SetPlayerMove(char inputKeys[], char preInputKeys[]) {
	if (inputKeys[DIK_UP]) {
		position_.y -= speed_.y;
	}
	if (inputKeys[DIK_DOWN]) {
		position_.y += speed_.y;
	}
	if (inputKeys[DIK_LEFT]) {
		position_.x -= speed_.x;
	}
	if (inputKeys[DIK_RIGHT]) {
		position_.x += speed_.x;
	}

	for (int i = 0; i < 6; i++) {
		if (inputKeys[DIK_Z] && !preInputKeys[DIK_Z] && !playerBullet_[i]->GetIsExist()) {
			playerBullet_[i]->SetBullet(position_);
			break;
		}
		playerBullet_[i]->SetMove();
	}

}
Bullet* Player::GetPlayerBullet(int i) {
	return playerBullet_[i];
}