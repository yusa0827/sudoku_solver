#pragma once
#include string
#include Windows.h

class Sudoku {
	表用の文字を指定
	stdstring space_ =  ;文字のためのスペース
	stdstring vertical_ = ;縦線
	stdstring horizontal_ = -;横線

	33 のインクリメンター
	int inclimenter_3_3 = 0;

	33マスにバツが2個か3この時に発動 ここに行と列の条件によって他ブロックの候補を消去
	int counter_del = 0;
	int counter_tate_yoko = 0;


	 special_delete 用の変数
	int save_tate_ = 0;
	int save_yoko_ = 0;
	int start_1_tate = 0;初期化プール用のスタート位置
	int start_2_tate = 0;初期化プール用のスタート位置
	int start_1_yoko = 0;初期化プール用のスタート位置
	int start_2_yoko = 0;初期化プール用のスタート位置



public
	数独　数値
	int s[10][10] = { 0 };
	数独　文字列
	stdstring s_str[10][10];
	各ナンバー　bool_num_[縦][横][指定文字] 1に初期化
	bool bool_num_[10][10][10];
	bool bool_num_cover[10][10][10];再度、解くように仮保存
	特徴量マップ用変数
	int f_map[10][10];
	int f_map_sum = 0;

	1 数独を初期化
	void _1_1_initailize_bool_num_3N_and_feature_map_2N();
	2 特定の数値における 0と1　処理  
	void _2_Nth_0_1_checker(int number_);

	特別な処理　
	3 33エリア内に縦・横のみに1がある場合に他の縦・横を消去	 
	void _2_4_special_delete_ver2(int number_);
	int one_counter_in_3_3 = 0;
	int row_or_col_counter = 0;

	それぞれの特徴量マップの33のマスの中に1があったら定数に変化 5 
	void _2_5_change_1_to_number_in_3_3_blocks(int number_);

	4 3次元的な特徴を2次元的な特徴に落とし込む 
	void _4_decliment_3N_to_2N();

	全体の特徴量マップの中に1があったら定数に変化 6 
	void find_1_in_each_f_map();
	   	 
	数独のはじめの表 7 
	void sudoku_table_first(); 

	数独の最後
	void sudoku_table_end();

	解析コメント数
	int comment_result_num = 0;

	特徴マップを表示させる関数
	void f_map_table();

	数字が聞いている範囲を特徴をマップ化する
	void number_working_map(int number_);
	stdstring num_working[10][10][10];

	数字が聞いている範囲を特徴をマップを初期化
	void _1_2_num_working_map_initialize();


	数字被り　定数と一致した場合
	void _2_1_Nth_0_1_checker_1_TEISU(int number_);

	数字被り　33エリアに特定の数字が存在した場合
	void _2_2_Nth_0_1_checker_2_area_3_3(int number_);

	数字被り　数字がある列と行は0にする
	void _2_3_Nth_0_1_checker_3_row_col_3_3(int number_);
	int _2_3_Nth_0_1_checker_3_row_col_3_3_counter = 0;

	細分化しよう


	確定した値を色を変えて数独に代入した表
	void sudoku_table_first_with_paint();
	
	初期化 カバーを表示
	void _2_Nth_0_1_checker_for_cover(int number_);


	もう一度解析するときには値が置き換わっているので、その情報を一時的に保存しておく。
	stdstring num_working_cover[10][10][10];


	special_delete_だと一括で消されてしまう
	そのため細分化させる
	void _3_special_delete_in_detale_overwrite(int number_, int tate_move, int yoko_move);
	bool show_sudoku_table = false;初期値は表を表示させないのでfalse

	なぞ
	void nazo(int number_);
	int keep_tate_move = 0;この変数は初期化する
	int keep_yoko_move= 0 ;


	1から9までの特徴マップを足し合わせた合計値1を確定させる
	void detect_num_from_Fmap();

	なぜそのマスがそのマスの縦と横の数字で決定するのか
	void investigate_num_on_block();
	仮変数ナンバー
	int keep_number_ = 1;


	void find_1_in_each_f_map_one_time();
	int keep_col_row_num_tate = 0;
	int keep_col_row_num_yoko = 0;



