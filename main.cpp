#include <Novice.h>
#include<time.h>
#include<stdlib.h>
const char kWindowTitle[] = "切り替えの達人";
enum number {
	TITLE,
	MANUAL,
	GAME,
	SCORE
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	

	int number = 0;
	int playerX = 500;
	int playerY = 600;
	int radius = 64;
	int enemyX[9] = {};
	int enemyY[9] = {};
	int MyColor = 0;
	int Speed = 10;
	int enemySpeed = 5;
	int enemyFlag[9] = {};
	int color[9] = {};

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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
		switch (number)
		{
		case TITLE:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 1;
			}
			break;
		case MANUAL:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 2;
			}
			break;
		case GAME:
			//移動
			if (keys[DIK_A] || keys[DIK_LEFT]) {
				playerX -= Speed;

			}
			if (keys[DIK_D] || keys[DIK_RIGHT]) {
				playerX += Speed;
			}
			if (playerX + radius>= 1000) {
				playerX = 1000-radius;
			}
			if (playerX - radius<= 0) {
				playerX = 0+radius;
			}
			//色変更
			if (keys[DIK_J] ) {
				MyColor = 0;
			}
			if (keys[DIK_K] ) {
				MyColor = 1;
			}
			if (keys[DIK_L] ) {
				MyColor = 2;
			}


			//敵乱数
			if (rand() % 50 == 0) {
				int x = rand() % 900+64;
				int y = rand() % 9;
				for (int e = 0; e < 3; e++) {
					for (int i = 0; i < 9; i++) {
							if (enemyFlag[i] == 0) {
								enemyFlag[i] = 1;
								
								enemyX[i] = x;
								enemyY[i] = y-e*130;
								color[i] = rand() % 3;
								break;

							}
					
					}
				}
				
			}
			//敵移動
				for (int i = 0; i < 9; i++) {
					if (enemyFlag[i] == 1) {
                   enemyY[i] += enemySpeed;
					}
					
					if (enemyY[i] >= 720) {
						enemyFlag[i] = 0;
						enemyY[i] = 0;
				     }
				}
			

			break;
		case SCORE:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 0;
			}
			break;
		}
		///
		/// ↑更新処理ここまで
		///
		/// 	
		/// ↓描画処理ここから
		///
		switch (number)
		{
		case TITLE:
			Novice::ScreenPrintf(0, 0, "Title");
			break;
		case MANUAL:
			Novice::ScreenPrintf(0, 0, "Manual");
			break;
		case GAME:
			Novice::ScreenPrintf(0, 0, "Game");
			Novice::DrawLine(1000, 0, 1000, 720, RED);
			if (MyColor == 0) {
				//自機
				Novice::DrawEllipse(playerX, playerY, radius, radius, 0.0f, RED, kFillModeSolid);
		    }
			if (MyColor == 1) {
				//自機
				Novice::DrawEllipse(playerX, playerY, radius, radius, 0.0f, BLUE, kFillModeSolid);
			}
			if (MyColor == 2) {
				//自機
				Novice::DrawEllipse(playerX, playerY, radius, radius, 0.0f, GREEN, kFillModeSolid);
			}
			
				for (int i = 0; i < 9; i++) {
					if (enemyFlag[i] == 1) {
						if (color[i] == 0) {
						    //敵
							Novice::DrawEllipse(enemyX[i], enemyY[i], radius, radius, 0.0f, RED, kFillModeSolid);
						}
						if (color[i] == 1) {
							//敵
							Novice::DrawEllipse(enemyX[i], enemyY[i], radius, radius, 0.0f, BLUE, kFillModeSolid);
						}
						if (color[i] == 2) {
							//敵
							Novice::DrawEllipse(enemyX[i], enemyY[i], radius, radius, 0.0f, GREEN, kFillModeSolid);
						}
					}
				
				}
			
			

			break;
		case SCORE:
			Novice::ScreenPrintf(0, 0, "Score");
			break;
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
