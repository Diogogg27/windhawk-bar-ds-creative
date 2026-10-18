// ==WindhawkMod==
// @id              dscreative-bar
// @name            Floating Launcher Bar
// @description     Barra de lançamento minimalista e de flutuação livre, deitada ou em pé. Temas de cor, escala ajustável, atalhos com ícones originais, texturas procedurais e controle de opacidade.
// @version         1.5.0
// @author          diogo
// @github          https://github.com/Diogogg27/windhawk-bar-ds-creative
// @homepage        https://github.com/Diogogg27/windhawk-bar-ds-creative
// @include         explorer.exe
// @compilerOptions -lcomctl32 -lshlwapi -lgdiplus -lgdi32 -ldwmapi -lole32 -lshell32 -ladvapi32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Floating Launcher Bar

Uma barra de atalhos que flutua sobre a área de trabalho do Windows 11: seus
programas, as ações do sistema e o controle de mídia em uma linha só. Traços
finos, ícones originais extraídos do seu próprio PC e nenhum emoji.

A barra fica onde você deixar e volta para o mesmo lugar depois de reiniciar.

Por padrão ela mora na área de trabalho: fica na frente do papel de parede e atrás
dos programas abertos. Nas configurações, **Ficar por cima das janelas** deixa ela
sempre à vista, sobre tudo.

## O que ela faz

- Deitada (672x44) ou em pé (46x671), com os separadores acompanhando
- Efeito magnético: os ícones crescem perto do cursor e voltam sozinhos
- 10 temas de cor prontos, mais um personalizado de três cores
- Escala de 70% a 150%, aplicada em tempo real
- 10 texturas procedurais, desenhadas em código — nenhum arquivo de imagem
- Opacidade de 10% a 100% só no fundo: os ícones ficam sempre nítidos
- Arraste para qualquer lugar, cole nas bordas, trave no lugar, mantenha na área
- Lista de atalhos de programas, editável, com o ícone extraído do próprio programa
- Painel do Creative Cloud, esvaziar lixeira, bloquear, desligar e mídia

## O efeito magnético

O ícone sob o cursor chega a 1,5 vez o tamanho; os vizinhos crescem menos, na
proporção da distância, e tudo se acomoda em cerca de um quinto de segundo. O
ícone cresce dentro da barra, então nenhum botão muda de lugar e o clique
continua caindo onde sempre caiu.

Três ajustes controlam: liga/desliga, **Força** (0 a 200%, 100 = 1,5 vez) e
**Alcance** (20 a 500 pixels).

## Atalhos de programas

O grupo **Atalhos de programas** das configurações é uma lista: cada item é um
atalho no formato

    Nome | Alvo | Ícone

O **alvo** pode ser um `.exe`, uma pasta, um documento, um site ou um programa
com argumentos entre aspas — como no Maple Bookmarks, que abre os seus favoritos
salvos numa janela do Comet:

    "C:\Program Files\Perplexity\Comet\Application\comet.exe" --app="chrome-extension://..."

O **ícone** é opcional: o nome de um PNG da pasta de ícones (`chrome`, `maple`,
`telegram`…) ou um arquivo de onde tirar o ícone. Em branco, o ícone é extraído
do próprio alvo.

O botão **+** acrescenta um atalho e a lixeira tira. Um item começando com `//`
fica desligado sem precisar ser apagado.

## Ícones

Este mod não distribui nenhum ícone. Os ícones são marcas dos seus respectivos
donos — Adobe, Google, Meta, Telegram, Perplexity e outros — e são extraídos dos
programas instalados na sua máquina:

    powershell -ExecutionPolicy Bypass -File extrair-icones.ps1

Depois aponte a configuração "Pasta de ícones" para a pasta resultante.

## Instalação

Windhawk > Mods > Create new mod > colar este arquivo > Compile.

Código, o README completo e o efeito Starfield avulso estão em:
https://github.com/Diogogg27/windhawk-bar-ds-creative
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- Textura: 0
  $name: Textura de fundo
  $description: Textura aplicada ao fundo da barra.
  $options:
  - 0: Nenhuma
  - 1: Vidro fosco
  - 2: Fibra de carbono
  - 3: Metal escovado
  - 4: Perfurado
  - 5: Linho
  - 6: Papel
  - 7: Diagonais
  - 8: Malha
  - 9: Granulado
- Opacidade: 72
  $name: Opacidade do fundo
  $description: 10 = quase invisível, 100 = totalmente opaco.
- Escala: 100
  $name: Escala da barra
  $description: Tamanho de tudo — botões, ícones, espaçamentos e cantos.
  $options:
  - 70: 70%
  - 80: 80%
  - 90: 90%
  - 100: 100%
  - 115: 115%
  - 130: 130%
  - 150: 150%
- Atalhos:
  - 'Comet | C:\Program Files\Perplexity\Comet\Application\comet.exe | comet'
  - 'Chrome | C:\Program Files\Google\Chrome\Application\chrome.exe | chrome'
  - 'Telegram | D:\Telegram Desktop\Telegram.exe | telegram'
  - 'WhatsApp | shell:AppsFolder\5319275A.WhatsAppDesktop_cv1g1gvanyjgm!App | whatsapp'
  - 'NeverWrite | C:\Program Files\NeverWrite\NeverWrite.exe | neverwrite'
  - 'Design Arena | C:\Program Files\Design Arena\pake-designarena.exe | arena'
  - 'OneCommander | C:\Program Files\OneCommander\OneCommander.exe | onecommander'
  - 'alphaXiv | https://www.alphaxiv.org/ | alphaxiv'
  - 'Maple Bookmarks | "C:\Program Files\Perplexity\Comet\Application\comet.exe" --app="chrome-extension://lgncmpklmepncbjpiebhdoejhmbcnjad/popup.html" --window-size=420,620 | maple'
  - 'Bloco de notas | C:\Windows\System32\notepad.exe | notepad'
  $name: Atalhos de programas
  $description: |-
    Um item por atalho, no formato:   Nome | Alvo | Ícone

    Alvo — o programa (.exe), uma pasta, um documento, um site, ou um programa
    com argumentos entre aspas:

        "C:\...\comet.exe" --app="chrome-extension://..."

    Ícone (opcional) — o nome de um PNG da pasta de ícones (comet, chrome,
    telegram, whatsapp, neverwrite, arena, onecommander, alphaxiv, maple,
    notepad) ou um arquivo de onde tirar o ícone. Em branco, o ícone sai do
    próprio alvo.

    Use o + para acrescentar um atalho e a lixeira para tirar. Um item começando
    com // fica desligado sem precisar ser apagado.
- Tema: 1
  $name: Tema de cores
  $description: Escolha Personalizado para usar as três cores soltas de baixo.
  $options:
  - 0: Personalizado
  - 1: Escuro
  - 2: Preto total
  - 3: Grafite
  - 4: Ardósia
  - 5: Verde-noite
  - 6: Vinho
  - 7: Âmbar
  - 8: Claro
  - 9: Papel
- CorFundo: "#0A0D12"
  $name: Cor do fundo (só no tema Personalizado)
  $description: Escreva no formato #RRGGBB.
- CorLinha: "#FFFFFF"
  $name: Cor dos traços e ícones (só no tema Personalizado)
  $description: Escreva no formato #RRGGBB.
- CorDivisoria: "#FFFFFF"
  $name: Cor da linha divisória (só no tema Personalizado)
  $description: Escreva no formato #RRGGBB.
- MostrarSempreVisivel: false
  $name: Ficar por cima das janelas
  $description: Ligado, a barra flutua por cima de tudo, sempre visível. Desligado (padrão), ela vive na área de trabalho e as janelas abertas passam por cima dela.
- Vertical: false
  $name: Barra em pé
  $description: Em vez de deitada, a barra fica em pé na vertical.
- ColarBordas: true
  $name: Colar nas bordas
  $description: Ao soltar a barra perto de uma borda da tela, ela encosta sozinha nela.
- TravarLugar: false
  $name: Travar no lugar
  $description: Impede de arrastar a barra. O clique nos botões continua funcionando.
- ManterNaArea: true
  $name: Manter sempre na área de trabalho
  $description: Se a barra ficar fora da tela, ela volta sozinha para dentro.
- EfeitoIma: true
  $name: Efeito magnético nos ícones
  $description: Ao passar o mouse, os ícones perto do cursor crescem e voltam ao normal sozinhos.
- ForcaIma: 100
  $name: Força do efeito magnético (%)
  $description: 100 deixa o ícone sob o cursor 1,5 vez maior. Aceita de 0 a 200.
- DistanciaIma: 150
  $name: Alcance do efeito magnético (px)
  $description: Até que distância os ícones vizinhos sentem o cursor. Padrão 150.
- PastaOpenCode: ""
  $name: Pasta de trabalho do OpenCode
  $description: Deixe em branco para usar H:\DS CREATIVE.
- PastaIcones: ""
  $name: Pasta de ícones
  $description: Deixe em branco para usar a pasta padrão de ícones.
*/
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

