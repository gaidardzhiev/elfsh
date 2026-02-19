#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
typedef unsigned char u8;typedef unsigned u32;typedef unsigned long u64;typedef size_t Z;typedef int I;typedef const char*Q;
typedef struct{u8 d[8192];Z l;}B;void bi(B*b){b->l=0;}void bp(B*b,const void*p,Z n){memcpy(b->d+b->l,p,n);b->l+=n;}void b8(B*b,u8 x){bp(b,&x,1);}char*cs(B*b){b8(b,0);char*s=malloc(b->l);if(!s)exit(1);memcpy(s,b->d,b->l);s[b->l-1]=0;bi(b);return s;}void pw(B*b,Z o,u32 v){b->d[o]=v;b->d[o+1]=v>>8;b->d[o+2]=v>>16;b->d[o+3]=v>>24;}

typedef struct{B b;}C;
C *c;
#define C8(x) b8(&c->b,x)
#define C32(x) bp(&c->b,&(u32){x},4)
#define C64(x) bp(&c->b,&(u64){x},8)
#define B2(a,b) C8(a);C8(b)
#define B3(a,b,c) C8(a);C8(b);C8(c)
#define B4(a,b,c,d) C8(a);C8(b);C8(c);C8(d)
#define POS() (c->b.l)

typedef struct{B p;}S;Z sa(S*s,Q x){Z o=s->p.l;bp(&s->p,x,strlen(x)+1);return o;}

typedef struct{char*v[32];I n;}SV;void sv(SV*s,char*x){s->v[s->n++]=x;}typedef struct{SV a;}St;typedef struct{St v[4];I n;}Pl;typedef struct{Pl p;I c;}En;typedef struct{En v[16];I n;}Sc;void pp(Pl*p,St s){p->v[p->n++]=s;}void spush(Sc*s,Pl p,I c){s->v[s->n++]=(En){p,c};}

I t(char c){return !c||c==' '||c=='\t'||c=='\r'||c=='\n'||c=='|'||c==';'||c=='<'||c=='>'||c=='&';}
char*w(Q*p){B b;bi(&b);Q q=*p;while(*q){if(*q=='"'){q++;while(*q&&*q!='"')b8(&b,*q++);if(*q=='"')q++;continue;}if(t(*q))break;b8(&b,*q++);}if(!b.l)return NULL;char*w=cs(&b);*p=q;return w;}
void f(Pl*pl,St*st){if(!st->a.n)return;pp(pl,*st);*st=(St){0};}
Sc p(Q src){Sc sc={0};Pl cur={0};St st={0};Q p=src;I cond=0;while(*p){while(*p==' '||*p=='\t'||*p=='\r')p++;if(!*p)break;if(*p=='#'){while(*p&&*p!='\n')p++;continue;}if(*p=='\n'||*p==';'){if(st.a.n)f(&cur,&st);if(cur.n){spush(&sc,cur,cond);cur=(Pl){0};cond=0;}while(*p=='\n'||*p==';')p++;continue;}if(*p=='&'&&p[1]=='&'){f(&cur,&st);spush(&sc,cur,cond);cur=(Pl){0};cond=1;p+=2;continue;}if(*p=='|'&&p[1]=='|'){f(&cur,&st);spush(&sc,cur,cond);cur=(Pl){0};cond=2;p+=2;continue;}if(*p=='|'){f(&cur,&st);p++;continue;}if(*p=='>'||*p=='<'){p++;if(*p=='>')p++;while(*p&&!t(*p))p++;continue;}char*t=w(&p);if(!t)break;sv(&st.a,t);}if(st.a.n)f(&cur,&st);if(cur.n)spush(&sc,cur,cond);return sc;}

#define A(x) B3(0x48,0xC7,0xC0);C32(x)
#define D(x) B2(0x48,0xBF);C64(x)
#define S(x) B2(0x48,0xBE);C64(x)
#define X(x) B2(0x48,0xBA);C64(x)
#define V() B3(0x48,0x31,0xD2)
#define W() B3(0x4D,0x31,0xD2)
#define R_() B3(0x48,0x89,0xFE)
#define P_() B3(0x48,0x89,0xC7)
#define H() B2(0x8B,0x07)
#define Y() B2(0x0F,0x05)
#define UO BB+ST
#define M(o,v) memcpy(E+o,&(u64){v},8)
#define PW(o,v) pw(&f,o,v)
Z J(u8 o){C8(0x0F);C8(o);Z p=POS();C32(0);return p;}
void PHC(Z a){pw(&c->b,a,(u32)(POS()-(a+4)));}
void MM(u32 d){C8(0x48);C8(0x89);C8(0x87);C32(d);}
#define SC(n) A(n);Y()
#define FK(x) SC(57);B4(0x48,0x83,0xF8,0);Z x=J(0x85)

