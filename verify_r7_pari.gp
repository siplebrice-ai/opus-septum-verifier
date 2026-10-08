\\ Independent PARI/GP verifier for the secondary-order-7 problem for (2,3).
\\ Usage: gp -q verify_r7_pari.gp < 64000000
\\ This intentionally uses PARI native znorder/znlog rather than the C++ CRT-root algorithm.
secondary7(p)=
{
  my(d2=znorder(Mod(2,p)), d3=znorder(Mod(3,p)), k);
  if(d2 != d3, return(0));
  k = znlog(Mod(3,p), Mod(2,p), [d2,factor(d2)]);
  if(type(k)=="t_VEC", return(0));
  return(znorder(Mod(k,d2)) == 7);
}

N=input();
countp=0; counteq=0; hits=List();
forprime(p=5,N-1,
  countp++;
  my(d2=znorder(Mod(2,p)), d3=znorder(Mod(3,p)));
  if(d2==d3,
    counteq++;
    my(k=znlog(Mod(3,p),Mod(2,p),[d2,factor(d2)]));
    if(type(k)!="t_VEC" && znorder(Mod(k,d2))==7,
      listput(hits,[p,d2,k]); print("HIT ", [p,d2,k]);
    );
  );
);
print("N=",N," primes_checked=",countp," equal_order=",counteq," hits=",#hits);
print(Vec(hits));
