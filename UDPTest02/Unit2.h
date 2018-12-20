//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdUDPClient.hpp>
#include "cxContainer.hpp"
#include "cxControls.hpp"
#include "cxEdit.hpp"
#include "cxGraphics.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "cxTextEdit.hpp"
#include "dxSkinBlack.hpp"
#include "dxSkinBlue.hpp"
#include "dxSkinBlueprint.hpp"
#include "dxSkinCaramel.hpp"
#include "dxSkinCoffee.hpp"
#include "dxSkinDarkRoom.hpp"
#include "dxSkinDarkSide.hpp"
#include "dxSkinDevExpressDarkStyle.hpp"
#include "dxSkinDevExpressStyle.hpp"
#include "dxSkinFoggy.hpp"
#include "dxSkinGlassOceans.hpp"
#include "dxSkinHighContrast.hpp"
#include "dxSkiniMaginary.hpp"
#include "dxSkinLilian.hpp"
#include "dxSkinLiquidSky.hpp"
#include "dxSkinLondonLiquidSky.hpp"
#include "dxSkinMcSkin.hpp"
#include "dxSkinMetropolis.hpp"
#include "dxSkinMetropolisDark.hpp"
#include "dxSkinMoneyTwins.hpp"
#include "dxSkinOffice2007Black.hpp"
#include "dxSkinOffice2007Blue.hpp"
#include "dxSkinOffice2007Green.hpp"
#include "dxSkinOffice2007Pink.hpp"
#include "dxSkinOffice2007Silver.hpp"
#include "dxSkinOffice2010Black.hpp"
#include "dxSkinOffice2010Blue.hpp"
#include "dxSkinOffice2010Silver.hpp"
#include "dxSkinOffice2013DarkGray.hpp"
#include "dxSkinOffice2013LightGray.hpp"
#include "dxSkinOffice2013White.hpp"
#include "dxSkinPumpkin.hpp"
#include "dxSkinsCore.hpp"
#include "dxSkinsDefaultPainters.hpp"
#include "dxSkinSeven.hpp"
#include "dxSkinSevenClassic.hpp"
#include "dxSkinSharp.hpp"
#include "dxSkinSharpPlus.hpp"
#include "dxSkinSilver.hpp"
#include "dxSkinSpringTime.hpp"
#include "dxSkinStardust.hpp"
#include "dxSkinSummer2008.hpp"
#include "dxSkinTheAsphaltWorld.hpp"
#include "dxSkinValentine.hpp"
#include "dxSkinVisualStudio2013Blue.hpp"
#include "dxSkinVisualStudio2013Dark.hpp"
#include "dxSkinVisualStudio2013Light.hpp"
#include "dxSkinVS2010.hpp"
#include "dxSkinWhiteprint.hpp"
#include "dxSkinXmas2008Blue.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
struct TstHeader                                 	//9바이트
{
	BYTE bySTX1;
	BYTE bySTX2;
	WORD wVMSID;
	BYTE byOpCode;
	BYTE bySFNo;
	BYTE byAFNo;
	WORD wDataLen;
};

struct TstTail                                  	 //4바이트
{
	WORD wCRC;
	BYTE byETX1;
	BYTE byETX2;
};

//---------------------------------------------------------------------------
struct TstFormHeader
{
	BYTE byFormNo;
	BYTE byAllFormCount;
	BYTE byDisplayTime;
	BYTE byDisplayType;
	BYTE byBackColor;
	BYTE byObjectCount;
};

struct TstObjectString
{
	BYTE byFontColor;
	BYTE byFontSize;
	BYTE byFontKind;
	BYTE byFontBold;
	BYTE byEtc;
	BYTE *byString;
};

struct TstObjectBitMap
{
	BYTE byBitMapWidth[2];
	BYTE byBitMapHeight[2];
	BYTE byBitMapType;
	BYTE byEtc;
	BYTE *byBitMapData;
};

struct TstObjectBitMapId
{
	BYTE byBitMapIdWidth[2];
	BYTE byBitMapIdHeight[2];
	BYTE byBitMapIdType;
	BYTE *byBitMapId;
};

struct TstObjectHeader
{
	BYTE byObjectKind;
	BYTE byObjectSize[2];
	BYTE byBlinkOnOff;
	BYTE byXposition[2];
	BYTE byYposition[2];
	BYTE byStringBackCol;
	TstObjectString stObjectString;
	TstObjectBitMap stObjectBitMap;
	TstObjectBitMapId stObjectBitMapId;
};

