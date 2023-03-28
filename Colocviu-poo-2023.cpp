#include <iostream>
#include <vector>
/* Ghinea Elena-Alexandra
    Clion
    Dobrovat Anca
 */
using namespace std;
class Interfata{
    virtual void citire(istream&)=0;
    virtual void afisare(ostream&)=0;
    friend istream & operator>>(istream & in, Interfata & ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream & operator<<(ostream & out, Interfata & ob)
    {
        ob.afisare(out);
        return out;
    }
};

class Programator: public Interfata{
protected:
    string nume, tipProgram;
    int experienta;
public:
    Programator();
    Programator(string nume, string tipProgram, int experienta);
    Programator(const Programator&);
    Programator & operator=(const Programator&);
    ~Programator(){}
    void citire(istream&);
    void afisare(ostream&);

};
Programator::Programator():nume("Nume anonim"),tipProgram(""), experienta(0) {}
Programator::Programator(std::string nume, std::string tipProgram, int experienta):nume(nume), tipProgram(tipProgram), experienta(experienta) {}
Programator::Programator(const Programator & ob): nume(ob.nume), tipProgram(ob.tipProgram), experienta(ob.experienta)  {}
Programator & Programator::operator=(const Programator & ob) {
    if(this!=&ob)
    {
        this->nume=ob.nume;
        this->tipProgram=ob.tipProgram;
        this->experienta=ob.experienta;
    }
    return * this;
}
void Programator::citire(istream & in) {
    cout<<"Introduceti numele programatorului: "; in>>nume;
    cout<<"Introduceti tipul programului in care lucreaza:  "; in>>tipProgram;
    cout<<"Introduceti anii de experienta: "; in>>experienta;
}
void Programator::afisare(ostream & out) {
    out<<"Numele programatorului: "<<nume<<endl;
    out<<"Tipul programului in care lucreaza:  "<<tipProgram<<endl;
    out<<"Anii de experienta: "<<experienta<<endl;
}

class WorkItem: public Interfata{
    const int ID;
    static int contor;
    string data, area;
    int timpRezolvare;
    Programator *p;
    string status;
public:
    WorkItem();
    WorkItem(const int id, const string &data, const string &area, int timpRezolvare,const Programator &p ,const string &status);
    WorkItem(const WorkItem&);
    WorkItem & operator=(const WorkItem&);
    ~WorkItem(){}
    int get_timp(){ return timpRezolvare; }
    void citire(istream&);
    void afisare(ostream&);
};
int WorkItem::contor=0;

WorkItem:: WorkItem():ID(), data("DD/MM/YYYY"),area(""),  timpRezolvare(0), /*p(p),*/status("Open"){}
WorkItem::WorkItem(const int id, const string &data, const string &area, int timpRezolvare,const Programator &p,const string &status) : ID(contor++), data(data), area(area), timpRezolvare(timpRezolvare),/* p(p),*/
status(status) {}
WorkItem::WorkItem(const WorkItem &ob ):ID(ob.contor), data(ob.data), area(ob.area), timpRezolvare(ob.timpRezolvare), p(ob.p),
status(ob.status) {}

WorkItem &WorkItem::operator=(const WorkItem &ob) {
   if(this!=&ob)
   {
       //this->ID=ob.ID;
       this->data=ob.data;
       this->area=ob.area;
       this->timpRezolvare=ob.timpRezolvare;
       //this->p=ob.p;
       this->status=ob.status;
   }
   return *this;
}
void WorkItem::citire(istream &in) {
    //cout<<"ID ul WorkItem-ului: "; in>>ID;///asta nu cred
    cout<<"Data cand a fost creat WorkItem-ul: "; in>>data;
    cout<<"Area in care este aplicat:" ;in>>area;
    cout<<"Timpul de rezolvare al acestuia: ";in>>timpRezolvare;
    cout<<"Programatorul care se ocupa de acesta: ";
    p=new Programator();
    p->citire(in);
   /// p->citire(in);
    cout<<"Statusul proiectului: "; in>>status;
}
void WorkItem::afisare(ostream & out) {
    out<<"Data cand a fost creat WorkItem-ul: "<<data<<endl;
    out<<"Area in care este aplicat:" <<area<<endl;
    out<<"Timpul de rezolvare al acestuia: "<<timpRezolvare<<endl;
    out<<"Programatorul care se ocupa de acesta: ";p->afisare(out);
    out<<"Statusul proiectului: "<<status<<endl;
}
class Change: public WorkItem{
protected:
    string descriere, Data;
public:
    Change():descriere(""), Data("DD/MM/YYYY"){}

