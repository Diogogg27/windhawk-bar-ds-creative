// ==WindhawkMod==
// @id              dscreative-bar
// @name            Floating Launcher Bar
// @description     Barra de lançamento horizontal, minimalista e de flutuação livre. 20 atalhos com ícones originais, texturas procedurais, controle de opacidade e efeito Starfield no hover.
// @version         1.0.0
// @author          diogo
// @github          https://github.com/Diogogg27/windhawk-bar-ds-creative
// @homepage        https://github.com/Diogogg27/windhawk-bar-ds-creative
// @include         explorer.exe
// @compilerOptions -lcomctl32 -lshlwapi -lgdiplus -lgdi32 -ldwmapi -lole32 -lshell32 -ladvapi32
// ==/WindhawkMod==

// ==WindhawkModReadme==
// Floating Launcher Bar
// =====================
//
// Uma barra de lançamento horizontal, minimalista e de flutuação livre que
// vive sobre a área de trabalho do Windows 11.
//
// O que ela faz
// -------------
// - Fundo invisível por padrão: o painel aparece apenas quando o mouse passa
// - Efeito Starfield no hover: luz orbitando a borda + grade de pixels + halo
// - Arraste para qualquer lugar; a posição volta depois de reiniciar
// - 10 texturas procedurais, desenhadas em código — nenhum arquivo de imagem
// - Opacidade ajustável de 10% a 100%, aplicável em tempo real
// - Grupos separados por linhas de 1px
//
// Ícones
// ------
// Este mod não distribui nenhum ícone. Os 20 ícones são marcas dos seus
// respectivos donos (Adobe, Google, Meta, Telegram, Perplexity...).
//
// Extraia-os dos programas instalados na sua máquina:
//
//   powershell -ExecutionPolicy Bypass -File extrair-icones.ps1
//
// e aponte a configuração "Pasta de ícones" para a pasta resultante.
//
// Instalação
// ----------
// Windhawk > Mods > Create new mod > colar este arquivo > Compile.
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
// - Textura:
//     $name: Textura de fundo
//     $description: Aplicada ao painel que surge no hover
//     $type: choice
//     $options:
//       Nenhuma: 0
//       Vidro fosco: 1
//       Fibra de carbono: 2
//       Metal escovado: 3
//       Perfurado: 4
//       Linho: 5
//       Papel: 6
//       Diagonais: 7
//       Malha: 8
//       Granulado: 9
//     $default: 0
// - Opacidade:
//     $name: Opacidade da barra
//     $description: 10 = quase invisível, 100 = totalmente opaco
//     $type: int
//     $min: 10
//     $max: 100
//     $default: 72
// - OpacidadeHover:
//     $name: Forçar 100% ao passar o mouse
//     $description: Ignora o slider enquanto o mouse está em cima
//     $type: bool
//     $default: true
// - EfeitoStarfield:
//     $name: Efeito Starfield no hover
//     $description: Luz na borda, grade de pixels e halo
//     $type: bool
//     $default: true
// - CorDivisoria:
//     $name: Cor da linha divisória
//     $type: color
//     $default: "#FFFFFF"
// - MostrarSempreVisivel:
//     $name: Mostrar em todas as áreas de trabalho
//     $type: bool
//     $default: true
// - PastaOpenCode:
//     $name: Pasta de trabalho do OpenCode
//     $type: string
//     $default: "H:\\DS CREATIVE"
// - PastaIcones:
//     $name: Pasta de ícones
//     $description: Pasta com os PNG gerados pelo extrair-icones.ps1
//     $type: string
//     $default: "%USERPROFILE%\\windhawk-bar-ds-creative\\icons"
// ==/WindhawkModSettings==

#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <gdiplus.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
#include <string>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// nem todo header do MinGW traz a família completa de APPCOMMAND
#ifndef APPCOMMAND_MEDIA_PREVIOUS_TRACK
#define APPCOMMAND_MEDIA_PREVIOUS_TRACK 11
#endif
#ifndef APPCOMMAND_MEDIA_NEXT_TRACK
#define APPCOMMAND_MEDIA_NEXT_TRACK 12
#endif
#ifndef APPCOMMAND_MEDIA_PLAY_PAUSE
#define APPCOMMAND_MEDIA_PLAY_PAUSE 14
#endif

// ---------------------------------------------------------------------------
// Tipos
// ---------------------------------------------------------------------------

enum LineIcon {
    LI_NONE = 0,
    LI_TRASH,
    LI_LOCK,
    LI_POWER,
    LI_PREV,
    LI_PLAY,
    LI_NEXT,
};

enum ButtonKind {
    BK_APP,    // ícone PNG de programa
    BK_LINE,   // ícone SVG desenhado (sistema / mídia)
    BK_ADOBE,  // abre o painel do Creative Cloud
};

struct Button {
    RECT rc{};
    ButtonKind kind = BK_APP;
    std::wstring iconKey;      // chave do PNG, ex. L"chrome"
    int lineIcon = LI_NONE;
    std::function<void()> onClick;
};

// ---------------------------------------------------------------------------
// Estado global
// ---------------------------------------------------------------------------

static HINSTANCE g_hInst = nullptr;
static HANDLE    g_thread = nullptr;
static DWORD     g_threadId = 0;

static HWND g_hwnd    = nullptr;   // a barra
static HWND g_panel   = nullptr;   // painel do Adobe (criado sob demanda)
static int  g_idxAdobe = -1;       // índice do botão Creative Cloud na barra

static std::vector<Button> g_buttons;
static std::vector<Button> g_panelButtons;

static bool   g_hover      = false;
static double g_reveal     = 0.0;   // 0 repouso .. 1 hover completo
static bool   g_running    = true;

static int g_barW = 0;
static int g_barH = 0;

// configurações
static int       g_textura    = 0;
static int       g_opacidade  = 72;
static bool      g_forcar100  = true;
static bool      g_starfield  = true;
static COLORREF  g_corDiv     = RGB(255, 255, 255);
static bool      g_todasAreas = true;
static std::wstring g_pastaOpenCode = L"H:\\DS CREATIVE";
static std::wstring g_pastaIcones;

// GDI+
static ULONG_PTR g_gdiplusToken = 0;
static std::map<std::wstring, Gdiplus::Bitmap*> g_icons;
static Gdiplus::Bitmap* g_texture = nullptr;
static int g_textureId = -1;
static UINT g_textureW = 0, g_textureH = 0;

// ---------------------------------------------------------------------------
// Utilidades
// ---------------------------------------------------------------------------

static bool PtIn(const RECT& r, POINT p) {
    return p.x >= r.left && p.x < r.right && p.y >= r.top && p.y < r.bottom;
}

// expande %VARIAVEL% de um caminho
static std::wstring Expandir(const std::wstring& in) {
    if (in.empty()) return in;
    wchar_t buf[MAX_PATH * 2] = {};
    DWORD n = ExpandEnvironmentStringsW(in.c_str(), buf, ARRAYSIZE(buf));
    return n > 0 ? std::wstring(buf) : in;
}

