[CmdletBinding()]
param(
  [Parameter(Mandatory = $true)]
  [string]$RepoUrl,

  [string]$Branch = "main",
  [string]$Message = "init",
  [string]$Path = (Get-Location).Path,

  [switch]$NoCommit,
  [switch]$DryRun
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Invoke-Git {
  param([Parameter(ValueFromRemainingArguments = $true)][string[]]$GitArgs)
  if ($DryRun) {
    Write-Host ("DRYRUN> git " + ($GitArgs -join " "))
    return
  }
  & git @GitArgs
  if ($LASTEXITCODE -ne 0) {
    throw "git command failed ($LASTEXITCODE): git $($GitArgs -join ' ')"
  }
}

function Test-GitAvailable {
  try {
    & git --version | Out-Null
    return $true
  }
  catch {
    return $false
  }
}

if (-not (Test-GitAvailable)) {
  throw "Git not found on PATH. Install Git for Windows and ensure 'git --version' works."
}

if (-not (Test-Path -LiteralPath $Path)) {
  throw "Path does not exist: $Path"
}

Set-Location -LiteralPath $Path

# 1) init
if (-not (Test-Path -LiteralPath (Join-Path $Path ".git"))) {
  Invoke-Git init
}

# 2) ensure .gitignore exists (only create when missing)
$gitignorePath = Join-Path $Path ".gitignore"
if (-not (Test-Path -LiteralPath $gitignorePath)) {
  $defaultGitignore = @(
    "# OS / Editor",
    "Thumbs.db",
    "Desktop.ini",
    ".DS_Store",
    "",
    "# VS Code / Visual Studio",
    ".vscode/",
    ".vs/",
    "",
    "# C/C++ build artifacts",
    "*.exe",
    "*.obj",
    "*.o",
    "*.out",
    "",
    "# Common outputs",
    "**/output/",
    ".cph/"
  ) -join "`r`n"

  if ($DryRun) {
    Write-Host "DRYRUN> create .gitignore"
  }
  else {
    $defaultGitignore | Out-File -FilePath $gitignorePath -Encoding utf8
  }
}

# 3) stage
Invoke-Git add -A

# 4) commit (optional)
if (-not $NoCommit) {
  $hasStagedChanges = $true
  try {
    if (-not $DryRun) {
      & git diff --cached --quiet
      if ($LASTEXITCODE -eq 0) { $hasStagedChanges = $false }
    }
  }
  catch {
    # ignore
  }

  if ($DryRun -or $hasStagedChanges) {
    try {
      Invoke-Git commit -m $Message
    }
    catch {
      # Most common case: nothing to commit
      if ($_.Exception.Message -notmatch "nothing to commit") {
        throw
      }
    }
  }
}

# 5) branch name
try {
  Invoke-Git branch -M $Branch
}
catch {
  # ignore
}

# 6) remote
$remoteExists = $false
if (-not $DryRun) {
  $remotes = & git remote 2>$null
  if ($LASTEXITCODE -eq 0 -and $remotes) {
    $remoteExists = ($remotes -split "\r?\n" | Where-Object { $_ -eq "origin" } | Measure-Object).Count -gt 0
  }
}

if ($DryRun) {
  Write-Host "DRYRUN> ensure origin remote = $RepoUrl"
}
else {
  if ($remoteExists) {
    Invoke-Git remote set-url origin $RepoUrl
  }
  else {
    Invoke-Git remote add origin $RepoUrl
  }
}

# 7) warn about large files in HEAD (if there is a commit)
if (-not $DryRun) {
  $hasHead = $true
  & git rev-parse --verify HEAD 2>$null | Out-Null
  if ($LASTEXITCODE -ne 0) { $hasHead = $false }

  if ($hasHead) {
    $large = @()
    $lines = & git ls-tree -r --long HEAD
    foreach ($line in $lines) {
      # format: <mode> <type> <object> <size>\t<path>
      $parts = $line -split "\t", 2
      if ($parts.Count -ne 2) { continue }
      $meta = $parts[0] -split "\s+"
      if ($meta.Count -lt 4) { continue }
      $size = 0
      if (-not [int64]::TryParse($meta[-1], [ref]$size)) { continue }
      if ($size -ge 50MB) {
        $large += [pscustomobject]@{ SizeMB = [math]::Round($size / 1MB, 2); Path = $parts[1] }
      }
    }
    if ($large.Count -gt 0) {
      Write-Warning "Large files (>=50MB) detected. GitHub recommends <=50MB and blocks >100MB. Consider Git LFS or ignoring large files."
      $large | Sort-Object SizeMB -Descending | Select-Object -First 10 | Format-Table -AutoSize | Out-Host
    }
  }
}

# 8) push
Invoke-Git push -u origin $Branch

Write-Host "Done: pushed to $RepoUrl ($Branch)"