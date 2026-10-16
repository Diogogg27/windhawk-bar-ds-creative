Add-Type -AssemblyName System.Drawing

$out = "C:\Users\diogo\.superpowers\brainstorm\windhawk-bar\icons"
$repoImgs = "C:\Users\diogo\windhawk-bar-ds-creative\imagens"
New-Item -ItemType Directory -Path $repoImgs -Force | Out-Null

function Carrega-Ico([string]$k) {
    $p = Join-Path $out "$k.png"
    if (-not (Test-Path $p)) { return $null }
    return [System.Drawing.Image]::FromFile($p)
}

# ---------------- canvas ----------------
$W = 1500; $H = 210
$bmp = New-Object System.Drawing.Bitmap($W, $H)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.SmoothingMode = 'AntiAlias'
$g.TextRenderingHint = 'ClearTypeGridFit'
$g.PixelOffsetMode = 'HighQuality'

# fundo: gradiente escuro de desktop
$rect = New-Object System.Drawing.Rectangle(0,0,$W,$H)
$brushBg = New-Object System.Drawing.Drawing2D.LinearGradientBrush($rect,
    [System.Drawing.Color]::FromArgb(255,42,54,70), [System.Drawing.Color]::FromArgb(255,10,15,22), 35)
$g.FillRectangle($brushBg, $rect)

# vinheta suave
$pth = New-Object System.Drawing.Drawing2D.GraphicsPath
$pth.AddRectangle($rect)
$vig = New-Object System.Drawing.Drawing2D.PathGradientBrush($pth)
$vig.CenterColor = [System.Drawing.Color]::FromArgb(0,0,0,0)
$vig.SurroundColors = @(
    [System.Drawing.Color]::FromArgb(110,0,0,0),
    [System.Drawing.Color]::FromArgb(110,0,0,0),
    [System.Drawing.Color]::FromArgb(110,0,0,0),
    [System.Drawing.Color]::FromArgb(110,0,0,0))
$g.FillRectangle($vig, $rect)

# ---------------- geometria da barra ----------------
$tileW = 36; $tileH = 36; $gap = 4; $padX = 13; $padY = 11
$sepW = 1; $sepH = 19; $sepGap = 11

# grupos: 0=abertura de app, 1=adobe+figma, 2=favoritos, 3=sistema, 4=midia
$g1 = @('oc')
$g2 = @('cc','fg')
$g3 = @('comet','chrome','telegram','whatsapp','neverwrite','arena','onecommander','alphaxiv','maple','notepad')
$nG4 = 3   # lixeira, bloquear, desligar  (SVG)
$nG5 = 3   # anterior, tocar, proxima    (SVG)

$largura = $padX*2
$largura += $g1.Count*($tileW+$gap) + $g2.Count*($tileW+$gap) + $g3.Count*($tileW+$gap)
$largura += ($nG4+$nG5)*($tileW+$gap)
$largura += 4 * ($sepGap*2 + $sepW)

$barH = $tileH + $padY*2
$barX = [int](($W - $largura)/2)
$barY = $H - $barH - 44

# painel da barra (translucido escuro)
$barRect = New-Object System.Drawing.Rectangle($barX, $barY, $largura, $barH)
$brushBar = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(150,10,13,18))
$g.FillRectangle($brushBar, $barRect)

# borda fina de 1px
$penBorda = New-Object System.Drawing.Pen([System.Drawing.Color]::FromArgb(70,255,255,255), 1)
$g.DrawRectangle($penBorda, $barX, $barY, $largura-1, $barH-1)

# ---------------- desenha ----------------
$cx = $barX + $padX
$cy = $barY + $padY

function Desenha-Tile([System.Drawing.Graphics]$g, [int]$x, [int]$y, [string]$k) {
    $img = Carrega-Ico $k
    if (-not $img) { return }
    $r = 9
    $t = New-Object System.Drawing.Rectangle($x, $y, $script:tileW, $script:tileH)
    # pastilha escura com relevo
    $grad = New-Object System.Drawing.Drawing2D.LinearGradientBrush($t,
        [System.Drawing.Color]::FromArgb(46,255,255,255), [System.Drawing.Color]::FromArgb(18,0,0,0), 90)
    $g.FillRectangle($grad, $t)
    $penT = New-Object System.Drawing.Pen([System.Drawing.Color]::FromArgb(150,0,0,0), 1)
    $g.DrawRectangle($penT, $x, $y, $script:tileW-1, $script:tileH-1)
    # icone
    $m = 5
    $dst = New-Object System.Drawing.Rectangle(($x+$m), ($y+$m), ($script:tileW-$m*2), ($script:tileH-$m*2))
    $g.DrawImage($img, $dst)
    $img.Dispose()
}

