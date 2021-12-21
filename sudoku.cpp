#include "sudoku.h"


// #ifndef DEBUG_SUDOKU
// #define DEBUG_SUDOKU
// #endif

//初期値をクラスのメンバー変数に代入
void SUDOKU_::insert_init_(uint8_t init_s[10][10]) {
	//横
	for (int j = 1; j <= 9; j++) {
		//縦
		for (int i = 1; i <= 9; i++) {
			//初期値を代入
			if (init_s[j][i] != 0) {
				s[j][i] = init_s[j][i];
			}
		}
	}
}


void SUDOKU_::MT_nth_single_shot_() {

	//探査の初期位置と初期値を代入
	tate = start_tate;
	yoko = start_yoko;
	//クラスに代入した値を初期位置の初期値
	s[tate][yoko] = init_value_from_class;

	for (;;) {
		//数独のルールに違反したらtrue→fALSE
		maybe_fix = true;
		//辞書と照らし合わせるために現在のマスを文字列化
		s_tate_yoko_ = "s[" + std::to_string(tate) + "][" + std::to_string(yoko) + "]";
				
		//現在のマスと辞書が一致するかを確認
		for (int i = 0; i < key_num; i++) {

			//辞書と一致した場合は繰り上げ
			if (s_tate_yoko_ == key_[i]) {

				//s[tate][9]のとき、s[yoko+1][1] 足したときに9だったら、1にする
				++yoko;//横をインクリメント
				if (yoko > 9) {//9=1になったら、1に初期化
					yoko = 1;
					++tate;//縦を1つ進める
				}

				//辞書と一致したため
				maybe_fix = false;
			}

		}

		/* check
		横で一致しないかを確認 一致したら値をインクリメント
		縦で一致しないかを確認 一致したら値をインクリメント
		3*3以内に同じ文字が入っていないかを確認 一致したら値をインクリメント
		*/
		SUDOKU_::check_row_and_col_and_area();

		//現在のマスs[][]が9を超えたら
		if (s[tate][yoko] > 9) {

			//定数の場合は初期化してはいけない
			//--yoko;//1ステップ戻る しかし、定数の場合はさらにスキップするfor分の処理

			maybe_fix = false;//まだあがる可能性があります
			bool jisyo_check = true;

			//現在のマスを初期化
			s[tate][yoko] = 0;

			//繰り下げ
			if (yoko == 1) {//s[tate][1](左端)のとき、下に移動s[tate - 1][9]
				tate = tate - 1;
				yoko = 9;

			}
			else {//隣に移動する
				yoko = yoko - 1;
			}


			//移動したセルが定数だったら、もう一度同じ処理　移動
			int incliment = 0;
			for (;;) {

				//戻った値が文字列であったら、breakする　キー文字列分for分を回す				
				for (int i = 0; i < key_num; i++) {

					//1ステップ戻った値を文字列とする 仮に戻ってみる
					s_tate_yoko_ = "s[" + std::to_string(tate) + "][" + std::to_string(yoko) + "]";

					//　1ステップ戻った値を文字列が定数ではないかをチェックする
					if (s_tate_yoko_ == key_[i]) {
						jisyo_check = false;

						if (yoko == 1) {//s[tate][1]のとき、下に移動s[tate - 1][9]
							tate = tate - 1;
							yoko = 9;
						}
						else {
							yoko = yoko - 1;
						}

						incliment = 0;
						break;//一致したら抜ける
					}

				}

				++incliment;
				// incliment が三回インクリメントしたときに
				if (incliment == 3) {

					++s[tate][yoko];

					maybe_fix = false;//まだあがる可能性があります
					break;//一致したら抜ける
				}

			}

		}
		
		//数独のルールに違反していいなかったらtrue
		if (maybe_fix == true) {

			//違反していなかったときの回数
			static int repeat_times = 0;
			++repeat_times;//インクリメント

			//trueで帰ってきたら、表作成
			if (repeat_times % 1000000 == 0) {
				std::cout << "trail time = " << repeat_times << std::endl;

				std::cout << "init_value_from_class = " << init_value_from_class << std::endl;
				
				//表作成
				SUDOKU_::display_table(sleep_from_class);
							   
			}

			//指定した初期値
			if (s[start_tate][start_yoko] != init_value_from_class) {

				std::cout << "because initial value = " << init_value_from_class << "is not, break." << std::endl;
				break;
			}

			//chekerで全てに該当しなく、すべて埋まったら成功？　終了
			if (yoko == 9 && tate == 9) {
				std::cout <<"initial value = " << init_value_from_class 
					<< "complete sudoku" << std::endl;
				std::cout << "finish sudoku_solver app" << std::endl;
				SUDOKU_::display_table(sleep_from_class);//表作成
				
				fin_sudoku_switch = true;// trueになると、メイン関数を終了させる
				break;
			}

			//隣にスキップする
			++yoko;//s[tate][yoko] → s[tate][yoko + 1]

			if (yoko > 9) {
				++tate;//縦を増やして、
				yoko = 1;//横を初期化

			}

			//スキップしたマスが辞書にあるかを確認
			for (int i = 0; i < key_num; i++) {

				// 辞書のために文字列を初期化
				s_tate_yoko_ = "s[" + std::to_string(tate) + "][" + std::to_string(yoko) + "]";
				//文字列を辞書が一致した場合、横にスキップ
				if (s_tate_yoko_ == key_[i]) {

					++yoko;//横にスキップ
					//最スキップしたマスが9を超えたら次の行の1マス目
					if (yoko > 9) {//9=1になったら、1に初期化
						yoko = 1;
						++tate;//縦を1つ進める

					}

				}

				//定数ではなかった、つまり0だった場合は1にする
				if (s[tate][yoko] == 0) {
					s[tate][yoko] = 1;//次のステップへの初期化　定数の場合は初期化をしてはいけない
				}

			}

		}

	}

}


