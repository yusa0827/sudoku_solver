// test_sudoku_7_class.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <thread>
#include <assert.h>
#include "sudoku.h"
#include "sudoku_block.h"

// #ifndef DEBUG_SUDOKU
// #define DEBUG_SUDOKU_BCLOCK
// #endif


#define TESTCASE_2
// #define DEBUG_MY_B

/*
・数独の辞書数をvector型にする
・クラスをポインタ型にする、使用したらメモリを消去　
・マルチスレッドで2つのスレッドを走らせる
・例えば((1,2),(1,3)(4,5))のように走らせる
・数独での
*/

/*
■ 数独票のエリア定義
                   row
          1 2 3   4 5 6   7 8 9
        + - - - + - - - + - - - +
     1  + block + block + block + 
     2  +   1   +   2   +   3   + 
     3  +       +       +       + 
        + - - - + - - - + - - - +
     4  + block + block + block + 
col  5  +   4   +   5   +   6   + 
     6  +       +       +       + 
        + - - - + - - - + - - - +
     7  + block + block + block + 
     8  +   7   +   8   +   9   + 
     9  +       +       +       + 
        + - - - + - - - + - - - + 

※0は未定と定義しなくてはいけないのでは？
　数独の入力があるときに、0が入力されることはない
　直感的でわかりやすい

■ 解放の方針
・最も入力の数が大きい area から攻める
　制約：同じ数のエリアが重なった時はエリア番号が小さいもの



// 数独入力と数独ブロックの値が一致しているか
*/

