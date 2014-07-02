#ifndef ITEM_BASE_H
#define ITEM_BASE_H

class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	virtual unsigned int getEquipLevel();
public:
	unsigned int	m_id;				//物品Id
	char			m_name[128];		//物品名
	bool			b_isPiledUp;		//是否可堆叠
	unsigned int	m_maxPiledNum;		//最大堆叠数量
	unsigned int	m_source[5];		//获取方式
	unsigned int	m_byeprice;			//购买价格
	unsigned int	m_sellprice;		//卖出价格
	unsigned int	m_requiredLevel;	//等级要求
	unsigned int	m_type;				//物品类型
	bool			b_Destroyed;		//是否可摧毁
	char            m_szDescription[128]; //描述字段
	unsigned int	m_quality;			//物品品质
	char     m_szInlayHole[128];
};

#endif