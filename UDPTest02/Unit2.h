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
//---------------------------------------------------------------------------
struct TstHeader
{
	BYTE bySTX1;
	BYTE bySTX2;
	WORD wVMSID;
	BYTE byOpCode;
	BYTE bySFNo;
	BYTE byAFNo;
	WORD wDataLen;
};


struct TstTail
{
	WORD wCRC;
	BYTE byETX1;
	BYTE byETX2;
};


struct TstData06						// State
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
	TButton *btReply;
	TButton *btStart;
	TEdit *edClientPort;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edHostPort;
	TEdit *edHostIP;
	TLabel *Label3;
	void __fastcall btStartClick(TObject *Sender);
	void __fastcall btRequestClick(TObject *Sender);
	void __fastcall edClientPortKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
          TIdSocketHandle *ABinding);
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