static int Clamp(int v, int lo, int hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

// alpha em uso para o fundo (0..255), considerando opacidade e hover
static int AlphaFundo() {
    int base = g_forcar100 && g_hover ? 100 : g_opacidade;
    return Clamp(base, 5, 100) * 255 / 100;
}

// ---------------------------------------------------------------------------
// Registro: posição persistida
// ---------------------------------------------------------------------------

static const wchar_t* kRegPath = L"Software\\Windhawk\\Engine\\Mods\\dscreative-bar";

static void SalvarPosicao(int x, int y) {
    HKEY key = nullptr;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, kRegPath, 0, nullptr, 0,
                        KEY_SET_VALUE, nullptr, &key, nullptr) != ERROR_SUCCESS)
        return;
    DWORD vx = (DWORD)x, vy = (DWORD)y;
    RegSetValueExW(key, L"PosicaoX", 0, REG_DWORD, (const BYTE*)&vx, sizeof(vx));
    RegSetValueExW(key, L"PosicaoY", 0, REG_DWORD, (const BYTE*)&vy, sizeof(vy));
    RegCloseKey(key);
}

static bool LerPosicao(int& x, int& y) {
    HKEY key = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, kRegPath, 0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
        return false;
    DWORD vx = 0, vy = 0, type = 0, size = sizeof(DWORD);
    bool okX = RegQueryValueExW(key, L"PosicaoX", 0, &type, (LPBYTE)&vx, &size) == ERROR_SUCCESS && type == REG_DWORD;
    size = sizeof(DWORD);
    bool okY = RegQueryValueExW(key, L"PosicaoY", 0, &type, (LPBYTE)&vy, &size) == ERROR_SUCCESS && type == REG_DWORD;
    RegCloseKey(key);
    if (!okX || !okY) return false;
    x = (int)vx; y = (int)vy;
    return true;
}

// ---------------------------------------------------------------------------
// Configurações do mod
// ---------------------------------------------------------------------------

static void CarregarConfig() {
    // nesta versão do Windhawk não existe Wh_GetBoolSetting:
    // bools voltam como int via Wh_GetIntSetting
    g_textura    = Wh_GetIntSetting(L"Textura");
    g_opacidade  = Clamp(Wh_GetIntSetting(L"Opacidade", 72), 10, 100);
    g_forcar100  = Wh_GetIntSetting(L"OpacidadeHover") != 0;
    g_starfield  = Wh_GetIntSetting(L"EfeitoStarfield") != 0;
    g_corDiv     = (COLORREF)Wh_GetIntSetting(L"CorDivisoria", RGB(255, 255, 255));
    g_todasAreas = Wh_GetIntSetting(L"MostrarSempreVisivel") != 0;

    PCWSTR s = Wh_GetStringSetting(L"PastaOpenCode");
    g_pastaOpenCode = (s && *s) ? s : L"H:\\DS CREATIVE";
    Wh_FreeStringSetting(s);

    s = Wh_GetStringSetting(L"PastaIcones");
    g_pastaIcones = Expandir(s ? s : L"");
    Wh_FreeStringSetting(s);
}

// ---------------------------------------------------------------------------
// Ícones: PNG carregados da pasta configurada (o mod não embute marca nenhuma)
// ---------------------------------------------------------------------------

static void LiberarIcones() {
    for (auto& kv : g_icons) delete kv.second;
    g_icons.clear();
}

static void CarregarIcones() {
    LiberarIcones();
    if (g_pastaIcones.empty()) return;

    static const wchar_t* chaves[] = {
        L"oc", L"cc", L"fg", L"comet", L"chrome", L"telegram", L"whatsapp",
        L"neverwrite", L"arena", L"onecommander", L"alphaxiv", L"maple",
        L"notepad", L"ps", L"ai", L"ae", L"pr", L"lr",
    };

    for (const wchar_t* k : chaves) {
        std::wstring caminho = g_pastaIcones + L"\\" + k + L".png";
        if (GetFileAttributesW(caminho.c_str()) == INVALID_FILE_ATTRIBUTES) continue;
        Gdiplus::Bitmap* bmp = Gdiplus::Bitmap::FromFile(caminho.c_str(), FALSE);
        if (!bmp || bmp->GetLastStatus() != Gdiplus::Ok) { delete bmp; continue; }
        g_icons[k] = bmp;
    }
}

// ---------------------------------------------------------------------------
// Texturas procedurais — desenhadas em GDI+, nenhum arquivo externo
// ---------------------------------------------------------------------------

static void LiberarTextura() {
    delete g_texture;
    g_texture = nullptr;
    g_textureId = -1;
    g_textureW = g_textureH = 0;
}

// pseudo-aleatório determinístico em [0,1) — igual ao Math.floor do original
static float Ruido(int i, int salt) {
    float x = std::sin((i + 1) * 12.9898f + salt * 78.233f) * 43758.5453f;
    return x - std::floor(x);
}

