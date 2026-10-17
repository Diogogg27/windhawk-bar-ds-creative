<div align="center">

# 🛠️ Barra DS Creative

**Uma barra de lançamento horizontal, minimalista e de flutuação livre para o Windows 11.**

Feita como mod do [Windhawk](https://windhawk.org). Sem emoji, sem firula —
só traços finos, ícones originais e atalhos onde importam.

<img src="imagens/print-barra.png" alt="Barra DS Creative" width="900">

</div>

---

## O que ela faz

Uma única linha flutuando sobre a área de trabalho, com **20 atalhos** divididos
em grupos por linhas de 1px:

```
[OpenCode] │ [Adobe▸] [Figma] │ [Comet][Chrome][Telegram][WhatsApp][NeverWrite][Arena][OneCommander][alphaXiv][Maple][Notepad] │ [🗑][🔒][⏻] │ [⏮][▶][⏭]
```

| Grupo | Conteúdo |
|---|---|
| **OpenCode** | Abre o Windows Terminal na sua pasta de projeto e retoma a última sessão |
| **Adobe** | Um botão só — o Creative Cloud abre um painel **acima** com Photoshop, Illustrator, After Effects, Premiere e Lightroom |
| **Favoritos** | Navegadores, mensageiros e ferramentas do dia a dia |
| **Sistema** | Esvaziar lixeira, bloquear, desligar |
| **Mídia** | Anterior, tocar/pausar, próxima — funciona com qualquer player |

### O fundo fica

A barra tem fundo **sempre visível**, com a textura e a opacidade que você
escolher. Passar o mouse por cima **não muda nada** — nem a opacidade, nem o
desenho.

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

### 10 texturas procedurais

Desenhadas em GDI+ na hora — sem arquivo de imagem, quase nada de peso.

| | | | |
|---|---|---|---|
| Nenhuma | Vidro fosco | Fibra de carbono | Metal escovado |
| Perfurado | Linho | Papel | Diagonais |
| Malha | Granulado | | |

### Opacidade

Deslizador de **10% a 100%**, aplicado só ao fundo. Os ícones e as linhas ficam
sempre em 100%, então a barra nunca perde legibilidade por estar transparente.

### Mais

- Cor da linha divisória
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

Este repositório **não distribui nenhum ícone**. Os 20 ícones são marcas
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
