/////////////////////////////
///
///  Percent-Encoding(RFC 3986)
///
///  2010.03.08 

#include "percentEncoding.h"



/////////////Percent-Encoding/////////////////////////

#define ASCII_ALPHA1_START	(0x41)	//A
#define ASCII_ALPHA1_END	(0x5A)	//Z
#define ASCII_ALPHA2_START	(0x61)	//a
#define ASCII_ALPHA2_END	(0x7A)	//z
#define ASCII_DIGIT_START	(0x30)	//0
#define ASCII_DIGIT_END		(0x39)	//9
#define ASCII_HYPHEN		(0x2D)	//-
#define ASCII_PERIOD		(0x2E)	//.
#define ASCII_UNDERSCORE	(0x5F)	//_
#define ASCII_TILDA			(0x7E)	//‾




//16進数文字[A-F|a-f]から数値を得る
static inline int valueFromHexChar(char hex)
{
	if('0' <= hex && hex <= '9') return hex - '0';
	else if('A' <= hex && hex <= 'F') return hex - 'A' +10;
	else if('a' <= hex && hex <= 'f') return hex - 'a' +10;
	else return 0;
}

//数値[0=15]から16進数文字を得る
char hexCharFromValue(unsigned int value)
{
	if(16 <= value) return '0';
	return "0123456789ABCDEF"[value];
}

//URLエンコードをデコードする
void urlDecode(char* decoded 
			,unsigned int decoded_length
			   ,const char* source)
{
	decoded_length--;	//最後の¥0の分
	while(*source && decoded_length){
		if(*source == '%'){
			if(*(source+1) == '\0') break; //%の後2Byte続かずに終わっている場合に備えて
			*(decoded++) 
				= (valueFromHexChar( *(source+1) ) <<4 )
				+ valueFromHexChar( *(source+2) );
			source += 3;
#ifdef REPLACE_PLUS
		}else if(*source == '+'){	//おまけ
			*(decoded++) = ' ';
			source++;
#endif
		}else{
			*(decoded++) = *(source++);
		}
		decoded_length--;
	}
	*decoded = '\0';
}

//URLエンコードにエンコードする
void urlEncode(char* encoded 
			   ,unsigned int encoded_length
			   ,const char* source)
{
	char temp;
	encoded_length--;
	while(*source && encoded_length){
		temp =*source;
		if(   (ASCII_ALPHA1_START <= temp &&  temp<= ASCII_ALPHA1_END)
			||(ASCII_ALPHA2_START <= temp &&  temp<= ASCII_ALPHA2_END)
			||(ASCII_DIGIT_START <= temp &&  temp<= ASCII_DIGIT_END)
			|| temp == ASCII_HYPHEN
			|| temp == ASCII_PERIOD
			|| temp == ASCII_UNDERSCORE
			|| temp == ASCII_TILDA)
		{
			//Unreserved Characters
			*(encoded++) = temp;
			
		}else{
			//Reserved Characters
			*(encoded++) = '%';
			if(!(--encoded_length)) break;
			*(encoded++) = hexCharFromValue((unsigned char)temp >> 4);
			if(!(--encoded_length)) break;
			*(encoded++) = hexCharFromValue(temp & 0x0F);
			encoded_length-=2;
		}
		source++;
		encoded_length--;
	}
	*encoded = '\0';
}

///////////////////