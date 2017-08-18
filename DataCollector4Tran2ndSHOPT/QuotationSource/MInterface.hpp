//--------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ����ݽṹ��Ԫ
//      ..;;:  .;;,.;;:',;;"					��ע��Ϣ��
//    ,;;;;;;" :;`',;",;;"						
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------
#ifndef __TransrvPlat_InterfaceH__
#define __TransrvPlat_InterfaceH__
//--------------------------------------------------------------------------------------------------------------------------
#include <vadefs.h>
class MControlBaseClass;
//--------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//..........................................................................................................................
//�����ǻ�����־���Ͷ���
//..........................................................................................................................
#define VIEW	0
#define INFO	1
#define WARN	2
#define ERR		3 
#define REPORT	4
//add by liuqy 20101027 for �µļ�������ı�־���汾��״̬���� 
#define DRV_STATIS_MAGIC       0xF81115
#define DRV_STATIS_VERSION      0

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//..........................................................................................................................
//������Э������
//..........................................................................................................................
typedef struct												//�г�����������ȫ�г����ݵ�����
{
	unsigned char					MarketID;				//�г����
} tagCcComm_MarketApply;
//..........................................................................................................................
typedef struct												//�г��ֶ�����������ȫ�г����ݷֶ�ηֶ�����
{
	unsigned char					MarketID;				//�г����
	unsigned short					ApplyOffset;			//��ʼ���[�󲿷�Э��ָ��Ʒ����ţ�����һ������ָ�ض����ݵ���ţ�����������������ж�]
} tagCcComm_MarketSubApply;
//..........................................................................................................................
typedef struct
{
	unsigned short					ApplyEnd;				//����������Ľ���λ��[Ŀǰ�����������Ʒ��ĳ������λ��]
} tagCcComm_MarketSubResponse;
//..........................................................................................................................
typedef struct												//�г����ݸ�������ʱ��[���������������]
{
	unsigned long					Date;					//��������
	unsigned long					Time;					//����ʱ��
} tagCcComm_MarketUpdateTime;
//................................................................................................................
typedef struct												//ʱ����Ϣ
{
	unsigned long					CurTime;				//��ǰ�г�ʱ��{HHMMSS��ʽ]
} tagCcComm_TimeInfo;
//--------------------------------------------------------------------------------------------------------------------------
//[2��0] ��¼���鴫��ϵͳ������

//����MAIN_FRAME_HEAD | tagCcComm_CertityApply
//Ӧ��MAIN_FRAME_HEAD

typedef struct												//�û���¼����
{
	char							UserName[32];			//�û�����
	char							PassWord[16];			//�û�����
	char							MacAddr[12];			//����������ַ[������ڶ����������ȡ��һ��]
	unsigned long					ClientVersion;			//���鴫��ͻ��˰汾��[(�汾*100)<<16|�����]
	unsigned short					ClientType;				//�ͻ�������[��Ӧ�������ĵĲ�Ʒ���ͱ��]
	unsigned char					MarketId;				//��¼�г�
	char							Reserved[33];			//����
} tagCcComm_CertityApply;

//ע�⣺
//�������ǲ���DES���м��ܵģ������������������Ա��ȡ��<2009-1-21 Lumy����>
//--------------------------------------------------------------------------------------------------------------------------
//[2��1]�����г���Ϣ[���������г�ȫ��ͳһ]

//����MAIN_FRAME_HEAD | tagCcComm_MarketApply
//Ӧ��MAIN_FRAME_HEAD | �г���Ϣ
//ע�⣺�г���Ϣ = tagCcComm_MarketInfoHead | tagCcComm_MarketInfoDetail | tagCcComm_MarketInfoDetail | ...
//�ṹtagCcComm_MarketInfoDetail��������tagCcComm_MarketInfoHeadָ������ͬ��

typedef struct												//�г���Ϣͷ���ṹ
{
	unsigned char					MarketID;				//�г����
	unsigned char					MarketStatus;			//�г�״̬[0��ʾ��ʼ�� 1��ʾ������]
	unsigned long					Date;					//�г�����[YYYYMMDD��ʽ]
	unsigned long					Time;					//�г�ʱ��[HHMMSS��ʽ]
	unsigned short					WareCount;				//��Ʒ����[����ָ���͸��ɵ����е���Ʒ]
	unsigned char					KindCount;				//�������
	unsigned short					Periods[4][2];			//����ʱ�������[���֧��4��ʱ�Σ�ÿ��ʱ�μ�¼��ʼ�ͽ���ʱ�䣬��ȷ�����ӣ�HH * 60 + MM��ʽ]
	unsigned char					PeriodsCount;			//����ʱ���
	char							TimeZoom;				//���г�Ŀǰ����ʱ��[�й�����+8��]
	unsigned short					DelayTime;				//������ʱʱ��[��λ����]
	char							CheckCode [16];			//�г�У���루����ԭ����һ�����У���룩<2009-1-21 Lumy����>
} tagCcComm_MarketInfoHead;

//ע�⣺
//�г�У���� = ���У���� + �г���Ϣ���������������Ϣ�����⴦����У����
//�г���Ϣ�����������Ϣ�����⴦�� �����������ֶ���У��ʱ��0��Ȼ�����У��
//unsigned char					MarketStatus;			//�г�״̬[0��ʾ��ʼ�� 1��ʾ������]
//unsigned long					Time;				//�г�ʱ��[HHMMSS��ʽ]
//char							CheckCode [16];		//�г�У����

//У������Ӳ��������㷨��
//����һ���ڴ�ռ� = �������ĳ��� + �г���Ϣ���������������Ϣ���ĳ��ȣ����������г���Ϣ����������ÿռ��У�Ȼ�����MD5У��
//��������ʹ�������仯�����г���Ϣ�仯���������ϵ�ϵͳҲ�ܹ��������г�ʼ���ˡ�
//�������������ϲ����ӶϿ����������ӳɹ������������г���Ϣ��Ȼ��Ƚ��ڴ���ԭ�е��г���Ϣ����������г���ϢУ�����Ƿ�һ�£������һ�£���Ҫ�����������Ȩ֤����ծ��ȫ�г�ָ�����ݺ�ȫ�г��������ݵȵ���Ϣ������֪ͨ����ƽ̨�Ͽ�����һ�����г������ӡ����һ�£���ֱ������ȫ�г�ָ�����ݺ�ȫ�г��������ݡ�

typedef struct
{
	char							KindName[8];			//��������
	unsigned char					PriceRate;				//������м۸�Ŵ���[10�Ķ��ٴη�]
	unsigned short					LotSize;				//�������"��"����
	unsigned short					WareCount;				//������Ʒ������
} tagCcComm_MarketInfoDetail;
//--------------------------------------------------------------------------------------------------------------------------
//[2��2]�����Ϻ�֤ȯ�г�L1��L2������֤ȯ�г�L1���ܱ��г����Ϻ��ƽ�����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ShNameTable | tagCcComm_ShNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��

typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ���[��ӦMarketInfo�е����]
	char							Code[6];				//��Ʒ����
	char							Name[8];				//��Ʒ����
	char							PreName[4];				//���ǰ׺[�������г����Ϻ��г�����]
} tagCcComm_ShNameTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��3]�����Ϻ�֤ȯ�г�L1���Ϻ�L2������֤ȯ�г�L1������L2��ծ��Ϣ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_Gzlx | tagCcComm_Gzlx | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					StartDate;				//�Ϻ�[��Ϣ����]����[��Ϣ����]��YYYYMMDD��ʽ
	unsigned long					EndDate;				//�Ϻ�[��Ϣ����]����[��������,YYYYMMDD��ʽ]
	unsigned long					Yjlx;					//Ӧ����Ϣ[�Ŵ�10000��]
	unsigned long					Pmlx;					//Ʊ����Ϣ[�Ŵ�10000��]
} tagCcComm_Gzlx;
//--------------------------------------------------------------------------------------------------------------------------
//[2��4]�����Ϻ�֤ȯ�г�L1���Ϻ�L2������֤ȯ�г�L1������L2Ȩ֤��Ϣ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_Qzxx | tagCcComm_Qzxx | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	char							XqCode[6];				//��Ȩ����
	char							BdCode[6];				//���֤ȯ����
	char							Kind;					//Ȩ֤����['C'�Ϲ� 'P'�Ϲ�]
	unsigned __int64				BlanceVolume;			//Ȩ֤��ͨ����[��]
	unsigned __int64				TotalVolume;			//Ȩ֤��������[��]
	char							JsMode;					//���㷽ʽ["C"��ʾ�ֽ���㷽ʽ��"S"��ʾ֤ȯ�������㷽ʽ]
	char							XqMode;					//��Ȩ��ʽ['A'��ʽȨ֤��Ȩ 'E'ŷʽȨ֤��Ȩ 'B'��Ľ��ʽȨ֤��Ȩ]
	unsigned long					JsPrice;				//����۸�[�Ŵ�1000��]
	unsigned long					XqPrice;				//��Ȩ�۸�[�Ŵ�1000��]
	unsigned long					XqScale;				//��Ȩ����[�Ŵ�10000��]
	unsigned long					OnDate;					//Ȩ֤��������[YYYYMMDD��ʽ]
	unsigned long					DeDate;					//Ȩ֤��������[YYYYMMDD��ʽ]
	unsigned long					QonDate;				//��Ȩ��ʼ����[YYYYMMDD��ʽ]
	unsigned long					QdeDate;				//��Ȩ��ֹ����(�Ϻ���ʾ�����ʹ������)[YYYYMMDD��ʽ]
	unsigned long					UpdateDate;				//������¼��������[YYYYMMDD��ʽ]
	unsigned long					UpdateTime;				//������¼����ʱ��[HHMMSS��ʽ]
} tagCcComm_Qzxx;
//--------------------------------------------------------------------------------------------------------------------------
//[2��5]��������֤ȯ�г�L1������֤ȯ�г�L2���ջ���ֵ[ע�⣺������֤ȯ�г����Ϻ�û�и�����]

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_SZJjjz | tagCcComm_SZJjjz | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					Price;					//����ֵ[�Ŵ�10000��]	
} tagCcComm_SZJjjz;
//--------------------------------------------------------------------------------------------------------------------------
//[2��6]�����Ϻ�֤ȯ�г�L1���Ϻ�L2������֤ȯ�г�L1������L2�����֤ȯ�г�������ָ��ȫ�г�ָ����������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_IndexData | tagCcComm_IndexData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					High;					//���ָ��[* �Ŵ���]
	unsigned long					Open;					//����ָ��[* �Ŵ���]
	unsigned long					Low;					//���ָ��[* �Ŵ���]
	unsigned long					Close;					//����ָ��[* �Ŵ���]
	unsigned long					Now;					//����ָ��[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
} tagCcComm_IndexData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��7]�����Ϻ�֤ȯ�г�L1������֤ȯ�г�L1���ܱ��г�(���и���)���ɿ�������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_StockData5 | tagCcComm_StockData5 | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned long					Price;					//ί�м۸�[* �Ŵ���]
	unsigned __int64				Volume;					//ί����[��]
} tagCcComm_BuySell;

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					Records;				//�ɽ�����
	unsigned long					HighLimit;				//��ͣ�۸�[* �Ŵ���]��ע�⣺�Ϻ�L1�г�Դͷû�У���Դ�������м���<2009-1-21 Lumy����>
	unsigned long					LowLimit;				//��ͣ�۸�[* �Ŵ���] ��ע�⣺�Ϻ�L1�г�Դͷû�У���Դ�������м���<2009-1-21 Lumy����>
	tagCcComm_BuySell				Buy[5];					//����
	tagCcComm_BuySell				Sell[5];				//����
	unsigned long					Voip;					//����ģ�⾻ֵ��Ȩ֤���[�Ŵ�1000��][ETF������LOF��Ȩ֤��ֵ��Ч]
} tagCcComm_StockData5;


//[2��8]������չ���ƴ������Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_NameTableEx | tagCcComm_NameTableEx

typedef struct
{
	char							Code[6];				//���ƴ����
	unsigned short					MKind;					//����
	unsigned char					CType;					//��ϸ���ί��ʹ�õķ���
	unsigned char					BType;					//�������A��B�ɵ�
	unsigned char					SFlag;					//ͣ�Ʊ�ǣ��Ƿ�ɽ��ף���Ҫ����
	unsigned char					PLimit;					//�ǡ���ͣ�Ƿ���Ч
	unsigned long					Worth;					//ÿ����ֵ��*�Ŵ���10000
	unsigned long					ExTts;					//���׵�λ
	unsigned long					MaxExVol;				//���������
	unsigned long					MinExVol;				//��С��������
} tagCcComm_NameTableEx;

//[2��14]����ɷ�ת�÷ֲ���Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_NeeqLayer | tagCcComm_NeeqLayer

typedef struct
{
	char						Code[6];				//����
	unsigned char				LayerType;				//�г��ֲ����255Ϊ�գ�������ֵ���г�һ��
	unsigned char				uchVer;					//�汾�ţ�0��ʾֻ��LayerTypeID
	unsigned char				uchTmp[6];				//Ԥ��
} tagCcComm_NeeqLayer;


//[2,9]������չ���ƴ�����Ϣ�ı仯
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �仯����
//�仯���� = �������� + ���� + ����
//����	= char[6]
//�������� = unsigned char
//���� 0 = ͣ�Ʊ��(unsigned char)
//���� 1 = ���������(unsigned long)
//���� 2 = ��С��������(unsigned long)
//���� 3 = ÿ����ֵ(unsigned long)
//���� 4 = ���׵�λ(unsigned long)

//[2��10]�����Ϻ�֤ȯ�г�L1��L2ծȯָ����ֵ

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ShZJGZ | tagCcComm_ShZJGZ | ...

typedef struct
{
	char						Code[6];				//��Ʒ����
	unsigned long				BondValuation;			//ծȯ��ֵ *�Ŵ���10000
} tagCcComm_ShZJGZ;

//--------------------------------------------------------------------------------------------------------------------------
//[2��11] ��۰��ָ����������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD|tagCcComm_MarketSubResponse| tagCcComm_HkIndexData| tagCcComm_HkIndexData | ...

typedef struct
{
	char						Code[6];				// ��Ʒ����
	unsigned long				High;					// ��߼۸�[* �Ŵ���]
	unsigned long				Open;					// ���̼۸�[* �Ŵ���]
	unsigned long				Low;					// ��ͼ۸�[* �Ŵ���]
	unsigned long				Close;					// ���ռ۸�[* �Ŵ���]
	unsigned long				Now;					// ���¼۸�[* �Ŵ���]
	double					Amount;						// �ܳɽ����[Ԫ]
	unsigned __int64			Volume;					// �ܳɽ���[��]
	double					dTotalLTG;					// ��ͨ�ɱ�	ȨϢ��Ҫ���ֶ�
	double					dTotalZGB;					// �ܹɱ�	����
	double					dTotalValue;				// ����ֵ
	double					dMarketValue;				// ��ͨ��ֵ
	unsigned short				ushTotal;				// �����ܼ���[ָ������ʼ��ʱ����]
	unsigned short				ushRise;				// ���Ǽ���[ָ�������в��ϱ仯]
	unsigned short				ushDown;				// �µ�����[ָ�������в��ϱ仯]
	unsigned long				ulEarnRate;				// ��ӯ�� [��100]
	long						lNetRate;				// �о��� [��100]
	short					shAvgZF;					// ƽ������[��λ%����100������޵�λ�����10000]
	unsigned __int64		uiVBuy;						// ��ί����[��λ����]
	unsigned __int64		uiVSell;					// ��ί����[��λ����] 
	char				szUpCode[7];					// ���ǹɴ��룫���ǹ��г����
} tagCcComm_HkIndexData;

//--------------------------------------------------------------------------------------------------------------------------
//[2��17]�ͻ������������г�����[��Ӧ�������г�]

//����MAIN_FRAME_HEAD | tagCcComm_MarketApply
//Ӧ��MAIN_FRAME_HEAD

//ע�⣺����ϵͳ���յ�����������ÿͻ�������ȫ�г�����
//--------------------------------------------------------------------------------------------------------------------------
//[2��50]�����Ϻ�֤ȯ�г�L1������֤ȯ�г�L1���ܱ��г�������ָ������<2009-1-21 Lumy����>

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1������ָ������ =	  	tagCcComm_IndexData
//���� 2: ������Ʒ�������� =	tagCcComm_StockData5
//���� 3�����ǰ׺��� =	tagCcComm_SzPerNameChg
//���� 4: �ܱ��г����׶� = [2,57]��鹱�׶�ֵ
//���� 5: �ܱ��г��ǵ����� = [2,58]����ǵ���������

typedef struct
{
	unsigned char					MarketID;				//�г����
	unsigned long					MarketDate;				//�г�����[YYYYMMDD��ʽ]
	unsigned long					MarketTime;				//�г�ʱ��[HHMMSS��ʽ]
	unsigned char					MarketStatus;			//�г�״̬[0��ʼ��״̬ 1������״̬]
} tagCcComm_MarketStatusInfo;