	bool bool_find_1_in_each_f_map_one_time;
	bool break_keep_number_;
	int keep_number_array[10] = { 0 };10個準備する


};



-------------
       87
         
  123    
-------------
  2  4   
  3   5  
   8 5 6 
-------------
    1 3  
8    7   
6        
-------------



1 数独を初期化
void Sudoku_1_1_initailize_bool_num_3N_and_feature_map_2N() {

	同時に初期化
	for (int number_ = 1; number_ = 9; number_++) {
		for (int tate_ = 1; tate_ = 9; tate_++) {
			for (int yoko_ = 1; yoko_ = 9; yoko_++) {

				各数字の特徴マップを1にする
				bool_num_[tate_][yoko_][number_] = true;

				再度計算する用
				bool_num_cover[tate_][yoko_][number_] = true;

				特徴特徴マップを初期化　
				f_map[tate_][yoko_] = 0;
			}
		}
	}
}

数字が聞いている範囲を特徴をマップを初期化
void Sudoku_1_2_num_working_map_initialize() {
	同時に初期化
	for (int number_ = 1; number_ = 9; number_++) {
		for (int tate_ = 1; tate_ = 9; tate_++) {
			for (int yoko_ = 1; yoko_ = 9; yoko_++) {
				各数字の特徴マップをその数字にする
				num_working[tate_][yoko_][number_] = stdto_string(number_);
			}
		}
	}
}

void Sudokudetect_num_from_Fmap() {

	数独を初期化 全体の特徴マップの変数を初期化する
	_1_1_initailize_bool_num_3N_and_feature_map_2N();

	解説コメント変数を初期化
	_1_2_num_working_map_initialize();


	各番号において　0と1に分ける　0存在しない　1存在する可能性がある
	for (int number_ = 1; number_ = 9; number_++) {

		N番目の特徴マップ 既存の値とかぶっていたら 0に変更
		sudoku._2_Nth_0_1_checker(number_);

		2_1 定数の場合　  
		_2_1_Nth_0_1_checker_1_TEISU(number_);
		2_2 33エリアにその数字がある場合
		_2_2_Nth_0_1_checker_2_area_3_3(number_);
		2_3 数字がある列と行は0にする
		_2_3_Nth_0_1_checker_3_row_col_3_3(number_);
		2_4 33エリア内に縦・横のみに1がある場合に他の縦・横を消去 
		_2_4_special_delete_ver2(number_);難易度

		それぞれの特徴量マップの33のマスの中に1があったら定数に変化
		この処理で動作を確定させているので、除外する
		_2_5_change_1_to_number_in_3_3_blocks(number_);

	}


	上記の処理をすると上書きされるかもしれない
	特定させて、確定させる処理を除けばいいのではないか・・・
	_4_decliment_3N_to_2N();
	
	初期化　ループに入る前に初期化する
	keep_col_row_num_tate = 1;
	keep_col_row_num_yoko = 1;
	keep_number_ = 1;探査する数字を初期化する
	配列の初期化もしないといけない
	for (int i = 0; i  10; i++) {
		keep_number_array[i] = 0;
	}

	1マス1マス出力さえる処理を行う
	find_1_in_each_f_map_one_time(); ここでbool変数をtrueで返したら、どこに1から9までの値があるのかを調べられる

	しかし、その時の理由を図示しなくてはいけないですね。
	if (bool_find_1_in_each_f_map_one_time == true) {

		簡易探査が1-9まで終わるまではこの処理をする
		break_keep_number_ = false;

		どこにその数字があるのかを調べる
		まだ9まで探査していなかったら、簡易探査を実行
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();
		if (break_keep_number_ == false) investigate_num_on_block();

		上の調査処理で数値がすべて完結したら、以下の「数字が効いている処理」はいらない



		まずは簡易探査ができるかを確認
		次に上記の処理でヒットしなかった数字の特徴マップを再度調べる
		bool break_array = false;配列探査をするかどうか 初期値はしない

		以下の処理をbreak_arrayの条件で実行させる
		for (int num = 1; num = 9; num++) {

			keep_number_array[num] = num;ヒットした数値を記録しておく
			配列とその値が一致していなかったら、探査させる
			if (keep_number_array[num] != num) {
				break_array = true;初期値探査をする必要がある
			}
		}

		if (break_array == true) {初期値探査をする必要がある場合
		
			for (int num = 1; num = 9; num++) {

				keep_number_array[num] = num;ヒットした数値を記録しておく
				配列とその値が一致していなかったら、探査させる
				if (keep_number_array[num] != num) {
					stdcout  num   この数字を調査する必要があります  stdendl;

					ヒットしなかった数値の特徴マップを表示させる、初期化が必要

					解説コメント変数を初期化
					_1_2_num_working_map_initialize();

					数独表に数値がなかった場合に特徴マップを使って、表示させる。

					2_1 定数の場合　  
					_2_1_Nth_0_1_checker_1_TEISU(num);
					number_working_map(num);
					2_2 33エリアにその数字がある場合
					_2_2_Nth_0_1_checker_2_area_3_3(num);
					number_working_map(num);
					2_3 数字がある列と行は0にする
					_2_3_Nth_0_1_checker_3_row_col_3_3(num);
					number_working_map(num);
					2_4 33エリア内に縦・横のみに1がある場合に他の縦・横を消去 
					_2_4_special_delete_ver2(num);難易度
					number_working_map(num);

					
					stdcout  縦マス：  keep_col_row_num_tate   横マス：  keep_col_row_num_yoko
						  は  s[keep_col_row_num_tate][keep_col_row_num_yoko]
						 stdendl;
					stdcout  縦マス：  keep_col_row_num_tate   横マス：  keep_col_row_num_yoko
						  には  num  の数値が縦または横で聞いています  stdendl;



				}

			}
		
		}

		

	}


}


