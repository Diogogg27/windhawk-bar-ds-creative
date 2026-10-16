# ============================================================
#  extrair-icones.ps1
#  Extrai os icones originais do SEU proprio computador.
#  Nada aqui e distribuido: cada pessoa extrai dos programas
#  que ja estao instalados na maquina dela.
# ============================================================
#  Uso:  powershell -NoProfile -ExecutionPolicy Bypass -File .\extrair-icones.ps1
#  Saida:  .\icons\*.png   e   .\icons\b64.txt
# ============================================================

$ErrorActionPreference = 'SilentlyContinue'
$out = Join-Path $PSScriptRoot 'icons'
New-Item -ItemType Directory -Path $out -Force | Out-Null

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Drawing.CompositeImage

Write-Host ''
Write-Host '  Extraindo icones dos programas instalados...' -ForegroundColor Cyan
Write-Host ''

# ---------- 1) icones extraidos de .exe ------------------------
$alvos = [ordered]@{
    ps           = 'D:\Programas ADOBE\Adobe Photoshop 2026\Photoshop.exe'
    ai           = 'D:\Programas ADOBE\Adobe Illustrator 2026\Support Files\Contents\Windows\Illustrator.exe'
    ae           = 'D:\Programas ADOBE\Adobe After Effects 2026\Support Files\AfterFX.exe'
    pr           = 'D:\Programas ADOBE\Adobe Premiere Pro 2026\Adobe Premiere Pro.exe'
    lr           = 'D:\Programas ADOBE\Adobe Lightroom CC\lightroom.exe'
    cc           = 'C:\Program Files\Adobe\Adobe Creative Cloud\ACC\Creative Cloud.exe'
    comet        = 'C:\Program Files\Perplexity\Comet\Application\comet.exe'
    chrome       = 'C:\Program Files\Google\Chrome\Application\chrome.exe'
    telegram     = 'D:\Telegram Desktop\Telegram.exe'
    neverwrite   = 'C:\Program Files\NeverWrite\NeverWrite.exe'
    arena        = 'C:\Program Files\Design Arena\pake-designarena.exe'
    onecommander = 'C:\Program Files\OneCommander\OneCommander.exe'
    notepad      = 'C:\Windows\System32\notepad.exe'
    aimp         = 'D:\Programas\AIMP MUSIC\AIMP\AIMP.exe'
    vlc          = 'D:\VLC\vlc.exe'
}

# caminhos que tem versao no nome -> procurar em runtime
$varreduras = [ordered]@{
    whatsapp = @{ Raiz = "$env:ProgramFiles\WindowsApps"; Padrão = '5319275A.WhatsAppDesktop_*'; Exe = 'WhatsApp.Root.exe' }
    fg       = @{ Raiz = "$env:LOCALAPPDATA\Figma";        Padrão = 'app-*';                  Exe = 'Figma.exe' }
}

$linhas = @()

foreach ($k in $alvos.Keys) {
    $p = $alvos[$k]
    if (-not (Test-Path $p)) { Write-Host ("  {0,-14} nao encontrado" -f $k) -ForegroundColor DarkGray; continue }
    try {
        $ico = [System.Drawing.Icon]::ExtractAssociatedIcon($p)
        if (-not $ico) { continue }
        $png = Join-Path $out "$k.png"
        $bmp = $ico.ToBitmap(); $bmp.Save($png, [System.Drawing.Imaging.ImageFormat]::Png)
        $bmp.Dispose(); $ico.Dispose()
        $linhas += "$k=$([Convert]::ToBase64String([IO.File]::ReadAllBytes($png)))"
        Write-Host ("  {0,-14} ok" -f $k) -ForegroundColor Green
    } catch { Write-Host ("  {0,-14} falhou" -f $k) -ForegroundColor DarkYellow }
}

foreach ($k in $varreduras.Keys) {
    $v = $varreduras[$k]
    $pasta = Get-ChildItem $v.Raiz -Directory -Filter $v.Padrão -EA SilentlyContinue | Sort-Object Name -Descending | Select-Object -First 1
    if (-not $pasta) { Write-Host ("  {0,-14} nao encontrado" -f $k) -ForegroundColor DarkGray; continue }
    $exe = Join-Path $pasta.FullName $v.Exe
    if (-not (Test-Path $exe)) { Write-Host ("  {0,-14} exe ausente" -f $k) -ForegroundColor DarkGray; continue }
    try {
        $ico = [System.Drawing.Icon]::ExtractAssociatedIcon($exe)
        $png = Join-Path $out "$k.png"
        $bmp = $ico.ToBitmap(); $bmp.Save($png, [System.Drawing.Imaging.ImageFormat]::Png)
        $bmp.Dispose(); $ico.Dispose()
        $linhas += "$k=$([Convert]::ToBase64String([IO.File]::ReadAllBytes($png)))"
        Write-Host ("  {0,-14} ok  (versao {1})" -f $k, $pasta.Name) -ForegroundColor Green
    } catch { Write-Host ("  {0,-14} falhou" -f $k) -ForegroundColor DarkYellow }
}

