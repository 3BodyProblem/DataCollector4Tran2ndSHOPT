#include "MCheckCode.h"


unsigned short	MCRC16::scrctable[256] = {	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
											0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
											0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
											0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
											0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
											0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
											0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
											0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
											0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
											0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
											0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
											0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
											0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
											0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
											0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
											0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
											0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
											0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
											0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
											0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
											0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
											0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
											0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
											0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
											0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
											0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
											0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
											0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
											0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
											0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
											0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
											0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0	};
//------------------------------------------------------------------------------------------------------------------------------
MCRC16::MCRC16(void)
{
	
}
//..............................................................................................................................
MCRC16::~MCRC16()
{
	
}
//..............................................................................................................................
unsigned short MCRC16::CheckCode(const char * lpInBuf,unsigned long sInSize, unsigned short wLastCk)
{

	register int						i;
	
	assert(lpInBuf != NULL);
	
	for ( i=0;i<sInSize;i++ )
	{
		wLastCk = scrctable[((wLastCk >> 8) & 0xff ) ^ ( lpInBuf[i] & 0xff )] ^ (wLastCk << 8);
	}
	
	return(wLastCk);
}

unsigned long MCRC32::lcrctable[256] = {0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
										0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
										0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
										0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
										0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
										0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
										0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
										0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
										0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
										0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
										0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
										0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
										0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
										0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
										0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
										0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
										
										0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
										0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
										0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
										0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
										0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
										0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
										0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
										0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
										0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
										0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
										0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
										0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
										0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
										0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
										0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
										0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
										
										0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
										0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
										0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
										0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
										0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
										0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
										0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
										0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
										0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
										0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
										0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
										0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
										0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
										0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
										0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
										0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
										
										0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
										0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
										0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
										0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
										0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
										0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
										0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
										0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
										0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
										0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
										0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
										0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
										0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
										0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
										0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
										0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D	};