//ע�⣺
//Դ�������������ڡ�����ʱ�䡢�г�״̬�κ�һ�������仯ʱ���¼����͸��г�״̬��Ϣ��
//���������ڱ�����ȷ����Ҫ������ȫ��ʼ��ʱ��Ҫ�Ͽ����¼����г������ӣ�ԭ��Ϊ���͸��г�״̬��Ϣ������ν��Ҫ��ȫ��ʼ�������Ǳ��������ϲ����ӶϿ������������ӵ��µ��ϲ㣬����ȡ���г���Ϣ��У�������ϴ���ȫ��һ������Ҫ��������������·����ڴ�ṹ�ȣ����ǳ�Ϊ��ȫ��ʼ����<2009-1-21 Lumy����>

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	char							PreName[4];				//��Ʒǰ׺
} tagCcComm_SzPerNameChg;
//--------------------------------------------------------------------------------------------------------------------------
//[2��13]�����Ϻ�֤ȯ�г�L2������L2���ɿ�������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_StockData5 | tagCcComm_StockData5 | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					Records;				//�ɽ�����
	unsigned long					VBuyPrice;				//ί�����[* �Ŵ���]
	unsigned __int64				VBuyVolume;				//ί������[��]
	unsigned long					VSellPrice;				//ί������[* �Ŵ���]
	unsigned __int64				VSellVolume;			//ί������[��]
	tagCcComm_BuySell				Buy[10];				//����
	tagCcComm_BuySell				Sell[10];				//����
	unsigned long					Voip;					//����ģ�⾻ֵ[�Ŵ�1000��][ETF������LOF��ֵ��Ч]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					HighLimit;				//��ͣ�۸�[* �Ŵ���]
	unsigned long					LowLimit;				//��ͣ�۸�[* �Ŵ���]
} tagCcComm_StockData10;
//--------------------------------------------------------------------------------------------------------------------------
//[2��14]�����Ϻ�֤ȯ�г�L1��L2�۶� //add by jiangb 2015.11

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_TradingPhaseCode | tagCcComm_TradingPhaseCode | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
    char                                   Code[6];              //��Ʒ����
    char                                   Fusing;               ///< �۶ϱ�־����S����ʾ����������ǰ��ʱ�Σ���C����ʾ���Ͼ���ʱ�Σ���T����ʾ��������ʱ�Σ���B����ʾ��                                          
                                                                 ///��ʱ�Σ���E����ʾ����ʱ�Σ���P����ʾ��Ʒͣ�ƣ���M����ʾ�ɻָ����׵��۶�ʱ�Σ����м��Ͼ��ۣ�����N��
                                                                 ///��ʾ���ɻָ����׵��۶�ʱ�Σ���ͣ���������У�����D��        ��ʾ���Ͼ��۽׶ν������������۽�///�ο�ʼ֮ǰ��ʱ�Σ����У����ո�Ϊ������
    char                                   Declaration;          //< �걨��־��'0'�������¶����걨;'1'�ɽ����¶����걨;��������ո�
    char                                   Reserve[8];           //< ������Ϊ�Ժ���չ
} tagCcComm_TradingPhaseCode;
//--------------------------------------------------------------------------------------------------------------------------
//[2��19]�����Ϻ�֤ȯ�г�L2��ί����������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_OrderRankingData | tagCcComm_OrderRankingData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned __int64				VBuySellVol;			//ί������[��]
	unsigned __int64				TradeVol;				//��������[��]
	double							TradeAmount;			//�����ܽ��[Ԫ]
} tagCcComm_OrderRankingDetail;

typedef struct
{
	unsigned char					WareType;				//��Ʒ���[��L2��Ʒ���ת����ΪMarketInfo�е���Ʒ���] <2009-1-21 Lumy����>
	unsigned char					Side;					//���׷���[0 �� 1 ��]
	tagCcComm_OrderRankingDetail	Records[10];			//��������
} tagCcComm_OrderRankingData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��21]�����Ϻ�֤ȯ�г�L2����ʱ��������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_CancelRankData | tagCcComm_CancelRankData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					Time;					//ί��ʱ��[HHMMSS��ʽ]
	unsigned long					Price;					//ί�м۸�[* �Ŵ���]
	unsigned __int64				Volume;					//ί������[��]
} tagCcComm_CancelRankDetail;

typedef struct
{
	unsigned char					WareType;				//��Ʒ���[��L2��Ʒ���ת����ΪMarketInfo�е���Ʒ���] <2009-1-21 Lumy����>
	unsigned char					Side;					//���׷���[0 �� 1 ��]
	tagCcComm_CancelRankDetail		Records[10];			//��������
} tagCcComm_CancelRankData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��23]�����Ϻ�֤ȯ�г�L2���ۼƳ�������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_TotalCancelRank | tagCcComm_TotalCancelRank | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned __int64				Volume;					//��������[��]
} tagCcComm_TotalCancelDetail;

typedef struct
{
	unsigned char					WareType;				//��Ʒ���[��L2��Ʒ���ת����ΪMarketInfo�е���Ʒ���] <2009-1-21 Lumy����>
	unsigned char					Side;					//���׷���[0 �� 1 ��]
	tagCcComm_TotalCancelDetail		Records[10];			//��������
} tagCcComm_TotalCancelRank;
//--------------------------------------------------------------------------------------------------------------------------
//[2��42]�����Ϻ�L2��������

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =            tagCcComm_MarketStatusInfo
//���� 2������ָ������ =	  	tagCcComm_IndexData
//���� 3: ��ʳɽ� =			tagCcComm_ShL2TransData
//���� 4��ί������ =			tagCcComm_OrderRankingData
//���� 5����ʱ���� =			tagCcComm_CancelRankData
//���� 6���ۼƳ��� =			tagCcComm_TotalCancelRank
//���� 7��ί�ж��� =    (L2)	tagCcComm_OrderQueueHead | tagCcComm_OrderVolDetail | tagCcComm_OrderVolDetail | ...
//                      (L2fast)tagCcComm_OrderQueueHeadL2Fast | tagCcComm_OrderPrice | tagCcComm_OrderVolDetail | ...  | tagCcComm_OrderPrice | tagCcComm_OrderVolDetail ...    
//���� 8����ǰ����۸� =	  	tagCcComm_VirtualPrice
//���� 25 ������Ʒ�������� =	tagCcComm_StockData5

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					TransNo;				//�������
	unsigned long					TransTime;				//����ʱ��[HHMMSS��ʽ]
	unsigned long					TransPrice;				//���׼۸�[* �Ŵ���]
	unsigned __int64				TransVolume;			//�ɽ���[��]
} tagCcComm_ShL2TransData;

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					virtualprice;			//����۸�[* �Ŵ���]
	unsigned __int64				virtualvolume;			//����ƥ����[��]
	unsigned __int64				buyvirtualvol;			//������ƥ����[��]
	unsigned __int64				sellvirtualvol;			//��������ƥ����[��]
} tagCcComm_VirtualPrice;

typedef struct
{
	char							Code[6];				//��Ʒ����
	unsigned char					Side;					//��������[0 �� 1 ��]
	unsigned long					Price;					//ί�м۸�[* �Ŵ���]
	unsigned short					VolCount;				//ί�з�������[ע�⣺�����ֵ����50����ô������ŵķ���ֻ��Ϊ50��]
} tagCcComm_OrderQueueHead;

typedef struct
{
	char							Code[6];				//��Ʒ����
	unsigned char					Side;					//��������[0 �� 1 ��]
	unsigned char					PriceCount;				//��λ��
} tagCcComm_OrderQueueHeadL2Fast;

typedef struct
{
	unsigned long					Price;					//ί�м۸�[* �Ŵ���]
	unsigned short					VolCount;				//ί�з�������[ע�⣺�����ֵ����200����ô������ŵķ���ֻ��Ϊ200��]
} tagCcComm_OrderPrice;

typedef struct
{
	unsigned __int64				Volume;					//��������
} tagCcComm_OrderVolDetail;

//--------------------------------------------------------------------------------------------------------------------------
//[2��27]�������֤ȯ�г������ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HkNameTable | tagCcComm_HkNameTable | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ����
	char							Code[6];				//��Ʒ����
	char							EnglishName[16];		//Ӣ������
	char							ChineseName[16];		//��������
	char							SName[8];				//���ļ��
	unsigned long					ListDate;				//��������
	unsigned long					OffDate;				//��������
	unsigned long					SpreadValue;			//���[* �Ŵ���]
	unsigned long					LotSize;				//����Ʒ��"��"����
	unsigned char					Currency;				//��������
	unsigned char					PriceTb;				//ʹ�����ż�λ��
	float							NrRate;					//�޷�������
} tagCcComm_HkNameTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��28]�������֤ȯ�г���Ȩ֤��Ϣ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_QzxxHK | tagCcComm_QzxxHK | ...
//ע�⣺���ؽ���е�tagCcComm_MarketUpdateTime�ṹ����ʾ�������˱��г�Ȩ֤��Ϣ�ĸ���ʱ�䡣
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����
	char							XqCode[6];				//��Ȩ����
	char							BdCode[6];				//���֤ȯ����
	char							Kind;					//Ȩ֤����['C'�Ϲ� 'P'�Ϲ���ţ��֤Ϊ'c'��'p']
	unsigned __int64				BlanceVolume;			//Ȩ֤��ͨ����[��]
	unsigned __int64				TotalVolume;			//Ȩ֤��������[��]
	char							JsMode;					//���㷽ʽ["C"��ʾ�ֽ���㷽ʽ��"S"��ʾ֤ȯ�������㷽ʽ]
	char							XqMode;					//��Ȩ��ʽ['A'��ʽȨ֤��Ȩ 'E'ŷʽȨ֤��Ȩ 'B'��Ľ��ʽȨ֤��Ȩ,ţ��֤��Ȩ��ʽ'N'����'R']
	unsigned long					JsPrice;				//����۸�[�Ŵ�1000��]
	unsigned long					XqPrice;				//��Ȩ�۸�[�Ŵ�1000��]
	unsigned long					XqScale;				//��Ȩ����[�Ŵ�1000��]
	unsigned long					CallPrice;				//ţ��֤ǿ�ƻ��ռ�[�Ŵ�1000��]
	unsigned __int64				JhVolume;				//Ȩ֤�ֻ��� 
	unsigned long					OnDate;					//Ȩ֤��������[YYYYMMDD��ʽ]
	unsigned long					DeDate;					//Ȩ֤��������[YYYYMMDD��ʽ]
	unsigned long					QonDate;				//��Ȩ��ʼ����[YYYYMMDD��ʽ]
	unsigned long					QdeDate;				//��Ȩ��ֹ����(�Ϻ���ʾ�����ʹ������)[YYYYMMDD��ʽ]
	unsigned long					UpdateDate;				//������¼��������[YYYYMMDD��ʽ]
	unsigned long					UpdateTime;				//������¼����ʱ��[HHMMSS��ʽ]
} tagCcComm_QzxxHK;
//--------------------------------------------------------------------------------------------------------------------------
//[2��29]�������֤ȯ�г���������������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | ĳ��Ʒ������������ | ĳ��Ʒ������������ | ...
//���У�ĳ��Ʒ������������ = tagCcComm_HKRelateTable | tagCcComm_HKRelateCode | tagCcComm_HKRelateCode | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned short					Count;					//������Ʒ������[���500����������tagCcComm_HKRelateCode�ṹ������]
} tagCcComm_HKRelateTable;

typedef struct
{
	unsigned char					MarketID;				//�г����<2009-1-21 Lumy����>
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
} tagCcComm_HKRelateCode;
//--------------------------------------------------------------------------------------------------------------------------
//[2��30]�������֤ȯ�г����������б�����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKBrokerTable | tagCcComm_HKBrokerTable | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned short 					BrokerSerial;			//���
	char							Name[8];				//�����̼��
	char							FullName[32];			//������ȫ��
	unsigned short       			StartNumber;			//��ʼ���ͺ���
	unsigned short 					EndNumber;				//�������ͺ���
	unsigned long					UpdateDate;				//������¼��������[YYYYMMDD��ʽ]
	unsigned long					UpdateTime;				//������¼����ʱ��[HHMMSS��ʽ]
} tagCcComm_HKBrokerTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��31]�������֤ȯ�г���ȫ�г����ɿ�������(5������)[�𲽱�2,32Э��ȡ��]

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKStockData | tagCcComm_HKStockData | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned __int64				Volume;					//ί������[��]
	unsigned short					Records;				//ί�б���
} tagCcComm_HKBuySell;

#ifdef __3X_HK__
typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					VBuyPrice;				//ί��۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VBuy[5];				//5������
	unsigned long					VSellPrice;				//ί���۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VSell[5];				//5������
} tagCcComm_HKStockData;
#else
typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					VBuyPrice;				//ί��۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VBuy[5];				//5������
	unsigned long					VSellPrice;				//ί���۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VSell[5];				//5������
	unsigned long					Voip;					//Ȩ֤���
} tagCcComm_HKStockData;
#endif

//--------------------------------------------------------------------------------------------------------------------------
//[2��32]�������֤ȯ�г���ȫ�г����ɿ�������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKStockDataEx | tagCcComm_HKStockDataEx | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					VBuyPrice;				//ί��۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VBuy[10];				//5������
	unsigned long					VSellPrice;				//ί���۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VSell[10];				//5������
	unsigned long					Voip;					//Ȩ֤���
} tagCcComm_HKStockDataEx;
//--------------------------------------------------------------------------------------------------------------------------
//[2��33]�������֤ȯ�г������ƴ���� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HkIdxNameTable | tagCcComm_HkIdxNameTable | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ����
	char							Code[6];				//��Ʒ����
	char							EnglishName[16];		//Ӣ������
	char							ChineseName[16];		//��������
	char							SName[8];				//���ļ��
	unsigned long					ListDate;				//��������
	unsigned long					OffDate;				//��������
	unsigned long					SpreadValue;			//���[* �Ŵ���]
	unsigned long					LotSize;				//����Ʒ��"��"����
	unsigned char					Currency;				//��������
	unsigned char					PriceTb;				//ʹ�����ż�λ��
	float							NrRate;					//�޷�������
	unsigned char					uchFlags;				//�ر��־��0x01:�ȵ�ָ��(�ñ�־��Դ�������İ�������ļ�) 
} tagCcComm_HkIdxNameTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��35]�������֤ȯ�г���ȫ�г�������λ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | ĳ��Ʒ������λ���� | ĳ��Ʒ������λ���� | ...
//���У�ĳ��Ʒ������λ���� = tagCcComm_HKJjpwDataRequest | tagCcComm_HKJjpwDetail | tagCcComm_HKJjpwDetail | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned char					BCount;					//�򷽵���
	unsigned char					ACount;					//��������
} tagCcComm_HKJjpwDataRequest;

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	bool							Side;					//��������[true �� false ��]
	unsigned char					Count;					//��Ч����[���40��]
} tagCcComm_HKJjpwDataPush;

typedef struct
{
	short							S_Broker;				//S_Broker<0����ʾ������λ��S_Broker>=0����ʾ���ͺ���
} tagCcComm_HKJjpwDetail;
//--------------------------------------------------------------------------------------------------------------------------
//[2��37]������ۼ�λ��

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_PriceTable | tagCcComm_PriceTable | tagCcComm_PriceTable
//ע��������tagCcComm _PriceTable
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned long					PriceTo;				//�۸�ȥ��, ����3λС��
	unsigned short					SpreadValue;			//ǰһ���۸�ȥ�򣨻��߼۸���Դ�� ����ǰ�۸�ȥ��, ����3λС��
} tagCcComm_PriceItem; 

typedef struct
{
	char							SpreadTableCode[2];		//��λ����
	unsigned long 					PriceFrom;				//��λ�����Ͷ����۸�����3λС����
	unsigned short					ItemsNumber;			//��Ŀ�б��е���Ŀ������1~52
   	tagCcComm_PriceItem				PriceItem[52];			//��λ����
} tagCcComm_PriceTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��38]�������֤���ض���������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | ĳ��Ʒ�ض��������� |��ĳ��Ʒ�ض��������ݡ�| ĳ��Ʒ�ض��������ݡ�|...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned short					PERatio;				//��ӯ��   ����1λС��. 
	unsigned long					CurrentYield;			//��Ϣ��   ����3λС��. 
	unsigned long					MaturityYield;			//֤ȯ��������, ����4λС��
	char							MaturityYieldIndi;		//ָ�����������ֶε����塣N-����, O-��ֵ, U-���泬ֵ, X-�����ṩ 
	__int64							Share_Out;				//���й��� 
	__int64							Market_Cap;				//����ֵ 
} tagCcomm_FinanceData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��40]���͸۹��г���������Ϣ

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������� | ����
//�������� = tagComm_NewsIndex | tagComm_SecuNI | tagComm_SecuNI | ������
//���š�����tagComm_NewsPage��| ���ݣ������ֽڣ�| ���ݣ������ֽڣ� |��������

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
} tagComm_SecuNI;

typedef struct
{
	unsigned char					NewsType;				//��������
	unsigned short					NewsId;					//����Ψһid
	unsigned char     				SecurityNumber;			//�������
}tagComm_NewsIndex;

