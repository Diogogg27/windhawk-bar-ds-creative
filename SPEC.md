# Especificação — Barra DS Creative (mod do Windhawk)

> **Estado:** especificação aprovada. Nenhum código foi escrito ainda.
> **Autor do documento:** assistente, a partir do design aprovado em 16/10/2026.
> **Meta do Windhawk:** `dscreative-bar`

---

## 1. Visão geral

Uma barra de lançamento horizontal, minimalista e de flutuação livre, que vive
sobre a área de trabalho do Windows 11. Não é uma taskbar e não interage com ela.

| Característica | Decisão |
|---|---|
| Orientação | Horizontal, uma única linha |
| Posição | Flutuante, arrastável, lembra a posição ao reiniciar |
| Fundo | **Invisível por padrão**; o painel aparece **apenas no hover** |
| Estilo | Minimalista, traços finos e leves |
| Emoji | **Proibido** em qualquer lugar da interface |
| Ícones de programa | **Sempre o ícone original**, extraído do `.exe` real |
| Ícones de ação | SVG desenhado, traço **1,5px**, pontas arredondadas |
| Tema | Monocromático, com revelação no hover |

### Não faz parte

- Não se integra à taskbar nem a janelas de programas
- Não abre navegador embutido
- Não mostra notificações, relógio ou indicadores de sistema
- Não faz streaming de mídia — só envia comandos

---

## 2. Hospedagem

O mod roda como **hook dentro do `explorer.exe`**, que já está sempre em execução
e tem permissão para criar janelas e usar APIs de shell.

```
==WindhawkMod==
@id              dscreative-bar
@name            Barra DS Creative
@description     Barra de lançamento horizontal, minimalista e flutuante
@author          diogo
@include         explorer.exe
@compilerOptions -lcomctl32 -lshlwapi -lgdiplus -ldwmapi -lole32
==WindhawkMod==
```

O `explorer.exe` é escolhido porque:

1. Nunca falta — é o processo da área de trabalho
2. Consegue criar sua própria janela
3. Tem acesso às APIs de shell (`ShellExecute`, `SHGetKnownFolderPath`)
4. Já é alvo de mods do Windhawk, então o hook é estável

---

## 3. Janela

| Propriedade | Valor | Motivo |
|---|---|---|
| `WS_POPUP` | sim | sem borda nem moldura |
| `WS_EX_TOOLWINDOW` | sim | não aparece na taskbar nem no Alt+Tab |
| `WS_EX_TOPMOST` | sim | fica acima das janelas |
| `WS_EX_NOACTIVATE` | sim | clicar não rouba o foco da janela aberta |
| `WS_EX_LAYERED` | sim | permite a opacidade configurável |
| `WS_EX_TRANSPARENT` | dinâmico | ativo só quando **sem** mouse em cima, para clique atravessar |

**Clique atravessa a barra quando o mouse não está nela.** Isso é o que permite
a barra ficar parada sobre a área de trabalho sem bloquear nada. Ao detectar
`WM_MOUSEMOVE`, o mod remove `WS_EX_TRANSPARENT`; ao sair, devolve.

**Arrastar:** o `WM_NCHITTEST` devolve `HTCAPTION` para qualquer área que não
seja um botão. Assim o usuário arrasta a barra inteira sem escrever código de
arrasto manual, e o Windows cuida do snap e da maximização.

---

## 4. Layout

Grupos separados por **divisórias de 1px**, altura 16px, cor configurável.

```
[OpenCode] │ [Adobe▸] [Figma] │ [Comet][Chrome][Telegram][WhatsApp][NeverWrite][Arena][OneCommander][alphaXiv][Maple][Notepad] │ [🗑][🔒][⏻] │ [⏮][▶][⏭]
    A            B                                    C                                                  D                     E
```

| Grupo | Conteúdo |
|---|---|
| **A** | Botão do OpenCode (o mais à esquerda) |
| **B** | Creative Cloud (abre painel) + Figma |
| **C** | Favoritos — 10 botões com ícone real |
| **D** | Sistema — lixeira, bloquear, desligar (SVG) |
| **E** | Mídia — anterior, tocar/pausar, próxima (SVG) |

### 4.1 Painel do Adobe

O Creative Cloud é um **único botão**. Ao clicar, abre um painel **acima** da
barra contendo os cinco programas Adobe como botões grandes, **sem pastilha**
atrás do ícone — apenas uma sombra suave.

