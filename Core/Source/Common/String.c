#include "String.h"
#include "DataType.h"
#include "DataTypeString.h"
#include "ConvertString.h"
#include "ConvertInteger.h"

signed int charRemove(unsigned char *String, unsigned char RemoveChar )
{
	unsigned int i=0;
	signed int RemoveCharPosition=-1;

	while(String[i]) 
		{ 
			if(String[i] == RemoveChar)  
				{ 
					RemoveCharPosition = i;
					while(String[i+1] != '\0') 
						{
							String[i] = String[i+1]; 
							i++;
						} 
					String[i] = '\0'; 
				}
			else
				i++;
		}
	return RemoveCharPosition;
}

unsigned short charRemoveAll(unsigned char *String, unsigned char RemoveChar )
{
	signed int RemovePos=0;
	unsigned short i=0;
	while(String[i] &&  RemovePos>=0) { RemovePos = charRemove(String,RemoveChar); i++;}
	return i;
}

unsigned char *strmid(unsigned char *strto,unsigned  char *strfrom,unsigned int CopyStartPos)
{
  unsigned int i=0,strlen;
	strlen = strlength(strfrom);
	if (strlen >= CopyStartPos) 
		while(strfrom[CopyStartPos+i]!='\0') {strto[i]=strfrom[CopyStartPos+i]; i++;}  
  
	strto[i]='\0';
  return strto;
}

unsigned char *strmid2(unsigned char *strto,unsigned  char *strfrom,unsigned int CopyStartPos,unsigned short Length)
{
  unsigned int i=0,strlen;
	strlen = strlength(strfrom);
	if (strlen >= CopyStartPos) 
		while(strfrom[CopyStartPos+i]!='\0' && i<Length) {strto[i]=strfrom[CopyStartPos+i]; i++;}  
  
	strto[i]='\0';
  return strto;
}


void strcopy(unsigned char *strto,unsigned char *strfrom)
{
  unsigned short i;
  for(i=0; strfrom[i] != '\0'; i++) strto[i]=strfrom[i]; 
	strto[i] = '\0';
}

void strcopyFromConst(unsigned char *strto,const char *strfrom)
{
  unsigned short i;
  for(i=0; strfrom[i] != '\0'; i++) strto[i]=strfrom[i]; 
	strto[i] = '\0';
}


void strncopy(unsigned char *strto,unsigned char *strfrom,unsigned char LengthOfString)
{
  unsigned short i;
  for(i=0; (i<LengthOfString) && (strfrom[i] != '\0') ; i++) strto[i]=strfrom[i]; 
	strto[i] = '\0';
}

void strncopyFromConst(unsigned char *strto,const char *strfrom,unsigned char LengthOfString)
{
  unsigned short i;
  for(i=0; (i<LengthOfString) && (strfrom[i] != '\0') ; i++) strto[i]=strfrom[i]; 
	strto[i] = '\0';
}

void strcopy2(unsigned char *strto,unsigned char *strfrom)
{
  unsigned short i;
  for(i=0; strfrom[i] != '\0'; i++) strto[i]=strfrom[i]; 
	strto[i] = '\0';
}

void ConstStrCopy2(unsigned char *strto,const char *strfrom)
{
  unsigned short i;
  for(i=0; strfrom[i] != '\0'; i++) strto[i]=strfrom[i]; 
	strto[i] = '\0';
}

unsigned short strlength(unsigned char *str)
{
  unsigned short result=0;
  while(str[result]!= '\0' && (result < 1024) ) result++;
  return result;
}


unsigned short strltrim(unsigned char *str)
{
	
	 unsigned short strpos=0, i=0, length=0;
	 length = strlength(str);
	 while(str[strpos] == 0x20) strpos++;
	 if((strpos == length) || !length)
		{
			str[0] = '\0';
			return 0;
		}
	 else
		{
			if (strpos>0)
			{
				for(i=0;i<(length-strpos);i++)
					str[i] = str[strpos+i];
				str[i] = '\0';
				return i;
			}
		}	
	 return length;
}

