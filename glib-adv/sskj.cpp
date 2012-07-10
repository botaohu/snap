/////////////////////////////////////////////////
// Includes
#include "sskj.h"

/////////////////////////////////////////////////
// Sskj-Lexical-Chars
void TSskjLxChDef::SetUcCh(const TStr& Str){
  for (int ChN=1; ChN<Str.Len(); ChN++){UcChV[Str[ChN]-TCh::Mn]=TCh(Str[0]);}}

void TSskjLxChDef::SetChTy(const TSskjLxChTy& ChTy, const TStr& Str){
  for (int ChN=0; ChN<Str.Len(); ChN++){ChTyV[Str[ChN]-TCh::Mn]=TInt(ChTy);}}

void TSskjLxChDef::SetEscStr(const TStr& SrcStr, const TStr& DstStr){
  EscStrH.AddDat(SrcStr, DstStr);}

TStr TSskjLxChDef::GetEscStr(const TStr& Str){
  int EscStrId;
  if ((EscStrId=EscStrH.GetKeyId(Str))!=-1){
    return EscStrH[EscStrId];
  } else
  if ((Str.Len()>=2)&&(Str[0]=='&')&&(Str[1]=='#')){
    int ChCd=0;
    for (int ChN=2; ChN<Str.Len(); ChN++){
      if (ChCd<=0xFFFF){ChCd=ChCd*10+Str[ChN]-'0';}}
    return TStr((char)ChCd);
  } else {
    return TStr(' ');
  }
}

TSskjLxChDef::TSskjLxChDef():
  ChTyV(TCh::Vals), UcChV(TCh::Vals), EscStrH(100){

  // Character-Types
  ChTyV.PutToAll(TInt(hlctSpace));
  SetChTy(hlctAlpha, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  SetChTy(hlctAlpha, "abcdefghijklmnopqrstuvwxyz");
  SetChTy(hlctAlpha, "~^{[@`}]\\|");
  SetChTy(hlctNum, "0123456789");
  SetChTy(hlctSym, "!#$%&*()-=+;:'\",./?");
  SetChTy(hlctLTag, "<"); SetChTy(hlctRTag, ">");
  SetChTy(hlctEof, EofCh);
  for (int Ch=TCh::Mn; Ch<=TCh::Mx; Ch++){
    if ((Ch<0)||(Ch>127)){SetChTy(hlctAlpha, TStr(TCh(char(Ch))));}}

  // Upper-Case
  {for (int Ch=TCh::Mn; Ch<=TCh::Mx; Ch++){UcChV[Ch-TCh::Mn]=TCh(char(Ch));}}
  SetUcCh("Aa"); SetUcCh("��"); SetUcCh("��"); SetUcCh("��");
  SetUcCh("��"); SetUcCh("��"); SetUcCh("��"); SetUcCh("��");
  SetUcCh("Bb"); SetUcCh("Cc"); SetUcCh("��"); SetUcCh("Dd");
  SetUcCh("��"); SetUcCh("Ee"); SetUcCh("��"); SetUcCh("��");
  SetUcCh("��"); SetUcCh("��"); SetUcCh("Ff"); SetUcCh("Gg");
  SetUcCh("Hh"); SetUcCh("Ii"); SetUcCh("��"); SetUcCh("��");
  SetUcCh("��"); SetUcCh("��"); SetUcCh("Jj"); SetUcCh("Kk");
  SetUcCh("Ll"); SetUcCh("Mm"); SetUcCh("Nn"); SetUcCh("��");
  SetUcCh("Oo"); SetUcCh("��"); SetUcCh("��"); SetUcCh("��");
  SetUcCh("��"); SetUcCh("��"); SetUcCh("��"); SetUcCh("Pp");
  SetUcCh("Qq"); SetUcCh("Rr"); SetUcCh("Ss"); SetUcCh("Tt");
  SetUcCh("Uu"); SetUcCh("��"); SetUcCh("��"); SetUcCh("��");
  SetUcCh("��"); SetUcCh("Vv"); SetUcCh("Ww"); SetUcCh("Xx");
  SetUcCh("Yy�"); SetUcCh("��"); SetUcCh("Zz");

  // Escape-Sequences
  SetEscStr("&quot", "\""); SetEscStr("&amp", "&");
  SetEscStr("&lt", "<"); SetEscStr("&gt", ">");
  SetEscStr("&nbsp", " ");

  SetEscStr("&auml", "�"); SetEscStr("&Auml", "�");
  SetEscStr("&ouml", "�"); SetEscStr("&Ouml", "�");
  SetEscStr("&uuml", "�"); SetEscStr("&Uuml", "�");
  SetEscStr("&aring", "�"); SetEscStr("&Aring", "�");
  SetEscStr("&oslash", "�"); SetEscStr("&Oslash", "�");
  SetEscStr("&Aelig", "�"); SetEscStr("&aelig", "�");

  SetEscStr("&eacute", "e"); SetEscStr("&Eacute", "E");
  SetEscStr("&egrave", "e"); SetEscStr("&Egrave", "E");
  SetEscStr("&agrave", "a"); SetEscStr("&Agrave", "A");
}

/////////////////////////////////////////////////
// Sskj-Lexical
TSskjLxChDef TSskjLx::ChDef;

void TSskjLx::GetCh(){
  if (ChStack.Empty()){
    Ch=(SIn->Eof()) ? EofCh : SIn->GetCh();
  } else {
    Ch=ChStack.Pop();
  }
  if ((Ch==CrCh)||(Ch==LfCh)){GetCh();}
}

