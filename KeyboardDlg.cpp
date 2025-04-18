
#include "pch.h"
#include "PCICT_MFC.h"
#include "PCICT_MFCDlg.h"
#include "afxdialogex.h"
#include "KeyboardDlg.h"





// KeyboardDlg dialog

IMPLEMENT_DYNAMIC(KeyboardDlg, CDialogEx)

KeyboardDlg::KeyboardDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_KB, pParent)
{

}

KeyboardDlg::~KeyboardDlg()
{
}

void KeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_kb1, kb1);
}


BEGIN_MESSAGE_MAP(KeyboardDlg, CDialogEx)
    //ON_BN_CLICKED(1046, &KeyboardDlg::OnBnClicked1046)
    ON_WM_CLOSE()
    ON_WM_HELPINFO()
    ON_BN_CLICKED(IDC_BUTTON_kb_yes, &KeyboardDlg::OnBnClickedButtonkbyes)
    ON_BN_CLICKED(IDC_BUTTON_kb_no, &KeyboardDlg::OnBnClickedButtonkbno)
    ON_BN_CLICKED(IDC_BUTTON_kb_refresh, &KeyboardDlg::OnBnClickedButtonkbrefresh)
END_MESSAGE_MAP()

void KeyboardDlg::allKeyNormal() 
{

    LOGFONT lf;
    CFont* pDefaultFont = GetFont(); // Get the default font of the dialog
    if (pDefaultFont)
    {
        // Retrieve the LOGFONT structure of the default font
        pDefaultFont->GetLogFont(&lf);

        // Modify the size or weight as needed
        lf.lfHeight = -13;     // Example: Set to 15-pixel height
        lf.lfWeight = FW_NORMAL; // Set weight to medium (FW_NORMAL for regular)

        // Create a new font based on the default font
        NFont.CreateFontIndirect(&lf);
    }
    else {
        NFont.CreateFont(
            -13,                      // Height of font (negative for pixel height, e.g., -12 for smaller font)
            0,                       // Width of font (0 for default)
            0,                       // Escapement
            0,                       // Orientation
            FW_NORMAL,               // Font weight (FW_NORMAL for regular text)
            FALSE,                   // Italic
            FALSE,                   // Underline
            0,                       // StrikeOut
            DEFAULT_CHARSET,         // Character Set
            OUT_DEFAULT_PRECIS,      // Output Precision
            CLIP_DEFAULT_PRECIS,     // Clipping Precision
            DEFAULT_QUALITY,         // Quality
            DEFAULT_PITCH | FF_SWISS,// Pitch and Family
            _T("Arial")              // Font face name
        );
    }

    CButton* button0 = (CButton*)GetDlgItem(IDC_BUTTON_kb0);
    CButton* button1 = (CButton*)GetDlgItem(IDC_BUTTON_kb1);
    CButton* button2 = (CButton*)GetDlgItem(IDC_BUTTON_kb2);
    CButton* button3 = (CButton*)GetDlgItem(IDC_BUTTON_kb3);
    CButton* button4 = (CButton*)GetDlgItem(IDC_BUTTON_kb4);
    CButton* button5 = (CButton*)GetDlgItem(IDC_BUTTON_kb5);
    CButton* button6 = (CButton*)GetDlgItem(IDC_BUTTON_kb6);
    CButton* button7 = (CButton*)GetDlgItem(IDC_BUTTON_kb7);
    CButton* button8 = (CButton*)GetDlgItem(IDC_BUTTON_kb8);
    CButton* button9 = (CButton*)GetDlgItem(IDC_BUTTON_kb9);

        // Letter keys
    CButton* button10 = (CButton*)GetDlgItem(IDC_BUTTON_kbA);
    CButton* button11 = (CButton*)GetDlgItem(IDC_BUTTON_kbB);
    CButton* button12 = (CButton*)GetDlgItem(IDC_BUTTON_kbC);
    CButton* button13 = (CButton*)GetDlgItem(IDC_BUTTON_kbD);
    CButton* button14 = (CButton*)GetDlgItem(IDC_BUTTON_kbE);
    CButton* button15 = (CButton*)GetDlgItem(IDC_BUTTON_kbF);
    CButton* button16 = (CButton*)GetDlgItem(IDC_BUTTON_kbG);
    CButton* button17 = (CButton*)GetDlgItem(IDC_BUTTON_kbH);
    CButton* button18 = (CButton*)GetDlgItem(IDC_BUTTON_kbI);
    CButton* button19 = (CButton*)GetDlgItem(IDC_BUTTON_kbJ);
    CButton* button20 = (CButton*)GetDlgItem(IDC_BUTTON_kbK);
    CButton* button21 = (CButton*)GetDlgItem(IDC_BUTTON_kbL);
    CButton* button22 = (CButton*)GetDlgItem(IDC_BUTTON_kbM);
    CButton* button23 = (CButton*)GetDlgItem(IDC_BUTTON_kbN);
    CButton* button24 = (CButton*)GetDlgItem(IDC_BUTTON_kbO);
    CButton* button25 = (CButton*)GetDlgItem(IDC_BUTTON_kbP);
    CButton* button26 = (CButton*)GetDlgItem(IDC_BUTTON_kbQ);
    CButton* button27 = (CButton*)GetDlgItem(IDC_BUTTON_kbR);
    CButton* button28 = (CButton*)GetDlgItem(IDC_BUTTON_kbS);
    CButton* button29 = (CButton*)GetDlgItem(IDC_BUTTON_kbT);
    CButton* button30 = (CButton*)GetDlgItem(IDC_BUTTON_kbU);
    CButton* button31 = (CButton*)GetDlgItem(IDC_BUTTON_kbV);
    CButton* button32 = (CButton*)GetDlgItem(IDC_BUTTON_kbW);
    CButton* button33 = (CButton*)GetDlgItem(IDC_BUTTON_kbX);
    CButton* button34 = (CButton*)GetDlgItem(IDC_BUTTON_kbY);
    CButton* button35 = (CButton*)GetDlgItem(IDC_BUTTON_kbZ);

        // Function keys
    CButton* button36 = (CButton*)GetDlgItem(IDC_BUTTON_kbf1);
    CButton* button37 = (CButton*)GetDlgItem(IDC_BUTTON_kbf2);
    CButton* button38 = (CButton*)GetDlgItem(IDC_BUTTON_kbf3);
    CButton* button39 = (CButton*)GetDlgItem(IDC_BUTTON_kbf4);
    CButton* button40 = (CButton*)GetDlgItem(IDC_BUTTON_kbf5);
    CButton* button41 = (CButton*)GetDlgItem(IDC_BUTTON_kbf6);
    CButton* button42 = (CButton*)GetDlgItem(IDC_BUTTON_kbf7);
    CButton* button43 = (CButton*)GetDlgItem(IDC_BUTTON_kbf8);
    CButton* button44 = (CButton*)GetDlgItem(IDC_BUTTON_kbf9);
    CButton* button45 = (CButton*)GetDlgItem(IDC_BUTTON_kbf10);
    CButton* button46 = (CButton*)GetDlgItem(IDC_BUTTON_kbf11);
    CButton* button47 = (CButton*)GetDlgItem(IDC_BUTTON_kbf12);

        // Numpad keys
    CButton* button48 = (CButton*)GetDlgItem(IDC_BUTTON_kbn0);
    CButton* button49 = (CButton*)GetDlgItem(IDC_BUTTON_kb_numlk);
    CButton* button50 = (CButton*)GetDlgItem(IDC_BUTTON_kbn1);
    CButton* button51 = (CButton*)GetDlgItem(IDC_BUTTON_kbn2);
    CButton* button52 = (CButton*)GetDlgItem(IDC_BUTTON_kbn3);
    CButton* button53 = (CButton*)GetDlgItem(IDC_BUTTON_kbn4);
    CButton* button54 = (CButton*)GetDlgItem(IDC_BUTTON_kbn5);
    CButton* button55 = (CButton*)GetDlgItem(IDC_BUTTON_kbn6);
    CButton* button56 = (CButton*)GetDlgItem(IDC_BUTTON_kbn7);
    CButton* button57 = (CButton*)GetDlgItem(IDC_BUTTON_kbn8);
    CButton* button58 = (CButton*)GetDlgItem(IDC_BUTTON_kbn9);

    CButton* button59 = (CButton*)GetDlgItem(IDC_BUTTON_kb_plus);
    CButton* button60 = (CButton*)GetDlgItem(IDC_BUTTON_kb_minus2);
    CButton* button61 = (CButton*)GetDlgItem(IDC_BUTTON_kb_asteric);
    CButton* button62 = (CButton*)GetDlgItem(IDC_BUTTON_kb_slash2);
    CButton* button63 = (CButton*)GetDlgItem(IDC_BUTTON_kb_period2);

        // Navigation keys
    CButton* button64 = (CButton*)GetDlgItem(IDC_BUTTON_kb_pgup);
    CButton* button65 = (CButton*)GetDlgItem(IDC_BUTTON_kb_pgdn);
    CButton* button66 = (CButton*)GetDlgItem(IDC_BUTTON_kb_home);
    CButton* button67 = (CButton*)GetDlgItem(IDC_BUTTON_kb_end);
    CButton* button68 = (CButton*)GetDlgItem(IDC_BUTTON_kb_insert);
    CButton* button69 = (CButton*)GetDlgItem(IDC_BUTTON_kb_del);

    CButton* button70 = (CButton*)GetDlgItem(IDC_BUTTON_kb_prtsc);
    CButton* button71 = (CButton*)GetDlgItem(IDC_BUTTON_kb_scrlk);
    CButton* button72 = (CButton*)GetDlgItem(IDC_BUTTON_kb_pause);


        // Arrow keys
    CButton* button73 = (CButton*)GetDlgItem(IDC_BUTTON_kb_larrow);
    CButton* button74 = (CButton*)GetDlgItem(IDC_BUTTON_kb_rarrow);
    CButton* button75 = (CButton*)GetDlgItem(IDC_BUTTON_kb_uarrow);
    CButton* button76 = (CButton*)GetDlgItem(IDC_BUTTON_kb_darrow);

        // Special keys 
    CButton* button77 = (CButton*)GetDlgItem(IDC_BUTTON_kb_esc);
    CButton* button78 = (CButton*)GetDlgItem(IDC_BUTTON_kb_lctrl);
    CButton* button79 = (CButton*)GetDlgItem(IDC_BUTTON_kb_rctrl);
    CButton* button80 = (CButton*)GetDlgItem(IDC_BUTTON_kb_lshift);
    CButton* button81 = (CButton*)GetDlgItem(IDC_BUTTON_kb_rshift);
    CButton* button82 = (CButton*)GetDlgItem(IDC_BUTTON_kb_lalt);
    CButton* button83 = (CButton*)GetDlgItem(IDC_BUTTON_kb_ralt);
    CButton* button84 = (CButton*)GetDlgItem(IDC_BUTTON_kb_enter);
    CButton* button85 = (CButton*)GetDlgItem(IDC_BUTTON_kb_enter2);

    CButton* button86 = (CButton*)GetDlgItem(IDC_BUTTON_kb_cplk);
    CButton* button87 = (CButton*)GetDlgItem(IDC_BUTTON_kb_minus);
    CButton* button88 = (CButton*)GetDlgItem(IDC_BUTTON_kb_equal);
    CButton* button89 = (CButton*)GetDlgItem(IDC_BUTTON_kb_bksp);
    CButton* button90 = (CButton*)GetDlgItem(IDC_BUTTON_kb_bktk);

    CButton* button91 = (CButton*)GetDlgItem(IDC_BUTTON_kb_tab);
    CButton* button92 = (CButton*)GetDlgItem(IDC_BUTTON_kb_space);
    CButton* button93 = (CButton*)GetDlgItem(IDC_BUTTON_kb_lwin);
    CButton* button94 = (CButton*)GetDlgItem(IDC_BUTTON_kb_rwin);
    CButton* button95 = (CButton*)GetDlgItem(IDC_BUTTON_kb_menu);

        // Brackets, Slash, and Other Special Keys
    CButton* button96 = (CButton*)GetDlgItem(IDC_BUTTON_kb_braceS);
    CButton* button97 = (CButton*)GetDlgItem(IDC_BUTTON_kb_braceE);
    CButton* button98 = (CButton*)GetDlgItem(IDC_BUTTON_kb_bkslash);
    CButton* button99 = (CButton*)GetDlgItem(IDC_BUTTON_kb_colon);
    CButton* button100 = (CButton*)GetDlgItem(IDC_BUTTON_kb_quote);

    CButton* button101 = (CButton*)GetDlgItem(IDC_BUTTON_kb_comma);
    CButton* button102 = (CButton*)GetDlgItem(IDC_BUTTON_kb_period);
    CButton* button103 = (CButton*)GetDlgItem(IDC_BUTTON_kb_slash);

    button0->SetWindowTextW(L"0"); button0->SetFont(&NFont);
	button1->SetWindowTextW(L"1"); button1->SetFont(&NFont);
    button2->SetWindowTextW(L"2"); button2->SetFont(&NFont);
    button3->SetWindowTextW(L"3"); button3->SetFont(&NFont);
    button4->SetWindowTextW(L"4"); button4->SetFont(&NFont);
    button5->SetWindowTextW(L"5"); button5->SetFont(&NFont);
    button6->SetWindowTextW(L"6"); button6->SetFont(&NFont);
    button7->SetWindowTextW(L"7"); button7->SetFont(&NFont);
    button8->SetWindowTextW(L"8"); button8->SetFont(&NFont);
    button9->SetWindowTextW(L"9"); button9->SetFont(&NFont);

    button10->SetWindowTextW(L"A"); button10->SetFont(&NFont);
    button11->SetWindowTextW(L"B"); button11->SetFont(&NFont);
    button12->SetWindowTextW(L"C"); button12->SetFont(&NFont);
    button13->SetWindowTextW(L"D"); button13->SetFont(&NFont);
    button14->SetWindowTextW(L"E"); button14->SetFont(&NFont);
    button15->SetWindowTextW(L"F"); button15->SetFont(&NFont);
    button16->SetWindowTextW(L"G"); button16->SetFont(&NFont);
    button17->SetWindowTextW(L"H"); button17->SetFont(&NFont);
    button18->SetWindowTextW(L"I"); button18->SetFont(&NFont);
    button19->SetWindowTextW(L"J"); button19->SetFont(&NFont);
    button20->SetWindowTextW(L"K"); button20->SetFont(&NFont);
    button21->SetWindowTextW(L"L"); button21->SetFont(&NFont);
    button22->SetWindowTextW(L"M"); button22->SetFont(&NFont);
    button23->SetWindowTextW(L"N"); button23->SetFont(&NFont);
    button24->SetWindowTextW(L"O"); button24->SetFont(&NFont);
    button25->SetWindowTextW(L"P"); button25->SetFont(&NFont);
    button26->SetWindowTextW(L"Q"); button26->SetFont(&NFont);
    button27->SetWindowTextW(L"R"); button27->SetFont(&NFont);
    button28->SetWindowTextW(L"S"); button28->SetFont(&NFont);
    button29->SetWindowTextW(L"T"); button29->SetFont(&NFont);
    button30->SetWindowTextW(L"U"); button30->SetFont(&NFont);
    button31->SetWindowTextW(L"V"); button31->SetFont(&NFont);
    button32->SetWindowTextW(L"W"); button32->SetFont(&NFont);
    button33->SetWindowTextW(L"X"); button33->SetFont(&NFont);
    button34->SetWindowTextW(L"Y"); button34->SetFont(&NFont);
    button35->SetWindowTextW(L"Z"); button35->SetFont(&NFont);

    button36->SetWindowTextW(L"F1"); button36->SetFont(&NFont);
    button37->SetWindowTextW(L"F2"); button37->SetFont(&NFont);
    button38->SetWindowTextW(L"F3"); button38->SetFont(&NFont);
    button39->SetWindowTextW(L"F4"); button39->SetFont(&NFont);
    button40->SetWindowTextW(L"F5"); button40->SetFont(&NFont);
    button41->SetWindowTextW(L"F6"); button41->SetFont(&NFont);
    button42->SetWindowTextW(L"F7"); button42->SetFont(&NFont);
    button43->SetWindowTextW(L"F8"); button43->SetFont(&NFont);
    button44->SetWindowTextW(L"F9"); button44->SetFont(&NFont);
    button45->SetWindowTextW(L"F10"); button45->SetFont(&NFont);
    button46->SetWindowTextW(L"F11"); button46->SetFont(&NFont);
    button47->SetWindowTextW(L"F12"); button47->SetFont(&NFont);

    button48->SetWindowTextW(L"0"); button48->SetFont(&NFont);
    button49->SetWindowTextW(L"Num Lock"); button49->SetFont(&NFont);
    button50->SetWindowTextW(L"1"); button50->SetFont(&NFont);
    button51->SetWindowTextW(L"2"); button51->SetFont(&NFont);
    button52->SetWindowTextW(L"3"); button52->SetFont(&NFont);
    button53->SetWindowTextW(L"4"); button53->SetFont(&NFont);
    button54->SetWindowTextW(L"5"); button54->SetFont(&NFont);
    button55->SetWindowTextW(L"6"); button55->SetFont(&NFont);
    button56->SetWindowTextW(L"7"); button56->SetFont(&NFont);
    button57->SetWindowTextW(L"8"); button57->SetFont(&NFont);
    button58->SetWindowTextW(L"9"); button58->SetFont(&NFont);

    button59->SetWindowTextW(L"+"); button59->SetFont(&NFont);
    button60->SetWindowTextW(L"-"); button60->SetFont(&NFont);
    button61->SetWindowTextW(L"*"); button61->SetFont(&NFont);
    button62->SetWindowTextW(L"/"); button62->SetFont(&NFont);
    button63->SetWindowTextW(L"."); button63->SetFont(&NFont);

    button64->SetWindowTextW(L"Pg Up"); button64->SetFont(&NFont);
    button65->SetWindowTextW(L"Pg Dn"); button65->SetFont(&NFont);
    button66->SetWindowTextW(L"Home"); button66->SetFont(&NFont);
    button67->SetWindowTextW(L"End"); button67->SetFont(&NFont);
    button68->SetWindowTextW(L"Insert"); button68->SetFont(&NFont);
    button69->SetWindowTextW(L"Delete"); button69->SetFont(&NFont);

    button70->SetWindowTextW(L"Prt Sc"); button70->SetFont(&NFont);
    button71->SetWindowTextW(L"Scr Lock"); button71->SetFont(&NFont);
    button72->SetWindowTextW(L"Pause"); button72->SetFont(&NFont);

    button73->SetWindowTextW(L"◄"); button73->SetFont(&NFont);
    button74->SetWindowTextW(L"►"); button74->SetFont(&NFont);
    button75->SetWindowTextW(L"▲"); button75->SetFont(&NFont);
    button76->SetWindowTextW(L"▼"); button76->SetFont(&NFont);

    button77->SetWindowTextW(L"Esc"); button77->SetFont(&NFont);
    button78->SetWindowTextW(L"Ctrl"); button78->SetFont(&NFont);
    button79->SetWindowTextW(L"Ctrl"); button79->SetFont(&NFont);
    button80->SetWindowTextW(L"Shift"); button80->SetFont(&NFont);
    button81->SetWindowTextW(L"Shift"); button81->SetFont(&NFont);
    button82->SetWindowTextW(L"Alt"); button82->SetFont(&NFont);
    button83->SetWindowTextW(L"Alt"); button83->SetFont(&NFont);
    button84->SetWindowTextW(L"Enter"); button84->SetFont(&NFont);
    button85->SetWindowTextW(L"Enter"); button85->SetFont(&NFont);

    button86->SetWindowTextW(L"Caps Lock"); button86->SetFont(&NFont);
    button87->SetWindowTextW(L"-"); button87->SetFont(&NFont);
    button88->SetWindowTextW(L"="); button88->SetFont(&NFont);
    button89->SetWindowTextW(L"Backspace"); button89->SetFont(&NFont);
    button90->SetWindowTextW(L"`"); button90->SetFont(&NFont);

    button91->SetWindowTextW(L"Tab"); button91->SetFont(&NFont);
    button92->SetWindowTextW(L"Space"); button92->SetFont(&NFont);
    button93->SetWindowTextW(L"Win"); button93->SetFont(&NFont);
    button94->SetWindowTextW(L"Win"); button94->SetFont(&NFont);
    button95->SetWindowTextW(L"Menu"); button95->SetFont(&NFont);

    button96->SetWindowTextW(L"["); button96->SetFont(&NFont);
    button97->SetWindowTextW(L"]"); button97->SetFont(&NFont);
    button98->SetWindowTextW(L"\\"); button98->SetFont(&NFont);
    button99->SetWindowTextW(L";"); button99->SetFont(&NFont);
    button100->SetWindowTextW(L"'"); button100->SetFont(&NFont);

    button101->SetWindowTextW(L","); button101->SetFont(&NFont);
    button102->SetWindowTextW(L"."); button102->SetFont(&NFont);
    button103->SetWindowTextW(L"/"); button103->SetFont(&NFont);

}


