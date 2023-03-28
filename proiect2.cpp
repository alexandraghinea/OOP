#include <iostream>
#include <vector>
using namespace std;
///Ex.8/Tema2-2021
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

class Contract: public Interfata
{
protected:
    int nrContract, an;
    string beneficiar, furnizor;
    int valoare;

public:
    Contract();
    Contract(const Contract &);
    Contract(int nrContract, int an, const string & beneficiar, const string & furnizor, int valoare);
    virtual ~Contract();

    int getnrContract()
    {
        return this->nrContract;
    }

    int getvaloare()
    {
        return this->valoare;
    }

    void citire(istream &);
    virtual void afisare(ostream &);
};

Contract::Contract()
{
    nrContract = an = 0;
    valoare = 0;
    beneficiar = "";
}

Contract::Contract(const Contract & ob)
{
    nrContract = ob.nrContract;
    an = ob.an;
    beneficiar = ob.beneficiar;
    furnizor = ob.furnizor;
    valoare = ob.valoare;

}

Contract::Contract(int nrContract, int an, const string & beneficiar, const string & furnizor, int valoare)
{
    this->an = an;
    this->nrContract = nrContract;
    this->beneficiar = beneficiar;
    this->furnizor = furnizor;
    this->valoare = valoare;
}

Contract::~Contract() = default;

///exceptie

void eroare_an(int x)
{
    if(x<1000 || x>2022)
        throw 11;
}

void Contract::citire(istream & in)
{
   cout<<"Numar contract: "; in>>nrContract;
   cout<<"An: ";
    int k = 1;
    while(k == 1)
    {
        try
        {
            in>>an;
            eroare_an(an);
            k = 0;
        }
        catch (int)
        {
            cout << "Anul introdus nu este valid" << endl;
            cout << "Reintroduceti\n";
        }
    }
   cout<<"Nume beneficiar: "; in>>beneficiar;
   cout<<"Furnizor: "; in>>furnizor;
   cout<<"Valoarea totala a produsului: "; in>>valoare;
}

void Contract::afisare(ostream & out)
{
    out<<"Numar contract: "; out<<nrContract<<endl;
    out<<"An: "; out<<an<<endl;
    out<<"Nume beneficiar: "; out<<beneficiar<<endl;
    out<<"Furnizor: "; out<<furnizor<<endl;
    out<<"Valoarea totala a produsului: "; out<<valoare<<" lei"<<endl;
}

class ContractInchiriere: public Contract
{
private:
    int perioada{};

public:
    ContractInchiriere();
    explicit ContractInchiriere(int perioada);
    ContractInchiriere(int nrContract, int an, const string & beneficiar, const string & furnizor, int valoare, int perioada);
    ContractInchiriere(const Contract & contract, int perioada);

    int val()
    {
        return perioada*getvaloare();
    }

    void citire(istream &);
    void afisare(ostream &);
};

void ContractInchiriere :: citire(istream & in)
{
    Contract :: citire(in);
    cout<<"Perioada contractului este: "; in>>perioada;
}

void ContractInchiriere ::afisare(ostream & out)
{
    Contract :: afisare(out);
    out<<"Perioada contractului este: ";
    out<<perioada<<" luni"<<endl;
    out<<endl;
}

ContractInchiriere::ContractInchiriere(int nrContract, int an, const string & beneficiar, const string & furnizor, int valoare, int perioada) : Contract(nrContract, an, beneficiar, furnizor, valoare), perioada(perioada) {}
ContractInchiriere::ContractInchiriere(const Contract & contract, int perioada) : Contract(contract), perioada(perioada) {}
ContractInchiriere::ContractInchiriere(int perioada) : perioada(perioada) {}
ContractInchiriere::ContractInchiriere() = default;

class Dosar
{
    vector <ContractInchiriere *> contract;
    int numarContracte{};

public:
    Dosar();

    explicit Dosar(const vector<ContractInchiriere *> & contract);
    explicit Dosar(int numarContracte);
    Dosar(const vector<ContractInchiriere *> & contract, int numarContracte);
    void afis_val()
    {
      for(int i = 0;i < contract.size(); i++)
          cout<<"Pentru contractul "<<contract[i]->getnrContract()<<" valoarea incasata este de "<<contract[i]->val()<<" de lei"<<endl;
    }
    int getval_totala()
    {
                    static int incasari_totale = 0;
                    for(int i = 0;i < contract.size(); i++)
                    {
                        int p, v;
                        incasari_totale += contract[i]->val();
                    }
                return incasari_totale;
    };
    friend istream & operator >>(istream & in, Dosar  & );
    friend ostream & operator <<(ostream & out, const Dosar & );
    void citire();
    void afisare() const;
    virtual ~Dosar();
};

Dosar::Dosar(const vector<ContractInchiriere *> & contract) : contract(contract) {}
Dosar::Dosar(int numarContracte) : numarContracte(numarContracte) {}
Dosar::Dosar(const vector<ContractInchiriere *> & contract, int numarContracte) : contract(contract), numarContracte(numarContracte) {}
Dosar::~Dosar() = default;

Dosar::Dosar()
{
    numarContracte=0;
}

istream &operator>>(istream & in, Dosar & dosar)
{
    cout<<"Numarul de contracte pe care vreti sa il adaugati : ";
    in>>dosar.numarContracte;
    dosar.citire();
    return in;
}

ostream &operator<<(ostream & out, const Dosar & dosar)
{
    cout<<"Numarul de contracte din dosar este :";
    out<<dosar.numarContracte<<endl;
    dosar.afisare();
    return out;
}

void Dosar::citire()
{
    ContractInchiriere* c = nullptr;
    for(int i = 0;i < numarContracte; i++)
    {
        c = new ContractInchiriere;
        cin>>(*c);
        contract.push_back(c);
    }
}

void Dosar::afisare() const
{
    for(int i = 0; i < numarContracte; i++)
        cout<<*contract[i]<<" ";
    cout<<endl;
}

void eroare_meniu(int x)
{
    try{
        if(x < 1 || x > 4)
         throw 1;
    }
    catch (int x){cout<<"Eroare! x-ul introdus nu este valid!"<<endl; }
}

class Meniu
{
    Dosar contracte;

public:
    void afis_meniu();
    static void afis_mesaj()
    {
        cout<<"Valoarea totala incasata este de ";
    }
};

void Meniu::afis_meniu()
{
    cout<<"1.Adauga contracte in dosar\n";
    cout<<"2.Afiseaza valoarea incasata pentru fiecare contract\n";
    cout<<"3.Afiseaza valoarea totala incasata\n";
    cout<<"4.Inchide \n";
    int x;
    cout<<"Optiunea?"<<endl;
    cin>>x;
    while(x)
    {
        eroare_meniu(x);
        switch (x)
        {
            case 1:
            {
                cin>>contracte;
                cout<<contracte;
                break;
            }
            case 2:
            {
                contracte.afis_val();
                break;
            }
            case 3:
            {
                afis_mesaj();
                cout<<contracte.getval_totala()<<" de lei"<<endl;
                break;
            }
            case 4:
                return;
        }
        cout<<"1.Adauga contracte in dosar\n";
        cout<<"2.Afiseaza valoarea incasata pentru fiecare contract\n";
        cout<<"3.Afiseaza valoarea totala incasata\n";
        cout<<"4.Inchide\n";
        cout<<"Alta optiune? "<<endl;
        cin>>x;
    }
}

int main()
{
  Meniu m;
  m.afis_meniu();
}