typedef struct
{		
	unsigned __int64				DateTime;				//ʱ��/����
	unsigned char					LineNum;				//����
}tagComm_NewsPage;

typedef struct
{
	char							LineContext[80];		//��������
}tagCcomm_PGContext;
//--------------------------------------------------------------------------------------------------------------------------
//[2��41]���͸۹���������

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 1������ָ������ =  tagCcComm_IndexData
//���� 2��������Ʒ������λ���� =  tagCcComm_HKJjpwDataPush | tagCcComm_HKJjpwDetail | tagCcComm_HKJjpwDetail | ��
//���� 3��������Ʒ������ϸ���� =  tagCcComm_HKTradeData
//����13��������Ʒȫ���������� =  tagCcComm_HKStockData
//����14���г���Ϣ =  tagCcComm_MarketStatusInfo<2009-1-21 Lumy����>

//���� 15��������Ʒȫ���������� =  tagCcComm_HKStockDataEx, ȡ������13
typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					Price;					//���׼۸�[* �Ŵ���]
	unsigned __int64				Volume;					//��������[��]
	unsigned long					TradeTime;				//����ʱ��[HHMMSS��ʽ]
	unsigned char					TradeType;				//������������
} tagCcComm_HKTradeData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��43]�۹��ڻ��������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKFNameTable | tagCcComm_HKFNameTable | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ���[��ӦMarketInfo�е����]
	char							Code[6];				//��Ʒ����
	char							CHName[16];				//����ȫ��
	char							EnName[16];				//Ӣ�ļ��
	char							TargetCode[6];			//���ָ���Ĵ��룬�ޱ��ָ��ʱ���
	unsigned char					TargetMarketID;			//���ָ���г����(Ŀǰ�������»�25ָ������5������ָ������2��0xFF��ʾδ֪)
	unsigned long					ContractMultiplier;		//��Լ����
	unsigned long					Settle;					//�����۸�
	__int64							OpenInterest;			//��ֲ���(��λ����Լ)
	unsigned long					Close;					//���ռ۸�
	unsigned long					PreSettle;				//�����۸�
	__int64							PreOpenInterest;		//��ֲ���(��λ����Լ)
} tagCcComm_HKFNameTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��44]�۹��ڻ�����̬����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKFObjectData | tagCcComm_HKFObjectData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					sequenceID;				//�����(ÿ����Ʒ�������)
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	unsigned long					CurVolume;				//�ɽ�����
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					EstimatedSettlement;	//���ܽ���۸�
	unsigned long					Cop;					//Ԥ���̼۸�[* �Ŵ���]
	tagCcComm_BuySell				VBuy[5];				//5������
	tagCcComm_BuySell				VSell[5];				//5������
} tagCcComm_HKFObjectData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��45]�۹��ڻ�����̬����(��ǰ��ʼ��ʱ��������Ϊ�����Ѿ������������,����ʱҪ����)
				 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKFStaticData | tagCcComm_HKFStaticData | ...
//ע�⣺���������֧�ֶַ�����
				 
typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					Close;					//���ռ۸�
	unsigned long					Settle;					//�����۸�
	__int64							OpenInterest;			//��ֲ���(��λ����Լ)
	unsigned long					PreSettle;				//�����۸�
	__int64							PreOpenInterest;		//��ֲ���(��λ����Լ)
} tagCcComm_HKFStaticData;

//[2��46]���͸۹�ָ����������

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char
//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1������ָ������ =	  	tagCcComm_HkIndexData
//���� 2: ������Ʒ�������� =	tagCcComm_StockData5
//���� 4: �۹ɰ�ָ�г����׶� = [2,57]��鹱�׶�ֵ
//���� 5: �۹ɰ�ָ�г��ǵ����� = [2,58]����ǵ���������


//--------------------------------------------------------------------------------------------------------------------------
//[2��49]���͸۹��ڻ�����<2009-1-21 Lumy����>

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1���ɽ���ϸ =	  		tagCcComm_HKFTradeData
//���� 2: �嵵������ =		tagCcComm_HKFBuySellData;
//���� 3����̬���� =			tagCcComm_HKFStaticData

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					sequenceID;				//�����(ÿ����Ʒ�������)
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	unsigned long					CurVolume;				//�ɽ�����
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					EstimatedSettlement;	//���ܽ���۸�( Դ�յ�UT��ʱ������Чֵ������ֵȫ��0,���յ�TT��ʱ��ֵΪ0 )
	unsigned long					Cop;					//Ԥ���̼۸�
} tagCcComm_HKFTradeData;

typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned char					Side;					//��������(0 ��;1 ��)
	tagCcComm_BuySell				VBuy[5];				//5������
} tagCcComm_HKFBuySellData;

//--------------------------------------------------------------------------------------------------------------------------
//[2��51]���������ʡ������ڻ����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ForeignFutureNameTable| tagCcComm_ForeignFutureNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��

typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ���[��ӦMarketInfo�е����]
	char							PriceRate;				//���ķŴ���
	char							TimeZoom;				//��Ʒ����ʱ��
	char							Code[6];				//��Ʒ����
	char							Name[8];				//��Ʒ����
	unsigned short					Periods[2][2];			//��ָ��������ʱ��Σ����֧������,��Ч����ʼ������ʱ�����Ϊ0xFFFF
} tagCcComm_ForeignFutureNameTable;

//--------------------------------------------------------------------------------------------------------------------------
//[2��52]��������ڻ�

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ForeignFutureData | tagCcComm_ForeignFutureData | ...
typedef struct
{
    char							Code[6];				//��Ʒ����
    unsigned long					High;                   //��߼۸�[* �Ŵ���]
    unsigned long					Open;                   //���̼۸�[* �Ŵ���]
    unsigned long					Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long					Close;                  //���ռ۸�[* �Ŵ���]
    unsigned long					Now;                    //���¼۸�[* �Ŵ���]
	unsigned __int64			    NowVolume;				//����
    unsigned __int64           		Volume;                 //�ܳɽ���[��]
    unsigned __int64            	PreOpenInterest;        //���ճֲ���[��]
    unsigned __int64            	OpenInterest;           //�ֲ���[��]
	tagCcComm_BuySell				Buy;					//����
	tagCcComm_BuySell				Sell;					//����
} tagCcComm_ForeignFutureData;

//--------------------------------------------------------------------------------------------------------------------------
//[2��53]���͹����ڻ�����

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1���������� =	  	  tagCcComm_ForeignFutureData

//--------------------------------------------------------------------------------------------------------------------------
//[2��54]��������������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ForeignExchangeData | tagCcComm_ForeignExchangeData | ...
typedef struct
{
    char							Code[6];				//��Ʒ����
    unsigned long					High;                   //��߼۸�[* �Ŵ���]
    unsigned long					Open;                   //���̼۸�[* �Ŵ���]
    unsigned long					Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long					Close;                  //���ռ۸�[* �Ŵ���]
    unsigned long					Now;                    //���¼۸�[* �Ŵ���]
    unsigned __int64           		Volume;                 //�ܳɽ���[��]
	tagCcComm_BuySell				Buy;					//����
	tagCcComm_BuySell				Sell;					//����
} tagCcComm_ForeignExchangeData;

//--------------------------------------------------------------------------------------------------------------------------
//[2��55]���͹����������

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1���������� =	  	  tagCcComm_ForeignExchangeData


//[2��56]�������ָ�����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ForeignIndexNameTable0 | tagCcComm_ForeignIndexNameTable0 | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��
typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ���[��ӦMarketInfo�е����]
	char							PriceRate;
	char							TimeZoom;				//��Ʒ����ʱ��
	char							Code[6];				//��Ʒ����
	char							CName[16];				//��Ʒ��������
	char							EName[40];				//��ƷӢ������
	unsigned short					Periods[2][2];			//��ָ��������ʱ��Σ����֧������,��Ч����ʼ������ʱ�����Ϊ0xFFFF
} tagCcComm_ForeignIndexNameTable;

//[2��57]�����ܱ��г������ع��׶�
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | ���1����+���1�Ĺ��׶�ֵ | ���2����+���2�Ĺ��׶�ֵ | ........ | ���n����+���n�Ĺ��׶�ֵ 
//������� = tagCcComm_BlockInfo
//��鹱�׶�ֵ = tagCcComm_BlockContributeValue(�������) | ���׶�����(ǰ20) | ���׶�����(��20)

typedef struct
{
	char							Code[6];				//������
	char							Name[8];				//�������
} tagCcComm_BlockInfo;


typedef struct
{
	char							Code[6];				//����,���Դ��̵Ĺ��׶�ʱ����Ϊ����ָ������, �汾���׶������еĴ�����Ϊ�ɷֹɴ���
	char							MarketId;				//���������г���0��ʾ�Ϻ�, 1��ʾ����
	unsigned long					Price;					//�ּ�, �Ŵ�1000����
	double							CtbValue;				//����ֵ(�ǵ�����)
} tagCcComm_BlockContributeValue;

//[2��58]�����ܱ��г��������ǵ�������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | ���1����+���1���ǵ��������� (ǰ20)| ���2����+���2���ǵ��������� | ........ | ���n����+���n���ǵ��������� 
//������� = tagCcComm_BlockInfo
//�ǵ��������� = �ǵ���������(ǰ20) | �ǵ���������(��20)


//[2��59]��������L2�г� //�𲽱�[2,65]Э��ȡ��
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =            tagCcComm_MarketStatusInfo
//���� 1������ָ������ =	  	tagCcComm_IndexData
//���� 2  ������Ʒ�������� =	tagCcComm_StockData5
//���� 3: ��ʳɽ� =			tagCcComm_SzL2TransData
//���� 4: ���ί�� =			tagCcComm_SzL2OderData
//���� 5: ί�ж��� =			tagCcComm_OrderQueueHeadSzL2 | tagCcComm_OrderVolDetail | tagCcComm_OrderVolDetail | ...
//���� 6: ǰ׺�仯 =			tagCcComm_SzPerNameChg
//���� 7: ��ծ��Ϣ =			tagCcComm_Gzlx						

typedef struct
{
	char							Code[6];				//��Ʒ����
	char							TranType;				//�ɽ����
	unsigned long					TransNo;				//�������
	unsigned long					TransTime;				//����ʱ��[HHMMSS��ʽ]
	unsigned long					TransPrice;				//���׼۸�[* �Ŵ���]
	unsigned __int64				TransVolume;			//�ɽ���[��]
} tagCcComm_SzL2TransData;

typedef struct
{
	char							Code[6];				//��Ʒ����
	char							OrderType;				//ί�����
	unsigned long					OrderNo;				//ί�����
	unsigned long					OrderTime;				//ί��ʱ��[HHMMSS��ʽ]
	unsigned long					OrderPrice;				//ί�м۸�[* �Ŵ���]
	unsigned __int64				OrderVolume;			//ί����[��]
} tagCcComm_SzL2OderData;


typedef struct
{
	char							Code[6];				//��Ʒ����
	unsigned char					Side;					//��������[0 �� 1 ��]
	unsigned long					Price;					//ί�м۸�[* �Ŵ���]
	unsigned short					TVolCount;				//ί���ܱ�
	unsigned short					VolCount;				//��ʾί�з�������, ���200
} tagCcComm_OrderQueueHeadSzL2;

//--------------------------------------------------------------------------------------------------------------------------
//[2��65]ѹ��������L2�г�
//Э������ͬ[2��59]��ȫһ��, ��ȡ��[2,59]

//--------------------------------------------------------------------------------------------------------------------------
//[2��99]������Ʒ�ڻ����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CsfexNameTable | tagCcComm_CsfexNameTable | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	char							Type;
	char							Code[6];				//��Ʒ����
	char							Name[8];				//��Ʒ����
	unsigned long					LotFactor;				//��
} tagCcComm_CsfexNameTable;


//--------------------------------------------------------------------------------------------------------------------------
//[2��100]�����н�����ָ�ڻ����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexNameTable | tagCcComm_CffexNameTable | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
    unsigned short					Serial;                	//��Ʒ���
    unsigned char					Type;                  	//����Ʒ���[��ӦMarketInfo�е����]
	unsigned char					ObjectMId;				//���ָ���г����[�μ������ֵ�-�г����]��0xFF��ʾδ֪
	unsigned char					ExFlag;					//������ձ��,0x01��ʾ���������ֻ����ͨ��Լ��Ч������ֵ��δ����
    char							Code[6];                //��Ʒ����
    char							Name[8];               	//��Ʒ����
	char							ObjectCode[6];			//���ָ���Ĵ��룬�ޱ��ָ��ʱ���
	unsigned long					ContractMult;			//��Լ����
} tagCcComm_CffexNameTable;
//--------------------------------------------------------------------------------------------------------------------------
//[2��101]�����н�������Ʒ�ڻ����Ϻ��ƽ�ȫ�г���������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexStockData | tagCcComm_CffexStockData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
    char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
    unsigned long					High;                   //��߼۸�[* �Ŵ���]
    unsigned long					Open;                   //���̼۸�[* �Ŵ���]
    unsigned long					Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long					PreClose;               //���ռ۸�[* �Ŵ���]
    unsigned long					PreSettlePrice;         //���ս���۸�[* �Ŵ���]
    unsigned long					Now;                    //���¼۸�[* �Ŵ���]
    unsigned long					Close;                  //�������̼۸�[* �Ŵ���]
    unsigned long					SettlePrice;            //���ս���۸�[* �Ŵ���]
    unsigned long					UpperPrice;             //��ͣ�۸�[* �Ŵ���]
    unsigned long					LowerPrice;             //��ͣ�۸�[* �Ŵ���]
    double							Amount;                 //�ܳɽ����[Ԫ]
    unsigned __int64           		Volume;                 //�ܳɽ���[��]
    unsigned __int64            	PreOpenInterest;        //���ճֲ���[��]
    unsigned __int64            	OpenInterest;           //�ֲ���[��]
    tagCcComm_BuySell				Buy[5];                 //ί������
    tagCcComm_BuySell				Sell[5];                //ί������
} tagCcComm_CffexStockData;

//[2��102]�����н��ڻ���������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexStockDataEx | tagCcComm_CffexStockDataEx | ...
//ע�⣺���������֧�ֶַ�����

//[2��103]�����н��ڻ��������� 
//���ͣ�MAIN_FRAME_HEAD | unsigned long | unsigned char | tagCcComm_CffexStockDataEx 
//unsigned long ֵ��Ӧ�г�����ʱ��,
//unsigned char ֵ�Ƕ�Ӧ���͹�Ʊ��Ϣ��Э�����ͣ�
//StockPushType = 2; 

typedef struct
{
    unsigned int      DataTimeStamp;   //ʱ���(HHMMSSmmm)
    char              Code[6];    //��Ʒ����<2009-1-21 Lumy����>
    unsigned long     High;                   //��߼۸�[* �Ŵ���]
    unsigned long     Open;                   //���̼۸�[* �Ŵ���]
    unsigned long     Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long     PreClose;               //���ռ۸�[* �Ŵ���]
    unsigned long     PreSettlePrice;         //���ս���۸�[* �Ŵ���]
    unsigned long     Now;                    //���¼۸�[* �Ŵ���]
    unsigned long     Close;                  //�������̼۸�[* �Ŵ���]
    unsigned long     SettlePrice;            //���ս���۸�[* �Ŵ���]
    unsigned long     UpperPrice;             //��ͣ�۸�[* �Ŵ���]
    unsigned long     LowerPrice;             //��ͣ�۸�[* �Ŵ���]
    double       Amount;                 //�ܳɽ����[Ԫ]
    unsigned __int64             Volume;                 //�ܳɽ���[��]
    unsigned __int64             PreOpenInterest;        //���ճֲ���[��]
    unsigned __int64             OpenInterest;           //�ֲ���[��]
    tagCcComm_BuySell    Buy[5];                 //ί������
    tagCcComm_BuySell    Sell[5];                //ί������
} tagCcComm_CffexStockDataEx;

//[2, 106] �����н��ڻ��г�������չ��Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_KindPeriod | ��..

typedef struct
{	
	unsigned char                    Type;               // ���[��ӦMarketInfo�е����]
	unsigned char                    PeriodsCount;       // ʱ�������
	unsigned short                   Periods[4][2];      // ����ʱ���[���ֻ��4������ʱ�Σ�ÿ��ʱ�ΰ�����ʼ������ʱ�䣬��ȷ���֣�HH * 60 + MM��ʽ]
} tagCcComm_KindPeriod;