unsigned short strlength2(unsigned char *str, unsigned short MaxLength)
{
  unsigned short result=0;
  while(str[result]!= '\0' && (result<MaxLength) ) result++;
  return result;
}

unsigned short ConstStrLength(const char *str)
{
  unsigned short result=0;
  while(str[result]!= '\0' ) result++;
  return result;
}

unsigned short strlengthConst(const char *ConstStr)
{
  unsigned short result=0;
  while(ConstStr[result]!= '\0' ) 
			result++;
  return result;
}
//
// Buffer Dizisi icerisinde "StartPos" dan itibaren "StartChar" Karakterini Arar ve 
// "StartChar" karakterinden sonraki sayi olan degeri bulur
//
unsigned short getNumberFromString(unsigned char *Buffer, unsigned char StartPos,unsigned char StartChar)
{
	signed short i;
	unsigned char *Tx;
	unsigned char TxData[15],Counter=0;
	unsigned char NumberEnd = 0;
	unsigned char NumberStart =0 ;
	unsigned short Value;

	Tx = &TxData[0];
	i = charsearch(Buffer,StartChar, StartPos);
	if ( i<0)  return 0;

	i = 0;
	while(i<15 && !NumberEnd && Counter <50)
		{
			if (Buffer[StartPos + Counter] >= 48 && Buffer[StartPos + Counter] <= 57)
				{
					//uarttxchar(0,Buffer[StartPos + Counter]);
					NumberStart = 1;
					Tx[i++] = Buffer[StartPos + Counter] -48;
				}
			else if (NumberStart) NumberEnd = 1;
				
			Counter++;
		}
	if (i>0) 
		{
			Tx[i] = '\0';
			Value = ConvertStringToLong(Tx,i); 
		}
	else
		{
		 Value = 0;
		}
	return Value;
}

signed short strsearch(unsigned char *str1,unsigned  char *str2,unsigned int SearchStartPos)
{
	signed short i,j=0;
	unsigned short StrLen,StrLen2;
	StrLen = strlength(str1);    
	StrLen2 = strlength(str2);
	if (!StrLen)  return -1;
	if (!StrLen2) return -1;
	if (StrLen <= SearchStartPos ) return -1;
	
	i=SearchStartPos;
	while(str1[i] != '\0')
	  {
	    if (str1[i] != str2[0]) i++;
	    else
	      {
	        j=0;
	        while(str1[i+j] != '\0' && str2[j] != '\0' && str1[i+j] == str2[j]) j++;
	        if ( str2[j] == '\0') return i;   else i++;
	      }           
	  }
	return -1;
}


signed short strsearchConst(unsigned char *str1,const  char *str2,unsigned int SearchStartPos)
{
	signed short i,j=0;
	unsigned short StrLen,StrLen2;
	StrLen = strlength(str1);    
	StrLen2 = strlengthConst(str2);
	if (!StrLen)  return -1;
	if (!StrLen2) return -1;
	if (StrLen <= SearchStartPos ) return -1;
	
	i=SearchStartPos;
	while(str1[i] != '\0')
	  {
	    if (str1[i] != str2[0]) i++;
	    else
	      {
	        j=0;
	        while(str1[i+j] != '\0' && str2[j] != '\0' && str1[i+j] == str2[j]) j++;
	        if ( str2[j] == '\0') return i;   else i++;
	      }           
	  }
	return -1;
}
 

