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
	Novice::Initialize(kWindowTitle, 600, 720);

	int number = 0;




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
			if (keys[DIK_SPACE]) {
				number = 1;
			}
			break;
		case MANUAL:
			if (keys[DIK_SPACE]) {
				number = 2;
			}
			break;
		case GAME:

			break;
		case SCORE:

			break;
		}
		///
		/// ↑更新処理ここまで
		///

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
