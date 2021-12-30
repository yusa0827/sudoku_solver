#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#ifdef DEBUG_SUDOKU
// #define DEBUG_SUDOKU
#endif

#define SUDOKU_MAX_COL      9
#define SUDOKU_MAX_R0W      9
#define SUDOKU_FIRST_RANGE  2
#define SUDOKU_MIDDLE_RANGE 5
#define SUDOKU_LAST_RANGE   8
#define SUDOKU_SPLIT        3

//数独の解法用のクラス
class SUDOKU_ {

private://表舞台には出てこない変数
	int tate;
	int yoko;
	int sleep_from_class;// 引数から拾ってくる
	bool maybe_fix;//チェッカーに反応したらfalseになってもう一度
	
public://メインで使う変数や関数たち
	
	//数独座標の初期化
	int s[10][10] = { 0 };
	//辞書　数値を文字列に入れる
	std::string s_[10][10];
	//現在のマスが辞書と一致していないかを確認するための変数
	std::string s_tate_yoko_;
	//s[start_tate][start_yoko] = init_value_from_class
	int init_value_from_class;
	//探索スタート位置　辞書と一致した場合は動く
	int start_tate = 1;
	int start_yoko = 1;
	//辞書の数
	int key_num = -1;
	//辞書　辞書とは初期値の定数
	std::string key_[81];//配列の数を求める必要がある
	//s[9][9]まで埋まるとfalse→trueにする
	bool fin_sudoku_switch = false;
	
	//  コンストラクタ スタート位置の値を代入している
	SUDOKU_(uint8_t start_number) {
		init_value_from_class = start_number;
	};
	   	
	//辞書を代入　定数を代入
	void insert_init_(uint8_t init_s[10][10]);
	//辞書作り
	void make_dictionary();
	//表を表示 表示時間は0.2秒
	void display_table(uint8_t sleep_ = 200);
	//初期位置ポジションをクラスに代入した初期値で探査
	void detect_start_position();
	//探査開始　縦、横、各(3*3)エリアをチェック
	void check_row_and_col_and_area();
	//指定した値で全探査
	void start_multi_thread_();
	
	//マルチスレッド関数　初期値Nみの探査を開始
	void MT_nth_single_shot_();//
};