static Gdiplus::Bitmap* GerarTextura(int id, UINT w, UINT h) {
    using namespace Gdiplus;

    Bitmap* bmp = new Bitmap((INT)w, (INT)h, PixelFormat32bppARGB);
    if (bmp->GetLastStatus() != Ok) { delete bmp; return nullptr; }
    Graphics g(bmp);
    g.SetSmoothingMode(SmoothingModeAntiAlias);

    const BYTE BR = 13, BG = 17, BB = 23;   // base escura neutra
    SolidBrush base(Color(255, BR, BG, BB));
    g.FillRectangle(&base, 0, 0, (INT)w, (INT)h);

    switch (id) {
    case 1: { // Vidro fosco — gradiente diagonal claro
        LinearGradientBrush br(PointF(0, 0), PointF((REAL)w, (REAL)h),
                               Color(255, 34, 41, 52), Color(255, 17, 21, 28));
        g.FillRectangle(&br, 0, 0, (INT)w, (INT)h);
        break;
    }
    case 2: { // Fibra de carbono — duas tramas cruzadas a 45°
        SolidBrush claro(Color(255, 44, 51, 62));
        SolidBrush escuro(Color(255, 8, 10, 14));
        for (INT y = -((INT)h); y < (INT)w; y += 8) {
            for (INT x = -((INT)h); x < (INT)w; x += 8) {
                if (((x + y) / 8) % 2 == 0)
                    g.FillRectangle(&claro, x, y, 4, 4);
                else
                    g.FillRectangle(&escuro, x + 4, y + 4, 4, 4);
            }
        }
        break;
    }
    case 3: { // Metal escovado — linhas horizontais + brilho lateral
        SolidBrush linha(Color(255, 30, 35, 43));
        for (UINT y = 0; y < h; y += 3) g.FillRectangle(&linha, 0, (INT)y, (INT)w, 1);
        LinearGradientBrush br(PointF(0, 0), PointF((REAL)w, 0),
                               Color(40, 255, 255, 255), Color(0, 255, 255, 255));
        g.FillRectangle(&br, 0, 0, (INT)w, (INT)h);
        break;
    }
    case 4: { // Perfurado — grade de pontos com brilho 1px deslocado
        SolidBrush pto(Color(255, 6, 8, 11));
        SolidBrush hi(Color(70, 255, 255, 255));
        for (UINT y = 6; y < h; y += 9)
            for (UINT x = 6; x < w; x += 9) {
                g.FillEllipse(&hi, (INT)x - 3, (INT)y - 4, 7, 7);
                g.FillEllipse(&pto, (INT)x - 3, (INT)y - 3, 7, 7);
            }
        break;
    }
    case 5: { // Linho — trama cruzada de 1px a cada 2px
        SolidBrush v(Color(255, 24, 28, 35));
        SolidBrush o(Color(255, 10, 13, 17));
        for (UINT x = 0; x < w; x += 2) g.FillRectangle(&v, (INT)x, 0, 1, (INT)h);
        for (UINT y = 0; y < h; y += 2) g.FillRectangle(&o, 0, (INT)y, (INT)w, 1);
        break;
    }
    case 6: { // Papel — grão fino irregular
        for (UINT y = 0; y < h; y++)
            for (UINT x = 0; x < w; x++) {
                float n = Ruido((int)(y * w + x), 7);
                if (n < 0.5f) continue;
                int d = (int)((n - 0.5f) * 60.0f);
                bmp->SetPixel((INT)x, (INT)y,
                              Color(255, (BYTE)Clamp(BR + d, 0, 255),
                                    (BYTE)Clamp(BG + d, 0, 255),
                                    (BYTE)Clamp(BB + d, 0, 255)));
            }
        break;
    }
    case 7: { // Diagonais — listras de 2px a cada 7px a 135°
        Pen p(Color(255, 36, 42, 52), 2);
        for (INT x = -((INT)h); x < (INT)w + (INT)h; x += 7)
            g.DrawLine(&p, x, 0, x + (INT)h, (INT)h);
        break;
    }
    case 8: { // Malha — grade quadriculada de 1px a cada 9px
        Pen p(Color(255, 38, 44, 54), 1);
        for (UINT x = 0; x <= w; x += 9) g.DrawLine(&p, (INT)x, 0, (INT)x, (INT)h);
        for (UINT y = 0; y <= h; y += 9) g.DrawLine(&p, 0, (INT)y, (INT)w, (INT)y);
        break;
    }
    case 9: { // Granulado — ruído de película
        for (UINT y = 0; y < h; y++)
            for (UINT x = 0; x < w; x++) {
                float n = Ruido((int)(y * w + x), 13);
                int d = (int)((n - 0.5f) * 90.0f);
                BYTE r = (BYTE)Clamp(BR + d, 0, 255);
                BYTE gg = (BYTE)Clamp(BG + d, 0, 255);
                BYTE b = (BYTE)Clamp(BB + d, 0, 255);
                bmp->SetPixel((INT)x, (INT)y, Color(255, r, gg, b));
            }
        break;
    }
    default:
        break;
    }
    return bmp;
}

static Gdiplus::Bitmap* TexturaAtual(UINT w, UINT h) {
    if (g_textura <= 0) return nullptr;
    if (g_texture && g_textureId == g_textura && g_textureW == w && g_textureH == h)
        return g_texture;
    LiberarTextura();
    g_texture = GerarTextura(g_textura, w, h);
    g_textureId = g_textura;
    g_textureW = w;
    g_textureH = h;
    return g_texture;
}

// ---------------------------------------------------------------------------
// Ações de lançamento
// ---------------------------------------------------------------------------

static void AbrirShell(const std::wstring& alvo,
                       const std::wstring& args = std::wstring(),
                       const std::wstring& dir = std::wstring()) {
    if (alvo.empty()) return;
    ShellExecuteW(nullptr, L"open", alvo.c_str(),
                  args.empty() ? nullptr : args.c_str(),
                  dir.empty() ? nullptr : dir.c_str(),
                  SW_SHOWNORMAL);
}

// Varre "raiz\padrao" e devolve "raiz\<pasta mais recente>\<relativo>".
// Necessário porque Figma e WhatsApp guardam a versão no nome da pasta.
static std::wstring MaisRecente(const std::wstring& raiz,
                                const std::wstring& padrao,
                                const std::wstring& relativo) {
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((raiz + L"\\" + padrao).c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return std::wstring();

    std::wstring melhor;
    FILETIME melhorT{};
    do {
        if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) continue;
        if (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0) continue;

        std::wstring cand = raiz + L"\\" + fd.cFileName;
        if (!relativo.empty()) cand += L"\\" + relativo;
        if (GetFileAttributesW(cand.c_str()) == INVALID_FILE_ATTRIBUTES) continue;

        if (melhor.empty() || CompareFileTime(&fd.ftLastWriteTime, &melhorT) > 0) {
            melhor = cand;
            melhorT = fd.ftLastWriteTime;
        }
    } while (FindNextFileW(h, &fd));
    FindClose(h);
    return melhor;
}

static void AbrirFigma() {
    std::wstring exe = MaisRecente(Expandir(L"%LOCALAPPDATA%\\Figma"), L"app-*", L"Figma.exe");
    if (exe.empty()) {
        // alias da loja / versão já conhecida
        exe = Expandir(L"%LOCALAPPDATA%\\Figma\\Figma.exe");
    }
    AbrirShell(exe);
}

static void AbrirWhatsApp() {
    // App User Model ID: o Windows lança o app da Store por ele, sem depender
    // de caminho de arquivo. A pasta WindowsApps é ilegível para usuário comum,
    // então procurar o .exe por varredura falharia — e o alias da Store nem
    // sempre existe.
    const wchar_t* aumid = L"5319275A.WhatsAppDesktop_cv1g1gvanyjgm!App";

    std::wstring args = L"shell:AppsFolder\\";
    args += aumid;
    AbrirShell(Expandir(L"%WINDIR%\\explorer.exe"), args);
}

static void AbrirOpenCode() {
    std::wstring wt = Expandir(L"%LOCALAPPDATA%\\Microsoft\\WindowsApps\\wt.exe");
    if (GetFileAttributesW(wt.c_str()) == INVALID_FILE_ATTRIBUTES)
        wt = L"wt.exe";   // deixa o Shell resolver

    const wchar_t* opencode =
        L"C:\\Users\\diogo\\AppData\\Roaming\\npm\\node_modules\\@opencode\\cli\\bin\\opencode.exe";

    std::wstring pasta = g_pastaOpenCode.empty() ? L"H:\\DS CREATIVE" : g_pastaOpenCode;
    if (GetFileAttributesW(pasta.c_str()) == INVALID_FILE_ATTRIBUTES) {
        wchar_t meu[MAX_PATH] = {};
        GetEnvironmentVariableW(L"USERPROFILE", meu, MAX_PATH);
        pasta = meu;
    }

    // sem elevação: o usuário não é administrador e o UAC pediria senha toda vez
    std::wstring args = L"powershell -NoExit -Command \"Set-Location '" + pasta +
                        L"'; & '" + opencode + L"' --continue\"";
    AbrirShell(wt, args);
}

// ---------------------------------------------------------------------------
// Ações do sistema
// ---------------------------------------------------------------------------

