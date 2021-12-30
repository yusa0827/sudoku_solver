#include <assert.h>

#include "sudoku.h"
#include "sudoku_block.h"


// block 単独表示
void BLOCK::shwo_block_table(BLOCK my_b){
    //　数独 単独 block を表示させる
	for(int i = 0; i < 9 ; i++){
		for(int j = 0; j < 9 ; j++){
			// block 1
			if((i <= 2) && (j <= 2)){
				int block_number = 0;
				std::cout << my_b.block[i][j];
				// 3で割ったあまりが2のときに + で区切る
				int block_area_row  = j / SUDOKU_SPLIT ;
				int block_row = j - SUDOKU_SPLIT * block_area_row;
				if(2 == block_row){
					std::cout <<  std::endl;
				}
			}
		}
	}
}


// block 単独表示
void BLOCK::shwo_block_table(int my_b[9][9]){
    //　数独 単独 block を表示させる
	for(int i = 0; i < 9 ; i++){
		for(int j = 0; j < 9 ; j++){
			// block 1
			if((i <= 2) && (j <= 2)){
				int block_number = 0;
				std::cout << my_b[i][j];
				// 3で割ったあまりが2のときに + で区切る
				int block_area_row  = j / SUDOKU_SPLIT ;
				int block_row = j - SUDOKU_SPLIT * block_area_row;
				if(2 == block_row){
					std::cout <<  std::endl;
				}
			}
		}
	}
}


void BLOCK::show_one_block_table(BLOCK my_b[], int block_number){
	//　数独 単独 block を表示させる
	std::cout << "+++++++++++++"  << std::endl;
	std::cout << "show_one_block_table block_number()" << std::endl;
	std::cout << "block_number = " << block_number  << std::endl;
	std::cout << "+++++++++++++"  << std::endl;

	std::cout << "show_one_block_table block_number = " << block_number  << std::endl;
	std::cout << "+++++"  << std::endl;
	for(int i = 1; i <= 3 ; i++){
		std::cout << "+";
		for(int j = 1; j <= 3 ; j++){
			std::cout << my_b[block_number].block[i][j];
		}
		std::cout << "+";
		std::cout <<  std::endl;
	}
	std::cout << "+++++"  << std::endl;
};



void BLOCK::calculate_division_and_remainder(int input_number, int *division, int *remainder){
	// 計算 商と余り
	// 14 = 3 * 4 + 2
	// 14 / 3 = 4 ... 2  
	// 14 - 3 * 4 = 2 
	//  2 = 3 * 0 + 2 
	//  2 - 3* 0 = 2

    *division  = input_number / SUDOKU_SPLIT ;
    *remainder = input_number - SUDOKU_SPLIT * (*division);
    if(0 == *remainder){
        *remainder = 3;
    }
}


int BLOCK::get_block_number_on_table(int i, int j){
    int block_number;
    // 商の値と、余りでブロック分類する
    if( ( (1 <= i) && (i <= 3) ) && ( (1 <= j) && (j <= 3) ) ){
        block_number = 1;
    }
    else if( ( (1 <= i) && (i <= 3) ) && ( (4 <= j) && (j <= 6) ) ){
        block_number = 2;
    }
    else if( ( (1 <= i) && (i <= 3) ) && ( (7 <= j) && (j <= 9) ) ){
        block_number = 3;
    }
    else if( ( (4 <= i) && (i <= 6) ) && ( (1 <= j) && (j <= 3) ) ){
        block_number = 4;
    }
    else if( ( (4 <= i) && (i <= 6) ) && ( (4 <= j) && (j <= 6) ) ){
        block_number = 5;
    }
    else if( ( (4 <= i) && (i <= 6) ) && ( (7 <= j) && (j <= 9) ) ){
        block_number = 6;
    }
    else if( ( (7 <= i) && (i <= 9) ) && ( (1 <= j) && (j <= 3) ) ){
        block_number = 7;
    }
    else if( ( (7 <= i) && (i <= 9) ) && ( (4 <= j) && (j <= 6) ) ){
        block_number = 8;
    }
    else if( ( (7 <= i) && (i <= 9) ) && ( (7 <= j) && (j <= 9) ) ){
        block_number = 9;
    }
    else{

    }
    return block_number;
}