| Item | Caminho |
|---|---|
| Photoshop | `D:\Programas ADOBE\Adobe Photoshop 2026\Photoshop.exe` |
| Illustrator | `D:\Programas ADOBE\Adobe Illustrator 2026\Support Files\Contents\Windows\Illustrator.exe` |
| After Effects | `D:\Programas ADOBE\Adobe After Effects 2026\Support Files\AfterFX.exe` |
| Premiere Pro | `D:\Programas ADOBE\Adobe Premiere Pro 2026\Adobe Premiere Pro.exe` |
| Lightroom CC | `D:\Programas ADOBE\Adobe Lightroom CC\lightroom.exe` |
| Creative Cloud | `C:\Program Files\Adobe\Adobe Creative Cloud\ACC\Creative Cloud.exe` |

O painel fecha ao clicar fora, ao escolher um item ou ao tirar o mouse da região.

---

## 5. Inventário de ícones

**20 ícones**, todos originais e com fundo transparente.

| Chave | Programa | Origem do ícone |
|---|---|---|
| `oc` | OpenCode | `opencode.ai/apple-touch-icon-v3.png` — 180×180 |
| `cc` | Creative Cloud | extraído do `.exe` |
| `ps` | Photoshop | extraído do `.exe` |
| `ai` | Illustrator | extraído do `.exe` |
| `ae` | After Effects | extraído do `.exe` |
| `pr` | Premiere Pro | extraído do `.exe` |
| `lr` | Lightroom CC | extraído do `.exe` |
| `fg` | Figma | `figma.com/favicon.ico` — 64×64 |
| `comet` | Comet | extraído do `.exe` |
| `chrome` | Chrome | extraído do `.exe` |
| `telegram` | Telegram | extraído do `.exe` |
| `whatsapp` | WhatsApp | asset oficial da Store — 256px |
| `neverwrite` | NeverWrite | `NeverWrite\resources\icons\icon.png` — 512px |
| `arena` | Arena AI | favicon de `designarena.ai` — 128px |
| `maple` | Maple Bookmarks | ícone da Chrome Web Store — 128px |
| `alphaxiv` | alphaXiv | favicon de `alphaxiv.org` — 48px |
| `onecommander` | OneCommander | extraído do `.exe` |
| `notepad` | Bloco de notas | extraído do `notepad.exe` |
| `aimp` | AIMP | extraído do `.exe` (reserva) |
| `vlc` | VLC | extraído do `.exe` (reserva) |

Os ícones ficam embutidos no código como `HBITMAP` decodificado de PNG, ou
carregados de uma pasta `icons\` ao lado do mod — decidir na implementação
conforme o tamanho do binário.

---

## 6. Ações de lançamento

Todos os lançamentos usam `ShellExecuteW(NULL, L"open", exe, args, dir, SW_SHOWNORMAL)`.

### 6.1 Programas comuns

| Botão | Executável |
|---|---|
| Figma | resolver em runtime a pasta mais recente em `%LOCALAPPDATA%\Figma\app-*\Figma.exe` |
| Comet | `C:\Program Files\Perplexity\Comet\Application\comet.exe` |
| Chrome | `C:\Program Files\Google\Chrome\Application\chrome.exe` |
| Telegram | `D:\Telegram Desktop\Telegram.exe` |
| WhatsApp | `C:\Program Files\WindowsApps\5319275A.WhatsAppDesktop_*\WhatsApp.Root.exe` |
| NeverWrite | `C:\Program Files\NeverWrite\NeverWrite.exe` |
| Arena AI | `C:\Program Files\Design Arena\pake-designarena.exe` |
| OneCommander | `C:\Program Files\OneCommander\OneCommander.exe` |
| Bloco de notas | `C:\Windows\System32\notepad.exe` |

> **Figma:** o caminho tem a versão no nome (`app-126.9.11`). Ele **quebra a cada
> atualização**. O mod deve varrer `%LOCALAPPDATA%\Figma\` em cada clique e usar
> a pasta `app-*` de maior número de versão.

> **WhatsApp:** é o pacote da Microsoft Store. O caminho tem o número de versão;
> varrer `%ProgramFiles%\WindowsApps\5319275A.WhatsAppDesktop_*\`.

### 6.2 Sites

| Botão | URL |
|---|---|
| alphaXiv | `https://www.alphaxiv.org/` |
| Maple Bookmarks | `https://chromewebstore.google.com/detail/lgncmpklmepncbjpiebhdoejhmbcnjad` |

