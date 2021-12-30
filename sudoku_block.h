#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

// デバッグログ
template<typename T> void view(T e){std::cout << e << std::endl;}
#define debug(debug_switch, var) if(debug_switch) do{std::cout << #var << " = ";view(var);}while(0)
// how to use
// debug(true, max_counter_except_0);



#ifdef DEBUG_SUDOKU
// #define DEBUG_SUDOKU
#endif

#define BLOCK_SIZE    10
#define BLOCK_MAX_COL  4
#define BLOCK_MAX_ROW  4

//数独の解法用のクラス
class BLOCK {

private://表舞台には出てこない変数
	int tate;
	int yoko;
	int sleep_from_class;// 引数から拾ってくる
	bool maybe_fix;//チェッカーに反応したらfalseになってもう一度
	
public://メインで使う変数や関数たち
	
	//数独座標の初期化
	// uint8_t block[BLOCK_MAX_COL][BLOCK_MAX_ROW];
	int block[BLOCK_MAX_COL][BLOCK_MAX_ROW] = {0};

	//バイナリ情報を取得
	bool block_binary[BLOCK_SIZE][BLOCK_MAX_COL][BLOCK_MAX_ROW] = {false};

	void shwo_block_table(BLOCK my_b);
	void shwo_block_table(int my_b[9][9]);

	void show_one_block_table(BLOCK my_b[], int block_number);

	// ブロック番号の数値のバイナリー表示
	void binary_show_in_one_number_in_one_block(BLOCK my_binary[], int block_number, int number);

	// 数独全体の数値(1~9)のバイナリー表示
	void binary_show_in_one_number_on_table(BLOCK my_b[], BLOCK my_binary[],int number_in_block);

	// バイナリ解析 自分のエリアのブロックをtrue
	void binary_analyz_set_own_area_block();

	// バイナリ解析 水平方向に対するバイナリをtrue
	void binary_analyz_set_horizonl();

	// バイナリ解析 水平方向に対するバイナリをtrue
	void binary_analyz_set_vertical();


	// block 分割するために商と余りを計算
	void calculate_division_and_remainder(
		int input_number, int *division, int *remainder);

	// 数独表全体からどのブロックに属するかを返す
	int get_block_number_on_table(int i, int j);

	// ブロックの中で最も0以外の数字が多い値
	int get_max_numbers_value_in_block_in_blocks(BLOCK my_b[], int block_number);

	// //辞書　数値を文字列に入れる
	// std::string s_[10][10];
	// //現在のマスが辞書と一致していないかを確認するための変数
	// std::string s_tate_yoko_;
	// //s[start_tate][start_yoko] = init_value_from_class
	// int init_value_from_class;
	// //探索スタート位置　辞書と一致した場合は動く
	// int start_tate = 1;
	// int start_yoko = 1;
	// //辞書の数
	// int key_num = -1;
	// //辞書　辞書とは初期値の定数
	// std::string key_[81];//配列の数を求める必要がある
	// //s[9][9]まで埋まるとfalse→trueにする
	// bool fin_sudoku_switch = false;
	
	//  コンストラクタ スタート位置の値を代入している
	BLOCK() {

		// uint8_t block[BLOCK_MAX_COL][BLOCK_MAX_ROW];

		// // block インスタンスの初期化
		// for(int i = 0; i < BLOCK_MAX_COL; i++){
		// 	for(int j = 0; j < BLOCK_MAX_ROW; j++){
		// 		block[i][j] = 0;
		// 		std::cout << "block[i][j]=" << block[i][j] << std::endl;
		// 		std::cout << "i = " << i << ", j = " << j << std::endl;

		// 	}
		// }

		// std::cout << "BLOCK()" << std::endl;

	};
	   	
	//辞書を代入　定数を代入
	// void insert_init_(uint8_t init_s[10][10]);
	// //辞書作り
	// void make_dictionary();
	// //表を表示 表示時間は0.2秒
	// void display_table(uint8_t sleep_ = 200);
	// //初期位置ポジションをクラスに代入した初期値で探査
	// void detect_start_position();
	// //探査開始　縦、横、各(3*3)エリアをチェック
	// void check_row_and_col_and_area();
	// //指定した値で全探査
	// void start_multi_thread_();
	
	// //マルチスレッド関数　初期値Nみの探査を開始
	// void MT_nth_single_shot_();//
};

