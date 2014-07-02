#ifndef __TAI_BEVTREE_H__
#define __TAI_BEVTREE_H__

#include <assert.h>
#include <string>
#include "AnyData.h"

namespace BehaviorTree{

#define k_BLimited_MaxChildNodeCnt              16
#define k_BLimited_InvalidChildNodeIndex        k_BLimited_MaxChildNodeCnt

	enum E_ParallelFinishCondition
	{
		k_PFC_OR = 1,
		k_PFC_AND
	};

	enum BevRunningStatus
	{
		k_BRS_Executing					= 0,
		k_BRS_Finish					= 1,
		k_BRS_ERROR_Transition			= -1,
	};

	enum E_TerminalNodeStaus
	{
		k_TNS_Ready         = 1,
		k_TNS_Running       = 2,
		k_TNS_Finish        = 3,
	};

	typedef AnyData BevNodeInputParam;
	typedef AnyData BevNodeOutputParam;

	//-------------------------------------------------------------------------------------------------------------------------------------
	class BevNodePrecondition
	{
	public:
		virtual bool ExternalCondition(const BevNodeInputParam& input) const = 0;
	};
	class BevNodePreconditionTRUE : public BevNodePrecondition
	{
	public:
		virtual bool ExternalCondition(const BevNodeInputParam& input) const{
			return true;
		}
	};
	class BevNodePreconditionFALSE : public BevNodePrecondition
	{
	public:
		virtual bool ExternalCondition(const BevNodeInputParam& input) const{
			return false;
		}
	};
	class BevNodePreconditionNOT : public BevNodePrecondition
	{
	public:
		BevNodePreconditionNOT(BevNodePrecondition* lhs)
			: m_lhs(lhs)
		{
			assert(m_lhs != NULL);
		}
		~BevNodePreconditionNOT()
		{
			delete m_lhs;
			m_lhs = NULL;
		}
		virtual bool ExternalCondition(const BevNodeInputParam& input) const{
			return !m_lhs->ExternalCondition(input);
		}
	private:
		BevNodePrecondition* m_lhs;
	};
	class BevNodePreconditionAND : public BevNodePrecondition
	{
	public:
		BevNodePreconditionAND(BevNodePrecondition* lhs, BevNodePrecondition* rhs)
			: m_lhs(lhs)
			, m_rhs(rhs)
		{
			assert(m_lhs && m_rhs);
		}
		~BevNodePreconditionAND()
		{
			delete m_lhs;
			delete m_rhs;
			m_lhs = NULL;
			m_rhs = NULL;
		}
		virtual bool ExternalCondition(const BevNodeInputParam& input) const{
			return m_lhs->ExternalCondition(input) && m_rhs->ExternalCondition(input);
		}
	private:
		BevNodePrecondition* m_lhs;
		BevNodePrecondition* m_rhs;
	};
	class BevNodePreconditionOR : public BevNodePrecondition
	{
	public:
		BevNodePreconditionOR(BevNodePrecondition* lhs, BevNodePrecondition* rhs)
			: m_lhs(lhs)
			, m_rhs(rhs)
		{
			assert(m_lhs && m_rhs);
		}
		~BevNodePreconditionOR(){
			delete m_lhs;
			delete m_rhs;
			m_lhs = NULL;
			m_rhs = NULL;
		}
		virtual bool ExternalCondition(const BevNodeInputParam& input) const{
			return m_lhs->ExternalCondition(input) || m_rhs->ExternalCondition(input);
		}
	private:
		BevNodePrecondition* m_lhs;
		BevNodePrecondition* m_rhs;
	};
	class BevNodePreconditionXOR : public BevNodePrecondition
	{
	public:
		BevNodePreconditionXOR(BevNodePrecondition* lhs, BevNodePrecondition* rhs)
			: m_lhs(lhs)
			, m_rhs(rhs)
		{
			assert(m_lhs && m_rhs);
		}
		~BevNodePreconditionXOR(){
			delete m_lhs;
			m_lhs = NULL;
			delete m_rhs;
			m_rhs = NULL;
		}
		virtual bool ExternalCondition(const BevNodeInputParam& input) const{
			return m_lhs->ExternalCondition(input) ^ m_rhs->ExternalCondition(input);
		}
	private:
		BevNodePrecondition* m_lhs;
		BevNodePrecondition* m_rhs;
	};
	//-------------------------------------------------------------------------------------------------------------------------------------
	class BevNode
	{
	public:
		BevNode(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodeScript = NULL)
			: mul_ChildNodeCount(0)
			, mz_DebugName("UNNAMED")
			, mo_ActiveNode(NULL)
			, mo_LastActiveNode(NULL)
			, mo_NodePrecondition(NULL)
		{
			for(int i = 0; i < k_BLimited_MaxChildNodeCnt; ++i)
				mao_ChildNodeList[i] = NULL;

			_SetParentNode(_o_ParentNode);
			SetNodePrecondition(_o_NodeScript);
		}
		virtual ~BevNode()
		{
			for(unsigned int i = 0; i < mul_ChildNodeCount; ++i)
			{
				delete mao_ChildNodeList[i];
				mao_ChildNodeList[i] = NULL;
			}
			delete mo_NodePrecondition;
			mo_NodePrecondition = NULL;
		}
		bool Evaluate(const BevNodeInputParam& input)
		{
			return (mo_NodePrecondition == NULL || mo_NodePrecondition->ExternalCondition(input)) && _DoEvaluate(input);
		}
		void Transition(const BevNodeInputParam& input)
		{
			_DoTransition(input);
		}
		BevRunningStatus Tick(const BevNodeInputParam& input, BevNodeOutputParam& output)
		{
			return _DoTick(input, output);
		}
		//---------------------------------------------------------------
		BevNode& AddChildNode(BevNode* _o_ChildNode)
		{
			if(mul_ChildNodeCount == k_BLimited_MaxChildNodeCnt)
			{
				//D_Output("The number of child nodes is up to 16");
				assert(0);
				return (*this);
			}
			mao_ChildNodeList[mul_ChildNodeCount] = _o_ChildNode;
			++mul_ChildNodeCount;
			return (*this);
		}
		BevNode& SetNodePrecondition(BevNodePrecondition* _o_NodePrecondition)
		{
			if(mo_NodePrecondition != _o_NodePrecondition)
			{
				if(mo_NodePrecondition)
					delete mo_NodePrecondition;

				mo_NodePrecondition = _o_NodePrecondition;
			}
			return (*this);
		}
		BevNode& SetDebugName(const char* _debugName)
		{
			mz_DebugName = _debugName;
			return (*this);
		}
		const BevNode* oGetLastActiveNode() const
		{
			return mo_LastActiveNode;
		}
		void SetActiveNode(BevNode* _o_Node)
		{
			mo_LastActiveNode = mo_ActiveNode;
			mo_ActiveNode = _o_Node;
			if(mo_ParentNode != NULL)
				mo_ParentNode->SetActiveNode(_o_Node);
		}
		const char* GetDebugName() const
		{
			return mz_DebugName.c_str();
		}
	protected:
		//--------------------------------------------------------------
		// virtual function
		//--------------------------------------------------------------
		virtual bool _DoEvaluate(const BevNodeInputParam& input)
		{
			return true;
		}
		virtual void _DoTransition(const BevNodeInputParam& input)
		{
		}
		virtual BevRunningStatus _DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output)
		{
			return k_BRS_Finish;
		}
	protected:
		void _SetParentNode(BevNode* _o_ParentNode)
		{
			mo_ParentNode = _o_ParentNode;
		}
		bool _bCheckIndex(unsigned int _ui_Index) const
		{
			return _ui_Index >= 0 && _ui_Index < mul_ChildNodeCount;
		}
	protected:
		BevNode*                mao_ChildNodeList[k_BLimited_MaxChildNodeCnt];
		unsigned int			mul_ChildNodeCount;
		BevNode*                mo_ParentNode;
		BevNode*                mo_ActiveNode;
		BevNode*				mo_LastActiveNode;
		BevNodePrecondition*    mo_NodePrecondition;
		std::string				mz_DebugName;
	};

	class BevNodePrioritySelector : public BevNode
	{
	public:
		BevNodePrioritySelector(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodePrecondition = NULL)
			: BevNode(_o_ParentNode, _o_NodePrecondition)
			, mui_LastSelectIndex(k_BLimited_InvalidChildNodeIndex)
			, mui_CurrentSelectIndex(k_BLimited_InvalidChildNodeIndex)
		{}
		virtual bool _DoEvaluate(const BevNodeInputParam& input);
		virtual void _DoTransition(const BevNodeInputParam& input);
		virtual BevRunningStatus _DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output);

	protected:
		unsigned int mui_CurrentSelectIndex;
		unsigned int mui_LastSelectIndex;
	};

	class BevNodeNonePrioritySelector : public BevNodePrioritySelector
	{
	public:
		BevNodeNonePrioritySelector(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodePrecondition = NULL)
			: BevNodePrioritySelector(_o_ParentNode, _o_NodePrecondition)
		{}
		virtual bool _DoEvaluate(const BevNodeInputParam& input);
	};

	class BevNodeSequence : public BevNode
	{
	public:
		BevNodeSequence(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodePrecondition = NULL)
			: BevNode(_o_ParentNode, _o_NodePrecondition)
			, mui_CurrentNodeIndex(k_BLimited_InvalidChildNodeIndex)
		{}
		virtual bool _DoEvaluate(const BevNodeInputParam& input);
		virtual void _DoTransition(const BevNodeInputParam& input);
		virtual BevRunningStatus _DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output);

	private:
		unsigned int mui_CurrentNodeIndex;
	};

	class BevNodeTerminal : public BevNode
	{
	public:
		BevNodeTerminal(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodePrecondition = NULL)
			: BevNode(_o_ParentNode, _o_NodePrecondition)
			, me_Status(k_TNS_Ready)
			, mb_NeedExit(false)
		{}
		virtual void _DoTransition(const BevNodeInputParam& input);
		virtual BevRunningStatus _DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output);

	protected:
		virtual void				_DoEnter(const BevNodeInputParam& input)								{}
		virtual BevRunningStatus	_DoExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)	{ return k_BRS_Finish;}
		virtual void				_DoExit(const BevNodeInputParam& input, BevRunningStatus _ui_ExitID)	{}

	private:
		E_TerminalNodeStaus me_Status;
		bool                mb_NeedExit;
	};

	class BevNodeParallel : public BevNode
	{
	public:
		BevNodeParallel(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodePrecondition = NULL)
			: BevNode(_o_ParentNode, _o_NodePrecondition)
			, me_FinishCondition(k_PFC_OR)
		{
			for(unsigned int i = 0; i < k_BLimited_MaxChildNodeCnt; ++i)
				mab_ChildNodeStatus[i] = k_BRS_Executing;
		}
		virtual bool _DoEvaluate(const BevNodeInputParam& input);
		virtual void _DoTransition(const BevNodeInputParam& input);
		virtual BevRunningStatus _DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output);

		BevNodeParallel& SetFinishCondition(E_ParallelFinishCondition _e_Condition);

	protected:
		E_ParallelFinishCondition me_FinishCondition;
		BevRunningStatus		  mab_ChildNodeStatus[k_BLimited_MaxChildNodeCnt];
	};

	class BevNodeLoop : public BevNode
	{
	public:
		static const int kInfiniteLoop = -1;

	public:
		BevNodeLoop(BevNode* _o_ParentNode, BevNodePrecondition* _o_NodePrecondition = NULL, int _i_LoopCnt = kInfiniteLoop)
			: BevNode(_o_ParentNode, _o_NodePrecondition)
			, mi_LoopCount(_i_LoopCnt)
			, mi_CurrentCount(0)
		{}
		virtual bool _DoEvaluate(const BevNodeInputParam& input);
		virtual void _DoTransition(const BevNodeInputParam& input);
		virtual BevRunningStatus _DoTick(const BevNodeInputParam& input, BevNodeOutputParam& output);

	private:
		int mi_LoopCount;
		int mi_CurrentCount;
	};

	class BevNodeFactory
	{
	public:
		static BevNode& oCreateParallelNode(BevNode* _o_Parent, E_ParallelFinishCondition _e_Condition, const char* _debugName)
		{
			BevNodeParallel* pReturn = new BevNodeParallel(_o_Parent);
			pReturn->SetFinishCondition(_e_Condition);
			oCreateNodeCommon(pReturn, _o_Parent, _debugName);
			return (*pReturn);
		}
		static BevNode& oCreatePrioritySelectorNode(BevNode* _o_Parent, const char* _debugName)
		{
			BevNodePrioritySelector* pReturn = new BevNodePrioritySelector(_o_Parent);
			oCreateNodeCommon(pReturn, _o_Parent, _debugName);
			return (*pReturn);
		}
		static BevNode& oCreateNonePrioritySelectorNode(BevNode* _o_Parent, const char* _debugName)
		{
			BevNodeNonePrioritySelector* pReturn = new BevNodeNonePrioritySelector(_o_Parent);
			oCreateNodeCommon(pReturn, _o_Parent, _debugName);
			return (*pReturn);
		}
		static BevNode& oCreateSequenceNode(BevNode* _o_Parent, const char* _debugName)
		{
			BevNodeSequence* pReturn = new BevNodeSequence(_o_Parent);
			oCreateNodeCommon(pReturn, _o_Parent, _debugName);
			return (*pReturn);
		}
		static BevNode& oCreateLoopNode(BevNode* _o_Parent, const char* _debugName, int _i_LoopCount)
		{
			BevNodeLoop* pReturn = new BevNodeLoop(_o_Parent, NULL, _i_LoopCount);
			oCreateNodeCommon(pReturn, _o_Parent, _debugName);
			return (*pReturn);
		}
		template<typename T>
		static BevNode& oCreateTeminalNode(BevNode* _o_Parent, const char* _debugName)
		{
			BevNodeTerminal* pReturn = new T(_o_Parent);
			oCreateNodeCommon(pReturn, _o_Parent, _debugName);
			return (*pReturn);
		}
	private:
		static void oCreateNodeCommon(BevNode* _o_Me, BevNode* _o_Parent, const char* _debugName)
		{
			if(_o_Parent)
				_o_Parent->AddChildNode(_o_Me);
			_o_Me->SetDebugName(_debugName);
		}
	};
}

#endif