> **Maple Bookmarks não está instalada** em nenhum perfil do Comet, Chrome ou
> Edge. O botão abre a página da loja, onde ela é instalada com um clique.
> Depois de instalada, o comportamento pode ser trocado para abrir a extensão.

### 6.3 OpenCode

O botão abre o **Windows Terminal sem elevação**, na pasta de trabalho fixa,
e retoma a última sessão.

```powershell
wt.exe powershell -NoExit -Command "Set-Location 'H:\DS CREATIVE'; & 'C:\Users\diogo\AppData\Roaming\npm\node_modules\@opencode\cli\bin\opencode.exe' --continue"
```

| Detalhe | Valor |
|---|---|
| Pasta de trabalho | `H:\DS CREATIVE` |
| Binário | caminho completo do `opencode.exe` |
| Flag | `--continue` (retoma a última sessão **daquela pasta**) |
| Elevação | **não** — o usuário não é administrador |

**Sem elevação** porque o usuário `DSCREATIVE\diogo` não pertence a
`Administradores`. Uma janela elevada exigiria senha de administrador a cada
clique. O OpenCode funciona normalmente sem administração; só não consegue
rodar comandos que exijam privilégio elevado.

**Primeira execução:** `H:\DS CREATIVE` ainda não tem sessão salva, então o
`--continue` inicia uma sessão nova. A partir da segunda vez, retoma.

### 6.4 Ações do sistema

| Botão | Mecanismo |
|---|---|
| Esvaziar lixeira | `SHEmptyRecycleBinW(NULL, NULL, SHERB_NOCONFIRMATION \| SHERB_NOPROGRESSUI \| SHERB_NOSOUND)` |
| Bloquear | `LockWorkStation()` de `user32.dll` |
| Desligar | `InitiateSystemShutdownExW` com privilégio `SeShutdownPrivilege` |

A ação de **desligar pede confirmação** numa caixa simples antes de executar.
A de **esvaziar lixeira também** — sem isso, um clique acidental apaga tudo.

### 6.5 Mídia

Controles **apenas** — sem ícones de AIMP ou VLC.

| Botão | `lParam` enviado |
|---|---|
| Anterior | `APPCOMMAND_MEDIA_PREVIOUS_TRACK` |
| Tocar/Pausar | `APPCOMMAND_MEDIA_PLAY_PAUSE` |
| Próxima | `APPCOMMAND_MEDIA_NEXT_TRACK` |

Enviados como `WM_APPCOMMAND` via `PostMessageW` à janela em primeiro plano.
Funciona com AIMP, VLC, Spotify e o player embutido do navegador.

---

## 7. Configurações do mod

O Windhawk gera a tela de controle automaticamente a partir deste bloco YAML.
Nenhuma interface precisa ser programada.

```
==WindhawkModSettings==
- Textura:
    $name: Textura de fundo
    $description: Aplicada ao painel que surge no hover
    $type: choice
    $options:
      Nenhuma: 0
      Vidro fosco: 1
      Fibra de carbono: 2
      Metal escovado: 3
      Perfurado: 4
      Linho: 5
      Papel: 6
      Diagonais: 7
      Malha: 8
      Granulado: 9
    $default: 0
- Opacidade:
    $name: Opacidade da barra
    $description: 10 = quase invisível, 100 = totalmente opaco
    $type: int
    $min: 10
    $max: 100
    $default: 72
- OpacidadeHover:
    $name: Forçar 100% ao passar o mouse
    $description: Ignora o slider enquanto o mouse está em cima
    $type: bool
    $default: true
- CorDivisoria:
    $name: Cor da linha divisória
    $type: color
    $default: "#FFFFFF"
- MostrarSempreVisivel:
    $name: Mostrar em todas as áreas de trabalho
    $type: bool
    $default: true
- IgnorarCliqueMaximizar:
    $name: Ignorar clique de maximizar
    $description: Permite arrastar sobre janelas maximizadas
    $type: bool
    $default: true
- PastaOpenCode:
    $name: Pasta de trabalho do OpenCode
    $type: string
    $default: "H:\\DS CREATIVE"
==WindhawkModSettings==
```