typedef struct{C c;S s;Z bb,bo,st;}G;G g;C*c=&g.c;
#define BB g.bb
#define BO g.bo
#define ST g.st
#define SS g.s
Z a(Q s){return sa(&SS,s);}
void q(Z s){D(BB+s);SC(59);D(1);SC(60);}
void z(){D(UO);H();C8(0x48);C8(0xC1);C8(0xE8);C8(8);C8(0x25);C32(0xFF);D(UO);MM(0);}
void ex(St*s,Z aoff){I n=s->a.n;D(BB+aoff);for(I i=0;i<n;i++){C8(0x48);C8(0xB8);C64(BB+a(s->a.v[i]));MM((u32)(i*8));}A(0);MM((u32)(n*8));R_();X(BB+aoff+n*8);Q c=s->a.v[0];if(strchr(c,'/')){q(a(c));return;}char b[64];sprintf(b,"/bin/%s",c);q(a(b));}
void m(St*s,Z aoff){FK(jp);ex(s,aoff);PHC(jp);P_();S(UO);V();W();SC(61);z();}
void h(Pl*p){Z pa=BO;BO+=16;D(BB+pa);SC(22);FK(j1);D(BB+pa+4);H();P_();S(1);SC(33);D(BB+pa+0);H();P_();SC(3);Z a=BO;BO+=8*(p->v[0].a.n+1);ex(&p->v[0],a);PHC(j1);D(BB+pa+4);H();P_();SC(3);FK(j2);D(BB+pa+0);H();P_();S(0);SC(33);D(BB+pa+0);H();P_();SC(3);a=BO;BO+=8*(p->v[1].a.n+1);ex(&p->v[1],a);PHC(j2);D(BB+pa+0);H();P_();SC(3);P_();S(UO);V();W();SC(61);z();}
void el(Q o){Z co=0xB0,cl=g.c.b.l,ro=(co+cl+4095)&~4095,rl=SS.p.l;B f={0};f.l=ro+rl;memcpy(f.d+co,g.c.b.d,cl);memcpy(f.d+ro,SS.p.d,rl);u8*E=f.d;E[0]=0x7F;E[1]='E';E[2]='L';E[3]='F';E[4]=2;E[5]=1;E[6]=1;PW(0x10,2);PW(0x12,0x3E);PW(0x14,1);M(0x18,0x400000+co);M(0x20,0x40);PW(0x34,0x40);PW(0x36,0x38);PW(0x38,2);PW(0x40,1);PW(0x44,5);M(0x48,0);M(0x50,0x400000);M(0x58,0x400000);M(0x60,ro);M(0x68,ro);M(0x70,0x1000);PW(0x78,1);PW(0x7C,6);M(0x80,ro);M(0x88,BB);M(0x90,BB);M(0x98,rl);M(0xA0,BO>rl?BO:rl);M(0xA8,1);FILE*f2=fopen(o,"wb");if(!f2)exit(1);fwrite(f.d,1,f.l,f2);fclose(f2);chmod(o,0755);}
void ge(Sc*sc){BO=768;ST=BO;BO+=8;for(I i=0;i<sc->n;i++){En*e=&sc->v[i];Pl*p=&e->p;Z sk=0;if(e->c){D(UO);H();C8(0x85);C8(0xC0);sk=e->c==1?J(0x85):J(0x84);}if(p->n==1){St*st=&p->v[0];Z a=BO;BO+=8*(st->a.n+1);m(st,a);}else h(p);if(sk)PHC(sk);}D(0);SC(60);}
char*rf(Q p){FILE*f=fopen(p,"rb");if(!f)exit(1);fseek(f,0,SEEK_END);long n=ftell(f);fseek(f,0,SEEK_SET);char*b=malloc(n+1);if(!b)exit(1);fread(b,1,n,f);b[n]=0;fclose(f);return b;}
I main(I a,char**v){char*o=a>3?v[3]:"a.out";Sc sc=p(rf(v[1]));BB=0x600000;ge(&sc);el(o);return 0;}
