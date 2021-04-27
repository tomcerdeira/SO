

#include "./include/chessPieces.h"

// static unsigned char __piece_bitmap__[] = {
// 	//  32 $20 'space'
// 	//	width 8, bbx 0, bby -4, bbw 8, bbh 16    ///sacar comentarios, cambiar
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	________,
// 	//  33 $21 'exclam'
// 	//	width 8, bbx 0, bby -4, bbw 8, bbh 16
// 	// PEON
// 	________,
// 	________,
// 	___XX___,
// 	__XXXX__,
// 	__XXXX__,
// 	__XXXX__,
// 	___XX___,
// 	___XX___,
// 	___XX___,
// 	___XX___,
// 	___XX___,
// 	__XXXX__,
// 	__XXXX__,
// 	________,
// 	________,
// 	________,

// 	///////////////////
// 	// TORRE

// 	________,
// 	________,
// 	X__XX__X,
// 	X__XX__X,
// 	XXXXXXXX,
// 	XXXXXXXX,
// 	__XXXX__,
// 	__XXXX__,
// 	__XXXX__,
// 	__XXXX__,
// 	__XXXX__,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	________,
// 	________,

// 	//////////////////////
// 	// ALFIL

// 	________,
// 	___XX___,
// 	__XXXX__,
// 	__XXXX__,
// 	XXXXXXXX,
// 	__XXXX__,
// 	___XX___,
// 	__XXXX__,
// 	___XX___,
// 	___XX___,
// 	___XX___,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	________,
// 	________,

// 	////////////////////
// 	// CABALLO

// 	________,
// 	____X___,
// 	___XXX__,
// 	__XXX_X_,
// 	_XXXXXXX,
// 	XXXXX_XX,
// 	XXXX____,
// 	_XXXX___,
// 	_XXXX___,
// 	__XXXX__,
// 	__XXXX__,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	________,
// 	________,

// 	////////////////////
// 	// REY

// 	________,
// 	___XX___,
// 	_XXXXXX_,
// 	___XX___,
// 	XXXXXXXX,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	___XX___,
// 	_XXXXXX_,
// 	___XX___,
// 	__XXXX__,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	________,
// 	________,

// 	////////////////////
// 	// REINA

// 	________,
// 	X__XX__X,
// 	_XX__XX_,
// 	XXXXXXXX,
// 	_XXXXXX_,
// 	___XX___,
// 	__XXXX__,
// 	___XX___,
// 	__XXXX__,
// 	___XX___,
// 	__XXXX__,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	_XXXXXX_,
// 	________,
// 	________,
// };

static unsigned char __piece_bitmap__[] = {

	//PEON
	' ', ' ', ' ', ' ', '\n',
	' ', ' ', 'O', ' ', '\n',
	' ', 'O', 'O', 'O', '\n',
	' ', ' ', 'O', ' ', '\n',
	' ', ' ', '|', ' ', '\n',
	' ', '_', '|', '_', '\n',
	' ', ' ', '|', ' ', '\n',
	' ', ' ', '|', ' ', '\n',
	' ', ' ', '|', ' ', '\n',
	' ', '_', '-', '_', '\n',

	//TORRE
};

unsigned char *pieceBitmap(int c)
{
	return (__piece_bitmap__ + (c) * (PIECE_HEIGHT + PIECE_WIDTH));
}