static bool Confirmar(const wchar_t* titulo, const wchar_t* texto) {
    return MessageBoxW(g_hwnd, texto, titulo,
                       MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES;
}

static void EsvaziarLixeira() {
    if (!Confirmar(L"Esvaziar lixeira",
                   L"Esvaziar permanentemente todos os itens da lixeira?"))
        return;
    SHEmptyRecycleBinW(nullptr, nullptr,
                       SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

static void Bloquear() {
    LockWorkStation();
}

static void HabilitarShutdown() {
    HANDLE tok = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &tok))
        return;
    TOKEN_PRIVILEGES tp{};
    if (LookupPrivilegeValueW(nullptr, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid)) {
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(tok, FALSE, &tp, 0, nullptr, nullptr);
    }
    CloseHandle(tok);
}

static void Desligar() {
    if (!Confirmar(L"Desligar o computador",
                   L"Desligar o computador em 30 segundos?"))
        return;
    HabilitarShutdown();
    InitiateSystemShutdownExW(nullptr, const_cast<LPWSTR>(L"O computador vai desligar em 30 segundos."),
                              30, TRUE, FALSE,
                              SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_OTHER);
}

// ---------------------------------------------------------------------------
// Mídia — WM_APPCOMMAND para a janela em primeiro plano
// ---------------------------------------------------------------------------

static void Midia(int comando) {
    HWND alvo = GetForegroundWindow();
    if (!alvo) return;
    PostMessageW(alvo, WM_APPCOMMAND, (WPARAM)alvo, MAKELPARAM(0, comando));
}

// ---------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------

static const int SLOT        = 30;   // lado de cada botão
static const int PAD_X       = 8;
static const int PAD_Y       = 7;
static const int GAP         = 3;
static const int SEP_W       = 1;
static const int SEP_H       = 18;
static const int SEP_MARGEM  = 5;
static const int RAIO        = 10;   // cantos arredondados da barra

static const int PANEL_TILE  = 40;
static const int PANEL_GAP   = 4;
static const int PANEL_PAD   = 9;
static const int PANEL_LABEL = 14;
static const int PANEL_RAIO  = 12;

static std::vector<int> g_seps;      // posição X (centro) de cada divisória

static void AbrirPainel();   // definido mais abaixo, junto às janelas

// --- grupos -------------------------------------------------------------
static void AddIcon(std::vector<Button>& v, const wchar_t* key,
                    std::function<void()> fn, ButtonKind kind = BK_APP) {
    Button b;
    b.kind = kind;
    b.iconKey = key;
    b.onClick = std::move(fn);
    v.push_back(b);
}

static void AddLine(std::vector<Button>& v, int li, std::function<void()> fn) {
    Button b;
    b.kind = BK_LINE;
    b.lineIcon = li;
    b.onClick = std::move(fn);
    v.push_back(b);
}

struct Grupo {
    const wchar_t* nome;
    size_t inicio;
    size_t fim;   // exclusivo
};

static std::vector<Grupo> g_grupos;

static void MonteBarra() {
    g_buttons.clear();
    g_seps.clear();
    g_grupos.clear();

    // --- A: OpenCode ---
    size_t a0 = g_buttons.size();
    AddIcon(g_buttons, L"oc", [] { AbrirOpenCode(); });

    // --- B: Adobe + Figma ---
    size_t b0 = g_buttons.size();
    AddIcon(g_buttons, L"cc", [] { AbrirPainel(); }, BK_ADOBE);
    AddIcon(g_buttons, L"fg", [] { AbrirFigma(); });

    // --- C: favoritos ---
    size_t c0 = g_buttons.size();
    AddIcon(g_buttons, L"comet", [] {
        AbrirShell(L"C:\\Program Files\\Perplexity\\Comet\\Application\\comet.exe"); });
    AddIcon(g_buttons, L"chrome", [] {
        AbrirShell(L"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe"); });
    AddIcon(g_buttons, L"telegram", [] {
        AbrirShell(L"D:\\Telegram Desktop\\Telegram.exe"); });
    AddIcon(g_buttons, L"whatsapp", [] { AbrirWhatsApp(); });
    AddIcon(g_buttons, L"neverwrite", [] {
        AbrirShell(L"C:\\Program Files\\NeverWrite\\NeverWrite.exe"); });
    AddIcon(g_buttons, L"arena", [] {
        AbrirShell(L"C:\\Program Files\\Design Arena\\pake-designarena.exe"); });
    AddIcon(g_buttons, L"onecommander", [] {
        AbrirShell(L"C:\\Program Files\\OneCommander\\OneCommander.exe"); });
    AddIcon(g_buttons, L"alphaxiv", [] {
        AbrirShell(L"https://www.alphaxiv.org/"); });
    AddIcon(g_buttons, L"maple", [] {
        AbrirShell(L"https://chromewebstore.google.com/detail/lgncmpklmepncbjpiebhdoejhmbcnjad"); });
    AddIcon(g_buttons, L"notepad", [] {
        AbrirShell(L"C:\\Windows\\System32\\notepad.exe"); });

    // --- D: sistema ---
    size_t d0 = g_buttons.size();
    AddLine(g_buttons, LI_TRASH, [] { EsvaziarLixeira(); });
    AddLine(g_buttons, LI_LOCK,  [] { Bloquear(); });
    AddLine(g_buttons, LI_POWER, [] { Desligar(); });

    // --- E: mídia ---
    size_t e0 = g_buttons.size();
    AddLine(g_buttons, LI_PREV,  [] { Midia(APPCOMMAND_MEDIA_PREVIOUS_TRACK); });
    AddLine(g_buttons, LI_PLAY,  [] { Midia(APPCOMMAND_MEDIA_PLAY_PAUSE); });
    AddLine(g_buttons, LI_NEXT,  [] { Midia(APPCOMMAND_MEDIA_NEXT_TRACK); });

    size_t fim = g_buttons.size();

    g_grupos.push_back({ L"OpenCode", a0, b0 });
    g_grupos.push_back({ L"Adobe",    b0, c0 });
    g_grupos.push_back({ L"Favoritos", c0, d0 });
    g_grupos.push_back({ L"Sistema",  d0, e0 });
    g_grupos.push_back({ L"Mídia",    e0, fim });

    // --- posicionamento ---
    int x = PAD_X;
    for (size_t gi = 0; gi < g_grupos.size(); gi++) {
        const Grupo& gr = g_grupos[gi];
        for (size_t i = gr.inicio; i < gr.fim; i++) {
            auto& b = g_buttons[i];
            b.rc = { x, PAD_Y, x + SLOT, PAD_Y + SLOT };
            x += SLOT;
            if (i + 1 < gr.fim) x += GAP;
        }
        if (gi + 1 < g_grupos.size()) {
            x += SEP_MARGEM;
            g_seps.push_back(x);
            x += SEP_W + SEP_MARGEM;
        }
    }

    g_barW = x + PAD_X;
    g_barH = PAD_Y * 2 + SLOT;

    // índice do Creative Cloud, para posicionar o painel acima dele
    g_idxAdobe = -1;
    for (size_t i = 0; i < g_buttons.size(); i++) {
        if (g_buttons[i].kind == BK_ADOBE) { g_idxAdobe = (int)i; break; }
    }
}

static void MontePainel() {
    g_panelButtons.clear();

    struct Adobe { const wchar_t* key; const wchar_t* rot; std::function<void()> fn; };
    const Adobe itens[] = {
        { L"ps", L"Photoshop", [] { AbrirShell(L"D:\\Programas ADOBE\\Adobe Photoshop 2026\\Photoshop.exe"); } },
        { L"ai", L"Illustrator", [] { AbrirShell(L"D:\\Programas ADOBE\\Adobe Illustrator 2026\\Support Files\\Contents\\Windows\\Illustrator.exe"); } },
        { L"ae", L"After Effects", [] { AbrirShell(L"D:\\Programas ADOBE\\Adobe After Effects 2026\\Support Files\\AfterFX.exe"); } },
        { L"pr", L"Premiere", [] { AbrirShell(L"D:\\Programas ADOBE\\Adobe Premiere Pro 2026\\Adobe Premiere Pro.exe"); } },
        { L"lr", L"Lightroom", [] { AbrirShell(L"D:\\Programas ADOBE\\Adobe Lightroom CC\\lightroom.exe"); } },
    };

    int x = PANEL_PAD;
    for (const auto& it : itens) {
        Button b;
        b.kind = BK_APP;
        b.iconKey = it.key;
        b.onClick = it.fn;
        b.rc = { x, PANEL_PAD, x + PANEL_TILE, PANEL_PAD + PANEL_TILE };
        g_panelButtons.push_back(b);
        x += PANEL_TILE + PANEL_GAP;
    }
}

static int PainelLargura() {
    return PANEL_PAD * 2 + 5 * PANEL_TILE + 4 * PANEL_GAP;
}

static int PainelAltura() {
    return PANEL_PAD * 2 + PANEL_TILE + 4 + PANEL_LABEL;
}

// ---------------------------------------------------------------------------
// Desenho
// ---------------------------------------------------------------------------

// rounded rectangle em sentido horário
static void AddRaio(Gdiplus::GraphicsPath& p, const Gdiplus::RectF& r, Gdiplus::REAL rad) {
    using namespace Gdiplus;
    REAL rr = rad;
    if (rr > r.Width / 2) rr = r.Width / 2;
    if (rr > r.Height / 2) rr = r.Height / 2;
    p.AddArc(r.X, r.Y, rr * 2, rr * 2, 180, 90);
    p.AddArc(r.GetRight() - rr * 2, r.Y, rr * 2, rr * 2, 270, 90);
    p.AddArc(r.GetRight() - rr * 2, r.GetBottom() - rr * 2, rr * 2, rr * 2, 0, 90);
    p.AddArc(r.X, r.GetBottom() - rr * 2, rr * 2, rr * 2, 90, 90);
    p.CloseFigure();
}

// percorre o contorno arredondado por comprimento de arco
// (port de pointOnRoundRect — Originkit Starfield Button)
static Gdiplus::PointF PontoNoContorno(float t, float w, float h, float r) {
    using namespace Gdiplus;
    float rr = (std::max)(0.0f, (std::min)(r, (std::min)(w / 2, h / 2)));
    float sx = (std::max)(0.0f, w - 2 * rr);
    float sy = (std::max)(0.0f, h - 2 * rr);
    float arc = (float)(M_PI / 2.0) * rr;
    float total = 2 * sx + 2 * sy + 4 * arc;
    if (total <= 0) return PointF(w / 2, h / 2);

    float d = (t - (float)(int)t);
    if (d < 0) d += 1.0f;
    d = d * total + sx / 2;
    while (d > total) d -= total;

    if (d < sx) return PointF(rr + d, 0);
    d -= sx;
    if (d < arc) { float a = d / rr; return PointF(w - rr + rr * (float)sin(a), rr - rr * (float)cos(a)); }
    d -= arc;
    if (d < sy) return PointF(w, rr + d);
    d -= sy;
    if (d < arc) { float a = d / rr; return PointF(w - rr + rr * (float)cos(a), h - rr + rr * (float)sin(a)); }
    d -= arc;
    if (d < sx) return PointF(w - rr - d, h);
    d -= sx;
    if (d < arc) { float a = d / rr; return PointF(rr - rr * (float)sin(a), h - rr + rr * (float)cos(a)); }
    d -= arc;
    if (d < sy) return PointF(0, h - rr - d);
    d -= sy;
    float a = d / rr;
    return PointF(rr - rr * (float)cos(a), rr - rr * (float)sin(a));
}

// fundo: chapada ou textura, com alpha controlado (ícones ficam nítidos)
static void DesenharFundo(Gdiplus::Graphics& g, int w, int h, int rv) {
    using namespace Gdiplus;
    if (rv <= 0) return;

    const float efetivo = (float)rv * AlphaFundo() / 255.0f;
    if (efetivo <= 0.004f) return;

    Bitmap* tex = TexturaAtual((UINT)w, (UINT)h);
    GraphicsState st = g.Save();

    if (tex) {
        ColorMatrix cm{};
        cm.m[0][0] = 1; cm.m[1][1] = 1; cm.m[2][2] = 1;
        cm.m[3][3] = efetivo;
        cm.m[4][4] = 1;
        ImageAttributes ia;
        ia.SetColorMatrix(&cm, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
        g.DrawImage(tex, Rect(0, 0, w, h), 0, 0, (INT)tex->GetWidth(), (INT)tex->GetHeight(),
                    UnitPixel, &ia);
    } else {
        BYTE a = (BYTE)(efetivo * 255);
        SolidBrush br(Color(a, 10, 13, 18));
        GraphicsPath path;
        AddRaio(path, RectF(0, 0, (REAL)w, (REAL)h), (REAL)RAIO);
        g.FillPath(&br, &path);
    }
    g.Restore(st);
}

// efeito Starfield: grade de pixels + luz na borda + halo (Originkit)
static void DesenharStarfield(Gdiplus::Graphics& g, int w, int h, float rv) {
    using namespace Gdiplus;
    if (!g_starfield || rv <= 0.004f) return;

    const float t = (float)GetTickCount() / 1000.0f;

    // ---- grade de pixels ------------------------------------------------
    {
        const int cell = 4;
        const int dens = 50;
        int cols = (std::max)(1, w / cell);
        int rows = (std::max)(1, h / cell);
        int offX = (w - cols * cell) / 2;
        int offY = (h - rows * cell) / 2;
        int dot = (std::max)(1, (int)(cell * 0.62f));
        float cx = w / 2.0f, cy = h / 2.0f;
        float maxD = std::sqrt(cx * cx + cy * cy);
        if (maxD < 1) maxD = 1;

        SolidBrush br(Color(255, 131, 255, 245));   // #83FFF5
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int i = r * cols + c;
                bool aceso = (Ruido(i, 1) * 100.0f) < (float)dens;
                float base = aceso ? 0.5f + Ruido(i, 2) * 0.5f
                                   : 0.05f + Ruido(i, 3) * 0.18f;
                float speed = 0.6f + Ruido(i, 4) * 2.4f;
                float phase = Ruido(i, 5) * 2.0f * (float)M_PI;

                float px = (float)offX + c * cell + cell / 2.0f;
                float py = (float)offY + r * cell + cell / 2.0f;

                float tw = 0.55f + 0.45f * (float)sin(t * speed + phase);
                float d = std::sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy)) / maxD;
                float centerBias = 0.55f + 0.45f * (1.0f - d);
                float a = base * tw * centerBias * rv;
                if (a <= 0.002f) continue;
                if (a > 1.0f) a = 1.0f;

                br.SetColor(Color((BYTE)(a * 255), 131, 255, 245));
                g.FillRectangle(&br, (INT)px - dot / 2, (INT)py - dot / 2, dot, dot);
            }
        }
    }

    // ---- luz orbitando a borda (recortada pro anel) ---------------------
    {
        const float BAND = 1.0f;
        const float THICK = 2.0f;
        const float ringInset = BAND / 2 - THICK / 2;      // = -0.5
        const float half = BAND / 2;

        float pw = (float)(w - 1);
        float ph = (float)(h - 1);
        float pr = (std::max)(0.0f, (float)RAIO - half);

        const float turnsPerSec = 0.2f;   // 1 volta a cada 5 s (speed 50)
        float base = t * turnsPerSec * -1.0f;   // ccw
        float tt = base - (float)(int)base;
        if (tt < 0) tt += 1.0f;

        PointF p = PontoNoContorno(tt, pw, ph, pr);
        float lx = p.X + half - ringInset;
        float ly = p.Y + half - ringInset;

        // anel = contorno externo menos interno
        GraphicsPath anel;
        AddRaio(anel, RectF(-(float)ringInset, -(float)ringInset,
                            (float)w + 2 * ringInset, (float)h + 2 * ringInset),
                (float)RAIO - ringInset);
        GraphicsPath furo;
        AddRaio(furo, RectF(THICK, THICK, (float)w - 2 * THICK, (float)h - 2 * THICK),
                (std::max)(0.0f, (float)RAIO - THICK));
        furo.Reverse();
        anel.AddPath(&furo, FALSE);
        anel.SetFillMode(FillModeAlternate);

        GraphicsState st = g.Save();
        g.SetClip(&anel);

        const float R = 48.0f;   // stroke.size / 2
        GraphicsPath circ;
        circ.AddEllipse(lx - R, ly - R, R * 2, R * 2);
        PathGradientBrush pb(&circ);
        pb.SetCenterPoint(PointF(lx, ly));
        pb.SetCenterColor(Color((BYTE)(rv * 240), 0, 239, 255));   // #00EFFF
        Color volta[1] = { Color(0, 0, 239, 255) };
        INT n = 1;
        pb.SetSurroundColors(volta, &n);
        g.FillEllipse(&pb, lx - R, ly - R, R * 2, R * 2);

        g.Restore(st);
    }

    // ---- halo interno (3 passagens simulando blur) ----------------------
    {
        GraphicsState st = g.Save();
        GraphicsPath base;
        AddRaio(base, RectF(1, 1, (REAL)w - 2, (REAL)h - 2), (REAL)RAIO);

        const struct { REAL larg; BYTE alfa; } passos[] = {
            { 9.0f, (BYTE)(rv * 34) },
            { 5.0f, (BYTE)(rv * 70) },
            { 3.0f, (BYTE)(rv * 190) },
        };
        for (const auto& ps : passos) {
            if (ps.alfa < 3) continue;
            Pen p(Color(ps.alfa, 0, 223, 255), ps.larg);   // #00DFFF
            p.SetLineJoin(LineJoinRound);
            g.DrawPath(&p, &base);
        }
        g.Restore(st);
    }
}