//------------------------------------------------------------------------------------------------------------------------------
MCRC32::MCRC32(void)
{
	
}
//..............................................................................................................................
MCRC32::~MCRC32()
{
	
}
//..............................................................................................................................
unsigned long MCRC32::CheckCode(const char * lpInBuf,unsigned long sInSize, unsigned long dwLastCk)
{
	register unsigned long				errorcode = 0;
	register int						i;
	
	assert(lpInBuf != NULL);
	
	for ( i=0;i<sInSize;i++ )
	{
		dwLastCk = lcrctable[(dwLastCk ^ lpInBuf[i]) & 0xff] ^ (( dwLastCk >> 8) & 0x00FFFFFF); 
	}
	
	return(dwLastCk);
}
//------------------------------------------------------------------------------------------------------------------------------
MConCheckCode::MConCheckCode(void)
{
	
}
//..............................................................................................................................
MConCheckCode::~MConCheckCode()
{
	
}
//..............................................................................................................................
unsigned short MConCheckCode::CheckCode(char * lpInBuf,unsigned long sInSize)
{
	unsigned long						errorcode = 0;
	unsigned short					*	lptempptr;
	
	assert(lpInBuf != NULL);
	
	lptempptr = (unsigned short *)lpInBuf;
	while ( sInSize > 1 )
	{
		errorcode += * lptempptr ++;
		sInSize -= sizeof(unsigned short);
	}
	
	if ( sInSize > 0 )
	{
		errorcode += *(unsigned char *)lptempptr;
	}
	
	errorcode = (errorcode >> 16) + (errorcode & 0xFFFF);
	errorcode += (errorcode >> 16);
	
	return((unsigned short)(~errorcode));
}
//------------------------------------------------------------------------------------------------------------------------------
MMD5::MMD5(void)
{

}
//..............................................................................................................................
MMD5::~MMD5()
{

}
//..............................................................................................................................
DWORD  MMD5::inner_f(DWORD X,DWORD Y,DWORD Z)
{
    return((X & Y) | ((~X) & Z));
}
//..............................................................................................................................
DWORD  MMD5::inner_g(DWORD X,DWORD Y,DWORD Z)
{
    return((X & Z) | (Y & (~Z)));
}
//..............................................................................................................................
DWORD  MMD5::inner_h(DWORD X,DWORD Y,DWORD Z)
{
    return(X ^ Y ^ Z);
}
//..............................................................................................................................
DWORD  MMD5::inner_i(DWORD X,DWORD Y,DWORD Z)
{
    return(Y ^ (X | (~Z)));
}
//..............................................................................................................................
DWORD  MMD5::inner_shrloop(DWORD Value,unsigned char N)
{
    return((Value << N) | (Value >> (32-N)));
}
//..............................................................................................................................
void  MMD5::inner_ff(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T)
{
    A = A + inner_f(B,C,D) + X + T;
    A = inner_shrloop(A,S);
    A = A + B;
}
//..............................................................................................................................
void  MMD5::inner_gg(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T)
{
    A = A + inner_g(B,C,D) + X + T;
    A = inner_shrloop(A,S);
    A = A + B;
}
//..............................................................................................................................
void  MMD5::inner_hh(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T)
{
    A = A + inner_h(B,C,D) + X + T;
    A = inner_shrloop(A,S);
    A = A + B;
}
//..............................................................................................................................
void  MMD5::inner_ii(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T)
{
    A = A + inner_i(B,C,D) + X + T;
    A = inner_shrloop(A,S);
    A = A + B;
}
//modify by liuqy 20110923 for 使用接力计算
//..............................................................................................................................
int  MMD5::MD5(const char * lpInBuf,int iInSize,char szOutBuf[16])
{
    DWORD                   aa,bb,cc,dd;
	char szMd5Key[16] = {0};

	assert(lpInBuf != NULL);
	assert(iInSize != 0);

    aa = 0x67452301;
    bb = 0xefcdab89;
    cc = 0x98badcfe;
    dd = 0x10325476;


    memcpy(szMd5Key,(char *)&aa,4);
    memcpy(szMd5Key + 4,(char *)&bb,4);
    memcpy(szMd5Key + 8,(char *)&cc,4);
    memcpy(szMd5Key + 12,(char *)&dd,4);

    return MD5(szMd5Key, lpInBuf, iInSize, szOutBuf);
}
//add by liuyqy 20110923 for 增加接力计算方式
//Md5接力计算方式，注意接力计算与一次计算的值可能不相等待，主要是因为接力计算时不足64位时的系统补了空数据参与计算，接力为保存与一次性计算相同，则每次数据计算长度必须为64的倍数
//in_OldMd5Value为上一次的MAC值，lpInBuf为需要计算的数据，iInSize为需要计算的数据长度, szOutBuf为输出的MAC值
//moidfy by liuqy 20111110 for 使用少量的内存去做MD5计算，重复使用用户的空间
int MMD5::MD5(const char in_OldMd5[16], const char * lpInBuf,int iInSize,char szOutBuf[16])
{
    const char                *   lpextendbuf;
	//char					tempbuf[9000];
	char					szTmpBuf[256]  ;

    int                     iextendsize = 0;
    int                     itemp = 0;
	int						iLen = 0;
	int						iPos = 0;
	int						iCount = 0;
	int						iFrmTmpCount = 0;
    register int            i = 0;
    DWORD                   a,b,c,d;
    DWORD                   aa,bb,cc,dd;
    const DWORD               *   x;

	assert(lpInBuf != NULL);
	assert(iInSize != 0);

    memcpy(&aa, in_OldMd5, 4);
    memcpy(&bb, in_OldMd5 + 4, 4);
    memcpy(&cc, in_OldMd5 + 8, 4);
    memcpy(&dd, in_OldMd5 + 12, 4);

    if ( iInSize % 64 < 56 )
        iextendsize = ( iInSize / 64 ) * 64 + 64;
    else
        iextendsize = ( iInSize / 64 + 1 )  * 64 + 64;

	memset(szTmpBuf, 0, sizeof(szTmpBuf));

	//moidfy by liuqy 20111110 for 使用少量的内存去做MD5计算，重复使用用户的空间
	itemp = iInSize / 64;
	iPos = itemp * 64;
	if(iPos >= iInSize)
		iPos = iInSize;
	iLen = iInSize - iPos;
	
	iCount = iextendsize/64;
	if(iLen < 56)  
	{
		iFrmTmpCount = 1;
        iextendsize = 64;
	}
    else
	{
		iFrmTmpCount = 2;
        iextendsize = 64 + 64;
	}
	if(0 < iLen)
		memcpy(szTmpBuf, lpInBuf + iPos, iLen);
	szTmpBuf[iLen] = (unsigned char)128;
/*
    for ( i=iLen; i<iextendsize-8;i++ )
    {
        if ( i == iLen )  szTmpBuf[i] = (unsigned char)128;
        else    szTmpBuf[i] = 0;
    }
	*/

    itemp = iInSize * 8;
    memcpy((char *)&szTmpBuf[iextendsize-8],(char *)&itemp,4);
    memset((char *)&szTmpBuf[iextendsize-4],0x00,4);

	lpextendbuf = lpInBuf;

	iPos = 0;

    for (i=0; i<iCount; i++ )
    {
        a = aa;
        b = bb;
        c = cc;
        d = dd;
		if(i+iFrmTmpCount >= iCount)
		{
			if(i+iFrmTmpCount == iCount)
				iPos = 0;
			x = (const DWORD *)&szTmpBuf[iPos];
		}
		else
			x = (const DWORD *)&lpextendbuf[iPos];

		iPos += 64;

        inner_ff (a, b, c, d, x[ 0],  7, 0xd76aa478); /* 1 */
        inner_ff (d, a, b, c, x[ 1], 12, 0xe8c7b756); /* 2 */
        inner_ff (c, d, a, b, x[ 2], 17, 0x242070db); /* 3 */
        inner_ff (b, c, d, a, x[ 3], 22, 0xc1bdceee); /* 4 */
        inner_ff (a, b, c, d, x[ 4],  7, 0xf57c0faf); /* 5 */
        inner_ff (d, a, b, c, x[ 5], 12, 0x4787c62a); /* 6 */
        inner_ff (c, d, a, b, x[ 6], 17, 0xa8304613); /* 7 */
        inner_ff (b, c, d, a, x[ 7], 22, 0xfd469501); /* 8 */
        inner_ff (a, b, c, d, x[ 8],  7, 0x698098d8); /* 9 */
        inner_ff (d, a, b, c, x[ 9], 12, 0x8b44f7af); /* 10 */
        inner_ff (c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
        inner_ff (b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
        inner_ff (a, b, c, d, x[12],  7, 0x6b901122); /* 13 */
        inner_ff (d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
        inner_ff (c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
        inner_ff (b, c, d, a, x[15], 22, 0x49b40821); /* 16 */

        inner_gg (a, b, c, d, x[ 1],  5, 0xf61e2562); /* 17 */
        inner_gg (d, a, b, c, x[ 6],  9, 0xc040b340); /* 18 */
        inner_gg (c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
        inner_gg (b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /* 20 */
        inner_gg (a, b, c, d, x[ 5],  5, 0xd62f105d); /* 21 */
        inner_gg (d, a, b, c, x[10],  9,  0x2441453); /* 22 */
        inner_gg (c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
        inner_gg (b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /* 24 */
        inner_gg (a, b, c, d, x[ 9],  5, 0x21e1cde6); /* 25 */
        inner_gg (d, a, b, c, x[14],  9, 0xc33707d6); /* 26 */
        inner_gg (c, d, a, b, x[ 3], 14, 0xf4d50d87); /* 27 */
        inner_gg (b, c, d, a, x[ 8], 20, 0x455a14ed); /* 28 */
        inner_gg (a, b, c, d, x[13],  5, 0xa9e3e905); /* 29 */
        inner_gg (d, a, b, c, x[ 2],  9, 0xfcefa3f8); /* 30 */
        inner_gg (c, d, a, b, x[ 7], 14, 0x676f02d9); /* 31 */
        inner_gg (b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */

        inner_hh (a, b, c, d, x[ 5],  4, 0Xfffa3942); /* 33 */
        inner_hh (d, a, b, c, x[ 8], 11, 0X8771f681); /* 34 */
        inner_hh (c, d, a, b, x[11], 16, 0X6d9d6122); /* 35 */
        inner_hh (b, c, d, a, x[14], 23, 0Xfde5380c); /* 36 */
        inner_hh (a, b, c, d, x[ 1],  4, 0Xa4beea44); /* 37 */
        inner_hh (d, a, b, c, x[ 4], 11, 0X4bdecfa9); /* 38 */
        inner_hh (c, d, a, b, x[ 7], 16, 0Xf6bb4b60); /* 39 */
        inner_hh (b, c, d, a, x[10], 23, 0Xbebfbc70); /* 40 */
        inner_hh (a, b, c, d, x[13],  4, 0X289b7ec6); /* 41 */
        inner_hh (d, a, b, c, x[ 0], 11, 0Xeaa127fa); /* 42 */
        inner_hh (c, d, a, b, x[ 3], 16, 0Xd4ef3085); /* 43 */
        inner_hh (b, c, d, a, x[ 6], 23,  0X4881d05); /* 44 */
        inner_hh (a, b, c, d, x[ 9],  4, 0Xd9d4d039); /* 45 */
        inner_hh (d, a, b, c, x[12], 11, 0Xe6db99e5); /* 46 */
        inner_hh (c, d, a, b, x[15], 16, 0X1fa27cf8); /* 47 */
        inner_hh (b, c, d, a, x[ 2], 23, 0Xc4ac5665); /* 48 */

        inner_ii (a, b, c, d, x[ 0],  6, 0xf4292244); /* 49 */
        inner_ii (d, a, b, c, x[ 7], 10, 0X432aff97); /* 50 */
        inner_ii (c, d, a, b, x[14], 15, 0Xab9423a7); /* 51 */
        inner_ii (b, c, d, a, x[ 5], 21, 0Xfc93a039); /* 52 */
        inner_ii (a, b, c, d, x[12],  6, 0X655b59c3); /* 53 */
        inner_ii (d, a, b, c, x[ 3], 10, 0X8f0ccc92); /* 54 */
        inner_ii (c, d, a, b, x[10], 15, 0Xffeff47d); /* 55 */
        inner_ii (b, c, d, a, x[ 1], 21, 0X85845dd1); /* 56 */
        inner_ii (a, b, c, d, x[ 8],  6, 0X6fa87e4f); /* 57 */
        inner_ii (d, a, b, c, x[15], 10, 0Xfe2ce6e0); /* 58 */
        inner_ii (c, d, a, b, x[ 6], 15, 0Xa3014314); /* 59 */
        inner_ii (b, c, d, a, x[13], 21, 0X4e0811a1); /* 60 */
        inner_ii (a, b, c, d, x[ 4],  6, 0Xf7537e82); /* 61 */
        inner_ii (d, a, b, c, x[11], 10, 0Xbd3af235); /* 62 */
        inner_ii (c, d, a, b, x[ 2], 15, 0X2ad7d2bb); /* 63 */
        inner_ii (b, c, d, a, x[ 9], 21, 0Xeb86d391); /* 64 */
        
        aa += a;
        bb += b;
        cc += c;
        dd += d;
    }

// 	if ( lpextendbuf != tempbuf )
// 	{
// 		delete [] lpextendbuf;
// 	}

    memcpy(szOutBuf,(char *)&aa,4);
    memcpy(szOutBuf + 4,(char *)&bb,4);
    memcpy(szOutBuf + 8,(char *)&cc,4);
    memcpy(szOutBuf + 12,(char *)&dd,4);

    return(1);

}


//------------------------------------------------------------------------------------------------------------------------------
