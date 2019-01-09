
#include "stdafx.h"
#include "SYS.h"

//--------------------------------------------------------------------
int main(int argc, char **argv)
{
	//-----------------------------------------------------------
	cout<<GetTime()<<"main()"<<endl;
	//-----------------------------------------------------------
	cout<<GetTime()<<"create Shared Memory"<<endl;
	m_handle = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MemoryPoolStruc), L"MySharedMemory");
	m_pMemPool =  (struct MemoryPoolStruc*) MapViewOfFile(m_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, sizeof(MemoryPoolStruc));
	//-----------------------------------------------------------
	cout<<GetTime()<<"main argv: ";
	for(int i = 1; i < argc; i++) 
		cout << argv[i]<<" ";
	cout << endl; 
	//-----------------------------------------------------------
	cout<<GetTime()<<"remove static memory query files"<<endl;
	remove(m_sUIPath);
	remove(m_sSYSPath);
	//-----------------------------------------------------------
	cout<<GetTime()<<"create static memory query files"<<endl;
	if (!std::ifstream(m_sUIPath))
		std::ofstream outfile (m_sUIPath);
	if (!std::ifstream(m_sSYSPath))
		std::ofstream outfile (m_sSYSPath);
	if (!std::ifstream(m_sStaticPoolPath))
		std::ofstream outfile (m_sStaticPoolPath);
	//-----------------------------------------------------------
	cout<<GetTime()<<"set static memory query files hidden"<<endl;
	mbstowcs(m_wtextUI, m_sUIPath, strlen(m_sUIPath)+1); 
	m_pCShandle = m_wtextUI;
	mbstowcs(m_wtextSYS, m_sSYSPath, strlen(m_sSYSPath)+1);    
	LPWSTR ptr_CPP_control = m_wtextSYS;   m_nAttr= GetFileAttributes(ptr_CPP_control); 
	SetFileAttributes(m_wtextSYS, FILE_ATTRIBUTE_HIDDEN); 
	SetFileAttributes(m_wtextUI,  FILE_ATTRIBUTE_HIDDEN); 
	//-----------------------------------------------------------
	if (argc == 1)
	{  
		cout<<GetTime()<<"call UI"<<endl;
		system ("start D:\\ControlServer\\UI.exe SYS call UI");
	}
	//-----------------------------------------------------------
	cout<<GetTime()<<"SYS send UI test msg: TEST!"<<endl;
	log2ui("SYS send UI test msg: TEST!");
	//FreeConsole(); //hide console window
	//-----------------------------------------------------------
	log2ui("run SimulateMultiThread()");
	SimulateMultiThread();
	//-----------------------------------------------------------
}
//--------------------------------------------------------------------
void SimulateMultiThread()
{
	int nTimeNow = clock();
	int nOneMiniSecondTimer = nTimeNow;
	int nTenMiniSecondTimer = nTimeNow;
	int nOneSecondTimer = nTimeNow;

	while (true)
	{
		nTimeNow =  clock();

		//parent seq
		ParentSeq_ModA_Simple_Cmds(RP(IP::Sys_ParentSeq_ModA_Simple_Cmds));
		ParentSeq_ModA_Complex_Cmds(RP(IP::Sys_ParentSeq_ModA_Complex_Cmds));
		ParentSeq_ModB_Simple_Cmds(RP(IP::Sys_ParentSeq_ModB_Simple_Cmds));
		ParentSeq_ModB_Complex_Cmds(RP(IP::Sys_ParentSeq_ModB_Complex_Cmds));

		while (nTimeNow > nOneMiniSecondTimer+1)   
		{
			//write code here
			nOneMiniSecondTimer = nTimeNow;
		}

		while (nTimeNow > nTenMiniSecondTimer+10)   
		{
			//write code here
			nTenMiniSecondTimer = nTimeNow;
		}

		while (nTimeNow > nOneSecondTimer+1000)   
		{
			//write code here
			nOneSecondTimer = nTimeNow;
		}
	}
}
//--------------------------------------------------------------------
int SubSeq_NG(int nSeq_External)
{
	string sPrintSeq="SubSeq_NG-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);
	
	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		break;
		
	case cas::Seq_NNNNNNNNGGGGGGGG:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_NNNNNNNNGGGGGGGG;
	}
	return nSeq_Temp;
}
//--------------------------------------------------------------------
int SubSeq_b1(int nSeq_External)
{
	string sPrintSeq="SubSeq_b1-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		s_nSeq_Now = cas::Wait_1;
		break;

	case cas::Wait_1:
		s_nSeq_Now = cas::Wait_2;
		break;

	case cas::Wait_2:
		s_nSeq_Now = cas::Wait_3;
		break;

	case cas::Wait_3:
		s_nSeq_Now = cas::Seq_OK;
		break;

	case cas::Seq_OK:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_OK;
	}
	return nSeq_Temp;
}
//--------------------------------------------------------------------
int SubSeq_b2(int nSeq_External)
{
	string sPrintSeq="SubSeq_b2-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		s_nSeq_Now = cas::Wait_1;
		break;

	case cas::Wait_1:
		s_nSeq_Now = cas::Wait_2;
		break;

	case cas::Wait_2:
		s_nSeq_Now = cas::Call_ModA_Cmd_5;
		break;

	case cas::Call_ModA_Cmd_5:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModA,CS::CS_ModA_Cmd_5))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else
		{
			if(RP(IP::CS_ModA)==CS::CS_OK)
			{
				s_nSeq_Now = cas::Seq_OK;
			}
			else if(RP(IP::CS_ModA)==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

	case cas::Seq_NNNNNNNNGGGGGGGG:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_NNNNNNNNGGGGGGGG;

	case cas::Seq_OK:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_OK;
	}
	return nSeq_Temp;
}
//--------------------------------------------------------------------
int SubSeq_B(int nSeq_External)
{
	string sPrintSeq="SubSeq_B-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;
	//-------------------
	int nTemp;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		s_nSeq_Now = cas::Call_Seq_b1;
		break;

	case cas::Call_Seq_b1:
		nTemp = SubSeq_b1(cas::Seq_Start);
		if(nTemp ==cas::Seq_OK)
		{
			s_nSeq_Now = cas::Call_Seq_b2;
		}
		else if(nTemp == cas::Seq_NNNNNNNNGGGGGGGG)
		{
			s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		break;

	case cas::Call_Seq_b2:
		nTemp = SubSeq_b2(cas::Seq_Start);
		if(nTemp ==cas::Seq_OK)
		{
			s_nSeq_Now = cas::Seq_OK;
		}
		else if(nTemp == cas::Seq_NNNNNNNNGGGGGGGG)
		{
			s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		break;

	case cas::Seq_NNNNNNNNGGGGGGGG:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_NNNNNNNNGGGGGGGG;

	case cas::Seq_OK:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_OK;
	}
	return nSeq_Temp;
}
//--------------------------------------------------------------------
int SubSeq_A(int nSeq_External)
{
	string sPrintSeq="SubSeq_A-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		s_nSeq_Now = cas::Wait_1;
		break;

	case cas::Wait_1:
		s_nSeq_Now = cas::Wait_2;
		break;

	case cas::Wait_2:
		s_nSeq_Now = cas::Wait_3;
		break;

	case cas::Wait_3:
		s_nSeq_Now = cas::Seq_OK;
		break;

	case cas::Seq_OK:
		s_nSeq_Now = cas::Seq_Reject;
		return cas::Seq_OK;
	}
	return nSeq_Temp;
}
//--------------------------------------------------------------------
void ParentSeq_ModA_Simple_Cmds(int nSeq_External)
{
	string sPrintSeq="ParentSeq_ModA_Simple_Cmds-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;
	//-------------------
	int nTemp;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		if(s_nSameCaseCount==0)
		{
			msg2user("SYS: ParentSeq_ModA_Simple_Cmds START"); //parent seq
			log2ui(sPrintSeq+"check server lock");
		}


		nTemp = RP(IP::CS_ModA);
		if(RP(IP::CS_ModA)==CS::CS_Unlock)
		{
			log2ui(sPrintSeq+"lock server");
			WP(IP::CS_ModA,CS::CS_OK);
			s_nSeq_Now = Call_Seq_A;
		}
		break;

	case cas::Call_Seq_A:
		nTemp = SubSeq_A(cas::Seq_Start);
		if(nTemp ==cas::Seq_OK)
		{
			s_nSeq_Now = cas::ModA_Cmd_1;
		}
		else if(nTemp == cas::Seq_NNNNNNNNGGGGGGGG)
		{
			s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		break;

	case cas::ModA_Cmd_1:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModA,CS::CS_ModA_Cmd_1))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else
		{
			int nTemp = RP(IP::CS_ModA);
			if(nTemp==CS::CS_OK)
			{
				s_nSeq_Now = cas::ModA_Cmd_2;
			}
			else if(nTemp==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

	case cas::ModA_Cmd_2:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModA,CS::CS_ModA_Cmd_2))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else
		{
			int nTemp = RP(IP::CS_ModA);
			if(nTemp==CS::CS_OK)
			{
				s_nSeq_Now = cas::Call_Seq_B;
			}
			else if(nTemp==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

	case cas::Call_Seq_B:
		nTemp = SubSeq_B(cas::Seq_Start);
		if(nTemp ==cas::Seq_OK)
		{
			s_nSeq_Now = cas::Seq_OK;
		}
		else if(nTemp == cas::Seq_NNNNNNNNGGGGGGGG)
		{
			s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		break;

	case cas::Seq_OK:
		//---------------
		WP(IP::CS_ModA,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModA_Simple_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModA_Simple_Cmds DONE");  //parent seq
		//---------------
		break;


	case cas::Seq_NNNNNNNNGGGGGGGG:
		//---------------
		WP(IP::CS_ModA,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModA_Simple_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModA_Simple_Cmds FAIL");  //parent seq
		//---------------
		break;
	}

}
//--------------------------------------------------------------------
void ParentSeq_ModA_Complex_Cmds(int nSeq_External)
{
	string sPrintSeq="ParentSeq_ModA_Complex_Cmds-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;
	//--------------
	static int s_nCount;
	int nTemp;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		if(s_nSameCaseCount==0)
		{
			msg2user("SYS: ParentSeq_ModA_Complex_Cmds START"); //parent seq
			log2ui(sPrintSeq+"check server lock");
			s_nCount =0;
		}

		if(RP(IP::CS_ModA)==CS::CS_Unlock)
		{
			log2ui(sPrintSeq+"lock server");
			WP(IP::CS_ModA,CS::CS_OK);
			s_nSeq_Now = cas::ModA_Cmd_1;
		}
		break;


	case cas::Seq_Dispatch:
		if (s_nCount==0)
			s_nSeq_Now = cas::Turn_1;
		else if (s_nCount==1)
			s_nSeq_Now = cas::Turn_2;
		else if (s_nCount==2)
			s_nSeq_Now = cas::Turn_3;
		else if (s_nCount==3)
			s_nSeq_Now = cas::Turn_4;
		break;

	case cas::ModA_Cmd_1:
		if(s_nCount==4)
		{
			s_nSeq_Now = Call_NG_Seq;
			//s_nSeq_Now = cas::Seq_OK;
		}
		else
		{
			if(s_nSameCaseCount==0)
			{
				if(!Send_CS_Cmd(IP::CS_ModA,CS::CS_ModA_Cmd_1))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
			else if(s_nSameCaseCount==1)
			{
				log2ui(sPrintSeq+"wait cs cmd");
			}
			else
			{
				if(RP(IP::CS_ModA)==CS::CS_OK)
				{
					s_nSeq_Now = cas::Seq_Dispatch;
				}
				else if(RP(IP::CS_ModA)==CS::CS_NG)
				{
					s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
				}
			}
		}
		break;

	case cas::Turn_1:
	case cas::Turn_2:
	case cas::Turn_3:
	case cas::Turn_4:
		s_nSeq_Now = cas::ModA_Cmd_3;
		break;

	case cas::ModA_Cmd_3:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModA,CS::CS_ModA_Cmd_3))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else if(s_nSameCaseCount==1)
		{
			log2ui(sPrintSeq+"wait cs cmd");
		}
		else
		{
			if(RP(IP::CS_ModA)==CS::CS_OK)
			{
				s_nSeq_Now = cas::ModA_Cmd_1;
				s_nCount++;
			}
			else if(RP(IP::CS_ModA)==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

	case cas::Call_NG_Seq:
		nTemp = SubSeq_NG(cas::Seq_Start);
		if(nTemp ==cas::Seq_OK)
		{
			s_nSeq_Now = cas::Call_Seq_b2;
		}
		else if(nTemp == cas::Seq_NNNNNNNNGGGGGGGG)
		{
			s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		break;

	case cas::Seq_OK:
		//---------------
		WP(IP::CS_ModA,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModA_Complex_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModA_Complex_Cmds DONE");  //parent seq
		//---------------
		break;


	case cas::Seq_NNNNNNNNGGGGGGGG:
		//---------------
		WP(IP::CS_ModA,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModA_Complex_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModA_Complex_Cmds FAIL");  //parent seq
		//---------------
		break;
	}
}
//--------------------------------------------------------------------
void ParentSeq_ModB_Complex_Cmds(int nSeq_External)
{
	string sPrintSeq="ParentSeq_ModB_Complex_Cmds-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;
	//----------------
	static int s_nCount;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		if(s_nSameCaseCount==0)
		{
			msg2user("SYS: ParentSeq_ModB_Complex_Cmds START"); //parent seq
			log2ui(sPrintSeq+"check server lock");
			s_nCount =0;
		}
		else
		{
			if(RP(IP::CS_ModB)==CS::CS_Unlock)
			{
				log2ui(sPrintSeq+"lock server");
				WP(IP::CS_ModB,CS::CS_OK);
				s_nSeq_Now = cas::ModB_Cmd_1;
			}
		}
		break;

	case cas::Seq_Dispatch:
		if (s_nCount==0)
			s_nSeq_Now = cas::Turn_1;
		else if (s_nCount==1)
			s_nSeq_Now = cas::Turn_2;
		else if (s_nCount==2)
			s_nSeq_Now = cas::Turn_3;
		else if (s_nCount==3)
			s_nSeq_Now = cas::Turn_4;
		break;

	case cas::ModB_Cmd_1:
		if(s_nCount==4)
		{
			s_nSeq_Now = cas::Seq_OK;
		}
		else
		{
			if(s_nSameCaseCount==0)
			{
				if(!Send_CS_Cmd(IP::CS_ModB,CS::CS_ModB_Cmd_1))
					s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
			else if(s_nSameCaseCount==1)
			{
				log2ui(sPrintSeq+"wait cs cmd");
			}
			else
			{
				if(RP(IP::CS_ModB)==CS::CS_OK)
				{
					s_nSeq_Now = cas::Seq_Dispatch;
				}
				else if(RP(IP::CS_ModB)==CS::CS_NG)
				{
					s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
				}
			}
		}
		break;

	case cas::Turn_1:
		s_nSeq_Now = cas::ModB_Cmd_3;
		break;

	case cas::Turn_2:
		s_nSeq_Now = cas::ModB_Cmd_3;
		break;

	case cas::Turn_3:
		s_nSeq_Now = cas::ModB_Cmd_3;
		break;

	case cas::Turn_4:
		s_nSeq_Now = cas::ModB_Cmd_3;
		break;

	case cas::ModB_Cmd_3:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModB,CS::CS_ModB_Cmd_3))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else if(s_nSameCaseCount==1)
		{
			log2ui(sPrintSeq+"wait cs cmd");
		}
		else
		{
			if(RP(IP::CS_ModB)==CS::CS_OK)
			{
				s_nSeq_Now = cas::ModB_Cmd_1;
				s_nCount++;
			}
			else if(RP(IP::CS_ModB)==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

	case cas::Seq_OK:
		//---------------
		WP(IP::CS_ModB,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModB_Complex_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModB_Complex_Cmds DONE");  //parent seq
		//---------------
		break;

	case cas::Seq_NNNNNNNNGGGGGGGG:
		//---------------
		WP(IP::CS_ModB,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModB_Complex_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModB_Complex_Cmds FAIL");  //parent seq
		//---------------
		break;
	}
}
//--------------------------------------------------------------------
void ParentSeq_ModB_Simple_Cmds(int nSeq_External)
{
	string sPrintSeq="ParentSeq_ModB_Simple_Cmds-----------";
	static int s_nSameCaseCount;
	int nSeq_Temp = 0;
	static int s_nSeq_Pre;
	static int s_nSeq_Now;
	//----------------
	static int s_nCount;

	CaseChecker(
		sPrintSeq,
		s_nSameCaseCount,
		nSeq_Temp,
		s_nSeq_Pre,
		nSeq_External,
		(int)cas::Seq_Start,
		s_nSeq_Now,
		(int)cas::Seq_Reject
		);

	switch(nSeq_Temp)
	{
	case cas::Seq_Reject:
		break;

	case cas::Seq_Start:
		if(s_nSameCaseCount==0)
		{
			msg2user("SYS: ParentSeq_ModB_Simple_Cmds START"); //parent seq
			log2ui(sPrintSeq+"check server lock");
		}
		else
		{
			if(RP(IP::CS_ModB)==CS::CS_Unlock)
			{
				log2ui(sPrintSeq+"lock server");
				WP(IP::CS_ModB,CS::CS_OK);
				s_nSeq_Now = cas::ModB_Cmd_1;
			}
		}
		break;

	case cas::ModB_Cmd_1:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModB,CS::CS_ModB_Cmd_1))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else if(s_nSameCaseCount==1)
		{
			log2ui(sPrintSeq+"wait cs cmd");
		}
		else
		{
			int nTemp = RP(IP::CS_ModB);
			if(nTemp==CS::CS_OK)
			{
				s_nSeq_Now = cas::ModB_Cmd_2;
			}
			else if(nTemp==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

	case cas::ModB_Cmd_2:
		if(s_nSameCaseCount==0)
		{
			if(!Send_CS_Cmd(IP::CS_ModB,CS::CS_ModB_Cmd_2))
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
		}
		else if(s_nSameCaseCount==1)
		{
			log2ui(sPrintSeq+"wait cs cmd");
		}
		else
		{
			int nTemp = RP(IP::CS_ModB);
			if(nTemp==CS::CS_OK)
			{
				s_nSeq_Now = cas::Seq_OK;
			}
			else if(nTemp==CS::CS_NG)
			{
				s_nSeq_Now = cas::Seq_NNNNNNNNGGGGGGGG;
			}
		}
		break;

		
	case cas::Seq_NNNNNNNNGGGGGGGG:
		//---------------
		WP(IP::CS_ModB,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModB_Simple_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModB_Simple_Cmds FAIL");  //parent seq
		//---------------
		break;
		
	case cas::Seq_OK:
		//---------------
		WP(IP::CS_ModB,CS::CS_Unlock);
		log2ui(sPrintSeq+"unlock server");
		//---------------
		s_nSeq_Now = cas::Seq_Reject;
		WP(IP::Sys_ParentSeq_ModB_Simple_Cmds,cas::Seq_Reject);
		msg2user("SYS: ParentSeq_ModB_Simple_Cmds DONE");  //parent seq
		//---------------
		break;
	}
}
//--------------------------------------------------------------------
string GetTime()
{
	string text;
	ostringstream oss;

	GetLocalTime(&m_st);

	if(m_st.wHour<10)
		oss<<0;
	oss << m_st.wHour<<":";

	if(m_st.wMinute<10)
		oss<<0;
	oss << m_st.wMinute<<":";

	if(m_st.wSecond<10)
		oss<<0;
	oss << m_st.wSecond<< ".";

	if(m_st.wMilliseconds<100)
		oss<<0;
	if(m_st.wMilliseconds<10)
		oss<<0;
	oss <<m_st.wMilliseconds;

	text+=oss.str();
	return text;
}
//--------------------------------------------------------------------
void WSP(int location,int value)
{
	SetFileAttributes(m_wtextSYS, 32 & ~FILE_ATTRIBUTE_HIDDEN);
	while(true)
	{
		if ((GetFileAttributes(m_pCShandle) & FILE_ATTRIBUTE_HIDDEN) == 0) 
		{
			//SetFileAttributes(m_wtextSYS, m_nAttr | FILE_ATTRIBUTE_HIDDEN); 
			//only one between SYS and UI has to set(disable SYS for single thread performance)
			continue;
		}

		m_WIP = _fsopen(m_sStaticPoolPath, "rb+",_SH_DENYWR);
		fseek(m_WIP, (location) * 4/*=int size*/, SEEK_SET);
		fwrite(&value, 4/*=int size*/, 1, m_WIP); 
		fclose(m_WIP);

		SetFileAttributes(m_wtextSYS, FILE_ATTRIBUTE_HIDDEN); 
		break;
	}
	return ;
}
//--------------------------------------------------------------------
int RSP(int location)
{
	FILE *f = fopen(m_sStaticPoolPath, "rb");
	fseek(f, (location) * sizeof(int), SEEK_SET);
	fread(&m_nResultInt, sizeof(int), 1, f);
	fclose(f);

	return m_nResultInt;
}
//--------------------------------------------------------------------
bool Send_CS_Cmd(IP ip,CS Send_CS_Cmd)
{
	WP(ip,Send_CS_Cmd);
	int nIP=(int)ip;
	ostringstream oss;
	oss << nIP;

	bool flg;
	std::string filePipe = "//./pipe/ControlServerCmdPipe"+oss.str();
	std::wstring stemp = s2ws(filePipe);
	LPCWSTR result = stemp.c_str();
	LPDWORD dwWrite = NULL;

	HANDLE hFile = CreateFile(result, GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE , NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		log2ui("CreateFile failed for Named Pipe client\n:" );
		return false;
	}
	else
	{
		flg = WriteFile(hFile, &nIP, 2, dwWrite, NULL);
		if (FALSE == flg)  
		{
			log2ui("WriteFile failed for Named Pipe client\n");  
			return false;
		}
		CloseHandle(hFile);
		return true;
	}
}
//--------------------------------------------------------------------
void log2ui(string s)
{
	string text;
	text+=GetTime();
	text+=" [SYS] ";
	text+=s;

	bool flg;
	std::string file = "//./pipe/mypipe";
	std::wstring stemp = s2ws(file);
	LPCWSTR result = stemp.c_str();
	LPDWORD dwWrite = NULL;

	while(true)
	{
		HANDLE hFile = CreateFile(result, GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE , NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			//DWORD dw = GetLastError();
			//printf("CreateFile failed for Named Pipe client\n:" );
			continue;
		}
		else
		{
			flg = WriteFile(hFile, text.c_str(), text.length(), dwWrite, NULL);
			if (FALSE == flg)  
			{

				//printf("WriteFile failed for Named Pipe client\n");  
				continue;
			}
			CloseHandle(hFile);
			break;
		}
	}
}
//--------------------------------------------------------------------
void msg2user(string s)
{
	log2ui("MSG2USER"+s);
}
//--------------------------------------------------------------------
void CaseChecker(string sPrint,int &s_nSameCaseCount,int &nSeq_Temp,int &nSeq_Pre, int &nSeq_External,int nSeq_Target,int &s_nSeq_Now,int Seq_OK1)
{
	nSeq_Temp = s_nSeq_Now ;
	if(nSeq_External==nSeq_Target)
	{
		if(s_nSeq_Now==Seq_OK1 )
		{
			nSeq_Temp = nSeq_External;
		}
	}


	if(nSeq_Pre != nSeq_Temp)
	{
		s_nSameCaseCount = 0;
		log2ui(sPrint+p((cas)nSeq_Temp));
	}
	else
	{
		s_nSameCaseCount++;
	}

	nSeq_Pre = nSeq_Temp;

}
//--------------------------------------------------------------------
void CaseChecker(string sPrint,int &s_nSameCaseCount,int &nSeq_Temp,int &nSeq_Pre, int &nSeq_External,int nSeq_Target,int &s_nSeq_Now,int Seq_OK1,int Seq_OK2)
{
	nSeq_Temp = s_nSeq_Now ;
	if(nSeq_External==nSeq_Target)
	{
		if(s_nSeq_Now==Seq_OK1|| s_nSeq_Now==Seq_OK2)
		{
			nSeq_Temp = nSeq_External;
		}
	}


	if(nSeq_Pre != nSeq_Temp)
	{
		s_nSameCaseCount = 0;
		log2ui(sPrint+p((cas)nSeq_Temp));
	}
	else
	{
		s_nSameCaseCount++;
	}
	nSeq_Pre = nSeq_Temp;
}
//--------------------------------------------------------------------