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

		sHostIP    	 = edHostIP->Text;                                       // �����͸� ���޹��� ����Ip
		usHostPort   = StrToInt(edHostPort->Text);                           // �����͸� ���޹��� ����Port
		usClientPort = StrToInt(edClientPort->Text);                         // �����͸� �����ϴ� Ŭ���̾�Ʈ Port
		IdUDPServer1->DefaultPort = usClientPort;

		ShowMessage("HostPort: "+edHostPort->Text+
					"\nHostIP "+edHostIP->Text+
					"ClientPort: "+IntToStr(IdUDPServer1->DefaultPort));

		IdUDPServer1->Active = true;                                         // Active = true; �� �������� ��������� ���� ������ ������ ����Ȼ��·� ��Ž���.
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btRequestClick(TObject *Sender)
{
	BYTE byBuf[1024];
	TstHeader stHeader;
	TstTail stTail;
	int iIndex  = 0;
	//======= �޸� �ʱ�ȭ=======
	ZeroMemory(byBuf, sizeof(byBuf));
	ZeroMemory(&stHeader, sizeof(stHeader));
	ZeroMemory(&stTail, sizeof(stTail));

	stHeader.bySTX1   = 0x10;
	stHeader.bySTX2   = 0x02;
	stHeader.byOpCode = 0x06;
	stHeader.wDataLen = 0x00;


	stTail.byETX1	  = 0x10;
	stTail.byETX2	  = 0x03;
	//byBuf �迭�� �޸� �ʱ�ȭ�� �������ü�Է�.
	CopyMemory(byBuf, &stHeader, sizeof(stHeader));
	iIndex = sizeof(stHeader);
	// byOpCode�� ���� �����ͺκ� �ʱ�ȭ �� byBuf�迭�� ����� �Էµ� �κ� �ڿ� �Է�.
	switch(stHeader.byOpCode){

		case 0x06:
			TstData06 stData06;
			ZeroMemory(&stData06, sizeof(stData06));
			CopyMemory(byBuf+iIndex, &stData06, sizeof(stData06));
			iIndex += sizeof(stData06);
			break;
		case 0x07:
			TstData07 stData07;
			ZeroMemory(&stData07, sizeof(stData07));
			CopyMemory(byBuf+iIndex, &stData07, sizeof(stData07));
			iIndex += sizeof(stData07);
			break;
		default :
			ShowMessage("None of CodeNo");
			break;
	}
	// ���ϱ���ü �ʱ�ȭ �� byBuf �迭 ������ ������ �Է�.
	CopyMemory(byBuf+iIndex, &stTail, sizeof(stTail));
	iIndex += sizeof(stTail);

	// byBuf �迭�� ������ �����ϱ����� �κ�
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
		  TIdSocketHandle *ABinding)		// UDP�����͸������� �����ϴ� �Լ�
{
	BYTE byBuf[1024];
	ZeroMemory(byBuf, sizeof(byBuf));
	BytesToRaw(AData, byBuf, AData.Length);     // AData�� AData.Length ���̸�ŭ byBuf�� �Է�.
	UnicodeString sTemp;

	TstHeader stHeader;
	TstHeader stHeaderStore;
	TstTail	  stTail;
	TstData06 stData06;
	TstData07 stData07;
	// ��û�� �����ϴ� ����ü��� �ʱ�ȭ
	ZeroMemory(&stHeaderStore, sizeof(stHeaderStore));
	stHeaderStore.bySTX1   = 0x10;
	stHeaderStore.bySTX2   = 0x02;
	stHeaderStore.byOpCode = 0x06;
	stHeaderStore.wDataLen = 0x0C;

	int iIndex;
	ZeroMemory(&stHeader, sizeof(stHeader));
	CopyMemory(&stHeader, byBuf, sizeof(stHeader));
	iIndex = sizeof(stHeader);
	if(stHeader.byOpCode == 0x05){
	//

	}else if(stHeader.byOpCode == 0x06){
		if(stHeader.wDataLen > 0){    // ������� ������(byBuf)�� ������ (����)���, ������, ���Ϻκп� ����
			if(stHeader.wDataLen != sizeof(stData06)) return;
			ZeroMemory(&stData06, sizeof(stData06));
			CopyMemory(&stData06, byBuf+iIndex, sizeof(stData06));
			iIndex += sizeof(stData06);
			ZeroMemory(&stTail, sizeof(stTail));
			CopyMemory(&stTail, byBuf+iIndex, sizeof(stTail));
			iIndex += sizeof(stTail);
		}else{
			mmShow->Lines->Add("��û����");
			CopyMemory(byBuf, &stHeaderStore, sizeof(stHeaderStore)); //wDataLen ���� 0xf ??? , ����Ǵ� 16�������� 0x0c
//			ZeroMemory(&stData06, sizeof(stData06));
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
			mmShow->Lines->Add("��û����");
			CopyMemory(byBuf, &stHeaderStore, sizeof(stHeaderStore));
//			ZeroMemory(&stData07, sizeof(stData07));
			CopyMemory(byBuf+iIndex, &stData07, sizeof(stData07));
			IdUDPServer1->SendBuffer(sHostIP, usHostPort, RawToBytes(&byBuf, sizeof(byBuf)));
		}
	}else if(stHeader.byOpCode == 0x08){
	}else if(stHeader.byOpCode == 0x09){
	}else if(stHeader.byOpCode == 0x0A){
	}else if(stHeader.byOpCode == 0x0B){
	}


	// ��û�� ������� �����͸� ���.
	if(iIndex == sizeof(stHeader)+stHeader.wDataLen+sizeof(stTail)){
		mmShow->Lines->Add("���䵥���� ���");
		UnicodeString sData = "";
		// byBuf�� ����Ǿ��ִ� �����͸� 16���� ǥ���� UnicodeString���� ���.
		for(int i=0; i<iIndex; i++){
			sData +=sTemp.sprintf(L"%02X ", byBuf[i]);  // 0���ٿ��� (0����)2�ڸ����� 16���� ���
		}
		mmShow->Lines->Add(sData);

	}
}
//---------------------------------------------------------------------------

