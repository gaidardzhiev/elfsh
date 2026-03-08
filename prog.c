#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include "elfsh.h"

void el(Q o){Z co=0xB0,cl=g.c.b.l,ro=(co+cl+4095)&~4095,rl=SS.p.l;B f={0};f.l=ro+rl;memcpy(f.d+co,g.c.b.d,cl);memcpy(f.d+ro,SS.p.d,rl);u8*E=f.d;E[0]=0x7F;E[1]='E';E[2]='L';E[3]='F';E[4]=2;E[5]=1;E[6]=1;PW(0x10,2);PW(0x12,0x3E);PW(0x14,1);M(0x18,0x400000+co);M(0x20,0x40);PW(0x34,0x40);PW(0x36,0x38);PW(0x38,2);PW(0x40,1);PW(0x44,5);M(0x48,0);M(0x50,0x400000);M(0x58,0x400000);M(0x60,ro);M(0x68,ro);M(0x70,0x1000);PW(0x78,1);PW(0x7C,6);M(0x80,ro);M(0x88,BB);M(0x90,BB);M(0x98,rl);M(0xA0,BO>rl?BO:rl);M(0xA8,1);FILE*f2=fopen(o,"wb");if(!f2)exit(1);fwrite(f.d,1,f.l,f2);fclose(f2);chmod(o,0755);}void ge(Sc*sc){BO=768;ST=BO;BO+=8;for(I i=0;i<sc->n;i++){En*e=&sc->v[i];Pl*p=&e->p;Z sk=0;if(e->c){D(UO);H();C8(0x85);C8(0xC0);sk=e->c==1?J(0x85):J(0x84);}if(p->n==1){St*st=&p->v[0];Z a=BO;BO+=8*(st->a.n+1);m(st,a);}else h(p);if(sk)PHC(sk);}D(0);SC(60);}char*rf(Q p){FILE*f=fopen(p,"rb");if(!f)exit(1);fseek(f,0,SEEK_END);long n=ftell(f);fseek(f,0,SEEK_SET);char*b=malloc(n+1);if(!b)exit(1);fread(b,1,n,f);b[n]=0;fclose(f);return b;}I ___(I a,char**v){char*o=a>3?v[3]:"a.out";Sc sc=p(rf(v[1]));BB=0x600000;ge(&sc);el(o);return 0;}I main(I a,char**v){return ___(a,v);}