# ---------- 2) icones baixados dos sites oficiais --------------
#  OpenCode, alphaXiv e Maple nao sao .exe locais.
$web = [ordered]@{
    oc       = 'https://opencode.ai/apple-touch-icon-v3.png'
    alphaxiv = 'https://www.alphaxiv.org/favicon.ico'
    maple    = 'https://lh3.googleusercontent.com/7RtW7cKk05JD8bOFyM1vuea9Lg5BDcSROwHEtq-Y2X6UcuY4KRbunejLmfZ8_Nuft80i5pe4MEnRt9Z-fYZiUsJG=s128'
    arena    = 'https://www.google.com/s2/favicons?domain=designarena.ai&sz=128'
}

foreach ($k in $web.Keys) {
    $tmp = Join-Path $env:TEMP "ic_$k_$([IO.Path]::GetRandomFileName())"
    try {
        Invoke-WebRequest -Uri $web[$k] -OutFile $tmp -UseBasicParsing -EA Stop
        $img = [System.Drawing.Image]::FromFile($tmp)
        $novo = $img
        if ($img.Width -gt 128) {
            $novo = New-Object System.Drawing.Bitmap(128,128)
            $gr = [System.Drawing.Graphics]::FromImage($novo)
            $gr.InterpolationMode = 'HighQualityBicubic'
            $gr.DrawImage($img, 0, 0, 128, 128); $gr.Dispose()
        }
        $png = Join-Path $out "$k.png"
        $novo.Save($png, [System.Drawing.Imaging.ImageFormat]::Png)
        $novo.Dispose(); $img.Dispose()
        Remove-Item $tmp -Force
        $linhas += "$k=$([Convert]::ToBase64String([IO.File]::ReadAllBytes($png)))"
        Write-Host ("  {0,-14} ok  (web)" -f $k) -ForegroundColor Green
    } catch { Write-Host ("  {0,-14} falhou" -f $k) -ForegroundColor DarkYellow }
}

# ---------- 3) apaga o fundo branco que sobrar -----------------
#  Remove so o branco que encosta na borda, preservando glifos
#  internos (a letra do Photoshop, o telefone do WhatsApp etc).
$limiar = 232
foreach ($linha in $linhas) {
    $k = ($linha -split '=')[0]
    $f = Join-Path $out "$k.png"
    if (-not (Test-Path $f)) { continue }
    $img = [System.Drawing.Bitmap]::FromFile($f)
    $w = $img.Width; $h = $img.Height
    $vis = New-Object 'bool[,]' $w,$h
    $fila = New-Object System.Collections.Queue
    for ($x=0; $x -lt $w; $x++) { $fila.Enqueue(@($x,0)); $fila.Enqueue(@($x,($h-1))) }
    for ($y=0; $y -lt $h; $y++) { $fila.Enqueue(@(0,$y)); $fila.Enqueue(@(($w-1),$y)) }
    while ($fila.Count -gt 0) {
        $pt = $fila.Dequeue(); $px=[int]$pt[0]; $py=[int]$pt[1]
        if ($px -lt 0 -or $py -lt 0 -or $px -ge $w -or $py -ge $h) { continue }
        if ($vis[$px,$py]) { continue }
        $vis[$px,$py] = $true
        $c = $img.GetPixel($px,$py)
        if ($c.A -lt 8) {
            $fila.Enqueue(@(($px+1),$py)); $fila.Enqueue(@(($px-1),$py))
            $fila.Enqueue(@($px,($py+1))); $fila.Enqueue(@($px,($py-1)))
            continue
        }
        if ($c.R -lt $limiar -or $c.G -lt $limiar -or $c.B -lt $limiar) { continue }
        $min = [Math]::Min($c.R,[Math]::Min($c.G,$c.B))
        $img.SetPixel($px,$py,[System.Drawing.Color]::FromArgb([byte][Math]::Max(0,[int]$c.A*($limiar-$min)/24),$c.R,$c.G,$c.B))
        $fila.Enqueue(@(($px+1),$py)); $fila.Enqueue(@(($px-1),$py))
        $fila.Enqueue(@($px,($py+1))); $fila.Enqueue(@($px,($py-1)))
    }
    $tmp = "$f.tmp"
    $img.Save($tmp,[System.Drawing.Imaging.ImageFormat]::Png); $img.Dispose()
    Move-Item -LiteralPath $tmp -Destination $f -Force
    $idx = [array]::IndexOf($linhas, $linha)
    $linhas[$idx] = "$k=$([Convert]::ToBase64String([IO.File]::ReadAllBytes($f)))"
}

Set-Content (Join-Path $out 'b64.txt') $linhas -Encoding ASCII

Write-Host ''
Write-Host ('  Pronto: {0} icones em {1}' -f $linhas.Count, $out) -ForegroundColor Cyan
Write-Host ''