void KeyboardDlg::HighlightKey(UINT virtualKey, bool isPressed)
{
    CButton* button = nullptr;

    // Map each virtual key to its corresponding button ID
    switch (virtualKey)
    {
        // Numeric keys
    case 0x30: button = (CButton*)GetDlgItem(IDC_BUTTON_kb0); break;
    case 0x31: button = (CButton*)GetDlgItem(IDC_BUTTON_kb1); break;
    case 0x32: button = (CButton*)GetDlgItem(IDC_BUTTON_kb2); break;
    case 0x33: button = (CButton*)GetDlgItem(IDC_BUTTON_kb3); break;
    case 0x34: button = (CButton*)GetDlgItem(IDC_BUTTON_kb4); break;
    case 0x35: button = (CButton*)GetDlgItem(IDC_BUTTON_kb5); break;
    case 0x36: button = (CButton*)GetDlgItem(IDC_BUTTON_kb6); break;
    case 0x37: button = (CButton*)GetDlgItem(IDC_BUTTON_kb7); break;
    case 0x38: button = (CButton*)GetDlgItem(IDC_BUTTON_kb8); break;
    case 0x39: button = (CButton*)GetDlgItem(IDC_BUTTON_kb9); break;

        // Letter keys
    case 0x41: button = (CButton*)GetDlgItem(IDC_BUTTON_kbA); break; // 'A'
    case 0x42: button = (CButton*)GetDlgItem(IDC_BUTTON_kbB); break; // 'B'
    case 0x43: button = (CButton*)GetDlgItem(IDC_BUTTON_kbC); break; // 'C'
    case 0x44: button = (CButton*)GetDlgItem(IDC_BUTTON_kbD); break; // 'D'
    case 0x45: button = (CButton*)GetDlgItem(IDC_BUTTON_kbE); break; // 'E'
    case 0x46: button = (CButton*)GetDlgItem(IDC_BUTTON_kbF); break; // 'F'
    case 0x47: button = (CButton*)GetDlgItem(IDC_BUTTON_kbG); break; // 'G'
    case 0x48: button = (CButton*)GetDlgItem(IDC_BUTTON_kbH); break; // 'H'
    case 0x49: button = (CButton*)GetDlgItem(IDC_BUTTON_kbI); break; // 'I'
    case 0x4A: button = (CButton*)GetDlgItem(IDC_BUTTON_kbJ); break; // 'J'
    case 0x4B: button = (CButton*)GetDlgItem(IDC_BUTTON_kbK); break; // 'K'
    case 0x4C: button = (CButton*)GetDlgItem(IDC_BUTTON_kbL); break; // 'L'
    case 0x4D: button = (CButton*)GetDlgItem(IDC_BUTTON_kbM); break; // 'M'
    case 0x4E: button = (CButton*)GetDlgItem(IDC_BUTTON_kbN); break; // 'N'
    case 0x4F: button = (CButton*)GetDlgItem(IDC_BUTTON_kbO); break; // 'O'
    case 0x50: button = (CButton*)GetDlgItem(IDC_BUTTON_kbP); break; // 'P'
    case 0x51: button = (CButton*)GetDlgItem(IDC_BUTTON_kbQ); break; // 'Q'
    case 0x52: button = (CButton*)GetDlgItem(IDC_BUTTON_kbR); break; // 'R'
    case 0x53: button = (CButton*)GetDlgItem(IDC_BUTTON_kbS); break; // 'S'
    case 0x54: button = (CButton*)GetDlgItem(IDC_BUTTON_kbT); break; // 'T'
    case 0x55: button = (CButton*)GetDlgItem(IDC_BUTTON_kbU); break; // 'U'
    case 0x56: button = (CButton*)GetDlgItem(IDC_BUTTON_kbV); break; // 'V'
    case 0x57: button = (CButton*)GetDlgItem(IDC_BUTTON_kbW); break; // 'W'
    case 0x58: button = (CButton*)GetDlgItem(IDC_BUTTON_kbX); break; // 'X'
    case 0x59: button = (CButton*)GetDlgItem(IDC_BUTTON_kbY); break; // 'Y'
    case 0x5A: button = (CButton*)GetDlgItem(IDC_BUTTON_kbZ); break; // 'Z'

        // Function keys
    case VK_F1: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf1); break;
    case VK_F2: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf2); break;
    case VK_F3: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf3); break;
    case VK_F4: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf4); break;
    case VK_F5: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf5); break;
    case VK_F6: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf6); break;
    case VK_F7: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf7); break;
    case VK_F8: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf8); break;
    case VK_F9: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf9); break;
    case VK_F10: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf10); break;
    case VK_F11: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf11); break;
    case VK_F12: button = (CButton*)GetDlgItem(IDC_BUTTON_kbf12); break;

        // Numpad keys
    case VK_NUMPAD0: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn0); break;
    case VK_NUMLOCK: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_numlk); break;
    case VK_NUMPAD1: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn1); break;
    case VK_NUMPAD2: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn2); break;
    case VK_NUMPAD3: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn3); break;
    case VK_NUMPAD4: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn4); break;
    case VK_NUMPAD5: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn5); break;
    case VK_NUMPAD6: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn6); break;
    case VK_NUMPAD7: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn7); break;
    case VK_NUMPAD8: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn8); break;
    case VK_NUMPAD9: button = (CButton*)GetDlgItem(IDC_BUTTON_kbn9); break;
    case VK_ADD: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_plus); break;
    case VK_SUBTRACT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_minus2); break;
    case VK_MULTIPLY: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_asteric); break;
    case VK_DIVIDE: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_slash2); break;
    case VK_DECIMAL: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_period2); break;

        // Navigation keys
    case VK_PRIOR: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_pgup); break; // Page Up
    case VK_NEXT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_pgdn); break; // Page Down
    case VK_HOME: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_home); break;
    case VK_END: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_end); break;
    case VK_INSERT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_insert); break;
    case VK_DELETE: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_del); break;

    case VK_SNAPSHOT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_prtsc); break; // Print Screen
    case VK_SCROLL: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_scrlk); break; // Scroll Lock
    case 0x13: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_pause); break; // Pause/Break


        // Arrow keys
    case VK_LEFT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_larrow); break;
    case VK_RIGHT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_rarrow); break;
    case VK_UP: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_uarrow); break;
    case VK_DOWN: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_darrow); break;

        // Special keys 
	case VK_ESCAPE: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_esc); break; // Shift
    case VK_LCONTROL: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_lctrl); break; // Left Shift
    case VK_RCONTROL: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_rctrl); break; // Right Shift
    case VK_LSHIFT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_lshift); break; // Left Shift
    case VK_RSHIFT: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_rshift); break; // Right Shift
    case VK_LMENU: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_lalt); break;   // Left ALT
    case VK_RMENU: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_ralt); break;   // Right ALT
    case 0x1C: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_enter); break; // Enter
    case 0xE01C: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_enter2); break;
    case VK_CAPITAL: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_cplk); break; // Caps Lock
    case VK_OEM_MINUS: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_minus); break;
    case VK_OEM_PLUS: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_equal); break;
    case VK_BACK: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_bksp); break;
    case VK_OEM_3: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_bktk); break;
    case VK_TAB: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_tab); break;
    case VK_SPACE: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_space); break;
    case VK_LWIN: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_lwin); break;
    case VK_RWIN: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_rwin); break;
	case VK_APPS: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_menu); break;

        // Brackets, Slash, and Other Special Keys
    case VK_OEM_4: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_braceS); break; // '['
    case VK_OEM_6: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_braceE); break; // ']'
    case VK_OEM_5: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_bkslash); break; // '\'
    case VK_OEM_1: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_colon); break; // ';'
    case VK_OEM_7: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_quote); break; // '''
    case VK_OEM_COMMA: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_comma); break; // ','
    case VK_OEM_PERIOD: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_period); break; // '.'
    case VK_OEM_2: button = (CButton*)GetDlgItem(IDC_BUTTON_kb_slash); break; // '/'


    default:
        return; // Ignore keys that are not between '0' and '9'
    }

    // If the button exists, update its text based on key press/release state
    if (button)
    {
        if (isPressed)
        {
            CString buttonText;
            // Handle special cases for key text
            //if (virtualKey) {
                //buttonText = L"Pressed";
            //}
            if (virtualKey == VK_OEM_MINUS)
                buttonText = L"-";
            else if (virtualKey == VK_OEM_PLUS)
                buttonText = L"=";
            else if (virtualKey == VK_BACK)
                buttonText = L"Backspace";
            else if (virtualKey == VK_TAB)
                buttonText = L"Tab";
            else if (virtualKey == VK_CAPITAL)
                buttonText = L"Caps Lock";
            else if (virtualKey == VK_RETURN)
                buttonText = L"Enter";
            else if (virtualKey == VK_LSHIFT)
                buttonText = L"Shift";
            else if (virtualKey == VK_RSHIFT)
                buttonText = L"Shift";
            else if (virtualKey == VK_LMENU)
                buttonText = L"Alt";
            else if (virtualKey == VK_RMENU)
                buttonText = L"Alt";
            else if (virtualKey == VK_LCONTROL)
                buttonText = L"Ctrl";
            else if (virtualKey == VK_RCONTROL)
                buttonText = L"Ctrl";
            else if (virtualKey == 0xE01C)
                buttonText = L"Enter";
            else if (virtualKey == 0x1C)
                buttonText = L"Enter";
            else if (virtualKey == VK_SPACE)
                buttonText = L"Space";
            else if (virtualKey == VK_LWIN)
                buttonText = L"Win";
            else if (virtualKey == VK_RWIN)
                buttonText = L"Win";
            else if (virtualKey == VK_APPS)
                buttonText = L"Menu";
            else if (virtualKey == VK_ESCAPE)
                buttonText = L"Esc";

            else if (virtualKey == VK_PRIOR)
                buttonText = L"Pg Up";
            else if (virtualKey == VK_NEXT)
                buttonText = L"Pg Dn";
            else if (virtualKey == VK_HOME)
                buttonText = L"Home";
            else if (virtualKey == VK_END)
                buttonText = L"End";
            else if (virtualKey == VK_DELETE)
                buttonText = L"Delete";
            else if (virtualKey == VK_INSERT)
                buttonText = L"Insert";
            else if (virtualKey == VK_PRINT)
                buttonText = L"Prt Sc";
            else if (virtualKey == VK_SCROLL)
                buttonText = L"Scr Lock";
            else if (virtualKey == VK_PAUSE)
                buttonText = L"Pause";
            else if (virtualKey == VK_NUMLOCK)
                buttonText = L"Num Lock";
            else if (virtualKey == VK_SNAPSHOT)
                buttonText = L"Prt Sc";

            else if (virtualKey == VK_LEFT)
                buttonText = L"◄";
            else if (virtualKey == VK_RIGHT)
                buttonText = L"►";
            else if (virtualKey == VK_UP)
                buttonText = L"▲";
            else if (virtualKey == VK_DOWN)
                buttonText = L"▼";

            else if (virtualKey == VK_F1)
                buttonText = L"F1";
            else if (virtualKey == VK_F2)
                buttonText = L"F2";
            else if (virtualKey == VK_F3)
                buttonText = L"F3";
            else if (virtualKey == VK_F4)
                buttonText = L"F4";

            else if (virtualKey == VK_F5)
                buttonText = L"F5";
            else if (virtualKey == VK_F6)
                buttonText = L"F6";
            else if (virtualKey == VK_F7)
                buttonText = L"F7";
            else if (virtualKey == VK_F8)
                buttonText = L"F8";

            else if (virtualKey == VK_F9)
                buttonText = L"F9";
            else if (virtualKey == VK_F10)
                buttonText = L"F10";
            else if (virtualKey == VK_F11)
                buttonText = L"F11";
            else if (virtualKey == VK_F12)
                buttonText = L"F12";


            else{
                //button->SetWindowText(L"Pressed"); // Change text to indicate keypress
                buttonText.Format(L"%c", MapVirtualKey(virtualKey, MAPVK_VK_TO_CHAR));
                button->SetWindowText(buttonText); // Change text to indicate keypress
			}
            
            //buttonText.Format(L"%c", MapVirtualKey(virtualKey, MAPVK_VK_TO_CHAR));
            button->SetFont(&SFont);
            button->SetWindowText(buttonText); // Change text to indicate keypress
            
        }
        else
        {


            CString buttonText;
            // Handle special cases for key text
            //if (virtualKey) {
                //buttonText = L"Pressed";
            //}
            if (virtualKey == VK_OEM_MINUS)
                buttonText = L"-";
            else if (virtualKey == VK_OEM_PLUS)
                buttonText = L"=";
            else if (virtualKey == VK_BACK)
                buttonText = L"Backspace";
            else if (virtualKey == VK_TAB)
                buttonText = L"Tab";
            else if (virtualKey == VK_CAPITAL)
                buttonText = L"Caps Lock";
            else if (virtualKey == VK_RETURN)
                buttonText = L"Enter";
            else if (virtualKey == VK_LSHIFT)
                buttonText = L"Shift";
            else if (virtualKey == VK_RSHIFT)
                buttonText = L"Shift";
            else if (virtualKey == VK_LMENU)
                buttonText = L"Alt";
            else if (virtualKey == VK_RMENU)
                buttonText = L"Alt";
            else if (virtualKey == VK_LCONTROL)
                buttonText = L"Ctrl";
            else if (virtualKey == VK_RCONTROL)
                buttonText = L"Ctrl";
            else if (virtualKey == 0xE01C)
                buttonText = L"Enter";
            else if (virtualKey == 0x1C)
                buttonText = L"Enter";
            else if (virtualKey == VK_SPACE)
                buttonText = L"Space";
            else if (virtualKey == VK_LWIN)
                buttonText = L"Win";
            else if (virtualKey == VK_RWIN)
                buttonText = L"Win";
            else if (virtualKey == VK_APPS)
                buttonText = L"Menu";
            else if (virtualKey == VK_ESCAPE)
                buttonText = L"Esc";

            else if (virtualKey == VK_PRIOR)
                buttonText = L"Pg Up";
            else if (virtualKey == VK_NEXT)
                buttonText = L"Pg Dn";
            else if (virtualKey == VK_HOME)
                buttonText = L"Home";
            else if (virtualKey == VK_END)
                buttonText = L"End";
            else if (virtualKey == VK_DELETE)
                buttonText = L"Delete";
            else if (virtualKey == VK_INSERT)
                buttonText = L"Insert";
            else if (virtualKey == VK_PRINT)
                buttonText = L"Prt Sc";
            else if (virtualKey == VK_SCROLL)
                buttonText = L"Scr Lock";
            else if (virtualKey == VK_PAUSE)
                buttonText = L"Pause";
            else if (virtualKey == VK_NUMLOCK)
                buttonText = L"Num Lock";
            else if (virtualKey == VK_SNAPSHOT)
                buttonText = L"Prt Sc";

            else if (virtualKey == VK_LEFT)
                buttonText = L"◄";
            else if (virtualKey == VK_RIGHT)
                buttonText = L"►";
            else if (virtualKey == VK_UP)
                buttonText = L"▲";
            else if (virtualKey == VK_DOWN)
                buttonText = L"▼";

            else if (virtualKey == VK_F1)
                buttonText = L"F1";
            else if (virtualKey == VK_F2)
                buttonText = L"F2";
            else if (virtualKey == VK_F3)
                buttonText = L"F3";
            else if (virtualKey == VK_F4)
                buttonText = L"F4";

            else if (virtualKey == VK_F5)
                buttonText = L"F5";
            else if (virtualKey == VK_F6)
                buttonText = L"F6";
            else if (virtualKey == VK_F7)
                buttonText = L"F7";
            else if (virtualKey == VK_F8)
                buttonText = L"F8";

            else if (virtualKey == VK_F9)
                buttonText = L"F9";
            else if (virtualKey == VK_F10)
                buttonText = L"F10";
            else if (virtualKey == VK_F11)
                buttonText = L"F11";
            else if (virtualKey == VK_F12)
                buttonText = L"F12";

            else {
                //button->SetWindowText(L"Pressed"); // Change text to indicate keypress
                buttonText.Format(L"%c", MapVirtualKey(virtualKey, MAPVK_VK_TO_CHAR));
                button->SetWindowText(buttonText); // Change text to indicate keypress
            }

            //buttonText.Format(L"%c", MapVirtualKey(virtualKey, MAPVK_VK_TO_CHAR));
            button->SetFont(&BFont);
            button->SetWindowText(buttonText); // Change text to indicate keypress



            //CString buttonText;
            //  //buttonText.Format(L"%c", MapVirtualKey(virtualKey, MAPVK_VK_TO_CHAR));
            //    
            //
            //buttonText.Format(L"Pressed");
            //button->SetFont(&LFont);
            //button->SetWindowText(buttonText);
        }
    }
}



