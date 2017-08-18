//----------------------------------------------------------------------------------------------------------------------------------
#include "MLZW.h"
//----------------------------------------------------------------------------------------------------------------------------------
MLZW4096::MLZW4096(void)
{

}
//..............................................................................................................................
MLZW4096::~MLZW4096()
{

}
//..............................................................................................................................
void MLZW4096::Initialize(void)
{
	register int								i;

	for ( i=0;i<MLZW4096_TABLESIZE;i++ )
	{
		m_stDictory[i].nCodeValue = MLZW4096_UNUSER;
		m_stDictory[i].nParentCode = 0;
		m_stDictory[i].cCharacter = 0;
	}
}
//..............................................................................................................................
int  MLZW4096::FindChildNode(long nParentCode,long lChildCode,unsigned long * lpOutIndex)
{
	register unsigned long						lindex;
	register long								loffset;
	register int								itrytimes = 0;

	lindex = ( lChildCode << ( MLZW4096_BITS - 8) ) ^ nParentCode;
	if ( lindex == 0 )
	{
		loffset = 1;
	}
	else
	{
		loffset = MLZW4096_TABLESIZE - lindex;
	}

	while ( 1 )
	{
		if ( m_stDictory[lindex].nCodeValue == MLZW4096_UNUSER )
		{
			* lpOutIndex = lindex;
			return(1);
		}

		if ( m_stDictory[lindex].nParentCode == (short)nParentCode && m_stDictory[lindex].cCharacter == (char)lChildCode )
		{
			* lpOutIndex = lindex;
			return(1);
		}

		if ( (int)lindex >= loffset )
		{
			lindex -= loffset;
		}
		else
		{
			lindex += MLZW4096_TABLESIZE - loffset;
		}

		itrytimes ++;

		if ( itrytimes > (MLZW4096_TABLESIZE+1) )
		{
			return(ERR_MLZW_NOMATCHDIRECT);
		}
	}
}
//..............................................................................................................................
int  MLZW4096::CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register int											istringcode;
	register int											iinputptr = 1;
	register unsigned long									lindex;
	register int											icharecter;
	register int											inextcode = MLZW4096_FIRSTCODE;
	register unsigned long									loutbitptr = 0;
	register unsigned long									loutbitsize = 9;
	register int											inextbumpsize = 512;
	register unsigned short									slimitsize;
	unsigned char										*	lpinbuf;
	register int											errorcode;
	register int											ireturnsize;

	if ( sInSize > 4096 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	lpinbuf = (unsigned char *)lpInBuf;
	Initialize();
	memset(lpOutBuf,0,sOutSize);
	slimitsize = min(sOutSize,sInSize);

	istringcode = (int)lpinbuf[0];
	while ( iinputptr < sInSize )
	{
		icharecter = (int)lpinbuf[iinputptr];
		 if ( (errorcode = FindChildNode(istringcode,icharecter,&lindex)) < 0 )
		 {
			return(errorcode);
		 }
		
		if ( m_stDictory[lindex].nCodeValue != MLZW4096_UNUSER )
		{
			istringcode = (long)m_stDictory[lindex].nCodeValue;
		}
		else
		{
			m_stDictory[lindex].nCodeValue = (short)inextcode;
			m_stDictory[lindex].nParentCode = (short)istringcode;
			m_stDictory[lindex].cCharacter = (char)icharecter;

			if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,istringcode,loutbitsize)) < 0 )
			{
				return(errorcode);
			}

			inextcode ++;
			istringcode = icharecter;
			loutbitptr += loutbitsize;

			if ( inextcode >= inextbumpsize )
			{
				if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,(unsigned long)MLZW4096_BUMPCODE,loutbitsize)) < 0 )
				{
					return(errorcode);
				}

				loutbitptr += loutbitsize;
				
				loutbitsize ++;
				inextbumpsize = inextbumpsize << 1;
			}
		}

		iinputptr ++;
	}

	if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,istringcode,loutbitsize)) < 0 )
	{
		return(errorcode);
	}

	if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr + loutbitsize,MLZW4096_END,loutbitsize)) < 0 )
	{
		return(errorcode);
	}

	loutbitptr += loutbitsize + loutbitsize;

	if ( (loutbitptr % 8) != 0 )
	{
		ireturnsize = (loutbitptr >> 3) + 1;
	}
	else
	{
		ireturnsize = loutbitptr >> 3;
	}

	if ( ireturnsize >= sInSize )
	{
		return(ERR_MLZW_BUFFULL);
	}
	else
	{
		return(ireturnsize);
	}
}
//..............................................................................................................................
unsigned long MLZW4096::DecodeString(unsigned long lCount,unsigned long lCode)
{
	while ( lCode > 255 )
	{
		if ( lCount >= MLZW4096_TABLESIZE || lCode >= MLZW4096_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}
		m_szStackBuf[lCount] = m_stDictory[lCode].cCharacter;
		lCode = (short)m_stDictory[lCode].nParentCode;
		lCount ++;
	}

	m_szStackBuf[lCount] = (char)lCode;
	lCount ++;

	return(lCount);
}
//..............................................................................................................................
int  MLZW4096::ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register unsigned long								loldcode;
	register unsigned long								lnewcode;
	register int										inextcode = MLZW4096_FIRSTCODE;
	register unsigned long								lcount;
	register int										character;
	register unsigned short								soutptr = 1;
	register unsigned long								linbitptr = 9;
	register unsigned long								linbitsize = 9;
	register int										errorcode;
	register unsigned long								tempbitsize;
	
	tempbitsize = ((unsigned long)sInSize) << 3;

	if ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,0,&loldcode,9)) < 0 )
	{
		return(errorcode);
	}

	lpOutBuf[0] = (char)loldcode;
	character = (char)loldcode;

	while ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,linbitptr,&lnewcode,linbitsize)) > 0 )
	{
		if ( lnewcode == MLZW4096_END )
		{
			return(soutptr);
		}

		if ( lnewcode == MLZW4096_BUMPCODE )
		{
			linbitptr += linbitsize;
			linbitsize ++;
			continue;
		}
		
		linbitptr += linbitsize;

		if ( (int)lnewcode >= inextcode )
		{
			m_szStackBuf[0] = (char)character;
			lcount = DecodeString(1,loldcode);
		}
		else
		{
			lcount = DecodeString(0,lnewcode);
		}

		if ( lcount < 0 )
		{
			return(lcount);
		}
		else if ( lcount > MLZW4096_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		character = m_szStackBuf[lcount-1];

		while ( lcount > 0 )
		{
			if ( soutptr >= sOutSize )
			{
				return(ERR_MLZW_BUFFULL);
			}

			lpOutBuf[soutptr] = m_szStackBuf[lcount-1];
			lcount --;
			soutptr ++;
		}

		if ( inextcode >= MLZW4096_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		m_stDictory[inextcode].nParentCode = (short)loldcode;
		m_stDictory[inextcode].cCharacter = (char)character;
		inextcode ++;

		loldcode = lnewcode;
	}

	return(errorcode);

}
//------------------------------------------------------------------------------------------------------------------------------
MLZW8192::MLZW8192(void)
{

}
//..............................................................................................................................
MLZW8192::~MLZW8192()
{

}
//..............................................................................................................................
void MLZW8192::Initialize(void)
{
	register int								i;

	for ( i=0;i<MLZW8192_TABLESIZE;i++ )
	{
		m_stDictory[i].nCodeValue = MLZW8192_UNUSER;
		m_stDictory[i].nParentCode = 0;
		m_stDictory[i].cCharacter = 0;
	}
}
//..............................................................................................................................
int  MLZW8192::FindChildNode(long nParentCode,long lChildCode,unsigned long * lpOutIndex)
{
	register unsigned long						lindex;
	register long								loffset;
	register int								itrytimes = 0;

	lindex = ( lChildCode << ( MLZW8192_BITS - 8) ) ^ nParentCode;
	if ( lindex == 0 )
	{
		loffset = 1;
	}
	else
	{
		loffset = MLZW8192_TABLESIZE - lindex;
	}

	while ( 1 )
	{
		if ( m_stDictory[lindex].nCodeValue == MLZW8192_UNUSER )
		{
			* lpOutIndex = lindex;
			return(1);
		}

		if ( m_stDictory[lindex].nParentCode == (short)nParentCode && m_stDictory[lindex].cCharacter == (char)lChildCode )
		{
			* lpOutIndex = lindex;
			return(1);
		}

		if ( (int)lindex >= loffset )
		{
			lindex -= loffset;
		}
		else
		{
			lindex += MLZW8192_TABLESIZE - loffset;
		}

		itrytimes ++;

		if ( itrytimes > (MLZW8192_TABLESIZE+1) )
		{
			return(ERR_MLZW_NOMATCHDIRECT);
		}
	}
}
//..............................................................................................................................
int  MLZW8192::CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register int											istringcode;
	register int											iinputptr = 1;
	register unsigned long									lindex;
	register int											icharecter;
	register int											inextcode = MLZW8192_FIRSTCODE;
	register unsigned long									loutbitptr = 0;
	register unsigned long									loutbitsize = 9;
	register int											inextbumpsize = 512;
	register unsigned short									slimitsize;
	unsigned char										*	lpinbuf;
	register int											errorcode;
	register int											ireturnsize;

	if ( sInSize > 8192 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	lpinbuf = (unsigned char *)lpInBuf;
	Initialize();
	memset(lpOutBuf,0,sOutSize);
	slimitsize = min(sOutSize,sInSize);

	istringcode = (int)lpinbuf[0];
	while ( iinputptr < sInSize )
	{
		icharecter = (int)lpinbuf[iinputptr];
		 if ( (errorcode = FindChildNode(istringcode,icharecter,&lindex)) < 0 )
		 {
			return(errorcode);
		 }
		
		if ( m_stDictory[lindex].nCodeValue != MLZW8192_UNUSER )
		{
			istringcode = (long)m_stDictory[lindex].nCodeValue;
		}
		else
		{
			m_stDictory[lindex].nCodeValue = (short)inextcode;
			m_stDictory[lindex].nParentCode = (short)istringcode;
			m_stDictory[lindex].cCharacter = (char)icharecter;

			if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,istringcode,loutbitsize)) < 0 )
			{
				return(errorcode);
			}

			inextcode ++;
			istringcode = icharecter;
			loutbitptr += loutbitsize;

			if ( inextcode >= inextbumpsize )
			{
				if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,(unsigned long)MLZW8192_BUMPCODE,loutbitsize)) < 0 )
				{
					return(errorcode);
				}

				loutbitptr += loutbitsize;
				
				loutbitsize ++;
				inextbumpsize = inextbumpsize << 1;
			}
		}

		iinputptr ++;
	}

	if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,istringcode,loutbitsize)) < 0 )
	{
		return(errorcode);
	}

	if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr + loutbitsize,MLZW8192_END,loutbitsize)) < 0 )
	{
		return(errorcode);
	}

	loutbitptr += loutbitsize + loutbitsize;

	if ( (loutbitptr % 8) != 0 )
	{
		ireturnsize = (loutbitptr >> 3) + 1;
	}
	else
	{
		ireturnsize = loutbitptr >> 3;
	}
	
	if ( ireturnsize >= sInSize )
	{
		return(ERR_MLZW_BUFFULL);
	}
	else
	{
		return(ireturnsize);
	}
}
//..............................................................................................................................
unsigned long MLZW8192::DecodeString(unsigned long lCount,unsigned long lCode)
{
	while ( lCode > 255 )
	{
		if ( lCount >= MLZW8192_TABLESIZE || lCode >= MLZW8192_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}
		m_szStackBuf[lCount] = m_stDictory[lCode].cCharacter;
		lCode = (short)m_stDictory[lCode].nParentCode;
		lCount ++;
	}

	m_szStackBuf[lCount] = (char)lCode;
	lCount ++;

	return(lCount);
}
//..............................................................................................................................
int  MLZW8192::ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register unsigned long								loldcode;
	register unsigned long								lnewcode;
	register int										inextcode = MLZW8192_FIRSTCODE;
	register unsigned long								lcount;
	register int										character;
	register unsigned short								soutptr = 1;
	register unsigned long								linbitptr = 9;
	register unsigned long								linbitsize = 9;
	register int										errorcode;
	register unsigned long								tempbitsize;

	tempbitsize = ((unsigned long)sInSize) << 3;

	if ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,0,&loldcode,9)) < 0 )
	{
		return(errorcode);
	}

	lpOutBuf[0] = (char)loldcode;
	character = (char)loldcode;

	while ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,linbitptr,&lnewcode,linbitsize)) > 0 )
	{
		if ( lnewcode == MLZW8192_END )
		{
			return(soutptr);
		}
		else if ( lnewcode == MLZW8192_BUMPCODE )
		{
			linbitptr += linbitsize;
			linbitsize ++;
			continue;
		}
		
		linbitptr += linbitsize;

		if ( (int)lnewcode >= inextcode )
		{
			m_szStackBuf[0] = (char)character;
			lcount = DecodeString(1,loldcode);
		}
		else
		{
			lcount = DecodeString(0,lnewcode);
		}

		if ( lcount < 0 )
		{
			return(lcount);
		}
		else if ( lcount > MLZW8192_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		character = m_szStackBuf[lcount-1];

		while ( lcount > 0 )
		{
			if ( soutptr >= sOutSize )
			{
				return(ERR_MLZW_BUFFULL);
			}

			lpOutBuf[soutptr] = m_szStackBuf[lcount-1];
			lcount --;
			soutptr ++;
		}

		if ( inextcode >= MLZW8192_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		m_stDictory[inextcode].nParentCode = (short)loldcode;
		m_stDictory[inextcode].cCharacter = (char)character;
		inextcode ++;

		loldcode = lnewcode;
	}

	return(errorcode);

}
//------------------------------------------------------------------------------------------------------------------------------
MLZW::MLZW(void)
{

}
//..............................................................................................................................
MLZW::~MLZW()
{

}
//..............................................................................................................................
void MLZW::Initialize(void)
{
	register int								i;

	for ( i=0;i<MLZW_TABLESIZE;i++ )
	{
		m_stDictory[i].nCodeValue = MLZW_UNUSER;
		m_stDictory[i].nParentCode = 0;
		m_stDictory[i].cCharacter = 0;
	}
}
//..............................................................................................................................
int  MLZW::FindChildNode(long nParentCode,long lChildCode,unsigned long * lpOutIndex)
{
	register unsigned long						lindex;
	register long								loffset;
	register int								itrytimes = 0;

	assert(nParentCode >= 0);
	assert(lChildCode >= 0);

	lindex = (( lChildCode << ( MLZW_BITS - 8) ) ^ nParentCode) % MLZW_TABLESIZE;

	if ( lindex == 0 )
	{
		loffset = 1;
	}
	else
	{
		loffset = MLZW_TABLESIZE - lindex;
	}

	while ( 1 )
	{
		if ( m_stDictory[lindex].nCodeValue == MLZW_UNUSER )
		{
			* lpOutIndex = lindex;
			return(1);
		}

		if ( m_stDictory[lindex].nParentCode == (short)nParentCode && m_stDictory[lindex].cCharacter == (char)lChildCode )
		{
			* lpOutIndex = lindex;
			return(1);
		}

		if ( (int)lindex >= loffset )
		{
			lindex -= loffset;
		}
		else
		{
			lindex += (MLZW_TABLESIZE - loffset) % MLZW_TABLESIZE;
		}

		itrytimes ++;

		if ( itrytimes > (MLZW_TABLESIZE+1) )
		{
			return(ERR_MLZW_NOMATCHDIRECT);
		}
	}
}
//..............................................................................................................................
int  MLZW::CompressBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize)
{
	register int											istringcode;
	register int											iinputptr = 1;
	register unsigned long									lindex;
	register int											icharecter;
	register unsigned long									loutbitptr = 0;
	register unsigned long									slimitsize;
	unsigned char										*	lpinbuf;
	register int											errorcode;
	register int											ireturnsize;

	register int											inextcode = MLZW_FIRSTCODE;
	register unsigned long									loutbitsize = 9;
	register int											inextbumpsize = 512;

	if ( sInSize > 536870912 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	lpinbuf = (unsigned char *)lpInBuf;
	Initialize();
	memset(lpOutBuf,0,sOutSize);
	slimitsize = min(sOutSize,sInSize);

	istringcode = (int)lpinbuf[0];
	while ( iinputptr < (int)sInSize )
	{
		icharecter = (int)lpinbuf[iinputptr];
		 if ( (errorcode = FindChildNode(istringcode,icharecter,&lindex)) < 0 )
		 {
			return(errorcode);
		 }
		
		if ( m_stDictory[lindex].nCodeValue != MLZW_UNUSER )
		{
			istringcode = (long)m_stDictory[lindex].nCodeValue;
		}
		else
		{
			m_stDictory[lindex].nCodeValue = inextcode;
			m_stDictory[lindex].nParentCode = istringcode;
			m_stDictory[lindex].cCharacter = icharecter;

			assert(istringcode < MLZW_TABLESIZE);

			if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,istringcode,loutbitsize)) < 0 )
			{
				return(errorcode);
			}

			inextcode ++;
			istringcode = icharecter;
			loutbitptr += loutbitsize;

			if ( inextcode >= MLZW_TABLESIZE )
			{
				if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,(unsigned long)MLZW_CLEARTABLE,loutbitsize)) < 0 )
				{
					return(errorcode);
				}

				loutbitptr += loutbitsize;

				Initialize();
				inextcode = MLZW_FIRSTCODE;
				loutbitsize = 9;
				inextbumpsize = 512;
				
				istringcode = (int)lpinbuf[iinputptr];
				iinputptr ++;

				continue;
			}
			else if ( inextcode >= inextbumpsize )
			{
				if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,(unsigned long)MLZW_BUMPCODE,loutbitsize)) < 0 )
				{
					return(errorcode);
				}

				loutbitptr += loutbitsize;
				
				loutbitsize ++;
				inextbumpsize = inextbumpsize << 1;
			}
		}

		iinputptr ++;
	}

	if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr,istringcode,loutbitsize)) < 0 )
	{
		return(errorcode);
	}

	if ( (errorcode = PutBitToBuf32(lpOutBuf,slimitsize,loutbitptr + loutbitsize,MLZW_END,loutbitsize)) < 0 )
	{
		return(errorcode);
	}

	loutbitptr += loutbitsize + loutbitsize;

	if ( (loutbitptr % 8) != 0 )
	{
		ireturnsize = (loutbitptr >> 3) + 1;
	}
	else
	{
		ireturnsize = loutbitptr >> 3;
	}

	if ( ireturnsize >= (int)sInSize )
	{
		return(ERR_MLZW_BUFFULL);
	}
	else
	{
		return(ireturnsize);
	}
}
//..............................................................................................................................
unsigned long MLZW::DecodeString(unsigned long lCount,unsigned long lCode)
{
	while ( lCode > 255 )
	{
		if ( lCount >= MLZW_TABLESIZE || lCode >= MLZW_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		m_szStackBuf[lCount] = m_stDictory[lCode].cCharacter;
		lCode = (long)m_stDictory[lCode].nParentCode;
		lCount ++;
	}

	m_szStackBuf[lCount] = (char)lCode;
	lCount ++;

	return(lCount);
}
//..............................................................................................................................
int  MLZW::ExpandBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize)
{
	register unsigned long								loldcode;
	register unsigned long								lnewcode;
	register long										lcount;
	register int										character;
	register unsigned long								soutptr = 1;
	register unsigned long								linbitptr = 9;
	register int										errorcode;

	register int										inextcode = MLZW_FIRSTCODE;
	register unsigned long								linbitsize = 9;
	
	register unsigned long								tempbitsize;

	tempbitsize = sInSize << 3;

	if ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,0,&loldcode,9)) < 0 )
	{
		return(errorcode);
	}

	lpOutBuf[0] = (char)loldcode;
	character = (char)loldcode;

	while ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,linbitptr,&lnewcode,linbitsize)) > 0 )
	{
		assert(lnewcode < MLZW_TABLESIZE);

		if ( lnewcode == MLZW_END )
		{
			return(soutptr);
		}
		else if ( lnewcode == MLZW_BUMPCODE )
		{
			linbitptr += linbitsize;
			linbitsize ++;
			continue;
		}
		else if ( lnewcode == MLZW_CLEARTABLE )
		{
			linbitptr += linbitsize;

			inextcode = MLZW_FIRSTCODE;
			linbitsize = 9;

			if ( (errorcode = GetBitFromBuf32(lpInBuf,tempbitsize,linbitptr,&loldcode,linbitsize)) < 0 )
			{
				return(errorcode);
			}

			linbitptr += linbitsize;

			if ( loldcode == MLZW_END )
			{
				return(soutptr);
			}

			if ( soutptr >= sOutSize )
			{
				return(ERR_MLZW_BUFFULL);
			}

			lpOutBuf[soutptr] = (char)loldcode;
			soutptr ++;

			character = loldcode;

			continue;
		}
		
		linbitptr += linbitsize;

		if ( (long)lnewcode >= inextcode )
		{
			m_szStackBuf[0] = (char)character;
			lcount = DecodeString(1,loldcode);
		}
		else
		{
			lcount = DecodeString(0,lnewcode);
		}

		if ( lcount < 0 )
		{
			return(lcount);
		}
		else if ( lcount > MLZW_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		character = m_szStackBuf[lcount-1];

		while ( lcount > 0 )
		{
			if ( soutptr >= sOutSize )
			{
				return(ERR_MLZW_BUFFULL);
			}

			lpOutBuf[soutptr] = m_szStackBuf[lcount-1];
			lcount --;
			soutptr ++;
		}

		if ( inextcode >= MLZW_TABLESIZE )
		{
			return(ERR_MLZW_DECODE);
		}

		m_stDictory[inextcode].nParentCode = (long)loldcode;
		m_stDictory[inextcode].cCharacter = (char)character;
		inextcode ++;

		loldcode = lnewcode;
	}

	return(errorcode);

}
//----------------------------------------------------------------------------------------------------------------------------------
MLZW4096C::MLZW4096C(void)
{

}
//..............................................................................................................................
MLZW4096C::~MLZW4096C()
{

}
//..............................................................................................................................
int  MLZW4096C::CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register int					errorcode;
	register unsigned short			checkcode;
	MCRC16							crc;

	if ( sOutSize < 2 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	checkcode = crc.CheckCode(lpInBuf,sInSize);
	memcpy(lpOutBuf,&checkcode,2);

	if ( (errorcode = MLZW4096::CompressBuf(lpInBuf,sInSize,lpOutBuf + 2,sOutSize - 2)) < 0 )
	{
		//压缩错误
		return(errorcode);
	}

	if ( errorcode >= sInSize + 2 )
	{
		//压缩长度大于等于不压缩长度
		return(ERR_MLZW_BUFFULL);
	}

	return(errorcode + 2);
}
//..............................................................................................................................
int  MLZW4096C::ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register int					errorcode;
	register unsigned short			checkcode;
	MCRC16							crc;

	if ( sInSize < 2 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}

	memcpy(&checkcode,lpInBuf,2);

	if ( (errorcode = MLZW4096::ExpandBuf(lpInBuf + 2,sInSize - 2,lpOutBuf,sOutSize)) < 0 )
	{
		//解压缩发生错误
		return(errorcode);
	}

	if ( crc.CheckCode(lpOutBuf,errorcode) != checkcode )
	{
		//校验发生错误
		return(ERR_MLZW_NOMATCHDIRECT);
	}

	return(errorcode);
}
//----------------------------------------------------------------------------------------------------------------------------------
MLZW8192C::MLZW8192C(void)
{
	
}
//..............................................................................................................................
MLZW8192C::~MLZW8192C()
{
	
}
//..............................................................................................................................
int  MLZW8192C::CompressBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register int					errorcode;
	register unsigned short			checkcode;
	MCRC16							crc;
	
	if ( sOutSize < 2 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	checkcode = crc.CheckCode(lpInBuf,sInSize);
	memcpy(lpOutBuf,&checkcode,2);
	
	if ( (errorcode = MLZW8192::CompressBuf(lpInBuf,sInSize,lpOutBuf + 2,sOutSize - 2)) < 0 )
	{
		//压缩错误
		return(errorcode);
	}
	
	if ( errorcode >= sInSize + 2 )
	{
		//压缩长度大于等于不压缩长度
		return(ERR_MLZW_BUFFULL);
	}
	
	return(errorcode + 2);
}
//..............................................................................................................................
int  MLZW8192C::ExpandBuf(const char * lpInBuf,unsigned short sInSize,char * lpOutBuf,unsigned short sOutSize)
{
	register int					errorcode;
	register unsigned short			checkcode;
	MCRC16							crc;
	
	if ( sInSize < 2 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	memcpy(&checkcode,lpInBuf,2);
	
	if ( (errorcode = MLZW8192::ExpandBuf(lpInBuf + 2,sInSize - 2,lpOutBuf,sOutSize)) < 0 )
	{
		//解压缩发生错误
		return(errorcode);
	}
	
	if ( crc.CheckCode(lpOutBuf,errorcode) != checkcode )
	{
		//校验发生错误
		return(ERR_MLZW_NOMATCHDIRECT);
	}
	
	return(errorcode);
}
//----------------------------------------------------------------------------------------------------------------------------------
MLZWC::MLZWC(void)
{
	
}
//..............................................................................................................................
MLZWC::~MLZWC()
{
	
}
//..............................................................................................................................
int  MLZWC::CompressBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize)
{
	register int					errorcode;
	register unsigned short			checkcode;
	MCRC16							crc;
	
	if ( sOutSize < 2 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	checkcode = crc.CheckCode(lpInBuf,sInSize);
	memcpy(lpOutBuf,&checkcode,2);
	
	if ( (errorcode = MLZW::CompressBuf(lpInBuf,sInSize,lpOutBuf + 2,sOutSize - 2)) < 0 )
	{
		//压缩错误
		return(errorcode);
	}
	
	if ( errorcode >= sInSize + 2 )
	{
		//压缩长度大于等于不压缩长度
		return(ERR_MLZW_BUFFULL);
	}
	
	return(errorcode + 2);
}
//..............................................................................................................................
int  MLZWC::ExpandBuf(const char * lpInBuf,unsigned long sInSize,char * lpOutBuf,unsigned long sOutSize)
{
	register int					errorcode;
	register unsigned short			checkcode;
	MCRC16							crc;
	
	if ( sInSize < 2 )
	{
		return(ERR_PUBLIC_SLOPOVER);
	}
	
	memcpy(&checkcode,lpInBuf,2);
	
	if ( (errorcode = MLZW::ExpandBuf(lpInBuf + 2,sInSize - 2,lpOutBuf,sOutSize)) < 0 )
	{
		//解压缩发生错误
		return(errorcode);
	}
	
	if ( crc.CheckCode(lpOutBuf,errorcode) != checkcode )
	{
		//校验发生错误
		return(ERR_MLZW_NOMATCHDIRECT);
	}
	
	return(errorcode);
}
//----------------------------------------------------------------------------------------------------------------------------------