ヒント　答えからの逆算処理
void Sudokuinvestigate_num_on_block() {

	ブレイク変数
	bool break_ = false;
	


	数独の表をまずはプロット
	sudoku_table_first();

	次にそのマスの縦と横から数字を選び出す　
	使える変数 keep_col_row_num_yoko keep_col_row_num_tate s[tate_][yoko_]
	 keep_number_ は検索した文字を保存している
	for (int number_ = keep_number_; number_ = 9; number_++) {

		仮保存させる
		keep_number_ = number_;
		
		縦と横を調べなくてはいけない
		縦固定	 
		for (int yoko_ = 1; yoko_ = 9; yoko_++) {
			0 以外かつ数字のときはその場所を特定
			if (s[keep_col_row_num_tate][yoko_] != 0 && s[keep_col_row_num_tate][yoko_] == number_) {
				stdcout  縦：  keep_col_row_num_tate   横：  yoko_   に  number_   stdendl;
				break_ = true;
			}
		}

		if (break_ == true) {
			keep_number_array[number_] = number_;ヒットした数値を記録しておく
			break_ = false;　
			break;
		}

		縦固定	 
		for (int tate_ = 1; tate_ = 9; tate_++) {
			0 以外かつ数字のときはその場所を特定
			if (s[tate_][keep_col_row_num_yoko] != 0 && s[tate_][keep_col_row_num_yoko] == number_) {
				stdcout  縦：  tate_   横：  keep_col_row_num_yoko   に  number_  stdendl;
				break_ = true;
			}
		}

		if (break_ == true) {
			keep_number_array[number_] = number_;ヒットした数値を記録しておく
			break_ = false;
			break;

		}


	}


	数字がヒットしなかったら、数字が効いている可能性がある
	if (break_ == false) {
		stdcout  数字がヒットしませんでした  stdendl;
	}


	探索する数値をインクリメントする
	keep_number_++;
	if (keep_number_ = 10) {
		stdcout  簡易的な探査は終わりました  stdendl;


		全ての数値がすべて解析されたのかを確認する。
		for (int num = 1; num = 9; num++) {

			keep_number_array[num] = num;ヒットした数値を記録しておく
			配列とその値が一致していなかったら、探査させる
			if (keep_number_array[num] != num) {
				stdcout  num   この数字を調査する必要があります  stdendl;
			}
		}


		stdcout  ヒットしなかった数値を解析します  stdendl;



		処理を抜ける
		break_keep_number_ = true;

		keep_number_用の配列を準備する　初期値0

	}

}