signed short strsearch2(unsigned char *str1, unsigned short StrLen, unsigned char *str2,unsigned int SearchStartPos)
{
	signed short i,j=0;
	unsigned short StrLen2;
	 
	StrLen2 = strlength(str2);
	if (!StrLen)  return -1;
	if (!StrLen2) return -1;
	if (StrLen <= SearchStartPos ) return -1;
	
	i=SearchStartPos;
	while(str1[i] != '\0')
	  {
	    if (str1[i] != str2[0]) i++;
	    else
	      {
	        j=0;
	        while(str1[i+j] != '\0' && str2[j] != '\0' && str1[i+j] == str2[j]) j++;
	        if ( str2[j] == '\0') return i;   else i++;
	      }           
	  }
	return -1;
}

signed short strsearch3(unsigned char *str1, unsigned short StrLen, unsigned char *str2,unsigned short StrLen2)
{
	signed short i=0,j=0;
		
	if(StrLen2>StrLen) return -1;
	 
	while(i<StrLen)
	  {
	    if (str1[i] != str2[0]) i++;
	    else
	      {
	        j=0;
	        while(( (i+j) <StrLen) && (j<StrLen2) && str1[i+j] == str2[j]) j++;
	        if ( j == StrLen2) return i;   else i++;
	      }           
	  }
	return -1;
}

signed short ArraySearch(unsigned char *SearchArray, unsigned short ArrayLen, unsigned char *Data,unsigned short DataLen)
{
	signed short i=0,j=0;
		
	if(DataLen>ArrayLen) return -1;
	 
	while(i<ArrayLen)
	  {
	    if (SearchArray[i] != Data[0]) i+=DataLen;
	    else
	      {
	        j=0;
	        while(( (i+j) <ArrayLen) && (j<DataLen) && SearchArray[i+j] == Data[j]) j++;
	        if ( j == DataLen) return i/DataLen;   else i+=DataLen;
	      }           
	  }
	return -1;
}


signed short ArraySearchAnyPosition(unsigned char *SearchArray, unsigned short ArrayLen, unsigned char *Data,unsigned short DataLen)
{
	signed short i=0,j=0;
		
	if(DataLen>ArrayLen) return -1;
	 
	while(i<ArrayLen)
	  {
	    if (SearchArray[i] != Data[0]) i++;
	    else
	      {
	        j=0;
	        while(( (i+j) <ArrayLen) && (j<DataLen) && SearchArray[i+j] == Data[j]) j++;
	        if ( j == DataLen) return i;   else i++;
	      }           
	  }
	return -1;
}


signed short strsearch4(unsigned char *str1, signed short StrLen, unsigned char *str2, signed short StrLen2, unsigned short StartPos)
{
	signed short i=StartPos,j=0;
	if(StrLen== -1) StrLen = strlength(str1);	
	if(StrLen2== -1) StrLen2 = strlength(str2);	
	
	if(StrLen2>StrLen) return -1;
	 
	while(i<StrLen)
	  {
	    if (str1[i] != str2[0]) i++;
	    else
	      {
	        j=0;
	        while((i<StrLen) && (j<StrLen2) && str1[i+j] == str2[j]) j++;
	        if ( j == StrLen2) return i;   else i++;
	      }           
	  }
	return -1;
}

signed short charsearch(unsigned char *str1,const unsigned  char chr,unsigned short SearchStartPos)
{
 signed short i,StrLen;
 StrLen = strlength(str1);    
 if (!StrLen)  return -1;
 if (StrLen <= SearchStartPos ) return -1;

  i=SearchStartPos;
  while(str1[i] != '\0' && str1[i] != chr ) i++;
	if (str1[i] != '\0') return i; else   return -1;
}

signed int charpos(unsigned char *ptr,const unsigned  char chr,unsigned int SearchStartPos, unsigned short Length)
{
 signed int i;
  i=SearchStartPos;
  while((i < (SearchStartPos + Length)) && ptr[i] != chr ) i++;
	if (i < (SearchStartPos + Length)) return i; else   return -1;
}

