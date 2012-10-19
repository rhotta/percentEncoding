/////////////////////////////
///
///  Percent-Encoding(RFC 3986)
///


//+をスペースに置き換える(RFC3986にない挙動)
#define REPLACE_PLUS


//typedef unsigned int size_t;


//URLエンコードをデコードする
void urlDecode(char* decoded 
			   ,unsigned int decoded_length
			   ,const char* source);

//URLエンコードにエンコードする
void urlEncode(char* encoded 
			   ,unsigned int encoded_length
			   ,const char* source);



char hexCharFromValue(unsigned int value);