// ícone PNG original, centralizado e com proporção preservada
static void DesenharIcone(Gdiplus::Graphics& g, const RECT& rc, const std::wstring& chave) {
    using namespace Gdiplus;
    auto it = g_icons.find(chave);
    if (it == g_icons.end() || !it->second) return;

    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    int lado = (std::min)(w, h) - 6;
    if (lado < 4) return;

    RectF dest((REAL)(rc.left + (w - lado) / 2.0f),
               (REAL)(rc.top + (h - lado) / 2.0f),
               (REAL)lado, (REAL)lado);
    g.DrawImage(it->second, dest);
}

// ícone de linha: SVG de 24×24 traçado com 1,5px e pontas arredondadas
static void DesenharLinha(Gdiplus::Graphics& g, const RECT& rc, int icone) {
    using namespace Gdiplus;
    if (icone == LI_NONE) return;

    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;

    const REAL ALVO = 20.0f;
    REAL s = ALVO / 24.0f;
    REAL ox = (REAL)rc.left + (w - ALVO) / 2;
    REAL oy = (REAL)rc.top + (h - ALVO) / 2;

    GraphicsState st = g.Save();
    g.TranslateTransform(ox, oy);
    g.ScaleTransform(s, s);
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    g.SetPixelOffsetMode(PixelOffsetModeHalf);

    Pen p(Color(235, 255, 255, 255), 1.8f);   // 1.8 × (20/24) = 1,5px finais
    p.SetLineCap(LineCapRound, LineCapRound, DashCapRound);
    p.SetLineJoin(LineJoinRound);
    SolidBrush furo(Color(235, 255, 255, 255));

    switch (icone) {
    case LI_TRASH: {
        GraphicsPath path;
        path.StartFigure();
        path.AddLine(3, 6, 21, 6);                       // tampa
        GraphicsPath cabo;
        cabo.AddArc(9, 2, 6, 8, 180, 180);               // alça
        g.DrawPath(&p, &cabo);

        GraphicsPath corpo;
        corpo.StartFigure();
        corpo.AddLine(5, 6, 5, 19);
        corpo.AddArc(5, 17, 4, 4, 180, -90);             // canto inf. esq.
        corpo.AddLine(7, 21, 17, 21);
        corpo.AddArc(15, 17, 4, 4, 90, -90);             // canto inf. dir.
        corpo.AddLine(19, 19, 19, 6);
        corpo.CloseFigure();
        g.DrawPath(&p, &corpo);
        g.DrawPath(&p, &path);

        g.DrawLine(&p, 10, 11, 10, 17);
        g.DrawLine(&p, 14, 11, 14, 17);
        break;
    }
    case LI_LOCK: {
        GraphicsPath corpo;
        AddRaio(corpo, RectF(3, 11, 18, 11), 2);
        g.DrawPath(&p, &corpo);

        GraphicsPath arco;
        arco.StartFigure();
        arco.AddLine(7, 11, 7, 7);
        arco.AddArc(7, 2, 10, 10, 180, 180);
        arco.AddLine(17, 7, 17, 11);
        g.DrawPath(&p, &arco);
        break;
    }
    case LI_POWER: {
        GraphicsPath arco;
        arco.AddArc(3, 4, 18, 18, 300, 300);
        g.DrawPath(&p, &arco);
        g.DrawLine(&p, 12, 2, 12, 12);
        break;
    }
    case LI_PREV: {
        GraphicsPath tri;
        tri.AddLine(19, 20, 9, 12);
        tri.AddLine(9, 12, 19, 4);
        tri.CloseFigure();
        g.FillPath(&furo, &tri);
        g.DrawLine(&p, 5, 5, 5, 19);
        break;
    }
    case LI_PLAY: {
        GraphicsPath tri;
        tri.AddLine(5, 3, 19, 12);
        tri.AddLine(19, 12, 5, 21);
        tri.CloseFigure();
        g.FillPath(&furo, &tri);
        break;
    }
    case LI_NEXT: {
        GraphicsPath tri;
        tri.AddLine(5, 4, 15, 12);
        tri.AddLine(15, 12, 5, 20);
        tri.CloseFigure();
        g.FillPath(&furo, &tri);
        g.DrawLine(&p, 19, 5, 19, 19);
        break;
    }
    default:
        break;
    }

    g.Restore(st);
}