BOOL KeyboardDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP ||
        pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_SYSKEYUP)
    {
        UINT key = pMsg->wParam; // Virtual key code
        bool isPressed = (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN);
        UINT scanCode = (pMsg->lParam >> 16) & 0xFF;  // Extract scan code
        bool isExtended = (pMsg->lParam >> 24) & 0x01; // Check if it's an extended key

        // Handle ALT keys
        if (key == VK_MENU)
        {
            if (isExtended) // Right ALT
                HighlightKey(0xA5, isPressed); // VK_RMENU
            else // Left ALT
                HighlightKey(0xA4, isPressed); // VK_LMENU
        }
        else if (key == VK_SHIFT)
        {
            if (scanCode == 0x2A) // Left Shift
                HighlightKey(0xA0, isPressed);
            else if (scanCode == 0x36) // Right Shift
                HighlightKey(0xA1, isPressed);
        }
        else if (key == VK_CONTROL)
        {
            if (isExtended) // Right Ctrl
                HighlightKey(0xA3, isPressed); // VK_RCONTROL
            else // Left Ctrl
                HighlightKey(0xA2, isPressed); // VK_LCONTROL
        }
        else if (key == VK_RETURN)
        {
            if (isExtended) // Numpad Enter
            {
                HighlightKey(0xE01C, isPressed); // Replace with your Numpad Enter button ID
            }
            else // Main Enter
            {
                HighlightKey(0x1C, isPressed); // Replace with your Main Enter button ID
            }
        }
        else if (key == VK_PAUSE)
        {
            // Pause/Break key handling
            HighlightKey(0x13, isPressed); // VK_PAUSE corresponds to virtual key 0x13
        }
        else if (key == VK_SNAPSHOT)
        {
            // Print Screen key handling
            HighlightKey(0x2C, isPressed); // VK_SNAPSHOT corresponds to virtual key 0x2C
        }
        else
        {
            HighlightKey(key, isPressed);
        }
        return TRUE; // Message handled
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}



