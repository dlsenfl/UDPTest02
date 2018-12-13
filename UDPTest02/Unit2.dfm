object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 299
  ClientWidth = 635
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
    Height = 233
    TabOrder = 2
  end
  object btRequest: TButton
    Left = 350
    Top = 128
    Width = 75
    Height = 25
    Caption = #50836#52397
    TabOrder = 3
    OnClick = btRequestClick
  end
  object btReply: TButton
    Left = 464
    Top = 128
    Width = 75
    Height = 25
    Caption = #51025#45813
    TabOrder = 4
  end
  object btStart: TButton
    Left = 536
    Top = 16
    Width = 75
    Height = 25
    Caption = #49884#51089
    TabOrder = 5
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
    TabOrder = 6
    Text = '127.0.0.1'
  end
  object IdUDPServer1: TIdUDPServer
    Bindings = <>
    DefaultPort = 0
    OnUDPRead = IdUDPServer1UDPRead
    Left = 584
    Top = 256
  end
end
