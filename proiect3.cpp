#include <iostream>
#include <vector>
#include <map>
using namespace std;
///Ex 7- proiectul 3

class Interfata
{
public:
    virtual void citire(istream &) = 0;
    virtual void afisare(ostream &) = 0;

    friend istream& operator >>(istream & in, Interfata & ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, Interfata & ob)
    {
        ob.afisare(out);
        return out;
    }
};

class Cont : public Interfata{

protected :
    string detinator, data;
    double sold;
    const int IDcont;
    static int contorID;

public:
    Cont();//constructor de initializare
    Cont(string detinator, string data, double sold);//constructor cu parametri
    Cont(const Cont&);//constructor de copiere
    virtual ~Cont();//destructor
    Cont& operator =(const Cont&);// operator de atribuire
    int get_ID( ) const{ return this->IDcont;}
    string get_detinator(){ return this->detinator;}
    string get_data(){ return this->data;}
    double get_sold(){ return this->sold;}
    void citire(istream&);
    virtual void afisare(ostream&);
};
int Cont::contorID = 0;

Cont :: Cont(): IDcont(contorID++),detinator("Detinator anonim"), data("00/00/00"), sold(0) {}
Cont :: Cont(const Cont & ob) : IDcont(ob.contorID++),detinator(ob.detinator),data(ob.data), sold(ob.sold){}
Cont :: Cont(string detinator, string data, double sold) : IDcont(contorID++),detinator(detinator), data(data), sold(sold){}
Cont ::~Cont() {}

Cont & Cont::  operator=(const Cont & ob)
{
    if(this!=&ob)
    {
        this->detinator=ob.detinator;
        this->data=ob.data;
        this->sold=ob.sold;
    }
    return *this;
}

void Cont :: citire(istream & in) {
    cout<<"Numele detinatorului: "; in>>detinator;
    cout<<"Data de deschidere a contului: ";in>>data;
    cout<<"Soldul contului: "; in>>sold;
}
void Cont ::afisare(ostream & out) {
    out<<"Numele detinatorului: "; out<<detinator<<endl;
    out<<"Data de deschidere a contului: ";out<<data<<endl;
    out<<"Soldul contului: "; out<<sold<<" de lei"<<endl;
}


class ContEconomii: public Cont{

protected:
    int rata, nrluni_istoric;
    vector<float> istoric;

public:
    ContEconomii();
    ContEconomii(const ContEconomii&);
    ContEconomii(string detinator, string data, double sold, int rata, vector<float> istoric, int nrluni_istoric);
    virtual ~ContEconomii();
    ContEconomii & operator=(const ContEconomii&);
    int get_rata(){ return this->rata;}
    void citire(istream &);
    virtual void afisare(ostream &);

};

ContEconomii :: ContEconomii(): rata(0), istoric(0), nrluni_istoric(0){}
ContEconomii :: ContEconomii(const ContEconomii & ob): Cont(ob), rata(ob.rata), istoric(ob.istoric),nrluni_istoric(ob.nrluni_istoric) {}
ContEconomii :: ContEconomii(string detinator, string data, double sold, int rata, vector<float> istoric, int nrluni_istoric): Cont(detinator, data, sold),rata(rata), istoric(istoric), nrluni_istoric(nrluni_istoric){}
ContEconomii :: ~ContEconomii(){}
ContEconomii & ContEconomii:: operator=(const ContEconomii & ob)
{
    if(this!=&ob)
    {
        this->rata-ob.rata;
        this->nrluni_istoric=ob.nrluni_istoric;
        this->istoric=ob.istoric;
    }
    return *this;
}

void eroare_rata_int(int x)
{
    if(x<0)
        throw 11;
}

void ContEconomii :: citire(istream& in){

    Cont::citire(in);
    cout<<"Rata dobanzii este pe durata de: ";
    int k = 1;
    while(k == 1)
    {
        try
        {
            in>>rata;
            eroare_rata_int(rata);
            k = 0;
        }
        catch (...)
        {
            cout << "Rata introdusa nu este valida" << endl;
            cout << "Reintroduceti\n";
            cin.clear();
            cin.ignore();

        }
    }
    cout<<"Numarul de luni pentru istoric: "; in>>nrluni_istoric;
    float sold_istoric;
    cout<<"Cititi istoricul soldului: "<<endl;
    for(int i=0;i<nrluni_istoric;i++)
    {
        in>>sold_istoric;
        istoric.push_back(sold_istoric);
    }
    istoric.push_back(sold);
}

