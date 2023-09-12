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
	
	//シーン
	int number = 0;

	//自機
	int playerX = 500;
	int playerY = 600;
	int Playerradius = 64;
    int MyColor = 0;
	int Speed = 10;
	int PlayerLife = 3;


	//敵
    int enemyX[9] = {};
	int enemyY[9] = {};
	int radius = 64;
	int enemySpeed = 5;
	int enemyFlag[9] = {};
	int color[9] = {};

	//スコア・タイマー
	//int GameTimer = 1000;
	int GameScore = 0;

	int Title = Novice::LoadTexture("./Title.png");
	int Manual = Novice::LoadTexture("./Manual.png");
	int Stage = Novice::LoadTexture("./Stage.png");
	int Clear = Novice::LoadTexture("./Clear.png");
	int LIFE = Novice::LoadTexture("./LIFE.png");
	int One = Novice::LoadTexture("./1.png");
	int Two = Novice::LoadTexture("./2.png");
	int Three = Novice::LoadTexture("./3.png");
	//int TIME = Novice::LoadTexture("./TIME.png");
	int Score = Novice::LoadTexture("./Score.png");
	int ScoreSprite = Novice::LoadTexture("./number.png");

	int Start = Novice::LoadAudio("./Start.mp3");
	int Sub = Novice::LoadAudio("./Sub.mp3");
	int Main = Novice::LoadAudio("./Main.mp3");
	int Last = Novice::LoadAudio("./Last.mp3");

	//スコア表示
	int eachNumber[5] = {};//各桁の値
	int N = 0;//表示する数字
	int keta = 10000;//桁
	//int TimeNumber[5] = {};
	//int T = 0;
	//int TimeKeta = 10000;

	int musicFlag = 0;
		

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
			

			if (musicFlag == 0) {
					Novice::PlayAudio(Start, 0, 1);
					musicFlag = 1;
			}
			
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 1;
				musicFlag = 0;
				Novice::StopAudio(Start);
				
			}

			
			break;
		case MANUAL:
			
			if (musicFlag == 0) {
				Novice::PlayAudio(Sub,0,1);
				musicFlag = 1;
			}

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 2;
				GameScore = 0;
				PlayerLife = 3;
				for (int i = 0; i < 9; i++) {
					enemyY[i] = 0;
				}
				musicFlag = 0;
				Novice::StopAudio(Sub);

			}

			
			

			break;
		case GAME:
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
						//合ってたら加点
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
						//違ったら減点
						if (dx < 90 && dz < 90 && MyColor == 0 && color[i] != 0) {
							enemyFlag[i] = 0;
							PlayerLife -= 1;
							GameScore -= 10;
						}
						if (dx < 90 && dz < 90 && MyColor == 1 && color[i] != 1) {
							enemyFlag[i] = 0;
							PlayerLife -= 1;
							GameScore -= 10;
						}
						if (dx < 90 && dz < 90 && MyColor == 2 && color[i] != 2) {
							enemyFlag[i] = 0;
							PlayerLife -= 1;
							GameScore -= 10;
						}
					}
				}
				
				if (musicFlag == 0) {
					Novice::PlayAudio(Main, 0, 1);
					musicFlag = 1;
				}

			
				//ゲームタイマー
				//GameTimer -= 1;
				//ライフ
				if (PlayerLife <= 0) {
					number = 3;
					musicFlag = 0;
					Novice::StopAudio(Main);
				}

				

			break;
		case SCORE:
			//初期化

			if (musicFlag == 0) {
				Novice::PlayAudio(Last, 0, 1);
				musicFlag = 1;
			}

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				number = 0;
				//GameTimer = 1000;
				GameScore = 0;
				PlayerLife = 3;
				for (int i = 0; i < 9; i++) {
					enemyY[i] = 0;
				}
				musicFlag = 0;
				Novice::StopAudio(Last);
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
			Novice::DrawSprite(0, 0, Title, 1, 1, 0.0f, WHITE);
			break;
		case MANUAL:
			Novice::DrawSprite(0, 0, Manual, 1, 1, 0.0f, WHITE);
			break;
		case GAME:
            Novice::DrawSprite(0, 0, Stage, 1, 1, 0.0f, WHITE);
			
			//ライフ
		    Novice::DrawSprite(1000, 0, LIFE, 1, 1, 0.0f, WHITE);
			if (PlayerLife == 3) {
				Novice::DrawSprite(1000, 60, Three, 1, 1, 0.0f, WHITE);
			}
			if (PlayerLife == 2) {
				Novice::DrawSprite(1000, 60, Two, 1, 1, 0.0f, WHITE);
			}
			if (PlayerLife == 1) {
				Novice::DrawSprite(1000, 60, One, 1, 1, 0.0f, WHITE);
			}
            //タイマー
			//T = GameTimer;
			//TimeKeta = 10000;
			//for (int i = 0; i < 5; i++) {
			//	TimeNumber[i] = T / TimeKeta;//今の桁の値
			//	T = T % TimeKeta;//次の桁以下の値を取り出す
			//	TimeKeta = TimeKeta / 10;//桁を進める
			//}
			//for (int i = 0; i < 5; i++) {

			//	Novice::DrawQuad(
			//		1000 + i * 26, 30,			// 四角形の左上座標
			//		1032 + i * 26, 30,		// 四角形の右上座標
			//		1000 + i * 26, 94,		// 四角形の左下座標
			//		1032 + i * 26, 94,	// 四角形の右下座標
			//		TimeNumber[i] * 32, 0, // 画像上の描画したい範囲左上座標
			//		32, 64,			// 画像上の描画したい横幅、縦幅
			//		ScoreSprite,			// テクスチャハンドル
			//		0xFFFFFFFF			// 色
			//	);
			//}
			
			//スコア

            Novice::DrawSprite(1000, 360, Score, 1, 1, 0.0f, WHITE); 
		    N = GameScore;//表示する数字
		    keta = 10000;//桁

		    for (int i = 0; i < 5; i++) {
					eachNumber[i] = N / keta;//今の桁の値
					N = N % keta;//次の桁以下の値を取り出す
					keta = keta / 10;//桁を進める
				}
			for (int i = 0; i < 5; i++) {
				
				Novice::DrawQuad(
					1000+ i *26 , 400,			// 四角形の左上座標
					1032 + i * 26, 400,		// 四角形の右上座標
					1000 + i * 26, 464,		// 四角形の左下座標
					1032 + i * 26, 464,	// 四角形の右下座標
					eachNumber[i]*32, 0, // 画像上の描画したい範囲左上座標
					32, 64,			// 画像上の描画したい横幅、縦幅
					ScoreSprite,			// テクスチャハンドル
					0xFFFFFFFF			// 色
				);
			}
				
				
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
				
				
				
			break;
		case SCORE:
			
			Novice::DrawSprite(0, 0, Clear, 1, 1, 0.0f, WHITE);
			
			Novice::DrawSprite(450, 300, Score, 1, 1, 0.0f, WHITE);
			
			for (int i = 0; i < 5; i++) {

				Novice::DrawQuad(
					600 + i * 26, 290,			// 四角形の左上座標
					632 + i * 26, 290,		// 四角形の右上座標
					600 + i * 26, 354,		// 四角形の左下座標
					632 + i * 26, 354,	// 四角形の右下座標
					eachNumber[i] * 32, 0, // 画像上の描画したい範囲左上座標
					32, 64,			// 画像上の描画したい横幅、縦幅
					ScoreSprite,			// テクスチャハンドル
					0xFFFFFFFF			// 色
				);
			}
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