数値が効いている範囲を表示
void Sudokunumber_working_map(int number_) {

	　まず全体的に  を記入する

	横線
	stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;




	 jが1,2,3と増えると, iが0+1,3+1,61
	for (int j = 0; j  3; j++) {
		　1から3行目
		for (int tate_ = j  3 + 1; tate_  (j + 1)  3 + 1; tate_++) {
			　もし0の値の時は、[　]空白を文字列に代入する

			stdcout  vertical_  num_working[tate_][1][number_]  num_working[tate_][2][number_]  num_working[tate_][3][number_]  vertical_
				 num_working[tate_][4][number_]  num_working[tate_][5][number_]  num_working[tate_][6][number_]  vertical_
				 num_working[tate_][7][number_]  num_working[tate_][8][number_]  num_working[tate_][9][number_]  vertical_  stdendl;

		}

		stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;
	}



}


基本的にはsign　が代入される
void Sudoku_2_1_Nth_0_1_checker_1_TEISU(int number_) {

	for (int tate_ = 1; tate_ = 9; tate_++) {
		for (int yoko_ = 1; yoko_ = 9; yoko_++) {

			0 以外かつ特定番号1以外のとき
			if (s[tate_][yoko_] != 0 && s[tate_][yoko_] != number_) {
				bool_num_[tate_][yoko_][number_] = false;
				stdcout  特徴マップ　定数を消去　数：  number_  stdendl;

				候補を消す
				num_working[tate_][yoko_][number_] = @;
			}
		}
	}
}

void Sudoku_2_2_Nth_0_1_checker_2_area_3_3(int number_) {

	for (int tate_ = 1; tate_ = 9; tate_++) {
		for (int yoko_ = 1; yoko_ = 9; yoko_++) {


			特定の33エリアに特定の数値があった場合
			if (s[tate_][yoko_] == number_) {
				スタート範囲
				int start_tate;
				int start_yoko;

				縦のエリアを探索
				if (1 = tate_ && tate_ = 3) {
					start_tate = 1;
				}
				else if (4 = tate_ && tate_ = 6) {
					start_tate = 4;
				}
				else {
					start_tate = 7;
				}
				横のエリアを探索
				if (1 = yoko_ && yoko_ = 3) {
					start_yoko = 1;
				}
				else if (4 = yoko_ && yoko_ = 6) {
					start_yoko = 4;
				}
				else {
					start_yoko = 7;
				}

				エリアに加算する
				for (int i_ = start_tate; i_  start_tate + 3; i_++) {
					for (int j_ = start_yoko; j_  start_yoko + 3; j_++) {
						bool_num_[i_][j_][number_] = false;0にする


						stdcout  特徴マップ　33エリアを消去　数：  number_  stdendl;

						特定の33エリアに特定の数値があった場合、候補を消す
						num_working[i_][j_][number_] = ;
						stdcout  num_working[i_][j_]  stdendl;



					}
				}
			}

		}
	}

}

