//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
const int MAX_UDP_BUF = 1024;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm2::btStartClick(TObject *Sender)
{
	if(!IdUDPServer1->Active){

		sHostIP    	 = edHostIP->Text;
		usHostPort   = StrToInt(edHostPort->Text);
		usClientPort = StrToInt(edClientPort->Text);
		IdUDPServer1->DefaultPort = usClientPort;

		ShowMessage("HostPort: "+edHostPort->Text+
					"\nHostIP "+edHostIP->Text+
					"ClientPort: "+IntToStr(IdUDPServer1->DefaultPort));

		IdUDPServer1->Active = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btRequestClick(TObject *Sender)
{
	BYTE byBuf[1024];
	TstHeader stHeader;
	TstTail stTail;
	int iIndex  = 0;

	ZeroMemory(byBuf, sizeof(byBuf));
	ZeroMemory(&stHeader, sizeof(stHeader));
	ZeroMemory(&stTail, sizeof(stTail));

	stHeader.bySTX1   = 0x10;
	stHeader.bySTX2   = 0x02;
	stHeader.byOpCode = 0x06;
	stHeader.wDataLen = 0x00;


	stTail.byETX1	  = 0x10;
	stTail.byETX2	  = 0x03;
	CopyMemory(byBuf, &stHeader, sizeof(stHeader));
	iIndex = sizeof(stHeader);

	switch(stHeader.byOpCode){

		case 0x06:
			TstData06 stData06;
			ZeroMemory(&stData06, sizeof(stData06));
			CopyMemory(byBuf+iIndex, &stData06, sizeof(stData06));
			iIndex += sizeof(stData06);
			break;
		case 0x07:
			TstData06 stData07;
			ZeroMemory(&stData07, sizeof(stData07));
			CopyMemory(byBuf+iIndex, &stData07, sizeof(stData07));
			iIndex += sizeof(stData07);
			break;
		default :
			ShowMessage("None of CodeNo");
			break;
	}
	CopyMemory(byBuf+iIndex, &stTail, sizeof(stTail));
	iIndex += sizeof(stTail);
	TByteDynArray aBuf;
	aBuf.Length = iIndex;
	CopyMemory(&(aBuf[0]), byBuf, iIndex);
	IdUDPServer1->SendBuffer(sHostIP, usHostPort, aBuf);


//	TIdBytes aBuf;
//	BytesToRaw(aBuf, byBuf, iIndex);
//	CopyMemory(&(aBuf[0]), byBuf, iIndex);
//	aBuf.Length = iIndex;

//	IdUDPServer1->SendBuffer(sHostIP, usHostPort, RawToBytes(&byBuf, sizeof(byBuf)));
}
//---------------------------------------------------------------------------
void __fastcall TForm2::edClientPortKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		btStartClick(NULL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding)
{
	BYTE byBuf[1024];
	ZeroMemory(byBuf, sizeof(byBuf));
	BytesToRaw(AData, byBuf, AData.Length);
	UnicodeString sTemp;

	TstHeader stHeader;
	TstHeader stHeaderStore;
	TstTail	  stTail;
	TstData06 stData06;
	TstData07 stData07;

	stHeaderStore.bySTX1   = 0x10;
	stHeaderStore.bySTX2   = 0x02;
	stHeaderStore.byOpCode = 0x06;
	stHeaderStore.wDataLen = 0x0C;

	int iIndex;

	ZeroMemory(&stHeader, sizeof(stHeader));
	CopyMemory(&stHeader, byBuf, sizeof(stHeader));
	iIndex = sizeof(stHeader);

	if(stHeader.byOpCode == 0x06){
		if(stHeader.wDataLen > 0){
			if(stHeader.wDataLen != sizeof(stData06)) return;
			ZeroMemory(&stData06, sizeof(stData06));
			CopyMemory(&stData06, byBuf+iIndex, sizeof(stData06));
			iIndex += sizeof(stData06);
			ZeroMemory(&stTail, sizeof(stTail));
			CopyMemory(&stTail, byBuf+iIndex, sizeof(stTail));
			iIndex += sizeof(stTail);
		}else{
			mmShow->Lines->Add("요청받음");
			CopyMemory(byBuf, &stHeaderStore, sizeof(stHeaderStore));
			CopyMemory(byBuf+iIndex, &stData06, sizeof(stData06));
			IdUDPServer1->SendBuffer(sHostIP, usHostPort, RawToBytes(&byBuf, sizeof(byBuf)));
		}
	}else if(stHeader.byOpCode == 0x07){
		if(stHeader.wDataLen > 0){
			if(stHeader.wDataLen != sizeof(stData07)) return;
			ZeroMemory(&stData07, sizeof(stData07));
			CopyMemory(&stData07, byBuf+iIndex, sizeof(stData07));
			iIndex += sizeof(stData07);
			ZeroMemory(&stTail, sizeof(stTail));
			CopyMemory(&stTail, byBuf+iIndex, sizeof(stTail));
			iIndex += sizeof(stTail);
		}else{
			mmShow->Lines->Add("요청받음");
			CopyMemory(byBuf, &stHeaderStore, sizeof(stHeaderStore));
			CopyMemory(byBuf+iIndex, &stData07, sizeof(stData07));
			IdUDPServer1->SendBuffer(sHostIP, usHostPort, RawToBytes(&byBuf, sizeof(byBuf)));
		}
	}else if(stHeader.byOpCode == 0x09){
	}else if(stHeader.byOpCode == 0x0A){
	}else if(stHeader.byOpCode == 0x0B){
	}

	if(iIndex == sizeof(stHeader)+stHeader.wDataLen+sizeof(stTail)){
		mmShow->Lines->Add("응답데이터 출력");
//		sTemp = TEncoding::GetEncoding(1251)->GetString(byBuf);
//		sTemp =
//		mmShow->Lines->Add(sTemp);
	}
//	ZeroMemory(&stTail, sizeof(stTail));
//	CopyMemory(&stTail, byBuf+iIndex, sizeof(stTail));
//	iIndex += sizeof(stTail);

//	UnicodeString sTemp;
//	sTemp = BytesToString(AData);
//	mmShow->Lines->Add(sTemp);

}
//---------------------------------------------------------------------------

