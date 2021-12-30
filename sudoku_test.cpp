#include <iostream>
#include <thread>
#include <assert.h>
#include "sudoku.h"
#include "sudoku_block.h"




int main(){


	BLOCK my_b[10];
	BLOCK my_binary[10];

	// バイナリーを表示 ブロック番号の数値のバイナリ	
	int block_number = 1; 
	int number = 3;
	my_binary[0].binary_show_in_one_number_in_one_block(my_binary, block_number, number);

	// バイナリーを表示 ブロック番号の数値のバイナリ	
	block_number = 2, number = 3;
	my_binary[0].binary_show_in_one_number_in_one_block(my_binary, block_number, number);

	// バイナリーを表示 ブロック番号の数値のバイナリ
	block_number = 4, number = 3;
	my_binary[0].binary_show_in_one_number_in_one_block(my_binary, block_number, number);
	


}