// divisórias de 1px entre os grupos
static void DesenharDivisorias(Gdiplus::Graphics& g) {
    using namespace Gdiplus;
    if (g_seps.empty()) return;
    Pen p(Color(90, GetRValue(g_corDiv), GetGValue(g_corDiv), GetBValue(g_corDiv)), 1.0f);
    int topo = PAD_Y + (SLOT - SEP_H) / 2;
    for (int x : g_seps) g.DrawLine(&p, x, topo, x, topo + SEP_H);
}

// rotina principal da barra
static void PintarBarra(Gdiplus::Graphics& g, int w, int h) {
    g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
    DesenharFundo(g, w, h, (int)(g_reveal * 255.0));
    DesenharStarfield(g, w, h, (float)g_reveal);
    DesenharDivisorias(g);

    for (const auto& b : g_buttons) {
        if (b.kind == BK_LINE) {
            DesenharLinha(g, b.rc, b.lineIcon);
        } else {
            DesenharIcone(g, b.rc, b.iconKey);
        }
    }
}

// rotina do painel do Adobe (visível só quando aberto, então sempre opaco)
static void PintarPainel(Gdiplus::Graphics& g, int w, int h) {
    using namespace Gdiplus;
    SolidBrush fundo(Color(238, 9, 12, 17));
    GraphicsPath base;
    AddRaio(base, RectF(0, 0, (REAL)w, (REAL)h), (REAL)PANEL_RAIO);
    g.FillPath(&fundo, &base);

    Pen borda(Color(40, 255, 255, 255), 1.0f);
    g.DrawPath(&borda, &base);

    FontFamily fam(L"Segoe UI");
    Font rot(&fam, 8.0f, FontStyleRegular, UnitPixel);
    SolidBrush corRot(Color(170, 255, 255, 255));
    StringFormat sf;
    sf.SetAlignment(StringAlignmentCenter);

    static const wchar_t* rotulos[] = {
        L"Photoshop", L"Illustrator", L"After FX", L"Premiere", L"Lightroom"
    };

    for (size_t i = 0; i < g_panelButtons.size(); i++) {
        const auto& b = g_panelButtons[i];
        DesenharIcone(g, b.rc, b.iconKey);

        if (i < _countof(rotulos)) {
            REAL cx = (REAL)((b.rc.left + b.rc.right) / 2.0f);
            REAL top = (REAL)b.rc.bottom + 4;
            g.DrawString(rotulos[i], -1, &rot, RectF(cx - 40, top, 80, (REAL)PANEL_LABEL),
                         &sf, &corRot);
        }
    }
}

