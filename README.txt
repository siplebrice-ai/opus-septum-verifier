Opus Septum computational supplement
=====================================

Target definition
-----------------
For an equal-order prime p with d=ord_p(2)=ord_p(3), let k mod d satisfy
2^k = 3 (mod p). The secondary order is R_p(2,3)=ord_d(k).

First exact order-seven example
-------------------------------
p = 551,194,727
d = 275,597,363 = 43*71*90271
k = 217,192,027
CRT local orders: (7,7,1)
active displacement order m = ord_p(3/2) = 3053 = 43*71

Minimality search
-----------------
The exhaustive C++ verifier constructs all nonidentity seventh roots modulo the
common order d via prime-power roots + CRT, then directly tests 2^k=3 mod p.
It does not assume or solve a general discrete logarithm.

Retained ranges:
  p < 200,000,000: no hit
  200,000,000 <= p < 400,000,000: no hit
  400,000,000 <= p <= 551,194,727: one hit, at 551,194,727

Combined counts through the first hit:
  primes checked: 28,904,954
  equal-order primes: 8,178,941
  7-eligible equal-order primes: 2,386,472
  exact seventh-root candidates tested: 27,534,678
  hits: 1

Random-unit calibration through the first hit:
  E_7 = 2.27066800220848

Files
-----
verify_r7.cpp             original 0-to-N verifier
verify_r7_range.cpp       range-aware verifier used for extension search
verify_r7_expected.cpp    range verifier that also sums random-unit expectation
verify_r7_pari.gp         independent PARI/GP route (source retained; not claimed executed here)
check_first_hit.py        direct independent arithmetic check using SymPy
*.log                     retained search/calibration outputs
SHA256SUMS.txt            hashes for all files in this bundle
