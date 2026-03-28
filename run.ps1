################################################################################
#  run.ps1  --  C++20 STL Quick Runner
#
#  Usage:
#    .\run.ps1 array              compile and run array.cpp
#    .\run.ps1 array.cpp          extension is optional
#    .\run.ps1 vector map set     run multiple files in one go
#    .\run.ps1 all                compile and run all 20 STL files
################################################################################

# Add MSYS2 to PATH so g++ and its runtime DLLs are found
$env:PATH = "C:\msys64\mingw64\bin;C:\msys64\usr\bin;$($env:PATH)"
$GXX = "g++"

$STL_FILES = @(
    "array","bitset","deque","forward_list","list","map","multimap",
    "multiset","numeric_algorithms","pair_tuple","priority_queue","queue",
    "set","stack","string","unordered_map","unordered_multimap",
    "unordered_multiset","unordered_set","vector"
)

# Show help when no argument given
if ($args.Count -eq 0) {
    Write-Host ""
    Write-Host "  C++20 STL Runner" -ForegroundColor Cyan
    Write-Host "  Usage:"
    Write-Host "    .\run.ps1 <name>        -- compile and run one file"
    Write-Host "    .\run.ps1 n1 n2 ...     -- compile and run multiple"
    Write-Host "    .\run.ps1 all           -- compile and run all 20 STL files"
    Write-Host ""
    Write-Host "  Available:" -ForegroundColor Yellow
    $STL_FILES | ForEach-Object { Write-Host "    $_" }
    Write-Host ""
    exit 0
}

# Expand 'all' keyword
$targets = if ($args -contains "all") { $STL_FILES } else { [string[]]$args }
# Strip .cpp extension if provided
$targets = $targets | ForEach-Object { ($_ -replace '\.cpp$','').Trim() }

$pass = 0; $fail = 0; $total = $targets.Count
$dir  = $PSScriptRoot

foreach ($name in $targets) {
    $src = Join-Path $dir "$name.cpp"
    $exe = Join-Path $dir "$name.exe"

    Write-Host ""
    Write-Host ("=" * 56) -ForegroundColor DarkGray
    Write-Host "  $name.cpp" -ForegroundColor Cyan
    Write-Host ("=" * 56) -ForegroundColor DarkGray

    # Check source exists
    if (-not (Test-Path $src)) {
        Write-Host "  ERROR: '$name.cpp' not found." -ForegroundColor Red
        Write-Host "  Run .\run.ps1 with no args to list available files." -ForegroundColor Yellow
        $fail++
        continue
    }

    # Compile using & operator with g++ on PATH
    Write-Host "  Compiling ... " -ForegroundColor DarkYellow -NoNewline
    $compileOutput = & $GXX -std=c++20 -O2 -Wall -o $exe $src 2>&1
    $compileOk = ($LASTEXITCODE -eq 0)

    if (-not $compileOk) {
        Write-Host "FAILED" -ForegroundColor Red
        Write-Host ""
        $compileOutput | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
        $fail++
        continue
    }
    Write-Host "OK" -ForegroundColor Green
    Write-Host ""

    # Run the compiled binary
    & $exe
    $ec = $LASTEXITCODE

    # Delete exe to keep repo clean (no binaries committed)
    Remove-Item $exe -Force -ErrorAction SilentlyContinue

    Write-Host ""
    if ($ec -eq 0) {
        Write-Host "  [DONE]" -ForegroundColor Green
        $pass++
    } else {
        Write-Host "  [Exit code: $ec]" -ForegroundColor Red
        $fail++
    }
}

# Summary only when running multiple files
if ($total -gt 1) {
    Write-Host ""
    Write-Host ("=" * 56) -ForegroundColor DarkGray
    $col = if ($fail -eq 0) { "Green" } else { "Yellow" }
    Write-Host "  RESULTS: $pass / $total passed" -ForegroundColor $col
    if ($fail -gt 0) { Write-Host "  FAILED:  $fail" -ForegroundColor Red }
    Write-Host ("=" * 56) -ForegroundColor DarkGray
    Write-Host ""
}
