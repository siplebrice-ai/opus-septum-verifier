import sympy as sp, math
p=551_194_727
k=217_192_027
d=275_597_363
assert sp.isprime(p)
assert sp.factorint(p-1)=={2:1,43:1,71:1,90271:1}
assert sp.n_order(2,p)==d
assert sp.n_order(3,p)==d
assert pow(2,k,p)==3
assert sp.n_order(k,d)==7
assert sp.n_order(k%43,43)==7
assert sp.n_order(k%71,71)==7
assert k%90271==1
assert d//math.gcd(d,k-1)==3053
assert sp.n_order((3*pow(2,-1,p))%p,p)==3053
print('verified first-hit arithmetic:', p, d, k, '(7,7,1)', 'm=3053')