struct TstData01
{
	TstFormHeader stFormHeader;
	TstObjectHeader *stObjectHeader;
};

//---------------------------------------------------------------------------
struct TstData05
{
	BYTE byCtrlCode;
};

struct TstData05D1
{
	BYTE byCtrlData;
};

struct TstData05D2
{
	BYTE byCtrlData[2];
};

struct TstData05D3
{
	char byCtrlData[8];              // BYTE가 아니라 char를 쓰는이유??  : 같은 1바이트라 크게 상관X  문자열이 들어감을 나타내는 표식
};

struct TstData05D4
{
	char byCtrlData[14];
};

//---------------------------------------------------------------------------
struct TstData06						// State     //12바이트
{
	BYTE Door;							//	Open: 0x00, Close: 0x01, Unkown: 0x09
	BYTE Power;							//  On: 0x00, 	Off: 0x01
	BYTE Fan;							//  On: 0x00, 	Off: 0x01,   Unkown: 0x09
	BYTE Heater;                        //  On: 0x00, 	Off: 0x01,   Unkown: 0x09
	BYTE OuterLight;                    //  On: 0x00, 	Off: 0x01
	BYTE ShowFoam;						//  CFoam: 0x00, 	DFoam: 0x01
	BYTE RePlay;                        //  Normal: 0x00, 	RePlay: 0x01
	BYTE PowerOdd;						//	Eorror: 0x00,	Normal:	0x01,	0x02: Unknown
	BYTE ModulOdd;						//  Eorror: 0x00,	Normal:	0x01,	0x02: Unknown
	BYTE Temperature;					//  Range:0x00 ~ 0xfe(-127~127),	0xff: Unknown
	BYTE DisplayBright;                 //  백분율 표기
	BYTE Etc2;							// 	기타2
};

//---------------------------------------------------------------------------
struct TstData07                        // LocalState
{
	BYTE PowerMode;						//	Off: 0x00,  On: 0x01, Auto: 0x02
	BYTE Fan;							//  Off: 0x00, 	On: 0x01, Auto: 0x02,  Unkown: 0x09
	BYTE FanTemper;						//	Range:0x00 ~ 0x3f
	BYTE Etc1;							// 	기타1
	BYTE Heater;                        //  Off: 0x00, 	On: 0x01, Auto: 0x02,  Unkown: 0x09
	BYTE HeaterTemper;                  //	Range:0x00 ~ 0x3f
	BYTE DisplayBright;                 //  Manual: 0x00,	Auto: 0x01
	BYTE FlashCycle;					//	Range: 0x00 ~ 0x1e(0.1 ~ 3.0)
	BYTE OuterLightOperating;			//	Off: 0x00,	On: 0x01,	Auto: 0x02
	BYTE OuterLightOnBright;            //	백분율 표기
	BYTE DefaultScenarioWait;           //	Range: 0x00 ~ 0x1e(분)
	BYTE Etc2;							// 	기타2



	BYTE Year;					     	//  0x00 ~ 0x32 (년)
	BYTE Month;                         //  0x00 ~ 0x0c (월)
	BYTE Date;					     	//	0x01 ~ 0x1f (일)
	BYTE Hour;					     	//  0x00 ~ 0x17 (시)
	BYTE Minute;				     	//  0x00 ~ 0x3b (분)
	BYTE Second;                        //	0x00 ~ 0x3b (초)
};
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TMemo *mmShow;
	TButton *btRequest;
	TIdUDPServer *IdUDPServer1;
	TButton *btStart;
	TEdit *edClientPort;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edHostPort;
	TEdit *edHostIP;
	TLabel *Label3;
	TRadioGroup *rdCtrlData;
	TcxTextEdit *edData;
	TButton *btCtrl;
	TRadioGroup *rdOpCodeNo;
	TButton *btForm;
	void __fastcall btStartClick(TObject *Sender);
	void __fastcall btRequestClick(TObject *Sender);
	void __fastcall edClientPortKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding);
	void __fastcall btCtrlClick(TObject *Sender);
	void __fastcall edDataKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btFormClick(TObject *Sender);
private:	// User declarations
	UnicodeString  sHostIP;
	unsigned short usHostPort;
	unsigned short usClientPort;

public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