// mídia por tecla virtual real (SendInput). WM_APPCOMMAND depende da janela em
// primeiro plano e falha quando a barra WS_EX_NOACTIVATE ou a área de trabalho
// está na frente: a mensagem vai para a janela errada e nada toca.
// Teclas virtuais, não scan codes — SendInput com wScan + 0xE0 no valor alto
// não gera a tecla estendida.
#ifndef VK_MEDIA_PREV_TRACK
#define VK_MEDIA_PREV_TRACK  0xB1
#endif
#ifndef VK_MEDIA_PLAY_PAUSE
#define VK_MEDIA_PLAY_PAUSE  0xB3
#endif
#ifndef VK_MEDIA_NEXT_TRACK
#define VK_MEDIA_NEXT_TRACK  0xB0
#endif

// ---------------------------------------------------------------------------
// Tipos
// ---------------------------------------------------------------------------

enum LineIcon {
    LI_NONE = 0,
    LI_TRASH,
    LI_LOCK,
    LI_POWER,
    LI_USER,   // reserva de atalho sem ícone próprio: caixa + seta
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
static double g_reveal     = 1.0;   // 1 = fundo sempre presente
static bool   g_running    = true;

static int g_barW = 0;
static int g_barH = 0;

// configurações
static int       g_textura    = 0;
static int       g_opacidade  = 72;
static bool      g_forcar100  = false;
static bool      g_starfield  = false;
static COLORREF  g_corDiv     = RGB(255, 255, 255);
// Camada da barra: true = por cima de tudo (fica visível sobre os programas
// abertos), false = na área de trabalho (as janelas passam por cima dela).
static bool      g_porCima    = false;
static std::wstring g_pastaOpenCode = L"H:\\DS CREATIVE";
static std::wstring g_pastaIcones;

// ---------------------------------------------------------------------------
// Camada da barra
// ---------------------------------------------------------------------------

// Põe a barra na camada escolhida pela configuração "Ficar por cima das
// janelas". Com ela ligada, a barra é sempre a última da pilha (como era até a
// 1.4.1). Desligada, a barra sai da faixa "sempre no topo" e vai para trás da
// janela que está em uso — vira parte da área de trabalho, e qualquer programa
// aberto passa por cima dela.
//
// De propósito não uso HWND_BOTTOM: ele manda a janela para trás de tudo,
// inclusive do papel de parede, e a barra sumiria da tela.
static void AplicarCamada(HWND hwnd) {
    if (!hwnd) return;

    if (g_porCima) {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        return;
    }

    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    HWND frente = GetForegroundWindow();
    if (frente && frente != hwnd)
        SetWindowPos(hwnd, frente, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

// GDI+
static ULONG_PTR g_gdiplusToken = 0;
static std::map<std::wstring, Gdiplus::Bitmap*> g_icons;

// escala global da barra: 1.0 = desenho original de 30px por botão
static double g_escala = 1.0;

// opções de posição, todas ajustáveis nas configurações
static bool g_vertical     = false;   // em pé em vez de deitada
static bool g_colarBordas  = true;    // encosta sozinha na borda ao soltar
static bool g_travado      = false;   // não deixa arrastar
// efeito magnético (o mesmo do componente MagneticDock)
static bool g_efeitoIma    = true;
static int  g_forcaIma     = 100;     // 100 = o ícone sob o cursor cresce 1,5 vez
static int  g_distIma      = 150;     // alcance em px, medido no tamanho 100%
static bool g_manterNaArea = true;    // nunca fica fora da tela

// atalho de programa, vindo da lista das configurações, no formato
//     Nome | Alvo | Ícone
// O alvo pode ser um .exe, uma pasta, um documento, um site ou um programa com
// argumentos entre aspas:
//     "C:\...\comet.exe" --app="chrome-extension://..."
// O ícone é opcional: o nome de um PNG da pasta de ícones (ex. maple) ou um
// arquivo de onde tirar o ícone. Em branco, o ícone sai do próprio alvo.
struct AtalhoUser {
    std::wstring nome;
    std::wstring alvo;
    std::wstring icone;
};
static std::vector<AtalhoUser> g_atalhos;

// teto da lista: mais que isso não caberia em nenhum monitor
static const int kMaxAtalhos = 32;

// Lista de fábrica: vale enquanto nenhum atalho foi salvo nas configurações.
// É a barra como ela sai da caixa — e a mesma lista que aparece no primeiro
// salvamento, para o que está instalado e o que está escrito nunca divergirem.
static const wchar_t* kAtalhosPadrao[] = {
    L"Comet | C:\\Program Files\\Perplexity\\Comet\\Application\\comet.exe | comet",
    L"Chrome | C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe | chrome",
    L"Telegram | D:\\Telegram Desktop\\Telegram.exe | telegram",
    L"WhatsApp | shell:AppsFolder\\5319275A.WhatsAppDesktop_cv1g1gvanyjgm!App | whatsapp",
    L"NeverWrite | C:\\Program Files\\NeverWrite\\NeverWrite.exe | neverwrite",
    L"Design Arena | C:\\Program Files\\Design Arena\\pake-designarena.exe | arena",
    L"OneCommander | C:\\Program Files\\OneCommander\\OneCommander.exe | onecommander",
    L"alphaXiv | https://www.alphaxiv.org/ | alphaxiv",
    L"Maple Bookmarks | \"C:\\Program Files\\Perplexity\\Comet\\Application\\comet.exe\""
    L" --app=\"chrome-extension://lgncmpklmepncbjpiebhdoejhmbcnjad/popup.html\""
    L" --window-size=420,620 | maple",
    L"Bloco de notas | C:\\Windows\\System32\\notepad.exe | notepad",
};
static Gdiplus::Bitmap* g_texture = nullptr;
static int g_textureId = -1;
static UINT g_textureW = 0, g_textureH = 0;

// ---------------------------------------------------------------------------
// Utilidades
// ---------------------------------------------------------------------------

static bool PtIn(const RECT& r, POINT p) {
    return p.x >= r.left && p.x < r.right && p.y >= r.top && p.y < r.bottom;
}

// mesma pergunta, mas com folga em volta. O painel do Adobe nasce 8px acima do
// botão que o abre; sem folga essa faixa vira zona morta e o painel fecha
// sozinho no meio de um movimento lento do mouse até ele.
static bool PertoDe(const RECT& r, POINT p, int m = 16) {
    return p.x >= r.left - m && p.x < r.right + m &&
           p.y >= r.top  - m && p.y < r.bottom + m;
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

// comparado sem <cwctype> para não arrastar mais um include
static bool EspacoW(wchar_t c) {
    return c == L' ' || c == L'\t' || c == L'\r' || c == L'\n';
}

static std::wstring Aparar(const std::wstring& s) {
    size_t i = 0, f = s.size();
    while (i < f && EspacoW(s[i])) i++;
    while (f > i && EspacoW(s[f - 1])) f--;
    return s.substr(i, f - i);
}

// Separa o alvo em programa + argumentos, na convenção do Windows: o programa
// entre aspas e o resto solto atrás.
//     "C:\...\comet.exe" --app="chrome-extension://..."
// Sem aspas o alvo inteiro é o programa — assim caminho com espaço continua
// valendo sem precisar de aspas, e site/pasta/documento seguem iguais.
static void SepararAlvo(const std::wstring& alvo, std::wstring& prog, std::wstring& args) {
    prog.clear();
    args.clear();
    std::wstring t = Aparar(alvo);
    if (t.empty()) return;

    if (t[0] == L'"' || t[0] == L'\'') {
        wchar_t fecha = (t[0] == L'"') ? L'"' : L'\'';
        size_t f = t.find(fecha, 1);
        if (f != std::wstring::npos) {
            prog = Aparar(t.substr(1, f - 1));
            args = Aparar(t.substr(f + 1));
            return;
        }
    }
    prog = t;
}

// Quebra um item da lista de atalhos em nome, alvo e ícone. O separador é o |
// e o terceiro campo é opcional; sem nenhum | o alvo é o próprio item e o nome
// sai do arquivo apontado.
static AtalhoUser InterpretarAtalho(const std::wstring& texto) {
    std::wstring campo[3];
    int qual = 0;
    bool temBarra = false;
    for (wchar_t c : texto) {
        if (c == L'|') { temBarra = true; if (qual < 2) qual++; continue; }
        campo[qual] += c;
    }
    for (int k = 0; k < 3; k++) campo[k] = Aparar(campo[k]);

    AtalhoUser a;
    if (!temBarra) {
        a.alvo = campo[0];
        if (a.alvo.rfind(L"http", 0) == 0) {
            a.nome = a.alvo;                        // site: o nome é o endereço
        } else {
            std::wstring prog, args;
            SepararAlvo(a.alvo, prog, args);
            size_t barra = prog.find_last_of(L"\\/");
            a.nome = (barra == std::wstring::npos) ? prog : prog.substr(barra + 1);
            size_t ponto = a.nome.find_last_of(L'.');
            if (ponto != std::wstring::npos) a.nome = a.nome.substr(0, ponto);
        }
    } else {
        a.nome  = campo[0];
        a.alvo  = campo[1];
        a.icone = campo[2];
    }
    return a;
}

// ---------------------------------------------------------------------------
// Tema de cores
//
// Um tema é só um trio: cor base do fundo, cor dos traços e cor da divisória.
// É o mínimo que muda a cara da barra inteira sem tocar em cada desenho.
// O índice 0 não tem cores próprias: significa "use as três cores soltas dos
// ajustes", e por isso AplicarTema sai antes de mexer em qualquer coisa.
// ---------------------------------------------------------------------------

struct TemaCores {
    const wchar_t* nome;
    COLORREF fundo;
    COLORREF linha;
    COLORREF divisoria;
};

static const TemaCores kTemas[] = {
    { L"Personalizado", RGB(10, 13, 18),    RGB(255, 255, 255), RGB(255, 255, 255) },
    { L"Escuro",        RGB(10, 13, 18),    RGB(255, 255, 255), RGB(255, 255, 255) },
    { L"Preto total",   RGB(0, 0, 0),       RGB(237, 237, 237), RGB(42, 42, 42)    },
    { L"Grafite",       RGB(28, 28, 30),    RGB(242, 242, 247), RGB(72, 72, 74)    },
    { L"Ardósia",       RGB(23, 27, 34),    RGB(220, 227, 237), RGB(48, 58, 74)    },
    { L"Verde-noite",   RGB(7, 16, 13),     RGB(207, 245, 228), RGB(27, 58, 46)    },
    { L"Vinho",         RGB(21, 10, 14),    RGB(247, 218, 225), RGB(70, 32, 43)    },
    { L"Âmbar",         RGB(20, 16, 10),    RGB(247, 230, 200), RGB(70, 58, 34)    },
    { L"Claro",         RGB(244, 244, 246), RGB(29, 29, 31),   RGB(201, 201, 206) },
    { L"Papel",         RGB(239, 233, 220), RGB(42, 37, 27),   RGB(207, 198, 180) },
};

static int      g_tema     = 1;                       // 1 = Escuro, o de sempre
static COLORREF g_corBase  = RGB(10, 13, 18);
static COLORREF g_corLinha = RGB(255, 255, 255);

// Aceita "#RRGGBB" ou "RRGGBB", com ou sem espaços em volta.
static bool HexCor(const std::wstring& bruto, COLORREF& cor) {
    std::wstring s = Aparar(bruto);
    if (!s.empty() && s[0] == L'#') s = s.substr(1);
    if (s.size() != 6) return false;

    int v[6];
    for (int i = 0; i < 6; i++) {
        wchar_t c = s[i];
        if (c >= L'0' && c <= L'9')      v[i] = c - L'0';
        else if (c >= L'a' && c <= L'f') v[i] = c - L'a' + 10;
        else if (c >= L'A' && c <= L'F') v[i] = c - L'A' + 10;
        else return false;
    }
    cor = RGB(v[0] * 16 + v[1], v[2] * 16 + v[3], v[4] * 16 + v[5]);
    return true;
}

// Uma cor escrita torta não pode derrubar o tema: cai no padrão e pronto.
static COLORREF LerCor(PCWSTR nome, const wchar_t* padrao) {
    COLORREF cor = RGB(255, 255, 255);
    HexCor(padrao, cor);
    PCWSTR v = Wh_GetStringSetting(nome);
    if (v && *v) HexCor(v, cor);
    Wh_FreeStringSetting(v);
    return cor;
}

static void AplicarTema() {
    int i = Clamp(g_tema, 0, (int)_countof(kTemas) - 1);
    if (i == 0) return;   // Personalizado: valem as cores lidas dos ajustes
    g_corBase  = kTemas[i].fundo;
    g_corLinha = kTemas[i].linha;
    g_corDiv   = kTemas[i].divisoria;
}

static void CarregarConfig() {
    // nesta versão do Windhawk não existe Wh_GetBoolSetting:
    // bools voltam como int via Wh_GetIntSetting
    // defaults explícitos: se o bloco de settings não for reconhecido, o
    // mod continua com o comportamento correto em vez de virar tudo zero
    g_textura    = Wh_GetIntSetting(L"Textura", 0);
    g_opacidade  = Clamp(Wh_GetIntSetting(L"Opacidade", 72), 10, 100);
    // O visual NÃO muda no hover. Os ajustes OpacidadeHover e EfeitoStarfield
    // foram removidos de propósito: o Windhawk grava o valor escolhido no
    // registro (HKLM\SOFTWARE\Windhawk\Engine\Mods\local@dscreative-bar\
    // Settings) e ele sobreviveria a uma simples troca de padrão no código.
    // g_forcar100 e g_starfield ficam fixos em falso.
    // escala em por cento, guardada como inteiro. Clamp evita um valor absurdo
    // salvo no registro encolher ou explodir a barra.
    g_escala     = Clamp(Wh_GetIntSetting(L"Escala", 100), 60, 200) / 100.0;
    // ---- tema --------------------------------------------------------------
    // As três cores soltas são lidas sempre; o tema por cima delas decide se
    // elas valem (Personalizado) ou se são substituídas pela paleta pronta.
    g_corBase  = LerCor(L"CorFundo",     L"#0A0D12");
    g_corLinha = LerCor(L"CorLinha",     L"#FFFFFF");
    g_corDiv   = LerCor(L"CorDivisoria", L"#FFFFFF");
    g_tema     = Clamp(Wh_GetIntSetting(L"Tema", 1), 0, (int)_countof(kTemas) - 1);
    AplicarTema();
    // "Ficar por cima das janelas": desligado, a barra vive na área de trabalho.
    // Salvar a configuração já reaplica a camada na hora, sem recarregar nada.
    g_porCima = Wh_GetIntSetting(L"MostrarSempreVisivel", 0) != 0;
    if (g_hwnd) AplicarCamada(g_hwnd);

    // ---- posição -----------------------------------------------------------
    g_vertical     = Wh_GetIntSetting(L"Vertical", 0) != 0;
    g_colarBordas  = Wh_GetIntSetting(L"ColarBordas", 1) != 0;
    g_travado      = Wh_GetIntSetting(L"TravarLugar", 0) != 0;
    g_manterNaArea = Wh_GetIntSetting(L"ManterNaArea", 1) != 0;

    g_efeitoIma    = Wh_GetIntSetting(L"EfeitoIma", 1) != 0;
    g_forcaIma     = Clamp(Wh_GetIntSetting(L"ForcaIma", 100), 0, 200);
    g_distIma      = Clamp(Wh_GetIntSetting(L"DistanciaIma", 150), 20, 500);

    PCWSTR s = Wh_GetStringSetting(L"PastaOpenCode");
    g_pastaOpenCode = (s && *s) ? s : L"H:\\DS CREATIVE";
    Wh_FreeStringSetting(s);

    s = Wh_GetStringSetting(L"PastaIcones");
    // Wh_GetStringSetting devolve L"" (vazio, e não nulo) quando nada foi salvo
    // e o padrão não se aplica — sem este fallback nenhum PNG é carregado e a
    // barra fica só com os ícones desenhados em código (Sistema e Mídia).
    g_pastaIcones = Expandir((s && *s) ? s : L"%USERPROFILE%\\windhawk-bar-ds-creative\\icons");
    Wh_FreeStringSetting(s);

    // ---- atalhos de programas ----------------------------------------------
    // Uma lista só, editável nas configurações: Atalhos[0], Atalhos[1], ...
    // Cada item é um atalho no formato  Nome | Alvo | Ícone, com o ícone
    // opcional. Um item começando com // fica desligado sem ser apagado.
    g_atalhos.clear();
    for (int i = 0; i < kMaxAtalhos; i++) {
        wchar_t chave[32]{};
        wsprintfW(chave, L"Atalhos[%d]", i);
        PCWSTR v = Wh_GetStringSetting(chave);
        std::wstring texto = Aparar((v && *v) ? v : L"");
        Wh_FreeStringSetting(v);
        if (texto.empty() || texto.rfind(L"//", 0) == 0) continue;

        AtalhoUser a = InterpretarAtalho(texto);
        if (a.alvo.empty() || a.alvo.rfind(L"//", 0) == 0) continue;
        g_atalhos.push_back(a);
    }

    // Nada salvo ainda (primeira execução do mod): entra a lista de fábrica,
    // para a barra já nascer completa.
    if (g_atalhos.empty())
        for (const wchar_t* linha : kAtalhosPadrao)
            g_atalhos.push_back(InterpretarAtalho(linha));
}

// ---------------------------------------------------------------------------
// Ícones: PNG carregados da pasta configurada (o mod não embute marca nenhuma)
// ---------------------------------------------------------------------------

// Converte um HICON em bitmap GDI+ 32bpp com canal alfa de verdade.
//
// O caminho óbvio — desenhar o ícone num DIB zerado e pronto — falha com
// ícones antigos, que não têm canal alfa: o resultado fica 100% transparente e
// o botão some da barra. Aqui o ícone é desenhado DUAS vezes, sobre preto e
// sobre branco, e o alfa sai da diferença entre os dois:
//
//   preto  = cor * a
//   branco = cor * a + 255 * (1 - a)
//   branco - preto = 255 * (1 - a)   ->   a = (255 - (branco - preto)) / 255
//
// Vale para os dois casos: ícone com alfa e ícone com máscara. Para ícone com
// máscara, onde ele é transparente as duas cópias continuam preto e branco
// puras, então a diferença dá 255 e o alfa dá 0 — exatamente o certo.
static Gdiplus::Bitmap* IconeParaBitmap(HICON icone, int lado) {
    using namespace Gdiplus;
    if (!icone) return nullptr;

    // sem tamanho informado, usa o tamanho real do ícone: nada de esticar
    if (lado < 4) {
        ICONINFO ii{};
        if (GetIconInfo(icone, &ii)) {
            BITMAP bm{};
            if (ii.hbmColor && GetObject(ii.hbmColor, sizeof(bm), &bm)) lado = bm.bmWidth;
            else if (ii.hbmMask && GetObject(ii.hbmMask, sizeof(bm), &bm)) lado = bm.bmWidth;
            if (ii.hbmColor) DeleteObject(ii.hbmColor);
            if (ii.hbmMask)  DeleteObject(ii.hbmMask);
        }
    }
    if (lado < 4 || lado > 512) lado = 32;

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = lado;
    bmi.bmiHeader.biHeight      = -lado;   // top-down, igual ao GDI+
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    HDC tela = GetDC(nullptr);
    if (!tela) return nullptr;

    DWORD* preto  = nullptr;
    DWORD* branco = nullptr;
    HBITMAP dibPreto  = CreateDIBSection(tela, &bmi, DIB_RGB_COLORS, (void**)&preto,  nullptr, 0);
    HBITMAP dibBranco = CreateDIBSection(tela, &bmi, DIB_RGB_COLORS, (void**)&branco, nullptr, 0);
    ReleaseDC(nullptr, tela);
    if (!dibPreto || !dibBranco || !preto || !branco) {
        if (dibPreto)  DeleteObject(dibPreto);
        if (dibBranco) DeleteObject(dibBranco);
        return nullptr;
    }

    const size_t total = (size_t)lado * lado;
    for (size_t i = 0; i < total; i++) { preto[i] = 0xFF000000; branco[i] = 0xFFFFFFFF; }

    HDC mem = CreateCompatibleDC(nullptr);
    if (mem) {
        HGDIOBJ antigo = SelectObject(mem, dibPreto);
        DrawIconEx(mem, 0, 0, icone, lado, lado, 0, nullptr, DI_NORMAL);
        SelectObject(mem, dibBranco);
        DrawIconEx(mem, 0, 0, icone, lado, lado, 0, nullptr, DI_NORMAL);
        SelectObject(mem, antigo);
        DeleteDC(mem);
    }

    BYTE* saida = (BYTE*)preto;   // reaproveita o buffer do preto
    for (size_t i = 0; i < total; i++) {
        const BYTE* pp = (const BYTE*)preto  + i * 4;
        const BYTE* pb = (const BYTE*)branco + i * 4;
        int dB = pb[0] - pp[0];
        int dG = pb[1] - pp[1];
        int dR = pb[2] - pp[2];
        int d  = (dB + dG + dR) / 3;
        int a  = 255 - d;
        if (a < 0) a = 0;
        if (a > 255) a = 255;
        BYTE R = pp[2], G = pp[1], B = pp[0];
        if (a > 0) {
            // desfaz a multiplicação do alfa: a cor real é a do preto dividida
            int r = (pp[2] * 255) / a; if (r > 255) r = 255;
            int g = (pp[1] * 255) / a; if (g > 255) g = 255;
            int b = (pp[0] * 255) / a; if (b > 255) b = 255;
            R = (BYTE)r; G = (BYTE)g; B = (BYTE)b;
        }
        saida[i * 4 + 0] = B;
        saida[i * 4 + 1] = G;
        saida[i * 4 + 2] = R;
        saida[i * 4 + 3] = (BYTE)a;
    }

    Bitmap* temp  = new Bitmap(lado, lado, lado * 4, PixelFormat32bppARGB, (BYTE*)preto);
    Bitmap* copia = nullptr;
    if (temp && temp->GetLastStatus() == Ok)
        copia = temp->Clone(0, 0, lado, lado, PixelFormat32bppARGB);
    delete temp;
    DeleteObject(dibPreto);
    DeleteObject(dibBranco);
    return copia;
}

// Pega o ícone REAL do próprio arquivo — .exe, .dll, atalho ou pasta, o que o
// Windows mostraria no Explorer. Mesmo princípio dos ícones fixos da barra:
// nada desenhado à mão, nada inventado.
static Gdiplus::Bitmap* CarregarIconeDoArquivo(const std::wstring& caminho) {
    if (caminho.empty()) return nullptr;
    SHFILEINFOW sfi{};
    if (!SHGetFileInfoW(caminho.c_str(), 0, &sfi, sizeof(sfi),
                        SHGFI_ICON | SHGFI_LARGEICON))
        return nullptr;
    Gdiplus::Bitmap* bmp = IconeParaBitmap(sfi.hIcon, 0);
    DestroyIcon(sfi.hIcon);
    return bmp;
}

static void LiberarIcones() {
    for (auto& kv : g_icons) delete kv.second;
    g_icons.clear();
}

static void CarregarIcones() {
    LiberarIcones();

    // Ícones dos atalhos de programa. A ordem de preferência é:
    //   1. o PNG indicado no terceiro campo   (maple -> maple.png)
    //   2. o arquivo indicado no terceiro campo
    //   3. o próprio alvo do atalho
    // Como os dois últimos saem do próprio arquivo, um atalho continua
    // funcionando mesmo sem nenhuma pasta de ícones configurada.
    for (size_t i = 0; i < g_atalhos.size(); i++) {
        wchar_t chave[24]{};
        wsprintfW(chave, L"user%u", (unsigned)i);
        const AtalhoUser& a = g_atalhos[i];
        const std::wstring icone = Expandir(a.icone);

        if (!icone.empty() && !g_pastaIcones.empty()) {
            std::wstring png = g_pastaIcones + L"\\" + icone + L".png";
            if (GetFileAttributesW(png.c_str()) != INVALID_FILE_ATTRIBUTES) {
                Gdiplus::Bitmap* bmp = Gdiplus::Bitmap::FromFile(png.c_str(), FALSE);
                if (bmp && bmp->GetLastStatus() == Gdiplus::Ok) { g_icons[chave] = bmp; continue; }
                delete bmp;
            }
        }

        std::wstring de;
        if (!icone.empty() && GetFileAttributesW(icone.c_str()) != INVALID_FILE_ATTRIBUTES) {
            de = icone;
        } else {
            std::wstring prog, args;
            SepararAlvo(Expandir(a.alvo), prog, args);
            if (GetFileAttributesW(prog.c_str()) != INVALID_FILE_ATTRIBUTES) de = prog;
        }
        if (de.empty()) continue;
        if (Gdiplus::Bitmap* b = CarregarIconeDoArquivo(de))
            g_icons[chave] = b;
    }

    if (g_pastaIcones.empty()) return;

    // ícones dos botões internos: OpenCode, Creative Cloud, Figma e o painel
    static const wchar_t* chaves[] = {
        L"oc", L"cc", L"fg", L"ps", L"ai", L"ae", L"pr", L"lr",
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

// Executa um atalho da lista: programa, pasta, documento, site ou programa com
// argumentos. "shell:..." é atalho do próprio Windows (os apps da Store usam
// shell:AppsFolder) e vai pelo explorer, do mesmo jeito que o Windows faria.
static void AbrirAtalho(const std::wstring& alvo) {
    std::wstring t = Aparar(Expandir(alvo));
    if (t.empty()) return;

    if (t.rfind(L"shell:", 0) == 0) {
        AbrirShell(Expandir(L"%WINDIR%\\explorer.exe"), t);
        return;
    }

    std::wstring prog, args;
    SepararAlvo(t, prog, args);
    AbrirShell(prog, args);
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

// rastro cumulativo das ações em %TEMP%\dscreative-bar.log — prova se o clique
// chegou ao botão quando algo "não responde"
static void Marcar(const wchar_t* acao) {
    SYSTEMTIME st{};
    GetLocalTime(&st);
    wchar_t hora[40]{};
    wsprintfW(hora, L"%02d/%02d %02d:%02d:%02d  ", st.wDay, st.wMonth,
              st.wHour, st.wMinute, st.wSecond);
    wchar_t dir[MAX_PATH]{};
    GetTempPathW(MAX_PATH, dir);
    std::wstring caminho = dir;
    caminho += L"dscreative-bar.log";
    HANDLE f = CreateFileW(caminho.c_str(), FILE_APPEND_DATA,
                           FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                           OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE) return;
    DWORD n = 0;
    WriteFile(f, hora, (DWORD)wcslen(hora) * sizeof(wchar_t), &n, nullptr);
    WriteFile(f, acao, (DWORD)wcslen(acao) * sizeof(wchar_t), &n, nullptr);
    WriteFile(f, L"\r\n", 4, &n, nullptr);
    CloseHandle(f);
}

// A confirmação nasce no centro do monitor, longe da barra — quem olha para a
// barra acha que o botão não fez nada. Um gancho WH_CBT reposiciona o diálogo
// para junto da barra assim que ele é ativado.
//
// MEDIDO: ao FECHAR a caixa de diálogo o Windows ativa o dono dela — a própria
// barra — e o gancho, que só olhava o handle recebido sem conferir o que era,
// reposicionava a BARRA em cima dela mesma: y = bottom + 8 = +52px por clique,
// descendo para sempre. Agora o gancho só age se:
//   1. a janela NÃO for a barra nem o painel;
//   2. a janela for uma caixa de diálogo de verdade (classe #32770);
//   3. ainda não tiver reposicionado nada nesta confirmação.
static HHOOK g_hookDlg = nullptr;
static bool  g_dlgJaPosicionado = false;

static LRESULT CALLBACK HookDialogo(int code, WPARAM wp, LPARAM lp) {
    if (code == HCBT_ACTIVATE && g_hwnd && !g_dlgJaPosicionado) {
        HWND dlg = (HWND)wp;
        wchar_t cls[16]{};
        GetClassNameW(dlg, cls, 16);
        if (dlg != g_hwnd && dlg != g_panel && wcscmp(cls, L"#32770") == 0) {
        RECT rd{}, rb{};
        if (GetWindowRect(dlg, &rd) && GetWindowRect(g_hwnd, &rb)) {
            // Área útil do monitor ONDE A BARRA ESTÁ. Medido: usando a tela
            // virtual, com a barra perto do fundo do monitor principal o
            // diálogo nascia em y=1052 e ia até 1211, com o monitor terminando
            // em 1080 — só 18% visível, ou seja, praticamente invisível.
            HMONITOR mon = MonitorFromWindow(g_hwnd, MONITOR_DEFAULTTONEAREST);
            MONITORINFO mi{};
            mi.cbSize = sizeof(mi);
            GetMonitorInfoW(mon, &mi);
            RECT wa = mi.rcWork;

            int w = rd.right - rd.left;
            int h = rd.bottom - rd.top;
            int x = rb.left + ((rb.right - rb.left) - w) / 2;
            int y = rb.bottom + 8;               // abaixo da barra
            if (y + h > wa.bottom - 4) {         // não coube: vai para cima
                int acima = rb.top - 8 - h;
                y = (acima >= wa.top + 4) ? acima : (wa.bottom - 4 - h);
            }
            if (x + w > wa.right - 4)  x = wa.right - 4 - w;
            if (x < wa.left + 4)       x = wa.left + 4;
            if (y < wa.top + 4)        y = wa.top + 4;
            if (y + h > wa.bottom - 4) y = wa.bottom - 4 - h;

            SetWindowPos(dlg, HWND_TOPMOST, x, y, 0, 0,
                         SWP_NOSIZE | SWP_NOACTIVATE);
            g_dlgJaPosicionado = true;   // uma vez por confirmação, basta
        }
        }
    }
    return CallNextHookEx(g_hookDlg, code, wp, lp);
}

// MB_SETFOREGROUND é obrigatório: sem ela o diálogo nasce atrás das janelas de
// topo (Raycast, NVIDIA, PowerToys) e o dono — a barra — tem WS_EX_NOACTIVATE,
// que não ativa a janela filha.
static bool Confirmar(const wchar_t* titulo, const wchar_t* texto) {
    Marcar(titulo);
    g_dlgJaPosicionado = false;
    g_hookDlg = SetWindowsHookExW(WH_CBT, HookDialogo, nullptr,
                                  GetCurrentThreadId());
    int r = MessageBoxW(g_hwnd, texto, titulo,
                        MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 |
                        MB_TOPMOST |
                        MB_SETFOREGROUND);
    if (g_hookDlg) {
        UnhookWindowsHookEx(g_hookDlg);
        g_hookDlg = nullptr;
    }
    return r == IDYES;
}

static void EsvaziarLixeira() {
    if (!Confirmar(L"Esvaziar lixeira",
                   L"Esvaziar permanentemente todos os itens da lixeira?"))
        return;
    SHEmptyRecycleBinW(nullptr, nullptr,
                       SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

static void Bloquear() {
    Marcar(L"Bloquear");
    if (LockWorkStation()) {
        Marcar(L"  lock ok");
        return;
    }
    DWORD e = GetLastError();
    wchar_t m[96]{};
    wsprintfW(m, L"  lock falhou err=%lu -> tentando rundll32", e);
    Marcar(m);
    // um processo novo nasce no desktop de entrada atual e costuma conseguir
    // travar onde a thread do mod falha
    ShellExecuteW(nullptr, L"open", L"rundll32.exe",
                  L"user32.dll,LockWorkStation", nullptr, SW_HIDE);
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
    BOOL ok = InitiateSystemShutdownExW(
        nullptr, const_cast<LPWSTR>(L"O computador vai desligar em 30 segundos."),
        30, TRUE, FALSE,
        SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_OTHER);
    wchar_t m[96]{};
    wsprintfW(m, L"  shutdown r=%d err=%lu", ok, (unsigned long)GetLastError());
    Marcar(m);
}

// ---------------------------------------------------------------------------
// Mídia — o caminho principal é a barra de tarefas, não o SendInput.
//
// MEDIDO em 17/10 com um rig (Media Session API + porta de depuração do
// Chrome), cada caminho testado 2 vezes:
//   SendInput com VK_MEDIA_*        -> devolve 2/2 e NÃO faz nada quando a
//                                      janela em primeiro plano ignora teclas
//                                      de mídia. Falso positivo silencioso; só
//                                      funcionou com o Chrome na frente, o que
//                                      explica o "às vezes funciona".
//   WM_APPCOMMAND -> primeiro plano -> nada.
//   WM_APPCOMMAND -> Shell_TrayWnd  -> funcionou 2 de 2, qualquer janela.
//
// Os dois caminhos NÃO rodam juntos: somados alternariam o play/pause duas
// vezes e o efeito final seria nenhum.

static const int AC_PREV = 12;   // APPCOMMAND_MEDIA_PREVIOUSTRACK
static const int AC_NEXT = 11;   // APPCOMMAND_MEDIA_NEXTTRACK
static const int AC_PLAY = 14;   // APPCOMMAND_MEDIA_PLAY_PAUSE

static void Midia(WORD vk, int appcmd) {
    HWND tarefa = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (tarefa) {
        DWORD_PTR res = 0;
        SendMessageTimeoutW(tarefa, WM_APPCOMMAND, 0,
                            (LPARAM)((DWORD)appcmd << 16),
                            SMTO_ABORTIFHUNG, 800, &res);
        Marcar(L"  midia via Shell_TrayWnd");
        return;
    }

    // reserva: só quando não existe barra de tarefas
    INPUT in[2]{};
    for (auto& i : in) {
        i.type   = INPUT_KEYBOARD;
        i.ki.wVk = vk;
    }
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;
    UINT enviadas = SendInput(2, in, sizeof(INPUT));
    wchar_t num[48]{};
    wsprintfW(num, L"  midia reserva SendInput=%u/2", enviadas);
    Marcar(num);
}

// ---------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------

// Os valores abaixo são o desenho original, medido em 100%. Deixaram de ser
// constantes de compilação porque a escala os recalcula em tempo de execução —
// assim todo o layout acompanha, sem uma segunda tabela de medidas.
static int SLOT        = 30;   // lado de cada botão
static int PAD_X       = 8;
static int PAD_Y       = 7;
static int GAP         = 3;
static int SEP_W       = 1;
static int SEP_H       = 18;
static int SEP_MARGEM  = 5;
static int RAIO        = 10;   // cantos arredondados da barra

static int PANEL_TILE  = 40;
static int PANEL_GAP   = 4;
static int PANEL_PAD   = 9;
static int PANEL_LABEL = 14;
static int PANEL_RAIO  = 12;

// arredonda para o inteiro mais próximo e nunca deixa chegar a zero: um
// espaçamento de 0px colaria os botões e uma espessura de 0px sumiria da tela
static int Esc(int base) {
    int v = (int)(base * g_escala + 0.5);
    return v < 1 ? 1 : v;
}

static void CalcularLayout() {
    SLOT        = Esc(30);
    PAD_X       = Esc(8);
    PAD_Y       = Esc(7);
    GAP         = Esc(3);
    SEP_W       = Esc(1);
    SEP_H       = Esc(18);
    SEP_MARGEM  = Esc(5);
    RAIO        = Esc(10);
    PANEL_TILE  = Esc(40);
    PANEL_GAP   = Esc(4);
    PANEL_PAD   = Esc(9);
    PANEL_LABEL = Esc(14);
    PANEL_RAIO  = Esc(12);
}

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
    CalcularLayout();
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

    // --- C: atalhos de programas (a lista das configurações) ---
    // Se o ícone real foi extraído, usa ele. Se não, cai num traço fino de
    // "abrir" — melhor um botão discreto do que um botão invisível.
    size_t c0 = g_buttons.size();
    for (size_t i = 0; i < g_atalhos.size(); i++) {
        wchar_t chave[24]{};
        wsprintfW(chave, L"user%u", (unsigned)i);
        const std::wstring alvo   = g_atalhos[i].alvo;
        const std::wstring rotulo = L"Atalho: " + g_atalhos[i].nome;
        if (g_icons.find(chave) != g_icons.end())
            AddIcon(g_buttons, chave, [alvo, rotulo] { Marcar(rotulo.c_str()); AbrirAtalho(alvo); });
        else
            AddLine(g_buttons, LI_USER, [alvo, rotulo] { Marcar(rotulo.c_str()); AbrirAtalho(alvo); });
    }
    size_t c1 = g_buttons.size();

    // --- D: sistema ---
    size_t d0 = g_buttons.size();
    AddLine(g_buttons, LI_TRASH, [] { EsvaziarLixeira(); });
    AddLine(g_buttons, LI_LOCK,  [] { Bloquear(); });
    AddLine(g_buttons, LI_POWER, [] { Desligar(); });

    // --- E: mídia ---
    size_t e0 = g_buttons.size();
    AddLine(g_buttons, LI_PREV,  [] { Marcar(L"Midia anterior");  Midia(VK_MEDIA_PREV_TRACK,  AC_PREV); });
    AddLine(g_buttons, LI_PLAY,  [] { Marcar(L"Midia play/pause"); Midia(VK_MEDIA_PLAY_PAUSE, AC_PLAY); });
    AddLine(g_buttons, LI_NEXT,  [] { Marcar(L"Midia proxima");   Midia(VK_MEDIA_NEXT_TRACK,  AC_NEXT); });

    size_t fim = g_buttons.size();

    g_grupos.push_back({ L"OpenCode", a0, b0 });
    g_grupos.push_back({ L"Adobe",    b0, c0 });
    if (c1 > c0) g_grupos.push_back({ L"Atalhos", c0, c1 });
    g_grupos.push_back({ L"Sistema",  d0, e0 });
    g_grupos.push_back({ L"Mídia",    e0, fim });

    // --- posicionamento ---
    // Deitada ou em pé, é a mesma conta com x trocado por y. g_seps guarda a
    // posição da divisória no eixo em que a barra cresce, então o desenho das
    // divisórias também acompanha sem uma segunda tabela de medidas.
    int avanco = PAD_X;
    for (size_t gi = 0; gi < g_grupos.size(); gi++) {
        const Grupo& gr = g_grupos[gi];
        for (size_t i = gr.inicio; i < gr.fim; i++) {
            auto& b = g_buttons[i];
            if (!g_vertical)
                b.rc = { avanco, PAD_Y, avanco + SLOT, PAD_Y + SLOT };
            else
                b.rc = { PAD_X, avanco, PAD_X + SLOT, avanco + SLOT };
            avanco += SLOT;
            if (i + 1 < gr.fim) avanco += GAP;
        }
        if (gi + 1 < g_grupos.size()) {
            avanco += SEP_MARGEM;
            g_seps.push_back(avanco);
            avanco += SEP_W + SEP_MARGEM;
        }
    }

    if (!g_vertical) {
        g_barW = avanco + PAD_X;
        g_barH = PAD_Y * 2 + SLOT;
    } else {
        g_barW = PAD_X * 2 + SLOT;
        g_barH = avanco + PAD_Y;
    }

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
        // A textura é gerada em cima de uma base escura fixa (13,17,23). Aqui
        // ela é reescalada para a cor base do tema. No tema Escuro a base do
        // tema é a própria base da textura, então k = 1 e o desenho sai
        // exatamente como sempre saiu — os outros temas só puxam a textura
        // para o tom deles, sem perder o relevo.
        const double TR = 13, TG = 17, TB = 23;
        const double br = GetRValue(g_corBase);
        const double bg = GetGValue(g_corBase);
        const double bb = GetBValue(g_corBase);
        double dist = (std::max)({ std::fabs(br - TR), std::fabs(bg - TG), std::fabs(bb - TB) });
        double k = 1.0 - dist / 255.0;
        if (k < 0.25) k = 0.25;

        ColorMatrix cm{};
        cm.m[0][0] = (REAL)k; cm.m[1][1] = (REAL)k; cm.m[2][2] = (REAL)k;
        cm.m[3][3] = efetivo;
        cm.m[4][0] = (REAL)((br - k * TR) / 255.0);
        cm.m[4][1] = (REAL)((bg - k * TG) / 255.0);
        cm.m[4][2] = (REAL)((bb - k * TB) / 255.0);
        cm.m[4][4] = 1;
        ImageAttributes ia;
        ia.SetColorMatrix(&cm, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
        g.DrawImage(tex, Rect(0, 0, w, h), 0, 0, (INT)tex->GetWidth(), (INT)tex->GetHeight(),
                    UnitPixel, &ia);
    } else {
        BYTE a = (BYTE)(efetivo * 255);
        SolidBrush solido(Color(a, GetRValue(g_corBase),
                                GetGValue(g_corBase), GetBValue(g_corBase)));
        GraphicsPath path;
        AddRaio(path, RectF(0, 0, (REAL)w, (REAL)h), (REAL)RAIO);
        g.FillPath(&solido, &path);
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
static void DesenharIcone(Gdiplus::Graphics& g, const RECT& rc, const std::wstring& chave,
                          float escala = 1.0f, float subir = 0.0f) {
    using namespace Gdiplus;
    auto it = g_icons.find(chave);
    if (it == g_icons.end() || !it->second) return;

    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    // 6px de folga em 30px de botão = 20%, proporcional na escala.
    // "escala" é o efeito magnético: 1.0 é o tamanho normal.
    int lado = (int)((std::min)(w, h) * 0.8f * escala + 0.5f);
    if (lado < 4) return;

    RectF dest((REAL)(rc.left + (w - lado) / 2.0f),
               (REAL)(rc.top + (h - lado) / 2.0f - subir),
               (REAL)lado, (REAL)lado);
    g.DrawImage(it->second, dest);
}

// ícone de linha: SVG de 24×24 traçado com 1,5px e pontas arredondadas
static void DesenharLinha(Gdiplus::Graphics& g, const RECT& rc, int icone,
                          float escala = 1.0f, float subir = 0.0f) {
    using namespace Gdiplus;
    if (icone == LI_NONE) return;

    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;

    // 20px de alvo dentro de um botão de 30px no desenho original
    const REAL ALVO = (REAL)SLOT * (20.0f / 30.0f) * escala;
    REAL s = ALVO / 24.0f;
    REAL ox = (REAL)rc.left + (w - ALVO) / 2;
    REAL oy = (REAL)rc.top + (h - ALVO) / 2 - subir;

    GraphicsState st = g.Save();
    g.TranslateTransform(ox, oy);
    g.ScaleTransform(s, s);
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    g.SetPixelOffsetMode(PixelOffsetModeHalf);

    // a cor vem do tema: no tema Claro os traços ficam escuros, senão sumiriam
    const BYTE LR = GetRValue(g_corLinha);
    const BYTE LG = GetGValue(g_corLinha);
    const BYTE LB = GetBValue(g_corLinha);

    Pen p(Color(235, LR, LG, LB), 1.8f);   // 1.8 × (20/24) = 1,5px finais
    p.SetLineCap(LineCapRound, LineCapRound, DashCapRound);
    p.SetLineJoin(LineJoinRound);
    SolidBrush furo(Color(235, LR, LG, LB));

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
    case LI_USER: {
        // caixa com a ponta saindo: "abrir isto"
        GraphicsPath caixa;
        caixa.StartFigure();
        caixa.AddLine(4, 10, 4, 20);
        caixa.AddLine(4, 20, 14, 20);
        caixa.AddLine(14, 20, 14, 10);
        caixa.AddLine(14, 10, 4, 10);
        g.DrawPath(&p, &caixa);

        g.DrawLine(&p, 12, 12, 20, 4);

        GraphicsPath ponta;
        ponta.StartFigure();
        ponta.AddLine(14, 4, 20, 4);
        ponta.AddLine(20, 4, 20, 10);
        g.DrawPath(&p, &ponta);
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
    if (!g_vertical) {
        int topo = PAD_Y + (SLOT - SEP_H) / 2;
        for (int x : g_seps) g.DrawLine(&p, x, topo, x, topo + SEP_H);
    } else {
        // em pé a divisória também gira: vira uma linha deitada
        int esq = PAD_X + (SLOT - SEP_H) / 2;
        for (int y : g_seps) g.DrawLine(&p, esq, y, esq + SEP_H, y);
    }
}

// ---------------------------------------------------------------------------
// Efeito magnético dos ícones
// ---------------------------------------------------------------------------
// É o mesmo efeito do componente MagneticDock, com os mesmos números: o ícone
// sob o cursor chega a 1,5 vez, os vizinhos caem linearmente até 1,0 no fim do
// alcance (150px no original), a subida acompanha o tamanho, o botão apertado
// afunda para 0,9 e a animação é mola {damping 20, stiffness 300, massa 0,5}.
// O que muda é só o motor: lá é framer-motion no navegador, aqui é um passo
// de integração a cada 16ms.
static std::vector<float> g_imaEscala;   // escala desenhada de cada botão
static std::vector<float> g_imaVel;      // velocidade da mola
static std::vector<float> g_imaAlvo;     // para onde cada botão está indo
static int  g_idxPressionado = -1;       // botão apertado (equivale ao whileTap)
static UINT g_intervaloTimer = 50;       // 50ms parado, 16ms com a mola correndo

static const float IMA_RIGIDEZ = 600.0f;   // stiffness / massa = 300 / 0.5
static const float IMA_AMORTEC  = 40.0f;   // damping   / massa =  20 / 0.5
static const float IMA_PASSO    = 1.0f / 60.0f;

static void SincronizarIma() {
    if (g_imaEscala.size() != g_buttons.size()) {
        g_imaEscala.assign(g_buttons.size(), 1.0f);
        g_imaVel.assign(g_buttons.size(), 0.0f);
        g_imaAlvo.assign(g_buttons.size(), 1.0f);
    }
}

// para onde cada ícone tem que ir. cli é o cursor em coordenadas do cliente.
// ativo é falso quando o cursor está fora da barra — é o onMouseLeave do
// original: fora dela tudo volta para 1.
static void AlvoIma(POINT cli, bool ativo) {
    SincronizarIma();
    g_imaAlvo.assign(g_imaEscala.size(), 1.0f);
    if (!g_efeitoIma || !ativo || g_imaEscala.empty()) return;

    const float maxEsc  = 1.0f + 0.5f * ((float)g_forcaIma / 100.0f);
    const float alcance = (float)g_distIma * (float)g_escala;
    if (maxEsc <= 1.0f || alcance <= 1.0f) return;

    const float pos = (float)(g_vertical ? cli.y : cli.x);
    for (size_t i = 0; i < g_buttons.size(); i++) {
        const RECT& b = g_buttons[i].rc;
        // o original mede só no eixo do dock; no outro eixo não mede nada
        const float centro = g_vertical ? (b.top + b.bottom) / 2.0f
                                        : (b.left + b.right) / 2.0f;
        const float d = std::fabs(pos - centro);
        float f = 1.0f - d / alcance;          // 1 no centro, 0 no limite
        if (f <= 0.0f) continue;
        g_imaAlvo[i] = 1.0f + f * (maxEsc - 1.0f);
    }

    // whileTap={{ scale: 0.9 }}: o botão apertado encolhe por cima do efeito
    if (g_idxPressionado >= 0 && (size_t)g_idxPressionado < g_imaAlvo.size())
        g_imaAlvo[g_idxPressionado] *= 0.9f;
}

// um passo da mola. devolve o maior salto do quadro: 0 quer dizer parada.
static float PassoIma() {
    float maior = 0.0f;
    for (size_t i = 0; i < g_imaEscala.size(); i++) {
        float x = g_imaEscala[i];
        float v = g_imaVel[i];
        const float a = (g_imaAlvo[i] - x) * IMA_RIGIDEZ - v * IMA_AMORTEC;
        v += a * IMA_PASSO;
        x += v * IMA_PASSO;
        // parou de verdade perto do alvo: encosta e zera, senão a mola fica
        // tremendo em micro-passos para sempre e a barra nunca para de redesenhar
        if (std::fabs(g_imaAlvo[i] - x) < 0.002f && std::fabs(v) < 0.02f) {
            x = g_imaAlvo[i];
            v = 0.0f;
        }
        const float salto = std::fabs(x - g_imaEscala[i]);
        if (salto > maior) maior = salto;
        g_imaEscala[i] = x;
        g_imaVel[i] = v;
    }
    return maior;
}

// rotina principal da barra
static void PintarBarra(Gdiplus::Graphics& g, int w, int h) {
    g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
    DesenharFundo(g, w, h, (int)(g_reveal * 255.0));
    DesenharStarfield(g, w, h, 0.0f);   // efeito removido a pedido
    DesenharDivisorias(g);

    // Desenha em ordem de escala: o ícone maior por último. Sem isso um vizinho
    // menor passaria por cima do maior quando os dois se encostam.
    SincronizarIma();
    std::vector<size_t> ordem(g_buttons.size());
    for (size_t i = 0; i < ordem.size(); i++) ordem[i] = i;
    if (g_efeitoIma)
        std::stable_sort(ordem.begin(), ordem.end(),
                         [](size_t a, size_t b) { return g_imaEscala[a] < g_imaEscala[b]; });

    for (size_t i : ordem) {
        const Button& b = g_buttons[i];
        const float e = g_efeitoIma ? g_imaEscala[i] : 1.0f;
        // sobe junto com o tamanho, como no original (lá: (escala-1) * -10 para
        // um ícone de 56px; aqui o ícone tem 24px, então a conta dá 4)
        const float subir = (e - 1.0f) * 4.0f * (float)g_escala;
        if (b.kind == BK_LINE) {
            DesenharLinha(g, b.rc, b.lineIcon, e, subir);
        } else {
            DesenharIcone(g, b.rc, b.iconKey, e, subir);
        }
    }
}

// rotina do painel do Adobe (visível só quando aberto, então sempre opaco)
static void PintarPainel(Gdiplus::Graphics& g, int w, int h) {
    using namespace Gdiplus;
    const BYTE LR = GetRValue(g_corLinha);
    const BYTE LG = GetGValue(g_corLinha);
    const BYTE LB = GetBValue(g_corLinha);

    // o painel é a cor da barra um pouco mais funda, como sombra por baixo
    SolidBrush fundo(Color(238, (BYTE)(GetRValue(g_corBase) * 0.85),
                                (BYTE)(GetGValue(g_corBase) * 0.85),
                                (BYTE)(GetBValue(g_corBase) * 0.85)));
    GraphicsPath base;
    AddRaio(base, RectF(0, 0, (REAL)w, (REAL)h), (REAL)PANEL_RAIO);
    g.FillPath(&fundo, &base);

    Pen borda(Color(40, LR, LG, LB), 1.0f);
    g.DrawPath(&borda, &base);

    FontFamily fam(L"Segoe UI");
    Font rot(&fam, 8.0f * (REAL)g_escala, FontStyleRegular, UnitPixel);
    SolidBrush corRot(Color(170, LR, LG, LB));
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
            REAL top = (REAL)b.rc.bottom + (REAL)PANEL_GAP;
            g.DrawString(rotulos[i], -1, &rot,
                         RectF(cx - 40 * (REAL)g_escala, top,
                               80 * (REAL)g_escala, (REAL)PANEL_LABEL),
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

// estado do arraste manual da barra
static bool  g_arrastando = false;
static POINT g_origemMouse{};
static POINT g_origemJanela{};

// Os botões têm 30px de lado separados por 3px de gap, dentro de uma barra de
// 44px. A área de acerto era exata na vertical: um clique 1px acima ou abaixo
// do ícone não pertencia a botão nenhum, virava arraste e DESAPARECIA — é a
// causa do "às vezes clico e não responde".
//
// Agora TOL_X fecha os 3px de gap e TOL_Y abre na vertical até as bordas, ou
// seja, a barra inteira é área de clique. Quem arrasta é o arraste manual em
// WM_MOUSEMOVE, que só começa depois de 4px de movimento: clicar em qualquer
// ponto acerta um botão e arrastar continua funcionando.
static Button* BotaoMaisProximo(std::vector<Button>& v, const POINT& pt) {
    // ambos derivam do layout, então continuam corretos em qualquer escala:
    const int TOL_X = g_vertical ? (PAD_X + 1) : GAP;
    const int TOL_Y = g_vertical ? GAP : (PAD_Y + 1);
    for (auto& b : v)
        if (pt.x >= b.rc.left - TOL_X && pt.x <= b.rc.right + TOL_X &&
            pt.y >= b.rc.top - TOL_Y && pt.y <= b.rc.bottom + TOL_Y)
            return &b;
    return nullptr;
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

    if (g_vertical) {
        // em pé não sobra espaço em cima: o painel sai para o lado que tiver
        // folga e, se não couber em nenhum, fica à direita mesmo
        RECT work{};
        SystemParametersInfoW(SPI_GETWORKAREA, 0, &work, 0);
        px = (br.x + 8 + pw <= work.right) ? (br.x + 8) : (tl.x - pw - 8);
        py = (tl.y + br.y) / 2 - ph / 2;
    }

    g_panel = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
                              kClassePainel, L"Adobe", WS_POPUP,
                              px, py, pw, ph, g_hwnd, nullptr, g_hInst, nullptr);
    if (!g_panel) return;

    ShowWindow(g_panel, SW_SHOWNOACTIVATE);
    Compor(g_panel, pw, ph, true);
}

// Encosta a barra na borda da área de trabalho mais próxima, quando ela foi
// solta perto o bastante. O limite é generoso de propósito: a ideia é que
// "quase na borda" já vire "na borda", sem exigir acertar no pixel.
static void ColarNaBorda(int& x, int& y) {
    if (!g_colarBordas || !g_hwnd) return;

    RECT r{ x, y, x + g_barW, y + g_barH };
    HMONITOR mon = MonitorFromRect(&r, MONITOR_DEFAULTTONEAREST);
    if (!mon) return;
    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(mon, &mi)) return;
    const RECT& w = mi.rcWork;

    const int MARGEM = 28;   // em pixels de tela, não acompanha a escala

    if (x - w.left <= MARGEM)                   x = w.left;
    else if (w.right - (x + g_barW) <= MARGEM)  x = w.right - g_barW;

    if (y - w.top <= MARGEM)                    y = w.top;
    else if (w.bottom - (y + g_barH) <= MARGEM) y = w.bottom - g_barH;
}

// Empurra a barra de volta para dentro da área de trabalho. Cobre o caso de a
// resolução mudar ou um monitor ser desconectado com a barra salva fora: sem
// isso ela ficaria inalcançável até alguém editar o registro na mão.
static void PrenderNaArea(int& x, int& y) {
    RECT r{ x, y, x + g_barW, y + g_barH };
    HMONITOR mon = MonitorFromRect(&r, MONITOR_DEFAULTTONEAREST);
    if (!mon) return;
    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(mon, &mi)) return;
    const RECT& w = mi.rcWork;

    if (x + g_barW > w.right)  x = w.right - g_barW;
    if (y + g_barH > w.bottom) y = w.bottom - g_barH;
    if (x < w.left) x = w.left;
    if (y < w.top)  y = w.top;
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

    // "manter sempre na área de trabalho": no fim das contas a barra precisa
    // estar dentro da tela, não importa o que estava salvo nem o tamanho novo
    if (g_manterNaArea) PrenderNaArea(x, y);

    SetWindowPos(g_hwnd, HWND_TOP, x, y, g_barW, g_barH,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
    AplicarCamada(g_hwnd);   // devolve a barra para a camada configurada
    Compor(g_hwnd, g_barW, g_barH, false);
}

// ---------------------------------------------------------------------------
// Procedimento da barra
// ---------------------------------------------------------------------------

static LRESULT CALLBACK BarraProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_ERASEBKGND:
        return 1;   // o conteúdo vem do UpdateLayeredWindow

    case WM_NCHITTEST:
        // a barra inteira é área de clique; o arraste é tratado à mão abaixo
        return HTCLIENT;

    case WM_LBUTTONDOWN: {
        SetCapture(hwnd);
        g_arrastando = false;
        GetCursorPos(&g_origemMouse);
        RECT r{};
        GetWindowRect(hwnd, &r);
        g_origemJanela = POINT{ r.left, r.top };
        // whileTap: guarda qual botão está apertado para ele afundar
        g_idxPressionado = -1;
        {
            POINT pt{ (short)LOWORD(lp), (short)HIWORD(lp) };
            if (Button* b = BotaoMaisProximo(g_buttons, pt))
                g_idxPressionado = (int)(b - g_buttons.data());
        }
        return 0;
    }

    case WM_MOUSEMOVE: {
        if (GetCapture() != hwnd) break;
        if (g_travado) return 0;   // travar no lugar: o clique continua de pé
        POINT agora{};
        GetCursorPos(&agora);
        int dx = agora.x - g_origemMouse.x;
        int dy = agora.y - g_origemMouse.y;
        // 4px de folga: o tremor natural da mão não pode cancelar o clique
        if (!g_arrastando && (dx > 4 || dx < -4 || dy > 4 || dy < -4)) {
            g_arrastando = true;
            if (g_panel) FecharPainel();   // o painel não acompanha o arraste
        }
        // Durante o arraste a barra vai para o topo de propósito: é onde ela
        // precisa estar para o dono escolher o lugar. Ao soltar, o tratamento
        // do WM_LBUTTONUP devolve ela para a camada configurada.
        if (g_arrastando)
            SetWindowPos(hwnd, HWND_TOPMOST,
                         g_origemJanela.x + dx, g_origemJanela.y + dy, 0, 0,
                         SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
        return 0;
    }

    case WM_LBUTTONUP: {
        bool arrastou = g_arrastando;
        g_arrastando = false;
        g_idxPressionado = -1;
        if (GetCapture() == hwnd) ReleaseCapture();
        // usa o ponto do PRÓPRIO evento, não a posição do cursor agora
        POINT pt{ (short)LOWORD(lp), (short)HIWORD(lp) };
        if (arrastou) {
            RECT r{};
            GetWindowRect(hwnd, &r);
            int nx = r.left, ny = r.top;
            ColarNaBorda(nx, ny);                  // encosta, se soltou perto
            if (g_manterNaArea) PrenderNaArea(nx, ny);
            if (nx != r.left || ny != r.top)
                SetWindowPos(hwnd, HWND_TOP, nx, ny, 0, 0,
                             SWP_NOSIZE | SWP_NOACTIVATE);
            SalvarPosicao(nx, ny);
            AplicarCamada(hwnd);   // solta a barra de volta na camada dela
        } else if (Button* b = BotaoMaisProximo(g_buttons, pt)) {
            if (b->onClick) b->onClick();
        }
        return 0;
    }

    case WM_CAPTURECHANGED:
        g_arrastando = false;
        g_idxPressionado = -1;
        return 0;

    case WM_DISPLAYCHANGE:
        if (g_manterNaArea) PosicionarBarra();
        return 0;

    case WM_SETTINGCHANGE:
        // só interessa quando a área de trabalho em si muda — barra de tarefas
        // mudou de tamanho ou de lado — não qualquer ajuste do sistema
        if (wp == SPI_SETWORKAREA && g_manterNaArea) PosicionarBarra();
        return 0;

    case WM_TIMER: {
        if (wp != IDT_HOVER) break;

        POINT pt{};
        GetCursorPos(&pt);
        RECT wr{};
        GetWindowRect(hwnd, &wr);
        bool dentro = PtIn(wr, pt);

        // efeito magnético: recalcula o alvo e anda um passo da mola
        POINT cli = pt;
        ScreenToClient(hwnd, &cli);
        AlvoIma(cli, dentro && !g_arrastando);
        const float saltoIma = PassoIma();

        // painel fecha sozinho quando o mouse sai dele e do botão Adobe
        if (g_panel) {
            RECT pr{};
            GetWindowRect(g_panel, &pr);
            bool noBotao = (g_idxAdobe >= 0) && [&] {
                RECT br{};
                const RECT& b = g_buttons[g_idxAdobe].rc;
                br = b;
                MapWindowPoints(hwnd, nullptr, (POINT*)&br, 2);
                return PertoDe(br, pt);
            }();
            if (!PertoDe(pr, pt) && !noBotao) FecharPainel();
        }

        bool mudou = false;
        if (dentro != g_hover) { g_hover = dentro; mudou = true; }

        // Sem animação de hover: o fundo fica sempre presente, idêntico, com o
        // mouse em cima ou não. Era esta revelação que fazia a barra "acender"
        // quando o cursor passava por cima.
        g_reveal = 1.0;
        bool animando = false;

        if (mudou || animando || saltoIma > 0.003f) Compor(hwnd, g_barW, g_barH, false);

        // 16ms (60 quadros) enquanto a mola corre, 50ms parada. Sem trocar o
        // intervalo o efeito fica aos saltos; sem voltar para 50ms ele ficaria
        // gastando processador para sempre com a barra parada.
        const UINT quer = (saltoIma > 0.0f) ? 16u : 50u;
        if (quer != g_intervaloTimer) {
            g_intervaloTimer = quer;
            SetTimer(hwnd, IDT_HOVER, quer, nullptr);
        }

        // mantém a barra na camada escolhida: por cima de tudo quando o "Ficar
        // por cima das janelas" está ligado, e fora do topo quando está
        // desligado (outro programa pode devolver o topo por conta própria)
        if (g_porCima) {
            if ((GetWindowLongPtrW(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST) == 0)
                SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        } else if ((GetWindowLongPtrW(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0) {
            AplicarCamada(hwnd);
        }

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
        // Mesmo problema da barra: lParam em coordenadas de tela, b.rc em
        // coordenadas de cliente.
        POINT pt{ (short)LOWORD(lp), (short)HIWORD(lp) };
        ScreenToClient(hwnd, &pt);
        if (BotaoMaisProximo(g_panelButtons, pt)) return HTCLIENT;
        return HTTRANSPARENT;
    }

    case WM_LBUTTONUP: {
        POINT pt = PontoMouse(hwnd);
        if (Button* b = BotaoMaisProximo(g_panelButtons, pt)) {
            auto fn = b->onClick;
            FecharPainel();
            if (fn) fn();
            return 0;
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

    g_hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
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
            SetWindowPos(g_hwnd, HWND_TOP, 0, 0, g_barW, g_barH,
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

// O motor do Windhawk localiza estas funções pelo nome MANGLED do C++, não pelo
// nome puro. Ele procura exatamente:
//     _Z10Wh_ModInitv  _Z12Wh_ModUninitv  _Z21Wh_ModSettingsChangedv
//
// Por isso NÃO podem ser `extern "C"` — com extern "C" o compilador exporta
// "Wh_ModInit" sem mangled, o motor não encontra, e a DLL é carregada mas nunca
// inicializada (a barra simplesmente não aparece).
//
// Basta `__declspec(dllexport)`: isso garante a exportação e mantém o mangling.
__declspec(dllexport) BOOL Wh_ModInit() {
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

__declspec(dllexport) void Wh_ModUninit() {
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

__declspec(dllexport) void Wh_ModSettingsChanged() {
    if (g_threadId) PostThreadMessageW(g_threadId, WM_RECARGAR, 0, 0);
    else { CarregarConfig(); CarregarIcones(); MonteBarra(); MontePainel(); }
}