//--------------------------------------------------------------------------------------------------------------------------
//[2��103]�����н�����ָ�ڻ�����Ʒ�ڻ����Ϻ��ƽ���������<2009-1-21 Lumy����>

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1���������� =	  	  tagCcComm_CffexStockData
//--------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
//[2��108]�����н�����ָ�ڻ����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexOptNameTable | tagCcComm_CffexOptNameTable | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
    unsigned short    Serial;             //��Ʒ���
    unsigned char     Type;               //����Ʒ���[��ӦMarketInfo�е����]
    unsigned char     ObjectMId;          //���ָ���г����[�μ������ֵ�-�г����]��0xFF��ʾδ֪
    unsigned char     ExFlag;             //������ձ��,0x01��ʾ���������ֻ����ͨ��Լ��Ч������ֵ��δ����
    char              Code[32];           //��Ʒ����,�����������
    //char          Name[8];            //��Ʒ����,����Ӧ�ò���Ҫ��
    char              ObjectCode[6];      //���ָ���Ĵ��룬�ޱ��ָ��ʱ���
    unsigned long     ContractMult;       //��Լ����
    int                   ContractUnit;           //��Լ��λ
    unsigned char         SettlementMode;         //���㷽ʽ(1-ʵ��,2-�ֽ�)
    char                  OptionsType;            //��Ȩ����(E-ŷʽ,A-��ʽ)
    int                   StartDate;              //�׸�������(YYYYMMDD)
    int                   EndDate;                //�������(YYYYMMDD)
    int                   XqDate;                 //��Ȩ��(YYYYMMDD)
    int                   DeliveryDate;           //������(YYYYMMDD)
    int                   ExpireDate;             //������(YYYYMMDD)
} tagCcComm_CffexOptNameTable;

//--------------------------------------------------------------------------------------------------------------------------
//[2��109]�����н���ȫ�г���������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexOptStockData | tagCcComm_CffexOptStockData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned int      DataTimeStamp;          //ʱ���(HHMMSSmmm)
    char              Code[32];               //��Ʒ����,�����������
    unsigned long     High;                   //��߼۸�[* �Ŵ���]
    unsigned long     Open;                   //���̼۸�[* �Ŵ���]
    unsigned long     Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long     PreClose;               //���ռ۸�[* �Ŵ���]
    unsigned long     PreSettlePrice;         //���ս���۸�[* �Ŵ���]
    unsigned long     Now;                    //���¼۸�[* �Ŵ���]
    unsigned long     Close;                  //�������̼۸�[* �Ŵ���]
    unsigned long     SettlePrice;            //���ս���۸�[* �Ŵ���]
    unsigned long     UpperPrice;             //��ͣ�۸�[* �Ŵ���]
    unsigned long     LowerPrice;             //��ͣ�۸�[* �Ŵ���]
    double            Amount;                 //�ܳɽ����[Ԫ]
    unsigned __int64  Volume;                 //�ܳɽ���[��]
    unsigned __int64  PreOpenInterest;        //���ճֲ���[��]
    unsigned __int64  OpenInterest;           //�ֲ���[��]
    tagCcComm_BuySell Buy[5];                 //ί������
    tagCcComm_BuySell Sell[5];                //ί������
} tagCcComm_CffexOptStockData;
//--------------------------------------------------------------------------------------------------------------------------
//[2��110]�����н�����Ȩ����

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =          tagCcComm_MarketStatusInfo
//���� 1���������� =	  	  tagCcComm_CffoptStockData
//--------------------------------------------------------------------------------------------------------------------------

// add by liuqy 20100610 for �����ܱ��г���ָ�����ͽṹ
//modify by liuqy 2010707 for �����޸�ָ���ṹ
typedef struct
{
	char						Code[6];					// ��Ʒ����
	unsigned long				High;					// ��߼۸�[* �Ŵ���]
	unsigned long				Open;					// ���̼۸�[* �Ŵ���]
	unsigned long				Low;					// ��ͼ۸�[* �Ŵ���]
	unsigned long				Close;					// ���ռ۸�[* �Ŵ���]
	unsigned long				Now;					// ���¼۸�[* �Ŵ���]
	double					Amount;					// �ܳɽ����[Ԫ]
	unsigned __int64			Volume;					// �ܳɽ���[��]
	double					dTotalLTG;			// ��ͨ�ɱ�
	double					dTotalZGB;			// �ܹɱ�
	//delete by liuqy 20100823 for ��ʹ�����½ṹ
	/*
	double					dTotalJzc;			// ���ʲ��ۼӺ�
	unsigned __int64			uiDtNd;				// ��̬����ۼӺ�
	unsigned __int64			uiJtNd;				// ��̬����ۼӺ�	
	*/
	double					dTotalValue;				// ����ֵ
	double					dMarketValue;				// ��ͨ��ֵ
	double					dAdjustedMarketValue;		// �ּ�������ͨ��ֵ
	unsigned short				ushTotal;					// �����ܼ���[ָ������ʼ��ʱ����]
	unsigned short				ushRise;					// ���Ǽ���[ָ�������в��ϱ仯]
	unsigned short				ushDown;					// �µ�����[ָ�������в��ϱ仯]
	//delete by liuqy 20100823 for ��ʹ�����½ṹ
	//unsigned short				ushExchangeRate;			// ������ [��λ%����100������޵�λ�����10000]
	unsigned long				ulEarnRate;				// ��ӯ�� [��100]
	long						lNetRate;					// �о��� [��100]
	short					shAvgZF;					//ƽ������[��λ%����100������޵�λ�����10000]
	unsigned __int64		uiVBuy;					// ��ί����[��λ����]
	unsigned __int64		uiVSell;				// ��ί����[��λ����] 
	char				szUpCode[7];		// ���ǹɴ��룫���ǹ��г����
	
} tagCcComm_OtherIndexData;
//add by liuqy 20110826 for ��Ʒ�ڻ���չ���
//[2, 104] ������Ʒ�ڻ���չ���ƴ������Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexRelation | ��..
typedef struct
{
unsigned  char 	ExchKind;			//shfe 0  dce 1  zse 2
char 			ContractCode[2];		//��Լ���� RB
char 			ContractMap [2][6];	//Map��Լ���� 8070**
char 			OddEvenFlag ;		// Map��Լ�����Ƿ�������ż 0 ������ 1���� ��ż
char 			IndexCode[4];			//ָ������ RBZS
char 			IndexMap[6];			//Mapָ������ 807099

char 			Reserved[6];			//�����ֽ�
} tagCcComm_CffexRelation ; 
//end add

//add by liuqy 20100823 for �ܱ��г����ʹ�����½ṹ
//[2��2]�����ܱ��г������ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_OtherNameTable | tagCcComm_OtherNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��

typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ���[��ӦMarketInfo�е����]
	char							Code[6];				//��Ʒ����
	char							Name[8];				//��Ʒ����
	unsigned char				uchFlags;					//�ر��־��0x01:�ȵ�ָ��(�ñ�־��Դ�������İ�������ļ�) 
} tagCcComm_OtherNameTable;
//add by liuqy 20101102 for Ϊ�¼����������ݽṹ
//[2,60]�����¼����г����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_SgxNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��
typedef struct
{
	unsigned short		Serial;	//��Ʒ���
	unsigned char			Type;	//����Ʒ���[��ӦMarketInfo�е����][E, W, B]
	char					Code[6];			//��Ʒ����  SIN
	char 				Name[8];			//���
	char                   FullName[32];      //ȫ�� add by liuqy 20101129
	unsigned char			Currency;			//�ο��۹ɵ�Currency
	unsigned long			LotSize;			//�ֱ���(ÿ��ADR���ܻ᲻ͬ)
	char 				PriceRate;		//�Ŵ���(ÿ��ADR���ܻ᲻ͬ)
} tagCcComm_SgxNameTable;

//[2,61]�����¼����г�����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_SgxStockData ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char						Code[6];				//��Ʒ����
	unsigned long				High;				//��߼۸�[* �Ŵ���]
	unsigned long				Open;				//���̼۸�[* �Ŵ���]
	unsigned long				Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long				Close;				//���ռ۸�[* �Ŵ���]
	unsigned long				Now;					//���¼۸�[* �Ŵ���]
	unsigned __int64			NowVolume;			//����
	double					Amount;				//�ܳɽ����[Ԫ] 
	unsigned __int64			Volume;				//�ܳɽ���[��]
	tagCcComm_BuySell			Buy;					//����
	tagCcComm_BuySell			Sell;				//����
} tagCcComm_SgxStockData;
//end add 


//[2,12]������չ���ǰ׺Э���
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagMemPreNameExt| tagMemPreNameExt| ...
typedef struct  
{
	char Code[6]; //��Ʒ����
	char Prename[6]; //��Ʒǰ׺,0��4����ǰ��һ������5���ֽ��� XXZQJB ֤ȯ����,��6���ֽڱ���
	unsigned short ushZSSSL; //����������XXZSSSL
	char Reserve[2]; //����
}tagMemPreNameExt;

//[2,50]������չ���ǰ׺Э���
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo |�仯����|�仯����| ��
//�仯���� = �������� + tagMemPreNameExt
//���� 6 =������չ���ǰ׺�ṹ(tagMemPreNameExt)


//[2,62]����߶���Ѷ��������
//����MAIN_FRAME_HEAD | tagTransComm_AdvInfoApplyType | <tagTransComm_AdvInfoIDApply/tagTransComm_AdvInfoApply>
//Ӧ��(tagTransComm_AdvInfoIDApply)��MAIN_FRAME_HEAD | ULONG(��ѶID) | ULONG |...
//Ӧ��(tagTransComm_AdvInfoApply)��MAIN_FRAME_HEAD | ��Ѷͷ&���� | ��Ѷͷ&���� |...

typedef struct
{
	unsigned char marketid;			//�г�ID
	unsigned char applytype;		//0������ID����
									//1��������������
									//2������ָ��ID����Ѷ
									//3������ָ�������ļ�����
									//4��������ѶID��
									//5������ָ��ID�Ժ����Ѷ����������
} tagTransComm_AdvInfoApplyType;

#define			ADVINFO_APPLYTYPE_IDBEGIN		(0)		//���ڵ���ĳ��ID����Ѷ
#define			ADVINFO_APPLYTYPE_DAYCOUNT		(1)		//ָ�����������Ѷ
#define			ADVINFO_APPLYTYPE_APPOINTID		(2)		//ָ��ĳ��ID����Ѷ
#define			ADVINFO_APPLYTYPE_DATEFILE		(3)		//����ָ�������ļ�����
#define			ADVINFO_APPLYTYPE_IDLIST		(4)		//������ѶID��
#define			ADVINFO_APPLYTYPE_IDNEXT		(5)		//����ָ��ID�Ժ����Ѷ����������

typedef struct
{
	unsigned long	LastID;			//���ĸ�ID��ʼ����������
	unsigned long	ApplyCount;		//����ID����
} tagTransComm_AdvInfoIDApply;

typedef struct
{
	union
	{
		struct
		{//0������ID����
			unsigned long	BeginID;		//��ʼID��0Ϊ��ͷȡ��-1Ϊ�Ӻ���ǰ����
			unsigned long	ApplyInfoCount;	//��������
		};
		struct
		{//1��������������
			unsigned long	BeginDate;		//��ʼ���ڣ�0Ϊ��ͷȡ��-1Ϊ�Ӻ���ǰ����
			unsigned long	ApplyDayCount;	//��������
		};
		struct
		{//2������ָ��ID����Ѷ
			unsigned long	InfoID;			//��ѶID
			char			Reserved2[4];	//����
		};
		struct
		{//3������ָ�������ļ�����
			unsigned long	FileDate;		//�����ļ�����
			unsigned long	FileOffset;		//�ļ�ƫ��
		};
		struct
		{//5������ID��������ָ��ID�Ժ����Ѷ������������
			unsigned long	LastID;				//��ʼID��0Ϊ��ͷȡ��-1Ϊ�Ӻ���ǰ����
			unsigned long	ApplyInfoCount5;	//��������
		};
	};
} tagTransComm_AdvInfoApply;


//[2,63]����߶���Ѷ�����ļ�
//����MAIN_FRAME_HEAD | tagTransComm_Info6ConfigApply
//Ӧ��MAIN_FRAME_HEAD | tagTransComm_Info6ConfigApply | �����ļ�����(�ı�����)
typedef struct
{
	unsigned char			MarketId;			//�г�ID
	unsigned char			ApplyType;
	unsigned long			UpdateDate;
	unsigned long			UpdateTime;
	char					FileName[64];
} tagTransComm_Info6ConfigApply;

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//..........................................................................................................................
//����Ϊ������̬��ӿ�
//..........................................................................................................................
typedef struct														//����������Ϣ
{
	unsigned char				drvMarketId;						//�����ṩ������г���ţ��ܲ������������˴�������ѯ��
	unsigned short				drvUnitType;						//�����ĵ�Ԫ���ͣ��ܲ������������˴�������ѯ��
	char						drvName[40];						//�������ƣ��ܲ������������˴�������ѯ��
	char						drvDescription[128];				//��������
	MControlBaseClass		*	drvControlClassPtr;					//���������ຯ��ָ��[����������μ�����������ӿ�MServiceInterActive.hpp]
	char						Reserved[81];						//����
} tagDll_DriverBaseInfo;
//..........................................................................................................................
typedef void (__cdecl tagOnPushDataFun)(		
											unsigned char 		MainType,		//�������ݵ����汾�ţ��μ���������Э�飩
											unsigned char 		ChildType,		//�������ݵ��Ӱ汾�ţ��μ���������Э�飩
											const char		* 	InBuf,			//�����������ݻ���
											unsigned short 		InSize,			//Ҫ�������ݵĳ���
											unsigned char 		Marketid,		//�������ݵ��г�ID
											unsigned short		UnitNo,			//���������ĵ�Ԫ���룬ת������������õ�
											bool 				SendDirectFlag	//���ߴ���ƽ̨�Ը����Ͱ�����Ҫ����ѹ���ȴ���ֱ�ӷ��;Ϳ�����
										);
//..........................................................................................................................
typedef void (__cdecl tagWriteLogFun) (		
											unsigned char 		Type,			//��־����[0=��ˮ��־��1=��Ϣ��־��2=������־��3=������־]
											unsigned short		SrvUnit, 		//�������������ĵ�Ԫ��ţ�����ƽ̨��ͨ����������֪ͨ������
											unsigned short		LogLevel,		//��־�ȼ�[����Խ���ʾԽ��ϸ��0��Ϊ��ͨ��Ӫ����]
											const char 		* 	Source,			//����־�����������ڲ�ģ������
											const char		* 	Format, ...		//��־����
										);		
//..........................................................................................................................
typedef void (__cdecl tagPrintFun) (
											unsigned long		CmdSerail,		//���������ţ��ɴ���ƽ̨����ʱ��Ϊ�������롣
											const char 		* 	Format, ... 	//���ص���ʾ��Ϣ����
									);

typedef void (__cdecl tagCloseFun)(
										   unsigned char		Marketid,		//��Ҫ�رյ��г�ID
										   unsigned short		UnitCode		//�����ĵ�Ԫ���
									);

typedef int  (__cdecl tagPrepareDataFrame)(unsigned char cMainType,				//������
										   unsigned char cChildType,			//������
										   const char * lpInBuf,				//ԭʼ���ݣ���Ҫѹ���ʹ�������ݣ�
										   unsigned short sInSize,				//ԭʼ���ݴ�С
										   char * lpOutBuf,						//�Ѿ�����õ����ݣ�����ѹ�������ݻ����ѹ�������ݣ�
										   unsigned short sOutSize);			//lpOutBuf�ռ��С

typedef int  (__cdecl tagRestoreDataFrame)(	const char * lpInBuf,				//��Ҫ��ԭ��ѹ�����ݣ�����ѹ�������ݻ����ѹ�������ݣ�
											unsigned short sInSize,				//��Ҫ��ԭ��ѹ�����ݳ���
											char * * lpOutPtr,					//�Ѿ���ԭ�����ݵ�ַ
											char * lpTempBuf,					//��ʱ����ռ�
											unsigned short sTempSize );			//��ʱ����ռ��С
//add by liuqy 20100901 for ���ӶԵ�Ԫ��־�����飬�������ʹ�÷���true,�����÷���false
typedef bool tagSmFun_ChkWriteLogLevel(unsigned short wSrvUnit, unsigned short wLogLevel);
//end add

//add by liuqy for 20150323 for д���ط�����־��Ϣ��������
//wSrvUnitΪ��Ԫ��;
//in_ulSysErrNo ϵͳ�����
//in_ulErrCode Ӧ�ô����
//pszFileName	��ӡ��־���ļ���
//nFileLine		��ӡ��־���ļ��к�
//in_uchSndFlag ���ط��ͱ�־ 0�����ͣ�1����
//lLogLevelΪ�ȼ�: 0Ϊ��ͨ��־��1Ϊά����־��2Ϊ�����ɼ���־��255Ϊ������Ӫ��־��
//cLogType VIEW	0	INFO	1	WARN	2	ERR		3	ALARM	4
typedef void tagSmFun_WriteMonLog(unsigned short wSrvUnit, unsigned long in_ulSysErrNo, unsigned long in_ulErrCode, 
					 const char * pszFileName, int nFileLine, unsigned char in_uchSndFlag, 
					 unsigned long lLogLevel, unsigned char cLogType, const char * pszFormat, va_list valist);
typedef void (tagNewWriteLogFun) (		
									   unsigned char 		Type,			//��־����[0=��ˮ��־��1=��Ϣ��־��2=������־��3=������־]
									   unsigned short		SrvUnit, 		//�������������ĵ�Ԫ��ţ�����ƽ̨��ͨ����������֪ͨ������
									   unsigned short		LogLevel,		//��־�ȼ�[����Խ���ʾԽ��ϸ��0��Ϊ��ͨ��Ӫ����]
									   const char 		* 	Source,			//����־�����������ڲ�ģ������
									   const char		* 	Format, va_list valist		//��־����
									   );		

