#include "Controller.h"

Controller::Controller(){}

bool Controller::bilanciate(QString in, int s, int e) const {
    int stack=0;
    for(int i=s;i<e;i++){
        if(stack<0) return false;
        if(in.at(i)=='(') stack++;
        if(in.at(i)==')') stack--;
    }
    if(stack!=0)
        return false;
    else
        return true;
}

bool Controller::valutabile(QString in, QString tipo) const {

    for(int i=0;i<in.length();i++){
        if(!par.contains(in.at(i))&&!operandi.contains(in.at(i))&&!operazioni.contains(in.at(i)))
            return false;
    }

    if(tipo=="Geometrica"||tipo=="Bernoulli")
        if(in.contains('-')||in.contains('*')||in.contains('/'))
            return false;
        else return true;
    else if(tipo=="Binomiale"||tipo=="Pascal"||tipo=="Ipergeometrica")
        if(in.contains('/'))
            return false;
        else return true;
    else if(tipo=="Poisson"||tipo=="Skellam")
        return true;
    else return true;

}

VariabileAleatoria* Controller::valutaespressione(QString in, const VariabileAleatoria& x, const VariabileAleatoria& y) const {

    if(in.isEmpty()) throw CustomException("Manca un operando");
    if(!operandi.contains(in.at(0))&&in.at(0)!='(') throw CustomException("Espressione non inizia per variabile o parentesi");
    if(in.length()==1)
        if(operandi.contains(in.at(0))){
            if(in.at(0)=='x'||in.at(0)=='X') return x.clone();
            else if(in.at(0)=='y'||in.at(0)=='Y') return y.clone();
        }
        else throw CustomException("Espressione non valida: operazione o parentesi al posto di variabile");

    bool ip = false;
    int a=0;
    while(in.at(a)=='(' && in.at(in.length()-a-1)==')'){
        a++;
        if(!bilanciate(in, a, in.length()-a)){
            a--;
            break;
        }
    }

    int lHP = -1;
    if(!operandi.contains(in.at(0))&&in.at(0)!='(') throw CustomException("sottoEspressione non inizia per variabile o parentesi");

    for(int i=a;i<in.length()-a;i++){

        if(in.at(i)=='*'||in.at(i)=='/'){ lHP=i; continue; }

        if(in.at(i)=='('){ ip=true; continue; }

        if(in.at(i)==')' && i+1<in.length()-a && operazioni.contains(in.at(i+1))){ ip=false; lHP=i+1; continue; }
        else if(in.at(i)==')' && i+1<in.length()-a ) throw CustomException("Espressione non valida: variabile dopo parentesi");

        if((in.at(i)=='+' || in.at(i)=='-') && ip==false){

            VariabileAleatoria* a1 = valutaespressione(in.mid(a, i-a), x, y);
            VariabileAleatoria* a2 = valutaespressione(in.mid(i+1, in.length()-a-(i+1)), x, y);
            VariabileAleatoria* res = NULL;

            try{
                if(in.at(i)=='+')
                    res = a1->somma(*a2);
                else
                    res = a1->differenza(*a2);
            }catch(CustomException e){ throw e; }
            delete a1;
            delete a2;
            return res;
        }

        if(i==in.length()-a-1 && lHP!=-1){

            VariabileAleatoria* a1 = valutaespressione(in.mid(a, lHP-a), x, y);
            VariabileAleatoria* a2 = valutaespressione(in.mid(lHP+1, in.length()-a-(lHP+1)), x, y);
            VariabileAleatoria* res;
            try{
                if(in.at(lHP)=='+')
                    res = a1->somma(*a2);
                else if(in.at(lHP)=='-')
                    res = a1->differenza(*a2);
                else if(in.at(lHP)=='*')
                    res = a1->prodotto(*a2);
                else if(in.at(lHP)=='/')
                    res = a1->quoziente(*a2);
            }catch(CustomException e){ throw e; }
            delete a1;
            delete a2;
            return res;
        }

    }

    if(in.length()==3 && a==1 && operandi.contains(in.at(1))){
        if(in.at(0)=='x') return x.clone();
        else if(in.at(0)=='y') return y.clone();
    }
    throw CustomException("Valutazione andata storta");

}

VariabileAleatoria* Controller::valuta(QString in, QString tipo, const VariabileAleatoria& x, const VariabileAleatoria& y) const {
    if(in.isEmpty()) throw CustomException("Input vuoto");
    if(!valutabile(in, tipo)) throw CustomException("Espressione non valutabile");
    if(!bilanciate(in, 0, in.length())) throw CustomException("Parentesi non bilanciate");
    VariabileAleatoria* res;
    try{
        res = valutaespressione(in, x, y);
    }catch(CustomException e){ throw e; }
    return res;
}

QString Controller::monoperando(const VariabileAleatoria& v, QString f, int k) const {
  QString res;
  if(f=="E"){
    try{
      res = QString::number(v.media());
    }catch(CustomException e){throw e;}
  }
  else if(f=="V"){
    try{
      res = QString::number(v.varianza());
    }catch(CustomException e){throw e;}
  }
  else if(f=="M"){
    try{
      QVector<int>* m = v.moda();
      for(int i=0; i<m->size();i++){
        if(i > 0)
            res +=", ";
        res += QString::number(m->at(i));
      }
    }catch(CustomException e){throw e;}
  }
  else if(f=="D"){
    try{
      res = QString::number(v.densita(k));
    }catch(CustomException e){throw e;}
  }

  else if(f=="I"){
    try{
      const Bernoulli* b = dynamic_cast<const Bernoulli*>(&v);
      const Binomiale* bin = dynamic_cast<const Binomiale*>(&v);
      const Pascal* pa = dynamic_cast<const Pascal*>(&v);
      const Poisson* po = dynamic_cast<const Poisson*>(&v);
      if(b) res = QString::number(b->informazione());
      else if(bin) res = QString::number(bin->informazione());
      else if(pa) res = QString::number(pa->informazione());
      else if(po) res = QString::number(po->informazione());
      else throw CustomException("Funzione non applicabile all'operando");
    }catch(CustomException e){throw e;}
  }
  else if(f=="e"){
    try{
      const Bernoulli* b = dynamic_cast<const Bernoulli*>(&v);
      const Binomiale* bin = dynamic_cast<const Binomiale*>(&v);
      const Geometrica* g = dynamic_cast<const Geometrica*>(&v);
      if(b) res = QString::number(b->entropia());
      else if(bin) res = QString::number(bin->entropia());
      else if(g) res = QString::number(g->entropia());
      else throw CustomException("Funzione non applicabile all'operando");
    }catch(CustomException e){throw e;}
  }
  return res;
}
