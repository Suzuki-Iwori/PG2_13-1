#include"Object.h"
#include <Novice.h>

const char kWindowTitle[] = "GC1A_14_スズキ_イヲリ";


bool Enemy::isExist_;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Player* player = new Player;

	Enemy* enemy[2]{};

	enemy[0] = new Enemy(Vector2{ 200.0f,200.0f });
	enemy[1] = new Enemy(Vector2{ 400.0f,400.0f });

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player->SetPlayerMove(keys, preKeys);

		for (int i = 0; i < 2; i++) {
			enemy[i]->SetMove();

			for (int j = 0; j < 6; j++) {
				enemy[i]->SetCollision(player->GetPlayerBullet(j));
			}

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->SetDraw();

		for (int i = 0; i < 2; i++) {
			enemy[i]->SetDraw();
		}

		for (int j = 0; j < 6; j++) {
			player->GetPlayerBullet(j)->SetDraw();
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
