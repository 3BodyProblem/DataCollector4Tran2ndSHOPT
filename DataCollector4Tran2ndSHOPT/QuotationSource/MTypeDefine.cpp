//------------------------------------------------------------------------------------------------------------------------------
#include "MTypeDefine.h"

//------------------------------------------------------------------------------------------------------------------------------
char * my_strncpy(char * strDest,const char * strSource,size_t iCount)
{
	char				*	lpsztempptr;

	assert(strDest != NULL);
	assert(strSource != NULL);
	assert(iCount > 0);

	if ( strDest == NULL || strSource == NULL || iCount <= 0 )
	{
		return(NULL);
	}

	lpsztempptr = strncpy(strDest,strSource,iCount);
	strDest[iCount - 1] = 0;
	
	return(lpsztempptr);
}

//..............................................................................................................................
char * my_strncat(char * strDest,const char * strSource,size_t iCount)
{
	char				*	lpsztempptr;
	
	assert(strDest != NULL);
	assert(strSource != NULL);
	assert(iCount > 0);
	
	if ( strDest == NULL || strSource == NULL || iCount <= 0 )
	{
		return(NULL);
	}

	lpsztempptr = strncat(strDest,strSource,iCount);
	strDest[iCount - 1] = 0;
	
	return(lpsztempptr);
}

//..............................................................................................................................
void my_snprintf(char * lpszBuffer,size_t lCount,const char * lpszFormat,...)
{
	va_list					smarker;

	assert(lpszBuffer != NULL);
	assert(lCount > 0);

	if ( lpszBuffer == NULL || lCount <= 0 )
	{
		return;
	}
	
	va_start(smarker,lpszFormat);
	_vsnprintf(lpszBuffer,lCount,lpszFormat,smarker);
	va_end( smarker );

	lpszBuffer[lCount - 1] = 0;
}

//------------------------------------------------------------------------------------------------------------------------------
// add by yuanjj for safe string formating 2014-03-08
/**
 *	string formating input
 *
 * 	@buf			[out] the output buf
 * 	@size			[in] the output buf size
 * 	@format			[in] the const formating string
 * 	@...			[in] other arguments
 *
 * 	return:
 * 		>=	0	successful, the number of bytes are written into the buf( excluding the terminating null character )
 * 		<	0	failed
 *
 * 	remark:
 * 		Not more than size bytes (including the terminating null byte) will be written. The terminating null byte is written on the successful return.
 * 		The content of the buf is indetermination on the failed return.
 */
df_s32_t my_snprintf_s( df_s8_t* buf, df_s32_t size, const df_s8_t* format, ... )
{
	df_s32_t		len;
	va_list			valist;

	if ( 0 >= size )
		return -1;

#ifndef		LINUXCODE
	va_start( valist, format );
	len = _vsnprintf( buf, size, format, valist );
	va_end( valist );

	if ( 0 > len )
		len = size - 1;
	else if ( len == size )
		len--;

	buf[len] = '\0';
#else
	va_start( valist, format );
	len = vsnprintf( buf, size, format, valist );
	va_end( valist );

	if ( 0 >= len )
		len = -2;
	else if ( len > size )	// the len of 'format' > 'size'
		len = size - 1;
#endif

	return len;
}
// add end
