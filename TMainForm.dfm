object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'JanviewPro Server'
  ClientHeight = 617
  ClientWidth = 1070
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesigned
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1070
    Height = 185
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 1066
    object GroupBox2: TGroupBox
      AlignWithMargins = True
      Left = 186
      Top = 4
      Width = 267
      Height = 177
      Align = alLeft
      Caption = 'Statistics'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object Panel2: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 19
        Width = 257
        Height = 153
        Margins.Top = 0
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          257
          153)
        object IterationsLbl: TLabel
          Left = 242
          Top = 57
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
          ExplicitLeft = 235
        end
        object ServerRunLbl: TLabel
          Left = 4
          Top = 32
          Width = 137
          Height = 17
          Caption = 'Threads Running Time:'
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlue
          Font.Height = -13
          Font.Name = 'Segoe UI Semibold'
          Font.Style = [fsItalic, fsUnderline]
          ParentFont = False
          OnClick = ServerRunLblClick
        end
        object Label5: TLabel
          Left = 4
          Top = 57
          Width = 149
          Height = 17
          Caption = 'System Check Iterations:'
        end
        object ServerRunTimeLbl: TLabel
          Left = 242
          Top = 32
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
          ExplicitLeft = 235
        end
        object ExceptionCountLbl: TLabel
          Left = 242
          Top = 80
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
          Font.Charset = ANSI_CHARSET
          Font.Color = clRed
          Font.Height = -13
          Font.Name = 'Segoe UI Semibold'
          Font.Style = [fsBold]
          ParentFont = False
          ExplicitLeft = 235
        end
        object Label3: TLabel
          Left = 4
          Top = 80
          Width = 109
          Height = 17
          Caption = 'Exceptions Count:'
        end
        object Label7: TLabel
          Left = 4
          Top = 9
          Width = 90
          Height = 17
          Caption = 'Server Started:'
        end
        object ServerTimeLbl: TLabel
          Left = 242
          Top = 9
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
          ExplicitLeft = 235
        end
      end
    end
    object GroupBox1: TGroupBox
      AlignWithMargins = True
      Left = 459
      Top = 4
      Width = 198
      Height = 177
      Align = alLeft
      Caption = 'Database'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object Panel3: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 19
        Width = 188
        Height = 153
        Margins.Top = 0
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          188
          153)
        object Label4: TLabel
          Left = 4
          Top = 6
          Width = 78
          Height = 17
          Caption = 'Connections:'
        end
        object DBConnectionsLbl: TLabel
          Left = 173
          Top = 6
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
        end
        object Label1: TLabel
          Left = 4
          Top = 29
          Width = 126
          Height = 17
          Caption = 'Customer Insertions:'
        end
        object CustInsertsLbl: TLabel
          Left = 173
          Top = 29
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
        end
        object InvInsertLbl: TLabel
          Left = 173
          Top = 52
          Width = 7
          Height = 17
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Caption = '0'
        end
        object Label9: TLabel
          Left = 4
          Top = 52
          Width = 110
          Height = 17
          Caption = 'Invoice Insertions:'
        end
      end
    end
    object GroupBox3: TGroupBox
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 176
      Height = 177
      Align = alLeft
      Caption = 'Server Tasks'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      object ThreadStateLbl: TLabel
        Left = 21
        Top = 99
        Width = 79
        Height = 17
        Caption = 'Thread State:'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold, fsItalic, fsUnderline]
        ParentFont = False
        OnClick = ThreadStateLblClick
      end
      object RunningIndicator: TShape
        Left = 102
        Top = 104
        Width = 21
        Height = 10
        Brush.Color = clRed
        Shape = stCircle
      end
      object StartSchedulerBtn: TButton
        Left = 18
        Top = 25
        Width = 142
        Height = 26
        Caption = 'Start Server'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        OnClick = StartSchedulerBtnClick
      end
      object StopTimerBtn: TButton
        Left = 18
        Top = 59
        Width = 142
        Height = 26
        Caption = 'Stop Server'
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = StopTimerBtnClick
      end
    end
    object GroupBox4: TGroupBox
      AlignWithMargins = True
      Left = 663
      Top = 4
      Width = 402
      Height = 177
      Align = alLeft
      Caption = 'Column Contents'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object ColumnMemo: TMemo
        Left = 2
        Top = 19
        Width = 398
        Height = 156
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object StatusBar: TStatusBar
    AlignWithMargins = True
    Left = 5
    Top = 584
    Width = 1060
    Height = 30
    Margins.Left = 5
    Margins.Top = 1
    Margins.Right = 5
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBtnText
    Font.Height = -11
    Font.Name = 'Segoe UI'
    Font.Style = [fsItalic]
    Panels = <
      item
        Text = 'Today:'
        Width = 460
      end
      item
        Width = 50
      end
      item
        Alignment = taRightJustify
        Text = 'Copyright '#169'2023'
        Width = 150
      end>
    UseSystemFont = False
    ExplicitTop = 583
    ExplicitWidth = 1056
  end
  object Panel5: TPanel
    Left = 0
    Top = 185
    Width = 1070
    Height = 72
    Align = alTop
    TabOrder = 2
    ExplicitWidth = 1066
    object ClearLblBtn: TButton
      Left = 15
      Top = 7
      Width = 142
      Height = 26
      Caption = 'Clear Log View'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = ClearLblBtnClick
    end
    object FileLogChk: TCheckBox
      AlignWithMargins = True
      Left = 969
      Top = 4
      Width = 97
      Height = 22
      Margins.Left = 5
      Margins.Bottom = 45
      Align = alRight
      Caption = 'Log To File'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      State = cbChecked
      TabOrder = 1
      ExplicitLeft = 965
    end
    object ForceLogRotBtn: TButton
      Left = 15
      Top = 39
      Width = 142
      Height = 26
      Caption = 'Force Log Rotations'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = ForceLogRotBtnClick
    end
    object ShowCustThreadView: TButton
      Left = 163
      Top = 39
      Width = 142
      Height = 26
      Caption = 'Show Customers'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = ShowCustThreadViewClick
    end
    object ShowInvThreadView: TButton
      Left = 311
      Top = 38
      Width = 142
      Height = 26
      Caption = 'Show Invoices'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = ShowInvThreadViewClick
    end
    object GetCconnectionsBtn: TButton
      Left = 163
      Top = 7
      Width = 142
      Height = 26
      Caption = 'Get Connections'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnClick = GetConnectionsBtnClick
    end
    object AdHocQryBtn: TButton
      Left = 311
      Top = 7
      Width = 142
      Height = 26
      Caption = 'Ad Hoc Query'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = AdHocQryBtnClick
    end
    object SetLastRetrieveTime: TButton
      Left = 459
      Top = 6
      Width = 142
      Height = 26
      Caption = 'Set Last Retrieval'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      OnClick = SetLastRetrieveTimeClick
    end
    object ShowPymtThreadView: TButton
      Left = 459
      Top = 38
      Width = 142
      Height = 26
      Caption = 'Show Payments'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      OnClick = ShowPymtThreadViewClick
    end
    object SetupTableBtn: TButton
      Left = 607
      Top = 6
      Width = 142
      Height = 26
      Caption = 'Setup Tables From Qbo'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
    end
  end
  object BottomPnl: TPanel
    Left = 0
    Top = 257
    Width = 1070
    Height = 326
    Align = alClient
    Caption = 'BottomPnl'
    TabOrder = 3
    ExplicitWidth = 1066
    ExplicitHeight = 325
    object Memo: TMemo
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 1062
      Height = 318
      Align = alClient
      Lines.Strings = (
        '')
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object StatusTimer: TTimer
    Enabled = False
    OnTimer = StatusTimerTimer
    Left = 111
    Top = 449
  end
  object ServerTimer: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = ServerTimerTimer
    Left = 111
    Top = 513
  end
  object FDGUIxWaitCursor1: TFDGUIxWaitCursor
    Provider = 'Forms'
    ScreenCursor = gcrHourGlass
    Left = 112
    Top = 384
  end
  object FDManager: TFDManager
    WaitCursor = gcrHourGlass
    FormatOptions.AssignedValues = [fvMapRules]
    FormatOptions.OwnMapRules = True
    FormatOptions.MapRules = <>
    Active = True
    Left = 224
    Top = 384
  end
  object FDPhysPgDriverLink: TFDPhysPgDriverLink
    Left = 352
    Top = 384
  end
  object TetheringManager: TTetheringManager
    Text = 'TetheringManager'
    AllowedAdapters = 'Network'
    Left = 352
    Top = 504
  end
  object TetheringAppProfile: TTetheringAppProfile
    Manager = TetheringManager
    Text = 'TetheringAppProfile'
    Actions = <>
    Resources = <>
    Left = 352
    Top = 448
  end
  object MainMenu1: TMainMenu
    Left = 496
    Top = 408
    object Exit1: TMenuItem
      Caption = 'File'
      object Exit: TMenuItem
        Caption = 'Exit'
        OnClick = ExitClick
      end
    end
  end
  object FDPhysCDataGmailDriverLink1: TFDPhysCDataGmailDriverLink
    DriverID = 'CDataGmail'
    Left = 744
    Top = 472
  end
  object FDGmailConnection: TFDConnection
    Left = 744
    Top = 408
  end
end
