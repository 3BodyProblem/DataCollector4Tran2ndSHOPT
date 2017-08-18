#ifndef __CTP_QUOTATION_PROTOCAL_TRAN2ND_SHOPT_H__
#define	__CTP_QUOTATION_PROTOCAL_TRAN2ND_SHOPT_H__
#pragma pack(1)


typedef struct
{
	char						Key[20];					///< ������ֵ
	unsigned int				MarketID;					///< �г����
	unsigned int				MarketDate;					///< �г�����
	unsigned int				KindCount;					///< �������
	unsigned int				WareCount;					///< ��Ʒ����
	unsigned int				PeriodsCount;				///< ����ʱ����Ϣ�б���
	unsigned int				MarketPeriods[8][2];		///< ����ʱ��������Ϣ�б�
} tagSHOptMarketInfo_LF157;


typedef struct
{
	char						Key[20];					///< ������ֵ
	char						KindName[64];				///< ��������
	unsigned int				PriceRate;					///< �۸�Ŵ���[10�Ķ��ٴη�]
	unsigned int				LotSize;					///< ���֡�����
	unsigned int				WareCount;					///< �÷������Ʒ����
} tagSHOptKindDetail_LF158;


typedef struct
{
	char						Key[20];					///< ������ֵ
	unsigned int				MarketTime;					///< �г�ʱ��
	char						StatusFlag[8];				///< �г�״̬(8���ַ�,��ϸ������ĵ�)
} tagSHOptMarketStatus_HF159;


typedef struct
{
	char						Code[20];					///< ��Լ����
	char						ContractID[20];				///< ��Լ����
	char						Name[64];					///< ��Լ����
	unsigned short				Kind;						///< ֤ȯ����
	unsigned char				DerivativeType;				///< ����Ʒ���ͣ�ŷʽ��ʽ+�Ϲ��Ϲ�
	char						UpdateVersion;				///< ��Ȩ��Լ�İ汾��(�¹Һ�Լ��'1')
	unsigned int				LotSize;					///< һ�ֵ��ڼ��ź�Լ
	char						UnderlyingCode[20];			///< ���֤ȯ����
	unsigned int				ContractUnit;				///< ��Լ��λ(������Ȩ��Ϣ������ĺ�Լ��λ��һ��Ϊ����)
	unsigned int				XqPrice;					///< ��Ȩ�۸�[*�Ŵ���]
	unsigned int				StartDate;					///< �׸�������(YYYYMMDD)
	unsigned int				EndDate;					///< �������(YYYYMMDD)
	unsigned int				XqDate;						///< ��Ȩ��(YYYYMM)
	unsigned int				DeliveryDate;				///< ������(YYYYMMDD)
	unsigned int				ExpireDate;					///< ������(YYYYMMDD)
	char						StatusFlag[8];				///< ��Ȩ��Լ״̬(8���ַ�,��ϸ������ĵ�)
} tagSHOptReferenceData_LF160;


typedef struct
{
	char						Code[20];					///< ��Լ����
	unsigned int				Open;						///< ���̼�[*�Ŵ���]
	unsigned int				Close;						///< ���ռ�[*�Ŵ���]
	unsigned int				PreClose;					///< ���ռ�[*�Ŵ���]
	unsigned int				UpperPrice;					///< ������ͣ�۸�[*�Ŵ���], 0��ʾ������
	unsigned int				LowerPrice;					///< ���յ�ͣ�۸�[*�Ŵ���], 0��ʾ������
	unsigned int				SettlePrice;				///< ����[*�Ŵ���]
	unsigned int				PreSettlePrice;				///< ��Լ���[*�Ŵ���]
	unsigned __int64			PreOpenInterest;			///< ���ճֲ���(��)
	unsigned int				AuctionPrice;				///< �������жϲο���[*�Ŵ���]
	unsigned __int64			AuctionQty;					///< �������жϼ��Ͼ���������
	char						TradingPhaseCode[4];		///< ����״̬
} tagSHOptSnapData_LF161;


typedef struct
{
	char						Code[20];					///< ��Լ����
	unsigned int				Now;						///< ���¼�[*�Ŵ���]
	unsigned int				High;						///< ��߼�[*�Ŵ���]
	unsigned int				Low;						///< ��ͼ�[*�Ŵ���]
	double						Amount;						///< �ܳɽ����[Ԫ]
	unsigned __int64			Volume;						///< �ܳɽ���[��/��]
	unsigned __int64			Position;					///< �ֲ���
} tagSHOptSnapData_HF162;


typedef struct
{
	unsigned int				Price;						///< ί�м۸�[* �Ŵ���]
	unsigned __int64			Volume;						///< ί����[��]
} tagSHOptBuySellItem;


typedef struct
{
	char						Code[20];					///< ��Լ����
	tagSHOptBuySellItem			Buy[5];						///< ���嵵
	tagSHOptBuySellItem			Sell[5];					///< ���嵵
} tagSHOptSnapBuySell_HF163;


#pragma pack()
#endif









