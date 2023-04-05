unsigned char strcomp(unsigned char *CmpStr1,unsigned char *CmpStr2)
{
  unsigned char i=0,result=0 ;
  
  while(CmpStr1[i] != '\0' && CmpStr2[i] != '\0' && CmpStr1[i] == CmpStr2[i] ) i++;
  if (CmpStr1[i] == '\0' && CmpStr2[i] == '\0') 
    result = 0;
  else
    {
      if (CmpStr1[i] > CmpStr2[i]) result = 1 ; else result = 2 ;
    }
  return result;    
    
}

unsigned char strcompConst(unsigned char *CmpStr1,const char *CmpStr2)
{
  unsigned char i=0,result=0 ;
  
  while(CmpStr1[i] != '\0' && CmpStr2[i] != '\0' && CmpStr1[i] == CmpStr2[i] ) i++;
  if (CmpStr1[i] == '\0' && CmpStr2[i] == '\0') 
    result = 0;
  else
    {
      if (CmpStr1[i] > CmpStr2[i]) result = 1 ; else result = 2 ;
    }
  return result;    
    
}

unsigned char strncomp(unsigned char *CmpStr1,unsigned char *CmpStr2,unsigned char CompareLength)
{
  unsigned char i=0,result=0 ;
  
  while(CmpStr1[i] != '\0' && CmpStr2[i] != '\0' && CmpStr1[i] == CmpStr2[i] && i < CompareLength ) i++;
  if (i == CompareLength) 
    result = 0;
  else
    {
      if (CmpStr1[i] > CmpStr2[i]) result = 1 ; else result = 2 ;
    }
  return result;    
    
}

unsigned char strncompConst(unsigned char *CmpStr1,const char *CmpStr2,unsigned char CompareLength)
{
  unsigned char i=0,result=0 ;
  
  while(CmpStr1[i] != '\0' && CmpStr2[i] != '\0' && CmpStr1[i] == CmpStr2[i] && (i < CompareLength) ) i++;
  if (i == CompareLength) 
    result = 0;
  else
    {
      if (CmpStr1[i] > CmpStr2[i]) result = 1 ; else result = 2 ;
    }
  return result;    
    
}
unsigned char chararrayncomp(unsigned char *CmpStr1,unsigned char *CmpStr2,unsigned char CompareLength)
{
  unsigned char i=0,result=0 ;
  
  while(CmpStr1[i] == CmpStr2[i] && i < CompareLength ) i++;
  if (i == CompareLength) 
    result = 0;
  else
    {
      if (CmpStr1[i] > CmpStr2[i]) result = 1 ; else result = 2 ;
    }
  return result;    
    
}