void SUDOKU_::check_row_and_col_and_area() {

	//check_ 横で一致しないかを確認
	for (int i = 1; i < 10; i++) {
		//同じ配列番号出ないように、まえもってガード
		if (i != yoko) {
			//それでも値が一致した場合はインクリメント
			if (s[tate][yoko] == s[tate][i]) {
				
				++s[tate][yoko];//値をあげる
				maybe_fix = false;//まだあがる可能性があります
			}
		}
	}

	//check_ 縦で一致しないかを確認
	for (int i = 1; i < 10; i++) {
		//同じ配列番号出ないように、まえもってガード
		if (i != tate) {
			//それでも値が一致した場合はインクリメント
			if (s[tate][yoko] == s[i][yoko]) {

				++s[tate][yoko];//値をあげる
				maybe_fix = false;//まだあがる可能性があります
			}
		}
	}

	//check_ 横と縦　スライド範囲（3*3）を探索
	int state_of_yoko;
	int state_of_tate;
	//横　スライド範囲を探索
	if (1 <= yoko && yoko <= 3) {
		state_of_yoko = 1;
	}
	else if (4 <= yoko && yoko <= 6) {
		state_of_yoko = 4;
	}
	else {
		state_of_yoko = 7;
	}
	//縦　スライド範囲を探索
	if (1 <= tate && tate <= 3) {
		state_of_tate = 1;
	}
	else if (4 <= tate && tate <= 6) {
		state_of_tate = 4;
	}
	else {
		state_of_tate = 7;
	}
	//横＊縦スライドで一致しないかをチェック
	for (int i = state_of_tate; i < state_of_tate + 3; i++) {
		for (int j = state_of_yoko; j < state_of_yoko + 3; j++) {

			// 変数の横と縦の座標が一致しないことが条件
			if (i != tate && j != yoko) {

				//座標が一致しなく、値が一致した場合、繰り上げ
				if (s[tate][yoko] == s[i][j]) {

					++s[tate][yoko];//値をあげる
					maybe_fix = false;//まだあがる可能性があります

				}
			}
		}
	}
}


