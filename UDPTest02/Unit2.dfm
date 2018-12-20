object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 596
  ClientWidth = 835
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 334
    Top = 82
    Width = 60
    Height = 16
    Alignment = taRightJustify
    Caption = 'ClientPort:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 341
    Top = 44
    Width = 53
    Height = 16
    Alignment = taRightJustify
    BiDiMode = bdLeftToRight
    Caption = 'HostPort:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBiDiMode = False
    ParentFont = False
  end
  object Label3: TLabel
    Left = 341
    Top = 17
    Width = 41
    Height = 16
    Alignment = taRightJustify
    BiDiMode = bdLeftToRight
    Caption = 'HostIP:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBiDiMode = False
    ParentFont = False
  end
  object mmShow: TMemo
    Left = 16
    Top = 16
    Width = 305
    Height = 545
    TabOrder = 2
  end
  object btRequest: TButton
    Left = 455
    Top = 491
    Width = 75
    Height = 25
    Caption = #50836#52397
    TabOrder = 3
    OnClick = btRequestClick
  end
  object btStart: TButton
    Left = 536
    Top = 16
    Width = 75
    Height = 25
    Caption = #49884#51089
    TabOrder = 4
    OnClick = btStartClick
  end
  object edClientPort: TEdit
    Left = 409
    Top = 81
    Width = 121
    Height = 21
    TabOrder = 1
    OnKeyPress = edClientPortKeyPress
  end
  object edHostPort: TEdit
    Left = 409
    Top = 43
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object edHostIP: TEdit
    Left = 409
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 5
    Text = '127.0.0.1'
  end
  object rdCtrlData: TRadioGroup
    Left = 567
    Top = 108
    Width = 185
    Height = 377
    Caption = '05'#51228#50612#45936#51060#53552
    Items.Strings = (
      '30 '#51204#44305#54032' '#47784#46280#51204#50896#51228#50612
      '31 '#51228#50612#44592' '#47532#49483
      '32 '#53685#49888#49884#46020' '#54925#49688
      '33 '#51228#50612#44592' '#49884#44036#49483#53944
      '34 '#50868#50689#49884#44036
      '35 '#51216#47736#49884#44036' '#51452#44592
      '36 '#46356#54260#53944' '#49884#45208#47532#50724' '#46041#51089#49884#44036
      '37 '#48157#44592#51228#50612
      '38 Fan '#51228#50612
      '39 Heater '#51228#50612
      '40 '#46020#54805#49885' '#51204#46321#51228#50612
      '41 LED '#51204#50896#51228#50612)
    TabOrder = 6
  end
  object edData: TcxTextEdit
    Left = 567
    Top = 491
    TabOrder = 7
    OnKeyPress = edDataKeyPress
    Width = 185
  end
  object btCtrl: TButton
    Left = 758
    Top = 487
    Width = 75
    Height = 25
    Caption = #51228#50612
    TabOrder = 8
    OnClick = btCtrlClick
  end
  object rdOpCodeNo: TRadioGroup
    Left = 345
    Top = 108
    Width = 185
    Height = 377
    Caption = 'OpCode'
    Items.Strings = (
      '06 '#49345#53468
      '07 '#47196#52972#49345#53468)
    TabOrder = 9
  end
  object btForm: TButton
    Left = 640
    Top = 14
    Width = 75
    Height = 27
    Caption = #54268' '#45936#51060#53552
    TabOrder = 10
    OnClick = btFormClick
  end
  object IdUDPServer1: TIdUDPServer
    Bindings = <>
    DefaultPort = 0
    OnUDPRead = IdUDPServer1UDPRead
    Left = 776
    Top = 24
  end
end
