



#ifndef __Enum_H__
#define __Enum_H__ 1
#include "..\Enum\Enum.cs"






inline const char* p(cas v)
{
    switch (v)
    {
        case cas::Seq_Reject:  return "cas::Seq_Reject";
        case cas::Seq_OK:  return "cas::Seq_OK";
        case cas::Seq_NNNNNNNNGGGGGGGG:  return "cas::Seq_NNNNNNNNGGGGGGGG";
        case cas::Seq_Start:  return "cas::Seq_Start";
        case cas::Seq_Dispatch:  return "cas::Seq_Dispatch";
        case cas::Call_NG_Seq:  return "cas::Call_NG_Seq";
        case cas::Wait_1:  return "cas::Wait_1";
        case cas::Wait_2:  return "cas::Wait_2";
        case cas::Wait_3:  return "cas::Wait_3";
        case cas::Call_Module_A_Cmd_5:  return "cas::Call_Module_A_Cmd_5";
        case cas::Call_Seq_B:  return "cas::Call_Seq_B";
        case cas::Call_Seq_b1:  return "cas::Call_Seq_b1";
        case cas::Call_Seq_b2:  return "cas::Call_Seq_b2";
        case cas::Call_Seq_A:  return "cas::Call_Seq_A";
        case cas::Module_A_Cmd_1:  return "cas::Module_A_Cmd_1";
        case cas::Module_A_Cmd_2:  return "cas::Module_A_Cmd_2";
        case cas::Module_A_Cmd_3:  return "cas::Module_A_Cmd_3";
        case cas::Turn_1:  return "cas::Turn_1";
        case cas::Turn_2:  return "cas::Turn_2";
        case cas::Turn_3:  return "cas::Turn_3";
        case cas::Turn_4:  return "cas::Turn_4";
        case cas::Module_B_Cmd_1:  return "cas::Module_B_Cmd_1";
        case cas::Module_B_Cmd_2:  return "cas::Module_B_Cmd_2";
        case cas::Module_B_Cmd_3:  return "cas::Module_B_Cmd_3";
		default:
			return "ERROR: WRONG CASE IN Enum.h";
    }
}

inline const char* p(CS v)
{
    switch (v)
    {
        case CS::CS_Unlock:  return "CS::CS_Unlock";
        case CS::CS_OK:  return "CS::CS_OK";
        case CS::CS_NG:  return "CS::CS_NG";
        case CS::CS_Lock:  return "CS::CS_Lock";
        case CS::CS_Basic_State_End:  return "CS::CS_Basic_State_End";
        case CS::CS_Module_A_Cmd_1:  return "CS::CS_Module_A_Cmd_1";
        case CS::CS_Module_A_Cmd_2:  return "CS::CS_Module_A_Cmd_2";
        case CS::CS_Module_A_Cmd_3:  return "CS::CS_Module_A_Cmd_3";
        case CS::CS_Module_A_Cmd_4:  return "CS::CS_Module_A_Cmd_4";
        case CS::CS_Module_A_Cmd_5:  return "CS::CS_Module_A_Cmd_5";
        case CS::CS_Module_A_Cmd_6:  return "CS::CS_Module_A_Cmd_6";
        case CS::CS_Module_B_Cmd_1:  return "CS::CS_Module_B_Cmd_1";
        case CS::CS_Module_B_Cmd_2:  return "CS::CS_Module_B_Cmd_2";
        case CS::CS_Module_B_Cmd_3:  return "CS::CS_Module_B_Cmd_3";
        case CS::CS_Module_B_Cmd_4:  return "CS::CS_Module_B_Cmd_4";
        case CS::CS_Module_B_Cmd_5:  return "CS::CS_Module_B_Cmd_5";
        case CS::CS_Module_B_Cmd_6:  return "CS::CS_Module_B_Cmd_6";
        case CS::CS_Basic_State_Start:  return "CS::CS_Basic_State_Start";
		default:
			return "ERROR: WRONG CASE IN Enum.h";
    }
}

inline const char* p(IP v)
{
    switch (v)
    {
        case IP::IntegerDataPoolMinBoundary:  return "IP::IntegerDataPoolMinBoundary";
        case IP::ControlServer_Start:  return "IP::ControlServer_Start";
        case IP::CS_Module_A:  return "IP::CS_Module_A";
        case IP::CS_Module_A_AutoUnlock:  return "IP::CS_Module_A_AutoUnlock";
        case IP::CS_Module_B:  return "IP::CS_Module_B";
        case IP::CS_Module_B_AutoUnlock:  return "IP::CS_Module_B_AutoUnlock";
        case IP::ControlServer_End:  return "IP::ControlServer_End";
        case IP::Sys_Method_Start:  return "IP::Sys_Method_Start";
        case IP::Sys_M_Module_A_Simple_Cmds:  return "IP::Sys_M_Module_A_Simple_Cmds";
        case IP::Sys_M_Module_A_Complex_Cmds:  return "IP::Sys_M_Module_A_Complex_Cmds";
        case IP::Sys_M_Module_B_Simple_Cmds:  return "IP::Sys_M_Module_B_Simple_Cmds";
        case IP::Sys_M_Module_B_Complex_Cmds:  return "IP::Sys_M_Module_B_Complex_Cmds";
        case IP::Sys_Method_End:  return "IP::Sys_Method_End";
        case IP::IntegerDataPoolMaxBoundary:  return "IP::IntegerDataPoolMaxBoundary";
        case IP::INTEGER_DATA_POOL_SIZE:  return "IP::INTEGER_DATA_POOL_SIZE";
		default:
			return "ERROR: WRONG CASE IN Enum.h";
    }
}

#endif