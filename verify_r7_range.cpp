#include <bits/stdc++.h>
using namespace std; using u64=uint64_t; using u128=__uint128_t;
u64 mulm(u64 a,u64 b,u64 m){return (u128)a*b%m;} u64 powm(u64 a,u64 e,u64 m){u64 r=1;for(;e;e>>=1,a=mulm(a,a,m))if(e&1)r=mulm(r,a,m);return r;}
u64 gcdx(u64 a,u64 b){while(b){u64 t=a%b;a=b;b=t;}return a;}
u64 invm(u64 a,u64 m){ long long t=0,nt=1,r=m,nr=a; while(nr){long long q=r/nr; auto z=t-q*nt;t=nt;nt=z; auto w=r-q*nr;r=nr;nr=w;} if(t<0)t+=m; return t; }
vector<pair<u64,int>> factor_using_spf(u64 n,const vector<int>& primes){vector<pair<u64,int>> f;for(int q:primes){if((u64)q*q>n)break;if(n%q==0){int e=0;do{n/=q;e++;}while(n%q==0);f.push_back({(u64)q,e});}}if(n>1)f.push_back({n,1});return f;}
u64 order_mod(u64 a,u64 p,u64 pm1,const vector<pair<u64,int>>& f){u64 d=pm1;for(auto [q,e]:f)for(int i=0;i<e;i++){if(d%q==0 && powm(a,d/q,p)==1)d/=q;else break;}return d;}
u64 primitive_root_prime_power(u64 q,int e){ // odd q only
 u64 mod=1;for(int i=0;i<e;i++)mod*=q; u64 phi=mod/q*(q-1); vector<u64> pf; u64 x=phi; for(u64 r=2;r*r<=x;r+=(r==2?1:2))if(x%r==0){pf.push_back(r);while(x%r==0)x/=r;}if(x>1)pf.push_back(x);
 for(u64 g=2;;g++){if(gcdx(g,mod)!=1)continue;bool ok=1;for(u64 r:pf)if(powm(g,phi/r,mod)==1){ok=0;break;}if(ok)return g;}
}
vector<u64> roots7(u64 d,const vector<int>& primes){auto f=factor_using_spf(d,primes); vector<pair<u64,vector<u64>>> comps;
 for(auto [q,e]:f){u64 mod=1;for(int i=0;i<e;i++)mod*=q;u64 phi=mod/q*(q-1);vector<u64> rs={1};if(phi%7==0){u64 g=primitive_root_prime_power(q,e);u64 z=powm(g,phi/7,mod);rs.clear();u64 x=1;for(int j=0;j<7;j++){rs.push_back(x);x=mulm(x,z,mod);}}comps.push_back({mod,rs});}
 vector<pair<u64,u64>> cur={{0,1}};for(auto &C:comps){u64 m2=C.first;vector<pair<u64,u64>> nxt;for(auto [a,m1]:cur)for(u64 b:C.second){u64 t=mulm((b + m2 - a%m2)%m2,invm(m1%m2,m2),m2);u64 nm=m1*m2;u64 na=(a+m1*t)%nm;nxt.push_back({na,nm});}cur.swap(nxt);}vector<u64> out;for(auto [a,m]:cur)if(a%d!=1%d)out.push_back(a%d);return out;}
int main(int argc,char**argv){u64 START=argc>1?stoull(argv[1]):5;u64 N=argc>2?stoull(argv[2]):1000000;int lim=sqrt((long double)N)+2;vector<bool> isp(lim+1,true);vector<int> primes;isp[0]=isp[1]=false;for(int i=2;i<=lim;i++)if(isp[i]){primes.push_back(i);if((long long)i*i<=lim)for(int j=i*i;j<=lim;j+=i)isp[j]=false;}
 const u64 B=1<<20;u64 pc=0,eq=0,eligible=0,root_tests=0;vector<tuple<u64,u64,u64>> hits;auto start=chrono::steady_clock::now();
 u64 firstL=(START/B)*B; if(firstL<2) firstL=2;
 for(u64 L=firstL;L<N;L+=B){u64 R=min(N,L+B);vector<char> seg(R-L,1);for(int q:primes){u64 qq=q;u64 s=max(qq*qq,((L+qq-1)/qq)*qq);if(s>=R)continue;for(u64 x=s;x<R;x+=qq)seg[x-L]=0;}for(u64 p=max(L,START);p<R;p++)if(seg[p-L] && p>=5){pc++;auto f=factor_using_spf(p-1,primes);u64 d2=order_mod(2,p,p-1,f),d3=order_mod(3,p,p-1,f);if(d2!=d3)continue;eq++;u64 d=d2;auto rs=roots7(d,primes);if(rs.empty())continue;eligible++;for(u64 k:rs){root_tests++;if(powm(2,k,p)==3%p){hits.push_back({p,d,k});cout<<"HIT p="<<p<<" d="<<d<<" k="<<k<<"\n";}}}}
 auto secs=chrono::duration<double>(chrono::steady_clock::now()-start).count();cout<<"START="<<START<<" N="<<N<<" primes_checked="<<pc<<" equal_order="<<eq<<" eligible="<<eligible<<" root_tests="<<root_tests<<" hits="<<hits.size()<<" seconds="<<secs<<"\n";return 0;}