void SUDOKU_::start_multi_thread_() {

	tate = start_tate;
	yoko = start_yoko;
	s[tate][yoko] = init_value_from_class;
	
	for (;;) {


		std::string s_tate_yoko_ = "s[" + std::to_string(tate) + "][" + std::to_string(yoko) + "]";

		//値がこれ以上上がらないことをブールで表現
		maybe_fix = true;//条件という試練に会いながらも、trueで帰ってきたら、break

		//*******************************************************特殊
		//辞書にあるということは、今後の処理をスキップしないといけない
		//check1　辞書型で定数でないかを確認 s[1][1] 
		//辞書と一致した場合、隣に移動する
		for (int i = 0; i < key_num; i++) {

			//　s[1][1]が定数ではないかをチェックする
			if (s_tate_yoko_ == key_[i]) {

				//s[yoko][9]のとき、s[yoko+1][1] 足したときに9だったら、1にする
				++yoko;//横をインクリメント
				if (yoko == 10) {//9=1になったら、1に初期化
					yoko = 1;
					++tate;//縦を1つ進める

				}

				maybe_fix = false;//まだあがる可能性があります
				//break;次の文字も辞書にあるかもしれないので、 breakはしない
			}

		}

		/* check
		横で一致しないかを確認 一致したら値をインクリメント
		縦で一致しないかを確認 一致したら値をインクリメント
		3*3以内に同じ文字が入っていないかを確認 一致したら値をインクリメント
		*/
		SUDOKU_::check_row_and_col_and_area();

		//s[][]に加算するため、下記のフォルスカウンターでは無意味
		if (s[tate][yoko] > 9) {
			
			maybe_fix = false;//まだあがる可能性があります

			bool jisyo_check = true;

			s[tate][yoko] = 0;//①初期化

			//繰り上げ
			if (yoko == 1) {//s[tate][1](左端)のとき、下に移動s[tate - 1][9]
				tate = tate - 1;
				yoko = 9;

			}
			else {//隣に移動する
				yoko = yoko - 1;
			}

			//移動したセルが定数だったら、もう一度同じ処理　移動

			int incliment = 0;
			for (;;) {

				//戻った値が文字列であったら、breakする　キー文字列分for分を回す				
				for (int i = 0; i < key_num; i++) {

					//1ステップ戻った値を文字列とする 仮に戻ってみる
					s_tate_yoko_ = "s[" + std::to_string(tate) + "][" + std::to_string(yoko) + "]";

					//　1ステップ戻った値を文字列が定数ではないかをチェックする
					if (s_tate_yoko_ == key_[i]) {
						jisyo_check = false;


						if (yoko == 1) {//s[tate][1]のとき、下に移動s[tate - 1][9]
							tate = tate - 1;
							yoko = 9;

						}
						else {
							yoko = yoko - 1;
						}

						incliment = 0;
						break;//一致したら抜ける
					}

				}

				++incliment;
				//辞書に引っかからなかったときインクリメント
				if (incliment == 3) {

					++s[tate][yoko];

					maybe_fix = false;//まだあがる可能性があります
					break;//一致したら抜ける
				}

			}

		}


		//変更されずに帰ってきたら、trueとなる
		if (maybe_fix == true) {

			static int repeat_times = 0;//インクリメント
			++repeat_times;

			//trueで帰ってきたら、表作成
			if (repeat_times % 1000000 == 0) {
				std::cout << "trail time = " << repeat_times << std::endl;
				SUDOKU_::display_table(sleep_from_class);//表作成
			}

			//chekerで全てに該当しなく、すべて埋まったら成功？　終了
			if (yoko == 9 && tate == 9) {
				std::cout << "checkerでも問題なく、すべてのマスが埋まりました." << std::endl;
				SUDOKU_::display_table(sleep_from_class);//表作成
				std::cout << "finish sudoku_solver app" << std::endl;
				fin_sudoku_switch = true;// trueになると、メイン関数を終了させる
				break;
			}

			//繰り上げ
			++yoko;//s[tate][yoko] → s[tate][yoko + 1]

			if (yoko > 9) {
				++tate;//縦を増やして、
				yoko = 1;//横を初期化

			}

			//スキップしたマスが辞書にあるかを確認
			for (int i = 0; i < key_num; i++) {

				// 辞書のために文字列を初期化
				s_tate_yoko_ = "s[" + std::to_string(tate) + "][" + std::to_string(yoko) + "]";
				//文字列を辞書が一致した場合、横にスキップ
				if (s_tate_yoko_ == key_[i]) {

					++yoko;//横にスキップ
					//最スキップしたマスが9を超えたら次の行の1マス目
					if (yoko > 9) {//9=1になったら、1に初期化
						yoko = 1;
						++tate;//縦を1つ進める

					}

				}

				//定数ではなかった、つまり0だった場合は1にする
				if (s[tate][yoko] == 0) {
					s[tate][yoko] = 1;//次のステップへの初期化　定数の場合は初期化をしてはいけない
				}

			}

		}

	}

}