signed int charposReverse(unsigned char *ptr,const unsigned  char chr,unsigned int SearchStartPos)
{
 signed int i;
  i=SearchStartPos;
  while((i>=0) && ptr[i] != chr ) i--;
	if (i>=0) return i; else   return -1;
}
signed short charConstsearch(const char *str1,const unsigned  char chr,unsigned short SearchStartPos)
{
 signed short i,StrLen;
 StrLen = ConstStrLength(str1);    
 if (!StrLen)  return -1;
 if (StrLen <= SearchStartPos ) return -1;

  i=SearchStartPos;
  while(str1[i] != '\0' && str1[i] != chr ) i++;
	if (str1[i] != '\0') return i; else   return -1;
}

signed short charsearchReverse(unsigned char *str1,const unsigned  char chr,unsigned short SearchStartPos)
{
 signed short i,StrLen;
 StrLen = strlength(str1);    
 if (!StrLen)  return -1;
 if (StrLen <= SearchStartPos ) return -1;

  i=SearchStartPos;
  while(i>=0 && str1[i] != '\0' && str1[i] != chr ) i--;
	if (i>=0) return i; else   return -1;
}

signed short charConstsearchReverse(const char *str1,const unsigned  char chr,unsigned short SearchStartPos)
{
 signed short i,StrLen;
 StrLen = ConstStrLength(str1);    
 if (!StrLen)  return -1;
 if (StrLen <= SearchStartPos ) return -1;

  i=SearchStartPos;
  while(i>=0 && str1[i] != '\0' && str1[i] != chr ) i--;
	if (i>=0) return i; else   return -1;
}

signed char strreplace(unsigned char *String,unsigned char *FindString,unsigned char  *ReplaceString,unsigned char *NewString)
{
	signed int i;
	unsigned int LengthOfString,LengthOfFindString,LengthOfReplaceString;
	signed int FindPosition;
	unsigned char pos=0;

	LengthOfString 					= strlength(String);	
	LengthOfReplaceString 	= strlength(ReplaceString); 
	LengthOfFindString 			= strlength(FindString);

	FindPosition = strsearch(String,FindString,0);

	for(i=0;i<=LengthOfString;i++) NewString[i] = String[i];

	if (FindPosition>=0)
		{
			for(i=0;i<FindPosition;i++) NewString[i] = String[i];
			for(i=0; i< LengthOfReplaceString ; i++) NewString[FindPosition+i] = ReplaceString[i];
			for(i = FindPosition + LengthOfFindString; i<=LengthOfString;i++) NewString[FindPosition + LengthOfReplaceString + pos++] = String[i];
		}
	return FindPosition;
}


void StringSearch(strcSTRING_PARAMETERS *STRING_PARAMETERS)
{
	signed short i,j=0;
	STRING_PARAMETERS->Result = -1;
 
	if (STRING_PARAMETERS->LengthOfString < 0) 			STRING_PARAMETERS->LengthOfString = strlength(STRING_PARAMETERS->String);    
	if (STRING_PARAMETERS->LengthOfFindString < 0) 	STRING_PARAMETERS->LengthOfFindString = strlength(STRING_PARAMETERS->FindString);    
	
	if ( (STRING_PARAMETERS->LengthOfString == 0) || (STRING_PARAMETERS->LengthOfFindString == 0) ||  ((STRING_PARAMETERS->LengthOfString) < STRING_PARAMETERS->LengthOfFindString ) ) return ;
		
	i=0;
	
	while(STRING_PARAMETERS->String[i] != '\0' && (i < STRING_PARAMETERS->LengthOfString) )
	  {
	    if (STRING_PARAMETERS->String[i] != STRING_PARAMETERS->FindString[0]) i++;
	    else
	      {
	        j=0;
	        while(STRING_PARAMETERS->String[i+j] != '\0' && STRING_PARAMETERS->FindString[j] != '\0' && STRING_PARAMETERS->String[i+j] == STRING_PARAMETERS->FindString[j]) j++;
	        if ( STRING_PARAMETERS->FindString[j] == '\0') { STRING_PARAMETERS->Result = i; return; }  else i++;
	      }           
	  }
}
//
// TODO: Test Edilecek
//
void StringRemove(strcSTRING_PARAMETERS *STRING_PARAMETERS)
{
	signed int i;
	unsigned int LengthOfString=0,LengthOfFindString;
	signed int FindPosition=0;
	unsigned char pos=0;

	//LengthOfString 					= strlength(STRING_PARAMETERS->String1);	 

	StringSearch(STRING_PARAMETERS);
	
	if (STRING_PARAMETERS->Result >=0 )
		{
			LengthOfFindString 			= strlength(STRING_PARAMETERS->String);
			
			for(i = FindPosition + LengthOfFindString; i <= LengthOfString ; i++) STRING_PARAMETERS->String[FindPosition + pos++] = STRING_PARAMETERS->String[i];
			//
			// Length Of String
			//
			STRING_PARAMETERS->LengthOfFindString = strlength(STRING_PARAMETERS->String);
		}
	
}