void Sudoku_2_3_Nth_0_1_checker_3_row_col_3_3(int number_) {

	for (int tate_ = 1; tate_ = 9; tate_++) {
		for (int yoko_ = 1; yoko_ = 9; yoko_++) {

			特定の値の列、行
			if (s[tate_][yoko_] == number_) {
				行　横
				for (int row = 1; row = 9; row++) {
					bool_num_[tate_][row][number_] = false;


					横の候補を消す
					num_working[tate_][row][number_] = +;
				}

				列　縦
				for (int col = 1; col = 9; col++) {
					bool_num_[col][yoko_][number_] = false;

					縦の候補を消す
					num_working[col][yoko_][number_] = +;
				}
			}
		}
	}

}
void Sudoku_2_4_special_delete_ver2(int number_) {

	この処理を何回やったのかをカウント
	_2_3_Nth_0_1_checker_3_row_col_3_3_counter = 0;

	for (int tate_move = 0; tate_move  3; tate_move++) {

		for (int yoko_move = 0; yoko_move  3; yoko_move++) {

			one_counter_in_3_3 = 0;
			 tate=4-6 yoko=4-6 のtrueをカウント 
			for (int tate_ = tate_move  3 + 1; tate_ = tate_move  3 + 3; tate_++) {int tate_ = 4; tate_ = 6; tate_++
				for (int yoko_ = yoko_move  3 + 1; yoko_ = yoko_move  3 + 3; yoko_++) {
					if (bool_num_[tate_][yoko_][number_] == true) {
						one_counter_in_3_3++;33の加算数
					}
				}
			}

			row_or_col_counter = 0;

			33の加算数が3または2のとき
			↓
			これは33エリア内に縦か横に数値が連なっていたら、それに対応した縦か横を相殺する
			if (one_counter_in_3_3 == 3  one_counter_in_3_3 == 2) {
				 tate固定
				for (int tate_ = tate_move  3 + 1; tate_ = tate_move  3 + 3; tate_++) {
					row_or_col_counter = 0;この初期化が組まれていないかもしてない
					for (int yoko_ = yoko_move  3 + 1; yoko_ = yoko_move  3 + 3; yoko_++) {
						if (bool_num_[tate_][yoko_][number_] == true) {
							row_or_col_counter++;
						}
						save_yoko_ = yoko_;
					}

					if (save_yoko_ == 3) {
						start_1_yoko = 4;
						start_2_yoko = 7;
					}
					if (save_yoko_ == 6) {
						start_1_yoko = 1;
						start_2_yoko = 7;
					}
					if (save_yoko_ == 9) {
						start_1_yoko = 1;
						start_2_yoko = 4;
					}

					if (one_counter_in_3_3 == row_or_col_counter) {

						3のうちの対象ブロックを除いた1つ
						for (int yoko1 = start_1_yoko; yoko1 = start_1_yoko + 2; yoko1++) {
							bool_num_[tate_][yoko1][number_] = false;

							横の候補を消す
							num_working[tate_][yoko1][number_] = -;
						}

						3のうちの対象ブロックを除いた1つ
						for (int yoko1 = start_2_yoko; yoko1 = start_2_yoko + 2; yoko1++) {
							bool_num_[tate_][yoko1][number_] = false;
							
							横の候補を消す
							num_working[tate_][yoko1][number_] = -;
						}


						この処理を何回やったのかをカウント
						_2_3_Nth_0_1_checker_3_row_col_3_3_counter++;

					}
				}


				for (int yoko_ = yoko_move  3 + 1; yoko_ = yoko_move  3 + 3; yoko_++) {
					row_or_col_counter = 0;この初期化が組まれていないかもしてない
					for (int tate_ = tate_move  3 + 1; tate_ = tate_move  3 + 3; tate_++) {
						if (bool_num_[tate_][yoko_][number_] == true) {
							row_or_col_counter++;
						}
						save_tate_ = tate_;
					}

					if (one_counter_in_3_3 == row_or_col_counter) {

						if (save_tate_ == 3) {
							start_1_tate = 4;
							start_2_tate = 7;
						}
						if (save_tate_ == 6) {
							start_1_tate = 1;
							start_2_yoko = 7;
						}
						if (save_tate_ == 9) {
							start_1_tate = 1;
							start_2_yoko = 4;
						}

						3のうちの対象ブロックを除いた1つ
						for (int tate1 = start_1_tate; tate1 = start_1_tate + 2; tate1++) {
							bool_num_[tate1][yoko_][number_] = false;

							縦の候補を消す
							num_working[tate1][yoko_][number_] = ;
						}

						3のうちの対象ブロックを除いた1つ
						for (int tate1 = start_2_yoko; tate1 = start_2_yoko + 2; tate1++) {
							bool_num_[tate1][yoko_][number_] = false;

							縦の候補を消す
							num_working[tate1][yoko_][number_] = ;
						}


						この処理を何回やったのかをカウント
						_2_3_Nth_0_1_checker_3_row_col_3_3_counter++;

					}
				}
			}
		}
	}
}


