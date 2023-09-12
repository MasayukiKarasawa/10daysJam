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
	int Playerradius = 64;
	int radius = 64;
	int enemyX[9] = {};
	int enemyY[9] = {};
	int MyColor = 0;
	int Speed = 10;
	int enemySpeed = 5;
	int enemyFlag[9] = {};
	int color[9] = {};
	int GameTimer = 750;
	int GameScore = 0;

   // int Number = GameScore;
	int eachNumber[5] = {};
	
	
	int Clear = Novice::LoadTexture("./Clear.png");
	int TIME = Novice::LoadTexture("./TIME.png");
	int Score = Novice::LoadTexture("./Score.png");
	int NumberSprite = Novice::LoadTexture("./Number.png");

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
			
			eachNumber[0] = GameScore / 10000;
			GameScore = GameScore % 10000;
			eachNumber[1] = GameScore / 1000;
			GameScore = GameScore % 1000;
			eachNumber[2] = GameScore / 100;
			GameScore = GameScore % 100;
			eachNumber[3] = GameScore / 10;
			GameScore = GameScore % 10;
			eachNumber[4] = GameScore / 1;
			GameScore = GameScore % 1;
			//移動
			if (keys[DIK_A]) {
				playerX -= Speed;

			}
			if (keys[DIK_D]) {
				playerX += Speed;
			}
			if (playerX + Playerradius>= 1000) {
				playerX = 1000-Playerradius;
			}
			if (playerX - Playerradius<= 0) {
				playerX = 0+Playerradius;
			}
			//色変更
			if (keys[DIK_LEFT] ) {
				MyColor = 0;
			}
			if (keys[DIK_DOWN] ) {
				MyColor = 1;
			}
			if (keys[DIK_RIGHT] ) {
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

				//当たり判定
				for (int i = 0; i < 9; i++) {
					if (enemyFlag[i] == 1) {
						int dx = abs(playerX - enemyX[i]);
						int dz = abs(playerY - enemyY[i]);
                        if (dx < 90 && dz < 90 && MyColor == 0 && color[i] == 0 ) {
							enemyFlag[i] = 0;
							GameScore += 100;
						}
						if (dx < 90 && dz < 90 && MyColor == 1 && color[i] == 1 ) {
							enemyFlag[i] = 0;
							GameScore += 100;
						}
						if (dx < 90 && dz < 90 && MyColor == 2 && color[i] == 2 ) {
							enemyFlag[i] = 0;
							GameScore += 100;
						}
					}
				}

			
				//ゲームタイマー
				GameTimer -= 1;
				if (GameTimer == 0) {
					number = 3;
				}




			break;
		case SCORE:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 0;
				GameTimer = 750;
				for (int i = 0; i < 9; i++) {
					enemyY[i] = 0;
				}
			}
				
			
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
			Novice::ScreenPrintf(640, 0, "Timer%d",GameTimer);
			Novice::DrawLine(1000, 0, 1000, 720, RED);
			if (MyColor == 0) {
				//自機
				Novice::DrawEllipse(playerX, playerY, Playerradius, Playerradius, 0.0f, RED, kFillModeSolid);
		    }
			if (MyColor == 1) {
				//自機
				Novice::DrawEllipse(playerX, playerY, Playerradius, Playerradius, 0.0f, BLUE, kFillModeSolid);
			}
			if (MyColor == 2) {
				//自機
				Novice::DrawEllipse(playerX, playerY, Playerradius, Playerradius, 0.0f, GREEN, kFillModeSolid);
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
				for (int i = 0; i < 5; i++) {
					Novice::DrawSprite(1000, 380, NumberSprite, 1, 1, 0.0f, WHITE);
				}
				Novice::ScreenPrintf(1000, 0, "TIME");
				Novice::DrawSprite(1000, 0, TIME, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite(1000, 360, Score, 1, 1, 0.0f, WHITE);

			break;
		case SCORE:
			
			Novice::DrawSprite(0, 0, Clear, 1, 1, 0.0f, WHITE);
			
			Novice::DrawSprite(450, 360, Score, 1, 1, 0.0f, WHITE);

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