    Change(const int id, const string &data, const string &area, int timpRezolvare, const Programator &p,
           const string &status, const string &descriere, const string &data1) : WorkItem(id, data, area, timpRezolvare,
                                                                                          p, status),
                                                                                 descriere(descriere), Data(data1) {}

    Change(const WorkItem &item, const string &descriere, const string &data) : WorkItem(item), descriere(descriere),
                                                                                Data(data) {}
    Change & operator=(const Change&ob){
        if(this!=&ob)
        {
            this->descriere=descriere;
            this->Data=Data;
        }
        return *this;
    }
    ~Change(){}
    void citire(istream&);
    void afisare(ostream&);

};

void Change::citire(istream &in) {
    WorkItem::citire(in);
    cout<<"Decrierea: "; in>>descriere;
    cout<<"Data cand acesta va fi lansat in productie: "; in>>Data;
}
void Change::afisare(ostream &out) {
    WorkItem::afisare(out);
    out<<"Decrierea: "<<descriere<<endl;
    out<<"Data cand acesta va fi lansat in productie:" <<Data<<endl;
}
class bug: public WorkItem{
protected:
    int impactBug;
    string startWork;
public:
    bug() : impactBug(impactBug), startWork("DD/MM/YYYY") {}
    bug(const int id, const string &data, const string &area, int timpRezolvare, const Programator &p, const string &status, int impactBug, const string &startWork) : WorkItem(id, data, area, timpRezolvare, p, status), impactBug(impactBug),startWork(startWork) {}
    bug(const bug& ob) : WorkItem(ob), impactBug(ob.impactBug), startWork(ob.startWork) {}
    ~bug(){}
    void citire(istream&);
    void afisare(ostream&);
};

void bug::citire(istream &in) {
    WorkItem::citire(in);
    cout<<"Prioritatea de rezolvare: "; in>>impactBug;
    cout<<"Data cand programatorul incepe sa lucreze ;a rezolvarea bug-ului"; in>>startWork;
}
void bug::afisare(ostream &out) {
    WorkItem::afisare(out);
    out<<"Prioritatea de rezo;vare: "<<impactBug<<endl;
    out<<"Data cand programatorul incepe sa lucreze ;a rezolvarea bug-ului"<<startWork<<endl;
}

class Meniu{
    Meniu(){};
    Meniu(const Meniu&){};
    Meniu & operator=(const Meniu&){ return *this;}
    ~Meniu(){}
    static Meniu* instanta;
    vector<Programator*> lista_programatori;
    vector<WorkItem*> workitem;
public:
    static Meniu* getInstanta()
    {if(!instanta)
    instanta=new Meniu();
    return instanta;}
    void afis_meniu();
};
Meniu* Meniu::instanta;
void eroare_meniu(int x)
{
    try{
        if(x<0 || x>7)
            throw 12;
    }
    catch (int x)
    {
        cout<<" x-ul introdus nu este valid! Reintroduceti!";
    }

}
void Meniu::afis_meniu() {
    cout<<"1.Cititi lista de programatori: \n";
    cout<<"2.Creati un change :\n";
    cout<<"3.Cititi un bug\n";
    cout<<"4.Afisati workitem-urile\n";
    cout<<"Optiunea?";
    int x;
    cin>>x;
    while(x)
    {
       // eroare_meniu(x);
        switch(x)
        {
            case 1:
            {
                int nr_programatori;
                cout<<"Introduceti nr de programatori pe care ii adaugati in lista: ";
                cin>>nr_programatori; Programator *p;
                for(int i=0;i<nr_programatori;i++) {
                    p=new Programator();
                    cin>>*p; lista_programatori.push_back(p);
                }
                for(int i=0;i<lista_programatori.size();i++)
                    cout<<*lista_programatori[i]<<endl;
                break;
            }
            case 2:
            { WorkItem *c= new Change();
                cin>>*c;
                workitem.push_back(c);
                break;
            }
            case 3:
            { WorkItem * b=new bug();
                cin>>*b;
                workitem.push_back(b);
                break;
            }
            case 4:
            {
                for(int i=0;i<workitem.size();i++)
                    cout<<*workitem[i]<<endl;
            }
            case 5:
                return;
        }
        cout<<"1.Cititi lista de programatori: \n";
        cout<<"2.Creati un change :\n";
        cout<<"3.Cititi un bug\n";
        cout<<"4.Afisati workitem-urile\n";
        cout<<"ALta optiune?";
        cin>>x;
    }

}
int main()
{
 Meniu *p=p->getInstanta();
 p->afis_meniu();


    return 0;
}