Lidas em `Wh_ModInit` e relidas em `Wh_ModSettingsChanged` — trocar qualquer
valor aplica **em tempo real**, sem reiniciar o explorer.

---

## 8. Texturas

Todas são **procedurais**: desenhadas em GDI+ a partir de gradientes e pincéis,
sem arquivo de imagem externo. Custam quase nada em tamanho e memória.

| # | Nome | Desenho |
|---|---|---|
| 0 | Nenhuma | cor chapada com alpha |
| 1 | Vidro fosco | gradiente diagonal claro-claro-claro |
| 2 | Fibra de carbono | duas tramas de 45° cruzadas, preta e branca |
| 3 | Metal escovado | linhas horizontais de 1px a cada 3px + brilho lateral |
| 4 | Perfurado | grade de pontos escuros de 7px com brilho 1px deslocado |
| 5 | Linho | trama cruzada de 1px a cada 2px nos dois eixos |
| 6 | Papel | grão fino irregular, pontos claros e escuros |
| 7 | Diagonais | listras de 2px a cada 7px a 135° |
| 8 | Malha | grade quadriculada de 1px a cada 9px |
| 9 | Granulado | ruído de película via `feTurbulence` |

A textura é gerada **uma vez** num `HBITMAP` em memória no tamanho da barra e
reaproveitada a cada repaint. Regenerar só quando a opacidade ou o tamanho muda.

---

## 9. Opacidade

A opacidade vale para o **fundo do painel**. Ícones e linhas ficam sempre
nítidos, aplicados por cima.

| Situação | Opacidade aplicada |
|---|---|
| Barra parada, sem mouse | valor do slider |
| Mouse em cima da barra | `100%` se *Forçar 100% ao passar o mouse* estiver marcado, senão o slider |

Implementação: `SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA)`, onde
`alpha = slider * 255 / 100`.

---

## 10. Persistência

| O que | Onde |
|---|---|
| Posição X e Y | `Wh_SetIntSetting("PosicaoX"/"PosicaoY")` — não; usar registro próprio |

As configurações do Windhawk são só de leitura para o usuário. A posição, que
muda ao arrastar, é gravada no registro:

```
HKCU\Software\Windhawk\Engine\Mods\dscreative-bar
    PosicaoX  = REG_DWORD
    PosicaoY  = REG_DWORD
```

Lidas no `Wh_ModInit` antes de criar a janela. Se não existirem ou ficarem fora
da área útil de qualquer monitor, a barra abre **centralizada e no topo**.

A posição é gravada ao terminar o arraste (`WM_EXITSIZEMOVE`) e ao desligar o
explorer.

---

## 11. Restrições e cuidados conhecidos

| Risco | Cuidado |
|---|---|
| Caminho do Figma quebra ao atualizar | varrer `app-*` em runtime |
| Caminho do WhatsApp tem versão | varrer `5319275A.WhatsAppDesktop_*` |
| `D:\` é **somente-leitura** para o usuário | nenhum caminho do mod escreve no D: |
| Usuário **não é administrador** | OpenCode sem elevação; desligamento usa privilégio elevado com confirmação |
| Maple Bookmarks não instalada | botão abre a loja |
| Explorer reinicia e o hook some | o Windhawk reinicia o hook sozinho |

---

## 12. Instalação e build

1. Salvar o código como `dscreative-bar.wh.cpp`
2. Abrir o Windhawk → **Mods** → **Create new mod**
3. Colar o conteúdo e salvar
4. O Windhawk compila com o MinGW embutido e instala
5. O mod hooka o `explorer.exe` em execução, cria a janela e a barra aparece

Para desenvolver sem recompilar a cada passo: manter o Windhawk aberto em
**Editor** e usar o botão **Compile** — o `explorer.exe` recebe o hook na hora.

---

## 13. Critérios de aceite

- [ ] A barra aparece após instalar, sem reiniciar
- [ ] Arrastar move a barra; reiniciar o explorer mantém a posição
- [ ] O fundo fica invisível e aparece no hover
- [ ] Trocar textura e opacidade nas configurações aplica sem reiniciar
- [ ] Os 20 botões abrem o programa ou site certo
- [ ] O painel do Adobe abre acima e fecha ao clicar fora
- [ ] Lixeira e desligamento pedem confirmação
- [ ] Controles de mídia afetam o player em primeiro plano
- [ ] Clique fora da barra atravessa e alcança o que está atrás