33ブロックに数字が一個だったら定数に変化
void Sudoku_2_5_change_1_to_number_in_3_3_blocks(int number_) {

	確定数値の個数
	comment_result_num = 0;

	for (int tate_tate = 0; tate_tate  3; tate_tate++) {
		for (int yoko_yoko = 0; yoko_yoko  3; yoko_yoko++) {

			左ブロック目 33 を走査
			inclimenter_3_3 = 0;
			for (int tate_ = tate_tate  3 + 1; tate_ = tate_tate  3 + 3; tate_++) {
				for (int yoko_ = yoko_yoko  3 + 1; yoko_ = yoko_yoko  3 + 3; yoko_++) {
					if (bool_num_[tate_][yoko_][number_] == true) {

						++inclimenter_3_3;
						save_tate_ = tate_;
						save_yoko_ = yoko_;

					}
				}
			}


			33ブロックでインクリメント1のときに確定　座標を確保
			if (inclimenter_3_3 == 1) {
							   
				数独の数値が確定
				s[save_tate_][save_yoko_] = number_;

				確定した数値を表記
				num_working[save_tate_][save_yoko_][number_] =  ;

				確定数値の個数
				comment_result_num++;

			}

		}
	}

	確定数値の個数が1個以上の時
	if (comment_result_num  0) {

	}

}

void Sudoku_4_decliment_3N_to_2N() {

	f_map_sum = 0;

	for (int number_ = 1; number_ = 9; number_++) {
		for (int tate_ = 1; tate_ = 9; tate_++) {
			for (int yoko_ = 1; yoko_ = 9; yoko_++) {
				trueはチェックを潜り抜けた生き残り
				if (bool_num_[tate_][yoko_][number_] == true) {
					f_map[tate_][yoko_]++;
					全体の特徴マップの和が0だとブレイク
					f_map_sum++;
				}
			}
		}
	}

}

全体の特徴マップの中で値が1だったら定数に変換 
void Sudokufind_1_in_each_f_map() {

	comment_result_num = 0;

	数字が一個見つかったらループを抜ける
	find_1_in_each_f_map_bool = false;

	for (int tate_ = 1; tate_ = 9; tate_++) {
		for (int yoko_ = 1; yoko_ = 9; yoko_++) {


			特徴マップで1のときにその値しか入らない
			if (f_map[tate_][yoko_] == 1) {


				その1はどこの数値かを調べる
				for (int number_ = 1; number_ = 9; number_++) {
					みつけたら、それを定数化する
					if (bool_num_[tate_][yoko_][number_] == true) {

						数独の数値を代入
						s[tate_][yoko_] = number_;


						stdcout  tate_=  tate_   yoko_=  yoko_   number_=  number_  stdendl;

						comment_result_num++;

						int tate_, intyoko_, int number_ 
						investigate_num_on_block();

						なぜこのマスに値が代入されるのかを再度調査する関数を作成

					}
				}



			}
		}
	}

	stdcout  comment_result_num =   comment_result_num  stdendl;

}

void Sudokufind_1_in_each_f_map_one_time() {

	bool_find_1_in_each_f_map_one_time = false;

	comment_result_num = 0;


	bool detect_num = false;

	for (int tate_ = keep_col_row_num_tate; tate_ = 9; tate_++) {
		for (int yoko_ = keep_col_row_num_yoko; yoko_ = 9; yoko_++) {

			仮保存
			keep_col_row_num_tate = tate_;
			keep_col_row_num_yoko = yoko_;

			特徴マップで1のときにその値しか入らない
			if (f_map[tate_][yoko_] == 1) {

				その1はどこの数値かを調べる
				for (int number_ = 1; number_ = 9; number_++) {
					みつけたら、それを定数化する
					if (bool_num_[tate_][yoko_][number_] == true) {

						数独の数値を代入
						s[tate_][yoko_] = number_;


						stdcout  tate_=  tate_   yoko_=  yoko_   number_=  number_  stdendl;

						comment_result_num++;

						回答を見つけられたら、その場所を特定する
						bool_find_1_in_each_f_map_one_time = true;


						detect_num = true;

						なぜこのマスに値が代入されるのかを再度調査する関数を作成

					}


					if (detect_num == true) {
						break;
					}


				}


				if (detect_num == true) {
					break;
				}

			}


			if (detect_num == true) {
				break;
			}

		}




		if (detect_num == true) {
			break;
		}
		else {

			でなかったら初期化してあげる
			keep_col_row_num_yoko = 0;

		}


		keep_col_row_num_yoko++;

		if (keep_col_row_num_yoko  10) {
			keep_col_row_num_yoko = 1;
			keep_col_row_num_tate = 0;

		}


	}

	stdcout  comment_result_num =   comment_result_num  stdendl;




	なぜそのマスの値が決定されるのかを調査する
	investigate_num_on_block();
	investigate_num_on_block();

}