function Desenha-Separador([System.Drawing.Graphics]$g, [int]$x, [int]$y) {
    $pen = New-Object System.Drawing.Pen([System.Drawing.Color]::FromArgb(80,255,255,255), 1)
    $g.DrawLine($pen, $x, $y, $x, ($y+$script:sepH))
}

foreach ($k in $g1) { Desenha-Tile $g $cx $cy $k; $cx += $tileW+$gap }
$cx += $sepGap; Desenha-Separador $g $cx $cy; $cx += $sepW+$sepGap
foreach ($k in $g2) { Desenha-Tile $g $cx $cy $k; $cx += $tileW+$gap }
$cx += $sepGap; Desenha-Separador $g $cx $cy; $cx += $sepW+$sepGap
foreach ($k in $g3) { Desenha-Tile $g $cx $cy $k; $cx += $tileW+$gap }
$cx += $sepGap; Desenha-Separador $g $cx $cy; $cx += $sepW+$sepGap

# --- icones de linha do sistema e da midia (SVG 1.5px -> pen 1.6) ---
$penLinha = New-Object System.Drawing.Pen([System.Drawing.Color]::FromArgb(235,255,255,255), 1.8)
$penLinha.StartCap = 'Round'; $penLinha.EndCap = 'Round'; $penLinha.LineJoin = 'Round'
$brushCheio = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(235,255,255,255))

function Centro([int]$x) { return ($x + [int]($script:tileW/2)) }

# lixeira
$c = Centro $cx
$g.DrawArc($penLinha, ($c-9), ($cy+14), 18, 8, 180, 180)
$g.DrawLine($penLinha, ($c-9), ($cy+17), ($c-7), ($cy+30))
$g.DrawLine($penLinha, ($c+9), ($cy+17), ($c+7), ($cy+30))
$g.DrawLine($penLinha, ($c-7), ($cy+30), ($c+7), ($cy+30))
$g.DrawLine($penLinha, ($c-4), ($cy+21), ($c-4), ($cy+27))
$g.DrawLine($penLinha, ($c+4), ($cy+21), ($c+4), ($cy+27))
$cx += $tileW+$gap

# bloquear
$c = Centro $cx
$g.DrawRectangle($penLinha, ($c-8), ($cy+19), 16, 12)
$g.DrawArc($penLinha, ($c-5), ($cy+10), 10, 12, 180, 180)
$cx += $tileW+$gap

# desligar
$c = Centro $cx
$g.DrawArc($penLinha, ($c-9), ($cy+9), 18, 18, 40, 280)
$g.DrawLine($penLinha, $c, ($cy+9), $c, ($cy+20))
$cx += $sepGap+$sepW+$sepGap

# anterior
$c = Centro $cx
$g.FillPolygon($brushCheio, @(
    (New-Object System.Drawing.Point(($c+7),($cy+11))),
    (New-Object System.Drawing.Point(($c-6),($cy+18))),
    (New-Object System.Drawing.Point(($c+7),($cy+25)))))
$g.DrawLine($penLinha, ($c-8), ($cy+11), ($c-8), ($cy+25))
$cx += $tileW+$gap

# tocar
$c = Centro $cx
$g.FillPolygon($brushCheio, @(
    (New-Object System.Drawing.Point(($c-5),($cy+10))),
    (New-Object System.Drawing.Point(($c+9),($cy+18))),
    (New-Object System.Drawing.Point(($c-5),($cy+26)))))
$cx += $tileW+$gap

# proxima
$c = Centro $cx
$g.FillPolygon($brushCheio, @(
    (New-Object System.Drawing.Point(($c-7),($cy+11))),
    (New-Object System.Drawing.Point(($c+6),($cy+18))),
    (New-Object System.Drawing.Point(($c-7),($cy+25)))))
$g.DrawLine($penLinha, ($c+8), ($cy+11), ($c+8), ($cy+25))

# ---------------- legenda ----------------
$fonte = New-Object System.Drawing.Font('Segoe UI', 11, [System.Drawing.FontStyle]::Regular)
$brushTxt = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(160,255,255,255))
$legenda = "Barra DS Creative  ·  20 icones originais  ·  fundo invisivel, aparece no hover"
$sz = $g.MeasureString($legenda, $fonte)
$g.DrawString($legenda, $fonte, $brushTxt, [int](($W-$sz.Width)/2), ($barY-34))

$g.Dispose()
$dest = Join-Path $repoImgs "print-barra.png"
$bmp.Save($dest, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
"  print-barra.png   $([math]::Round((Get-Item $dest).Length/1KB,1)) KB   ($W x $H)"