BOOL KeyboardDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Initialize the map of key codes to button controls
    //InitializeKeyButtonMap();

    SFont.CreateFont(
        15,                      // Height of font (negative for pixel height, e.g., -12 for smaller font)
        0,                       // Width of font (0 for default)
        0,                       // Escapement
        0,                       // Orientation
        FW_SEMIBOLD,               // Font weight (FW_NORMAL for regular text)
        FALSE,                   // Italic
        FALSE,                   // Underline
        0,                       // StrikeOut
        DEFAULT_CHARSET,         // Character Set
        OUT_DEFAULT_PRECIS,      // Output Precision
        CLIP_DEFAULT_PRECIS,     // Clipping Precision
        DEFAULT_QUALITY,         // Quality
        DEFAULT_PITCH | FF_SWISS,// Pitch and Family
        _T("Arial")              // Font face name
    );

    //CFont BFont;
    BFont.CreateFont(
        18,                      // Height of font (in pixels)
        0,                       // Width of font (0 for default)
        0,                       // Escapement
        0,                       // Orientation
        FW_BOLD,                 // Font weight (FW_BOLD for bold text)
        FALSE,                   // Italic
        FALSE,                   // Underline
        0,                       // StrikeOut
        DEFAULT_CHARSET,         // Character Set
        OUT_DEFAULT_PRECIS,      // Output Precision
        CLIP_DEFAULT_PRECIS,     // Clipping Precision
        DEFAULT_QUALITY,         // Quality
        DEFAULT_PITCH | FF_SWISS,// Pitch and Family
        _T("Arial")              // Font face name
    );

    CButton* btn = nullptr;
    btn = (CButton*)GetDlgItem(IDC_BUTTON_kb_bold);
    btn->SetFont(&BFont);

	//AfxMessageBox(theApp.language);
    if (theApp.language == L"en")
    {
        //CStatic * stc = nullptr;
        //stc = (CStatic*)GetDlgItem(IDC_STATIC_PRESSED);
        //stc->SetWindowTextW(L"Hi");
        GetDlgItem(IDC_STATIC_PRESSED)->SetWindowTextW(L"Already pressed");
        GetDlgItem(IDC_STATIC_NOT_PRESSED)->SetWindowTextW(L"Not pressed yet");
        GetDlgItem(IDC_BUTTON_kb_refresh)->SetWindowTextW(L"Start again");
        GetDlgItem(IDC_STATIC_OKQ)->SetWindowTextW(L"Are all keyboard buttons okay?");
        GetDlgItem(IDC_BUTTON_kb_yes)->SetWindowTextW(L"Yes");
        GetDlgItem(IDC_BUTTON_kb_no)->SetWindowTextW(L"No");
    }
    if (theApp.language == L"jp")
    {
        GetDlgItem(IDC_STATIC_PRESSED)->SetWindowTextW(L"すでに押されています");
        GetDlgItem(IDC_STATIC_NOT_PRESSED)->SetWindowTextW(L"まだ押されていません");
        GetDlgItem(IDC_BUTTON_kb_refresh)->SetWindowTextW(L"もう一度始める");
        GetDlgItem(IDC_STATIC_OKQ)->SetWindowTextW(L"キーボードのボタンはすべて大丈夫ですか？");
        GetDlgItem(IDC_BUTTON_kb_yes)->SetWindowTextW(L"はい");
        GetDlgItem(IDC_BUTTON_kb_no)->SetWindowTextW(L"いいえ");
    }
    

    // Install the keyboard hook
    SetKeyboardHook();

    return FALSE;  // return TRUE unless you set the focus to a control
}