//
// TODO: Test Edilecek
//
void StringRemoveMid(strcSTRINGMID *STRING_MID)
{
	signed int i;
 
	//
	// STRING_PARAMETERS->LengthOfString 				 : Length Of String 
	//	STRING_PARAMETERS->LengthOfFindString 	 : Position Of First Char
	//	STRING_PARAMETERS->LengthOfReplaceString : Position Of Last Char
	//
	
	STRING_MID->Result = -1;
	if(STRING_MID->LengthOfString == -1) STRING_MID->LengthOfString = strlength(STRING_MID->String);
	
	if(STRING_MID->EndPos == -1 || (STRING_MID->EndPos > STRING_MID->LengthOfString) ) STRING_MID->EndPos = STRING_MID->LengthOfString - 1;
	
	
	if ( (STRING_MID->StartPos >=0 ) &&  (STRING_MID->EndPos >=0 ) )
		{
			//
			// Remove Char's
			//
			for(i=0;i<(STRING_MID->LengthOfString - STRING_MID->EndPos);i++)
					STRING_MID->String[STRING_MID->StartPos + i] = STRING_MID->String[STRING_MID->EndPos + i];
			
			//
			// New Length
			// 
			STRING_MID->LengthOfString = STRING_MID->LengthOfString - (STRING_MID->EndPos  - STRING_MID->StartPos);
			
			//
			//
			//
			STRING_MID->Result = 1;
		}
	
}

//
// String Replace
//

unsigned char StringReplace(strcSTRING_PARAMETERS *STRING_PARAMETERS)
{
	unsigned int i,LengthOfDifferance,MoveCharacter;
	signed int FindPosition;
	unsigned char LengthOfData, LengthOfReplaceData, LengthOfFindData;
 
 	LengthOfData = strlength(STRING_PARAMETERS->String);

	FindPosition = strsearch(STRING_PARAMETERS->String, STRING_PARAMETERS->FindString,0);
	
	if (FindPosition>=0)
		{
			LengthOfFindData		= strlength(STRING_PARAMETERS->FindString);
			LengthOfReplaceData = strlength(STRING_PARAMETERS->ReplaceString);
			
	
			if (LengthOfReplaceData > LengthOfFindData)
				{
					LengthOfDifferance = LengthOfReplaceData - LengthOfFindData;
					MoveCharacter = LengthOfData - (FindPosition + LengthOfFindData );
					for (i = 0 ;  i < MoveCharacter 		; i++ ) STRING_PARAMETERS->String[LengthOfData - i + LengthOfDifferance -1   ] = STRING_PARAMETERS->String[LengthOfData - 1- i];
				}
			else
				{
					LengthOfDifferance =  LengthOfFindData - LengthOfReplaceData;
					MoveCharacter = LengthOfData - (FindPosition + LengthOfFindData ) ;
					for (i = 0 ;  i < MoveCharacter	; i++ ) STRING_PARAMETERS->String[FindPosition + LengthOfReplaceData + i ] = STRING_PARAMETERS->String[FindPosition + LengthOfFindData + i  ];	
				}
			for (i = 0 ;  i <  LengthOfReplaceData ; i++ ) STRING_PARAMETERS->String[i+FindPosition] = STRING_PARAMETERS->ReplaceString[i];
			
			LengthOfData +=   LengthOfReplaceData - LengthOfFindData ;
		}
	return LengthOfData;
}	