//end add by liuqy
//..........................................................................................................................
typedef struct
{
	unsigned short				PlatUnitType;						//����ƽ̨���ͣ�����ƽ̨����ת������ܲ������������˴�������ѯ��
	unsigned long				PlatVersion;						//����ƽ̨�汾��
	unsigned long				DriverUnitCode;						//����ƽ̨ע�������󣬷������������ĵ�Ԫ��ţ�ע�⣺��־�ȵط���Ҫʹ�ã�
	unsigned long 				SendBufSize;						//���ͻ��峤�ȣ�����ƽ̨һ��Ϊ���ͻ����1/20��ת���Ϊ100 * FrameSize
	unsigned short 				FrameSize;							//����ʱÿ�����ݰ�����󳤶ȣ�һ��Ϊ8192
	tagOnPushDataFun		*	PushDataFunPtr;						//���¼��������ݣ�����ա���ʵȵȣ����ͱ仯��������ͣ�
	tagWriteLogFun			*	WriteLogFunPtr;						//��ӡ��־��ע�⣺������ӡ��־����ͨ���ýӿڣ����͵�����ƽ̨��
	tagPrintFun				*  	CmdPrintFunPtr;						//��ӡ�����������ʾ�������з�ʽ��
	tagPrintFun				*  	CmdPrintlnFunPtr;					//��ӡ�����������ʾ�����з�ʽ��
	tagCloseFun				*	CloseFunptr;						//֪ͨ����ƽ̨�ر��������������
	tagPrepareDataFrame		*	PrepareDataFrame;					//��ԭʼ���ݽ���ѹ���ȴ���
	tagRestoreDataFrame		*	RestoreDataFrame;					//�Դ�������ݽ��л�ԭ
	//add by liuqy 20100901 for ����һ�����ӶԵ�Ԫ��־�����麯���ӿ�,ͬʱ����һ���汾�ź�ʶ����������һ������Ƿ�֧��ĳЩ����
	unsigned long				ulSvcPlatFlag;					//ƽ̨ʶ���룬����ֵΪ"SVCP"��ASCII��ʱ����ʾ�к���Ľӿ�
	unsigned long				ulPlatVer;						//ƽ̨��ǰ�İ汾�ţ�����һ�����ĳЩ�����Ƿ�֧��
	//���ӶԵ�Ԫ��־�����飬�������ʹ�÷���true,�����÷���false
	tagSmFun_ChkWriteLogLevel	* ChkWriteLogLevel;					//�Ե�Ԫ��־������ 
	//add by liuqy for 20150323 for д���ط�����־��Ϣ��������
	tagSmFun_WriteMonLog	*	WriteMonLogFunPtr;				//����־�����ӿ�
	tagNewWriteLogFun		*	NewWriteLogFunPtr;
	char						Reserved[64];						//����
	//end add
} tagDll_DataCenterInput;
//..........................................................................................................................
typedef struct
{
	char						Reserved[128];						//����
} tagDll_DriverOutput;
//..........................................................................................................................
typedef struct
{
	unsigned short 				nCount;								//��ʾ����ƽ̨���ε���GetMarketInfo����ṩpInfo��������In��
																	//���������ʵ��pInfoʵ���������ڸ���ֵ��Ӧ�÷���ʧ�ܡ�
																	//��ֵ��ʾtagDll_GetMarketInfoOut�ṹ�������ٵ�pInfo�ṹ����
	char						Reserved[126];						//����
} tagDll_GetMarketInfoIn;
//..........................................................................................................................
typedef struct
{
	tagCcComm_MarketInfoHead 	*	pHead;							//�г���Ϣͷ��
	tagCcComm_MarketInfoDetail 	* 	pInfo;							//�г������Ϣ
	char							Reserved[120];					//����
} tagDll_GetMarketInfoOut;
//..........................................................................................................................
typedef struct
{
	unsigned char 				MainType;							//����������
	unsigned char 				ChildType; 							//����������
	const char 				* 	ApplyBuf;							//��������
	unsigned short 				ApplySize;							//���󳤶�
	char						Reserved[120];						//����
} tagDll_GetDataFrameCountIn;
//..........................................................................................................................
typedef struct
{
	char						RequestCompleteFlag;				//���������Ƿ���ɣ����BeginWorkʱSendBufSize��������������Ϣ����ֻ����ɲ��֣�
	char						Reserved[127];						//����
} tagDll_GetFrameCountOut;
//..........................................................................................................................
typedef struct
{
	unsigned char 				MainType;							//����������
	unsigned char 				ChildType; 							//����������
	const char 				* 	ApplyBuf;							//��������
	unsigned short 				ApplySize;							//���󳤶�
	unsigned short				FrameNo;							//����ڼ������ݰ�������
	unsigned short				DataOutBufSize;						//���ڲ���DataOutBuf�ĳ��ȣ����ʵ�ʷ������ݳ��ȴ��ڸ�ֵ����������ʧ��
	char						Reserved[116];						//����
} tagDll_GetOneDataFrameIn;
//..........................................................................................................................
typedef struct
{
	char					*	DataOutBuf;							//�������ݰ���������
	char						Reserved[124];						//����
} tagDll_GetOneDataFrameOut;
//..........................................................................................................................
typedef struct
{
	unsigned long				version;							//�����汾
	unsigned char 				marketid;							//�г����
	unsigned char			    marketstatus;						//�г�״̬
	unsigned long				freshtime; 							//�г�ˢ��ʱ��(��)
	unsigned long 				marketdate;							//�г�����
	unsigned long 				markettime;							//�г�ʱ��
	unsigned short				wareCount;							//���г���Ʒ����
	unsigned short 				packspeed;							//ÿ���Ӵ���İ��ĸ���
	unsigned long  				price;								//����Ʒ�ļ۸�
	__int64						amount;								//����Ʒ�ĳɽ����
	unsigned __int64			volumn;								//����Ʒ�ĳɽ���
	unsigned long				freshinterval;						//����Ʒ��ˢ��ʱ�������룩
	unsigned long				worktime;							//�������ӻỰ��ʱ��(��)����򿪵�ʱ�� 
	char						serverStatus;						//��������״̬
	char						HQSourceAddr[80];					//����Դ��ַ������������ΪDBF�ļ�·�����������������˿ڡ�IP��ַ���˿ڵȵ�
	char						additionInfo[32];					//������������Ϣ
} tagDll_DriverStatusInfo;
//add by liuqy 20101027 for �µļ��Ҫ�أ������Ҫ�޸����½ṹ
typedef struct
{
	union
	{
		struct
		{
			unsigned long m_u24Magic: 24;
			unsigned long m_u8Version:8;
		};
		
		unsigned long				ulHead;				// ���ͷ
	};
	unsigned long				ulVersion;							//�����汾
	unsigned char 				uchMarketid;							//�г����
	unsigned char			    uchMarketstatus;						//�г�״̬
	unsigned long				ulMarketFreshtime; 							//�г�ˢ��ʱ����(����)
	unsigned long 				ulMarkettime;							//�г�ʱ��
	unsigned long 				ulMarketdate;							//�г�����
	unsigned short				ushWareCount;							//���г���Ʒ����
	unsigned short 				ushPackspeed;							//ÿ���Ӵ���İ��ĸ���
	unsigned long  				ulPrice;								//����Ʒ�ļ۸�
	__int64						llAmount;								//����Ʒ�ĳɽ����
	unsigned __int64			ullVolumn;								//����Ʒ�ĳɽ���
	unsigned long				ulFreshinterval;						//����Ʒ��ˢ��ʱ���������룩
	unsigned long				ulStartupTime;							//����ʱ��
	unsigned long				ulStartupDate;							//��������
	unsigned long				ulInitializeTime;						//��ʼ��ʱ��
	unsigned char				uchServerStatus;						//��������״̬
	unsigned short				ushTotalCommBreakInterval;				//���������ʱ��(�� ���Ϊ65535)
	unsigned short				ushCurCommBreakInterval;				//��ǰ����ʱ��(�� ���Ϊ65535)
	unsigned char				uchConnectFlag;						//����һ������״̬
	unsigned short				ushCommSwitchCount;					//ͨ���л�ͳ��
	unsigned long				ulConnectedInterval;				//�������ӳɹ�ʱ��(��)
	unsigned short				ushConnectPort;						//���Ӷ˿�
	char						szConnectAddr[16];					//���ӵ�ַ
} tagDll_NewDriverStatusInfo;

//..........................................................................................................................
typedef struct
{
	unsigned char				MarketId;
	unsigned char				UnitType;
	unsigned short				UnitNo;
	unsigned long				Date;
	unsigned long				Time;
	unsigned long				DelayTime;
	char						IndexFileName[128];	
	char						DataFileName[128];
	char						Reserved[116];
} tagDelay_PreUnitInfo;
//..........................................................................................................................
typedef struct
{
	unsigned char	mainype;	//����������
	unsigned char	childType;	//����������
	unsigned short	size;		//�����ļ��еĴ�С
	unsigned int	offset;		//�����ļ��е���ʼλ��
	long			time;		//д�ļ�ʱ��
} tagIndexFileRecord;
//..........................................................................................................................
typedef struct
{
	unsigned char				Status0;
	unsigned char				Status1;
	char						Reserved[126];
} tagDelay_ThreadStatus;

//..........................................................................................................................
typedef unsigned long	__stdcall tagGetDllVersion(void);
typedef void			__stdcall tagGetDriverBaseInfo(tagDll_DriverBaseInfo * outdrvinfo);
typedef int				__stdcall tagBeginDriverWork(tagDll_DataCenterInput * In,tagDll_DriverOutput * Out);
typedef void			__stdcall tagEndDriverWork(void);
typedef int				__stdcall tagGetMarketInfo(tagDll_GetMarketInfoIn * In, tagDll_GetMarketInfoOut * Out);
typedef int				__stdcall tagGetDataFrameCount(tagDll_GetDataFrameCountIn * In,tagDll_GetFrameCountOut * Out);
typedef int				__stdcall tagGetOneDataFrame(tagDll_GetOneDataFrameIn * In,tagDll_GetOneDataFrameOut * Out);
typedef bool			__stdcall tagIsDriverWorking(void);
typedef void			__stdcall tagGetDriverStatusInfo(tagDll_DriverStatusInfo * Out);
//add by liuqy 20160511
typedef void			__stdcall tagSuspendDrvWork(void);
typedef void			__stdcall tagActivateDrvWork(void);
typedef bool			__stdcall tagGetActivateDrvWorkState(void);
//end add by liuqy 20160511 

//add by liuqy 20101027 Ϊ�����Ҫ��ȡ�µļ����Ϣ
/*********************
 * ��������GetNewDriverStatusInfo
 * ���ܣ�	ȡ�µ�������Ϣ
 * ������	out_pszDrvStatusInfoBuf	���-״̬��Ϣ
 *			in_ulDrvStatusInfoBufSize	����-״̬��Ϣ�ռ��С
 * ���أ� ����0�������ݴ�С��С��0��ʾʧ��
 **********************/
typedef int				__stdcall tagGetNewDriverStatusInfo(char * out_pszDrvStatusInfoBuf, unsigned long in_ulDrvStatusInfoBufSize);

//add by liuqy 20110808 for ���ӹ��ǽӿ���Ҫ�Ľṹ
//��������������Ϣ
typedef struct
{
	unsigned long					lLinkNo;					//���ӱ��
	unsigned long					lIPAddr;					//IP��ַ

	char							szUserName[32];				//�˺�����
	char							szMacAddr[12];				//MAC��ַ
	unsigned long					lClientVersion;				//���鴫��ͻ��˰汾��
	unsigned char					cMarketID;					//�г����
	unsigned short					uClientType;				//�ͻ�������
	
} tagTran2nd_LinkInfo;
//add by liuqy 20110808 for ���ӹ��ǽӿڴ���ӿڣ������Ƿ��ͱ�־

typedef bool			__stdcall tagSndDataSpecialFilter(tagTran2nd_LinkInfo * in_pstLinkInfo, unsigned char MainType,unsigned char ChildType,
														  const char * InBuf,unsigned short InSize);


//[2��2]���󿪷�ʽ�����г����ƴ����

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_KFSJJNameTable | tagCcComm_KFSJJNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��

typedef struct
{
	unsigned short					Serial;					//��Ʒ���
	unsigned char					Type;					//����Ʒ���[��ӦMarketInfo�е����]
	char							Code[6];				//��Ʒ����
	char							Name[16];				//��Ʒ����
	unsigned long					lZs;					//�ܷ���
} tagCcComm_KFSJJNameTable;

//[2,8]���󿪷�ʽ�����г�����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_KFSJJStockData ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char						Code[6];			//��Ʒ����
	unsigned long				High;				//��߼۸�[* �Ŵ���]
	unsigned long				Open;				//���̼۸�[* �Ŵ���]
	unsigned long				Low;				//��ͼ۸�[* �Ŵ���]
	unsigned long				Close;				//���ռ۸�[* �Ŵ���]
	unsigned long				Now;				//���¼۸�[* �Ŵ���]
	double						Amount;				//�ܳɽ���� 
	unsigned __int64			Volume;				//�ܳɽ���

} tagCcComm_KFSJJStockData;

//..........................................................................................................................
//--------------------------------------------------------------------------------------------------------------------------
//*********************************************�Ϻ���Ȩ��ͨѶ�ӿ�***********************************************************
//--------------------------------------------------------------------------------------------------------------------------
//..........................................................................................................................


//[2��80] ���ƴ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ ShOptNameTable | tagCcComm_ ShOptNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��

typedef struct 
{
	unsigned long					Serial;				//���(1 Ϊָ���� 2Ϊ ��Ȩ��Լ)
	unsigned char					Type;				//���

	char							Code[8];			//��ƷID
	char							ContractID[19];		//��Լ����
	char							SecuritySymbol[20];	//��Լ���
	char							OptionType;			//ŷʽ��ʽ(E-ŷʽ  A-��ʽ)
	char							CallOrPut;			//�Ϲ��Ϲ�(C-   P-)

	unsigned long					PreClosePx;			//��Լ����(������Ȩ��Ϣ��Ϊ����������̼۸�)//[*�Ŵ���]
	unsigned long					PreSettlePx;			//��Լ���//[*�Ŵ���]
	int								LeavesQty;			//δƽ�ֺ�Լ�� = ��ֲ� ��λ����

	char							UnderlyingSecurityID[6];	//���֤ȯ����
	char							UnderlyingName[8];	//���֤ȯ����
	char							UnderlyingType[3];		//���֤ȯ����(EBS -ETF, ASH -A��)
	unsigned long 					UnderlyingClosePx;	//���֤ȯ������ //[*�Ŵ���]

	char							PriceLimitType;		//�ǵ�����������(N ���ǵ���)(R ���ǵ���)
	unsigned long					UpLimit;				//������Ȩ��ͣ�۸�(��ȷ����) //[*�Ŵ���]
	unsigned long					DownLimit;			//������Ȩ��ͣ�۸�(��ȷ����) //[*�Ŵ���]
	int								LotSize;				//һ�ֵ��ڼ��ź�Լ
	int								ContractUnit;			//��Լ��λ(������Ȩ��Ϣ������ĺ�Լ��λ��һ��Ϊ����)
	
	unsigned long					XqPrice;			//��Ȩ�۸�(��ȷ����) //[*�Ŵ���] 
	int								StartDate;			//�׸�������(YYYYMMDD)
	int								EndDate;			//�������(YYYYMMDD)
	int								XqDate;				//��Ȩ��(YYYYMMDD)
	int								DeliveryDate;		//������(YYYYMMDD)
	int								ExpireDate;			//������(YYYYMMDD)
	

	char							UpdateVersion;		//��Ȩ��Լ�İ汾��


	int								MarginUnit;			//��λ��֤��
	short							MarginRatio;		//��֤�����(%)
	short							MarginRatio2;		//��֤�����(%)

	int								MinMktFloor;		//�����м��걨����
	int								MaxMktFloor;		//�����м��걨����
	int								MinLmtFloor;		//�����޼��걨����
	int								MaxLmtFloor;		//�����޼��걨����
	
	char							StatusFlag[8];		//��Ȩ��Լ״̬(8���ַ�,��ϸ������ĵ�)

}tagCcComm_ShOptNameTable;