// ---------------------------------------------------------------------------
// Composição por camadas — alpha por pixel
//
// O fundo é invisível no repouso, então a barra NÃO pode ser um retângulo
// sólido: usamos UpdateLayeredWindow, que respeita o alpha de cada pixel e
// deixa o mouse atravessar automaticamente onde não foi pintado.
// ---------------------------------------------------------------------------

static bool Compor(HWND hwnd, int w, int h, bool ehPainel) {
    using namespace Gdiplus;
    if (!hwnd || w <= 0 || h <= 0) return false;

    Bitmap bmp(w, h, PixelFormat32bppPARGB);
    if (bmp.GetLastStatus() != Ok) return false;

    {
        Graphics g(&bmp);
        g.SetCompositingQuality(CompositingQualityHighQuality);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        g.SetPixelOffsetMode(PixelOffsetModeHalf);
        if (ehPainel) PintarPainel(g, w, h);
        else PintarBarra(g, w, h);
    }

    BitmapData bd{};
    Rect rc(0, 0, w, h);
    if (bmp.LockBits(&rc, ImageLockModeRead, PixelFormat32bppPARGB, &bd) != Ok)
        return false;

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;          // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    HDC screen = GetDC(nullptr);
    void* pixels = nullptr;
    HBITMAP dib = CreateDIBSection(screen, &bmi, DIB_RGB_COLORS, &pixels, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!dib || !pixels) {
        bmp.UnlockBits(&bd);
        if (dib) DeleteObject(dib);
        return false;
    }

    const int linha = w * 4;
    for (int y = 0; y < h; y++)
        memcpy((BYTE*)pixels + (size_t)y * linha,
               (BYTE*)bd.Scan0 + (ptrdiff_t)y * bd.Stride, linha);
    bmp.UnlockBits(&bd);

    HDC mem = CreateCompatibleDC(nullptr);
    if (!mem) { DeleteObject(dib); return false; }
    HGDIOBJ antigo = SelectObject(mem, dib);

    RECT wr{};
    GetWindowRect(hwnd, &wr);
    POINT ptDst{ wr.left, wr.top };
    POINT ptSrc{ 0, 0 };
    SIZE sz{ w, h };

    BLENDFUNCTION bf{};
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;
    bf.AlphaFormat = AC_SRC_ALPHA;

    BOOL ok = UpdateLayeredWindow(hwnd, nullptr, &ptDst, &sz, mem, &ptSrc, 0, &bf, ULW_ALPHA);

    SelectObject(mem, antigo);
    DeleteDC(mem);
    DeleteObject(dib);
    return ok != FALSE;
}

// ---------------------------------------------------------------------------
// Janelas
// ---------------------------------------------------------------------------

static const wchar_t* kClasseBarra  = L"DSCreativeBarClasse";
static const wchar_t* kClassePainel = L"DSCreativePainelClasse";
static const UINT WM_RECARGAR = WM_APP + 50;
static const UINT IDT_HOVER   = 1;

static POINT PontoMouse(HWND hwnd) {
    POINT pt{};
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    return pt;
}

static void FecharPainel() {
    if (!g_panel) return;
    HWND p = g_panel;
    g_panel = nullptr;
    DestroyWindow(p);
}

static void AbrirPainel() {
    if (g_panel) { FecharPainel(); return; }
    if (g_idxAdobe < 0 || !g_hwnd) return;

    const RECT& b = g_buttons[g_idxAdobe].rc;
    POINT tl{ b.left, b.top }, br{ b.right, b.bottom };
    ClientToScreen(g_hwnd, &tl);
    ClientToScreen(g_hwnd, &br);

    int pw = PainelLargura();
    int ph = PainelAltura();
    int px = (tl.x + br.x) / 2 - pw / 2;
    int py = tl.y - ph - 8;

    g_panel = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
                              kClassePainel, L"Adobe", WS_POPUP,
                              px, py, pw, ph, g_hwnd, nullptr, g_hInst, nullptr);
    if (!g_panel) return;

    ShowWindow(g_panel, SW_SHOWNOACTIVATE);
    Compor(g_panel, pw, ph, true);
}

