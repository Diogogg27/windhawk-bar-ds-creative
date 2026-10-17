<div align="center">

# 🛠️ Barra DS Creative

**Uma barra de lançamento minimalista e de flutuação livre para o Windows 11.**
Deitada ou em pé, do tamanho que você quiser, na cor que você escolher.

Feita como mod do [Windhawk](https://windhawk.org). Sem emoji, sem firula —
só traços finos, ícones originais e atalhos onde importam.

<img src="imagens/print-barra.png" alt="Barra DS Creative" width="900">

</div>

---

## O que ela faz

Uma única linha flutuando sobre a área de trabalho, com **19 atalhos** divididos
em grupos por linhas de 1px:

```
[OpenCode] │ [Adobe▸] [Figma] │ [Comet][Chrome][Telegram][WhatsApp][NeverWrite][Arena][OneCommander][alphaXiv][Maple][Notepad] │ [🗑][🔒][⏻] │ [⏮][▶][⏭]
```

| Grupo | Conteúdo |
|---|---|
| **OpenCode** | Abre o Windows Terminal na sua pasta de projeto e retoma a última sessão |
| **Adobe** | Um botão só — o Creative Cloud abre um painel com Photoshop, Illustrator, After Effects, Premiere e Lightroom |
| **Favoritos** | Navegadores, mensageiros e ferramentas do dia a dia |
| **Meus atalhos** | Até 8 programas seus. O grupo só aparece quando você preenche algum |
| **Sistema** | Esvaziar lixeira, bloquear, desligar |
| **Mídia** | Anterior, tocar/pausar, próxima — funciona com qualquer player |

### Deitada ou em pé

A barra deitada mede **672×44**. Em pé mede **46×671** — a mesma barra com os
eixos trocados, e os separadores deitam junto. Medido com o mod rodando, não
estimado.

Em pé, o painel do Creative Cloud abre **ao lado** da barra em vez de abrir
acima: em pé não sobra espaço vertical, e o painel seria cortado pela borda da
tela.

### O fundo fica

A barra tem fundo **sempre visível**, com o tema, a textura e a opacidade que
você escolher. Passar o mouse por cima **não muda nada** — nem a opacidade, nem
o desenho.

### Clique em qualquer lugar, arraste segurando

**A barra inteira é área de clique.** Não existe zona morta: clicar 1px acima ou
abaixo de um ícone ativa o mesmo botão. Medido na 1.0.6 — antes disso, 13 dos 44
pixels de altura engoliam o clique em silêncio e a barra era arrastada no lugar.

Para **arrastar**, segure e mova mais de 4px. O tremor natural da mão não cancela
mais o clique, e um clique nunca move a barra sem querer.

A barra é de **flutuação livre**: arraste para qualquer lugar da tela. Ela guarda
a posição e volta para o mesmo lugar depois de reiniciar o explorer.

---

## Configurações

O Windhawk gera a tela de controle automaticamente. Tudo aplica **em tempo real**,
sem reiniciar nada.

### Temas de cor

Cada tema é um trio: cor do fundo, cor dos traços e cor da divisória. Trocar o
tema troca a barra inteira de uma vez.

| | | |
|---|---|---|
| **Personalizado** — usa as três cores soltas dos ajustes | **Escuro** — o visual de sempre | **Preto total** |
| **Grafite** | **Ardósia** | **Verde-noite** |
| **Vinho** | **Âmbar** | **Claro** |
| **Papel** | | |

Nos temas claros os **traços dos ícones ficam escuros**. Não é enfeite: traço
branco sobre fundo claro some. Medido — no tema Claro o fundo sai em `76,76,76` e
o traço mais escuro em `17`; no tema Preto total o fundo sai em `7,7,7` e o
traço mais claro em `255`.

As três cores do tema Personalizado aceitam `#RRGGBB` ou `RRGGBB`. Escrita
errada não quebra nada: cai no padrão.

### Escala da barra

De **70% a 150%**, em sete degraus. Muda tudo junto — botões, ícones, cantos,
espaçamentos e a área de clique. Os ícones de traço fino são desenhados de novo
no tamanho certo, então não ficam borrados.

### Atalhos personalizados

Até **8 programas seus**. Em cada campo, escreva:

```
Nome | C:\Caminho\do\programa.exe
```

O terceiro campo é opcional e diz de onde tirar o ícone, quando o `.exe` não tem
um bom:

```
Nome | C:\Caminho\programa.exe | C:\Outro\icone.exe
```

Se você escrever **só o caminho**, o nome sai do próprio arquivo. E o ícone é
**extraído do programa de verdade** — nada de ícone desenhado. Se a extração
falhar, aparece um marcador de contorno fino, para o botão nunca ficar invisível.

### Posição

| Ajuste | O que faz |
|---|---|
| **Barra em pé** | Deita ou levanta a barra inteira |
| **Colar nas bordas** | Ao soltar, a barra encosta na borda mais próxima (28px de margem). Arrastar além da borda também encosta |
| **Travar no lugar** | A barra não sai do lugar. O clique continua funcionando normalmente |
| **Manter na área de trabalho** | A barra nunca fica fora da área visível. Vale também quando a resolução muda ou um monitor é desconectado |

Se você travar a barra fora da tela, ligar **Manter na área de trabalho** traz ela
de volta.

### 10 texturas procedurais

Desenhadas em GDI+ na hora — sem arquivo de imagem, quase nada de peso. Todas
acompanham a cor do tema escolhido.

| | | | |
|---|---|---|---|
| Nenhuma | Vidro fosco | Fibra de carbono | Metal escovado |
| Perfurado | Linho | Papel | Diagonais |
| Malha | Granulado | | |

### Opacidade

Deslizador de **10% a 100%**, aplicado só ao fundo. Os ícones e as linhas ficam
sempre em 100%, então a barra nunca perde legibilidade por estar transparente.

### Mais

- Cor do fundo, dos traços e da divisória (no tema Personalizado)
- Mostrar em todas as áreas de trabalho
- Pasta de trabalho do OpenCode
- Pasta de ícones

---

## Efeito Starfield (fora do mod)

O mod **não tem mais** efeito de hover. Antes a barra era limpa no repouso e
acendia ao passar o mouse — luz percorrendo a borda, grade de pixels cintilando e
halo interno subindo em 600 ms. Isso trocava o visual inteiro a cada movimento do
mouse e foi removido.

O efeito continua no repositório como **demo avulso**, sem relação com o mod:

**[`starfield.html`](starfield.html)** — abra direto no navegador e passe o mouse.

<img src="imagens/print-starfield.png" alt="Efeito Starfield" width="760">

É o
[Starfield Button](https://www.originkit.dev/components/starfield-button)
da **Originkit**, portado de React/Framer Motion para JavaScript puro — o
repositório não tem build. As funções `pointOnRoundRect`, `buildCity`, `draw` e
`placeLights` são as da fonte original, não uma reescrita.

Ciano do preset: `#00EFFF` luz · `#83FFF5` pixels · `#00DFFF` halo.

---

## Instalação

1. Instale o [Windhawk](https://windhawk.org) se ainda não tiver
2. Abra o Windhawk → **Mods** → **Create new mod**
3. Cole o conteúdo de [`dscreative-bar.wh.cpp`](dscreative-bar.wh.cpp) e salve
4. O Windhawk compila com o MinGW embutido e instala
5. A barra aparece na hora — não precisa reiniciar nada

> O arquivo [`dscreative-bar.wh.cpp`](dscreative-bar.wh.cpp) é o mod completo.
> Compila sem nenhum erro e sem nenhum aviso com clang 20 / `-Wall -Wextra`.
> A especificação que o originou está em [`SPEC.md`](SPEC.md) — ela descreve o
> desenho original, incluindo o efeito de hover que foi removido depois.

---

## Ícones

Este repositório **não distribui nenhum ícone**. Os ícones dos programas são marcas
registradas da Adobe, Google, Meta, Telegram, Perplexity e de outros.

Cada pessoa extrai os ícones **dos programas que já estão instalados na máquina
dela**:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\extrair-icones.ps1
```

O script:

- Lê o ícone real de cada `.exe` instalado
- Resolve caminhos que mudam de versão (Figma, WhatsApp) sozinho
- Baixa os favicons dos sites que não são programa (OpenCode, alphaXiv)
- Remove o fundo branco só onde ele encosta na borda — preservando os glifos
  internos, como a letra do Photoshop e o telefone do WhatsApp
- Gera `icons\` e `icons\b64.txt`

Os **atalhos personalizados** não passam por esse script: o mod lê o ícone direto
do arquivo que você apontar.

---

## Requisitos

| Item | |
|---|---|
| Sistema | Windows 11 |
| Mod | [Windhawk](https://windhawk.org) 1.5+ |
| Terminal | Windows Terminal (para o botão do OpenCode) |
| Permissões | Nenhuma especial — roda sem elevação |

---

## Limitações conhecidas

- **Caminhos com versão no nome** (Figma, WhatsApp) são resolvidos em runtime;
  se o programa sumir, o botão não acha
- **Maple Bookmarks** é extensão de navegador — o botão abre a página da loja
- **Desligar** pede confirmação, e o Windows mostra aviso de UAC
- **Manter na área de trabalho** com o **colar nas bordas** desligado é a única
  combinação que deixa a barra sair da tela. É de propósito: é o que permite
  encostar metade dela fora, se você quiser

---

## Especificação

O documento completo de design e comportamento está em **[`SPEC.md`](SPEC.md)** —
janela, layout, ações, esquema de configuração, texturas, persistência e
critérios de aceite.

---

## Apoie o projeto

Se isso te poupar tempo, **paga um café** ☕

**Pix (Mercado Pago):**

```
diogogg27@gmail.com
```

<div align="center">

Obrigado por qualquer coisa — de verdade.

</div>

---

## Licença

MIT — use, modifique, distribua.

Os ícones dos programas citados pertencem aos seus respectivos donos e **não**
são distribuídos aqui.

---

<div align="center">
Feito por <b>Diogo Santos</b> · DS Creative
</div>