int main()
{
	std::cout << "start sudoku solver" << std::endl;

	BLOCK my_b[10];
	BLOCK my_binary[10];

	// TODO : set function of initial parameter
	// input sudoku initial parameter
	int init_s[10][10] = { 0 };

#ifdef TESTCASE_1	
	init_s[1][3] = 3;	init_s[1][7] = 5;	init_s[1][9] = 2;
	init_s[2][1] = 5;	init_s[2][5] = 4;	init_s[2][6] = 9;	init_s[2][7] = 8;	init_s[2][8] = 1;
	init_s[3][9] = 9;
	init_s[4][4] = 1;	init_s[4][6] = 4;
	init_s[5][1] = 7;	init_s[5][5] = 2;	init_s[5][8] = 6;
	init_s[6][2] = 9;	init_s[6][5] = 6;	init_s[6][7] = 7;
	init_s[7][3] = 4;
	init_s[8][1] = 2;	init_s[8][3] = 5;	init_s[8][9] = 8;
	init_s[9][1] = 8;	init_s[9][2] = 3;	init_s[9][5] = 1;	init_s[9][7] = 2;
#endif

#ifdef TESTCASE_2
	init_s[1][8] = 8;
	init_s[1][9] = 7;
	init_s[3][3] = 1;
	init_s[3][4] = 2;
	init_s[3][5] = 3;
	init_s[4][3] = 2;
	init_s[4][6] = 4;
	init_s[5][3] = 3;
	init_s[5][7] = 5;
	init_s[6][4] = 8;
	init_s[6][6] = 5;
	init_s[6][8] = 6;
	init_s[7][5] = 1;
	init_s[7][7] = 3;
	init_s[8][1] = 8;
	init_s[8][6] = 7;
	init_s[9][1] = 6;
#endif

	int block_number = 0;

	int block_area_col = 0;// = NULL;// = 0;
	int block_col = 0; //= NULL;// = 0;
	int block_area_row = 0;// = NULL;// = 0;
	int block_row = 0;// = NULL;// = 0;

	int test_output_block[10][10] = { 0 };	


	// input sudoku initial parameter to block
	for(int i = 1; i <= SUDOKU_MAX_COL; i++){

		for(int j = 1; j <= SUDOKU_MAX_R0W; j++){

			// 数独全体座標のどこのブロック内の座標を取得する
			my_b[0].calculate_division_and_remainder(
				i, &block_area_col, &block_col);

			my_b[0].calculate_division_and_remainder(
				j, &block_area_row, &block_row);

#ifdef DEBUG_MY_B

			std::cout << "block_area_col=" << block_area_col <<std::endl;
			std::cout << "block_area_row=" << block_area_row <<std::endl;
			// std::cout << "block_col=" << block_col <<std::endl;
			std::cout << "block_number=" << block_number <<std::endl;
			std::cout << "block_col=" << block_col << ", i=" << i <<std::endl;
			std::cout << "block_row=" << block_row << ", j=" << j <<std::endl;
			std::cout << std::endl;

#endif

			// 数族全体ざひょうからどこのブロックに属するかを取得する
			block_number = my_b[block_number].get_block_number_on_table(i, j) ;
			my_b[block_number].block[block_col][block_row] = init_s[i][j];

#ifdef DEBUG_MY_B
			std::cout << "block_number=" << block_number <<std::endl;
			std::cout << "my_b[ " << block_number << "].block[" << block_row <<"][" << block_col<< "]=" 
			<< my_b[block_number].block[block_row][block_col] <<std::endl;
#endif

		}

	}

	// 入力の数独表の表示
	std::cout << "++++++++++++++"  << std::endl;
	for(int i = 1; i <= 9; i++){
		std::cout << "+" ;
		for(int j = 1; j <= 9; j++){
			// 出力するときは+1して出力補正する
			std::cout << init_s[i][j];
			// 3で割ったあまりが2のときに + で区切る
			int block_area_row  = j / SUDOKU_SPLIT ;
			int block_row = j - SUDOKU_SPLIT * block_area_row;

			if(0 == block_row){
				std::cout << "+" ;
			}
		}
		std::cout <<std::endl;
		// 3で割ったあまりが2のときに + で区切る
		int block_area_row  = i / SUDOKU_SPLIT ;
		int block_row = i - SUDOKU_SPLIT * block_area_row;
		if(0 == block_row){
			std::cout << "++++++++++++++"  << std::endl;
		}
	}


	//　数独 単独 block を表示させる
	for(int i = 1; i <= 9 ; i++){
		for(int j = 1; j <= 9 ; j++){
			// block 1
			if((i <= 3) && (j <= 3)){
				int block_number = 1;
				std::cout << my_b[block_number].block[i][j];
				// 3で割ったあまりが2のときに + で区切る
				int block_area_row  = j / SUDOKU_SPLIT ;
				int block_row = j - SUDOKU_SPLIT * block_area_row;
				if(0 == block_row){
					std::cout <<  std::endl;
				}
			}
		}
	}
	std::cout << "++++++++++++++"  << std::endl;





	//　数独 複数 block (数独表) を表示させる
	block_number = 0;
	for(int i = 1; i <= 9 ; i++){
		std::cout <<  "+" ;
		for(int j = 1; j <= 9 ; j++){

			my_b[0].calculate_division_and_remainder(
				i, &block_area_col, &block_col);

			my_b[0].calculate_division_and_remainder(
				j, &block_area_row, &block_row);

			// 数族全体ざひょうからどこのブロックに属するかを取得する
			block_number = my_b[block_number].get_block_number_on_table(i, j) ;

			std::cout << my_b[block_number].block[block_col][block_row];

			// 3で割ったあまりが2のときに + で区切る
			if(3 == block_row){
				std::cout <<  "+" ;//std::endl;
			}
		}
		std::cout <<std::endl;
		// 3で割ったあまりが2のときに + で区切る
		int block_area_row  = i / SUDOKU_SPLIT ;
		int block_row = i - SUDOKU_SPLIT * block_area_row;
		if(0 == block_row){
			std::cout << "++++++++++++++"  << std::endl;
		}
	}

	std::cout << std::endl;

	// 数独 単独 block を表示させる
	my_b[0].show_one_block_table(my_b, block_number);


	//各ナンバーの数を数えて、数が多いナンバーから01で評価する
	// バイナリーテーブルを作成
	/*
	ブロックにおいて、0以外の値があれば、他のバイナリブロックを消す

	例えば、
	ブロック１の（０，０）に
	
	*/


	/*
	縦と横の情報からそのblockが埋まるかを確認する
	1 そのマスが0かを判断
	　　どの数字が埋まっていないかを判定
	
	*/


	// my_b[0].show_one_block_table(my_b, 1);

	/*
	バイナリー表を作成する
	番号1~9まで調査する
	ブロック番号から攻める

	+++++
	+003+
	+500+
	+000+
	+++++
	*/
	std::cout << std::endl;
	for(int block_number = 1; block_number <= 9; block_number++){

		for(int i = 1; i <= 3; i++){

			for(int j = 1; j <= 3; j++){

				// ブロック内の座標の値
				int number_in_block = my_b[block_number].block[i][j];

				// 0 でなかったらバイナリー埋め
				if(number_in_block){

					if(number_in_block == 5){
						std::cout << "555" << std::endl;
					}


					//1 自分のブロックの値のバイナリを変換する
					for(int i = 1; i <= 3; i++){
						for(int j = 1; j <= 3; j++){
							my_binary[block_number].block_binary[number_in_block][i][j] = true;
						}
					}

					
					//2 横隣のブロックの値のバイナリを変化する
					std::cout << "block_number=" << block_number 
					<< ", i=" << i << ", j=" << j 
					<< ", my_b[block_number].block[i][j]=" << my_b[block_number].block[i][j] << std::endl;
					
					//2 横方向のブロックの値のバイナリを変化する範囲
					int block_number_shift_horizonal_start = 0;
					int block_number_shift_horizonal_end   = 0;

					if( (1 <= block_number) && (block_number <= 3) ){
						block_number_shift_horizonal_start = 1;
						block_number_shift_horizonal_end   = 3;
					}
					else if( (4 <= block_number) && (block_number <= 6) ){
						block_number_shift_horizonal_start = 4;
						block_number_shift_horizonal_end   = 6;
					}
					else if( (7 <= block_number) && (block_number <= 9) ){
						block_number_shift_horizonal_start = 7;
						block_number_shift_horizonal_end   = 9;
					}

					// 横方向 ブロックを横探査
					for(int block_number_shift = block_number_shift_horizonal_start;
						block_number_shift <= block_number_shift_horizonal_end ;
						block_number_shift++){
						//自分のブロックとシフトブロックが一致していると、変換する必要はないためスルー
						if(block_number == block_number_shift){
							continue;
						}

						for(int j_move = 1; j_move <= 3; j_move++){
							my_binary[block_number_shift].block_binary[number_in_block][i][j_move] = true;
						}

					}

					//3 縦隣のブロックの値のバイナリを変化する
					// std::cout << "block_number=" << block_number <<", i=" << i << ", j=" << j << std::endl;
					// std::cout << my_b[block_number].block[i][j] << std::endl;

					//2 横方向のブロックの値のバイナリを変化する範囲
					int block_number_shift_vertical_start = 0;
					int block_number_shift_vertical_end   = 0;

					if( (1 == block_number) || (4 == block_number) || (7 == block_number) ){
						block_number_shift_vertical_start = 1;
						block_number_shift_vertical_end   = 7;
					}
					else if( (2 == block_number) || (5 == block_number) || (8 == block_number) ){
						block_number_shift_vertical_start = 2;
						block_number_shift_vertical_end   = 8;
					}
					else if( (3 == block_number) || (6 == block_number) || (9 == block_number) ){
						block_number_shift_vertical_start = 3;
						block_number_shift_vertical_end   = 9;
					}

					// assert(block_number_shift_vertical_start > 0);
					// std::cout << "### block_number =" << block_number << std::endl;
					assert( (1 <= block_number) && (block_number <= 9) );

					// 縦方向 ブロックを横探査
					for(int block_number_shift = block_number_shift_vertical_start;	
						block_number_shift <= block_number_shift_vertical_end ; 
						block_number_shift += 3 ) {
						
						//自分のブロックとシフトブロックが一致していると、変換する必要はないためスルー
						if(block_number == block_number_shift){
							continue;
						}

						// std::cout << "## block_number_shift =" << block_number_shift << std::endl;
					
						// block_numberブロックと探査ブロックが一致すると、そのブロックの値のバイナリを変える
						for(int i_move = 1; i_move <= 3; i_move++){
							assert(i > 0);
							// std::cout << "vertical block_number_shift=" << block_number_shift << ", i_move=" << i_move << std::endl;
							my_binary[block_number_shift].block_binary[number_in_block][i_move][j] = true;
						}
					}

				}
				
			}

		}

	}

	
	// ブロック内の値(1~9)を指定
	int number_in_block = 5;
	my_b[0].binary_show_in_one_number_on_table(my_b, my_binary, number_in_block);

	// ブロック内の値(1~9)を指定
	number_in_block = 2;
	my_b[0].binary_show_in_one_number_on_table(my_b, my_binary, number_in_block);

	for(int number_in_block = 1; number_in_block <= 9; number_in_block++){
		// ブロック内の値(1~9)を指定
		// number_in_block = 2;
		my_b[0].binary_show_in_one_number_on_table(my_b, my_binary, number_in_block);

	}


	// バイナリ解析 バイナリブロックの中でtrueが1つのボックスを探す
	number_in_block = 5;

	for(int block_number_shift = 1; block_number_shift <= 9; block_number_shift++){

		int binary_true_result_counter = 0;
		bool binary_true_result_break_switch = false;
		int temporary_i = 0;
		int temporary_j = 0;
		int temporary_number_in_block = 0;


		for(int i = 1; i <= 3; i++){

			for(int j = 1; j <= 3; j++){

				// バイナリブロックの座標がtrue かを判定
				bool binay_rsult = my_binary[block_number_shift].block_binary[number_in_block][i][j];
				
				if(binay_rsult){
					binary_true_result_counter++;
					temporary_i = i;
					temporary_j = j;
					temporary_number_in_block = block_number_shift;
				}

				if(binary_true_result_counter > 1){
					binary_true_result_break_switch = true;
					// continue;
					break;
				}

			}

			if(binary_true_result_break_switch){
				//カウンターが二回目に達した場合
				// continue;
				break;
			}

		}

		if(binary_true_result_break_switch){
			//カウンターが二回目に達した場合
			continue;
		}
		else if(!temporary_number_in_block){
			//初期値に変化なし
			continue;
		}
		else{
			std::cout 
			<< "["<< temporary_i << "][" <<temporary_j 
			<< "]=" << temporary_number_in_block
			<< " block_number_shift=" << block_number_shift;
			std::cout << std::endl;

		}




	}


#ifdef DEBUG_SUDOKU_BCLOCK

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
			std::cout << "start value " << sudoku_i->init_value_from_class
				<< ", finish" << std::endl;
			break;
		}
		if (sudoku_i_1->fin_sudoku_switch == true) {
			std::cout << "start value " << sudoku_i->init_value_from_class
				<< ", finish" << std::endl;
			break;
		}
		if (sudoku_i_2->fin_sudoku_switch == true) {
			std::cout << "start value " << sudoku_i->init_value_from_class
				<< ", finish" << std::endl;
			break;
		}

		delete sudoku_i;//メモリ開放
		delete sudoku_i_1;//メモリ開放
		delete sudoku_i_2;//メモリ開放

	}

#endif

}


