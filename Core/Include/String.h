#ifndef DEF_STRUCT_STRING_LIBRARY
	#define DEF_STRUCT_STRING_LIBRARY

	#include "DataType.h"
	#include "DataTypeString.h"

	signed int charRemove(unsigned char *String, unsigned char RemoveChar );
	unsigned short charRemoveAll(unsigned char *String, unsigned char RemoveChar );
	unsigned char *strmid(unsigned char *strto,unsigned  char *strfrom,unsigned int CopyStartPos);
	unsigned char *strmid2(unsigned char *strto,unsigned  char *strfrom,unsigned int CopyStartPos,unsigned short Length);
	signed short strsearch(unsigned char *str1,unsigned  char *str2,unsigned int SearchStartPos);
	signed short strsearchConst(unsigned char *str1,const  char *str2,unsigned int SearchStartPos);
	signed short strsearch2(unsigned char *str1, unsigned short StrLen, unsigned char *str2,unsigned int SearchStartPos);
	signed short strsearch3(unsigned char *str1, unsigned short StrLen, unsigned char *str2,unsigned short StrLen2);
	signed short strsearch4(unsigned char *str1, signed short StrLen, unsigned char *str2, signed short StrLen2, unsigned short StartPos);
	signed short ArraySearch(unsigned char *SearchArray, unsigned short ArrayLen, unsigned char *Data,unsigned short DataLen);
	signed short ArraySearchAnyPosition(unsigned char *SearchArray, unsigned short ArrayLen, unsigned char *Data,unsigned short DataLen);

	signed short charsearch(unsigned char *str1,const unsigned  char chr,unsigned short SearchStartPos);
	signed int charpos(unsigned char *ptr,const unsigned  char chr,unsigned int SearchStartPos, unsigned short Length);
	signed int charposReverse(unsigned char *ptr,const unsigned  char chr,unsigned int SearchStartPos);
	signed short charConstsearch(const char *str1,const unsigned  char chr,unsigned short SearchStartPos);
	signed short charsearchReverse(unsigned char *str1,const unsigned  char chr,unsigned short SearchStartPos);
	signed short charConstsearchReverse(const char *str1,const unsigned  char chr,unsigned short SearchStartPos);
	signed char strreplace(unsigned char *String,unsigned char *FindString,unsigned char  *ReplaceString,unsigned char  *NewString);
	signed char strreplaceWithConst(unsigned char *String, const char *FindString,unsigned char  *ReplaceString,unsigned char *NewString);
	signed char strConstReplaceWithConst(unsigned char *String, const char *FindString,const char  *ReplaceString,unsigned char *NewString);
	signed short GetCharArrayToChar(unsigned char *Data, unsigned char *PartialString, unsigned short SearchPosition, const char FindChar, unsigned short *DataSize) ;
	signed short GetCharArrayToCharWithOutFrame(unsigned char *Data, unsigned char *PartialString, unsigned short SearchPosition, const char FindChar, unsigned short *DataSize) ;
	unsigned short strlength(unsigned char *str);
	unsigned short strltrim(unsigned char *str);
	unsigned short strlength2(unsigned char *str, unsigned short MaxLength);
	unsigned short ConstStrLength(const char *str);
	unsigned short strlengthConst(const char *str);
	void strcopy(unsigned char *strto,unsigned char *strfrom);
	void strcopyFromConst(unsigned char *strto,const char *strfrom);
	void strncopy(unsigned char *strto,unsigned char *strfrom,unsigned char LengthOfString);
	void strncopyFromConst(unsigned char *strto,const char *strfrom,unsigned char LengthOfString);
	void strcopy2(unsigned char *strto,unsigned char *strfrom);
	void ConstStrCopy2(unsigned char *strto,const char *strfrom);
	unsigned short getNumberFromString(unsigned char *Buffer, unsigned char StartPos,unsigned char StartChar);

	void StringRemove(strcSTRING_PARAMETERS *STRING_PARAMETERS);


	void StringRemoveMid(strcSTRINGMID *STRING_MID);

	unsigned char StringReplace(strcSTRING_PARAMETERS *STRING_PARAMETERS );
	void StringReplace2(strcSTRING_PARAMETERS *STRING_PARAMETER);
	void StringSearh(strcSTRING_PARAMETERS *STRING_PARAMETERS );



#endif