void ContEconomii :: afisare(ostream & out){

    Cont ::afisare(out);
    out<<"Rata dobanzii este pe o durata de: "; out<<rata<<endl;
    out<<"Numarul de luni pentru istoric: "; out<<nrluni_istoric<<endl;
    out<<"Istoricul soldului este: ";
    for(int i=0;i<istoric.size();i++)
        out<<istoric[i]<<" ";
    out<<endl;
}

class Cont_curent: public Cont{

protected:
    int nrTranzactiiGratuite;
    double suma_retrasa, suma_depusa;

public:
    Cont_curent();
    Cont_curent(const Cont_curent&ob);
    Cont_curent(string detinator, string data, double sold, int nrTranzactiiGratuite, double suma_restrasa, double suma_depusa);
    Cont_curent & operator=(const Cont_curent&);
    ~Cont_curent();
    void Retragere();
    void Depunere();
    void citire(istream&);
    virtual void afisare(ostream&);
};

Cont_curent:: Cont_curent():nrTranzactiiGratuite(nrTranzactiiGratuite), suma_retrasa(0), suma_depusa(0){}
Cont_curent:: Cont_curent(const Cont_curent&ob):Cont(ob),nrTranzactiiGratuite(ob.nrTranzactiiGratuite), suma_retrasa(ob.suma_retrasa), suma_depusa(ob.suma_depusa){}
Cont_curent:: Cont_curent(string detinator, string data, double sold, int nrTranzactiiGratuite, double suma_restrasa, double suma_depusa): Cont(detinator, data, sold), nrTranzactiiGratuite(nrTranzactiiGratuite), suma_retrasa(suma_retrasa), suma_depusa(suma_depusa){}
Cont_curent:: ~Cont_curent(){};

Cont_curent & Cont_curent :: operator=(const Cont_curent& ob)
{
    if(this!=&ob)
    {
        this->nrTranzactiiGratuite=ob.nrTranzactiiGratuite;
        this->suma_depusa=ob.suma_depusa;
        this->suma_retrasa=ob.suma_retrasa;
    }
    return *this;
}

void Cont_curent::Retragere()
{
    cout<<"Introduceti suma pe care vreti sa o retrageti: ";
    cin>>suma_retrasa;
    int d=suma_retrasa*(1.5);
    if(nrTranzactiiGratuite!=0)
    {
        nrTranzactiiGratuite--;
        sold=sold-suma_retrasa;
    }
    else sold=sold-d;
}

void Cont_curent :: Depunere()
{
    cout<<"Introduceti suma pe care vreti sa o depuneti: ";
    cin>>suma_depusa;
    if(nrTranzactiiGratuite!=0)
    {
        nrTranzactiiGratuite--;
        sold=sold+suma_depusa;
    }
    else sold=sold+suma_depusa;
}

void Cont_curent::citire(istream &in)
{
    Cont::citire(in);
    cout<<"Introduceti numarul de tranzactii gratuite stabilite cu banca pentru contul curent: ";
    in>>nrTranzactiiGratuite;
}

void Cont_curent ::afisare(ostream & out)
{
    Cont::afisare(out);
    out<<endl;
}

template <class T>
class Gestionare_conturi
{
public:
    map<int, T> structura;
    map<int, vector<double>> istoric;

public:
    Gestionare_conturi(){}
    Gestionare_conturi&  operator+=(const T& ob)
    {
        static int idCont=0;
        structura[idCont]=ob;
        idCont++;
        return *this;
    }

    void AdaugaOperatiune(int id_cont, double sold) {
        istoric[id_cont].push_back(sold);
    }

    void AfisIstoric()
    {
        for (auto& pair : istoric)
        {
            cout <<"Contul cu nr: "<< pair.first<<" introdus in istoricul de solduri"<<endl;
            for(auto &el: istoric[pair.first])
                 cout<< el<< endl;
        }
    }
};

auto verific_numar=[](int a){ return (a>=1 && a<=8);};///functie lambda

class Meniu
{
    Meniu(){}
    Meniu & operator=(Meniu& ob) { return *this;}
    Meniu(const Meniu & ob){}
    ~Meniu();
    static Meniu* instanta;
    Gestionare_conturi<Cont> conturi_cu_map;
    Gestionare_conturi<ContEconomii> conturiEco;
    vector<Cont*> conturiBanca;
    vector<ContEconomii*> listaConturiEco;
    vector<Cont_curent*> listaConturiCurente;

public:
    static Meniu* get_instanta()
    {
        if(!instanta)
            instanta=new Meniu();
        return instanta;
    }
    void afis_meniu();
    void adaugare_cont_economii();
    void adaugare_cont_curent();
    void depunere_bani();
    void retragere_bani();
    void afisare_lista_conturiBancare();
    void rata_unu();
    void date_generale();
    void istoric_sold();
    void eroare_meniu(int x)
    {
        try{
            if(verific_numar(x)==false)
                throw 1;
        }
        catch (int x){ cout<<"Eroare! x-ul introdus nu este valid! "<<endl;}
    }
};

