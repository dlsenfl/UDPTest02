//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxTextEdit"
#pragma link "dxSkinBlack"
#pragma link "dxSkinBlue"
#pragma link "dxSkinBlueprint"
#pragma link "dxSkinCaramel"
#pragma link "dxSkinCoffee"
#pragma link "dxSkinDarkRoom"
#pragma link "dxSkinDarkSide"
#pragma link "dxSkinDevExpressDarkStyle"
#pragma link "dxSkinDevExpressStyle"
#pragma link "dxSkinFoggy"
#pragma link "dxSkinGlassOceans"
#pragma link "dxSkinHighContrast"
#pragma link "dxSkiniMaginary"
#pragma link "dxSkinLilian"
#pragma link "dxSkinLiquidSky"
#pragma link "dxSkinLondonLiquidSky"
#pragma link "dxSkinMcSkin"
#pragma link "dxSkinMetropolis"
#pragma link "dxSkinMetropolisDark"
#pragma link "dxSkinMoneyTwins"
#pragma link "dxSkinOffice2007Black"
#pragma link "dxSkinOffice2007Blue"
#pragma link "dxSkinOffice2007Green"
#pragma link "dxSkinOffice2007Pink"
#pragma link "dxSkinOffice2007Silver"
#pragma link "dxSkinOffice2010Black"
#pragma link "dxSkinOffice2010Blue"
#pragma link "dxSkinOffice2010Silver"
#pragma link "dxSkinOffice2013DarkGray"
#pragma link "dxSkinOffice2013LightGray"
#pragma link "dxSkinOffice2013White"
#pragma link "dxSkinPumpkin"
#pragma link "dxSkinsCore"
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSevenClassic"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSharpPlus"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinTheAsphaltWorld"
#pragma link "dxSkinValentine"
#pragma link "dxSkinVisualStudio2013Blue"
#pragma link "dxSkinVisualStudio2013Dark"
#pragma link "dxSkinVisualStudio2013Light"
#pragma link "dxSkinVS2010"
#pragma link "dxSkinWhiteprint"
#pragma link "dxSkinXmas2008Blue"
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
{	if(!IdUDPServer1->Active){

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
	//======= OpCode ����=======
	int iOpCode = 0;
	UnicodeString sTemp;
	UnicodeString sTemp2;
	sTemp = rdOpCodeNo->Items->Strings[rdOpCodeNo->ItemIndex].SubString(0, 2);
	iOpCode = StrToInt(sTemp);
	//======= �޸� �ʱ�ȭ=======
	ZeroMemory(byBuf, sizeof(byBuf));
	ZeroMemory(&stHeader, sizeof(stHeader));
	ZeroMemory(&stTail, sizeof(stTail));

	stHeader.bySTX1   = 0x10;
	stHeader.bySTX2   = 0x02;
//	stHeader.byOpCode = 0x06;
	stHeader.byOpCode = iOpCode;
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
	BytesToRaw(AData, byBuf, sizeof(byBuf));     // AData�� AData.Length ���̸�ŭ byBuf�� �Է�.
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


	int iIndex;
	ZeroMemory(&stHeader, sizeof(stHeader));
	CopyMemory(&stHeader, byBuf, sizeof(stHeader));
	iIndex = sizeof(stHeader);

//======= OpCode������ ������ ó��=======
	if(stHeader.byOpCode == 0x01){
//		for(int i=0; i<AData/1024 +1; i++){
//		}
	}else if(stHeader.byOpCode == 0x02){
	}else if(stHeader.byOpCode == 0x03){
	}else if(stHeader.byOpCode == 0x04){
	}else if(stHeader.byOpCode == 0x05){
		if(stHeader.wDataLen > 0){
			mmShow->Lines->Add("������� ���");
			iIndex += stHeader.wDataLen + sizeof(stTail);
			UnicodeString sData = "";
			UnicodeString sTemp;

			for(int i=0; i<iIndex; i++){
				sData += sTemp.sprintf(L"%02X ", byBuf[i]);
			}
			mmShow->Lines->Add(sData);
			stHeader.wDataLen = 0;
			ZeroMemory(byBuf, sizeof(byBuf));
			CopyMemory(byBuf, &stHeader, sizeof(stHeader));
			IdUDPServer1->SendBuffer(sHostIP, usHostPort,RawToBytes(byBuf, sizeof(byBuf)));
			return;
		}else{
			mmShow->Lines->Add("ACK");    // ��������
			return;
		}


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
			stHeaderStore.byOpCode = 0x06;
			stHeaderStore.wDataLen = sizeof(stData06);
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
			stHeaderStore.byOpCode = 0x07;
			stHeaderStore.wDataLen = sizeof(stData07);
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

void __fastcall TForm2::btCtrlClick(TObject *Sender)
{


//	UnicodeString sRdTest;
//	for(int i=0; i<rdCtrlData->Items->Count; i++){
//		sRdTest = rdCtrlData->Items->Strings[i];
//		ShowMessage(sRdTest);
//	}
//
//
//	return;

	BYTE byBuf[1024];
	TstHeader stHeader;
	TstTail	  stTail;
	int 	  iIndex;

	ZeroMemory(byBuf, sizeof(byBuf));
	ZeroMemory(&stHeader, sizeof(stHeader));
	ZeroMemory(&stTail, sizeof(stTail));

	stHeader.bySTX1   = 0x10;
	stHeader.bySTX2   = 0x02;
	stHeader.byOpCode = 0x05;


	TstData05	stData05;
	TstData05D1 stData05D1;
	TstData05D2 stData05D2;
	TstData05D3 stData05D3;
	TstData05D4 stData05D4;
	ZeroMemory(&stData05, sizeof(stData05));
	AnsiString sTime;
	switch(rdCtrlData->ItemIndex){		//�����ڵ忡 ���� ������͸� ����
		case  0:		//������ �����������( 0: ����, 1:����, 2:�ڵ�)
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);		// �����ڵ�(1BYTE) + �������(nBYTE)
			stData05.byCtrlCode = 0x30;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case  1:		//����� ����Ʈ
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x31;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case  2:		//��Žõ� ȹ��(0x01~0x09)
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x32;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case  3:		//����� �ð���Ʈ(�ð����� ������ ���)
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D4);
			stData05.byCtrlCode = 0x33;
			ZeroMemory(&stData05D4, sizeof(stData05D4));
//			sTime = edData->Text;
			sTime = Now().FormatString("yyyymmddhhnnss");
			CopyMemory(&stData05D4, sTime.c_str(), sizeof(stData05D4));
			break;
		case  4:	//��ð�(VMS��ð� ����)
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D3);
			stData05.byCtrlCode = 0x34;
			ZeroMemory(&stData05D3, sizeof(stData05D3));
			sTime = edData->Text;
			CopyMemory(&stData05D3, sTime.c_str(), sizeof(stData05D3));
			break;
		case  5:
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x35;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case  6:
			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x36;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case  7:
			// , �� �����ڷ� (���+���) �� ������ ����Ʈ ������ �Է�.
			TStringList *pTemp;
			pTemp = new TStringList();
			pTemp->CommaText = edData->Text;

			stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D2);
			stData05.byCtrlCode = 0x37;
			ZeroMemory(&stData05D2, sizeof(stData05D2));
			if(StrToInt(pTemp->Strings[0]) == 0){      // ����(0x00)�� ���
				for(int i=0; i<pTemp->Count; i++){
					stData05D2.byCtrlData[i] = StrToInt(pTemp->Strings[i]);
				}
			}else{                                     // �ڵ�(0x01)�� ���
				stData05D2.byCtrlData[0] = 1;
				stData05D2.byCtrlData[pTemp->Count-1] = 0;
			}
			delete pTemp;
			break;
		case  8:
            stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x36;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case  9:
            stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x36;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case 10:
            stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x36;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		case 11:
            stHeader.wDataLen = sizeof(stData05) + sizeof(stData05D1);
			stData05.byCtrlCode = 0x36;
			ZeroMemory(&stData05D1, sizeof(stData05D1));
			stData05D1.byCtrlData = StrToInt(edData->Text);
			break;
		default :
			ShowMessage("Error");
			break;
	}
	stTail.byETX1	= 0x10;
	stTail.byETX2	= 0x03;

	CopyMemory(byBuf, &stHeader, sizeof(stHeader));
	iIndex = sizeof(stHeader);


	switch(rdCtrlData->ItemIndex){
		case  0 :                    //
		case  1 :                    //
		case  2 :                    // case 0, 1, 2�� ��� ���� ���� �ڵ� ����.
		case  5 :
		case  6 :
        case  8 :
        case  9 :
        case 10 :
        case 11 :
			CopyMemory(byBuf + iIndex, &stData05, sizeof(stData05));		// �����ڵ� �κ� ����
			iIndex += sizeof(stData05);
			CopyMemory(byBuf + iIndex, &stData05D1, sizeof(stData05D1));    // ������� �κ� ����
			iIndex += sizeof(stData05D1);
			break;
		case  3 :
			CopyMemory(byBuf+iIndex, &stData05, sizeof(stData05));
			iIndex += sizeof(stData05);
			CopyMemory(byBuf+iIndex, &stData05D4, sizeof(stData05D4));
			iIndex += sizeof(stData05D4);
			break;
		case  4 :
			CopyMemory(byBuf+iIndex, &stData05, sizeof(stData05));
			iIndex += sizeof(stData05);
			CopyMemory(byBuf+iIndex, &stData05D3, sizeof(stData05D3));
			iIndex += sizeof(stData05D3);
			break;
		case  7 :
			CopyMemory(byBuf+iIndex, &stData05, sizeof(stData05));
			iIndex += sizeof(stData05);
			CopyMemory(byBuf+iIndex, &stData05D2, sizeof(stData05D2));
			iIndex += sizeof(stData05D2);
			break;





	}

	CopyMemory(byBuf+iIndex, &stTail, sizeof(stTail));
	iIndex += sizeof(stTail);

