#pragma once

#include <Windows.h>
#include <fstream>
#include <string>
#include <atlstr.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <random>
#include <time.h>
#include "Enum.h"
#include <cstring>
using namespace std;

static char m_sRootPath[] = "D:\\ControlServer\\";
static char m_sUIPath[] =   "D:\\ControlServer\\Query_Static_Pool_UI_hanle";
static char m_sSYSPath[] =   "D:\\ControlServer\\Query_Static_Pool_SYS_hanle";
static char m_sStaticPoolPath[] =   "D:\\ControlServer\\Static_Pool";
static wchar_t m_wtextSYS[100];
static wchar_t m_wtextUI[100];

static int m_nCount;
static int m_nAttr;
static int m_nResultInt;
static SYSTEMTIME m_st;

LPWSTR m_pCShandle;
FILE *m_WIP;
HANDLE m_handle;
struct MemoryPoolStruc {int value[IP::IntegerDataPoolMaxBoundary];};
struct MemoryPoolStruc* m_pMemPool;

void SimulateMultiThread();
void log2ui(string s);
void msg2user(string s);
bool Send_CS_Cmd(IP csip,CS Send_CS_Cmd);
string GetTime();

int M_Sequence_b2(int nSeq_State);
int M_Sequence_b1(int nSeq_State);
int M_Sequence_B(int nSeq_State);
int M_Sequence_A(int nSeq_State);
int M_Sequence_NG(int nSeq_State);

void M_Module_A_Complex_Cmds(int s_nSeq_Now);
void M_Module_A_Simple_Cmds(int s_nSeq_Now);
void M_Module_B_Complex_Cmds(int s_nSeq_Now);
void M_Module_B_Simple_Cmds(int s_nSeq_Now);

void WSP(int location,int value);
int RSP(int location);
void WP(int location,int value)
{
	m_pMemPool->value[location] = value;
}
int RP(int location)
{
	return  m_pMemPool->value[location];
}

void CaseChecker(string sPrint,int &s_nSameCaseCount,int &nSeq_Temp,int &nSeq_Pre,  int &nSeq_Outside,int nSeq_Target,int &s_nSeq_Now,int Seq_OK1);
void CaseChecker(string sPrint,int &s_nSameCaseCount,int &nSeq_Temp,int &nSeq_Pre,  int &nSeq_Outside,int nSeq_Target,int &s_nSeq_Now,int Seq_OK1,int Seq_OK2);
void CaseChecker(string sPrint,int &s_nSameCaseCount,int &nSeq_Temp,int &nSeq_Pre,  int &nSeq_Outside,int nSeq_Target,int &s_nSeq_Now,int Seq_OK1,int Seq_OK2,int Seq_OK3);
void CaseChecker(string sPrint,int &s_nSameCaseCount,int &nSeq_Temp,int &nSeq_Pre,  int &nSeq_Outside,int nSeq_Target,int &s_nSeq_Now,int Seq_OK1,int Seq_OK2,int Seq_OK3,int Seq_OK4);

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}