特徴マップを表示させる関数
void Sudokuf_map_table() {

	stdcout  stdendl;
	横線
	stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;


	 jが1,2,3と増えると, iが0+1,3+1,61
	for (int j = 0; j  3; j++) {
		　1から3行目
		for (int tate_ = j  3 + 1; tate_  (j + 1)  3 + 1; tate_++) {
			　もし0の値の時は、[　]空白を文字列に代入する
			for (int yoko_ = 1; yoko_ = 9; yoko_++) {

				s_str[tate_][yoko_] = stdto_string(s[tate_][yoko_]);
				0だとスペース
				if (s[tate_][yoko_] == 0) {
					s_str[tate_][yoko_] =  ;
				}

			}

			stdcout  vertical_  s_str[tate_][1]  s_str[tate_][2]  s_str[tate_][3]  vertical_
				 s_str[tate_][4]  s_str[tate_][5]  s_str[tate_][6]  vertical_
				 s_str[tate_][7]  s_str[tate_][8]  s_str[tate_][9]  vertical_  stdendl;

		}

		stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;
	}



}

全体の特徴マップの変数を初期化する
void Sudokusudoku_table_first() {

	stdcout  stdendl;
	横線
	stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;


	 jが1,2,3と増えると, iが0+1,3+1,61
	for (int j = 0; j  3; j++) {
		　1から3行目
		for (int tate_ = j  3 + 1; tate_  (j + 1)  3 + 1; tate_++) {
			　もし0の値の時は、[　]空白を文字列に代入する
			for (int yoko_ = 1; yoko_ = 9; yoko_++) {

				s_str[tate_][yoko_] = stdto_string(s[tate_][yoko_]);
				0だとスペース
				if (s[tate_][yoko_] == 0) {
					s_str[tate_][yoko_] =  ;
				}

			}

			stdcout  vertical_  s_str[tate_][1]  s_str[tate_][2]  s_str[tate_][3]  vertical_
				 s_str[tate_][4]  s_str[tate_][5]  s_str[tate_][6]  vertical_
				 s_str[tate_][7]  s_str[tate_][8]  s_str[tate_][9]  vertical_  stdendl;

		}

		stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;
	}
}

最後に表示させる 解析結果が不十分だったら、不十分と表示させる
void Sudokusudoku_table_end() {

	stdcout  stdendl;
	横線
	stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_
		 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;


	 jが1,2,3と増えると, iが0+1,3+1,61
	for (int j = 0; j  3; j++) {
		　1から3行目
		for (int tate_ = j  3 + 1; tate_  (j + 1)  3 + 1; tate_++) {
			　もし0の値の時は、[　]空白を文字列に代入する
			for (int yoko_ = 1; yoko_ = 9; yoko_++) {

				s_str[tate_][yoko_] = stdto_string(s[tate_][yoko_]);
				0だとスペース
				if (s[tate_][yoko_] == 0) {
					s_str[tate_][yoko_] =  ;


					解析が不十分でした
					stdstring out = 解析が不十分でした;
					stdcout  out  stdendl;


				}

			}

			stdcout  vertical_  s_str[tate_][1]  s_str[tate_][2]  s_str[tate_][3]  vertical_
				 s_str[tate_][4]  s_str[tate_][5]  s_str[tate_][6]  vertical_
				 s_str[tate_][7]  s_str[tate_][8]  s_str[tate_][9]  vertical_  stdendl;

		}

		stdcout  horizontal_  horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_
			 horizontal_  horizontal_  horizontal_  horizontal_  stdendl;
	}
}