//[2��81] �����Ϻ���Ȩ�г����������Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ ShOptNameTableEx | tagCcComm_ ShOptNameTableEx | ...
//ע�⣺���������֧�ֶַ�����
typedef struct 
{
	char							Code[8];		//��ƷID
	
	unsigned long					XqPrice;			//��Ȩ�۸�(��ȷ����) //[*�Ŵ���]
	int								StartDate;		//�׸�������(YYYYMMDD)
	int								EndDate;			//�������(YYYYMMDD)
	int								XqDate;			//��Ȩ��(YYYYMMDD)
	int								ExpireDate;		//������(YYYYMMDD)

	char							UpdateVersion;	//��Ȩ��Լ�İ汾��
	int								MemberLimit;		//��λ��Ա�ֲ�����(��)

	int								MarginUnit;		//��λ��֤��
	short							MarginRatio;		//��֤�����(%)

	int								MinMktFloor;		//�����м��걨����
	int								MaxMktFloor;		//�����м��걨����
	int								MinLmtFloor;		//�����޼��걨����
	int								MaxLmtFloor;		//�����޼��걨����

	char							StatusFlag[8];		//��Ȩ��Լ״̬
}tagCcComm_ShOptNameTableEx;
//[2��82] �����Ϻ���Ȩ�г���������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ ShOptionData | tagCcComm_ ShOptionData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned char					MarketID;				//�г����
	unsigned long					MarketDate;				//�г�����[YYYYMMDD��ʽ]
	unsigned long					MarketTime;				//�г�ʱ��[HHMMSS��ʽ]
	int								RecordNum;				//��Լ�ܸ���
	char							TradingPhaseSecurityID[8];		//�г�״̬
} tagCcComm_ShOptMarketStatus;

typedef struct 
{
	int								DataTimeStamp;			//ʱ���
	char							Code[8];				//��Ʒ���� (!= ��Լ����)
//	unsigned long					PreClosePx;				//���� [*�Ŵ���]����ȷ3λ��	//������п���ȡ��

	unsigned long					PreSettlePrice;				//��� [*�Ŵ���]����ȷ3λ��	//������п���ȡ��
	unsigned long					SettlePrice;				//��� [*�Ŵ���]����ȷ3λ��
	unsigned long					OpenPx;					//���̼� [*�Ŵ���]����ȷ3λ��
	unsigned long					HighPx;					//��� [*�Ŵ���]����ȷ3λ��
	unsigned long					LowPx;					//��� [*�Ŵ���]����ȷ3λ��
	unsigned long					Now;					//���� [*�Ŵ���]����ȷ3λ��

	__int64							Volume;				//�ɽ���
	__int64							Amount;				//�ɽ���� [�Ŵ�100��] 2λС��
	char							TradingPhaseSecurityID[4];	//����״̬

	unsigned long					AuctionPrice;			//�������жϲο��� [*�Ŵ���]����ȷ3λ��
 	__int64							AuctionQty;			//�������жϼ��Ͼ�������ƥ����
 	__int64							Position;			//�ֲ���
	tagCcComm_BuySell				Buy[5];					//ί����
	tagCcComm_BuySell				Sell[5];					//ί����
}tagCcComm_ShOptionData;

 //..........................................................................................................................
//--------------------------------------------------------------------------------------------------------------------------
//*************************************************����ͨѶ�ӿ�***************************************************************
//--------------------------------------------------------------------------------------------------------------------------
//..........................................................................................................................

//[2, 76]�����������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_BatsNameTable | tagCcComm_BatsNameTable | ...
typedef struct 
{
	unsigned short					Serial;
	unsigned char					Type;
	char							Code[8];
	char							szName[16];
	unsigned long					PreClose;	//����[*�Ŵ���]
}tagCcComm_BatsNameTable;

//[2, 78]�������ɿ���
//ע�⣺���������֧�ֶַ�����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_BatsData | tagCcComm_BatsData | ...


//[2, 79]���������г�����
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//����0�� �г���Ϣ	= tagCcComm_MarketStatusInfo
//����1�� ���ձ��  = tagCcComm_BatsPreCloseChg
//����2�� ������Լ�������� = tagCcComm_BatsData
//����3�� ��������У������ = tagCcComm_AdjustClosed

typedef struct _TCOM_ADJUSTCLOSED
{
	char    chAdjustClosed;    //��������У����־��1��ʾ��ʼ��0��ʾ����
}tagCcComm_AdjustClosed;

typedef struct 
{
	char							Code[8];
	unsigned long					PreClose;		//����[*�Ŵ���]
}tagCcComm_BatsPreCloseChg;
typedef struct 
{
	char							Code[8];
	unsigned long					Open;			//���̼�[*�Ŵ���]
	unsigned long					High;			//��߼�[*�Ŵ���]
	unsigned long					Low;			//��ͼ�[*�Ŵ���]
	unsigned long					Now;			//���¼�[*�Ŵ���]
	__int64							Volume;			//�ɽ���
	unsigned long					AvgPrice;		//��Ȩƽ���� [*�Ŵ���]
	unsigned char					TradingFlag;	//����״̬(0=������ 1=ͣ��)
	tagCcComm_BuySell				Buy;
	tagCcComm_BuySell				Sell;
}tagCcComm_BatsData;

//[2, 254]��������Ľڼ��ձ�
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_LastHolidayResponse | tagCcComm_LastHolidayTable | tagCcComm_LastHolidayTable | ...
typedef struct 
{
	unsigned short					ushDateCount; //�����������ڵĸ���
} tagCcComm_LastHolidayResponse;

typedef struct 
{
	unsigned char					uchIsHoliday; //�����ǽڼ��ձ�־��0��ʾ�ǣ�1��ʾ��
	unsigned int					ulDate; //���ڣ�������ı�־���Ƹ������Ƿ�Ϊ�ڼ���
}tagCcComm_LastHolidayTable;

////////////////////////////����ͨbegin/////////////////////////////////////////////
//[2��84] ���ƴ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHNameTable | tagCcComm_HKSHNameTable | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
    unsigned short                  Serial;						//��Ʒ��� 
    unsigned char                   Type;						//����Ʒ���� 
    char                            Code[6];					//��Ʒ���� 
    char                            EnglishName[16];			//Ӣ������ 
    char                            ChineseName[16];			//�������� 
    char                            SName[8];					//���ļ�� 
    unsigned long                   ListDate;					//�������� 
    unsigned long                   OffDate;					//�������� 
    unsigned long                   SpreadValue;				//���[* �Ŵ���] 
    unsigned long                   LotSize;					//����Ʒ��"��"���� 
    unsigned char                   Currency;					//�������� 
    unsigned char                   PriceTb;					//ʹ�����ż�λ�� 
    float                           NrRate;						//�޷������� 
    char                            SecurityStatusFlag[8];		//��1λ����0����ʾ�����򣬡�1����ʾ���� 
	//��2λ����0����ʾ����������1����ʾ������ 
} tagCcComm_HkSHNameTable; 

//[2��85] ���ɿ�������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHStockData | tagCcComm_HKSHStockData | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
    char							 Code[6];					//��Ʒ����<2009-1-21 Lumy����> 
    unsigned long                    High;						//��߼۸�[* �Ŵ���] 
    unsigned long                    Open;						//���̼۸�[* �Ŵ���] 
    unsigned long                    Low;						//��ͼ۸�[* �Ŵ���] 
    unsigned long                    Close;						//���ռ۸�[* �Ŵ���] 
    unsigned long                    Now;						//���¼۸�[* �Ŵ���] 
    double							 Amount;                    //�ܳɽ����[Ԫ] 
    unsigned __int64                 Volume;                    //�ܳɽ���[��] 
    unsigned long                    VBuyPrice;					//ί��۸�[* �Ŵ���] 
    tagCcComm_HKBuySell              VBuy;						//1������ 
    unsigned long                    VSellPrice;                //ί���۸�[* �Ŵ���] 
    tagCcComm_HKBuySell              VSell;						//1������ 
    unsigned long                    Voip;						//Ȩ֤��� 
} tagCcComm_HKSHStockData; 
//add by liuqy 20150414 for ����ͨ5������
//[2��93]���󻦸�֤ͨȯ�г���ȫ�г����ɿ�������

//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHStockDataLv5 | tagCcComm_HKSHStockDataLv5 | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char							Code[6];				//��Ʒ����
	unsigned long					High;					//��߼۸�[* �Ŵ���]
	unsigned long					Open;					//���̼۸�[* �Ŵ���]
	unsigned long					Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long					Close;					//���ռ۸�[* �Ŵ���]
	unsigned long					Now;					//���¼۸�[* �Ŵ���]
	double							Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64				Volume;					//�ܳɽ���[��]
	unsigned long					VBuyPrice;				//ί��۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VBuy[5];				//1������
	unsigned long					VSellPrice;				//ί���۸�[* �Ŵ���]
	tagCcComm_HKBuySell				VSell[5];				//1������
	unsigned long					Voip;					//Ȩ֤���
} tagCcComm_HKSHStockDataLv5;


//[2��94]���͸۹���������
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char
//����0: �г���Ϣ = tagCcComm_MarketStatusInfo
//����1��������Ʒȫ���������� =  tagCcComm_HKSHStockDataLv5
//����2���ο����� = tagCcComm_HKSHCurrency
//����3��������� = tagCcComm_HKSHAmount
//����4������ָ������ =  tagCcComm_HKSHIndexData
//����5: ��Ʒ״̬������� = tagCcComm_HKSHStatusChg



//[2��87] �ο�����
// �� ��MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
// Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHCurrency | tagCcComm_HKSHCurrency | ...
// ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned long BuyCurrencyRatio; //�ο���������ۣ�CNYHKD��[* �Ŵ� ��] * 100000
	unsigned long SellCurrencyRatio; //�ο����������ۣ�CNYHKD��[* �Ŵ� ��] * 100000
	unsigned long CurrencyRatio;    //�ο������м�ۣ�CNYHKD��[* �Ŵ� ��] * 100000 
} tagCcComm_HKSHCurrency;

//[2��88]���󻦸�֤ͨȯ�г��������������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHAmount | tagCcComm_HKSHAmount | ...
//ע�⣺���������֧�ֶַ�����
typedef struct 
{ 
    unsigned __int64                ThresholdAmount;        //ÿ�ճ�ʼ��ȣ���λ�����Ԫ 
    unsigned __int64                PosAmt;                    //����ʣ���ȣ���λ�����Ԫ 
    unsigned char                   TradSesStatus;            //���״̬ 1��������� 2����ȿ��á� 
    unsigned char                   MktStatus[8];            
	//��1λ����0����ʾȫ�г��������룬��1����ʾ�����޴����ơ� 
	//��2λ����0����ʾȫ�г�������������1����ʾ�����޴����ơ� 
	//��3λ����0����ʾ���շǸ۹�ͨ�����գ���1����ʾ���ո۹�ͨ�����ա� 
} tagCcComm_HKSHAmount; 

//[2��89] ָ����������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHIndexData | tagCcComm_HKSHIndexData | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
    char                            Code[6];                //��Ʒ����<2009-1-21 Lumy����> 
    unsigned long                   High;                    //���ָ��[* �Ŵ���] 
    unsigned long                   Open;                    //����ָ��[* �Ŵ���] 
    unsigned long                   Low;                    //���ָ��[* �Ŵ���] 
    unsigned long                   Close;                    //����ָ��[* �Ŵ���] 
    unsigned long                   Now;                    //����ָ��[* �Ŵ���] 
    double                          Amount;                    //�ܳɽ����[Ԫ] 
    unsigned __int64                Volume;                    //�ܳɽ���[��??] 
} tagCcComm_HKSHIndexData; 

//[2��90]�����λ��
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_PriceTable | tagCcComm_PriceTable | tagCcComm_PriceTable
//ע��������tagCcComm _PriceTable
//ע�⣺���������֧�ֶַ�����
//�۹ɼ�λ��ṹ
typedef struct
{
	unsigned long	 PriceTo;	 //�۸�ȥ��, ����3λС��
	unsigned short	 SpreadValue;	 //ǰһ���۸�ȥ�򣨻��߼۸���Դ�� ����ǰ�۸�ȥ��, ����3λС��
} tagHKMem_PriceItem;

typedef struct
{
	char			 SpreadTableCode[2];	 //��λ����
	unsigned long 	 PriceFrom;	 //��λ�����Ͷ����۸�����3λС����
	unsigned short	 ItemsNumber;	 //��Ŀ�б��е���Ŀ������1~52
	
   	tagHKMem_PriceItem	PriceItem[52];	
} tagCcComm_HKSHPriceTable;

//[2��91] ����۹�ͨ����ļ�����
// ����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
// Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHNameHKTable | tagCcComm_HKSHNameHKTable | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char Code[6]; ///< �� Ʒ����
	char Sname[8]; ///< ���
	char Lname[50]; ///< ȫ��
	unsigned long IndexCode; ///< ָ������
	float NrRate; ///< �� ��������
} tagCcComm_HKSHNameHKTable;

//[2��92] ������Ʒ״̬�������
// ����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
// Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHStatusChg | tagCcComm_HKSHStatusChg | ...
//ע�⣺���������֧�ֶַ�����
typedef struct 
{ 
    char                             Code[6];                //��Ʒ���� 
    unsigned char                    SecTradingStatus1[8];    //��1λ����0����ʾ�������룬��1����ʾ�����޴����ơ� 
	//��2λ����0����ʾ������������1����ʾ�����޴����ơ� 
    unsigned char                    SecTradingStatus2[8];    //��1λ����0����ʾ�������룬��1����ʾ�����޴����ơ� 
	//��2λ����0����ʾ������������1����ʾ�����޴����ơ� 
} tagCcComm_HKSHStatusChg; 

//[2��39]�������֤ȯ״̬

//[2��95] �������г�״̬
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse|tagCcCom_Hk2ShMarketStatus
typedef struct 
{
	unsigned long		ulDate;	//�г�����[YYYYMMDD��ʽ]
	unsigned long		ulTime;	//�г�ʱ��[HHMMSS��ʽ]
	unsigned short		ushStatus;	//�г�״̬[0ȫ������,1����������(���̼��Ͼ���),2����(���̼��Ͼ���ʱ��),3��������,4����(���̼��Ͼ���ʱ��),5����������(���̼��Ͼ���ʱ��),7��ͣ,100δ����,101����ǰ(���̼��Ͼ���ʱ��),102Exchange Intervention,103����,104ȡ��������,105�ο��۶���(���̼��Ͼ���ʱ��),106����ȡ��(���̼��Ͼ���ʱ��),107�������(���̼��Ͼ���ʱ��)]
} tagCcCom_Hk2ShMarketStatus;	//�������г�״̬ ֻ��һ����¼

//[2��96] �е���������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse|tagCcCom_Hk2ShVCMStockData| tagCcCom_Hk2ShVCMStockData| ... 
//ע�⣺���������֧�ֶַ����� 

typedef struct 
{ 
	char		Code[6];	//��Ʒ����	 
	unsigned long		ulStartTime;	//�е���ʼʱ��[HHMMSS��ʽ]
	unsigned long		ulEndTime;	//�е�����ʱ��[HHMMSS��ʽ]
	unsigned long		ulRefPrice;	//�е����Ʋο���[* �Ŵ���] 
	unsigned long		ulLowerPrice;	//�е��������޼�[* �Ŵ���] 
	unsigned long		ulUpperPrice;	//�е��������޼�[* �Ŵ���] 
	
} tagCcCom_Hk2ShVCMStockData; 	//�е����� ��������

//[2��97] ���̼��Ͼ���
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse|tagCcCom_Hk2ShCASStockData| tagCcCom_Hk2ShCASStockData| ... 
//ע�⣺���������֧�ֶַ����� 

typedef struct 
{ 
	char		Code[6];	//��Ʒ����	 
	unsigned long		ulRefPrice;	//�е����Ʋο���[* �Ŵ���] 
	unsigned long		ulLowerPrice;	//�е��������޼�[* �Ŵ���] 
	unsigned long		ulUpperPrice;	//�е��������޼�[* �Ŵ���] 
	unsigned char		uchOrdImbDirection;	//������������̷���
	unsigned __int64		ulOrdImbQty;	//���������������
} tagCcCom_Hk2ShCASStockData; 	//���̼��Ͼ��� ��������


//[2��98]���͸۹���������
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char
//����0: �������г���Ϣ =tagCcCom_Hk2ShMarketStatus
//����1���е����� =  tagCcCom_Hk2ShVCMStockData
//����2�����̼��Ͼ��� = tagCcCom_Hk2ShCASStockData

//[2��34]�������֤ȯ�г������о���״̬
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HkCASStatus | tagCcComm_HkCASStatus | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char							Code[6];				//��Ʒ����
	unsigned long					RefPrice;				//�ο��۸�[* �Ŵ���]
	unsigned long					LowerPrice;				//���޼۸�[* �Ŵ���]
	unsigned long					UpperPrice;				//���޼۸�[* �Ŵ���]
	char							OrderIBDirection;		//���������������
	unsigned __int64				OrderIBQuantity;		//���������������
	char							CASFlag;				// Y:����Ʒ֧��CAS N:��֧��
} tagCcComm_HkCASStatus;

//[2��36]�������֤ȯ�г����г���������״̬
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HkVCMStatus | tagCcComm_HkVCMStatus | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	char							Code[6];				//��Ʒ����<2009-1-21 Lumy����>
	unsigned long					CoolingOffStartTime;	//���ڿ�ʼʱ��[HHMMSS]
	unsigned long					CoolingOffEndTime;		//���ڽ���ʱ��[HHMMSS]
	unsigned long					RefPrice;				//�ο��۸�[* �Ŵ���]
	unsigned long					LowerPrice;				//���޼۸�[* �Ŵ���]
	unsigned long					UpperPrice;				//���޼۸�[* �Ŵ���]
	char							VCMFlag;				// Y:����Ʒ֧��VCM N:��֧��
} tagCcComm_HkVCMStatus;