Meniu* Meniu :: instanta;

void Meniu::adaugare_cont_economii() {
    Cont * ContE= new ContEconomii();
    cin>>* ContE;
    conturi_cu_map+=*(ContE);
    conturiBanca.push_back(ContE);
    listaConturiEco.push_back(dynamic_cast<ContEconomii*> (ContE));
}

void Meniu::adaugare_cont_curent() {
    Cont * ContC= new Cont_curent();
    cin>>*ContC;
    conturi_cu_map+=*(ContC);
    conturiBanca.push_back(ContC);
    listaConturiCurente.push_back(dynamic_cast<Cont_curent*>(ContC));
}

void Meniu::depunere_bani() {
    string nume;
    cout<<"Depune bani in contul detinut de: "; cin>>nume;
    for(int i=0;i<listaConturiCurente.size();i++)
        if((*listaConturiCurente[i]).get_detinator()==nume) {
            (*listaConturiCurente[i]).Depunere();
            conturi_cu_map.AdaugaOperatiune(listaConturiCurente[i]->get_ID(), listaConturiCurente[i]->get_sold());
        }
    conturi_cu_map.AfisIstoric();
}

void Meniu::retragere_bani() {
    string nume;
    cout<<"Retrage bani din contul detinut de: "; cin>>nume;
    for(int i=0;i<listaConturiCurente.size();i++)
        if((*listaConturiCurente[i]).get_detinator()==nume)
        {
            (*listaConturiCurente[i]).Retragere();
            conturi_cu_map.AdaugaOperatiune(listaConturiCurente[i]->get_ID(), listaConturiCurente[i]->get_sold());
        }
    conturi_cu_map.AfisIstoric();
}

void Meniu::afisare_lista_conturiBancare() {
    for(int i=0;i<conturiBanca.size();i++)
        cout<<*conturiBanca[i]<<endl;
}

void Meniu::rata_unu() {
    int ok=0;
    for(int i=0;i<listaConturiEco.size();i++)
        if (listaConturiEco[i]->get_rata()==12)
        {
            cout<<(*listaConturiEco[i])<<endl;
            ok=1;
        }
    if(ok==0)
        cout<<"Nu exista niciun cont de economii cu rata dobaznii de 1 an!\n";
}

void Meniu::date_generale() {
    for (auto& pair : conturi_cu_map.structura)
    {
        cout <<"Contul cu nr: "<< pair.first<<endl;
        cout<< pair.second << endl;
    }
}

void Meniu::afis_meniu()
{
    int x;
    cout<<"1.Pentru a adauga un cont de economii in banca\n";
    cout<<"2.Pentru a adauga un cont curent in banca\n";
    cout<<"3.Pentru a depune bani intr-un cont curent\n";
    cout<<"4.Pentru a retrage bani dintr-un cont curent\n";
    cout<<"5.Pentru a afisa lista de conturi bancare\n";
    cout<<"6.Pentru a se afiseza toate conturile cu durata ratei de 1 an\n";
    cout<<"7.Pentru date generale despre conturi\n";
    cout<<"8.Inchide\n";
    cout<<"Optiunea?"<<endl;
    cin>>x;
    while(x)
    {
        eroare_meniu(x);
        switch (x)
        {
            case 1:
            {
                adaugare_cont_economii();
                break;
            }
            case 2:
            {
               adaugare_cont_curent();
                break;
            }
            case 3:
            {
                depunere_bani();
                break;
            }
            case 4:
            {
                retragere_bani();
                break;
            }
            case 5:
            {
                afisare_lista_conturiBancare();
                break;
            }
            case 6:
            {
                rata_unu();
                break;
            }
            case 7:
            {
                date_generale();
                break;
            }
            case 8:
                return;
        }
        cout<<"1.Pentru a adauga un cont de economii in banca\n";
        cout<<"2.Pentru a adauga un cont curent in banca\n";
        cout<<"3.Pentru a depune bani intr-un cont curent\n";
        cout<<"4.Pentru a retrage bani dintr-un cont curent\n";
        cout<<"5.Pentru a afisa lista de conturi bancare\n";
        cout<<"6.Pentru a se afiseza toate conturile cu durata ratei de 1 an\n";
        cout<<"7.Pentru date generale despre conturi\n";
        cout<<"8.Inchide\n";
        cout<<"Alta optiune? "<<endl;
        cin>>x;
    }
}

int main()
{
    Meniu *p = p ->get_instanta();
    p ->afis_meniu();
    return 0;
}
