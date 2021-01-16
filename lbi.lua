local bit=bit or bit32 or require('bit')local unpack=table.unpack or unpack;local a;local b;local c;local d=50;local e={[0]='ABC','ABx','ABC','ABC','ABC','ABx','ABC','ABx','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','AsBx','ABC','ABC','ABC','ABC','ABC','ABC','ABC','ABC','AsBx','AsBx','ABC','ABC','ABC','ABx','ABC'}local f={[0]={b='OpArgR',c='OpArgN'},{b='OpArgK',c='OpArgN'},{b='OpArgU',c='OpArgU'},{b='OpArgR',c='OpArgN'},{b='OpArgU',c='OpArgN'},{b='OpArgK',c='OpArgN'},{b='OpArgR',c='OpArgK'},{b='OpArgK',c='OpArgN'},{b='OpArgU',c='OpArgN'},{b='OpArgK',c='OpArgK'},{b='OpArgU',c='OpArgU'},{b='OpArgR',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgR',c='OpArgN'},{b='OpArgR',c='OpArgN'},{b='OpArgR',c='OpArgN'},{b='OpArgR',c='OpArgR'},{b='OpArgR',c='OpArgN'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgK',c='OpArgK'},{b='OpArgR',c='OpArgU'},{b='OpArgR',c='OpArgU'},{b='OpArgU',c='OpArgU'},{b='OpArgU',c='OpArgU'},{b='OpArgU',c='OpArgN'},{b='OpArgR',c='OpArgN'},{b='OpArgR',c='OpArgN'},{b='OpArgN',c='OpArgU'},{b='OpArgU',c='OpArgU'},{b='OpArgN',c='OpArgN'},{b='OpArgU',c='OpArgN'},{b='OpArgU',c='OpArgN'}}local function g(h,i,j,k)local l=0;for m=i,j,k do l=l+string.byte(h,m,m)*256^(m-i)end;return l end;local function n(o,p,q,r)local s=(-1)^bit.rshift(r,7)local t=bit.rshift(q,7)+bit.lshift(bit.band(r,0x7F),1)local u=o+bit.lshift(p,8)+bit.lshift(bit.band(q,0x7F),16)local v=1;if t==0 then if u==0 then return s*0 else v=0;t=1 end elseif t==0x7F then if u==0 then return s*1/0 else return s*0/0 end end;return s*2^(t-127)*(1+v/2^23)end;local function w(o,p,q,r,x,y,z,A)local s=(-1)^bit.rshift(A,7)local t=bit.lshift(bit.band(A,0x7F),4)+bit.rshift(z,4)local u=bit.band(z,0x0F)*2^48;local v=1;u=u+y*2^40+x*2^32+r*2^24+q*2^16+p*2^8+o;if t==0 then if u==0 then return s*0 else v=0;t=1 end elseif t==0x7FF then if u==0 then return s*1/0 else return s*0/0 end end;return s*2^(t-1023)*(v+u/2^52)end;local function B(h,i,j)return g(h,i,j-1,1)end;local function C(h,i,j)return g(h,j-1,i,-1)end;local function D(h,i)return n(string.byte(h,i,i+3))end;local function E(h,i)local o,p,q,r=string.byte(h,i,i+3)return n(r,q,p,o)end;local function F(h,i)return w(string.byte(h,i,i+7))end;local function G(h,i)local o,p,q,r,x,y,z,A=string.byte(h,i,i+7)return w(A,z,y,x,r,q,p,o)end;local H={[4]={little=D,big=E},[8]={little=F,big=G}}local function I(J)local K=J.index;local L=string.byte(J.source,K,K)J.index=K+1;return L end;local function M(J,N)local O=J.index+N;local P=string.sub(J.source,J.index,O-1)J.index=O;return P end;local function Q(J)local N=J:s_szt()local P;if N~=0 then P=string.sub(M(J,N),1,-2)end;return P end;local function R(N,S)return function(J)local O=J.index+N;local T=S(J.source,J.index,O)J.index=O;return T end end;local function U(N,S)return function(J)local V=S(J.source,J.index)J.index=J.index+N;return V end end;local function W(J)local X=J:s_int()local Y={}for m=1,X do local Z=J:s_ins()local _=bit.band(Z,0x3F)local a0=e[_]local a1=f[_]local a2={value=Z,op=_,A=bit.band(bit.rshift(Z,6),0xFF)}if a0=='ABC'then a2.B=bit.band(bit.rshift(Z,23),0x1FF)a2.C=bit.band(bit.rshift(Z,14),0x1FF)a2.is_KB=a1.b=='OpArgK'and a2.B>0xFF;a2.is_KC=a1.c=='OpArgK'and a2.C>0xFF elseif a0=='ABx'then a2.Bx=bit.band(bit.rshift(Z,14),0x3FFFF)a2.is_K=a1.b=='OpArgK'elseif a0=='AsBx'then a2.sBx=bit.band(bit.rshift(Z,14),0x3FFFF)-131071 end;Y[m]=a2 end;return Y end;local function a3(J)local X=J:s_int()local a4={}for m=1,X do local a5=I(J)local a6;if a5==1 then a6=I(J)~=0 elseif a5==3 then a6=J:s_num()elseif a5==4 then a6=Q(J)end;a4[m]=a6 end;return a4 end;local function a7(J,h)local X=J:s_int()local a8={}for m=1,X do a8[m]=c(J,h)end;return a8 end;local function a9(J)local X=J:s_int()local aa={}for m=1,X do aa[m]=J:s_int()end;return aa end;local function ab(J)local X=J:s_int()local ac={}for m=1,X do ac[m]={varname=Q(J),startpc=J:s_int(),endpc=J:s_int()}end;return ac end;local function ad(J)local X=J:s_int()local ae={}for m=1,X do ae[m]=Q(J)end;return ae end;function c(J,af)local ag={}local h=Q(J)or af;ag.source=h;J:s_int()J:s_int()ag.numupvals=I(J)ag.numparams=I(J)I(J)I(J)ag.code=W(J)ag.const=a3(J)ag.subs=a7(J,h)ag.lines=a9(J)ab(J)ad(J)for ah,ai in ipairs(ag.code)do if ai.is_K then ai.const=ag.const[ai.Bx+1]else if ai.is_KB then ai.const_B=ag.const[ai.B-0xFF]end;if ai.is_KC then ai.const_C=ag.const[ai.C-0xFF]end end end;return ag end;function a(h)local aj;local ak;local al;local am;local an;local ao;local ap;local aq={index=1,source=h}assert(M(aq,4)=='\27Lua','invalid Lua signature')assert(I(aq)==0x51,'invalid Lua version')assert(I(aq)==0,'invalid Lua format')ak=I(aq)~=0;al=I(aq)am=I(aq)an=I(aq)ao=I(aq)ap=I(aq)~=0;aj=ak and B or C;aq.s_int=R(al,aj)aq.s_szt=R(am,aj)aq.s_ins=R(an,aj)if ap then aq.s_num=R(ao,aj)elseif H[ao]then aq.s_num=U(ao,H[ao][ak and'little'or'big'])else error('unsupported float size')end;return c(aq,'@virtual')end;local function ar(as,at)for m,au in pairs(as)do if au.index>=at then au.value=au.store[au.index]au.store=au;au.index='value'as[m]=nil end end end;local function av(as,at,aw)local ax=as[at]if not ax then ax={index=at,store=aw}as[at]=ax end;return ax end;local function ay(...)return select('#',...),{...}end;local function az(aA,aB)local h=aA.source;local aC=aA.lines[aA.pc-1]local af,aD,aE=string.match(aB,'^(.-):(%d+):%s+(.+)')local aF='%s:%i: [%s:%i] %s'aC=aC or'0'af=af or'?'aD=aD or'0'aE=aE or aB;error(string.format(aF,h,aC,af,aD,aE),0)end;local function aG(aA)local Y=aA.code;local aH=aA.subs;local aI=aA.env;local aJ=aA.upvals;local aK=aA.varargs;local aL=-1;local aM={}local aw=aA.stack;local aN=aA.pc;while true do local aO=Y[aN]local _=aO.op;aN=aN+1;if _<19 then if _<9 then if _<4 then if _<2 then if _<1 then aw[aO.A]=aw[aO.B]else aw[aO.A]=aO.const end elseif _>2 then for m=aO.A,aO.B do aw[m]=nil end else aw[aO.A]=aO.B~=0;if aO.C~=0 then aN=aN+1 end end elseif _>4 then if _<7 then if _<6 then aw[aO.A]=aI[aO.const]else local at;if aO.is_KC then at=aO.const_C else at=aw[aO.C]end;aw[aO.A]=aw[aO.B][at]end elseif _>7 then local au=aJ[aO.B]au.store[au.index]=aw[aO.A]else aI[aO.const]=aw[aO.A]end else local au=aJ[aO.B]aw[aO.A]=au.store[au.index]end elseif _>9 then if _<14 then if _<12 then if _<11 then aw[aO.A]={}else local aP=aO.A;local aQ=aO.B;local at;if aO.is_KC then at=aO.const_C else at=aw[aO.C]end;aw[aP+1]=aw[aQ]aw[aP]=aw[aQ][at]end elseif _>12 then local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;aw[aO.A]=aR-aS else local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;aw[aO.A]=aR+aS end elseif _>14 then if _<17 then if _<16 then local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;aw[aO.A]=aR/aS else local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;aw[aO.A]=aR%aS end elseif _>17 then aw[aO.A]=-aw[aO.B]else local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;aw[aO.A]=aR^aS end else local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;aw[aO.A]=aR*aS end else local at,aT;if aO.is_KB then at=aO.const_B else at=aw[aO.B]end;if aO.is_KC then aT=aO.const_C else aT=aw[aO.C]end;aw[aO.A][at]=aT end elseif _>19 then if _<29 then if _<24 then if _<22 then if _<21 then aw[aO.A]=#aw[aO.B]else local P=aw[aO.B]for m=aO.B+1,aO.C do P=P..aw[m]end;aw[aO.A]=P end elseif _>22 then local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;if aR==aS~=(aO.A~=0)then aN=aN+1 end else aN=aN+aO.sBx end elseif _>24 then if _<27 then if _<26 then local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;if aR<=aS~=(aO.A~=0)then aN=aN+1 end else if not aw[aO.A]==(aO.C~=0)then aN=aN+1 end end elseif _>27 then local aP=aO.A;local aQ=aO.B;local aU=aO.C;local aV;local aW,aX;if aQ==0 then aV=aL-aP else aV=aQ-1 end;aW,aX=ay(aw[aP](unpack(aw,aP+1,aP+aV)))if aU==0 then aL=aP+aW-1 else aW=aU-1 end;for m=1,aW do aw[aP+m-1]=aX[m]end else local aP=aO.A;local aQ=aO.B;if not aw[aQ]==(aO.C~=0)then aN=aN+1 else aw[aP]=aw[aQ]end end else local aR,aS;if aO.is_KB then aR=aO.const_B else aR=aw[aO.B]end;if aO.is_KC then aS=aO.const_C else aS=aw[aO.C]end;if aR<aS~=(aO.A~=0)then aN=aN+1 end end elseif _>29 then if _<34 then if _<32 then if _<31 then local aP=aO.A;local aQ=aO.B;local aY={}local X;if aQ==0 then X=aL-aP+1 else X=aQ-1 end;for m=1,X do aY[m]=aw[aP+m-1]end;ar(aM,0)return X,aY else local aP=aO.A;local aZ=aw[aP+2]local at=aw[aP]+aZ;local a_=aw[aP+1]local b0;if aZ==math.abs(aZ)then b0=at<=a_ else b0=at>=a_ end;if b0 then aw[aO.A]=at;aw[aO.A+3]=at;aN=aN+aO.sBx end end elseif _>32 then local aP=aO.A;local S=aw[aP]local b1=aw[aP+1]local at=aw[aP+2]local b2=aP+3;local aY;aw[b2+2]=at;aw[b2+1]=b1;aw[b2]=S;aY={S(b1,at)}for m=1,aO.C do aw[b2+m-1]=aY[m]end;if aw[b2]~=nil then aw[aP+2]=aw[b2]else aN=aN+1 end else local aP=aO.A;local b3,a_,aZ;b3=assert(tonumber(aw[aP]),'`for` initial value must be a number')a_=assert(tonumber(aw[aP+1]),'`for` limit must be a number')aZ=assert(tonumber(aw[aP+2]),'`for` step must be a number')aw[aP]=b3-aZ;aw[aP+1]=a_;aw[aP+2]=aZ;aN=aN+aO.sBx end elseif _>34 then if _<36 then ar(aM,aO.A)elseif _>36 then local aP=aO.A;local X=aO.B;if X==0 then X=aK.size;aL=aP+X-1 end;for m=1,X do aw[aP+m-1]=aK.list[m]end else local a8=aH[aO.Bx+1]local b4=a8.numupvals;local b5;if b4~=0 then b5={}for m=1,b4 do local b6=Y[aN+m-1]if b6.op==0 then b5[m-1]=av(aM,b6.B,aw)elseif b6.op==4 then b5[m-1]=aJ[b6.B]end end;aN=aN+b4 end;aw[aO.A]=b(a8,aI,b5)end else local aP=aO.A;local aU=aO.C;local X=aO.B;local b7=aw[aP]local b8;if X==0 then X=aL-aP end;if aU==0 then aU=aO[aN].value;aN=aN+1 end;b8=(aU-1)*d;for m=1,X do b7[m+b8]=aw[aP+m]end end else local aP=aO.A;local aQ=aO.B;local aV;if aQ==0 then aV=aL-aP else aV=aQ-1 end;ar(aM,0)return ay(aw[aP](unpack(aw,aP+1,aP+aV)))end else aw[aO.A]=not aw[aO.B]end;aA.pc=aN end end;function b(b1,aI,ae)local b9=b1.code;local ba=b1.subs;local bb=b1.lines;local bc=b1.source;local bd=b1.numparams;local function be(...)local aw={}local bf={}local bg=0;local bh,bi=ay(...)local aA;local bj,aB,aY;for m=1,bd do aw[m-1]=bi[m]end;if bd<bh then bg=bh-bd;for m=1,bg do bf[m]=bi[bd+m]end end;aA={varargs={list=bf,size=bg},code=b9,subs=ba,lines=bb,source=bc,env=aI,upvals=ae,stack=aw,pc=1}bj,aB,aY=pcall(aG,aA,...)if bj then return unpack(aY,1,aB)else az(aA,aB)end;return end;return be end;

game:GetService('StarterGui'):SetCore('SendNotification',{Title="Bogie LBI",Text="LBI is made by Bogie/Begie/Vegie and is free on my github, if you bought this request for a refund\n\n",Duration=5})

getrenv().bogie_execute = function(dumped_function)
	local CompiledFunction;
	local Status, Error = pcall(function() 
		CompiledFunction = b(a(dumped_function), getfenv()) 
	end)
	
	if not Status then
		error("Failed to compile script: " .. Error)
	else
		CompiledFunction()
	end
end