void KeyboardDlg::OnDestroy()
{
    KeyboardDlg::OnDestroy();

    // Uninstall the keyboard hook
    RemoveKeyboardHook();
}



BOOL KeyboardDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
    // Prevent F1 from triggering help
    return TRUE; // Suppress the default action
}



void KeyboardDlg::OnBnClickedButtonkbyes()
{
    // TODO: Add your control notification handler code here
    keyBoard_Status = 2;
    RemoveKeyboardHook();
    EndDialog(IDOK);
}


void KeyboardDlg::OnBnClickedButtonkbno()
{
    // TODO: Add your control notification handler code here
    keyBoard_Status = 3;
    RemoveKeyboardHook();
    EndDialog(IDOK);
}

void KeyboardDlg::OnClose()
{
    // Add your custom logic here
    //AfxMessageBox(L"Hello Test");
    RemoveKeyboardHook();
    //DestroyWindow(); // Properly destroy the dialog window
    CDialogEx::OnClose(); // Call the base class implementation
    //PostQuitMessage(0);
}

//void KeyboardDlg::OnCancel()
//{
//    //AfxMessageBox(L"Hello Test");
//    CDialogEx::OnClose(); // Call the base class implementation
//    //DestroyWindow(); // Properly destroy the dialog window
//}


void KeyboardDlg::OnBnClickedButtonkbrefresh()
{
    // TODO: Add your control notification handler code here
    keyBoard_Status = 1;
	allKeyNormal();
}

LRESULT CALLBACK KeyboardDlg:: LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KeyboardDlg dlg;
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* pKeyInfo = (KBDLLHOOKSTRUCT*)lParam;

        // Check if the Windows key is pressed
        if (pKeyInfo->vkCode == VK_LWIN || pKeyInfo->vkCode == VK_RWIN)
        {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
            {
                // Block the Windows key
                return 1; // Prevent further processing
            }
        }
    }

    // Pass the message to the next hook in the chain
    return CallNextHookEx(dlg.g_hKeyboardHook, nCode, wParam, lParam);
}

void KeyboardDlg::SetKeyboardHook()
{
    if (!g_hKeyboardHook)
    {
        g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
        if (!g_hKeyboardHook)
        {
            AfxMessageBox(_T("Failed to install keyboard hook!"));
        }
    }
}

void KeyboardDlg::RemoveKeyboardHook()
{
    if (g_hKeyboardHook)
    {
        UnhookWindowsHookEx(g_hKeyboardHook);
        g_hKeyboardHook = NULL;
    }
}