static void PosicionarBarra() {
    if (!g_hwnd) return;

    RECT work{};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &work, 0);

    int x = 0, y = 0;
    bool ok = LerPosicao(x, y);

    if (ok) {
        POINT p{ x, y };
        HMONITOR mon = MonitorFromPoint(p, MONITOR_DEFAULTTONULL);
        if (!mon) ok = false;
        else {
            MONITORINFO mi{};
            mi.cbSize = sizeof(mi);
            GetMonitorInfoW(mon, &mi);
            if (x + g_barW > mi.rcWork.right || y + g_barH > mi.rcWork.bottom ||
                x < mi.rcWork.left || y < mi.rcWork.top)
                ok = false;
        }
    }

    if (!ok) {
        x = work.left + ((work.right - work.left) - g_barW) / 2;
        y = work.top + 28;
    }

    SetWindowPos(g_hwnd, HWND_TOPMOST, x, y, g_barW, g_barH,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
    Compor(g_hwnd, g_barW, g_barH, false);
}

// ---------------------------------------------------------------------------
// Procedimento da barra
// ---------------------------------------------------------------------------

static LRESULT CALLBACK BarraProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_ERASEBKGND:
        return 1;   // o conteúdo vem do UpdateLayeredWindow

    case WM_NCHITTEST: {
        POINT pt{ (short)LOWORD(lp), (short)HIWORD(lp) };
        for (const auto& b : g_buttons)
            if (PtIn(b.rc, pt)) return HTCLIENT;
        return HTCAPTION;      // arrastar a barra inteira
    }

    case WM_LBUTTONUP: {
        POINT pt = PontoMouse(hwnd);
        for (auto& b : g_buttons) {
            if (PtIn(b.rc, pt)) {
                if (b.onClick) b.onClick();
                return 0;
            }
        }
        return 0;
    }

    case WM_EXITSIZEMOVE: {
        RECT r{};
        GetWindowRect(hwnd, &r);
        SalvarPosicao(r.left, r.top);
        return 0;
    }

    case WM_TIMER: {
        if (wp != IDT_HOVER) break;

        POINT pt{};
        GetCursorPos(&pt);
        RECT wr{};
        GetWindowRect(hwnd, &wr);
        bool dentro = PtIn(wr, pt);

        // painel fecha sozinho quando o mouse sai dele e do botão Adobe
        if (g_panel) {
            RECT pr{};
            GetWindowRect(g_panel, &pr);
            bool noBotao = (g_idxAdobe >= 0) && [&] {
                RECT br{};
                const RECT& b = g_buttons[g_idxAdobe].rc;
                br = b;
                MapWindowPoints(hwnd, nullptr, (POINT*)&br, 2);
                return PtIn(br, pt);
            }();
            if (!PtIn(pr, pt) && !noBotao) FecharPainel();
        }

        bool mudou = false;
        if (dentro != g_hover) { g_hover = dentro; mudou = true; }

        double alvo = g_hover ? 1.0 : 0.0;
        bool animando = false;
        if (g_reveal < alvo - 0.001) { g_reveal = (std::min)(alvo, g_reveal + 50.0 / 600.0); animando = true; }
        else if (g_reveal > alvo + 0.001) { g_reveal = (std::max)(alvo, g_reveal - 50.0 / 600.0); animando = true; }

        if (mudou || animando) Compor(hwnd, g_barW, g_barH, false);

        // garante que a barra continue por cima
        if (g_todasAreas && (GetWindowLongPtrW(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST) == 0)
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

        break;
    }

    case WM_NCDESTROY:
        g_hwnd = nullptr;
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Procedimento do painel do Adobe
// ---------------------------------------------------------------------------

static LRESULT CALLBACK PainelProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_ERASEBKGND:
        return 1;

    case WM_NCHITTEST: {
        POINT pt{ (short)LOWORD(lp), (short)HIWORD(lp) };
        for (const auto& b : g_panelButtons)
            if (PtIn(b.rc, pt)) return HTCLIENT;
        return HTTRANSPARENT;
    }

    case WM_LBUTTONUP: {
        POINT pt = PontoMouse(hwnd);
        for (auto& b : g_panelButtons) {
            if (PtIn(b.rc, pt)) {
                auto fn = b.onClick;
                FecharPainel();
                if (fn) fn();
                return 0;
            }
        }
        FecharPainel();
        return 0;
    }

    case WM_NCDESTROY:
        g_panel = nullptr;
        break;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Thread própria com laço de mensagens
// ---------------------------------------------------------------------------

static DWORD WINAPI ThreadPrincipal(LPVOID) {
    g_hInst = nullptr;
    HMODULE self = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCWSTR)&ThreadPrincipal, &self))
        g_hInst = (HINSTANCE)self;

    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = g_hInst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);

    wc.lpfnWndProc = BarraProc;
    wc.lpszClassName = kClasseBarra;
    RegisterClassExW(&wc);

    wc.lpfnWndProc = PainelProc;
    wc.lpszClassName = kClassePainel;
    RegisterClassExW(&wc);

    g_hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
                             kClasseBarra, L"Floating Launcher Bar", WS_POPUP,
                             0, 0, g_barW, g_barH,
                             nullptr, nullptr, g_hInst, nullptr);
    if (!g_hwnd) return 1;

    SetTimer(g_hwnd, IDT_HOVER, 50, nullptr);
    PosicionarBarra();

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.message == WM_RECARGAR) {
            CarregarConfig();
            LiberarTextura();
            CarregarIcones();
            MonteBarra();
            MontePainel();
            if (g_panel) FecharPainel();
            SetWindowPos(g_hwnd, HWND_TOPMOST, 0, 0, g_barW, g_barH,
                         SWP_NOMOVE | SWP_NOACTIVATE);
            PosicionarBarra();
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_hwnd) { DestroyWindow(g_hwnd); g_hwnd = nullptr; }
    return 0;
}

// ---------------------------------------------------------------------------
// Ciclo de vida do mod
// ---------------------------------------------------------------------------

// O Windhawk localiza estes três por nome via GetProcAddress: precisam ser
// extern "C" (sem mangling) e explicitamente exportados.
extern "C" __declspec(dllexport) BOOL Wh_ModInit() {
    Gdiplus::GdiplusStartupInput gsi;
    if (Gdiplus::GdiplusStartup(&g_gdiplusToken, &gsi, nullptr) != Gdiplus::Ok)
        g_gdiplusToken = 0;

    CarregarConfig();
    CarregarIcones();
    MonteBarra();
    MontePainel();

    g_thread = CreateThread(nullptr, 0, ThreadPrincipal, nullptr, 0, &g_threadId);
    if (!g_thread) return FALSE;
    return TRUE;
}

extern "C" __declspec(dllexport) void Wh_ModUninit() {
    g_running = false;

    if (g_threadId) PostThreadMessageW(g_threadId, WM_QUIT, 0, 0);
    if (g_thread) {
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
        g_thread = nullptr;
        g_threadId = 0;
    }

    g_panel = nullptr;
    g_hwnd = nullptr;
    LiberarIcones();
    LiberarTextura();

    if (g_gdiplusToken) {
        Gdiplus::GdiplusShutdown(g_gdiplusToken);
        g_gdiplusToken = 0;
    }
}

extern "C" __declspec(dllexport) void Wh_ModSettingsChanged() {
    if (g_threadId) PostThreadMessageW(g_threadId, WM_RECARGAR, 0, 0);
    else { CarregarConfig(); CarregarIcones(); MonteBarra(); MontePainel(); }
}