//[2��39]�������֤ȯ״̬
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcCom_Hk2ShMarketStatus | tagCcCom_Hk2ShMarketStatus | ...
//ע�⣺���������֧�ֶַ�����

//[2��48]���͸۹���չ��������
//���� 1�����о���״̬��Ϣ = tagCcComm_HkCASStatus
//���� 2���г�����״̬��Ϣ = tagCcComm_HkVCMStatus
//���� 3���г�״̬��Ϣ = tagCcComm_HkTrdSessionStatus

////////////////////////////����ͨend/////////////////////////////////////////////

////////////////////////////���ͨbegin/////////////////////////////////////////////

//[2��123] ���ƴ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHNameTable | tagCcComm_HKSHNameTable | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	unsigned short					Serial;                 //��Ʒ��� 
	unsigned char                   Type;                   //����Ʒ���� 
	char							Code[6];                //��Ʒ���� 
	char							EnglishName[16];        //Ӣ������ 
	char							ChineseName[16];        //�������� 
	char							SName[8];               //���ļ�� 
	unsigned long                   ListDate;               //�������� 
	unsigned long                   OffDate;                //�������� 
	unsigned long                   SpreadValue;            //���[* �Ŵ���] 
	unsigned long                   LotSize;                //����Ʒ��"��"���� 
	unsigned char                   Currency;               //�������� 
	unsigned char                   PriceTb;                //ʹ�����ż�λ�� 
	float							NrRate;                 //�޷������� 
	char							SecurityStatusFlag[8];  //��1λ����Y����ʾͣ�ƣ���N����ʾ��ͣ�� 
} tagCcComm_HKSZNameTable;

//[2��X] ���ɿ�������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSHStockData | tagCcComm_HKSHStockData | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	char							 Code[6];				 //��Ʒ����<2009-1-21 Lumy����> 
	unsigned long                    High;					 //��߼۸�[* �Ŵ���] 
	unsigned long                    Open;					 //���̼۸�[* �Ŵ���] 
	unsigned long                    Low;					 //��ͼ۸�[* �Ŵ���] 
	unsigned long                    Close;					 //���ռ۸�[* �Ŵ���] 
	unsigned long                    Now;					 //���¼۸�[* �Ŵ���] 
	double							 Amount;                 //�ܳɽ����[Ԫ] 
	unsigned __int64                 Volume;                 //�ܳɽ���[��] 
	unsigned long                    VBuyPrice;				 //ί��۸�[* �Ŵ���] 
	tagCcComm_HKBuySell              VBuy;					 //1������ 
	unsigned long                    VSellPrice;             //ί���۸�[* �Ŵ���] 
	tagCcComm_HKBuySell              VSell;					 //1������ 
	unsigned long                    Voip;					 //Ȩ֤��� 
} tagCcComm_HKSZStockData;

//[2��124]�������֤ͨȯ�г���ȫ�г����ɿ������� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZStockDataLv5 | tagCcComm_HKSZStockDataLv5 | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	char							Code[6];                //��Ʒ���� 
	unsigned long                   High;                   //��߼۸�[* �Ŵ���] 
	unsigned long                   Open;                   //���̼۸�[* �Ŵ���] 
	unsigned long                   Low;                    //��ͼ۸�[* �Ŵ���] 
	unsigned long                   Close;                  //���ռ۸�[* �Ŵ���] 
	unsigned long                   Now;                    //���¼۸�[* �Ŵ���] 
	double							Amount;                 //�ܳɽ����[Ԫ] 
	unsigned __int64                Volume;                 //�ܳɽ���[��] 
	unsigned long                   VBuyPrice;              //ί��۸�[* �Ŵ���] 
	tagCcComm_HKBuySell             VBuy[5];                //1������ 
	unsigned long                   VSellPrice;             //ί���۸�[* �Ŵ���] 
	tagCcComm_HKBuySell             VSell[5];               //1������ 
	unsigned long                   Voip;                   //Ȩ֤��� 
} tagCcComm_HKSZStockDataLv5;

//[2��125]�������֤ͨȯ�г����ο����� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZCurrency | tagCcComm_HKSZCurrency | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	unsigned long                   BuyCurrencyRatio;        //�ο���������ۣ�CNYHKD��[* �Ŵ���] * 100000 
	unsigned long                   SellCurrencyRatio;       //�ο����������ۣ�CNYHKD��[* �Ŵ���] * 100000 
	unsigned long                   CurrencyRatio;           //�ο������м�ۣ�CNYHKD��[* �Ŵ���] * 100000 
} tagCcComm_HKSZCurrency;

//[2��126]������֤ͨȯ�г�������������ݡ��г�״��Ϣ 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZAmount | tagCcComm_HKSZAmount | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	unsigned __int64                ThresholdAmount;         //ÿ�ճ�ʼ��ȣ���λ�����Ԫ 
	unsigned __int64                PosAmt;                  //����ʣ���ȣ���λ�����Ԫ 
	unsigned char                   TradSesStatus;           //���״̬ 
	//1��������ꣻ 
	//2����ȿ��á� 
	unsigned char                   MktStatus[8];            //��1λ����0����ʾȫ�г��������룬��1����ʾ�����޴����ơ� 
	//��2λ����0����ʾȫ�г�������������1����ʾ�����޴����ơ� 
	//��3λ����0����ʾ���շǸ۹�ͨ�����գ���1����ʾ���ո۹�ͨ�����ա� 
} tagCcComm_HKSZAmount;

//[2��127]����۹�֤ͨȯָ���������� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZIndexData | tagCcComm_HKSZIndexData | ... 
//ע�⣺���������֧�ֶַ����� 

typedef struct 
{ 
	char							Code[6];                 //��Ʒ����<2009-1-21 Lumy����> 
	unsigned long                   High;                    //���ָ��[* �Ŵ���] 
	unsigned long                   Open;                    //����ָ��[* �Ŵ���] 
	unsigned long                   Low;                     //���ָ��[* �Ŵ���] 
	unsigned long                   Close;                   //����ָ��[* �Ŵ���] 
	unsigned long                   Now;                     //����ָ��[* �Ŵ���] 
	double							Amount;                  //�ܳɽ����[Ԫ] 
	unsigned __int64                Volume;                  //�ܳɽ���[��??] 
} tagCcComm_HKSZIndexData;

//[2��128]������ۼ�λ�� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZPriceTable | tagCcComm_HKSZPriceTable | tagCcComm_HKSZPriceTable 
//ע��������tagCcComm_HKSZPriceTable 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	char							SpreadTableCode[2];      //��λ���� 
	unsigned long					PriceFrom;               //��λ�����Ͷ����۸�����3λС���� 
	unsigned short					ItemsNumber;             //��Ŀ�б��е���Ŀ������1~52 
	tagHKMem_PriceItem				PriceItem[52];     
} tagCcComm_HKSZPriceTable;

//[2��129]�������ͨ����ļ����� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZNameHKTable | tagCcComm_HKSZNameHKTable | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	char							Code[6];                 //��Ʒ���� 
	char							Sname[8];				 //��� 
	char							Lname[50];               //ȫ�� 
	unsigned long					IndexCode;               //ָ������ 
	float							NrRate;                  //�޷������� 
} tagCcComm_HKSZNameHKTable;

//[2��130]����۹�ͨ����״̬���� 
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKSZStatusChg | tagCcComm_HKSZStatusChg | ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	char							Code[6];                //��Ʒ���� 
	unsigned char					SecTradingStatus1[8];   //��1λ����0����ʾ�����������룬��1����ʾ�����޴����ơ� 
	//��2λ����0����ʾ����������������1����ʾ�����޴����ơ� 
	unsigned char					SecTradingStatus2[8];   //��1λ����0����ʾ����������룬��1����ʾ�����޴����ơ� 
	//��2λ����0����ʾ���������������1����ʾ�����޴����ơ� 
} tagCcComm_HKSZStatusChg;
//[2��134] ���̼��Ͼ���
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse|tagCcCom_Hk2ShCASStockData| tagCcCom_Hk2ShCASStockData| ... 
//ע�⣺���������֧�ֶַ����� 
typedef struct 
{ 
	char		Code[6];	//��Ʒ����	 
	unsigned long		ulRefPrice;	//�е����Ʋο���[* �Ŵ���] 
	unsigned long		ulLowerPrice;	//�е��������޼�[* �Ŵ���] 
	unsigned long		ulUpperPrice;	//�е��������޼�[* �Ŵ���] 
	unsigned char		uchOrdImbDirection;	//������������̷���
	unsigned __int64		ulOrdImbQty;	//���������������
} tagCcCom_Hk2SzCASStockData; 	//���̼��Ͼ��� ��������
//[2��132] �������г�״̬
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse|tagCcCom_Hk2ShMarketStatus
typedef struct 
{
	unsigned long		ulDate;	//�г�����[YYYYMMDD��ʽ]
	unsigned long		ulTime;	//�г�ʱ��[HHMMSS��ʽ]
	unsigned short		ushStatus;	//�г�״̬[0ȫ������,1����������(���̼��Ͼ���),2����(���̼��Ͼ���ʱ��),3��������,4����(���̼��Ͼ���ʱ��),5����������(���̼��Ͼ���ʱ��),7��ͣ,100δ����,101����ǰ(���̼��Ͼ���ʱ��),102Exchange Intervention,103����,104ȡ��������,105�ο��۶���(���̼��Ͼ���ʱ��),106����ȡ��(���̼��Ͼ���ʱ��),107�������(���̼��Ͼ���ʱ��)]
} tagCcCom_Hk2SzMarketStatus;	//�������г�״̬ ֻ��һ����¼

// [2��133] �е���������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply 
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse|tagCcCom_Hk2ShVCMStockData| tagCcCom_Hk2ShVCMStockData| ... 
//ע�⣺���������֧�ֶַ����� 

typedef struct 
{ 
	char		Code[6];	//��Ʒ����	 
	unsigned long		ulStartTime;	//�е���ʼʱ��[HHMMSS��ʽ]
	unsigned long		ulEndTime;	//�е�����ʱ��[HHMMSS��ʽ]
	unsigned long		ulRefPrice;	//�е����Ʋο���[* �Ŵ���] 
	unsigned long		ulLowerPrice;	//�е��������޼�[* �Ŵ���] 
	unsigned long		ulUpperPrice;	//�е��������޼�[* �Ŵ���] 
	
} tagCcCom_Hk2SzVCMStockData; 	//�е����� ��������

////////////////////////////���ͨend/////////////////////////////////////////////

////////////////////////////������Ȩbegin/////////////////////////////////////////////

typedef struct
{
     unsigned long			Serial;            //���
     unsigned char			Type;            //���(1 Ϊָ���� 2Ϊ ��Ȩ��Լ)
	 char					Code[8];		//��ƷID
//     char					SecurityID[8];        //��ƷID
     char					ContractID[20];        //��Լ���� 20150520 liuqy ��Լ��19����20
     char					SecuritySymbol[20];    //��Լ���
 
     char					OptionType;        //ŷʽ��ʽ(E-ŷʽ  A-��ʽ B-��Ľ��ʽ)
     char					CallOrPut;        //�Ϲ��Ϲ�(C-   P-)
 
     unsigned long			PreClosePx; //��Լ����(������Ȩ�� Ϣ��Ϊ����������̼۸�)(��ȷ����)//[*�Ŵ���]
     unsigned long			PreSettlePx; //��Լ���//[*�Ŵ���]
     int					LeavesQty;        //δƽ�ֺ�Լ�� = ��� �� ��λ��(��)
 
     char					UnderlyingCode[6];    //���֤ȯ����
 
     unsigned long			UpLimit; //������Ȩ��ͣ�۸�(��ȷ�� ��) //[*�Ŵ���]
     unsigned long			DownLimit; //������Ȩ��ͣ�۸�(��ȷ ����) //[*�Ŵ���]
     int                    LotSize;        //һ�ֵ��ڼ��ź�Լ
     int                    ContractUnit; //��Լ��λ(������Ȩ��Ϣ�� ����ĺ�Լ��λ��һ��Ϊ����)
 
     unsigned long          XqPrice;        //��Ȩ�۸�(��ȷ�� ��) //[*�Ŵ���]
     int                    StartDate;        //�׸�������(YYYYMMDD)
     int                    EndDate;        //�������(YYYYMMDD)
     int                    XqDate;            //��Ȩ��(YYYYMMDD)
     int                    DeliveryMonth;        //�����·�(YYMM)
     int                    ExpireDate;        //������(YYYYMMDD)
 
     unsigned long          MarginUnit; //��λ��֤��(��ȷ����) //[*�Ŵ�100]
 
//      char                   StatusFlag[8]; //��Ȩ��Լ״̬(8���ַ�, ��ϸ������ĵ�)
}tagCcComm_SzOptNameTable;
 
 
//[2, 113]�����Ϻ���Ȩ�г���������
//ע�⣺���������֧�ֶַ�����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_SzOptionData | tagCcComm_SzOptionData | ...
typedef struct
{
	unsigned int					  DataTimeStamp; //ʱ���(HHMMSSmmm)
	char					Code[8];		//��ƷID
	//     char					SecurityID[8];        //��ƷID
	//     char                             SecurityID[8];        //��Ʒ���� (!= �� Լ����)
	unsigned long                    PreSettlePx; //��Լ���//[*�Ŵ���]
	unsigned long                    SettlePrice;        //��� [*�Ŵ� ����]����ȷ3λ��
	unsigned long                    OpenPx;            //���̼� [*�Ŵ� ����]����ȷ3λ��
	unsigned long                    HighPx;            //��� [*�Ŵ� ��]����ȷ3λ��
	unsigned long                    LowPx;            //��� [*�Ŵ� ��]����ȷ3λ��
	unsigned long                    Now;            //���� [*�Ŵ� ��]����ȷ3λ��
	
	__int64                          Volume;            //�ɽ���
	__int64                          Amount;            //�ɽ���� [�Ŵ� 100��] 2λС��
// 	long							 TradingPhaseCode ;    //����״̬ ɾ��
// 	unsigned long					 AuctionPrice;        //�������ж� �ο��� [*�Ŵ���]����ȷ3λ��ɾ��
	char                            TradingPhaseCode[8]; //����״̬
	
	__int64                            Position;        //�ֲ���

// 	__int64							 AuctionQty; //�������жϼ��Ͼ������� ƥ����
// 	__int64                          Position;        //�ֲ���
	tagCcComm_BuySell                Buy[5];            //ί����
	tagCcComm_BuySell                Sell[5];        //ί����
}tagCcComm_SzOptionData; 
//[2,115]�����Ϻ���Ȩ�г�����
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ������� ϸ˵����
//�������ݿ����� = unsigned char
 
//����0�� �г���Ϣ = tagCcComm_SzOptMarketStatus
//����1�� ������Լ�������� = tagCcComm_SzOptionData
//����2�����ǰ׺��� = tagCcComm_SzPerNameChg
 
typedef struct
{
     unsigned char                    MarketID;        //�г����
     unsigned long                    MarketDate; //�г�����[YYYYMMDD��ʽ]
     unsigned long                    MarketTime; //�г�ʱ��[HHMMSS��ʽ]
     unsigned char                    MarketStatus; //�г�״̬[0��ʼ��״ 	 ̬ 1������״̬]
} tagCcComm_SzOptMarketStatus;
 
typedef struct
{
     char                            Code[8];        //��Ʒ����
     char                            PreName[4];        //��Ʒǰ׺
     unsigned char                    Status[2]; //�±�0���򿪲�=1(���� ��) =0(������);  �±�1,������=1(������) =0(������)
} tagCcComm_SzOptPerNameChg;
//[2, 116]����������Ȩ�г�֤ȯ״̬
//ע�⣺���������֧�ֶַ�����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_SzOptSecurityStatus | tagCcComm_SzOptSecurityStatus | ...
typedef struct
{
	char							Code[8];		//��Ʒ���� (!= ��Լ����)
	unsigned short      status;                //�����λ֤ȯ״̬����1~13
	char                        Reserve[4];       //�����ֶ�
} tagCcComm_SzOptSecurityStatus;
//[2, 117]����������Ȩ�г��������
// ����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
// Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_ SzOptBdData| tagCcComm_ SzOptBdData| ...
typedef struct
{
	char                        Code[6];
	unsigned long              BdClose;    //�������
	char                        Reserve[4]; //�����ֶ�
} tagCcComm_SzOptBdData;



////////////////////////////������Ȩend/////////////////////////////////////////////

////////////////////////////�����Ȩbegin/////////////////////////////////////////////

// [2��80] �������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKONameTable| tagCcComm_HKONameTable| ...