signed char strreplaceWithConst(unsigned char *String,const char *FindString,unsigned char  *ReplaceString,unsigned char *NewString)
{
	signed int i;
	unsigned int LengthOfString,LengthOfFindString,LengthOfReplaceString;
	signed int FindPosition;
	unsigned char pos=0;

	LengthOfString 					= strlength(String);	
	LengthOfReplaceString 	= strlength(ReplaceString); 
	LengthOfFindString 			= strlengthConst(FindString);

	FindPosition = strsearchConst(String,FindString,0);

	for(i=0;i<=LengthOfString;i++) NewString[i] = String[i];

	if (FindPosition>=0)
		{
			for(i=0;i<FindPosition;i++) NewString[i] = String[i];
			for(i=0; i< LengthOfReplaceString ; i++) NewString[FindPosition+i] = ReplaceString[i];
			for(i = FindPosition + LengthOfFindString; i<=LengthOfString;i++) NewString[FindPosition + LengthOfReplaceString + pos++] = String[i];
		}
	return FindPosition;
}


signed char strConstReplaceWithConst(unsigned char *String,const char *FindString, const char  *ReplaceString,unsigned char *NewString)
{
	signed int i;
	unsigned int LengthOfString,LengthOfFindString,LengthOfReplaceString;
	signed int FindPosition;
	unsigned char pos=0;

	LengthOfString 					= strlength(String);	
	LengthOfReplaceString 	= strlengthConst(ReplaceString); 
	LengthOfFindString 			= strlengthConst(FindString);

	FindPosition = strsearchConst(String,FindString,0);

	for(i=0;i<=LengthOfString;i++) NewString[i] = String[i];

	if (FindPosition>=0)
		{
			for(i=0;i<FindPosition;i++) NewString[i] = String[i];
			for(i=0; i< LengthOfReplaceString ; i++) NewString[FindPosition+i] = ReplaceString[i];
			for(i = FindPosition + LengthOfFindString; i<=LengthOfString;i++) NewString[FindPosition + LengthOfReplaceString + pos++] = String[i];
		}
	return FindPosition;
}

signed short GetCharArrayToChar(unsigned char *Data, unsigned char *PartialString, unsigned short SearchPosition, const char FindChar, unsigned short *DataSize) 
{
	signed int Pos;
 
	*DataSize = 0;
	//
	// Data Type
	//
	Pos = charsearch(Data,FindChar,SearchPosition); 
	if(Pos>=0)
		{
			while((*DataSize < (Pos - SearchPosition +1))) { PartialString[*DataSize] = Data[SearchPosition + *DataSize]; *DataSize= *DataSize + 1; };	 
			PartialString[*DataSize] = '\0';
		}
	return Pos;
}

signed short GetCharArrayToCharWithOutFrame(unsigned char *Data, unsigned char *PartialString, unsigned short SearchPosition, const char FindChar, unsigned short *DataSize) 
{
	signed int Pos;
 
	*DataSize = 0;
	//
	// Data Type
	//
	Pos = charsearch(Data,FindChar,SearchPosition); 
	if(Pos>=0)
		{
			while((*DataSize < (Pos - SearchPosition))) { PartialString[*DataSize] = Data[SearchPosition + *DataSize]; *DataSize= *DataSize + 1; };	 
			PartialString[*DataSize] = '\0';
		}
	return Pos;
}