//	�׽�Ʈ ���
//	if(iIndex == sizeof(stHeader)+stHeader.wDataLen+sizeof(stTail)){
//		UnicodeString sData = "";
//		UnicodeString sTemp;
//
//		for(int i=0; i<iIndex; i++){
//			sData += sTemp.sprintf(L"%02X ", byBuf[i]);
//		}
//		mmShow->Lines->Add(sData);
//	}
	if(iIndex == sizeof(stHeader)+stHeader.wDataLen+sizeof(stTail)){
		 IdUDPServer1->SendBuffer(sHostIP, usHostPort, RawToBytes(&byBuf, sizeof(byBuf)));
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm2::edDataKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		btCtrlClick(NULL);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::btFormClick(TObject *Sender)
{
	BYTE *byBuf = new BYTE();
	TstHeader stHeader;
	TstTail	  stTail;
	int 	  iIndex;

//	ZeroMemory(byBuf, sizeof(byBuf));
	ZeroMemory(&stHeader, sizeof(stHeader));
	ZeroMemory(&stTail, sizeof(stTail));

	stHeader.bySTX1   = 0x10;
	stHeader.bySTX2   = 0x02;
	stHeader.byOpCode = 0x01;

	TstData01 stData01;
//	TStringList * pTemp;
//	pTemp = new TStringList();
	// ======= ����� �ʱ�ȭ =======
//	ZeroMemory(stData01, sizeof(stData01));
	stData01.stFormHeader.byFormNo 		 = 0x00;
	stData01.stFormHeader.byAllFormCount = 0x01;
	stData01.stFormHeader.byDisplayTime  = 0x02;
	stData01.stFormHeader.byDisplayType  = 0x03;
	stData01.stFormHeader.byBackColor 	 = 0x04;
	stData01.stFormHeader.byObjectCount  = 0x01;

	stData01.stObjectHeader; //= new TstObjectHeader();
	stData01.stObjectHeader[0].byObjectKind = 0x00;
	stData01.stObjectHeader[0].byObjectSize[0] = 0x12;
	stData01.stObjectHeader[0].byObjectSize[1] = 0x12;
	stData01.stObjectHeader[0].byBlinkOnOff = 0x00;
	stData01.stObjectHeader[0].byXposition[0] = 0x01;
	stData01.stObjectHeader[0].byXposition[1] = 0x01;
	stData01.stObjectHeader[0].byYposition[0] = 0x02;
	stData01.stObjectHeader[0].byYposition[1] = 0x02;
	stData01.stObjectHeader[0].byStringBackCol = 0x03;
	stData01.stObjectHeader[0].stObjectString.byFontColor = 0x03;
	stData01.stObjectHeader[0].stObjectString.byFontSize  = 0x11;
	stData01.stObjectHeader[0].stObjectString.byFontKind  = 0x20;
	stData01.stObjectHeader[0].stObjectString.byFontBold  = 0x00;
	stData01.stObjectHeader[0].stObjectString.byEtc		  = 0x00;
	stData01.stObjectHeader[0].stObjectString.byString = "�׽�Ʈ�Դϴ�.�׽�Ʈ�Դϴ�.�׽�Ʈ�Դϴ�.�׽�Ʈ�Դϴ�.�׽�Ʈ�Դϴ�.";

	stTail.byETX1	= 0x10;
	stTail.byETX2	= 0x03;

	CopyMemory(byBuf, &stHeader, sizeof(stHeader));
	iIndex = sizeof(stHeader);
	CopyMemory(byBuf+iIndex, &stData01, sizeof(stData01));
	iIndex = sizeof(stData01);
	CopyMemory(byBuf+iIndex, &stTail, 	 sizeof(stTail));
	iIndex = sizeof(stTail);

	IdUDPServer1->SendBuffer(sHostIP, usHostPort, RawToBytes(&stData01, sizeof(stData01)));
}
//---------------------------------------------------------------------------