int BLOCK::get_max_numbers_value_in_block_in_blocks(BLOCK my_b[], int block_number){
	// 最も数の多いblockを算出する
	int max_counter_except_0 = 0;
	int mat_counter_block_number = 0;
	for(int block_number = 1; block_number <= 9 ; block_number++){

		int temporary_max_counter_except_0 = 0;

		for(int i = 1; i <= 3; i++){
			for(int j = 1; j <= 3; j++){
				if(0 != my_b[block_number].block[i][j]){
					temporary_max_counter_except_0++;
				}
				std::cout << my_b[block_number].block[i][j] ;

			}
		}
		std::cout << std::endl;

		debug(false, block_number);
		debug(false, block_number);

		// 0以外の個数の最大値を更新する 重複した場合は小さいブロックの番号を取得
		if(temporary_max_counter_except_0 > max_counter_except_0){
			max_counter_except_0 = temporary_max_counter_except_0;
			mat_counter_block_number = block_number;
		}
	}
    return mat_counter_block_number;
};


void BLOCK::binary_show_in_one_number_in_one_block(
	BLOCK my_binary[], int block_number, int number){

	// バイナリーを表示 ブロック番号の数値のバイナリ	
	std::cout << std::endl;
	std::cout << "show binary sudoku table()" << std::endl;
	std::cout << "block_number=" << block_number << ", number=" << number<< std::endl;

	for(int i =1 ; i <= 3; i++){
		for(int j =1 ; j <= 3; j++){
			std::cout << my_binary[block_number].block_binary[number][i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
};


void BLOCK::binary_show_in_one_number_on_table(
	BLOCK my_b[], BLOCK my_binary[],int number_in_block){

	assert((1 <= number_in_block) && (number_in_block <= 9));

	int block_area_col = 0;// = NULL;// = 0;
	int block_col = 0; //= NULL;// = 0;
	int block_area_row = 0;// = NULL;// = 0;
	int block_row = 0;// = NULL;// = 0;

	// number_in_block = 5;
	std::cout << "+++++++++++++"  << std::endl;
	std::cout << "binary_show_in_one_number_on_table()"  << std::endl;
	std::cout << "number_in_block = " << number_in_block  << std::endl;
	std::cout << "+++++++++++++"  << std::endl;

	// バイナリーを表示 数値のバイナリ	
	for(int i = 1; i <= 9; i++){

		for(int j = 1; j <= 9; j++){

			// 数独全体座標のどこのブロックに属するかを取得する
			int temporary_block_number = my_b[0].get_block_number_on_table(i, j) ;

			// 数独全体座標のどこのブロック内の座標を取得する
			my_b[0].calculate_division_and_remainder(
				i, &block_area_col, &block_col);

			my_b[0].calculate_division_and_remainder(
				j, &block_area_row, &block_row);
			
			if(1 == block_row) {
				std::cout << "+" ;
			}

			std::cout << my_binary[temporary_block_number].block_binary[number_in_block][block_col][block_row];
		}

		std::cout << "+" << std::endl;

		if(3 == block_col) {
			std::cout << "+++++++++++++" << std::endl;
		}
	
	}

	std::cout << std::endl;
}




/*

//2重ルール
for(int i = 1; i <= 3; i++){
    for(int j = 1; j <= 3; j++){
        
    }
}

//余りを求める
					// j の余り1（1, 4, 6）からスタートしないといけない
					int division_j, remainder_j;
					my_b[0].calculate_division_and_remainder(
						j, &division_j, &remainder_j);


std::cout << "BLOCK()" << std::endl;
std::cout << "+" << std::endl;

// assert 
assert(block_number <= 9);

*/
