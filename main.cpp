#include <Novice.h>

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
	Novice::Initialize(kWindowTitle, 1000, 720);

	int number = 0;
	int playerX = 500;
	int playerY = 600;
	int radius = 64;
	//int color[10] = {};
	int MyColor = 0;



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
			if (keys[DIK_A] ) {
				MyColor = 0;
			}
			if (keys[DIK_S] ) {
				MyColor = 1;
			}
			if (keys[DIK_D] ) {
				MyColor = 2;
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
			Novice::ScreenPrintf(0, 20, "MyColor%d");
			Novice::DrawEllipse(playerX, playerY, radius, radius, 0.0f, WHITE, kFillModeSolid);
			break;
		case SCORE:
			Novice::ScreenPrintf(0, 0, "Score");
			break;
		}
		///
		/// ↓描画処理ここから
		///
	
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
