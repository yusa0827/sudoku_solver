// test_sudoku_7_class.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <thread>
#include "sudoku.h"

// #ifndef DEBUG_SUDOKU
// #define DEBUG_SUDOKU
// #endif

/*
・数独の辞書数をvector型にする
・クラスをポインタ型にする、使用したらメモリを消去　
・マルチスレッドで2つのスレッドを走らせる
・例えば((1,2),(1,3)(4,5))のように走らせる
・数独での
*/

int main()
{
	std::cout << "start sudoku solver" << std::endl;

#ifdef DEBUG_SUDOKU

	//初期化
	uint8_t init_s[10][10] = { 0 };
	//初期化 辞書_1
	//init_s[1][8] = 8;
	//init_s[1][9] = 7;
	//init_s[3][3] = 1;
	//init_s[3][4] = 2;
	//init_s[3][5] = 3;
	//init_s[4][3] = 2;
	//init_s[4][6] = 4;
	//init_s[5][3] = 3;
	//init_s[5][7] = 5;
	//init_s[6][4] = 8;
	//init_s[6][6] = 5;
	//init_s[6][8] = 6;
	//init_s[7][5] = 1;
	//init_s[7][7] = 3;
	//init_s[8][1] = 8;
	//init_s[8][6] = 7;
	//init_s[9][1] = 6;

	//初期化 辞書_2
	//init_s[1][8] = 1;
	//init_s[2][1] = 4;
	//init_s[3][2] = 2;
	//init_s[4][5] = 5;
	//init_s[4][7] = 4;
	//init_s[4][9] = 7;
	//init_s[5][3] = 8;
	//init_s[5][7] = 3;
	//init_s[6][3] = 1;
	//init_s[6][5] = 9;
	//init_s[7][1] = 3;
	//init_s[7][4] = 4;
	//init_s[7][7] = 2;
	//init_s[8][2] = 5;
	//init_s[8][4] = 1;
	//init_s[9][4] = 8;
	//init_s[9][6] = 6;

	//初期化 辞書_2
	init_s[1][3] = 3;
	init_s[1][7] = 5;
	init_s[1][9] = 2;

	init_s[2][1] = 5;
	init_s[2][5] = 4;
	init_s[2][6] = 9;
	init_s[2][7] = 8;
	init_s[2][8] = 1;

	init_s[3][9] = 9;

	init_s[4][4] = 1;
	init_s[4][6] = 4;

	init_s[5][1] = 7;
	init_s[5][5] = 2;
	init_s[5][8] = 6;

	init_s[6][2] = 9;
	init_s[6][5] = 6;
	init_s[6][7] = 7;

	init_s[7][3] = 4;

	init_s[8][1] = 2;
	init_s[8][3] = 5;
	init_s[8][9] = 8;

	init_s[9][1] = 8;
	init_s[9][2] = 3;
	init_s[9][5] = 1;
	init_s[9][7] = 2;


	for (int i = 0; i < 4; i++) {

		//動的メモリでオブジェクトを生成　スタート値 = 1
		SUDOKU_* sudoku_i = new SUDOKU_(i * 3 + 1);
		//初期値をクラスのオブジェクトに代入
		sudoku_i->insert_init_(init_s);
		//初期値により表を作成
		sudoku_i->make_dictionary();
		//表を表示
		sudoku_i->display_table();
		//探査の初期位置ポジション
		sudoku_i->detect_start_position();
		//探査を開始する マルチスレッド
		//sudoku_i->MT_nth_single_shot_();
		std::thread MT_1(&SUDOKU_::MT_nth_single_shot_, *sudoku_i);


		//動的メモリでオブジェクトを生成　スタート値 = 1
		SUDOKU_* sudoku_i_1 = new SUDOKU_(i * 3 + 2);
		//初期値をクラスのオブジェクトに代入
		sudoku_i_1->insert_init_(init_s);
		//初期値により表を作成
		sudoku_i_1->make_dictionary();
		//表を表示
		sudoku_i_1->display_table();
		//探査の初期位置ポジション
		sudoku_i_1->detect_start_position();
		//探査を開始する マルチスレッド
		//sudoku_i_1->MT_nth_single_shot_();
		std::thread MT_2(&SUDOKU_::MT_nth_single_shot_, *sudoku_i_1);



		//メインスレッド
		//動的メモリでオブジェクトを生成　スタート値 = 1
		SUDOKU_* sudoku_i_2 = new SUDOKU_(i * 3 + 3);
		//初期値をクラスのオブジェクトに代入
		sudoku_i_2->insert_init_(init_s);
		//初期値により表を作成
		sudoku_i_2->make_dictionary();
		//表を表示
		sudoku_i_2->display_table();
		//探査の初期位置ポジション
		sudoku_i_2->detect_start_position();
		//探査を開始する マルチスレッド
		sudoku_i_2->MT_nth_single_shot_();//ここで処理をストッパーしている


		MT_1.join();//同期、待ち 上の処理が終わっても、MT_1が始まるのを待っている
		MT_2.join();//同期、待ち




		//開放される前にすべてのマスを受け取ったらブレイクする
		if (sudoku_i->fin_sudoku_switch == true) {
			std::cout << "スタート値 " << sudoku_i->init_value_from_class
				<< "で終了です。" << std::endl;
			break;
		}
		if (sudoku_i_1->fin_sudoku_switch == true) {
			std::cout << "スタート値 " << sudoku_i->init_value_from_class
				<< "で終了です。" << std::endl;
			break;
		}
		if (sudoku_i_2->fin_sudoku_switch == true) {
			std::cout << "スタート値 " << sudoku_i->init_value_from_class
				<< "で終了です。" << std::endl;
			break;
		}

		delete sudoku_i;//メモリ開放
		delete sudoku_i_1;//メモリ開放
		delete sudoku_i_2;//メモリ開放

	}

#endif

}