//初めに代入できるマスを探す
void SUDOKU_::detect_start_position() {
	
	//init_value_from_class = start_number;
	s[start_tate][start_yoko] = init_value_from_class;

	//初期のs[start_tate][start_yoko]は辞書にあるか無いかで判断する
	for (int i = 0; i < key_num; i++) {
		//現在のマスを文字列
		s_tate_yoko_ = "s[" + std::to_string(start_tate) + "][" + std::to_string(start_yoko) + "]";
		//辞書と一致した場合は繰り上げ
		if (s_tate_yoko_ == key_[i]) {
			//s[tate][yoko] → s[tate][yoko + 1] 
			start_yoko++;
			//s[tate][9] → s[tate + 1][1]
			if (start_yoko > 9) {
				start_yoko = 1;
				start_tate++;
			}			
		}
	}
	
	std::cout << "first position " 
		<< "s[" << start_tate <<"]["<< start_yoko <<"] = " << init_value_from_class << std::endl;

}

//表の表示
void SUDOKU_::display_table(uint8_t sleep_) {
	//クラスのprivate変数に代入
	sleep_from_class = sleep_;
	
	//表用の文字を指定
	std::string space_ = " ";//文字のためのスペース
	std::string vertical_ = "|";//縦線
	std::string horizontal_ = "-";//横線

	std::cout << std::endl;
	//横線
	std::cout << horizontal_ << horizontal_ << horizontal_ << horizontal_ << horizontal_
		<< horizontal_ << horizontal_ << horizontal_ << horizontal_
		<< horizontal_ << horizontal_ << horizontal_ << horizontal_ << std::endl;

	// jが1,2,3と増えると, iが0+1,3+1,6*1
	for (int j = 0; j < 3; j++) {

		//　1から3行目
		for (int i = j * 3 + 1; i < (j + 1) * 3 + 1; i++) {

			// 全て文字列に入れる、なぜなら[　]空白を使いたいから
			//　もし0の値の時は、空欄の文字列を代入する
			for (int k = 1; k <= 9; k++) {

				s_[i][k] = std::to_string(s[i][k]);

				//0だとスペース
				if (s_[i][k] == "0") {
					s_[i][k] = " ";
				}
				//9を超えるとX
				if (s[i][k] > 9) {
					s_[i][k] = "X";
				}

				s_tate_yoko_ = "s[" + std::to_string(i) + "][" + std::to_string(k) + "]";

				//辞書と一致したら、文字の色を変える
				for (int x = 0; x < key_num + 1; x++) {

					//　s[1][1]が定数ではないかをチェックする 
					//　辞書と一致したら
					if (s_tate_yoko_ == key_[x]) {
						
						//辞書と一致したら色を変える
						s_[i][k] = "\033[33m" + s_[i][k] + "\033[0m";
						s_[i][k] = "\033[33m" + s_[i][k] + "\033[0m";
						
					}
				}
			}

			std::cout << vertical_ << s_[i][1] << s_[i][2] << s_[i][3] << vertical_
				<< s_[i][4] << s_[i][5] << s_[i][6] << vertical_
				<< s_[i][7] << s_[i][8] << s_[i][9] << vertical_ << std::endl;

		}

		std::cout << horizontal_ << horizontal_ << horizontal_ << horizontal_ << horizontal_
			<< horizontal_ << horizontal_ << horizontal_ << horizontal_
			<< horizontal_ << horizontal_ << horizontal_ << horizontal_ << std::endl;
	}

	std::cout << std::endl;
	//停止　sleep_[ms]
	Sleep(sleep_);

}

//辞書の作成
void SUDOKU_::make_dictionary() {

	for (int i = 1; i <= 9; i++) {

		for (int j = 1; j <= 9; j++) {

			//初期値の0でなかったら辞書(定数)に保存
			if (s[i][j] != 0) {
				key_[++key_num] = "s[" + std::to_string(i) + "][" + std::to_string(j) + "]";

			}
		}
	}
}