typedef struct
{
	unsigned long				Serial;			//��Ʒ���
	unsigned char				Type;			//����Ʒ���[��ӦMarketInfo�е����]
	
	char						Code[32];		//��Ʒ����
	char						TargetCode[6];	//���ָ���Ĵ��룬�ޱ��ָ��ʱ���
	unsigned char				TargetMarketID;	//���ָ���г����
	unsigned int				OrderbookID;		//���׺�
	
	char						CallOrPut;		//�Ϲ��Ϲ�(0Undefined 1Call 2Put)
	
	unsigned long				PreClosePx;		//���ռ۸�
	unsigned long				PreSettlePx;		//�����۸�
	__int64					PreOpenInterest;	//��ֲ���(��λ����Լ)
	
	unsigned long				ContractMultiplier;//��Լ����
	
	unsigned int				ExpirationDate;	//��������
	unsigned short				NumberOfDecimalsPrice;//С������
} tagCcComm_HKONameTable;

//[2��82] ��������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKOObjectData| tagCcComm_HKOObjectData| ...

typedef struct
{
	unsigned int				DataTimeStamp;			//ʱ���(HHMMSS)
	char						Code[32];				//��Ʒ����
	unsigned long				PreClose;					//���ռ۸�[* �Ŵ���]
	unsigned long				High;					//��߼۸�[* �Ŵ���]
	unsigned long				Open;					//���̼۸�[* �Ŵ���]
	unsigned long				Low;					//��ͼ۸�[* �Ŵ���]
	unsigned long				Now;					//���¼۸�[* �Ŵ���]
	unsigned long				CurVolume;				//�ɽ�����
	double					Amount;					//�ܳɽ����[Ԫ]
	unsigned __int64			Volume;					//�ܳɽ���[��]
	tagCcComm_BuySell		VBuy[5];					//5������
	tagCcComm_BuySell		VSell[5];					//5������
} tagCcComm_HKOObjectData;

//[2��83] �г�������չ��Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_KindPeriod |  ...
// typedef struct
// { 
// 	unsigned char                    Type;               // ���[��ӦMarketInfo�е����]
// 	unsigned char                    PeriodsCount;       // ʱ�������
// 	unsigned short                   Periods[4][2];      // ����ʱ���[���ֻ��4������ʱ�Σ�ÿ��ʱ�ΰ�����ʼ������ʱ�䣬��ȷ���֣�HH * 60 + MM��ʽ]
// } tagCcComm_KindPeriod;

//[2��84] �۹���Ȩ����̬����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_HKOStaticData | tagCcComm_HKOStaticData | ...

typedef struct
{
	char							Code[32];			//��Ʒ����
	unsigned long					PreClose;				//���ռ۸�
	unsigned long					Settle;				//�����۸�
	__int64						OpenInterest;			//��ֲ���(��λ����Լ)
	unsigned long					PreSettle;				//�����۸�
	__int64						PreOpenInterest;		//��ֲ���(��λ����Լ)
} tagCcComm_HKOStaticData;


//[2��85] ��������
//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =        	tagCcComm_MarketStatusInfo
//���� 1������ =	  			tagCcComm_HKOObjectData
//���� 2: �嵵������ =		tagCcComm_HKOBuySellData;
//���� 3����̬���� =			tagCcComm_HKOStaticData
typedef struct
{
	char							Code[32];			//��Ʒ����
	unsigned char					Side;				//��������(0 ��;1 ��)
	tagCcComm_BuySell			VBuy[5];				//5������
} tagCcComm_HKOBuySellData;

////////////////////////////�����Ȩend/////////////////////////////////////////////


////////////////////////////��Ʒ�ڻ���Ȩbegin/////////////////////////////////////////////
//[2��105]������Ʒ�ڻ�/Ȩ���ƴ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CsfexFutOptNameTable | tagCcComm_CsfexFutOptNameTable | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned short			Serial;						//��Ʒ���
	char					Type;						//����
	char					Code[20];					//��Լ����
	char					Name[40];					//��Լ����
	unsigned long			LotFactor;					//��
	//	unsigned long			PreClosePx;					//��Լ����(������Ȩ��Ϣ��Ϊ����������̼۸�)(��ȷ����)//[*�Ŵ���]
	//	unsigned long			PreSettlePx;				//��Լ���//[*�Ŵ���]
	char					Filler[8];
	int						LeavesQty;					//δƽ�ֺ�Լ�� = ��ֲ� ��λ��(��)
	unsigned char			ObjectMId;					//�Ϻ��ڻ� 0  �����ڻ� 1  ֣���ڻ� 2 �Ϻ���Ȩ 3  ������Ȩ 4  ֣����Ȩ 5
	char					UnderlyingCode[6];			//���֤ȯ����
	char					PriceLimitType;				//�ǵ�����������(N ���ǵ���)(R ���ǵ���)
	unsigned long			UpLimit;					//������Ȩ��ͣ�۸�(��ȷ����) //[*�Ŵ���]
	unsigned long			DownLimit;					//������Ȩ��ͣ�۸�(��ȷ����) //[*�Ŵ���]
	int						LotSize;					//һ�ֵ��ڼ��ź�Լ
	unsigned long			ContractMult;				//��Լ����
	unsigned long			XqPrice;					//��Ȩ�۸�(��ȷ����) //[*�Ŵ���] 
	int						StartDate;					//�׸�������(YYYYMMDD)
	int						EndDate;					//�������(YYYYMMDD)
	int						XqDate;						//��Ȩ��(YYYYMM)
	int						DeliveryDate;				//������(YYYYMMDD)
	int						ExpireDate;					//������(YYYYMMDD)
	unsigned short          TypePeriodIdx;             // ���ཻ��ʱ���λ��
	char 					Reserved[4];				//�����ֽ�
} tagCcComm_CsfexFutOptNameTable;


//[2, 104] ������Ʒ�ڻ���չ���ƴ������Ϣ
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CffexRelation | ��..

//[2��107]������Ʒ�ڻ�/Ȩȫ�г���������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CsfexFutOptStockData | tagCcComm_CsfexFutOptStockData | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned short				Date;					//����(mmdd)
	unsigned int				DataTimeStamp;			//ʱ���(HHMMSSmmm)
    char						Code[20];				//��Ʒ����<2009-1-21 Lumy����>
    unsigned long				High;                   //��߼۸�[* �Ŵ���]
    unsigned long				Open;                   //���̼۸�[* �Ŵ���]
    unsigned long				Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long				PreClose;               //���ռ۸�[* �Ŵ���]
    unsigned long				PreSettlePrice;         //���ս���۸�[* �Ŵ���]
    unsigned long				Now;                    //���¼۸�[* �Ŵ���]
    unsigned long				Close;                  //�������̼۸�[* �Ŵ���]
    unsigned long				SettlePrice;            //���ս���۸�[* �Ŵ���]
    unsigned long				UpperPrice;             //��ͣ�۸�[* �Ŵ���]
    unsigned long				LowerPrice;             //��ͣ�۸�[* �Ŵ���]
    double						Amount;                 //�ܳɽ����[Ԫ]
    unsigned __int64			Volume;                 //�ܳɽ���[��]
    unsigned __int64			PreOpenInterest;        //���ճֲ���[��]
    unsigned __int64			OpenInterest;           //�ֲ���[��]
    tagCcComm_BuySell			Buy[5];                 //ί������
    tagCcComm_BuySell			Sell[5];                //ί������
} tagCcComm_CsfexFutOptStockData;


//[2��112]������Ʒ�ڻ�/Ȩ��������

//���ͣ�MAIN_FRAME_HEAD | tagCcComm_TimeInfo | �������ݿ� | �������ݿ� | �������ݿ� | ��
//�������ݿ� = �������ݿ����� + �������ݿ�������Ͷ�Ӧ�Ľṹ���μ�������ϸ˵����
//�������ݿ����� = unsigned char

//���� 0: �г���Ϣ =	tagCcComm_MarketStatusInfo
//���� 1���������� =	tagCcComm_CsfexFutOptStockData


//[2, 111]������ʱ��η�������. 
// ����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
// Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CnfTypePeriod| tagCcComm_CnfTypePeriod| ...

typedef struct
{
    unsigned char ucPeriodsCount;   // ����ʱ���
	unsigned short usPeriods[6][2]; // ����ʱ�������[���֧��4��ʱ�Σ�ÿ��ʱ�μ�¼��ʼ�ͽ���ʱ�䣬��ȷ�����ӣ�HH * 60 + MM��ʽ]
} tagCcComm_CnfTypePeriod;


//[2��201]������Ʒ�ڻ�/Ȩ���ƴ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CnfOptNameTable | tagCcComm_CnfOptNameTable | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned short			Serial;						//��Ʒ���
	char					Type;						//����
	char					Code[20];					//��Լ����
	char					Name[40];					//��Լ����
	unsigned long			LotFactor;					//��
	//	unsigned long			PreClosePx;					//��Լ����(������Ȩ��Ϣ��Ϊ����������̼۸�)(��ȷ����)//[*�Ŵ���]
	//	unsigned long			PreSettlePx;				//��Լ���//[*�Ŵ���]
	char					Filler[8];
	int						LeavesQty;					//δƽ�ֺ�Լ�� = ��ֲ� ��λ��(��)
	unsigned char			ObjectMId;					//�Ϻ��ڻ� 0  �����ڻ� 1  ֣���ڻ� 2 �Ϻ���Ȩ 3  ������Ȩ 4  ֣����Ȩ 5
	char					UnderlyingCode[6];			//���֤ȯ����
	char					PriceLimitType;				//�ǵ�����������(N ���ǵ���)(R ���ǵ���)
	unsigned long			UpLimit;					//������Ȩ��ͣ�۸�(��ȷ����) //[*�Ŵ���]
	unsigned long			DownLimit;					//������Ȩ��ͣ�۸�(��ȷ����) //[*�Ŵ���]
	int						LotSize;					//һ�ֵ��ڼ��ź�Լ
	unsigned long			ContractMult;				//��Լ����
	unsigned long			XqPrice;					//��Ȩ�۸�(��ȷ����) //[*�Ŵ���] 
	int						StartDate;					//�׸�������(YYYYMMDD)
	int						EndDate;					//�������(YYYYMMDD)
	int						XqDate;						//��Ȩ��(YYYYMM)
	int						DeliveryDate;				//������(YYYYMMDD)
	int						ExpireDate;					//������(YYYYMMDD)
	unsigned short            TypePeriodIdx;             // ���ཻ��ʱ���λ��
	unsigned char           EarlyNightFlag;             //����orҹ�̱�־ 1������ 2��ҹ�� 
	char 					Reserved[3];				//�����ֽ�
} tagCcComm_CnfOptNameTable;



//[2��202]������Ʒ�ڻ�/Ȩȫ�г���������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CnfOptStockData | tagCcComm_CnfOptStockData | ...
//ע�⣺���������֧�ֶַ�����
typedef struct
{
	unsigned short              Date;                   //����(mmdd)
	unsigned int				DataTimeStamp;			//ʱ���(HHMMSSmmm)
    char						Code[20];				//��Ʒ����<2009-1-21 Lumy����>
    unsigned long				High;                   //��߼۸�[* �Ŵ���]
    unsigned long				Open;                   //���̼۸�[* �Ŵ���]
    unsigned long				Low;                    //��ͼ۸�[* �Ŵ���]
    unsigned long				PreClose;               //���ռ۸�[* �Ŵ���]
    unsigned long				PreSettlePrice;         //���ս���۸�[* �Ŵ���]
    unsigned long				Now;                    //���¼۸�[* �Ŵ���]
    unsigned long				Close;                  //�������̼۸�[* �Ŵ���]
    unsigned long				SettlePrice;            //���ս���۸�[* �Ŵ���]
    unsigned long				UpperPrice;             //��ͣ�۸�[* �Ŵ���]
    unsigned long				LowerPrice;             //��ͣ�۸�[* �Ŵ���]
    double						Amount;                 //�ܳɽ����[Ԫ]
    unsigned __int64			Volume;                 //�ܳɽ���[��]
    unsigned __int64			PreOpenInterest;        //���ճֲ���[��]
    unsigned __int64			OpenInterest;           //�ֲ���[��]
    tagCcComm_BuySell			Buy[5];                 //ί������
    tagCcComm_BuySell			Sell[5];                //ί������
} tagCcComm_CnfOptStockData;

//[2, 113]�������̺�ҹ�̺�Լ���ڽ�������Ϣ
// ����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply

// Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_CnfTradeDate| tagCcComm_ CnfTradeDate | ...

typedef struct
{	
	unsigned long  nNightDate;   // ҹ�̺�Լ��������	
	unsigned long  nEarlyDate;   // ���̺�Լ��������	
} tagCcComm_CnfTradeDate;

////////////////////////////��Ʒ�ڻ���Ȩend/////////////////////////////////////////////


////////////////////////////����ʽ����begin/////////////////////////////////////////////
//[2��2] ���ƴ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_OpenFundNameTable | tagCcComm_OpenFundNameTable | ...
//ע�⣺���������֧�ֶַ������������󡢷��������ͻ����С��ͨѶ�����С���������Ȼ�ܹ��������е��������ͬ��

typedef struct
{
	unsigned char					ucType;				// ����Ʒ���[��ӦMarketInfo�е����]
	char							Code[6];			// ��Ʒ����	��ӦJJDM�ֶ�
	char							szName[30];			// ��Ʒ����	��ӦJJMC�ֶ�
	char							szFundMgr[30];		//���������	��ӦJJGS�ֶ�	
	unsigned char					uchFundType;			// �������ID ��ӦFLSX�ֶ�
	unsigned	__int64				iFundVol;				//�����ܷ���(��λ�����)	��ӦFXZS�ֶ�  �Ŵ���Ϊ2
	unsigned	__int64				iFundSize;			//�����ģ(���) ��ӦJJZGM�ֶ� �Ŵ���Ϊ2
	unsigned	__int64				iFundFaceVal;			//��Ӧ������ֵFXJG�ֶ� �Ŵ��ʣ�2��
} tagCcComm_OpenFundNameTable;

//[2��3] �������
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_OpenFundTypeTable | tagCcComm_OpenFundTypeTable | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned char					uchFundType;			// �������ID
	char							szName[16];			// �����������
} tagCcComm_OpenFundTypeTable;

//[2��4] ����
//����MAIN_FRAME_HEAD | tagCcComm_MarketSubApply
//Ӧ��MAIN_FRAME_HEAD | tagCcComm_MarketSubResponse | tagCcComm_OpenFundStockData | tagCcComm_OpenFundStockData | ...
//ע�⣺���������֧�ֶַ�����

typedef struct
{
	unsigned long					ulCode;			//�ֲֹ�Ʊ���� �ֶ�CCG?DM
	unsigned long					ulVolume;		//�ֲ����� �ֶ�CCG?SL �Ŵ���Ϊ2
	double						dMarketVal;		//�ֲ���ֵ �ֶ�CCG?SZ ��2λС��
} tagCcComm_OpenFundShares;	// ����ֲֹ�Ʊ

typedef struct
{
	char						Code[6];			//��Ʒ����<2009-1-21 Lumy����>
	unsigned long				High;			//��߼۸�[* �Ŵ���]  ��Ӧ����λ��ֵNAV�ֶ� �Ŵ��ʣ�4������г�������
	unsigned long				Open;			//���̼۸�[* �Ŵ���]  ��Ӧ����λ��ֵNAV�ֶ�
	unsigned long				Low;			//��ͼ۸�[* �Ŵ���]  ��Ӧ����λ��ֵNAV�ֶ�
	unsigned long				Close;			//���ռ۸�[* �Ŵ���]  �������ľ�ֵ
	unsigned long				Now;			//���¼۸�[* �Ŵ���]  ��Ӧ����λ��ֵNAV�ֶ�
	double					Amount;			//�ܳɽ����
	unsigned __int64			Volume;			//�ܳɽ���
	unsigned long				UpdateTime;		//������Ϣ�������� ��ӦGXRQ�ֶ�
	unsigned long				TotalNAV;			//�ۼƾ�ֵ ��ӦLJJZ�ֶ� �Ŵ���6
	unsigned long				FundSharesRatio;		//�����Ʊ�ֱֲ��� ��ӦGPCCBL�ֶ� �Ŵ���2
	tagCcComm_OpenFundShares	FundShares[10];	//����ֲֹ�Ʊ
} tagCcComm_OpenFundStockData;


////////////////////////////����ʽ����end/////////////////////////////////////////////


//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//���²�֪����ʲô����
/*
typedef struct
{
	unsigned char	MarketID;			//�����г�ID
	short			DrvUnitCode;		//������Ԫ��
	unsigned long	Date;				//�г�����[YYYYMMDD��ʽ]
	unsigned long	Time;				//�г�ʱ��[HHMMSS��ʽ]
	unsigned int	delayTime;			//��ʱʱ��(��)	
	char			indexFileName[128];	//�����ʱ�ļ���
	char			DataFileName[128];	//�����ʱ�����ļ���
} INIRECORD;

typedef struct
{
	tagWriteLog  			* writeLog;		//��־����
	tagOnPushDataFun 		* pushFun;		//���͸��º���
} PUSHUPDATA;

*/

//--------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------
////////////////////////This Code AUTO Mount Point By Append////////////

////////////////////////LINUX newline ���ڸ�ע�������CODE///////////////////
